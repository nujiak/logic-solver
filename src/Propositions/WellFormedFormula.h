#ifndef LOGIC_SOLVER_WELLFORMEDFORMULA_H
#define LOGIC_SOLVER_WELLFORMEDFORMULA_H

#include <string>
#include <memory>


class WellFormedFormula {
public:
    [[nodiscard]] virtual std::string getString() const = 0;

    [[nodiscard]] virtual bool operator==(const std::shared_ptr<WellFormedFormula> &other) const = 0;
};


#endif //LOGIC_SOLVER_WELLFORMEDFORMULA_H
