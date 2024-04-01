#ifndef LOGIC_SOLVER_VARIABLE_H
#define LOGIC_SOLVER_VARIABLE_H

#include "WellFormedFormula.h"
#include <string>
#include <utility>

class Variable : public WellFormedFormula {
private:
    char name;
public:
    explicit Variable(char name) : name(name) {};

    [[nodiscard]] char getName() const;

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;
};


#endif //LOGIC_SOLVER_VARIABLE_H
