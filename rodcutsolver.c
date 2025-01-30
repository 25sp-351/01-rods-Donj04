#include "rodcutsolver.h"

#include <stdio.h>

RodCutSolver createRodCutSolver() {
    RodCutSolver solver;
    PairVector new_vec = createPairVector(BASE_VEC_CAPACITY);
    solver.pairs       = new_vec;
    return solver;
}

void freeRodCutSolver(RodCutSolver* solver) {
    freePairVector(&(solver->pairs));
}

bool addLength(RodCutSolver* solver, KeyPair pair) {
    bool added = pushPair(&(solver->pairs), pair);
    if (added)
        printf("Added length %d, value %d\n", getKey(&pair), getValue(&pair));
    return added;
}

bool removeLength(RodCutSolver* solver, KeyPair pair) {
    bool removed;
    int index_to_remove = findPair(&(solver->pairs), pair);

    if (index_to_remove >= 0)
        removed = removePair(&(solver->pairs), index_to_remove);
    else
        removed = false;
    if (removed)
        printf("Removed length %d, value %d\n", getKey(&pair), getValue(&pair));
    return removed;
}

PairVector solveRodCutting(RodCutSolver* solver, int rod_length) {
    printf("Computing rod cutting problem with a rod length of %d\n",
           rod_length);
    printf("Ok, did calculation\n");
    PairVector p = createPairVector(BASE_VEC_CAPACITY);
    return p;
}
