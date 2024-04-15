#include "Printer.h"
#include <iostream>
#include "NotImplementedError.h"

std::string getRuleString(const Rule& rule) {
    switch (rule) {
        case Rule::NIF:
            return "NIF";
        case Rule::AND:
            return "AND";
        case Rule::NOR:
            return "NOR";
        case Rule::EQ:
            return "EQ";
        case Rule::NEQ:
            return "NEQ";
        case Rule::CS:
            return "CS";
        case Rule::DS:
            return "DS";
        case Rule::MP:
            return "MP";
        case Rule::MT:
            return "MT";
        case Rule::IFF:
            return "IFF";
        case Rule::NIFF:
            return "NIFF";
        case Rule::NONE:
            return "";
        default:
            throw NotImplementedError("getRuleString for given rule");
    }
}

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

        for (int j = 0 ; j < statement.assumptionLevel; j++) {
            std::cout << "  ";
        }
        switch (statement.type) {
            case StatementType::ASSUMPTION:
                std::cout << "asm: ";
                break;
            case StatementType::CONTRADICTION:
            case StatementType::CONCLUSION:
                std::cout << "\u2234 ";
                break;
            default:
                break;
        }

        std::cout << statement.proposition->getString() << " ";

        if (statement.rule == Rule::BREAK) {
            std::cout << "(break " << adjustedIndex[statement.references[0]] << ")";
        } else {
            if (statement.type == StatementType::CONTRADICTION) {
                std::cout << "(from " << adjustedIndex[statement.references[0]] << "; "
                          << adjustedIndex[statement.references[1]] << " contradicts "
                          << adjustedIndex[statement.references[2]] << ") ";
            } else if (!statement.references.empty()) {
                std::cout << "(from " << adjustedIndex[statement.references[0]];
                for (auto reference = statement.references.begin() + 1;
                     reference != statement.references.end(); reference++) {
                    std::cout << ", " << adjustedIndex[*reference];
                }
                std::cout << ") ";
            }

            std::cout << getRuleString(statement.rule);
        }

        std::cout << "\n";
    }
}
