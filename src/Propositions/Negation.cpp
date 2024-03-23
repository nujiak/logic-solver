#include "Negation.h"

std::string Negation::getString() const {
    return "!" + this->operand->getString();
}

std::shared_ptr<WellFormedFormula> Negation::of(std::shared_ptr<WellFormedFormula> proposition) {
    if (auto negation = std::dynamic_pointer_cast<Negation>(proposition)) {
        return negation->operand;
    } else {
        Negation newNegation{proposition};
        return std::make_shared<Negation>(newNegation);
    }
}

