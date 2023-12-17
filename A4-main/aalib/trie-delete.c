#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"

// Helper function to recursively delete a key from the trie
static int deleteKeyHelper(TrieNode **nodeRef, AAKeyType key, size_t keyLength, size_t level) {
    if (nodeRef == NULL || *nodeRef == NULL) {
        return 0; // Key not found or invalid node reference
    }

    TrieNode *node = *nodeRef;
    int deleted = 0;

    // If last character of key is being processed
    if (level == keyLength) {
        if (node->isKeySoHasValue) {
            node->isKeySoHasValue = 0; // Unmark leaf node
            deleted = 1;
        }
    } else {
        // If not last character, recur for the child
        int index = key[level];
        deleted = deleteKeyHelper(&(node->subtries[index]), key, keyLength, level + 1);
    }

    // Check if node can be deleted
    if (deleted && node->nSubtries == 0 && !node->isKeySoHasValue) {
        trieDeleteNode(node);
        *nodeRef = NULL;
        return 1; // Node deleted
    }

    return deleted; // Node deleted or not
}

// Function to delete a key from the trie
void *trieDeleteKey(KeyValueTrie *root, AAKeyType key, size_t keyLength, int *cost) {
    if (root == NULL || key == NULL) {
        return NULL;
    }

    // Start from the root and delete the key
    deleteKeyHelper(&(root->subtries[key[0]]), key, keyLength, 1);

    // Update cost if provided
    if (cost) {
        *cost += 1; // Example cost update, adjust as needed
    }

    return NULL; // Return value can be adjusted as per requirement
}
