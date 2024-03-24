cmake_minimum_required(VERSION 3.22.1)
project(logic_solver)
set(CMAKE_CXX_STANDARD 23)

include_directories(src)
add_executable(${PROJECT_NAME}
        src/Propositions/Variable.h
        src/Propositions/Variable.cpp
        src/Propositions/BinaryOperations/BinaryOperation.h
        src/Propositions/BinaryOperations/Conjunction.h
        src/Propositions/BinaryOperations/Conjunction.cpp
        src/Propositions/BinaryOperations/Disjunction.h
        src/Propositions/BinaryOperations/Disjunction.cpp
        src/Propositions/Negation.h
        src/Propositions/Negation.cpp
        src/Propositions/WellFormedFormula.h
        src/Propositions/BinaryOperations/Implication.h
        src/Propositions/BinaryOperations/Implication.cpp
        src/Propositions/BinaryOperations/Equivalence.h
        src/Propositions/BinaryOperations/Equivalence.cpp
        src/Propositions/BinaryOperations/BinaryOperation.cpp
        src/main.cpp
        src/Rules/InferenceRules/ConjunctiveSyllogism.h
        src/Rules/InferenceRules/ConjunctiveSyllogism.cpp
        src/Rules/Inference.h
        src/Rules/Inference.cpp
        src/Rules/InferenceRules/DisjunctiveSyllogism.h
        src/Rules/InferenceRules/DisjunctiveSyllogism.cpp
        src/Rules/InferenceRules/ModusPonens.h
        src/Rules/InferenceRules/ModusPonens.cpp
        src/Propositions/WellFormedFormula.cpp
        src/Rules/InferenceRules/ModusTollens.h
        src/Rules/InferenceRules/ModusTollens.cpp
        src/Rules/SimplifyRules/And.cpp)
