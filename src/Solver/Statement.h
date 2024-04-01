#ifndef LOGIC_SOLVER_STATEMENT_H
#define LOGIC_SOLVER_STATEMENT_H

#include "Propositions/WellFormedFormula.h"
#include <vector>
#include "Rule.h"

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
    const Rule rule;

    const std::vector<unsigned long> references;
    bool blocked {false};
    bool assumptionCompleted{false};
    unsigned int brokenLevel{0};
    bool unused{false};
    bool skip{false};

    [[nodiscard]] std::string getString() const;
};


#endif //LOGIC_SOLVER_STATEMENT_H
