#include <gtest/gtest.h>
#include "Propositions/Variable.h"
#include "Propositions/BinaryOperations/Disjunction.h"

TEST(DisjunctionTest, CorrectEqualityCheck) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto disjunction1 = std::make_shared<Disjunction>(A, B);
    auto disjunction2 = std::make_shared<Disjunction>(A, B);
    auto disjunction3 = std::make_shared<Disjunction>(B, A);
    auto disjunction4 = std::make_shared<Disjunction>(A, C);

    ASSERT_TRUE((*disjunction1) == disjunction2);
    ASSERT_TRUE((*disjunction1) == disjunction3);
    ASSERT_FALSE((*disjunction1) == disjunction4);
}

TEST(DisjunctionTest, CorrectInequalityCheck) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto disjunction1 = std::make_shared<Disjunction>(A, B);
    auto disjunction2 = std::make_shared<Disjunction>(A, B);
    auto disjunction3 = std::make_shared<Disjunction>(B, A);
    auto disjunction4 = std::make_shared<Disjunction>(A, C);

    ASSERT_FALSE((*disjunction1) != disjunction2);
    ASSERT_FALSE((*disjunction1) != disjunction3);
    ASSERT_TRUE((*disjunction1) != disjunction4);
}

TEST(DisjunctionTest, ReturnsCorrectOperands) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto disjunction = std::make_shared<Disjunction>(A, B);

    ASSERT_EQ((*disjunction->getLeftOperand()), A);
    ASSERT_NE((*disjunction->getLeftOperand()), B);

    ASSERT_EQ((*disjunction->getRightOperand()), B);
    ASSERT_NE((*disjunction->getRightOperand()), A);
}

TEST(DisjunctionTest, ReturnsCorrectString) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto disjunction1 = std::make_shared<Disjunction>(A, B);
    auto disjunction2 = std::make_shared<Disjunction>(B, A);

    ASSERT_EQ(disjunction1->getString(), "(A@B)");
    ASSERT_NE(disjunction1->getString(), "(B@A)");

    ASSERT_EQ(disjunction2->getString(), "(B@A)");
    ASSERT_NE(disjunction2->getString(), "(A@B)");
}
