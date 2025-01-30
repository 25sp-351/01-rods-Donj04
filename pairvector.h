#ifndef PAIRVECTOR_H
#define PAIRVECTOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "keypair.h"

#define BASE_VEC_CAPACITY 16

typedef struct {
    KeyPair* pairs;
    size_t size;
    size_t capacity;
} PairVector;

PairVector createPairVector(size_t init_capacity);

void freePairVector(PairVector* vector);

size_t getSize(PairVector* vector);

bool pushPair(PairVector* vector, KeyPair pair);

bool removePair(PairVector* vector, int index);

bool popPair(PairVector* vector);

KeyPair getPair(PairVector* vector, int index);

int findPair(PairVector* vector, KeyPair pair);

#endif
