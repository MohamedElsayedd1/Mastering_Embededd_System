#include <stdio.h>

int main(){
    char str[100];
    printf("Enter string : ");
    gets(str);
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 32;
        }
        i++;
    }
    printf("Uppercase string : %s", str);
    return 0;
}
