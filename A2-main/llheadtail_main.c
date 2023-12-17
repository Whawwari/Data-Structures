#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "fasta.h"
#include "LLvNode.c"
#include "fasta_read.c"

int processFastaWithHeadTail(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    FASTArecord record;
    LLvNode *head = NULL;
    LLvNode *tail = NULL;

    while (1) {
        fastaInitializeRecord(&record);
        int status = fastaReadRecord(file, &record);
        if (status == 0) {  // Assuming 0 indicates EOF for fastaReadRecord
            break;
        } else if (status == -1) {  // Assuming -1 indicates an error
            fastaClearRecord(&record);
            fclose(file);
            return -1;
        }

        LLvNode *newNode = llNewNode(record.description, &record);  // Using description as the key for now
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;  // Directly append to the tail
            tail = newNode;        // Update the tail pointer
        }

        fastaClearRecord(&record);
    }

    fclose(file);

    // Counting nodes
    int count = 0;
    LLvNode *temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    printf("Read %d records from the FASTA file.\n", count);

    // Cleanup the linked list.
    while (head) {
        LLvNode *next = head->next;
        free(head);
        head = next;
    }

    return 0;
}

int main(int argc, char **argv) {
    int runs = 1;  // Default to 1 run
    char *filename;

    // Argument parsing
    if (argc == 4 && strcmp(argv[1], "-R") == 0) {
        runs = atoi(argv[2]);
        filename = argv[3];
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [-R runs] <FASTA file>\n", argv[0]);
        return 1;
    }

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (int i = 0; i < runs; i++) {
        int result = processFastaWithHeadTail(filename);
        if (result != 0) {
            fprintf(stderr, "Error processing FASTA file '%s'\n", filename);
            return 1;
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%.3f seconds taken for processing total\n", cpu_time_used);
    printf("On average: 0 minutes, %.3f second per run\n", cpu_time_used / runs);

    return 0;
}
//finish