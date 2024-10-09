#include <stdio.h>

int main(){
    int n;
    int arr[100];
    int num;
    int pos;
    printf("Enter number of elements : ");
    scanf("%d", &n);
    printf("Enter elements : ");
    for(int i = 0; i < n ; i++){
        scanf("%d", &arr[i]);
    }

    printf("Enter the number you want to insert : ");
    scanf("%d", &num);
    printf("Enter the postion you want to insert in, between (1->%d) : ", n);
    scanf("%d", &pos);

    for(int i = n; i > pos-1; i--){
        arr[i] = arr[i-1]; // shift array after position to the right 
    }

    arr[pos-1] = num;
    n++; // now the array increased by one

    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }



    return 0;
}