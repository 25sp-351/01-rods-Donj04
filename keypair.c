#include "keypair.h"

KeyPair createKeyPair(size_t key, int value) {
    KeyPair new_pair;
    setKey(&new_pair, key);
    setValue(&new_pair, value);
    return new_pair;
}

// Setter functions
void setKey(KeyPair* pair, size_t new_key) {
    pair->key = new_key;
}

void setValue(KeyPair* pair, int new_value) {
    pair->value = new_value;
}

// Getter functions
size_t getKey(KeyPair* pair) {
    return pair->key;
}

int getValue(KeyPair* pair) {
    return pair->value;
}
