#include <stdio.h>

int main(){

    int m = 29;
    

    printf("Address of m : 0x%X\n", &m);
    printf("Value of m : %d\n\n", m);

    int *ab = &m;

    printf("Now ab is assigned with the address of m.\n");
    printf("Address of pointer ab : 0x%X\n", ab);
    printf("Content of pointer ab : %d\n\n", *ab);

    *ab = 34;

    printf("The value of m is now assigned to %d.\n", m);
    printf("Address of m : 0x%X\n", &m);
    printf("Value of m : %d\n\n", m);

    *ab = 7;

    printf("The value of m is now assigned to %d.\n", m);
    printf("Address of m : 0x%X\n", &m);
    printf("Value of m : %d\n\n", m);

    return 0;
}