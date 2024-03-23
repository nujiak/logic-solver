#ifndef LOGIC_SOLVER_NEGATION_H
#define LOGIC_SOLVER_NEGATION_H

#include "WellFormedFormula.h"
#include <memory>

class Negation : public WellFormedFormula {
private:
    std::shared_ptr<WellFormedFormula> operand;
public:
    explicit Negation(std::shared_ptr<WellFormedFormula> operand) : operand(std::move(operand)) {}

    [[nodiscard]] std::string getString() const override;
};


#endif //LOGIC_SOLVER_NEGATION_H
