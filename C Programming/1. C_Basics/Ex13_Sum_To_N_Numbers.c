#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n;
    printf("Enter a number : ");
    scanf("%d", &n);
    int sum = 0;
    for(int i = 1; i <= n; i++){
        sum += i;
    }
    printf("Sum = %d\n", sum);

    return 0;
}