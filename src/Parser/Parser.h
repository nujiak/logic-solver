#ifndef LOGIC_SOLVER_PARSER_H
#define LOGIC_SOLVER_PARSER_H

#include <Propositions/WellFormedFormula.h>

std::shared_ptr<WellFormedFormula> parse(const std::string &input);

#endif //LOGIC_SOLVER_PARSER_H
