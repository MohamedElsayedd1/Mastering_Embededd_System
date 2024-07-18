#include <stdio.h>
#include <math.h>

void isPrime(int n1, int n2)
{
    if (n2 < 2) {
        printf("No prime numbers in this interval.\n");
        return;
    }
    if (n1 < 2) {
        n1 = 2;
    }
    for (int i = n1; i <= n2; i++)
    {
        int is_Prime = 1;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                is_Prime = 0;
                break;
            }
        }
        if (is_Prime)
            printf("%d ", i);
    }
}

int main()
{
    int interval1, interval2;
    printf("Enter two numbers (Two intervals) : ");
    scanf("%d %d", &interval1, &interval2);

    if (interval1 > interval2) {
        printf("The first number should be less than or equal to the second number.\n");
        return 1;
    }
    
    isPrime(interval1, interval2);
    return 0;
}