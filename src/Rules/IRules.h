#ifndef LOGIC_SOLVER_IRULES_H
#define LOGIC_SOLVER_IRULES_H

#include <memory>
#include "Propositions/WellFormedFormula.h"
#include "Propositions/Negation.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Conjunction.h"

std::shared_ptr<WellFormedFormula> tryModusTollensFrom(const std::shared_ptr<WellFormedFormula> &maybeImplication,
                                                       const std::shared_ptr<WellFormedFormula> &antecedent);

std::shared_ptr<WellFormedFormula> tryModusPonensFrom(const std::shared_ptr<WellFormedFormula> &maybeImplication,
                                                      const std::shared_ptr<WellFormedFormula> &antecedent);

std::shared_ptr<WellFormedFormula> tryDisjunctiveSyllogismFrom(
        const std::shared_ptr<WellFormedFormula> &maybeDisjunction,
        const std::shared_ptr<WellFormedFormula> &secondProposition);

std::shared_ptr<WellFormedFormula> tryConjunctiveSyllogismFrom(
        const std::shared_ptr<WellFormedFormula> &maybeNegatedConjunction,
        const std::shared_ptr<WellFormedFormula> &secondProposition
);

#endif //LOGIC_SOLVER_IRULES_H
