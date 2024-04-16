#include <unordered_set>
#include <unordered_map>
#include "Solver.h"
#include "Propositions/Negation.h"
#include "Rules/IRules.h"
#include "Rules/SRules.h"
#include "Propositions/Variable.h"
#include "Propositions/Quantifiers/ForAll.h"
#include "Propositions/Quantifiers/ForEach.h"
#include <stdexcept>

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
    std::vector<size_t> frontier;
    if (isProof) {
        frontier.push_back(proof.size() - 1);
    } else {
        std::unordered_set<std::string> foundVariables;
        for (size_t i = proof.size() - 1; i < proof.size(); i--) {
            const auto& statement = proof[i];
            if (auto variable = std::dynamic_pointer_cast<Variable>(statement.proposition)) {
                if (!foundVariables.contains(variable->getString())) {
                    foundVariables.insert(variable->getString());
                    frontier.push_back(i);
                }
            } else if (auto negatedVariable = std::dynamic_pointer_cast<Variable>(
                    Negation::of(statement.proposition))) {
                if (!foundVariables.contains(negatedVariable->getString())) {
                    foundVariables.insert(negatedVariable->getString());
                    frontier.push_back(i);
                }
            }
        }
    }
    std::unordered_set<size_t> travelled;
    while (!frontier.empty()) {
        size_t index = frontier.back();
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
    std::unordered_map<size_t, size_t> adjustedIndex;
    for (int i = 0; i < proof.size(); i++) {
        const auto &statement = proof[i];
        if (statement.unused && statement.type != StatementType::PREMISE){
            continue;
        }
        adjustedIndex[i] = out.size();
        std::vector<size_t> adjustedReferences;
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
                statement.brokenLevel,
                statement.unused,
                statement.skip,
        };
        out.push_back(newStatement);
    }
    return out;
}

std::shared_ptr<WellFormedFormula> tryBreakComplexWff(const std::shared_ptr<WellFormedFormula> &maybeComplexWff) {
    if (auto implication = std::dynamic_pointer_cast<Implication>(maybeComplexWff)) {
        return Negation::of(implication->getLeftOperand());
    }

    if (auto embeddedConjunction = std::dynamic_pointer_cast<Conjunction>(Negation::of(maybeComplexWff))) {
        return Negation::of(embeddedConjunction->getLeftOperand());
    }

    if (auto disjunction = std::dynamic_pointer_cast<Disjunction>(maybeComplexWff)) {
        return disjunction->getLeftOperand();
    }

    return {};
}

/**
 * Performs reverse squiggles on any negated quantifiers
 * @param startAt
 * @param currentAssumptions
 * @param argument
 */
void reverseSquiggles(const size_t startAt, const std::vector<std::pair<size_t, Statement>> &currentAssumptions,
                      std::vector<Statement> &argument) {// Reverse squiggles
    const size_t currentLength = argument.size();
    for (size_t i = startAt; i < currentLength; i++) {
        Statement &statement = argument[i];
        if (statement.brokenLevel > 0) {
            continue;
        }
        if (auto embeddedForAll = std::dynamic_pointer_cast<ForAll>(Negation::of(statement.proposition))) {
            statement.brokenLevel = currentAssumptions.size();
            argument.emplace_back(
                    StatementType::CONCLUSION,
                    std::make_shared<ForEach>(Negation::of(embeddedForAll->getProposition())),
                    currentAssumptions.size(),
                    Rule::NONE,
                    std::vector<size_t>{i}
            );
        } else if (auto embeddedForEach = std::dynamic_pointer_cast<ForEach>(Negation::of(statement.proposition))) {
            statement.brokenLevel = currentAssumptions.size();
            argument.emplace_back(
                    StatementType::CONCLUSION,
                    std::make_shared<ForAll>(Negation::of(embeddedForEach->getProposition())),
                    currentAssumptions.size(),
                    Rule::NONE,
                    std::vector<size_t>{i}
            );
        }
    }
}

/**
 * Performs drop existentials on any unbroken existential quantifiers
 * @param startAt
 * @param currentAssumptions
 * @param argument
 * @param singularTerms
 */
void dropExistentials(const size_t startAt, const std::vector<std::pair<size_t, Statement>> &currentAssumptions,
                      std::vector<Statement> &argument,
                      std::unordered_set<char> &singularTerms) {
    const size_t currentLength = argument.size();
    char nextSingularTerm = 'a';
    for (size_t i = startAt; i < currentLength; i++) {
        Statement &statement = argument[i];
        if (statement.blocked || statement.skip || statement.brokenLevel > 0) {
            continue;
        }
        if (const auto forEach = std::dynamic_pointer_cast<ForEach>(statement.proposition)) {
            while (singularTerms.contains(nextSingularTerm) || nextSingularTerm == 'x') {
                nextSingularTerm++;
            }
            if (nextSingularTerm > 'z') {
                throw std::overflow_error("Singular terms exceeded z, argument may be too long");
            }
            statement.brokenLevel = currentAssumptions.size();
            argument.emplace_back(
                    StatementType::CONCLUSION,
                    forEach->getProposition()->replaceSingularTerm(nextSingularTerm, true),
                    currentAssumptions.size(),
                    Rule::NONE,
                    std::vector<size_t>{i}
            );
            singularTerms.insert(nextSingularTerm);
        }
    }
}

