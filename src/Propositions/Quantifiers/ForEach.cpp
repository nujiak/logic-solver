#include "ForEach.h"

bool ForEach::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto forEach = std::dynamic_pointer_cast<ForEach>(other)) {
        return (*this->proposition) == forEach->proposition;
    }
    return false;
}

std::string ForEach::getString() const {
    return "(!x)" + proposition->getString();
}
