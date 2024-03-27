#include <gtest/gtest.h>
#include "Propositions/Negation.h"
#include "Propositions/Variable.h"

TEST(NegationTest, CorrectEqualityCheck) {
    auto A = std::make_shared<Variable>('A');
    auto negatedA1 = Negation::of(A);
    auto negatedA2 = Negation::of(A);

    ASSERT_TRUE((*negatedA1) == negatedA2);
    ASSERT_FALSE((*negatedA1) == A);
    ASSERT_FALSE((*negatedA2) == A);
}

TEST(NegationTest, CorrectInqualityCheck) {
    auto A = std::make_shared<Variable>('A');
    auto negatedA = Negation::of(A);
    auto B = std::make_shared<Variable>('B');
    auto negatedB = Negation::of(B);

    ASSERT_TRUE((*negatedA) != A);
    ASSERT_TRUE((*negatedA) != negatedB);
    ASSERT_TRUE((*negatedA) != B);
    ASSERT_FALSE((*negatedA) != Negation::of(A));
}

TEST(NegationTest, UnwrapsCorrectly) {
    auto A = std::make_shared<Variable>('A');
    auto negatedA = Negation::of(A);
    auto doubleNegatedA = Negation::of(negatedA);
    ASSERT_EQ(*A, doubleNegatedA);
}

TEST(NegationTest, ReturnsCorrectString) {
    auto A = std::make_shared<Variable>('A');
    auto negatedA = Negation::of(A);
    ASSERT_EQ(negatedA->getString(), "!A");
    ASSERT_EQ(Negation::of(negatedA)->getString(), "A");

    auto B = std::make_shared<Variable>('B');
    auto negatedB = Negation::of(B);
    ASSERT_EQ(negatedB->getString(), "!B");
    ASSERT_EQ(Negation::of(negatedB)->getString(), "B");
}