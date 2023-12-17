#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"

/** compare a key with the letter in a node */
int trie_subtreeSearchComparator(const void *keyValue, const void *nodePtr) {
    TrieNode **node = (TrieNode **) nodePtr;
    AAKeyType key = (AAKeyType) keyValue;
    return (key[0] - (*node)->letter);
}

/** create a whole chain for the rest of the key */
static TrieNode * trie_create_chain(AAKeyType key, size_t keylength, void *value, int *cost) {
    TrieNode *current = NULL, *head = NULL;
    for (size_t i = 0; i < keylength; ++i) {
        TrieNode *newNode = malloc(sizeof(TrieNode));
        assert(newNode != NULL);
        newNode->letter = key[i];
        newNode->value = (i == keylength - 1) ? value : NULL;
        newNode->subtries = NULL;
        newNode->nSubtries = 0;

        if (current) {
            current->subtries = realloc(current->subtries, sizeof(TrieNode *));
            assert(current->subtries != NULL);
            current->subtries[0] = newNode;
            current->nSubtries = 1;
        } else {
            head = newNode;
        }
        current = newNode;
    }
    return head;
}

/** add the given chain to the list of tries in the current node */
static int trie_add_chain(TrieNode **subtreeList, int nSubtries, AAKeyType key, TrieNode *newChain) {
    // Implementation of adding the chain to the trie
    // ...
    return 0; // Return appropriate value
}

/** link the provided key into the current chain */
static int trie_link_to_chain(TrieNode *current, AAKeyType key, size_t keylength, void *value, int *cost) {
    // Implementation of linking the key into the chain
    // ...
    return 0; // Return appropriate value
}

int trieInsertKey(KeyValueTrie *root, AAKeyType key, size_t keylength, void *value, int *cost) {
    if (root->maxKeyLength < keylength) {
        root->maxKeyLength = keylength;
    }

    if (root->nSubtries == 0) {
        root->subtries[root->nSubtries++] = trie_create_chain(key, keylength, value, cost);
        return 0;
    }

    // Find the subtrie with the leading letter of the key
    // and insert the new key into the correct subtrie chain
    // based on that letter
    // ...
    return 0; // Return appropriate value
}
