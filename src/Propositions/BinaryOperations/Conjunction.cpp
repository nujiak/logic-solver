#include "Conjunction.h"

std::string Conjunction::getString() const {
    return BinaryOperation::getString('&');
}

bool Conjunction::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto otherConjunction = std::dynamic_pointer_cast<Conjunction>(other)) {
        return ((this->leftOperand == otherConjunction->leftOperand) &&
                (this->rightOperand == otherConjunction->rightOperand)) ||
               ((this->leftOperand == otherConjunction->rightOperand) &&
                (this->rightOperand == otherConjunction->leftOperand));
    }
    return false;
}

std::shared_ptr<WellFormedFormula> Conjunction::replaceSingularTerm(char from, char to, bool isTopLevel) const {
    return std::make_shared<Conjunction>(this->leftOperand->replaceSingularTerm(from, to, false),
                                         this->rightOperand->replaceSingularTerm(from, to, false));
}
