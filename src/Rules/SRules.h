#ifndef LOGIC_SOLVER_SRULES_H
#define LOGIC_SOLVER_SRULES_H

#include "Propositions/WellFormedFormula.h"
#include "Propositions/Negation.h"
#include <optional>
#include <vector>

std::vector<std::shared_ptr<WellFormedFormula>>
tryAndFrom(const std::shared_ptr<WellFormedFormula> &maybeConjunction);

std::vector<std::shared_ptr<WellFormedFormula>>
tryNorFrom(const std::shared_ptr<WellFormedFormula> &maybeNegatedDisjunction);

std::vector<std::shared_ptr<WellFormedFormula>>
tryNifFrom(const std::shared_ptr<WellFormedFormula> &negatedImplication);


#endif //LOGIC_SOLVER_SRULES_H
