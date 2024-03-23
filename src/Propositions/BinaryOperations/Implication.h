#ifndef LOGIC_SOLVER_IMPLICATION_H
#define LOGIC_SOLVER_IMPLICATION_H

#include <utility>

#include "BinaryOperation.h"

class Implication : public BinaryOperation {
public:
    Implication(std::shared_ptr<WellFormedFormula> leftOperand, std::shared_ptr<WellFormedFormula> rightOperand)
            : BinaryOperation(std::move(leftOperand), std::move(rightOperand)) {}

    [[nodiscard]] std::string getString() const override;
};


#endif //LOGIC_SOLVER_IMPLICATION_H
