#include <stdio.h>
#include <stdlib.h>

int main(){

    int a, b;
    printf("Enter value of a : ");
    scanf("%d", &a);
    printf("Enter value of b : ");
    scanf("%d", &b);
    printf("\n");
    
    a = a ^ b;
    b = a ^ b; // b = a ^ b ^ b = a ^ 0 = a
    a = a ^ b; // a = a ^ b ^ a = b ^ 0 = b


    printf("After swapping using XOR, a = %d\n", a); 
    printf("After swapping using XOR, b = %d\n", b);
    printf("\n");

    a = a + b;
    b = a - b;
    a = a - b;

    printf("After swapping using (+,-), a = %d\n", a);
    printf("After swapping using (+,-), b = %d\n", b);
    return 0;
}