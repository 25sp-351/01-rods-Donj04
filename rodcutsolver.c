#include "rodcutsolver.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "keypair.h"

RodCutSolver createRodCutSolver(size_t rod_length) {
    RodCutSolver solver;
    solver.rod_length    = rod_length;
    solver.length_prices = new_vec(sizeof(KeyPair));
    solver.cut_list      = new_vec(sizeof(KeyPair));
    solver.result_value  = 0;
    solver.remainder     = 0;
    return solver;
}

void freeRodCutSolver(RodCutSolver* solver) {
    vec_free(solver->length_prices);
    vec_free(solver->cut_list);
}

void setLengthPrices(RodCutSolver* solver, Vec v) {
    vec_free(solver->length_prices);
    solver->length_prices = vec_copy(v);
}

void setCutList(RodCutSolver* solver, size_t cuts[]) {
    size_t temp_length = solver->rod_length;

    while (temp_length > 0) {
        size_t cut = cuts[temp_length];
        printf("%zu\n", cut);

        bool unique = true;
        for (size_t i = 0; i < vec_length(solver->cut_list); i++) {
            // Get a pointer to the pair at this index of the vec
            KeyPair* pair = &((KeyPair*)vec_items(solver->cut_list))[i];
            if (cut > 0 && pair->key == cut) {
                pair->value++;
                unique = false;
                break;
            }
        }
        if (unique) {
            KeyPair new_pair = createKeyPair(cut, 1);
            vec_add(solver->cut_list, &new_pair);
        }
        temp_length -= cut;
    }
    solver->remainder = temp_length;
}

void printOutput(RodCutSolver solver, int prices[]) {
    for (size_t i = 0; i < vec_length(solver.cut_list); i++) {
        KeyPair* pair = &((KeyPair*)vec_items(solver.cut_list))[i];

        int price = prices[pair->key];
        printf("%zu @ %d = %d\n", pair->key, pair->value, pair->value * price);
    }
    printf("Remainder: %zu\n", solver.remainder);
    printf("Value: %d\n", solver.result_value);
}

void solveRodCutting(RodCutSolver* solver) {
    size_t arr_size = solver->rod_length + 1;
    int prices[arr_size];
    int max_profit[arr_size];
    size_t cuts[arr_size];

    // Initialize elements of arrays
    for (size_t i = 0; i < arr_size; i++) {
        prices[i]     = 0;
        max_profit[i] = 0;
        cuts[i]       = 0;
    }
    // Set length prices. Each index in prices[] corresponds to a length
    for (size_t j = 0; j < vec_length(solver->length_prices); j++) {
        // Get KeyPair at index j
        KeyPair pair = ((KeyPair*)vec_items(solver->length_prices))[j];
        if (pair.key < arr_size)
            prices[pair.key] = pair.value;
    }

    // debug
    for (size_t i = 0; i < arr_size; i++)
        printf("%d ", prices[i]);
    printf("\n");

    // Algorithm to solve rod cutting problem
    // for some reason 1 is included in the cuts even when it has 0 price
    for (size_t length = 1; length <= solver->rod_length; length++) {
        int curr_max = 0;
        for (size_t cut_length = 1; cut_length <= length; cut_length++) {
            int profit = prices[cut_length] + max_profit[length - cut_length];
            if (profit > curr_max) {
                curr_max     = profit;
                cuts[length] = cut_length;
            }
        }
        max_profit[length] = curr_max;
    }
    solver->result_value = max_profit[solver->rod_length];
    setCutList(solver, cuts);
    printOutput(*solver, prices);
}
