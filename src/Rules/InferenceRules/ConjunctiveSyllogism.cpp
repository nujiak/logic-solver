#include "ConjunctiveSyllogism.h"
#include "Propositions/Negation.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include <stdexcept>

ConjunctiveSyllogism::ConjunctiveSyllogism(const std::shared_ptr<Negation> &negatedConjunction,
                                           const std::shared_ptr<WellFormedFormula> &secondProposition) {
    if (auto embeddedConjunction = std::dynamic_pointer_cast<Conjunction>(Negation::of(negatedConjunction))) {
        if (secondProposition == embeddedConjunction->getLeftOperand()) {
            resultantProposition = Negation::of(embeddedConjunction->getRightOperand());
        } else if (secondProposition == embeddedConjunction->getRightOperand()) {
            resultantProposition = Negation::of(embeddedConjunction->getLeftOperand());
        } else {
            throw std::invalid_argument(
                    "Conjunctive syllogism: second proposition must be one of the embedded conjunction operands");
        }
    } else {
        throw std::invalid_argument(
                "Conjunctive syllogism: negatedConjunction did not contain an embedded conjunction (" +
                negatedConjunction->getString() + ")");
    }

    this->negatedConjunction = negatedConjunction;
    this->secondProposition = secondProposition;
}

std::string ConjunctiveSyllogism::getString() const {
    return this->resultantProposition->getString();
}
