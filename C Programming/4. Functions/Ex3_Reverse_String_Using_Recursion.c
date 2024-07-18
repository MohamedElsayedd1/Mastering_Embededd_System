#include <stdio.h>
#include <math.h>
#include <string.h>

void reverseString(char str[], int start, int end){
    if(start >= end)
        return;
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverseString(str ,++start, --end);
}

int main()
{
    char s[1000];
    printf("Enter a sentence : ");
    gets(s);
    
    reverseString(s, 0, strlen(s)-1);

    printf("Reversed string : %s\n\n", s);
    

    return 0;
}