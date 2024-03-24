#ifndef LOGIC_SOLVER_SOLVER_H
#define LOGIC_SOLVER_SOLVER_H

#include <optional>
#include <vector>
#include "Statement.h"

class Solver {
private:
    static std::optional<std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>>
    findSRule(const std::shared_ptr<WellFormedFormula> &proposition);

    static std::vector<std::shared_ptr<WellFormedFormula>> findIRule(std::shared_ptr<WellFormedFormula> propositionA,
                                                                     std::shared_ptr<WellFormedFormula> propositionB);

    static void verifyInitialArgument(const std::vector<Statement> &argument);

public:
    static std::vector<Statement> solve(std::vector<Statement> argument);
};


#endif //LOGIC_SOLVER_SOLVER_H
