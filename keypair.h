#ifndef KEYPAIR_H
#define KEYPAIR_H

typedef struct KeyPair {
    int key;
    int value;
} KeyPair;

// Setter functions
void setKey(KeyPair *pair, int new_key);

void setValue(KeyPair *pair, int new_value);

// Getter functions
int getKey(KeyPair *pair);

int getValue(KeyPair *pair);

#endif