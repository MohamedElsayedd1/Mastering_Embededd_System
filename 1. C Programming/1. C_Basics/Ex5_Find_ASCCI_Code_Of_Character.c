#include <stdio.h>
#include <stdlib.h>

int main(){

    char ch;
    printf("Enter a character : ");
    scanf("%c", &ch);
    printf("ASCII value of %c is : %d", ch, ch);
    return 0;
}