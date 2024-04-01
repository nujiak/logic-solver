#include <unordered_set>
#include <unordered_map>
#include "Solver.h"
#include "Propositions/Negation.h"
#include "Rules/IRules.h"
#include "Rules/SRules.h"
#include "Propositions/Variable.h"

struct InferredProposition {
    Rule rule;
    std::shared_ptr<WellFormedFormula> proposition;
};

std::vector<InferredProposition>
findSRule(const std::shared_ptr<WellFormedFormula> &proposition) {
    std::vector<InferredProposition> out;

    auto andResults = tryAndFrom(proposition);
    for (const auto &andResult: andResults) {
        out.emplace_back(Rule::AND, andResult);
    }

    auto norResults = tryNorFrom(proposition);
    for (const auto &norResult: norResults) {
        out.emplace_back(Rule::NOR, norResult);
    }

    auto nifResults = tryNifFrom(proposition);
    for (const auto &nifResult: nifResults) {
        out.emplace_back(Rule::NIF, nifResult);
    }

    auto eqResults = tryEqFrom(proposition);
    for (const auto &eqResult: eqResults) {
        out.emplace_back(Rule::EQ, eqResult);
    }

    auto neqResults = tryNeqFrom(proposition);
    for (const auto &neqResult: neqResults) {
        out.emplace_back(Rule::NEQ, neqResult);
    }

    return out;
}

std::vector<InferredProposition>
findIRule(const std::shared_ptr<WellFormedFormula> &propositionA,
          const std::shared_ptr<WellFormedFormula> &propositionB) {
    std::vector<InferredProposition> out;
    if (auto dsResult = tryDisjunctiveSyllogismFrom(propositionA, propositionB)) {
        out.emplace_back(Rule::DS, dsResult);
    }
    if (auto csResult = tryConjunctiveSyllogismFrom(propositionA, propositionB)) {
        out.emplace_back(Rule::CS, csResult);
    }
    if (auto mpResult = tryModusPonensFrom(propositionA, propositionB)) {
        out.emplace_back(Rule::MP, mpResult);
    }
    if (auto mtResult = tryModusTollensFrom(propositionA, propositionB)) {
        out.emplace_back(Rule::MT, mtResult);
    }
    if (auto iffResult = tryIffFrom(propositionA, propositionB)) {
        out.emplace_back(Rule::IFF, iffResult);
    }
    if (auto niffResult = tryNiffFrom(propositionA, propositionB)) {
        out.emplace_back(Rule::NIFF, niffResult);
    }
    return out;
}

void verifyInitialArgument(const std::vector<Statement> &argument) {
    for (auto i = 0; i < argument.size() - 1; i++) {
        if (argument[i].type != StatementType::PREMISE) {
            throw std::invalid_argument(
                    "argument should contain only premise statements and 1 conclusion statement as the last item");
        }
    }
    if (argument.back().type != StatementType::CONCLUSION) {
        throw std::invalid_argument(
                "argument should contain only premise statements and 1 conclusion statement as the last item");
    }
}

std::vector<Statement> simplifyProof(std::vector<Statement> &proof, bool isProof) {
    for (Statement &statement: proof) {
        statement.unused = true;
    }
    std::vector<unsigned long> frontier;
    if (isProof) {
        frontier.push_back(proof.size() - 1);
    } else {
        std::unordered_set<char> foundVariables;
        for (unsigned long i = proof.size() - 1; i < proof.size(); i--) {
            const auto& statement = proof[i];
            if (auto variable = std::dynamic_pointer_cast<Variable>(statement.proposition)) {
                if (!foundVariables.contains(variable->getName())) {
                    foundVariables.insert(variable->getName());
                    frontier.push_back(i);
                }
            } else if (auto negatedVariable = std::dynamic_pointer_cast<Variable>(
                    Negation::of(statement.proposition))) {
                if (!foundVariables.contains(negatedVariable->getName())) {
                    foundVariables.insert(negatedVariable->getName());
                    frontier.push_back(i);
                }
            }
        }
    }
    std::unordered_set<unsigned long> travelled;
    while (!frontier.empty()) {
        unsigned long index = frontier.back();
        frontier.pop_back();
        travelled.insert(index);
        auto& statement = proof[index];
        statement.unused = false;
        for (auto reference: statement.references) {
            if (!travelled.contains(reference)) {
                frontier.push_back(reference);
            }
        }
    }

    std::vector<Statement> out;
    std::unordered_map<unsigned long, unsigned long> adjustedIndex;
    for (int i = 0; i < proof.size(); i++) {
        const auto &statement = proof[i];
        if (statement.unused && statement.type != StatementType::PREMISE){
            continue;
        }
        adjustedIndex[i] = out.size();
        std::vector<unsigned long> adjustedReferences;
        adjustedReferences.reserve(statement.references.size());
        for (auto reference: statement.references) {
            adjustedReferences.push_back(adjustedIndex[reference]);
        }

        Statement newStatement{
                statement.type,
                statement.proposition,
                statement.assumptionLevel,
                statement.rule,
                adjustedReferences,
                statement.blocked,
                statement.assumptionCompleted,
                statement.brokenLevel,
                statement.unused,
                statement.skip,
        };
        out.push_back(newStatement);
    }
    return out;
}

