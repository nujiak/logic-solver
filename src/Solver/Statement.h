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
    size_t assumptionLevel;
    const Rule rule;

    const std::vector<size_t> references;
    bool blocked {false};
    bool assumptionCompleted{false};
    size_t brokenLevel{0};
    bool unused{false};
    bool skip{false};

    [[nodiscard]] std::string getString() const;
};


#endif //LOGIC_SOLVER_STATEMENT_H
