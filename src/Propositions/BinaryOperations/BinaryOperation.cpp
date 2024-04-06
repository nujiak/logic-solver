#include "BinaryOperation.h"

std::string BinaryOperation::getString(char operatorSymbol) const {
    return "(" + this->leftOperand->getString() + operatorSymbol + this->rightOperand->getString() + ")";
}

std::shared_ptr<WellFormedFormula> BinaryOperation::getLeftOperand() const {
    return this->leftOperand;
}

std::shared_ptr<WellFormedFormula> BinaryOperation::getRightOperand() const {
    return this->rightOperand;
}

std::unordered_set<char> BinaryOperation::getSingularTerms() const {
    auto leftSingularTerms = this->leftOperand->getSingularTerms();
    auto rightSingularTerms = this->rightOperand->getSingularTerms();
    leftSingularTerms.insert(rightSingularTerms.begin(), rightSingularTerms.end());
    return leftSingularTerms;
}

