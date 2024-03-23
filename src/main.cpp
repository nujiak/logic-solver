#include "Propositions/WellFormedFormula.h"
#include "Propositions/Variable.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Equivalence.h"
#include "Propositions/Negation.h"
#include <memory>
#include <iostream>


int main() {
    std::shared_ptr<WellFormedFormula> A = std::make_shared<Variable>('A');
    std::shared_ptr<WellFormedFormula> B = std::make_shared<Variable>('B');
    auto conj = std::make_shared<Conjunction>(A, B);
    auto disjunction = std::make_shared<Disjunction>(A, B);
    auto implication = std::make_shared<Implication>(conj, disjunction);
    auto equivalence = std::make_shared<Equivalence>(A, implication);
    auto negation = Negation::of(equivalence);
    auto conversedImplication = std::make_shared<Implication>(disjunction, conj);
    auto flippedConjunction = std::make_shared<Conjunction>(B, A);

    std::cout << Negation::of(negation)->getString() << "\n";
    std::cout << negation->getString() << "\n";
    std::cout << (*equivalence == Negation::of(negation)) << "\n";
    std::cout << (*implication == conversedImplication) << "\n";
    std::cout << (*conj == flippedConjunction) << "\n";
}
