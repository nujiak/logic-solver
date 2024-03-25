#include "Propositions/WellFormedFormula.h"
#include "Solver/Statement.h"
#include "Solver/Solver.h"
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Solver/Printer.h"
#include "Parser/Parser.h"

int main() {
    std::vector<std::shared_ptr<WellFormedFormula>> propositions;
    for (std::string line; std::getline(std::cin, line);) {
        propositions.push_back(parse(line));
    }
    std::vector<Statement> argument;
    argument.reserve(propositions.size());
    for (int i = 0; i < propositions.size() - 1; i++) {
        argument.emplace_back(StatementType::PREMISE, propositions[i], 0);
    }
    argument.emplace_back(StatementType::CONCLUSION, propositions.back(), 0);
    print(Solver::solve(argument));
}
