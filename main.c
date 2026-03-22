#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **CreateMatr(size_t row, size_t column)
{
    int **dmas = (int **)calloc(row, sizeof(int *)); //массив указателей(int*)
    if (dmas == NULL){
        return NULL;
    }


    for (size_t i = 0; i < row; i++) {
        dmas[i] = (int *)calloc(column, sizeof(int));
        if (dmas[i] == NULL){
            for (size_t u = 0; u < i; u++) free(dmas[u]);
            free(dmas);
            return NULL;
        }
    }
    return dmas;
}

void GenerateRandomMatr(int **Matr, size_t row, size_t column, int min, int max)
{
    if (Matr == NULL) return;

    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }

    int range = max - min + 1;

    for (size_t i = 0; i < row; i++) {
        if (Matr[i] != NULL)
        for (size_t j = 0; j < column; j++) {
            Matr[i][j] = rand() % range + min;
        }
    }
}

void PrintMatr(int **Matr, size_t row, size_t column)
{
    for (size_t ix = 0; ix < row; ix++) {
        if (Matr[ix]) {
            for (size_t jx = 0; jx < column; jx++) {
                printf("%4d ", Matr[ix][jx]);
            }
        } else {
            printf("NULL");
        }
        printf("\n");
    }
}

void FreeMatr(int ***Matr, size_t rows) {
    if (Matr == NULL || *Matr == NULL) return;

    for (size_t i = 0; i < rows; i++) {
        free((*Matr)[i]);
    }
    free(*Matr);
    *Matr = NULL;
}

int main()
{
    int **Matr = NULL;

    Matr = CreateMatr(3, 3);
    srand(time(0));
    GenerateRandomMatr(Matr, 3, 3, 1, 10);
    PrintMatr(Matr, 3, 3);
    FreeMatr(&Matr, 3);
    return 0;
}
