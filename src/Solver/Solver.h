#ifndef LOGIC_SOLVER_SOLVER_H
#define LOGIC_SOLVER_SOLVER_H

#include <optional>
#include <vector>
#include "Statement.h"

struct InferredProposition {
    Rule rule;
    std::shared_ptr<WellFormedFormula> proposition;
};

class Solver {
private:
    static std::vector<InferredProposition>
    findSRule(const std::shared_ptr<WellFormedFormula> &proposition);

    static std::vector<InferredProposition>
    findIRule(const std::shared_ptr<WellFormedFormula> &propositionA,
              const std::shared_ptr<WellFormedFormula> &propositionB);

    static void verifyInitialArgument(const std::vector<Statement> &argument);

public:
    static std::vector<Statement> solve(std::vector<Statement> argument);
};


#endif //LOGIC_SOLVER_SOLVER_H
