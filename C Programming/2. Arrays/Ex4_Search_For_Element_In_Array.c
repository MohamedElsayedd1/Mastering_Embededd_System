#include <stdio.h>

int main()
{
    int n;
    int arr[100];
    int num;
    printf("Enter number of elements : ");
    scanf("%d", &n);
    printf("Enter elements : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number you want to search for : ");
    scanf("%d", &num);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == num)
        {
            printf("Number found at location : %d\n", i + 1);
            return 0;
        }
    }

    printf("Number is not found !.\n");

    return 0;
}