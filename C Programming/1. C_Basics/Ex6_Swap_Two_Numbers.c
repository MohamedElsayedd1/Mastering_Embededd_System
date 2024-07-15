#include <stdio.h>
#include <stdlib.h>

int main(){

    float a, b;
    printf("Enter value of a : ");
    scanf("%f", &a);
    printf("Enter value of b : ");
    scanf("%f", &b);
    printf("\n");
    
    float temp = a;
    a = b;
    b = temp;

    printf("After swapping, a = %.2f\n", a);
    printf("After swapping, b = %.2f\n", b);
    return 0;
}