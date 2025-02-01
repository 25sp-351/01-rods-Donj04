#ifndef RODCUTSOLVER_H
#define RODCUTSOLVER_H

#include "vec.h"

typedef struct
{
    Vec length_prices;
    size_t rod_length;
    Vec cut_list;
    int result_value;
    size_t remainder;
} RodCutSolver;

RodCutSolver createRodCutSolver(size_t rod_length);

void setLengthPrices(RodCutSolver* solver, Vec v);

void solveRodCutting(RodCutSolver* solver);

#endif
