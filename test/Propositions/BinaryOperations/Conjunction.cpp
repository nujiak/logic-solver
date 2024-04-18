#include <gtest/gtest.h>
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Propositions/Variable.h"

TEST(ConjunctionTest, CorrectEqualityCheck) {
    auto A1 = std::make_shared<Variable>('A');
    auto A2 = std::make_shared<Variable>('A');
    auto B1 = std::make_shared<Variable>('B');
    auto B2 = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto conjunction1 = std::make_shared<Conjunction>(A1, B1);
    auto conjunction2 = std::make_shared<Conjunction>(A2, B2);
    auto conjunction3 = std::make_shared<Conjunction>(B1, A1);
    auto conjunction4 = std::make_shared<Conjunction>(A1, C);

    ASSERT_TRUE((*conjunction1) == conjunction2);
    ASSERT_TRUE((*conjunction1) == conjunction3);
    ASSERT_FALSE((*conjunction1) == conjunction4);
}

TEST(ConjunctionTest, CorrectInequalityCheck) {
    auto A1 = std::make_shared<Variable>('A');
    auto A2 = std::make_shared<Variable>('A');
    auto B1 = std::make_shared<Variable>('B');
    auto B2 = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto conjunction1 = std::make_shared<Conjunction>(A1, B1);
    auto conjunction2 = std::make_shared<Conjunction>(A2, B2);
    auto conjunction3 = std::make_shared<Conjunction>(B1, A1);
    auto conjunction4 = std::make_shared<Conjunction>(A1, C);

    ASSERT_FALSE((*conjunction1) != conjunction2);
    ASSERT_FALSE((*conjunction1) != conjunction3);
    ASSERT_TRUE((*conjunction1) != conjunction4);
}

TEST(ConjunctionTest, ReturnsCorrectOperands) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto conjunction = std::make_shared<Conjunction>(A, B);

    ASSERT_EQ((*conjunction->getLeftOperand()), A);
    ASSERT_NE((*conjunction->getLeftOperand()), B);

    ASSERT_EQ((*conjunction->getRightOperand()), B);
    ASSERT_NE((*conjunction->getRightOperand()), A);
}

TEST(ConjunctionTest, ReturnsCorrectString) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto conjunction1 = std::make_shared<Conjunction>(A, B);
    auto conjunction2 = std::make_shared<Conjunction>(B, A);

    ASSERT_EQ(conjunction1->getString(), "(A&B)");
    ASSERT_NE(conjunction1->getString(), "(B&A)");

    ASSERT_EQ(conjunction2->getString(), "(B&A)");
    ASSERT_NE(conjunction2->getString(), "(A&B)");
}