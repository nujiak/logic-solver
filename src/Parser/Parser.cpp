#include <vector>
#include <stack>
#include <regex>
#include <unordered_set>
#include "Parser.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Equivalence.h"
#include "Propositions/Variable.h"
#include "Propositions/Negation.h"
#include "Propositions/Quantifiers/ForAll.h"
#include "Propositions/Quantifiers/ForEach.h"
#include "Propositions/QuantifiedVariable.h"

template<typename T>
std::shared_ptr<WellFormedFormula> binaryOpFromStack(std::stack<std::shared_ptr<WellFormedFormula>> &propositions) {
    auto rightOperand = propositions.top();
    propositions.pop();
    auto operation = std::make_shared<T>(propositions.top(), rightOperand);
    propositions.pop();
    return operation;
}

const std::unordered_set<char> operators{'~', '>', '&', '@', '=', '!', '$'};
const std::unordered_set<char> unaryOperators{'~', '!', '$'};
const std::regex forAllPattern{"\\(x\\)"};
const std::regex forEachPattern{"\\(!x\\)"};

/**
 * Replaces quantifiers with single characters.
 *
 * Replace for each (!x) with '!' and for all "(x)" with '$'
 * @param input
 * @return
 */
std::string replaceQuantifiers(const std::string &input) {
    std::string forAllReplacedString = std::regex_replace(input, forAllPattern, "$");
    return std::regex_replace(forAllReplacedString, forEachPattern, "!");
}

std::string toRpn(const std::string &input) {
    const std::string replacedInput = replaceQuantifiers(input);
    std::string reversePolishNotation;
    std::stack<std::pair<char, int>> operatorStack;
    int precedenceLevel = 0;
    for (const char &c: replacedInput) {
        if (c == ' ') {
            continue;
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            reversePolishNotation += c;
        } else if (c == '(') {
            precedenceLevel++;
        } else if (c == ')') {
            precedenceLevel--;
            if (precedenceLevel < 0) {
                throw std::invalid_argument(input + " has mismatched closing parentheses");
            }
        } else if (operators.contains(c)) {
            // If current operator is not unary, places all lower precedence operators into rpn
            while (!unaryOperators.contains(c) && (!operatorStack.empty() && (operatorStack.top().second >= precedenceLevel))) {
                reversePolishNotation += operatorStack.top().first;
                operatorStack.pop();
            }
            operatorStack.emplace(c, precedenceLevel);
        }
    }
    if (precedenceLevel != 0) {
        throw std::invalid_argument(input + " is missing closing parentheses");
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
        if (c >= 'A' && c <= 'Z') {
            propositions.push(std::make_shared<Variable>(c));
            continue;
        }
        auto rightOperand = propositions.top();
        propositions.pop();
        if (c == '~') {
            propositions.push(Negation::of(rightOperand));
            continue;
        }
        if (c == '!') {
            propositions.push(std::make_shared<ForEach>(rightOperand));
            continue;
        }
        if (c == '$') {
            propositions.push(std::make_shared<ForAll>(rightOperand));
            continue;
        }
        if (c >= 'a' && c <= 'z') {
            if (auto variable = std::dynamic_pointer_cast<Variable>(rightOperand)) {
                propositions.push(std::make_shared<QuantifiedVariable>(variable->getName(), c));
                continue;
            } else {
                throw std::invalid_argument("Lowercase singular term must come immediately after an uppercase variable");
            }
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
