#ifndef LOGIC_SOLVER_IRULE_H
#define LOGIC_SOLVER_IRULE_H

#include <memory>
#include "Propositions/WellFormedFormula.h"

class IRule : public WellFormedFormula {
protected:
    std::shared_ptr<WellFormedFormula> resultantProposition;

public:
    bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;

    [[nodiscard]] std::string getString() const override;
};


#endif //LOGIC_SOLVER_IRULE_H
