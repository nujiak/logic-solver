#include "Nif.h"
#include "Propositions/BinaryOperations/Implication.h"

std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>
Nif::from(const std::shared_ptr<Negation> &negatedImplication) {
    if (auto implication = std::dynamic_pointer_cast<Implication>(Negation::of(negatedImplication))) {
        auto inferenceLeft = new Nif(negatedImplication, implication->getLeftOperand());
        auto inferenceRight = new Nif(negatedImplication, Negation::of(implication->getRightOperand()));
        return {std::shared_ptr<Nif>(inferenceLeft), std::shared_ptr<Nif>(inferenceRight)};
    } else {
        throw std::invalid_argument("Nor: given proposition should be a negated disjunction");
    }
}
