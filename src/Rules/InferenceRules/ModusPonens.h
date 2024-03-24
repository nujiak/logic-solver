#ifndef LOGIC_SOLVER_MODUSPONENS_H
#define LOGIC_SOLVER_MODUSPONENS_H

#include "Rules/Inference.h"
#include "Propositions/BinaryOperations/Implication.h"

class ModusPonens : public Inference {
private:
    std::shared_ptr<Implication> implication;
    std::shared_ptr<WellFormedFormula> antecedent;
public:
    ModusPonens(const std::shared_ptr<Implication> &implication,
                const std::shared_ptr<WellFormedFormula> &antecedent);
};


#endif //LOGIC_SOLVER_MODUSPONENS_H
