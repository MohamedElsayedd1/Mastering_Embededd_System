#include <stdio.h>
#include <stdlib.h>

int main()
{

    double n1, n2;
    char op;
    printf("Enter an operator(*,+,-,/,) : ");
    scanf("%c", &op);
    printf("Enter Number#1 : ");
    scanf("%lf", &n1);
    printf("Enter Number#2 : ");
    scanf("%lf", &n2);

    switch (op)
    {
    case '+':
        printf("%lf + %lf = %lf.\n", n1, n2, n1 + n2);
        break;
    case '-':
        printf("%lf - %lf = %lf.\n", n1, n2, n1 - n2);
        break;
    case '*':
        printf("%lf * %lf = %lf.\n", n1, n2, n1 * n2);
        break;
    case '/':
        printf("%lf / %lf = %lf.\n", n1, n2, n1 / n2);
        break;
    default:
        printf("Invalid Operator !.\n");
        break;
    }

    return 0;
}