#ifndef LOGIC_SOLVER_QUANTIFIEDVARIABLE_H
#define LOGIC_SOLVER_QUANTIFIEDVARIABLE_H

#include "Variable.h"

class QuantifiedVariable : public Variable {
private:
    const char singularTerm;
public:
    QuantifiedVariable(char name, char singularTerm) : Variable(name), singularTerm(singularTerm) {}

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;

    [[nodiscard]] std::shared_ptr<WellFormedFormula> replaceSingularTerm(char to, bool isTopLevel) const override;

    [[nodiscard]] std::unordered_set<char> getSingularTerms() const override;
};

#endif //LOGIC_SOLVER_QUANTIFIEDVARIABLE_H
