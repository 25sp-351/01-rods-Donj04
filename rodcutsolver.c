#include "rodcutsolver.h"

#include <stdbool.h>
#include <stdio.h>

#include "keypair.h"

// typedef struct rodcutsolver {
//     size_t rod_length;
//     Vec length_prices;  // Keypair = {length, price of length}
//     Vec cut_list;       // Keypair = {length, number of pieces}
//     int result_profit;
//     size_t remainder;
// } *RodCutSolver;

RodCutSolver createRodCutSolver(size_t rod_length) {
    RodCutSolver solver   = malloc(sizeof(struct rodcutsolver));
    solver->rod_length    = rod_length;
    solver->length_prices = new_vec(sizeof(KeyPair));
    solver->cut_list      = new_vec(sizeof(KeyPair));
    solver->result_profit = 0;
    solver->remainder     = 0;
    return solver;
}

void freeRodCutSolver(RodCutSolver solver) {
    vec_free(solver->length_prices);
    vec_free(solver->cut_list);
}

void setLengthPrices(RodCutSolver solver, Vec v) {
    vec_free(solver->length_prices);
    solver->length_prices = vec_copy(v);
}

void setCutList(RodCutSolver solver, size_t cuts[]) {
    size_t temp_length  = solver->rod_length;

    int remaining_loops = solver->rod_length;  // To prevent infinite loops
    while (temp_length > 0 && remaining_loops > 0) {
        size_t cut = cuts[temp_length];

        if (cut > 0) {
            bool unique = true;
            // Search for the KeyPair with a key matching with cut
            for (size_t i = 0; i < vec_length(solver->cut_list); i++) {
                // Get a pointer to the pair at this index of the vec
                KeyPair* pair = vec_get(solver->cut_list, i);
                if (pair->key == cut) {
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
        remaining_loops--;
    }
    solver->remainder = temp_length;
}

void printOutput(RodCutSolver solver, int prices[]) {
    for (size_t i = 0; i < vec_length(solver->cut_list); i++) {
        KeyPair* pair = vec_get(solver->cut_list, i);
        int price     = prices[pair->key];
        printf("%zu @ %d = %d\n", pair->key, pair->value, pair->value * price);
    }
    printf("Remainder: %zu\n", solver->remainder);
    printf("Value: %d\n", solver->result_profit);
}

void solveRodCutting(RodCutSolver solver) {
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
        KeyPair* pair = vec_get(solver->length_prices, j);
        if (pair->key < arr_size)
            prices[pair->key] = pair->value;
    }

    // debug
    // for (size_t i = 0; i < arr_size; i++)
    //     printf("%d ", prices[i]);
    // printf("\n");

    // Algorithm to solve rod cutting problem
    for (size_t first_cut = 1; first_cut <= solver->rod_length; first_cut++) {
        int curr_max = 0;
        int best_cut = 0;

        for (size_t sub_cut = 1; sub_cut <= first_cut; sub_cut++) {
            int profit = prices[sub_cut] + max_profit[first_cut - sub_cut];
            // printf("%zu: %zu: %d\n", first_cut, sub_cut, prices[sub_cut]);
            if (prices[sub_cut] > 0 && profit > curr_max) {
                curr_max = profit;
                best_cut = sub_cut;
                // printf("profit %d, add cut %zu\n", profit, sub_cut);
            }
        }
        max_profit[first_cut] = curr_max;
        cuts[first_cut]       = best_cut;
    }
    solver->result_profit = max_profit[solver->rod_length];
    setCutList(solver, cuts);
    printOutput(solver, prices);
}
