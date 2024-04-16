#ifndef LOGIC_SOLVER_FOREACH_H
#define LOGIC_SOLVER_FOREACH_H

#include "Quantifier.h"

class ForEach : public Quantifier {
public:
    explicit ForEach(const std::shared_ptr<WellFormedFormula> &proposition): Quantifier(proposition) {}

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;

    [[nodiscard]] std::shared_ptr<WellFormedFormula> replaceSingularTerm(char to, bool isTopLevel) const override;
};


#endif //LOGIC_SOLVER_FOREACH_H
