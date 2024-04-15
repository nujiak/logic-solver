#ifndef LOGIC_SOLVER_FORALL_H
#define LOGIC_SOLVER_FORALL_H

#include "Quantifier.h"

class ForAll : public Quantifier {
public:
    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula>& other) const override;
};


#endif //LOGIC_SOLVER_FORALL_H
