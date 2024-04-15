#ifndef LOGIC_SOLVER_QUANTIFIER_H
#define LOGIC_SOLVER_QUANTIFIER_H

#include "Propositions/WellFormedFormula.h"

class Quantifier : public WellFormedFormula {
protected:
    char singularTerm;
    const std::shared_ptr<WellFormedFormula> proposition;

public:
    Quantifier(const char &singularTerm, const std::shared_ptr<WellFormedFormula> &proposition) :
            singularTerm(singularTerm), proposition(proposition) {}

    [[nodiscard]] std::shared_ptr<WellFormedFormula> getProposition() const;
};

#endif //LOGIC_SOLVER_QUANTIFIER_H
