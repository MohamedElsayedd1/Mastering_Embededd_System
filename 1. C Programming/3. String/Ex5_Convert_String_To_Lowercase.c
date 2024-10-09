#include <stdio.h>

int main(){
    char str[100];
    printf("Enter string : ");
    gets(str);
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] += 32;
        }
        i++;
    }
    printf("Lowercase string : %s\n", str);
    return 0;
}