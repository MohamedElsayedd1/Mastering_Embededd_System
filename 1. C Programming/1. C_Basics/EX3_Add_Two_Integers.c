#include <stdio.h>
#include <stdlib.h>

int main(){

    int num1, num2;
    printf("Enter 2 numbers : ");
    scanf("%d %d", &num1, &num2);
    int sum = num1 + num2;
    printf("Sum : %d\n", sum);
    return 0;
}