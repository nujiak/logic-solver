#include <vector>
#include <stack>
#include <unordered_set>
#include "Parser.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Equivalence.h"
#include "Propositions/Variable.h"
#include "Propositions/Negation.h"

template<typename T>
std::shared_ptr<WellFormedFormula> binaryOpFromStack(std::stack<std::shared_ptr<WellFormedFormula>> &propositions) {
    auto rightOperand = propositions.top();
    propositions.pop();
    auto operation = std::make_shared<T>(propositions.top(), rightOperand);
    propositions.pop();
    return operation;
}

const std::unordered_set<char> operators{'~', '>', '&', '@', '='};

std::string toRpn(const std::string &input) {
    std::string reversePolishNotation;
    std::stack<std::pair<char, int>> operatorStack;
    int precedenceLevel = 0;
    for (const char &c: input) {
        if (c == ' ') {
            continue;
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            reversePolishNotation += c;
        } else if (c == '(') {
            precedenceLevel++;
        } else if (c == ')') {
            precedenceLevel--;
        } else if (operators.contains(c)) {
            while (c != '~' && (!operatorStack.empty() && (operatorStack.top().second >= precedenceLevel))) {
                reversePolishNotation += operatorStack.top().first;
                operatorStack.pop();
            }
            operatorStack.emplace(c, precedenceLevel);
        }
    }
    while (!operatorStack.empty()) {
        reversePolishNotation += operatorStack.top().first;
        operatorStack.pop();
    }
    return reversePolishNotation;
}

std::shared_ptr<WellFormedFormula> parse(const std::string &input) {
    std::string reversePolishNotation = toRpn(input);
    std::stack<std::shared_ptr<WellFormedFormula>> propositions;
    for (const char &c: reversePolishNotation) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            propositions.push(std::make_shared<Variable>(c));
            continue;
        }
        auto rightOperand = propositions.top();
        propositions.pop();
        if (c == '~') {
            propositions.push(Negation::of(rightOperand));
            continue;
        }
        auto leftOperand = propositions.top();
        propositions.pop();
        switch (c) {
            case '&':
                propositions.push(std::make_shared<Conjunction>(leftOperand, rightOperand));
                break;
            case '@':
                propositions.push(std::make_shared<Disjunction>(leftOperand, rightOperand));
                break;
            case '>':
                propositions.push(std::make_shared<Implication>(leftOperand, rightOperand));
                break;
            case '=':
                propositions.push(std::make_shared<Equivalence>(leftOperand, rightOperand));
            default:
                break;
        }
    }
    return propositions.top();
}
