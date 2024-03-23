#ifndef LOGIC_SOLVER_DISJUNCTION_H
#define LOGIC_SOLVER_DISJUNCTION_H

#include "BinaryOperation.h"

class Disjunction : public BinaryOperation {
public:
    Disjunction(std::shared_ptr<WellFormedFormula> leftOperand, std::shared_ptr<WellFormedFormula> rightOperand)
            : BinaryOperation(std::move(leftOperand), std::move(rightOperand)) {}

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;
};


#endif //LOGIC_SOLVER_DISJUNCTION_H
