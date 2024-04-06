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

char Variable::getName() const {
    return this->name;
}

std::shared_ptr<WellFormedFormula> Variable::replaceSingularTerm(char from, char to, bool isTopLevel) const {
    return std::make_shared<Variable>(this->name);
}

std::unordered_set<char> Variable::getSingularTerms() const {
    return {};
}

