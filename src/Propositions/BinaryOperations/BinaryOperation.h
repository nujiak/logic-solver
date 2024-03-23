#ifndef LOGIC_SOLVER_BINARYOPERATION_H
#define LOGIC_SOLVER_BINARYOPERATION_H

#include <memory>
#include "Propositions/WellFormedFormula.h"

class BinaryOperation : public WellFormedFormula {
protected:
    std::shared_ptr<WellFormedFormula> rightOperand;
    std::shared_ptr<WellFormedFormula> leftOperand;

    [[nodiscard]] std::string getString(char operatorSymbol) const;

public:
    BinaryOperation(std::shared_ptr<WellFormedFormula> leftOperand, std::shared_ptr<WellFormedFormula> rightOperand)
            : leftOperand(std::move(leftOperand)), rightOperand(std::move(rightOperand)) {}
};


#endif //LOGIC_SOLVER_BINARYOPERATION_H
