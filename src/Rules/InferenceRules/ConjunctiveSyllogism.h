#ifndef LOGIC_SOLVER_CONJUNCTIVESYLLOGISM_H
#define LOGIC_SOLVER_CONJUNCTIVESYLLOGISM_H

#include <memory>
#include "Propositions/Negation.h"
#include "Propositions/WellFormedFormula.h"
#include "Rules/InferenceRules/IRule.h"

class ConjunctiveSyllogism : public IRule {
private:
    std::shared_ptr<Negation> negatedConjunction;
    std::shared_ptr<WellFormedFormula> secondProposition;
    std::shared_ptr<WellFormedFormula> resultantProposition;
public:
    ConjunctiveSyllogism(const std::shared_ptr<Negation> &negatedConjunction,
                         const std::shared_ptr<WellFormedFormula> &secondProposition);

    [[nodiscard]] std::string getString() const override;
};


#endif //LOGIC_SOLVER_CONJUNCTIVESYLLOGISM_H
