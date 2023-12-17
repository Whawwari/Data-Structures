// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "word_tally.h"
// #include "word_extractor.h"
// #include "LLNode.h"

// // Defined the maximum length of a word
// #define MAX_WORD_LEN 24

// //function to show usage instructions 
// void usage() {
//     printf("Usage: hapax [<options>] <datafile> [ <datafile> ...]\n");
//     printf("Options:\n");
//     printf("-d : print out all data loaded before printing hapax legomena.\n");
//     printf("-h : this help.\n");
//     printf("-l <N> : only print hapax legomena of length <N>.\n");
// }

// int main(int argc, char **argv) {

// 	// Array of linked lists to store words of different lengths
//     LLNode *wordLists[MAX_WORD_LEN + 1] = {NULL};

//     int printAllData = 0;  // Flag to determine if all data should be printed
//     int hapaxLength = 0;   // Length of hapax to be printed
// 	int totalWordCount = 0;  // Total count of words

// 	// A for loop to loop through command line arguments
//     for (int i = 1; i < argc; i++) {
//         if (strcmp(argv[i], "-d") == 0) {
//             printAllData = 1;
//         } else if (strcmp(argv[i], "-h") == 0) {
//             usage();
//             return 0;
//         } else if (strcmp(argv[i], "-l") == 0) {
//             if (i + 1 < argc) {
//                 hapaxLength = atoi(argv[++i]);
//             }
//         } else {
//             char *filename = argv[i];
// 			printf("Processing file: %s\n", filename);
// 			// Tally words from the file and update the total word count
//             totalWordCount += tallyWordsInFile(filename, wordLists, MAX_WORD_LEN); 
//             printf("Total word count %d\n", totalWordCount); 
//             printf("Tally loaded\n");  
            
// 			 // If the -d command is set, print all data
//             if (printAllData) {
//                 printData(filename, wordLists, MAX_WORD_LEN);
//             }
// 			//print hapax legomena
//             printHapax(filename, wordLists, MAX_WORD_LEN, hapaxLength);
//         }
//     }
//     // Cleanup (free the linked lists)
//     for (int i = 0; i <= MAX_WORD_LEN; i++) {
//         llFree(wordLists[i], NULL, NULL);
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_tally.h"
#include "word_extractor.h"
#include "LLNode.h"

// The following constant represents the maximum permissible length of a word.
#define MAX_WORD_LEN 24

// The usage function displays instructions on how to utilize the program and its options to the user.
void usage() {
    // Displaying program usage instructions and available options.
    printf("Usage: hapax [<options>] <datafile> [ <datafile> ...]\n");
    printf("Options:\n");
    printf("-d : Print all loaded data before printing hapax legomena.\n");
    printf("-h : Display this help message.\n");
    printf("-l <N> : Only print hapax legomena of length <N>.\n");
}

int main(int argc, char **argv) {
    // Initializing an array of linked lists, each list corresponds to words of different lengths.
    LLNode *wordLists[MAX_WORD_LEN + 1] = {NULL};

    // Flags and counters initialization.
    int printAllData = 0; // Flag to check whether to print all data or not.
    int hapaxLength = 0;  // Specifies the length of the hapax legomena to be printed.
    int totalWordCount = 0; // Counter to hold the total number of words processed.

    // Looping over the command line arguments to parse options and filenames.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            // If -d option is provided, set the flag to print all data.
            printAllData = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            // If -h option is provided, display the usage instructions and terminate the program.
            usage();
            return 0;
        } else if (strcmp(argv[i], "-l") == 0) {
            // If -l option is provided, parse the next argument as the hapax legomena length.
            if (i + 1 < argc) {
                hapaxLength = atoi(argv[++i]);
            }
        } else {
            // If the argument is not an option, it's treated as a filename.
            char *filename = argv[i];
            printf("Processing file: %s\n", filename);

            // Tallying words from the file, updating the total word count, and displaying the processed information.
            totalWordCount += tallyWordsInFile(filename, wordLists, MAX_WORD_LEN);
            printf("Total word count %d\n", totalWordCount);
            printf("Tally loaded\n");

            // Depending on the flag, either print all data or only the hapax legomena.
            if (printAllData) {
                printData(filename, wordLists, MAX_WORD_LEN);
            }
            printHapax(filename, wordLists, MAX_WORD_LEN, hapaxLength);
        }
    }

    // Once all files are processed and relevant data is printed, freeing the linked lists.
    for (int i = 0; i <= MAX_WORD_LEN; i++) {
        llFree(wordLists[i], NULL, NULL);
    }

    return 0; // Signifying successful execution of the program.
}