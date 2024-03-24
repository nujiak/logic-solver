#include <iostream>
#include "Solver.h"
#include "Propositions/Negation.h"
#include "Rules/IRules.h"
#include "Rules/SRules.h"

std::vector<Statement> Solver::solve(std::vector<Statement> argument) {
    bool isChanged = true;
    unsigned long startAt = 0;
    verifyInitialArgument(argument);
    std::vector<Statement> currentAssumptions{argument.back()};

    // Set up proof by contradiction
    argument.back().blocked = true;
    argument.emplace_back(
            StatementType::CONCLUSION,
            Negation::of(argument.back().proposition),
            0
    );

    while (isChanged) {
        isChanged = false;
        auto currentLength = argument.size();
        for (unsigned long i = 0; i < currentLength; i++) {
            Statement leftStatement = argument[i];
            if (leftStatement.blocked) {
                continue;
            }
            if (i >= startAt) {
                std::cout << i << "*: " << leftStatement.getString() << "\n";
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
            } else {
                std::cout << i << ": " << leftStatement.getString() << "\n";
            }

            for (unsigned long j = std::max(i + 1, startAt); j < currentLength; j++) {
                Statement rightStatement = argument[j];
                std::cout << "\t" << j << ": " << rightStatement.getString() << "\n";
                if (rightStatement.blocked) {
                    continue;
                }

                // Check for contradiction
                if ((*leftStatement.proposition) == Negation::of(rightStatement.proposition)) {
                    argument.emplace_back(
                            StatementType::CONTRADICTION,
                            Negation::of(currentAssumptions.back().proposition),
                            currentAssumptions.size() - 1
                    );
                    currentAssumptions.pop_back();
                    if (currentAssumptions.empty()) {
                        return argument;
                    }
                }

                auto iRuleResult = findIRule(leftStatement.proposition, rightStatement.proposition);
                isChanged |= !iRuleResult.empty();
                for (const auto &proposition: iRuleResult) {
                    argument.emplace_back(
                            StatementType::CONCLUSION,
                            proposition.proposition,
                            rightStatement.assumptionLevel,
                            proposition.rule,
                            std::vector<unsigned long>{i, j}
                    );
                }

                auto reversedIRuleResult = findIRule(rightStatement.proposition, leftStatement.proposition);
                isChanged |= !reversedIRuleResult.empty();
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
        startAt = currentLength;
    }
    return argument;
}

std::vector<InferredProposition>
Solver::findSRule(const std::shared_ptr<WellFormedFormula> &proposition) {
    std::vector<InferredProposition> out;
    auto andResults = tryAndFrom(proposition);
    if (!andResults.empty()) {
        for (const auto &andResult: andResults) {
            out.emplace_back(Rule::AND, andResult);
        }
    }
    auto norResults = tryNorFrom(proposition);
    if (!norResults.empty()) {
        for (const auto &norResult: norResults) {
            out.emplace_back(Rule::NOR, norResult);
        }
    }
    auto nifResults = tryNifFrom(proposition);
    if (!nifResults.empty()) {
        for (const auto &nifResult: nifResults) {
            out.emplace_back(Rule::NIF, nifResult);
        }
    }
    return out;
}

std::vector<InferredProposition>
Solver::findIRule(const std::shared_ptr<WellFormedFormula> &propositionA,
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
    return out;
}

void Solver::verifyInitialArgument(const std::vector<Statement> &argument) {
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
