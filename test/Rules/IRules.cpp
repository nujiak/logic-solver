#include <gtest/gtest.h>
#include "Propositions/Variable.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Rules/IRules.h"

TEST(TryModusTollensTest, ReturnsCorrectPropositionOnPositiveInput) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto implication = std::make_shared<Implication>(A, B);

    ASSERT_EQ(*tryModusTollensFrom(implication, Negation::of(B)), Negation::of(A));
}

TEST(TryModusTollensTest, ReturnsNullOnNegativeInput) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto implication = std::make_shared<Implication>(A, B);

    ASSERT_FALSE(tryModusTollensFrom(implication, B));
    ASSERT_FALSE(tryModusTollensFrom(implication, Negation::of(A)));
    ASSERT_FALSE(tryModusTollensFrom(implication, A));
}

TEST(TryModusPonensTest, ReturnsCorrectPropositionOnPositiveInput) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto implication = std::make_shared<Implication>(A, B);

    ASSERT_EQ(*tryModusPonensFrom(implication, A), B);
}

TEST(TryModusPonensTest, ReturnsNullOnNegativeInput) {
    auto A = std::make_shared<Variable>('A');
    auto B = std::make_shared<Variable>('B');
    auto implication = std::make_shared<Implication>(A, B);

    ASSERT_FALSE(tryModusPonensFrom(implication, B));
    ASSERT_FALSE(tryModusPonensFrom(implication, Negation::of(A)));
    ASSERT_FALSE(tryModusPonensFrom(implication, Negation::of(B)));
}