#include "rodcutsolver.h"

#include <stdio.h>

RodCutSolver createRodCutSolver(size_t rod_length) {
    RodCutSolver solver;
    PairVector new_given_vec    = createPairVector(BASE_VEC_CAPACITY);
    PairVector new_solution_vec = createPairVector(BASE_VEC_CAPACITY);

    solver.given_lengths_values = new_given_vec;
    solver.solution_pairs       = new_solution_vec;
    solver.rod_length           = rod_length;
    return solver;
}

void freeRodCutSolver(RodCutSolver* solver) {
    freePairVector(&(solver->given_lengths_values));
    freePairVector(&(solver->solution_pairs));
    solver->rod_length = 0;
}

bool addLength(RodCutSolver* solver, KeyPair pair) {
    bool added = pushPair(&(solver->given_lengths_values), pair);
    if (added)
        printf("Added length %zu, value %d\n", getKey(&pair), getValue(&pair));
    return added;
}

bool removeLength(RodCutSolver* solver, KeyPair pair) {
    bool removed;
    int index_to_remove = findPair(&(solver->given_lengths_values), pair);

    if (index_to_remove >= 0)
        removed = removePair(&(solver->given_lengths_values), index_to_remove);
    else
        removed = false;
    if (removed)
        printf("Removed length %zu, value %d\n", getKey(&pair),
               getValue(&pair));
    return removed;
}

void addSolutionLength(RodCutSolver* solver, size_t length) {
    int index = findPairByKey(&(solver->solution_pairs), length);

    if (index >= 0) {
        KeyPair* pair = getPairRef(&(solver->given_lengths_values), index);
        setValue(pair, getValue(pair) + 1);
    } else {
        KeyPair new_pair = createKeyPair(length, 1);
        pushPair(&(solver->solution_pairs), new_pair);
    }
}

void removeSolutionLength(RodCutSolver* solver, size_t length) {
    int index = findPairByKey(&(solver->solution_pairs), length);

    if (index >= 0) {
        KeyPair* pair = getPairRef(&(solver->given_lengths_values), index);
        setValue(pair, getValue(pair) - 1);
        if (getValue(pair) <= 0)
            removeLength(solver, *pair);
    }
}

int cutRod(RodCutSolver* solver, size_t* lengths_arr, size_t remaining_length, size_t recursion_depth) {
    if (remaining_length <= 0)
        return 0;

    int max            = 0;

    for (size_t i = 0; i < solver->given_lengths_values.size; i++) {
        KeyPair pair    = getPairCopy(&(solver->given_lengths_values), i);
        size_t length   = getKey(&pair);
        int value       = getValue(&pair);

        int total_value = 0;
        // printf("checking length %zu\n", length);
        if (length <= remaining_length)
            total_value = value + cutRod(solver, lengths_arr, remaining_length - length, recursion_depth + 1);
        if (total_value > 0 && total_value >= max) {
            max         = total_value;
            // ? TODO: total price is correct, but does not show lengths correctly
            lengths_arr[recursion_depth] = length;
            // for (size_t i = recursion_depth + 1; i < solver->rod_length; i++)
            // {
            //     lengths_arr[i] = 0;
            // }
            
            printf("recursion: %zu, length %zu, $%d\n", recursion_depth, length, max);
        }
    }
    return max;
}

PairVector solveRodCutting(RodCutSolver* solver) {
    printf("Computing rod cutting problem with a rod length of %zu\n",
           solver->rod_length);

    printf("%zu pairs\n", solver->given_lengths_values.size);

    size_t arr_size = solver->rod_length;
    size_t* lengths = (size_t*)malloc(arr_size * sizeof(size_t));
    if (lengths == NULL) {
        printf("ERROR: Memory allocation failed\n");
    }
    for (size_t i = 0; i < arr_size; i++)
    {
        lengths[i] = 0;
    }
    
    
    int result = cutRod(solver, lengths, solver->rod_length, 0);
    for (size_t i = 0; i < arr_size; i++)
    {
        printf("%zu, ", lengths[i]);
    }
    printf("\n");
    

    printf("Result: $%d\n", result);

    printf("Ok, did calculation\n");
    PairVector p = createPairVector(BASE_VEC_CAPACITY);
    free(lengths);
    return p;
}

int findMax(int* array, size_t size) {
    if (size <= 0)
        return 0;
    int max = array[0];
    for (size_t i = 0; i < size; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}
