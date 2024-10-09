#include <stdio.h>
#include <string.h>

struct Person
{
    char name[20];
    int id;
} emp1 = {"Ahmed", 22}, emp2 = {"Mohamed", 44}, emp3 = {"Salem", 11};

int main()
{
    struct Person *arr[] = {&emp1, &emp2, &emp3}; // Array of pointers to structure of type Person

    for (int i = 0; i < 3; i++)
    {
        printf("Employee Name : %s\n", arr[i]->name);
        printf("Employee Id : %d\n", arr[i]->id);
        printf("\n");
    }

    printf("------------------------------ \n\n");

    struct Person persons[] = {emp1, emp2, emp3};
    struct Person(*Person_ptr)[] = &persons; // Pointer to array of structures of type Person

    for (int i = 0; i < 3; i++)
    {
        printf("Employee Name : %s\n", (*Person_ptr)[i].name);
        printf("Employee Id : %d\n", (*Person_ptr)[i].id);
        printf("\n");
    }

    return 0;
}