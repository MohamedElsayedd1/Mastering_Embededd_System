#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int rollno;
    float marks;
};

struct Student AddStudent(int count) {
    struct Student std;
    printf("Enter student %d name: ", count);
    fgets(std.name, 50, stdin);
    std.name[strcspn(std.name, "\n")] = 0; // Remove trailing newline
    printf("Enter student %d roll number: ", count);
    scanf("%d", &std.rollno);
    printf("Enter student %d mark: ", count);
    scanf("%f", &std.marks);
    while (getchar() != '\n'); // Clear the buffer
    return std;
}

void PrintStudents(int count, struct Student std) {
    printf("Student %d name: %s\n", count, std.name);
    printf("Student %d roll number: %d\n", count, std.rollno);
    printf("Student %d marks: %.2f\n", count, std.marks);
    printf("\n");
}

void SortStudent(struct Student stds[]){ // pass by ref
    for(int i = 0; i < 2; i++){
        for(int j = i+1; j < 2; j++){
            if(stds[j].rollno < stds[i].rollno){
                struct Student temp = stds[i];
                stds[i] = stds[j];
                stds[j] = temp;
            }
        }
    }
}

int main() {
    struct Student students[2];

    printf("\nEnter 5 students' info:\n\n");

    for (int i = 0; i < 2; i++) {
        students[i] = AddStudent(i + 1);
        printf("\n");
    }

    printf("============================\n");
    printf("\nStudents : \n\n");
    for (int i = 0; i < 2; i++) {
        PrintStudents(i + 1, students[i]);
        printf("\n");
    }

    printf("============================\n");
    SortStudent(students);
    printf("\nSorted Studens : \n\n");
    for (int i = 0; i < 2; i++) {
        PrintStudents(i + 1, students[i]);
        
    }

    return 0;
}
