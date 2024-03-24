#ifndef LOGIC_SOLVER_MODUSTOLLENS_H
#define LOGIC_SOLVER_MODUSTOLLENS_H

#include "Rules/Inference.h"
#include "Propositions/BinaryOperations/Implication.h"

class ModusTollens : public Inference {
private:
    std::shared_ptr<Implication> implication;
    std::shared_ptr<WellFormedFormula> antecedent;
public:
    ModusTollens(const std::shared_ptr<Implication> &implication,
                 const std::shared_ptr<WellFormedFormula> &antecedent);
};


#endif //LOGIC_SOLVER_MODUSTOLLENS_H
