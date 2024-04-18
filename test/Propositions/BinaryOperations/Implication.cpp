#include <gtest/gtest.h>
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/Variable.h"

TEST(ImplicationTest, CorrectEqualityCheck) {
    auto A1 = std::make_shared<Variable>('A');
    auto A2 = std::make_shared<Variable>('A');
    auto B1 = std::make_shared<Variable>('B');
    auto B2 = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto implication1 = std::make_shared<Implication>(A1, B1);
    auto implication2 = std::make_shared<Implication>(A2, B2);
    auto implication3 = std::make_shared<Implication>(B1, A1);
    auto implication4 = std::make_shared<Implication>(A1, C);

    ASSERT_TRUE((*implication1) == implication2);
    ASSERT_FALSE((*implication1) == implication3);
    ASSERT_FALSE((*implication1) == implication4);
}

TEST(ImplicationTest, CorrectInequalityCheck) {
    auto A1 = std::make_shared<Variable>('A');
    auto A2 = std::make_shared<Variable>('A');
    auto B1 = std::make_shared<Variable>('B');
    auto B2 = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto implication1 = std::make_shared<Implication>(A1, B1);
    auto implication2 = std::make_shared<Implication>(A2, B2);
    auto implication3 = std::make_shared<Implication>(B1, A1);
    auto implication4 = std::make_shared<Implication>(A1, C);

    ASSERT_FALSE((*implication1) != implication2);
    ASSERT_TRUE((*implication1) != implication3);
    ASSERT_TRUE((*implication1) != implication4);
}

TEST(ImplicationTest, ReturnsCorrectOperands) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto implication = std::make_shared<Implication>(A, B);

    ASSERT_EQ((*implication->getLeftOperand()), A);
    ASSERT_NE((*implication->getLeftOperand()), B);

    ASSERT_EQ((*implication->getRightOperand()), B);
    ASSERT_NE((*implication->getRightOperand()), A);
}

TEST(ImplicationTest, ReturnsCorrectString) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto implication1 = std::make_shared<Implication>(A, B);
    auto implication2 = std::make_shared<Implication>(B, A);

    ASSERT_EQ(implication1->getString(), "(A>B)");
    ASSERT_NE(implication1->getString(), "(B>A)");

    ASSERT_EQ(implication2->getString(), "(B>A)");
    ASSERT_NE(implication2->getString(), "(A>B)");
}
