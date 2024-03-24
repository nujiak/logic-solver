#ifndef LOGIC_SOLVER_DISJUNCTIVESYLLOGISM_H
#define LOGIC_SOLVER_DISJUNCTIVESYLLOGISM_H

#include "Rules/InferenceRules/IRule.h"
#include "Propositions/BinaryOperations/Disjunction.h"

class DisjunctiveSyllogism : public IRule {
private:
    std::shared_ptr<Disjunction> disjunction;
    std::shared_ptr<WellFormedFormula> secondProposition;
public:
    DisjunctiveSyllogism(const std::shared_ptr<Disjunction> &disjunction,
                         const std::shared_ptr<WellFormedFormula> &secondProposition);
};


#endif //LOGIC_SOLVER_DISJUNCTIVESYLLOGISM_H
