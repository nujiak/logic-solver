#include "IRule.h"

bool IRule::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    return this->resultantProposition == other;
}

std::string IRule::getString() const {
    return this->resultantProposition->getString();
}
