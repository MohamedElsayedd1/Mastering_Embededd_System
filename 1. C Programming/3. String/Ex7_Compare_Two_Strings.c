#include <stdio.h>
#include <string.h>

int my_strcmp(char s1[], char s2[]){
    int size = ((strlen(s1) < strlen(s2)) ? strlen(s1) : strlen(s2));
    for(int i = 0; i < size; i++){
        if(s1[i] > s2[i]){
            return 1;
            break;
        }
        else if(s1[i] < s2[i]){
            return -1;
            break;
        }
    }
    return 0;
}



int main(){
    char str1[100];
    char str2[100];
    printf("Enter string 1 : ");
    gets(str1);
    printf("Enter string 2 : ");
    gets(str2);

    int is_equal = my_strcmp(str1, str2);

    if(!is_equal){
        printf("Two string are equal.\n");
    }
    else if(is_equal == 1){
        printf("string 1 is bigger.\n");
    }
    else{
        printf("string 2 is bigger.\n");
    }
    


    return 0;
}