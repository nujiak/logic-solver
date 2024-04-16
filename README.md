# logic-solver

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/nujiak/logic-solver/cmake-multi-platform.yml?label=tests)

## Introduction

`logic-solver` proves or refutes propositional and quantificational logic arguments using methods
from [Introduction to logic](https://archive.org/details/introductiontolo0003gens_k7f4/page/424/mode/2up), as taught
in [GET1028/GEX1014 Logic](https://nusmods.com/courses/GET1028/logic).

The current implemented rules are:

- S-Rules
    - AND
    - NOR
    - NIF
    - EQ
    - NEQ
- I-Rules
    - Conjunctive syllogism (CS)
    - Disjunctive syllogism (DS)
    - Modus ponens (MP)
    - Modus tollens (MT)
    - IFF
    - NIFF

The following techniques are currently implemented:

1. Easier proofs
2. Harder proofs (by breaking implications, conjunctions, and disjunctions)
3. Easier refutations
4. Harder refutations (by breaking implications, conjunctions, and disjunctions)

The following quantificational logic rules are currently implemented:

1. Drop squiggle
2. Drop existential
3. Drop universal

## Compiling

`logic-solver` can be compiled using CMake.

1. Clone the repository:

```console
git clone https://github.com/nujiak/logic-solver
```

2. Compile `logic-solver`:

```console
cd logic-solver
cmake -B build
cmake --build build
```

3. `logic-solver` will be compiled into an executable `logic_solver` in the `build` subdirectory.

## Usage

`logic-solver` completes a proof by contradiction given an argument. An argument is a list of propositions where all
propositions are taken as premises, except the last which is taken as a conclusion.

The following symbols are used:

| Logical operator | Symbol |
|------------------|--------|
| Conjunction      | &      |
| Disjunction      | @      |
| Implication      | \>     |
| Equivalence      | =      |
| Negation         | ~      |

First, write the argument into a text file, using the symbols above. For example:

> ```console
> logic-solver/build$ cat sample_argument.in
> ((X>E)>(~C&T))
> (C&~P)
> ~(~X@P)
> ```

Then, redirect the file into `logic_solver`:

```console
.build/logic_solver < sample_argument.in
```

`logic-solver` will then complete the proof and output the simplified statements:

> ```console
> logic-solver/build$ ./build/logic_solver < sample_argument.in
> 1. ((X>E)>(~C&T))
> 2. (C&~P)
>  | ∴ ~(~X@P)
> 3. asm: (~X@P) (from 2)
> 4. ∴ C (from 1) AND
> 5. ∴ ~P (from 1) AND
> 6. ∴ ~X (from 3, 5) DS
> 7.   asm: ~(X>E) (break 1)
> 8.   ∴ X (from 7) NIF
> 9. ∴ (X>E) (from 7; 6 contradicts 8)
> 10. ∴ (~C&T) (from 0, 9) MP
> 11. ∴ ~C (from 10) AND
> 12. ∴ ~(~X@P) (from 3; 4 contradicts 11)
> ```

Note that `logic-solver` takes the last proposition in the given argument as the conclusion, and blocks it then assumes the negation.