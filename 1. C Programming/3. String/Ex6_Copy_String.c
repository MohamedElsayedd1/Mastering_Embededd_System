#include <stdio.h>

char* my_strcpy(char dest[], char src[]){
    char *pdest = dest;
    const char *psrc = src;
    while(*psrc != '\0'){
        *pdest++ = *psrc++;
    }
    *pdest = '\0';
    return dest;
}

int main(){
    char str1[100] = "Mohamed";
    char str2[100] = "Khaled";
    printf("Before copying : \n");
    printf("string 1 : %s\n", str1);
    printf("string 1 : %s\n", str1);
    
    my_strcpy(str1, str2);

    printf("\nAfter copying : \n");
    printf("string 1 : %s\n", str1);
    printf("string 1 : %s\n", str1);
    return 0;
}