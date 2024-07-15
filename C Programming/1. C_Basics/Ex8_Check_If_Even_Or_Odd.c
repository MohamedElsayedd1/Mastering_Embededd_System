#include <stdio.h>
#include <stdlib.h>

int main(){

    int num;
    printf("Enter a number to check : ");
    scanf("%d", &num);
    if(num % 2){
        printf("%d is odd.\n", num);
    }
    else{
        printf("%d is even.\n", num);
    }

    return 0;
}