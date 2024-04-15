#ifndef LOGIC_SOLVER_FORALL_H
#define LOGIC_SOLVER_FORALL_H

#include "Quantifier.h"

class ForAll : public Quantifier {
public:
    explicit ForAll(const std::shared_ptr<WellFormedFormula> &proposition): Quantifier(proposition) {}

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula>& other) const override;

    [[nodiscard]] std::shared_ptr<WellFormedFormula> replaceSingularTerm(char to, bool isTopLevel) const override;
};


#endif //LOGIC_SOLVER_FORALL_H
