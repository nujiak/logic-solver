#include "Quantifier.h"

std::shared_ptr<WellFormedFormula> Quantifier::getProposition() const {
    return this->proposition;
}

std::unordered_set<char> Quantifier::getSingularTerms() const {
    return this->proposition->getSingularTerms();
}
