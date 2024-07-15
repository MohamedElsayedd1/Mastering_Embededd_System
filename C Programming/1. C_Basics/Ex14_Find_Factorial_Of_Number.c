#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n;
    printf("Enter a number : ");
    scanf("%d", &n);
    if(n < 0){
        printf("Error!!! Factorial of negative number doesn't exist.\n");
        return 0;
    }
    int fact = 1;
    for(int i = 1; i <= n; i++){
        fact *= i;
    }
    printf("Factorial = %d\n", fact);

    return 0;
}