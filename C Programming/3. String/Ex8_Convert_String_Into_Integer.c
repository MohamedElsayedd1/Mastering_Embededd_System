#include <stdio.h>
#include <string.h>

int my_atoi(char s[]){
    int num = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] >= '0' && s[i] <= '9'){
            num *= 10;
            num += (s[i] - 48);
        }
    }
    return num;
}



int main(){
    char str1[100];
    printf("Enter string : ");
    gets(str1);

    int number = my_atoi(str1);
    printf("%d\n", number);

    


    return 0;
}