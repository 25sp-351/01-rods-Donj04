#ifndef KEYPAIR_H
#define KEYPAIR_H

typedef struct {
    int key;
    int value;
} KeyPair;

KeyPair createKeyPair(int key, int value);

// Setter functions
void setKey(KeyPair* pair, int new_key);

void setValue(KeyPair* pair, int new_value);

// Getter functions
int getKey(KeyPair* pair);

int getValue(KeyPair* pair);

#endif