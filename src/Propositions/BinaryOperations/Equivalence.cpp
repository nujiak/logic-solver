
#include "Equivalence.h"

std::string Equivalence::getString() const {
    return BinaryOperation::getString('=');
}

bool Equivalence::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto otherEquivalence = std::dynamic_pointer_cast<Equivalence>(other)) {
        return ((this->leftOperand == otherEquivalence->leftOperand) &&
                (this->rightOperand == otherEquivalence->rightOperand)) ||
               ((this->leftOperand == otherEquivalence->rightOperand) &&
                (this->rightOperand == otherEquivalence->leftOperand));
    }
    return false;
}
