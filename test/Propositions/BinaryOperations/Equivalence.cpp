#include <gtest/gtest.h>
#include "Propositions/BinaryOperations/Equivalence.h"
#include "Propositions/Variable.h"

TEST(EquivalenceTest, CorrectEqualityCheck) {
    auto A1 = std::make_shared<Variable>('A');
    auto A2 = std::make_shared<Variable>('A');
    auto B1 = std::make_shared<Variable>('B');
    auto B2 = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto equivalence1 = std::make_shared<Equivalence>(A1, B1);
    auto equivalence2 = std::make_shared<Equivalence>(A2, B2);
    auto equivalence3 = std::make_shared<Equivalence>(B1, A1);
    auto equivalence4 = std::make_shared<Equivalence>(A1, C);

    ASSERT_TRUE((*equivalence1) == equivalence2);
    ASSERT_TRUE((*equivalence1) == equivalence3);
    ASSERT_FALSE((*equivalence1) == equivalence4);
}

TEST(EquivalenceTest, CorrectInequalityCheck) {
    auto A1 = std::make_shared<Variable>('A');
    auto A2 = std::make_shared<Variable>('A');
    auto B1 = std::make_shared<Variable>('B');
    auto B2 = std::make_shared<Variable>('B');
    auto C = std::make_shared<Variable>('C');
    auto equivalence1 = std::make_shared<Equivalence>(A1, B1);
    auto equivalence2 = std::make_shared<Equivalence>(A2, B2);
    auto equivalence3 = std::make_shared<Equivalence>(B1, A1);
    auto equivalence4 = std::make_shared<Equivalence>(A1, C);

    ASSERT_FALSE((*equivalence1) != equivalence2);
    ASSERT_FALSE((*equivalence1) != equivalence3);
    ASSERT_TRUE((*equivalence1) != equivalence4);
}

TEST(EquivalenceTest, ReturnsCorrectOperands) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto equivalence = std::make_shared<Equivalence>(A, B);

    ASSERT_EQ((*equivalence->getLeftOperand()), A);
    ASSERT_NE((*equivalence->getLeftOperand()), B);

    ASSERT_EQ((*equivalence->getRightOperand()), B);
    ASSERT_NE((*equivalence->getRightOperand()), A);
}

TEST(EquivalenceTest, ReturnsCorrectString) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto equivalence1 = std::make_shared<Equivalence>(A, B);
    auto equivalence2 = std::make_shared<Equivalence>(B, A);

    ASSERT_EQ(equivalence1->getString(), "(A=B)");
    ASSERT_NE(equivalence1->getString(), "(B=A)");

    ASSERT_EQ(equivalence2->getString(), "(B=A)");
    ASSERT_NE(equivalence2->getString(), "(A=B)");
}
