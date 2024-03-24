#ifndef LOGIC_SOLVER_AND_H
#define LOGIC_SOLVER_AND_H

#include "Rules/Inference.h"
#include "Propositions/BinaryOperations/Conjunction.h"

class And : public Inference {
private:
    const std::shared_ptr<Conjunction> conjunction;

    And(const std::shared_ptr<Conjunction> &conjunction, const std::shared_ptr<WellFormedFormula> &resultantProposition)
            : conjunction(conjunction), Inference(resultantProposition) {}

public:
    static std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>
    from(const std::shared_ptr<Conjunction>& conjunction);
};


#endif //LOGIC_SOLVER_AND_H
