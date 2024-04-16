#include <gtest/gtest.h>
#include "Propositions/QuantifiedVariable.h"

TEST(QuantifiedVariableTest, CorrectEqualityCheck) {
    auto Ax1 = std::make_shared<QuantifiedVariable>('A', 'x');
    auto Ax2 = std::make_shared<QuantifiedVariable>('A', 'x');
    auto Bx = std::make_shared<QuantifiedVariable>('B', 'x');
    auto Ay = std::make_shared<QuantifiedVariable>('A', 'y');

    ASSERT_TRUE((*Ax1) == Ax2);
    ASSERT_FALSE((*Ax1) == Bx);
    ASSERT_FALSE((*Ax1) == Ay);
}

TEST(QuantifiedVariableTest, CorrectInequalityCheck) {
    auto Ax1 = std::make_shared<QuantifiedVariable>('A', 'x');
    auto Ax2 = std::make_shared<QuantifiedVariable>('A', 'x');
    auto Bx = std::make_shared<QuantifiedVariable>('B', 'x');
    auto Ay = std::make_shared<QuantifiedVariable>('A', 'y');

    ASSERT_FALSE((*Ax1) != Ax2);
    ASSERT_TRUE((*Ax1) != Bx);
    ASSERT_TRUE((*Ax1) != Ay);
}

TEST(QuantifiedVariableTest, ReturnsCorrectString) {
    auto Ax = std::make_shared<QuantifiedVariable>('A', 'x');
    auto Ba = std::make_shared<QuantifiedVariable>('B', 'a');

    ASSERT_EQ(Ax->getString(), "Ax");
    ASSERT_EQ(Ba->getString(), "Ba");
}