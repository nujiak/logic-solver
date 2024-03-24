#ifndef LOGIC_SOLVER_STATEMENT_H
#define LOGIC_SOLVER_STATEMENT_H

#include "Propositions/WellFormedFormula.h"
#include <vector>

enum class StatementType {
    PREMISE,
    CONCLUSION,
    CONTRADICTION,
    ASSUMPTION,
};

struct Statement {
    const StatementType type;
    const std::shared_ptr<WellFormedFormula> proposition;
    const int assumptionLevel;

    const std::vector<unsigned long> references;
    bool blocked {false};
    bool assumptionCompleted{false};
    bool broken{false};

    [[nodiscard]] std::string getString() const;
};


#endif //LOGIC_SOLVER_STATEMENT_H
