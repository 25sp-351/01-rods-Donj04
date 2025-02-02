#ifndef RODCUTSOLVER_H
#define RODCUTSOLVER_H

#include "vec.h"

typedef struct rodcutsolver {
    size_t rod_length;
    Vec length_prices;  // Keypair = {length, price of length}
    Vec cut_list;       // Keypair = {length, number of pieces}
    int result_profit;
    size_t remainder;
} *RodCutSolver;

RodCutSolver createRodCutSolver(size_t rod_length);

void freeRodCutSolver(RodCutSolver solver);

void setLengthPrices(RodCutSolver solver, Vec v);

void solveRodCutting(RodCutSolver solver);

#endif
