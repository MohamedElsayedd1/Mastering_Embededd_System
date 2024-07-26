#include <stdio.h>
#include <string.h>


int main()
{

    int arr[100];
    int size;

    printf(" Input 5 number of elements in the array : ");
    scanf("%d", &size);

    for(int i = 0; i < size; i++){
        printf("element - %d :", i+1);
        scanf("%d", arr+i);
    }

    int *ptr = arr+size-1;

    printf("\n The elements of array in reverse order are : \n");

    for(int i = size; i > 0; i--){
        printf("element - %d : %d\n", i, *ptr--);
    }
    printf("\n");

    return 0;
}