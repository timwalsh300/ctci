#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void print_matrix(int **m, int x, int y)
{
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int main(void)
{
    unsigned char buffer[1];
    int fd = open("/dev/urandom", O_RDONLY);

    // initialize matrix with random input
    read(fd, buffer, 1);
    int rows = (((int) *buffer) % 32) + 2;
    read(fd, buffer, 1);
    int columns = (((int) *buffer) % 32) + 2;
    int **matrix;
    matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(columns * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // assign 0 with probability 0.1
            read(fd, buffer, 1);
            int val = ((int) *buffer) % 10;
            if (val == 0) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = 1;
            }
        }
    }

    printf("input matrix...\n\n");
    print_matrix(matrix, rows, columns);

    // analyze the input
    int zero_rows[rows];
    memset(zero_rows, 0, rows * 4);
    int zero_cols[columns];
    memset(zero_cols, 0, columns * 4);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                zero_rows[i] = 1;
                zero_cols[j] = 1;
            }
        }
    }

    // modify the input to produce output
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (zero_rows[i]) {
                memset(matrix[i], 0, columns * 4);
                break;
            } else if (zero_cols[j]) {
                matrix[i][j] = 0;
            } else {
                // leave this value as-is
                continue;
            }
        }
    }


    printf("output matrix...\n\n");
    print_matrix(matrix, rows, columns);

}
