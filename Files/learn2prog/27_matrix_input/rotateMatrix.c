#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 12

void rotate(char matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - i; j++) {
            char t = matrix[i][j];
            matrix[i][j] = matrix[10 - j - 1][10 - i - 1];
            matrix[10 - j - 1][10 - i - 1] = t;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            char t = matrix[i][j];
            matrix[i][j] = matrix[10 - i - 1][j];
            matrix[10 - i - 1][j] = t;
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
        return EXIT_FAILURE;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Could not open file.");
        return EXIT_FAILURE;
    }

    char matrix[10][10];
    char line[LINE_SIZE];
    int nlines = 0;

    while (fgets(line, LINE_SIZE, f) != NULL) {
        if (nlines >= 10) {
            fprintf(stderr, "Too many lines!\n");
            return EXIT_FAILURE;
        }
        if (strchr(line, '\n') == NULL) {
            fprintf(stderr, "Line is too long!\n");
            return EXIT_FAILURE;
        }
        if (strchr(line, '\n') - line != 10) {
            fprintf(stderr, "Line is too short!\n");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < 10; i++) {
            if (line[i] == '\n') {
                fprintf(stderr, "Line is too short!\n");
                return EXIT_FAILURE;
            }
            matrix[nlines][i] = line[i];
        }
        nlines++;
    }
    if (nlines != 10) {
        fprintf(stderr, "No enough number of lines!\n");
        return EXIT_FAILURE;
    }

    fclose(f);

    rotate(matrix);

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
