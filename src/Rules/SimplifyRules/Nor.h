#ifndef LOGIC_SOLVER_NOR_H
#define LOGIC_SOLVER_NOR_H

#include "Rules/Inference.h"
#include "Propositions/Negation.h"

class Nor : public Inference {
private:
    const std::shared_ptr<Negation> negatedDisjunction;

    Nor(const std::shared_ptr<Negation> &negatedDisjunction,
        const std::shared_ptr<WellFormedFormula> &resultantProposition) : negatedDisjunction(negatedDisjunction),
                                                                          Inference(resultantProposition) {};
public:
    static std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>
    from(const std::shared_ptr<Negation> &negatedDisjunction);
};


#endif //LOGIC_SOLVER_NOR_H
