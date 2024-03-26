#include "SRules.h"
#include "Propositions/WellFormedFormula.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Equivalence.h"

std::vector<std::shared_ptr<WellFormedFormula>>
tryAndFrom(const std::shared_ptr<WellFormedFormula> &maybeConjunction) {
    auto conjunction = std::dynamic_pointer_cast<Conjunction>(maybeConjunction);
    if (!conjunction) {
        return {};
    }

    return {conjunction->getLeftOperand(), conjunction->getRightOperand()};
}

std::vector<std::shared_ptr<WellFormedFormula>>
tryNorFrom(const std::shared_ptr<WellFormedFormula> &maybeNegatedDisjunction) {
    auto disjunction = std::dynamic_pointer_cast<Disjunction>(Negation::of(maybeNegatedDisjunction));
    if (!disjunction) {
        return {};
    }
    return {Negation::of(disjunction->getLeftOperand()), Negation::of(disjunction->getRightOperand())};
}

std::vector<std::shared_ptr<WellFormedFormula>>
tryNifFrom(const std::shared_ptr<WellFormedFormula> &negatedImplication) {
    auto implication = std::dynamic_pointer_cast<Implication>(Negation::of(negatedImplication));
    if (!implication) {
        return {};
    }
    return {implication->getLeftOperand(), Negation::of(implication->getRightOperand())};
}

std::vector<std::shared_ptr<WellFormedFormula>>
tryEqFrom(const std::shared_ptr<WellFormedFormula> &maybeEquivalence) {
    auto equivalence = std::dynamic_pointer_cast<Equivalence>(maybeEquivalence);
    if (!equivalence) {
        return {};
    }
    return {std::make_shared<Implication>(equivalence->getLeftOperand(), equivalence->getRightOperand()),
            std::make_shared<Implication>(equivalence->getRightOperand(), equivalence->getLeftOperand())};
}

std::vector<std::shared_ptr<WellFormedFormula>>
tryNeqFrom(const std::shared_ptr<WellFormedFormula> &maybeNegatedEquivalence) {
    auto equivalence = std::dynamic_pointer_cast<Equivalence>(Negation::of(maybeNegatedEquivalence));
    if (!equivalence) {
        return {};
    }
    return {std::make_shared<Disjunction>(equivalence->getLeftOperand(), equivalence->getRightOperand()),
            Negation::of(std::make_shared<Conjunction>(equivalence->getLeftOperand(), equivalence->getRightOperand()))};
}