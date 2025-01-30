#ifndef RODCUTSOLVER_H
#define RODCUTSOLVER_H

#include "pairvector.h"

typedef struct
{
    PairVector pairs;
} RodCutSolver;

RodCutSolver createRodCutSolver();

void freeRodCutSolver(RodCutSolver* solver);

bool addLength(RodCutSolver* solver, KeyPair pair);

bool removeLength(RodCutSolver* solver, KeyPair pair);

PairVector solveRodCutting(RodCutSolver* solver, int rod_length);

#endif
