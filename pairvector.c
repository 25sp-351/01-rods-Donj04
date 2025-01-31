#include "pairvector.h"

#include <stdio.h>

#include "keypair.h"

PairVector createPairVector(size_t init_capacity) {
    PairVector new_vec;
    new_vec.size  = 0;
    new_vec.pairs = (KeyPair*)malloc(init_capacity * sizeof(KeyPair));

    if (new_vec.pairs == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        new_vec.capacity = 0;
    } else {
        new_vec.capacity = init_capacity;
    }
    return new_vec;
}

void freePairVector(PairVector* vector) {
    free(vector->pairs);
    vector->pairs    = NULL;
    vector->size     = 0;
    vector->capacity = 0;
}

size_t getSize(PairVector* vector) {
    return vector->size;
}

bool pushPair(PairVector* vector, KeyPair pair) {
    if (vector->size >= vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        KeyPair* new_pairs =
            (KeyPair*)realloc(vector->pairs, new_cap * sizeof(KeyPair));

        if (new_pairs != NULL) {
            vector->pairs    = new_pairs;
            vector->capacity = new_cap;
        } else {
            fprintf(stderr, "ERROR: Memory allocation failed\n");
            return false;
        }
    }
    vector->pairs[vector->size] = pair;
    vector->size++;
    return true;
}

bool removePair(PairVector* vector, int index) {
    if (index >= 0 && index < vector->size) {
        for (size_t i = index; i < vector->size - 1; i++)
            vector->pairs[i] = vector->pairs[i + 1];
        vector->size--;

        if (vector->capacity > 1 && vector->size < (vector->capacity / 4)) {
            size_t new_cap     = vector->capacity / 2;
            KeyPair* new_pairs = (KeyPair*)realloc(
                vector->pairs, vector->capacity * sizeof(KeyPair));

            if (new_pairs != NULL) {
                vector->pairs    = new_pairs;
                vector->capacity = new_cap;
            } else {
                fprintf(stderr, "ERROR: Memory allocation failed\n");
                return false;
            }
        }
    } else {
        fprintf(stderr, "ERROR: Index out of bounds\n");
        return false;
    }
    return true;
}

bool popPair(PairVector* vector) {
    return removePair(vector, vector->size - 1);
}

KeyPair getPairCopy(PairVector* vector, int index) {
    if (index >= 0 && index < vector->size) {
        return vector->pairs[index];
    } else {
        KeyPair err_pair;
        setKey(&err_pair, -1);
        setValue(&err_pair, -1);
        fprintf(stderr, "ERROR: Index out of bounds\n");
        return err_pair;
    }
}

KeyPair* getPairRef(PairVector* vector, int index) {
    if (index >= 0 && index < vector->size) {
        return &(vector->pairs[index]);
    } else {
        fprintf(stderr, "ERROR: Index out of bounds\n");
        return NULL;
    }
}

int findPair(PairVector* vector, KeyPair pair) {
    for (size_t i = 0; i < vector->size; i++) {
        size_t key = getKey(&(vector->pairs[i]));
        int value  = getValue(&(vector->pairs[i]));
        if (key == getKey(&pair) && value == getValue(&pair))
            return i;
    }
    printf("Pair not found\n");
    return -1;
}

int findPairByKey(PairVector* vector, size_t search_key) {
    for (size_t i = 0; i < vector->size; i++) {
        size_t key = getKey(&(vector->pairs[i]));
        if (search_key == key)
            return i;
    }
    // printf("Pair not found\n");
    return -1;
}
