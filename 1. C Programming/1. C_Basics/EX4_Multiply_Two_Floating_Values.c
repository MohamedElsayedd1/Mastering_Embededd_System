#include <stdio.h>
#include <stdlib.h>

int main(){

    float num1, num2;
    printf("Enter 2 numbers : ");
    scanf("%f %f", &num1, &num2);
    float mult = num1 * num2;
    printf("Product : %f\n", mult);
    return 0;
}