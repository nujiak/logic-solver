#ifndef LOGIC_SOLVER_QUANTIFIER_H
#define LOGIC_SOLVER_QUANTIFIER_H

#include "Propositions/WellFormedFormula.h"

class Quantifier : public WellFormedFormula {
protected:
    const std::shared_ptr<WellFormedFormula> proposition;

public:
    Quantifier(const std::shared_ptr<WellFormedFormula> &proposition) : proposition(proposition) {}

    [[nodiscard]] std::shared_ptr<WellFormedFormula> getProposition() const;

    [[nodiscard]] std::unordered_set<char> getSingularTerms() const override;
};

#endif //LOGIC_SOLVER_QUANTIFIER_H
