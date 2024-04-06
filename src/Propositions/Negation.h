#ifndef LOGIC_SOLVER_NEGATION_H
#define LOGIC_SOLVER_NEGATION_H

#include "WellFormedFormula.h"
#include <memory>

class Negation : public WellFormedFormula {
private:
    std::shared_ptr<WellFormedFormula> operand;

    explicit Negation(std::shared_ptr<WellFormedFormula> operand) : operand(std::move(operand)) {}

public:
    static std::shared_ptr<WellFormedFormula> of(const std::shared_ptr<WellFormedFormula> &proposition);

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;

    [[nodiscard]] std::shared_ptr<WellFormedFormula> replaceSingularTerm(char from, char to, bool isTopLevel) const override;

    [[nodiscard]] std::unordered_set<char> getSingularTerms() const override;
};


#endif //LOGIC_SOLVER_NEGATION_H
