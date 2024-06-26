#include "QuantifiedVariable.h"

std::string QuantifiedVariable::getString() const {
    return std::string{this->name, this->singularTerm};
}

bool QuantifiedVariable::operator==(const std::shared_ptr<WellFormedFormula> &other) const {
    if (auto quantifiedVariable = std::dynamic_pointer_cast<QuantifiedVariable>(other)) {
        return this->name == quantifiedVariable->name && this->singularTerm == quantifiedVariable->singularTerm;
    }
    return false;
}

std::shared_ptr<WellFormedFormula> QuantifiedVariable::replaceSingularTerm(char to, bool isTopLevel) const {
    return std::make_shared<QuantifiedVariable>(this->name, to);
}

std::unordered_set<char> QuantifiedVariable::getSingularTerms() const {
    return {this->singularTerm};
}
