#ifndef LOGIC_SOLVER_EQUIVALENCE_H
#define LOGIC_SOLVER_EQUIVALENCE_H

#include "BinaryOperation.h"

class Equivalence : public BinaryOperation {
public:
    Equivalence(std::shared_ptr<WellFormedFormula> leftOperand, std::shared_ptr<WellFormedFormula> rightOperand)
            : BinaryOperation(std::move(leftOperand), std::move(rightOperand)) {}

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;
};


#endif //LOGIC_SOLVER_EQUIVALENCE_H
