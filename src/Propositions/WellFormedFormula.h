#ifndef LOGIC_SOLVER_WELLFORMEDFORMULA_H
#define LOGIC_SOLVER_WELLFORMEDFORMULA_H

#include <string>
#include <memory>
#include <unordered_set>


class WellFormedFormula {
public:
    [[nodiscard]] virtual std::string getString() const = 0;

    [[nodiscard]] virtual bool operator==(const std::shared_ptr<WellFormedFormula> &other) const = 0;

    [[nodiscard]] bool operator!=(const std::shared_ptr<WellFormedFormula> &other) const;

    [[nodiscard]] virtual std::shared_ptr<WellFormedFormula> replaceSingularTerm(char to, bool isTopLevel) const = 0;

    [[nodiscard]] virtual std::unordered_set<char> getSingularTerms() const = 0;
};


#endif //LOGIC_SOLVER_WELLFORMEDFORMULA_H
