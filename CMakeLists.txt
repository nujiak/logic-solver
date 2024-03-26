cmake_minimum_required(VERSION 3.22.1)
project(logic_solver)
set(CMAKE_CXX_STANDARD 23)

include_directories(src)
add_executable(
        ${PROJECT_NAME}
        src/main.cpp
)
add_library(${PROJECT_NAME}_lib
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
        src/Propositions/WellFormedFormula.cpp
        src/Solver/Solver.cpp
        src/Solver/Statement.h
        src/Solver/Statement.cpp
        src/Rules/IRules.h
        src/Rules/IRules.cpp
        src/Rules/SRules.h
        src/Rules/SRules.cpp
        src/Solver/Rule.h
        src/Solver/Printer.h
        src/Solver/Printer.cpp
        src/Parser/Parser.h
        src/Parser/Parser.cpp
        src/NotImplementedError.h
)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/a1a608348ee09747d27a1501debf9c975142d06a.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        run_unit_tests
        test/Propositions/Variable.cpp
)
enable_testing()
target_link_libraries(
        run_unit_tests
        ${PROJECT_NAME}_lib
        GTest::gtest
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(run_unit_tests)