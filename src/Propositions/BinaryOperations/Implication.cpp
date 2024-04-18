#include "Implication.h"

std::string Implication::getString() const {
    return BinaryOperation::getString('>');
}

bool Implication::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto otherImplication = std::dynamic_pointer_cast<Implication>(other)) {
        return (*this->leftOperand == otherImplication->leftOperand) &&
               (*this->rightOperand == otherImplication->rightOperand);
    }
    return false;
}

std::shared_ptr<WellFormedFormula> Implication::replaceSingularTerm(char to, bool isTopLevel) const {
    return std::make_shared<Implication>(this->leftOperand->replaceSingularTerm(to, false),
                                         this->rightOperand->replaceSingularTerm(to, false));
}
