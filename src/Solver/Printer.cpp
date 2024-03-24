#include "Printer.h"
#include <iostream>

void print(const std::vector<Statement> &proof) {
    std::vector<unsigned long> adjustedIndex;
    adjustedIndex.reserve(proof.size());
    unsigned long runningBlockedCount = 0;

    for (int i = 0; i < proof.size(); i++) {
        Statement statement = proof[i];
        if (statement.blocked) {
            std::cout << " | ";
            runningBlockedCount++;
            adjustedIndex.push_back(i);
        } else {
            std::cout << (i + 1 - runningBlockedCount) << ". ";
            adjustedIndex.push_back(i + 1 - runningBlockedCount);
        }

        switch (statement.type) {
            case StatementType::ASSUMPTION:
                std::cout << "asm: ";
                break;
            case StatementType::CONCLUSION:
                std::cout << "\u2234 ";
                break;
            default:
                break;
        }

        std::cout << statement.proposition->getString() << " ";
        if (statement.type == StatementType::CONTRADICTION) {
            std::cout << "(from " << adjustedIndex[statement.references[0]] << "; "
                      << adjustedIndex[statement.references[1]] << " contradicts "
                      << adjustedIndex[statement.references[2]] << ") ";
        } else if (!statement.references.empty()) {
            std::cout << "(from";
            for (const auto &reference: statement.references) {
                std::cout << " " << adjustedIndex[reference];
            }
            std::cout << ") ";
        }

        switch (statement.rule) {
            case Rule::NIF:
                std::cout << "NIF";
                break;
            case Rule::AND:
                std::cout << "AND";
                break;
            case Rule::NOR:
                std::cout << "NOR";
                break;
            case Rule::CS:
                std::cout << "CS";
                break;
            case Rule::DS:
                std::cout << "DS";
                break;
            case Rule::MP:
                std::cout << "MP";
                break;
            case Rule::MT:
                std::cout << "MT";
                break;
            case Rule::NONE:
            default:
                break;
        }

        std::cout << "\n";
    }
}
