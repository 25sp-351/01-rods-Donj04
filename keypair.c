#include "keypair.h"

KeyPair createKeyPair(int key, int value) {
    KeyPair new_pair;
    setKey(&new_pair, key);
    setValue(&new_pair, value);
    return new_pair;
}

// Setter functions
void setKey(KeyPair* pair, int new_key) {
    pair->key = new_key;
}

void setValue(KeyPair* pair, int new_value) {
    pair->value = new_value;
}

// Getter functions
int getKey(KeyPair* pair) {
    return pair->key;
}

int getValue(KeyPair* pair) {
    return pair->value;
}
