#include <stdio.h>

int main(){
    char str[100];
    char ch;
    int freq = 0;
    printf("Enter string : ");
    gets(str);
    printf("Enter character to find frequency : ");
    scanf("%c", &ch);
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == ch){
            freq++;
        }
        i++;
    }
    printf("Frequency of %c = %d\n", ch, freq);
    return 0;
}