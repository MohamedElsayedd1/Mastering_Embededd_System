#include <stdio.h>

int main(){
    int row, column;
    printf("Enter rows and columns of a matrix : ");
    scanf("%d %d", &row, &column);
    int matrix[row][column];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("Enter element a(%d, %d) : ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
        }
    }
    int t_matrix[column][row];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            t_matrix[j][i] = matrix[i][j];
        }
    }
    // display original matrix
    printf("\nEntered matrix : \n");
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Transopse matrix : \n");
    // display transpose matrix
    for(int i = 0; i < column; i++){
        for(int j = 0; j < row; j++){
            printf("%d\t", t_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}