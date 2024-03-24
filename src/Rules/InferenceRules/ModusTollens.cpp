#include "ModusTollens.h"
#include "Propositions/Negation.h"
#include <stdexcept>

ModusTollens::ModusTollens(const std::shared_ptr<Implication> &implication,
                           const std::shared_ptr<WellFormedFormula> &antecedent) {
    if ((*antecedent) != Negation::of(implication->getRightOperand())) {
        throw std::invalid_argument("Modus tollens: given proposition is not the negated consequent of implication");
    }
    this->implication = implication;
    this->antecedent = antecedent;
    this->resultantProposition = Negation::of(implication->getLeftOperand());
}
