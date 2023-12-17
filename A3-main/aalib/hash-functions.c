#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()

#include "hashtools.h"

// Function to check if two keys are the same
int doKeysMatch(AAKeyType key1, size_t key1len, AAKeyType key2, size_t key2len) {
    if (key1len != key2len) return 0;
    return memcmp(key1, key2, key1len) == 0;
}

// Function to provide the hex representation of a value
static char toHex(int val) {
    return val < 10 ? (char) ('0' + val) : (char) ('a' + (val - 10));
}

// Function to provide the key in a printable form
int printableKey(char *buffer, int bufferlen, AAKeyType key, size_t printlen) {
    int i, allChars = 1;
    char *loadptr;

    for (i = 0; allChars && i < printlen; i++) {
        if (!isprint(key[i])) allChars = 0;
    }

    if (allChars) {
        snprintf(buffer, bufferlen, "char key:[%s]", (char *) key);
    } else {
        snprintf(buffer, bufferlen, "hex key:[0x");
        loadptr = &buffer[strlen(buffer)];
        for (i = 0; i < printlen && loadptr - buffer < bufferlen - 4; i++) {
            *loadptr++ = toHex((key[i] & 0xf0) >> 4);
            *loadptr++ = toHex(key[i] & 0x0f);
        }
        *loadptr++ = ']';
        *loadptr = 0;
    }
    return 1;
}

// Hash function based on the length of the key
HashIndex hashByLength(AAKeyType key, size_t keyLength, HashIndex size) {
    return keyLength % size;
}

// Hash function based on the sum of the values in the key
HashIndex hashBySum(AAKeyType key, size_t keyLength, HashIndex size) {
    HashIndex sum = 0;
    for (size_t i = 0; i < keyLength; ++i) {
        sum += (unsigned char)key[i];
    }
    return sum % size;
}

// Linear probing function
HashIndex linearProbe(AssociativeArray *hashTable, AAKeyType key, size_t keylength, int index, int invalidEndsSearch, int *cost) {
    int i = index;
    do {
        if (hashTable->table[i].validity != HASH_USED || doKeysMatch(key, keylength, hashTable->table[i].key, hashTable->table[i].keylen)) {
            return i;
        }
        i = (i + 1) % hashTable->size;
    } while (i != index);
    return -1;
}

// Quadratic probing function
HashIndex quadraticProbe(AssociativeArray *hashTable, AAKeyType key, size_t keylen, int startIndex, int invalidEndsSearch, int *cost) {
    int i = 0;
    int index;
    do {
        index = (startIndex + i * i) % hashTable->size;
        if (hashTable->table[index].validity != HASH_USED || doKeysMatch(key, keylen, hashTable->table[index].key, hashTable->table[index].keylen)) {
            return index;
        }
        i++;
    } while (i < hashTable->size);
    return -1;
}

// Double hashing probing function
HashIndex doubleHashProbe(AssociativeArray *hashTable, AAKeyType key, size_t keylen, int startIndex, int invalidEndsSearch, int *cost) {
    int stepSize = hashBySum(key, keylen, hashTable->size); // Using hashBySum as the second hash function
    int index = startIndex;
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[index].validity != HASH_USED || doKeysMatch(key, keylen, hashTable->table[index].key, hashTable->table[index].keylen)) {
            return index;
        }
        index = (index + stepSize) % hashTable->size;
    }
    return -1;
}
