#ifndef LOGIC_SOLVER_NIF_H
#define LOGIC_SOLVER_NIF_H

#include "Rules/Inference.h"
#include "Propositions/Negation.h"

class Nif : public Inference {
private:
    const std::shared_ptr<Negation> negatedImplication;

    Nif(const std::shared_ptr<Negation> &negatedImplication,
        const std::shared_ptr<WellFormedFormula> &resultantProposition) : negatedImplication(negatedImplication),
                                                                          Inference(resultantProposition) {};
public:
    static std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>
    from(const std::shared_ptr<Negation> &negatedImplication);
};


#endif //LOGIC_SOLVER_NIF_H
