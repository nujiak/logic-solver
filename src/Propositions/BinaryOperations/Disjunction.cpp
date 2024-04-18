#include "Disjunction.h"

std::string Disjunction::getString() const {
    return BinaryOperation::getString('@');
}

bool Disjunction::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto otherDisjunction = std::dynamic_pointer_cast<Disjunction>(other)) {
        return ((*this->leftOperand == otherDisjunction->leftOperand) &&
                (*this->rightOperand == otherDisjunction->rightOperand)) ||
               ((*this->leftOperand == otherDisjunction->rightOperand) &&
                (*this->rightOperand == otherDisjunction->leftOperand));
    }
    return false;
}

std::shared_ptr<WellFormedFormula> Disjunction::replaceSingularTerm(char to, bool isTopLevel) const {
    return std::make_shared<Disjunction>(this->leftOperand->replaceSingularTerm(to, false),
                                         this->rightOperand->replaceSingularTerm(to, false));
}
