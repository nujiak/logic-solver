#ifndef LOGIC_SOLVER_SOLVER_H
#define LOGIC_SOLVER_SOLVER_H

#include <optional>
#include <vector>
#include "Statement.h"

[[nodiscard]] std::vector<Statement> solve(std::vector<Statement> argument);

#endif //LOGIC_SOLVER_SOLVER_H
