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
    size_t brokenLevel{0};
    bool unused{false};

    /**
     * True when this statement is part of a completed assumption and should be skipped
     */
    bool skip{false};

    std::unordered_set<char> brokenSingularTerms{};

    [[nodiscard]] std::string getString() const;
};


#endif //LOGIC_SOLVER_STATEMENT_H
