#include <gtest/gtest.h>
#include "Propositions/Variable.h"

TEST(VariableTest, CorrectEqualityCheck) {
    std::shared_ptr<Variable> A1 = std::make_shared<Variable>('A');
    std::shared_ptr<Variable> A2 = std::make_shared<Variable>('A');

    EXPECT_TRUE((*A1) == A2);

    std::shared_ptr<Variable> B = std::make_shared<Variable>('B');

    EXPECT_FALSE((*A1) == B);
}

TEST(VariableTest, CorrectInequalityCheck) {
    std::shared_ptr<Variable> A1 = std::make_shared<Variable>('A');
    std::shared_ptr<Variable> A2 = std::make_shared<Variable>('A');

    EXPECT_FALSE((*A1) != A2);

    std::shared_ptr<Variable> B = std::make_shared<Variable>('B');

    EXPECT_TRUE((*A1) != B);
}

TEST(VariableTest, ReturnsCorrectString) {
    Variable A{'A'};
    EXPECT_EQ(A.getString(), "A");

    Variable z{'z'};
    EXPECT_EQ(z.getString(), "z");
}