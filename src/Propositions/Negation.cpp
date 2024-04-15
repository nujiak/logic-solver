#include "Negation.h"

std::string Negation::getString() const {
    return "~" + this->operand->getString();
}

std::shared_ptr<WellFormedFormula> Negation::of(const std::shared_ptr<WellFormedFormula> &proposition) {
    if (auto negation = std::dynamic_pointer_cast<Negation>(proposition)) {
        return negation->operand;
    } else {
        Negation newNegation{proposition};
        return std::make_shared<Negation>(newNegation);
    }
}

bool Negation::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto otherNegation = std::dynamic_pointer_cast<Negation>(other)) {
        return (*this->operand) == otherNegation->operand;
    }
    return false;
}

std::shared_ptr<WellFormedFormula> Negation::replaceSingularTerm(char to, bool isTopLevel) const {
    return this->operand->replaceSingularTerm(to, false);
}

std::unordered_set<char> Negation::getSingularTerms() const {
    return this->operand->getSingularTerms();
}

