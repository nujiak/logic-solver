#ifndef LOGIC_SOLVER_BINARYOPERATION_H
#define LOGIC_SOLVER_BINARYOPERATION_H

#include <memory>
#include "Propositions/WellFormedFormula.h"

class BinaryOperation : public WellFormedFormula {
protected:
    const std::shared_ptr<WellFormedFormula> rightOperand;
    const std::shared_ptr<WellFormedFormula> leftOperand;

    [[nodiscard]] std::string getString(char operatorSymbol) const;

public:
    BinaryOperation(std::shared_ptr<WellFormedFormula> leftOperand, std::shared_ptr<WellFormedFormula> rightOperand)
            : leftOperand(std::move(leftOperand)), rightOperand(std::move(rightOperand)) {}

    [[nodiscard]] std::shared_ptr<WellFormedFormula> getLeftOperand() const;

    [[nodiscard]] std::shared_ptr<WellFormedFormula> getRightOperand() const;

    [[nodiscard]] std::unordered_set<char> getSingularTerms() const override;
};


#endif //LOGIC_SOLVER_BINARYOPERATION_H
