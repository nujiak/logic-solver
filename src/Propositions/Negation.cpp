#include "Negation.h"

std::string Negation::getString() const {
    return "!" + this->operand->getString();
}

