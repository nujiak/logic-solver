#include "BinaryOperation.h"

std::string BinaryOperation::getString(char operatorSymbol) const {
    return "(" + this->leftOperand->getString() + " " + operatorSymbol + " " + this->rightOperand->getString() + ")";
}

