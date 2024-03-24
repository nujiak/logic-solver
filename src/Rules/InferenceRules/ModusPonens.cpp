#include "ModusPonens.h"
#include "Propositions/Negation.h"
#include <stdexcept>

ModusPonens::ModusPonens(const std::shared_ptr<Implication> &implication,
                         const std::shared_ptr<WellFormedFormula> &antecedent) {
    if ((*antecedent) != implication->getLeftOperand()) {
        throw std::invalid_argument("Modus ponens: given proposition is not the antecedent of implication");
    }
    this->implication = implication;
    this->antecedent = antecedent;
    this->resultantProposition = implication->getRightOperand();
}
