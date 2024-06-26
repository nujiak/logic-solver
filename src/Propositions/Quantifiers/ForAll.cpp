#include "ForAll.h"

bool ForAll::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto forAll = std::dynamic_pointer_cast<ForAll>(other)) {
        return (*this->proposition) == forAll->proposition;
    }
    return false;
}

std::string ForAll::getString() const {
    return "(x)" + this->proposition->getString();
}

std::shared_ptr<WellFormedFormula> ForAll::replaceSingularTerm(char to, bool isTopLevel) const {
    if (!isTopLevel) {
        return std::make_shared<ForAll>(this->proposition);
    }
    return std::make_shared<ForAll>(this->proposition->replaceSingularTerm(to, false));
}
