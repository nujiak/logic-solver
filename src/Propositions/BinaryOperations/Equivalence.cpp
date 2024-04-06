
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

std::shared_ptr<WellFormedFormula> Equivalence::replaceSingularTerm(char from, char to, bool isTopLevel) const {
    return std::make_shared<Equivalence>(this->leftOperand->replaceSingularTerm(from, to, false),
                                         this->rightOperand->replaceSingularTerm(from, to, false));
}
