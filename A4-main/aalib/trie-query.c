#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>
#include <stdbool.h>
#include "trie_defs.h"

/** find a key within the trie */
void *trieLookupKey(
        KeyValueTrie *root,
        AAKeyType key, size_t keylength,
        int *cost
    )
{
    if (root == NULL || key == NULL || root->nSubtries == 0) {
        return NULL; // Check for null pointers and empty trie
    }

    TrieNode *current = root;
    for (size_t i = 0; i < keylength; i++) {
        bool found = false;
        for (int j = 0; j < current->nSubtries; j++) {
            if (current->subtries[j]->letter == key[i]) {
                current = current->subtries[j];
                found = true;
                if (cost) (*cost)++;
                break;
            }
        }
        if (!found) {
            return NULL; // Key not found in the trie
        }
    }

    // Check if the final node represents the end of a key
    if (current->isKeySoHasValue) {
        return current->value; // Return the value if it's a valid key
    }

    return NULL; // Key not found or not a valid key
}
