#include <stdio.h>
#include <string.h>

void reverseString(char str[])
{
    char *left = str;
    char *right = str + strlen(str) - 2;
    while (left < right)
    {
        char temp = (*left);
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

int main()
{

    char s[100];
    printf("Input a string : ");
    fgets(s, 100, stdin);
    reverseString(s);
    printf("Reverse of the string is : %s\n\n", s);

    return 0;
}