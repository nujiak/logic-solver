#ifndef LOGIC_SOLVER_CONJUNCTIVESYLLOGISM_H
#define LOGIC_SOLVER_CONJUNCTIVESYLLOGISM_H

#include <memory>
#include "Propositions/Negation.h"
#include "Propositions/WellFormedFormula.h"
#include "Rules/Inference.h"

class ConjunctiveSyllogism : public Inference {
private:
    std::shared_ptr<Negation> negatedConjunction;
    std::shared_ptr<WellFormedFormula> secondProposition;
public:
    ConjunctiveSyllogism(const std::shared_ptr<Negation> &negatedConjunction,
                         const std::shared_ptr<WellFormedFormula> &secondProposition);
};


#endif //LOGIC_SOLVER_CONJUNCTIVESYLLOGISM_H
