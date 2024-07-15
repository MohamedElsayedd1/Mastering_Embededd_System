#include <stdio.h>
#include <stdlib.h>

int main(){

    float a, b, c;
    printf("Enter 3 numbers : ");
    scanf("%f %f %f", &a, &b, &c);
    if(a > b){
        if(a > c)
            printf("%f is the largest.\n", a);
        else
            printf("%f is the largest.\n", c);
    }
    else{
        if(b > c)
          printf("%f is the largest.\n", b);
        else
            printf("%f is the largest.\n", c);  
    }

    return 0;
}