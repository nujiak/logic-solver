#ifndef LOGIC_SOLVER_DISJUNCTIVESYLLOGISM_H
#define LOGIC_SOLVER_DISJUNCTIVESYLLOGISM_H

#include "Rules/Inference.h"
#include "Propositions/BinaryOperations/Disjunction.h"

class DisjunctiveSyllogism : public Inference {
private:
    std::shared_ptr<Disjunction> disjunction;
    std::shared_ptr<WellFormedFormula> secondProposition;
public:
    DisjunctiveSyllogism(const std::shared_ptr<Disjunction> &disjunction,
                         const std::shared_ptr<WellFormedFormula> &secondProposition);
};


#endif //LOGIC_SOLVER_DISJUNCTIVESYLLOGISM_H
