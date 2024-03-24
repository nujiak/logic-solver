#ifndef LOGIC_SOLVER_MODUSTOLLENS_H
#define LOGIC_SOLVER_MODUSTOLLENS_H

#include "IRule.h"
#include "Propositions/BinaryOperations/Implication.h"

class ModusTollens : public IRule {
private:
    std::shared_ptr<Implication> implication;
    std::shared_ptr<WellFormedFormula> antecedent;
public:
    ModusTollens(const std::shared_ptr<Implication> &implication,
                 const std::shared_ptr<WellFormedFormula> &antecedent);
};


#endif //LOGIC_SOLVER_MODUSTOLLENS_H
