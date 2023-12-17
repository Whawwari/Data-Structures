#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void printLineLeader(int lineNumber)
{
    printf("\n%4d >:", lineNumber);
    fflush(stdout);
}

static int convertLinesInFile(char *filename)
{
    FILE *ifp;
    int c, lineNumber = 0, isInEscape = 0;

    ifp = fopen(filename, "r");
    if (ifp == NULL) {
        fprintf(stderr, "Error: cannot open '%s' : %s\n", filename, strerror(errno));
        return -1;
    }

    printLineLeader(++lineNumber);

    while ((c = getc(ifp)) != EOF) {
        if (isInEscape) {
            switch (c) {
                case 'n':
                    putc('\n', stdout);
                    break;
                case 't':
                    putc('\t', stdout);
                    break;
                case '\'':
                    putc('\'', stdout);
                    break;
                case '\\':
                    putc('\\', stdout);
                    break;
                case '\n':
                    break;
                default:
                    putc(c, stdout);
            }
            isInEscape = 0;
        } else {
            if (c == '\\') {
                isInEscape = 1;
            } else if (c == '\n') {
                printLineLeader(++lineNumber);
            } else {
                putc(c, stdout);
            }
        }
    }

    printf("\n\nDONE\n");
    fclose(ifp);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Error: Please provide a file name as a command-line argument.\n");
        return -1;
    }

    int i;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            fprintf(stderr, "Error: unknown flag '%s'\n", argv[i]);
            return -1;
        } else if (convertLinesInFile(argv[i]) < 0) {
            fprintf(stderr, "Error: conversion of '%s' failed\n", argv[i]);
            return -1;
        }
    }
    return 0;
}
