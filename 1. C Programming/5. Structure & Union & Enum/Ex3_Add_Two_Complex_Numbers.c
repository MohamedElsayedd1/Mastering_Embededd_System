#include <stdio.h>
#include <string.h>

struct Complex {
    float real;
    float img;
};

int main() {
    struct Complex A, B, C;

    printf("\nEnter 1st Complex number (x+iy): ");
    scanf("%f+i%f", &A.real, &A.img);
    printf("\nEnter 2nd Complex number (x+iy): ");
    scanf("%f+i%f", &B.real, &B.img);

    C.real = A.real + B.real;
    C.img = A.img + B.img;

    printf("\nSum = %.2f + i%.2f\n", C.real, C.img);
    return 0;
}
