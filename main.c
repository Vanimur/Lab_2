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
    if (Matr == NULL) return;
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

int **Matr_Combining(int **Matr_A, size_t row_A, size_t col_A, int **Matr_B, size_t row_B, size_t col_B)
{
    if (row_A != row_B || Matr_A == NULL || Matr_B == NULL) return NULL;

    size_t new_col = col_A + col_B;
    int **Result = CreateMatr(row_A, new_col);
    if (Result == NULL) return NULL;

    for (size_t i = 0; i < row_A; i++) {
        if (Matr_A[i] != NULL) {
            for (size_t j = 0; j < col_A; j++) {
                Result[i][j] = Matr_A[i][j];
            }
        }

        if (Matr_B[i] != NULL) {
            for (size_t j = 0; j < col_B; j++) {
                Result[i][col_A + j] = Matr_B[i][j];
            }
        }
    }
    return Result;
}

int main()
{
    size_t r1 = 3, c1 = 3;
    size_t r2 = 3, c2 = 3;

    //size_t r1 = 3, c1 = 2;
    //size_t r2 = 3, c2 = 3;

    //size_t r1 = 3, c1 = 3;
    //size_t r2 = 2, c2 = 3;

    //size_t r1 = 2, c1 = 3;
    //size_t r2 = 3, c2 = 2;

    int **A = CreateMatr(r1, c1);
    int **B = CreateMatr(r2, c2);

    srand(time(0));
    GenerateRandomMatr(A, r1, c1, 0, 1);
    GenerateRandomMatr(B, r2, c2, 0, 1);

    //GenerateRandomMatr(A, r1, c1, 0, 0);
    //GenerateRandomMatr(B, r2, c2, 0, 0);

    //free(A[1]); // разреженная матрица А
    //A[1] = NULL;

    //free(B[2]); // разреженная матрица B
    //B[2] = NULL;

    printf("A:\n");
    PrintMatr(A, r1, c1);
    printf("-------------------\n");
    printf("B:\n");
    PrintMatr(B, r2, c2);

    int **Res = Matr_Combining(A, r1, c1, B, r2, c2);
    //int **Res = Matr_Combining(NULL, r1, c1, B, r2, c2);
    //int **Res = Matr_Combining(A, r1, c1, NULL, r2, c2);

    //int **p;
    //int **Res = Matr_Combining(*p, r1, c1, NULL, r2, c2);

    if (Res) {
        printf("Result:\n");
        PrintMatr(Res, r1, c1 + c2);
        FreeMatr(&Res, r1);
    }

    //int **p;
    //int **C = Matr_Multiply(p, r1, c1, B, r2, c2);
    FreeMatr(&A, r1);
    FreeMatr(&B, r2);
    return 0;
}
