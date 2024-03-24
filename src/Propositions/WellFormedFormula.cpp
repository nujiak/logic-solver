#include "WellFormedFormula.h"

bool WellFormedFormula::operator!=(const std::shared_ptr<WellFormedFormula> &other) const {
    return !this->operator==(other);
}
