#include <stdio.h>
#include <string.h>


int main()
{

    char ch = 65;
    char *ptr = &ch;

    int i = 26;
    while(i--){
        printf("%c ", (*ptr)++);
    }
    printf("\n");

    return 0;
}