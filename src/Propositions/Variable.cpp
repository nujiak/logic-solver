#include "Variable.h"

std::string Variable::getString() const {
    return {&this->name};
}

