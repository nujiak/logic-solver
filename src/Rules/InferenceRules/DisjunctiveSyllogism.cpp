#include "DisjunctiveSyllogism.h"
#include "Propositions/Negation.h"

DisjunctiveSyllogism::DisjunctiveSyllogism(const std::shared_ptr<Disjunction> &disjunction,
                                           const std::shared_ptr<WellFormedFormula> &secondProposition) {
    if ((*secondProposition) == Negation::of(disjunction->getLeftOperand())) {
        resultantProposition = disjunction->getRightOperand();
    } else if ((*secondProposition) == Negation::of(disjunction->getRightOperand())) {
        resultantProposition = disjunction->getLeftOperand();
    } else {
        throw std::invalid_argument(
                "Disjunctive syllogism: second proposition must be the negation of one of the disjunction operands");
    }
    this->disjunction = disjunction;
    this->secondProposition = secondProposition;
}