/**
 * Performs drop universals on any universal quantifiers not broken with singular terms from a given set
 * @param currentAssumptions
 * @param argument
 * @param singularTerms
 */
void
dropUniversals(const std::vector<std::pair<size_t, Statement>> &currentAssumptions, std::vector<Statement> &argument,
               const std::unordered_set<char> &singularTerms) {
    const size_t currentLength = argument.size();
    for (size_t i = 0; i < currentLength; i++) {
        argument.reserve(singularTerms.size());
        Statement &statement = argument[i];
        if (statement.blocked || statement.skip) {
            continue;
        }
        const auto forAll = std::dynamic_pointer_cast<ForAll>(statement.proposition);
        if (!forAll) {
            continue;
        }
        for (const auto singularTerm: singularTerms) {
            if (!statement.brokenSingularTerms.contains(singularTerm)) {
                statement.brokenSingularTerms.insert(singularTerm);
                argument.emplace_back(
                        StatementType::CONCLUSION,
                        forAll->getProposition()->replaceSingularTerm(singularTerm, true),
                        currentAssumptions.size(),
                        Rule::NONE,
                        std::vector<size_t>{i}
                );
            }
        }
    }
}

/**
 * Performs reverse squiggles, drop existentials and drop universals
 * @param startAt
 * @param currentAssumptions
 * @param argument
 * @return true if new statements have been added
 */
bool handleQuantificationalStatements(size_t startAt,
                                      const std::vector<std::pair<size_t, Statement>> &currentAssumptions,
                                      std::vector<Statement> &argument) {
    size_t initialNumStatements = argument.size();

    reverseSquiggles(startAt, currentAssumptions, argument);

    std::unordered_set<char> singularTerms{};
    // combine all singular terms used across all statements
    for (const auto &statement: argument) {
        const auto statementSingularTerms = statement.proposition->getSingularTerms();
        singularTerms.insert(statementSingularTerms.begin(), statementSingularTerms.end());
    }
    singularTerms.erase('x');

    dropExistentials(startAt, currentAssumptions, argument, singularTerms);
    dropUniversals(currentAssumptions, argument, singularTerms);
    return argument.size() > initialNumStatements;
}

std::vector<Statement> solve(std::vector<Statement> argument) {
    bool isChanged = true;
    bool canBreak = true;
    size_t startAt = 0;
    bool isProven = false;

    verifyInitialArgument(argument);

    std::vector<std::pair<size_t, Statement>> currentAssumptions;

    // Set up proof by contradiction
    argument.back().blocked = true;
    argument.emplace_back(
            StatementType::ASSUMPTION,
            Negation::of(argument.back().proposition),
            0,
            Rule::NONE,
            std::vector<size_t>{argument.size() - 1}
    );
    currentAssumptions.emplace_back(argument.size() - 1, argument.back());

    while (isChanged || canBreak) {
        bool lastIterationNoChange = !isChanged;
        if (lastIterationNoChange) {
            canBreak = false;
        }
        isChanged = false;

        isChanged |= handleQuantificationalStatements(startAt, currentAssumptions, argument);

        unsigned long currentLength = argument.size();
        for (size_t i = 0; i < currentLength; i++) {
            // Reserve space on argument to prevent reallocation and reference invalidation
            // on adding s-rule and i-rule results
            argument.reserve( argument.size() + 3 + currentLength - startAt);
            Statement& leftStatement = argument[i];
            if (leftStatement.blocked || leftStatement.skip) {
                continue;
            }
            // Break implication if no new statements were added last iteration
            if (lastIterationNoChange && leftStatement.brokenLevel == 0) {
                if (auto brokenProposition = tryBreakComplexWff(leftStatement.proposition)) {
                    leftStatement.brokenLevel = currentAssumptions.size() + 1;
                    argument.emplace_back(StatementType::ASSUMPTION,
                                          brokenProposition,
                                          leftStatement.brokenLevel,
                                          Rule::BREAK,
                                          std::vector<size_t>{i});
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
                            currentAssumptions.size(),
                            result.rule,
                            std::vector<size_t>{i}
                    );
                }
            }

            for (size_t j = std::max(i + 1, startAt); j < currentLength; j++) {
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
                            std::vector<size_t>{currentAssumptions.back().first, i, j}
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
                                currentAssumptions.size(),
                                proposition.rule,
                                std::vector<size_t>{i, j}
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
                                currentAssumptions.size(),
                                proposition.rule,
                                std::vector<size_t>{i, j}
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
