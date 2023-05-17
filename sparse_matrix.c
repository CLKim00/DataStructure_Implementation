#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101   // maximum number of terms +1
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y) ? 0 : 1))
// SparseMatrix
// void Create(maxRow, maxCol){  
//     typedef struct{
//         int col;
//         int row;
//         int value;
//     } term;
//     term a[MAX_TERMS];
// }

int main(void) {
    term a[MAX_TERMS] = {
        {3, 3, 5}, {0, 0, 1}, {0, 1, 2}, {1, 0, 3}, {1, 2, 4}, {2, 2, 5}
    };
    term b[MAX_TERMS] = {
        {3, 3, 4}, {0, 0, 1}, {0, 2, 2}, {1, 1, 3}, {2, 1, 4}
    };
    term d[MAX_TERMS];

    multiplication(a, b, d);

    for (int i = 1; i <= d[0].value; i++) {
        printf("(%d, %d, %d)\n", d[i].row, d[i].col, d[i].value);
    }

    return 0;
}

typedef struct{
    int row;
    int col;
    int value;
} term;

void transpose(term a[], term b[]){
    int n, i, j, currentb;

    n = a[0].value;
    b[0].col = a[0].row;            // 
    b[0].row = a[0].col;            // 
    b[0].value = n;                 // 

    if (n > 0){
        currentb = 1;

        for (i = 0; i < a[0].col; i++){
            for (j = 1; j <= n; j++){
                if (a[j].col == i){
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}

void storeSum(term d[], int *totalD, int row, int column, int *sum){
    if (*sum)
        if (*totalD < MAX_TERMS){
            d[++*totalD].row = row;
            d[*totalD].col = column;
            d[*totalD].value = *sum;
            *sum = 0;
        }
        else {
            fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
            exit(EXIT_FAILURE);
        }
}

void multiplication(term a[], term b[], term d[]){
    int i, j, column, totalB = b[0].value, totalD = 0;
    int rowsA = a[0].row, colsA = a[0].col, totalA = a[0].value;
    int colsB = b[0].col;
    int rowBegin = 1, row = a[1].row, sum = 0;
    term newB[MAX_TERMS];

    if (colsA != b[0].row){
        fprintf(stderr, "Incompatible matrices\n");
        exit(EXIT_FAILURE);                         // stdlib.h 와 같이 쓰임
    }

    transpose(b, newB);

    a[totalA+1].row = rowsA;
    
    newB[totalB+1].row = colsB;
    newB[totalB+1].col = 0;

    for (i = 1; i <= totalA; ){
        column = newB[1].row;
        for (j = 1; j <= totalB+1; ){
            if (a[i].row != row){
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                for ( ; newB[j].row == column; j++)
                    ;
                column = newB[j].row;
            }
            else if (newB[j].row != column){
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                column = newB[j].row;
            }
            else switch (COMPARE (a[i].col, newB[j].col)){
                case -1:
                    i++;    
                    break;
                case 0:
                    sum += (a[i++].value * newB[j++].value);
                    break;
                case 1:
                    j++;
            }
        }
        for ( ; a[i].row == row; i++)
            ;
        rowBegin = i;
        row = a[i].row;
    }
    d[0].row = rowsA;
    d[0].col = colsB;
    d[0].value = totalD;
}