std::shared_ptr<WellFormedFormula> tryBreakImplication(const std::shared_ptr<WellFormedFormula> &maybeImplication) {
    auto implication = std::dynamic_pointer_cast<Implication>(maybeImplication);
    if (!implication) {
        return {};
    }
    return Negation::of(implication->getLeftOperand());
}

std::vector<Statement> solve(std::vector<Statement> argument) {
    bool isChanged = true;
    bool canBreak = true;
    unsigned long startAt = 0;
    bool isProven = false;

    verifyInitialArgument(argument);

    std::vector<std::pair<unsigned long, Statement>> currentAssumptions;

    // Set up proof by contradiction
    argument.back().blocked = true;
    argument.emplace_back(
            StatementType::ASSUMPTION,
            Negation::of(argument.back().proposition),
            0,
            Rule::NONE,
            std::vector<unsigned long>{argument.size() - 1}
    );
    currentAssumptions.emplace_back(argument.size() - 1, argument.back());

    while (isChanged || canBreak) {
        bool lastIterationNoChange = !isChanged;
        if (lastIterationNoChange) {
            canBreak = false;
        }
        isChanged = false;
        auto currentLength = argument.size();
        for (unsigned long i = 0; i < currentLength; i++) {
            // Reserve space on argument to prevent reallocation and reference invalidation
            // on adding s-rule and i-rule results
            argument.reserve( argument.size() + 3 + currentLength - startAt);
            Statement& leftStatement = argument[i];
            if (leftStatement.blocked || leftStatement.skip) {
                continue;
            }
            // Break implication if no new statements were added last iteration
            if (lastIterationNoChange && leftStatement.brokenLevel == 0) {
                if (auto brokenProposition = tryBreakImplication(leftStatement.proposition)) {
                    leftStatement.brokenLevel = currentAssumptions.size();
                    argument.emplace_back(StatementType::ASSUMPTION,
                                          brokenProposition,
                                          leftStatement.assumptionLevel + 1,
                                          Rule::BREAK,
                                          std::vector<unsigned long>{i});
                    currentAssumptions.emplace_back(argument.size() - 1, argument.back());
                    canBreak = true;
                    isChanged = true;
                    break;
                }
            }
            if (i >= startAt) {
                auto sRuleResult = findSRule(leftStatement.proposition);
                isChanged |= !sRuleResult.empty();
                for (const auto &result: sRuleResult) {
                    argument.emplace_back(
                            StatementType::CONCLUSION,
                            result.proposition,
                            leftStatement.assumptionLevel,
                            result.rule,
                            std::vector<unsigned long>{i}
                    );
                }
            }

            for (unsigned long j = std::max(i + 1, startAt); j < currentLength; j++) {
                Statement& rightStatement = argument[j];
                if (rightStatement.blocked || rightStatement.skip) {
                    continue;
                }

                // Check for contradiction
                if ((*leftStatement.proposition) == Negation::of(rightStatement.proposition)) {
                    isChanged = true;
                    argument.emplace_back(
                            StatementType::CONTRADICTION,
                            Negation::of(currentAssumptions.back().second.proposition),
                            currentAssumptions.size() <= 1 ? 0 : currentAssumptions.size() - 2,
                            Rule::NONE,
                            std::vector<unsigned long>{currentAssumptions.back().first, i, j}
                    );
                    currentAssumptions.pop_back();

                    // Un-break all statements broken after last assumption
                    for (Statement& statement: argument) {
                        if (statement.brokenLevel >= currentAssumptions.size()) {
                            statement.brokenLevel = 0;
                        }
                    }
                    if (currentAssumptions.empty()) {
                        isProven = true;
                        goto SolverEnd;
                    } else {
                        for (auto statement = argument.end() - 2; statement >= argument.begin(); statement--) {
                            if (statement->assumptionLevel < rightStatement.assumptionLevel) {
                                break;
                            }
                            statement->skip = true;
                        }
                    }
                }

                if (leftStatement.brokenLevel == 0) {
                    auto iRuleResult = findIRule(leftStatement.proposition, rightStatement.proposition);
                    if (!iRuleResult.empty()) {
                        isChanged = true;
                        leftStatement.brokenLevel = currentAssumptions.size();
                    }
                    for (const auto &proposition: iRuleResult) {
                        argument.emplace_back(
                                StatementType::CONCLUSION,
                                proposition.proposition,
                                rightStatement.assumptionLevel,
                                proposition.rule,
                                std::vector<unsigned long>{i, j}
                        );
                    }
                }

                if (rightStatement.brokenLevel == 0) {
                    auto reversedIRuleResult = findIRule(rightStatement.proposition, leftStatement.proposition);
                    if (!reversedIRuleResult.empty()) {
                        isChanged = true;
                        rightStatement.brokenLevel = currentAssumptions.size();
                    }
                    for (const auto &proposition: reversedIRuleResult) {
                        argument.emplace_back(
                                StatementType::CONCLUSION,
                                proposition.proposition,
                                rightStatement.assumptionLevel,
                                proposition.rule,
                                std::vector<unsigned long>{i, j}
                        );
                    }
                }

            }
        }
        startAt = currentLength;
    }
    SolverEnd:
    return simplifyProof(argument, isProven);
}
