#include "Variable.h"

std::string Variable::getString() const {
    return {this->name};
}

bool Variable::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto otherVariable = std::dynamic_pointer_cast<Variable>(other)) {
        return this->name == otherVariable->name;
    }
    return false;
}

