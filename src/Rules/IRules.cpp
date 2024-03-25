#include "IRules.h"
#include <memory>
#include "Propositions/WellFormedFormula.h"
#include "Propositions/Negation.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Conjunction.h"

std::shared_ptr<WellFormedFormula> tryModusTollensFrom(const std::shared_ptr<WellFormedFormula> &maybeImplication,
                                                       const std::shared_ptr<WellFormedFormula> &consequence) {
    auto implication = std::dynamic_pointer_cast<Implication>(maybeImplication);
    if (!implication) {
        return {};
    }
    auto negatedRightOperand = Negation::of(implication->getRightOperand());
    if ((*consequence) != negatedRightOperand) {
        return {};
    }
    return Negation::of(implication->getLeftOperand());
}

std::shared_ptr<WellFormedFormula> tryModusPonensFrom(const std::shared_ptr<WellFormedFormula> &maybeImplication,
                                                      const std::shared_ptr<WellFormedFormula> &antecedent) {
    auto implication = std::dynamic_pointer_cast<Implication>(maybeImplication);
    if (!implication) {
        return {};
    }
    if ((*antecedent) != implication->getLeftOperand()) {
        return {};
    }
    return implication->getRightOperand();
}

std::shared_ptr<WellFormedFormula> tryDisjunctiveSyllogismFrom(
        const std::shared_ptr<WellFormedFormula> &maybeDisjunction,
        const std::shared_ptr<WellFormedFormula> &secondProposition) {
    auto disjunction = std::dynamic_pointer_cast<Disjunction>(maybeDisjunction);
    if (!disjunction) {
        return {};
    }
    if ((*secondProposition) == Negation::of(disjunction->getLeftOperand())) {
        return disjunction->getRightOperand();
    } else if ((*secondProposition) == Negation::of(disjunction->getRightOperand())) {
        return disjunction->getLeftOperand();
    }
    return {};
}

std::shared_ptr<WellFormedFormula>
tryConjunctiveSyllogismFrom(const std::shared_ptr<WellFormedFormula> &maybeNegatedConjunction,
                            const std::shared_ptr<WellFormedFormula> &secondProposition) {
    auto embeddedConjunction = std::dynamic_pointer_cast<Conjunction>(Negation::of(maybeNegatedConjunction));
    if (!embeddedConjunction) {
        return {};
    }
    if (secondProposition == embeddedConjunction->getLeftOperand()) {
        return Negation::of(embeddedConjunction->getRightOperand());
    } else if (secondProposition == embeddedConjunction->getRightOperand()) {
        return Negation::of(embeddedConjunction->getLeftOperand());
    }
    return {};
}
