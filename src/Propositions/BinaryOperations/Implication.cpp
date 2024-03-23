#include "Implication.h"

std::string Implication::getString() const {
    return BinaryOperation::getString('>');
}
