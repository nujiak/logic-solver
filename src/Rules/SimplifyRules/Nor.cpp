#include "Nor.h"
#include "Propositions/BinaryOperations/Disjunction.h"

std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>
Nor::from(const std::shared_ptr<Negation> &negatedDisjunction) {
    if (auto disjunction = std::dynamic_pointer_cast<Disjunction>(Negation::of(negatedDisjunction))) {
        auto inferenceLeft = new Nor(negatedDisjunction, Negation::of(disjunction->getLeftOperand()));
        auto inferenceRight = new Nor(negatedDisjunction, Negation::of(disjunction->getRightOperand()));
        return {std::shared_ptr<Nor>(inferenceLeft), std::shared_ptr<Nor>(inferenceRight)};
    } else {
        throw std::invalid_argument("Nor: given proposition should be a negated disjunction");
    }
}
