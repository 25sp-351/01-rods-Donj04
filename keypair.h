#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <stdlib.h>

typedef struct {
    size_t key;
    int value;
} KeyPair;

KeyPair createKeyPair(size_t key, int value);

// Setter functions
void setKey(KeyPair* pair, size_t new_key);

void setValue(KeyPair* pair, int new_value);

// Getter functions
size_t getKey(KeyPair* pair);

int getValue(KeyPair* pair);

#endif