#include <stdio.h>
#include <math.h>

int getFactorial(int num){
    if(num <= 1)
        return 1;
    return num * getFactorial(num-1);
}

int main()
{
    unsigned int num;
    printf("Enter a positive number : ");
    scanf("%d", &num);
    
    printf("Factorial of %d = %ld", num, getFactorial(num));

    return 0;
}