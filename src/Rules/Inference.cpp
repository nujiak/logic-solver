#include "Inference.h"

bool Inference::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    return this->resultantProposition == other;
}

std::string Inference::getString() const {
    return this->resultantProposition->getString();
}

std::shared_ptr<WellFormedFormula> Inference::getProposition() const {
    return resultantProposition;
}
