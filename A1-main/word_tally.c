// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "LLNode.h"
// #include "word_extractor.h"

// int printData(char *filename, LLNode **wordListHeads, int maxLen);
// int printHapax(char *filename, LLNode **wordListHeads, int maxLen, int hapaxLength);

// // Function to tally words in a file
// int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen) {
// 	//creating a word extractor for a specific given file
//     struct WordExtractor *we = weCreateExtractor(filename, maxLen);
//     if (!we) {
//         fprintf(stderr, "Error: Could not open file %s\n", filename);
//         return -1;
//     }
// 	int wordCount = 0; // setting word count to 0

// 	//while loop to go through each word in the file
//     while (weHasMoreWords(we)) {
//         char *word = weGetNextWord(we);
//         int len = strlen(word);
//         if (len > maxLen) {
//             continue;  // if length of a word is over the maximum it skips it
//         }

// 		//checks if word already exists
//         LLNode *node = llLookupKey(wordLists[len], word);
//         if (node) {
// 			// Increment count for existing word
//             node->value++;  
//         } else {
//             // Add new word to the list with count 1
//             node = llNewNode(strdup(word), 1);
//             wordLists[len] = llAppend(wordLists[len], node);
//         }
// 		wordCount++;
//     }
// 	//cleanup (deletes the extractor)
//     weDeleteExtractor(we);
//     return wordCount;
// }

// // Function to print all data loaded
// int printData(char *filename, LLNode **wordListHeads, int maxLen) {
//     printf("Data from file '%s':\n", filename);
// 	// a for loop to go through words of all lengths up to maximum length
//     for (int i = 0; i <= maxLen; i++) {
//         LLNode *current = wordListHeads[i];
//         while (current) {
//             printf("%s: %d\n", current->key, current->value);
//             current = current->next;
//         }
//     }
//     return 0;
// }

// // Function to print hapax legomena
// int printHapax(char *filename, LLNode **wordListHeads, int maxLen, int hapaxLength) {
//     printf("Hapax legomena from file '%s':\n", filename);
// 	// a for loop to go through words of all lengths up to maximum length
//     for (int i = 0; i <= maxLen; i++) {
//         if (hapaxLength == 0 || hapaxLength == i) {
//             LLNode *current = wordListHeads[i];
//             while (current) {
// 				//if words appear only once its a hapax legomenon
//                 if (current->value == 1) {
//                     printf("%s\n", current->key);
//                 }
//                 current = current->next; //move to next node
//             }
//         }
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LLNode.h"
#include "word_extractor.h"

// Declaring the prototypes for printData and printHapax functions
int printData(char *filename, LLNode **wordListHeads, int maxLen);
int printHapax(char *filename, LLNode **wordListHeads, int maxLen, int hapaxLength);

// The function tallyWordsInFile is designed to tally words read from a file.
// It takes a filename, an array of linked lists of words (wordLists), and an integer maxLen representing the maximum allowable word length.
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen) {
    // Creating a word extractor for the given file. The word extractor is responsible for reading words from the file.
    struct WordExtractor *we = weCreateExtractor(filename, maxLen);
    
    // If the word extractor could not be created, it implies that the file could not be opened.
    // In such case, an error message is printed to the standard error stream and the function returns -1.
    if (!we) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return -1;
    }

    // Initializing wordCount to keep track of the number of words read from the file.
    int wordCount = 0;

    // Iterating through each word in the file using the word extractor.
    while (weHasMoreWords(we)) {
        // Retrieving the next word from the word extractor
        char *word = weGetNextWord(we);
        int len = strlen(word);

        // If the word length exceeds the specified maximum length, the word is skipped.
        if (len > maxLen) {
            continue;
        }

        // Checking if the word already exists in the wordLists.
        // If the word exists, its occurrence count is incremented.
        // If the word does not exist, it is added to the wordLists with a count of 1.
        LLNode *node = llLookupKey(wordLists[len], word);
        if (node) {
            node->value++;
        } else {
            node = llNewNode(strdup(word), 1);
            wordLists[len] = llAppend(wordLists[len], node);
        }
        
        // Incrementing the wordCount for each word read.
        wordCount++;
    }

    // Deleting the word extractor after processing all words.
    weDeleteExtractor(we);

    // Returning the total word count.
    return wordCount;
}

// The printData function is responsible for printing the tally of each word read from the file.
// It iterates through each word in the wordLists and prints the word alongside its occurrence count.
int printData(char *filename, LLNode **wordListHeads, int maxLen) {
    // Printing the filename as a header to the output.
    printf("Data from file '%s':\n", filename);

    // Iterating through each linked list in the wordListHeads array.
    for (int i = 0; i <= maxLen; i++) {
        // Initializing the current node to the head of the linked list.
        LLNode *current = wordListHeads[i];

        // Iterating through each node in the linked list and printing the word and its occurrence count.
        while (current) {
            printf("%s: %d\n", current->key, current->value);
            current = current->next;
        }
    }

    return 0;
}

// The printHapax function prints words that appear only once (hapax legomenon) in the file.
// It can filter the words based on their lengths if hapaxLength is specified; otherwise, it prints all hapax legomena.
int printHapax(char *filename, LLNode **wordListHeads, int maxLen, int hapaxLength) {
    // Printing the filename as a header to the output.
    printf("Hapax legomena from file '%s':\n", filename);

    // Iterating through each linked list in the wordListHeads array.
    for (int i = 0; i <= maxLen; i++) {
        // If hapaxLength is specified, the function only prints words of that length.
        // Otherwise, it prints all words that are hapax legomena.
        if (hapaxLength == 0 || hapaxLength == i) {
            // Initializing the current node to the head of the linked list.
            LLNode *current = wordListHeads[i];

            // Iterating through each node in the linked list and printing the word if its occurrence count is 1.
            while (current) {
                if (current->value == 1) {
                    printf("%s\n", current->key);
                }
                current = current->next;
            }
        }
    }

    return 0;
}