#ifndef LOGIC_SOLVER_FOREACH_H
#define LOGIC_SOLVER_FOREACH_H

#include "Quantifier.h"

class ForEach : public Quantifier {
public:
    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;

};


#endif //LOGIC_SOLVER_FOREACH_H
