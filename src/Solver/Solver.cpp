#include <iostream>
#include "Solver.h"
#include "Rules/SimplifyRules/And.h"
#include "Propositions/Negation.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Rules/SimplifyRules/Nor.h"
#include "Rules/SimplifyRules/Nif.h"
#include "Rules/InferenceRules/ConjunctiveSyllogism.h"
#include "Rules/InferenceRules/DisjunctiveSyllogism.h"
#include "Rules/InferenceRules/ModusPonens.h"
#include "Rules/InferenceRules/ModusTollens.h"

std::shared_ptr<WellFormedFormula> getInnerProposition(const std::shared_ptr<WellFormedFormula>& proposition) {
    if (auto inference = std::dynamic_pointer_cast<Inference>(proposition)) {
        return inference->getProposition();
    } else {
        return proposition;
    }
}
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
                if (sRuleResult.has_value()) {
                    isChanged = true;
                    argument.emplace_back(
                            StatementType::CONCLUSION,
                            sRuleResult.value().first,
                            leftStatement.assumptionLevel,
                            std::vector<unsigned long>{i}
                    );
                    argument.emplace_back(
                            StatementType::CONCLUSION,
                            sRuleResult.value().second,
                            leftStatement.assumptionLevel,
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
                            proposition,
                            rightStatement.assumptionLevel,
                            std::vector<unsigned long>{i, j}
                    );
                }

                auto reversedIRuleResult = findIRule(rightStatement.proposition, leftStatement.proposition);
                isChanged |= !reversedIRuleResult.empty();
                for (const auto &proposition: reversedIRuleResult) {
                    argument.emplace_back(
                            StatementType::CONCLUSION,
                            proposition,
                            rightStatement.assumptionLevel,
                            std::vector<unsigned long>{i, j}
                    );
                }
            }
        }
        startAt = currentLength;
    }
    return argument;
}

std::optional<std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>>
Solver::findSRule(const std::shared_ptr<WellFormedFormula> &proposition) {
    std::shared_ptr<WellFormedFormula> innerProposition = getInnerProposition(proposition);
    if (auto conjunction = std::dynamic_pointer_cast<Conjunction>(innerProposition)) {
        return And::from(conjunction);
    }
    if (auto negation = std::dynamic_pointer_cast<Negation>(innerProposition)) {
        auto negatedProposition = Negation::of(innerProposition);
        if (auto disjunction = std::dynamic_pointer_cast<Disjunction>(negatedProposition)) {
            return Nor::from(negation);
        }
        if (auto implication = std::dynamic_pointer_cast<Implication>(
                std::dynamic_pointer_cast<Negation>(innerProposition))) {
            return Nif::from(negation);
        }
    }
    return {};
}

std::vector<std::shared_ptr<WellFormedFormula>>
Solver::findIRule(std::shared_ptr<WellFormedFormula> propositionA,
                  std::shared_ptr<WellFormedFormula> propositionB) {
    propositionA = getInnerProposition(propositionA);
    propositionB = getInnerProposition(propositionB);
    if (auto disjunction = std::dynamic_pointer_cast<Disjunction>(propositionA)) {
        if ((*propositionB) == Negation::of(disjunction->getLeftOperand()) ||
            (*propositionB) == Negation::of(disjunction->getRightOperand())) {
            return {std::make_shared<DisjunctiveSyllogism>(disjunction, propositionB)};
        }
        return {};
    }
    if (auto negation = std::dynamic_pointer_cast<Negation>(propositionA)) {
        if (auto conjunction = std::dynamic_pointer_cast<Conjunction>(Negation::of(propositionA))) {
            if ((*propositionB) == conjunction->getLeftOperand() || (*propositionB) == conjunction->getRightOperand()) {
                return {std::make_shared<ConjunctiveSyllogism>(negation, propositionB)};
            }
        }
        return {};
    }
    if (auto implication = std::dynamic_pointer_cast<Implication>(propositionA)) {
        std::vector<std::shared_ptr<WellFormedFormula>> out;
        if ((*propositionB) == implication->getLeftOperand()) {
            out.push_back(std::make_shared<ModusPonens>(implication, propositionB));
        }
        if ((*propositionB) == Negation::of(implication->getRightOperand())) {
            out.push_back(std::make_shared<ModusTollens>(implication, propositionB));
        }
        return out;
    }
    return {};
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
