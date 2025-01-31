#ifndef RODCUTSOLVER_H
#define RODCUTSOLVER_H

#include "pairvector.h"

typedef struct
{
    PairVector given_lengths_values;
    PairVector solution_pairs;
    size_t rod_length;
} RodCutSolver;

RodCutSolver createRodCutSolver(size_t rod_length);

void freeRodCutSolver(RodCutSolver* solver);

bool addLength(RodCutSolver* solver, KeyPair pair);

bool removeLength(RodCutSolver* solver, KeyPair pair);

PairVector solveRodCutting(RodCutSolver* solver);

#endif
