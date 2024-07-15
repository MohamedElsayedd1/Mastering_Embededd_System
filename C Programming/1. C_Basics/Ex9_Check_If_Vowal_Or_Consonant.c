#include <stdio.h>
#include <stdlib.h>

int main(){

    char ch;
    printf("Enter an alphabet : ");
    scanf("%c", &ch);
    if(ch == 'a' || ch == 'i' || ch == 'u' || ch == 'o' || ch == 'e'){
        printf("%c is a Vowal.\n", ch);
    }
    else{
        printf("%c is Consonant.\n", ch);
    }

    return 0;
}