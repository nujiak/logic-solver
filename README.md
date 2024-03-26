# logic-solver

## Introduction

`logic-solver` proves logical arguments using methods
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
| Negation         | !      |

First, write the argument into a text file, using the symbols above. For example:

> ```console
> logic-solver/build$ cat sample_argument.in
> I > (U & !C)
> U > (D @ E)
> D > A
> !A
> E > C
> !I
> ```

Then, pipe the file content into `logic_solver`:

```console
cat sample_argument.in | .build/logic_solver
```

`logic-solver` will then complete the proof and output the simplified statements:

> ```console
> logic-solver/build$ cat sample_argument.in | ./build/logic_solver
> 1. (I > (U & !C)) 
> 2. (U > (D @ E))
> 3. (D > A)
> 4. !A
> 5. (E > C)
 > | ∴ !I
> 6. asm: I (from 5)
> 7. ∴ (U & !C) (from 1 6) MP
> 8. ∴ !D (from 3 4) MT
> 9. ∴ U (from 7) AND
> 10. ∴ !C (from 7) AND
> 11. ∴ (D @ E) (from 2 9) MP
> 12. ∴ !E (from 5 10) MT
> 13. ∴ D (from 11 12) DS
> 14. !I (from 6; 8 contradicts 13)
> ```

Note that `logic-solver` takes the last proposition in the given argument as the conclusion, and blocks it then assumes the negation.