#ifndef LOGIC_SOLVER_CONJUNCTION_H
#define LOGIC_SOLVER_CONJUNCTION_H

#include "BinaryOperation.h"
#include <memory>
#include <utility>

class Conjunction : public BinaryOperation {
public:
    Conjunction(const Conjunction &c) : BinaryOperation(c.leftOperand, c.rightOperand) {}

    Conjunction(std::shared_ptr<WellFormedFormula> leftOperand,
                std::shared_ptr<WellFormedFormula> rightOperand) : BinaryOperation(std::move(leftOperand),
                                                                                   std::move(rightOperand)) {}

    [[nodiscard]] std::string getString() const override;

};


#endif //LOGIC_SOLVER_CONJUNCTION_H
