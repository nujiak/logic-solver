#include "And.h"

std::pair<std::shared_ptr<WellFormedFormula>, std::shared_ptr<WellFormedFormula>>
And::from(const std::shared_ptr<Conjunction> &conjunction) {
    auto inferenceLeft = new And{conjunction, conjunction->getLeftOperand()};
    auto inferenceRight = new And{conjunction, conjunction->getRightOperand()};
    return {std::shared_ptr<And>(inferenceLeft), std::shared_ptr<And>(inferenceRight)};
}