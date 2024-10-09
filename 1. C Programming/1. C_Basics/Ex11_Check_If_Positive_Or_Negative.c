#include <stdio.h>
#include <stdlib.h>

int main()
{

    float num;
    printf("Enter a number : ");
    scanf("%f", &num);
    if (num > 0)
    {
        printf("%0.2f is Positive.\n", num);
    }
    else if (num < 0)
    {
        printf("%0.2f is Negative.\n", num);
    }
    else
    {
        printf("Yoe entered Zero.\n", num);
    }

    return 0;
}