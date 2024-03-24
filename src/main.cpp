#include "Propositions/WellFormedFormula.h"
#include "Propositions/Variable.h"
#include "Propositions/BinaryOperations/Conjunction.h"
#include "Propositions/BinaryOperations/Disjunction.h"
#include "Propositions/BinaryOperations/Implication.h"
#include "Propositions/BinaryOperations/Equivalence.h"
#include "Propositions/Negation.h"
#include "Rules/InferenceRules/ConjunctiveSyllogism.h"
#include "Rules/InferenceRules/DisjunctiveSyllogism.h"
#include "Rules/InferenceRules/ModusPonens.h"
#include "Rules/InferenceRules/ModusTollens.h"
#include "Rules/SimplifyRules/And.h"
#include "Rules/SimplifyRules/Nor.h"
#include "Rules/SimplifyRules/Nif.h"
#include "Solver/Statement.h"
#include "Solver/Solver.h"
#include <memory>
#include <iostream>
#include <vector>

void testSimplePropositions() {
    const std::shared_ptr<WellFormedFormula> A = std::make_shared<Variable>('A');
    const std::shared_ptr<WellFormedFormula> B = std::make_shared<Variable>('B');
    const auto conj = std::make_shared<Conjunction>(A, B);
    const auto disjunction = std::make_shared<Disjunction>(A, B);
    const auto implication = std::make_shared<Implication>(conj, disjunction);
    const auto equivalence = std::make_shared<Equivalence>(A, implication);
    const auto negation = Negation::of(equivalence);

    std::cout << Negation::of(negation)->getString() << "\n";
    std::cout << negation->getString() << "\n";
    std::cout << (*equivalence == Negation::of(negation)) << "\n";

    const auto conversedImplication = std::make_shared<Implication>(disjunction, conj);
    const auto flippedConjunction = std::make_shared<Conjunction>(B, A);

    std::cout << (*implication == conversedImplication) << "\n";
    std::cout << (*conj == flippedConjunction) << "\n";

    const auto negatedConjunction = std::dynamic_pointer_cast<Negation>(Negation::of(conj));
    const auto conjunctiveSyllogism = std::make_shared<ConjunctiveSyllogism>(negatedConjunction, A);

    std::cout << std::make_shared<ConjunctiveSyllogism>(negatedConjunction, B)->getString() << "\n";
    std::cout << std::make_shared<ConjunctiveSyllogism>(negatedConjunction, A)->getString() << "\n";

    std::cout << std::make_shared<DisjunctiveSyllogism>(disjunction, Negation::of(A))->getString() << "\n";
    std::cout << std::make_shared<DisjunctiveSyllogism>(disjunction, Negation::of(B))->getString() << "\n";

    std::cout << std::make_shared<ModusPonens>(implication, conj)->getString() << "\n";
    std::cout << std::make_shared<ModusTollens>(implication, Negation::of(disjunction))->getString() << "\n";

    auto andInferences = And::from(conj);
    std::cout << andInferences.first->getString() << "\n";
    std::cout << andInferences.second->getString() << "\n";

    const auto negatedDisjunction = std::dynamic_pointer_cast<Negation>(Negation::of(disjunction));
    auto norInferences = Nor::from(negatedDisjunction);
    std::cout << norInferences.first->getString() << "\n";
    std::cout << norInferences.second->getString() << "\n";

    const auto negatedImplication = std::dynamic_pointer_cast<Negation>(Negation::of(implication));
    auto nifInferences = Nif::from(negatedImplication);
    std::cout << nifInferences.first->getString() << "\n";
    std::cout << nifInferences.second->getString() << "\n";
}

void testSimpleSolver() {
    auto I = std::make_shared<Variable>('I');
    auto U = std::make_shared<Variable>('U');
    auto C = std::make_shared<Variable>('C');
    auto D = std::make_shared<Variable>('D');
    auto A = std::make_shared<Variable>('A');
    auto E = std::make_shared<Variable>('E');

    auto statement1 = std::make_shared<Implication>(I, std::make_shared<Conjunction>(U, Negation::of(C)));
    auto statement2 = std::make_shared<Implication>(U, std::make_shared<Disjunction>(D, E));
    auto statement3 = std::make_shared<Implication>(D, A);
    auto statement4 = Negation::of(A);
    auto statement5 = std::make_shared<Implication>(E, C);
    auto conclusion = Negation::of(I);

    std::vector<Statement> argument{
            {StatementType::PREMISE, statement1, 0},
            {StatementType::PREMISE, statement2, 0},
            {StatementType::PREMISE, statement3, 0},
            {StatementType::PREMISE, statement4, 0},
            {StatementType::PREMISE, statement5, 0},
            {StatementType::CONCLUSION, conclusion, 0},
    };
    auto results = Solver::solve(argument);
    for (const auto &result : results) {
        std::cout << result.getString() << "\n";
    }
}

int main() {
//    testSimplePropositions();
    testSimpleSolver();
}
