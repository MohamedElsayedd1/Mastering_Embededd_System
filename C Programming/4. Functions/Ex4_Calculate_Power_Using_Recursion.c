#include <stdio.h>
#include <math.h>
#include <string.h>

long long int GetPower(int base, int pow)
{
    if (pow == 1)
        return base;

    return base * GetPower(base, --pow);
}

int main()
{
    int n, power;
    printf("Enter base numbber : ");
    scanf("%d", &n);
    printf("Enter power number : ");
    scanf("%d", &power);

    printf("\n%d ^ %d = %ld\n\n", n, power, GetPower(n, power));

    return 0;
}