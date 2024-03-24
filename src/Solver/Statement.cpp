#include "Statement.h"

std::string Statement::getString() const {
    std::string line;
    if (blocked) {
        line += "| ";
    }
    switch (type) {
        case StatementType::PREMISE:
            line += proposition->getString();
            break;
        case StatementType::CONTRADICTION:
        case StatementType::CONCLUSION:
            line += "∴ " + proposition->getString();
            break;
        case StatementType::ASSUMPTION:
            line += "asm: " + proposition->getString();
            break;
    }
    return line;
}

