#include "Quantifier.h"

std::shared_ptr<WellFormedFormula> Quantifier::getProposition() const {
    return this->proposition;
}
