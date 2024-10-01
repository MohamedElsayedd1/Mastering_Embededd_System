/*
 * main.c
 *
 *  Created on: Sep 30, 2024
 *      Author: Mohamed Elsayed
 */

#include "StudentDataBase.h"


int main(){
	char choice[5];
	student_t *student_db = NULL;

	while(1){
		DPRINTF("\nStudent Database Menu:\n");
		DPRINTF("1. Add Student At Beginning\n");
		DPRINTF("2. Add Student At End\n");
		DPRINTF("3. Display All Students\n");
		DPRINTF("4. Search Student by ID\n");
		DPRINTF("5. Get Number Of Students\n");
		DPRINTF("6. Get The Nth Student From The Beginning\n");
		DPRINTF("7. Get The Nth Student From The End\n");
		DPRINTF("8. Get The Middle Student Data\n");
		DPRINTF("9. Reverse The Student DataBase\n");
		DPRINTF("10. Swap Two Students By IDs\n");
		DPRINTF("11. Sort The Student DataBase By ID\n");
		DPRINTF("12. Delete Student by ID\n");
		DPRINTF("13. Delete All Student\n");
		DPRINTF("14. Exit\n");
		DPRINTF("Enter your choice: ");
		gets(choice);

		switch(atoi(choice)){
			case 1:
				AddStudentAtBeginning(&student_db);
				DPRINTF("Student added successfully!\n");

				break;
			case 2:
				// Adding student to the linked list database
				AddStudentAtEnd(&student_db);
				DPRINTF("Student added successfully!\n");
				break;

			case 3 :
				// Display all students
				DisplayStudents(student_db);

				break;
			case 4:
//				// Search for a student by ID
				student_t *found_student;
				int id;
				DPRINTF("Enter student ID to search: ");
				scanf("%d", &id);
				found_student = SearchStudent(student_db, id);
				if (found_student) {
					DPRINTF("Student found - ID: %d, Name: %s, GPA: %.2f\n", found_student->id, found_student->name, found_student->gpa);
				} else {
					DPRINTF("Student with ID %d not found.\n", id);
				}
				break;

			case 5:
				// Get the number of student in the database
				int numberOfStudents = GetLength(student_db);
				DPRINTF("Number Of Students : %d\n", numberOfStudents);
				break;

			case 6:
				// Get the Nth student from the beginning in the database
				GetNthStudentFromBeginning(student_db);
				break;

			case 7:
				// Get the Nth student from the end in database
				GetNthStudentFromEnd2(student_db);
				// GetNthStudentFromEnd1(student_db); // Another Method To Get Nth student from the end of DataBase
				break;

			case 8:
				// Get the Middle student from the database
				GetTheMiddleStudent2(student_db);
				//GetTheMiddleStudent1(student_db); // Another Method To Get The Middle Of The DataBase
				break;

			case 9:
				// Reverse The Linked List
				ReverseLinkedList(&student_db);
				break;

			case 10:
				// Swap 2 student in the database
				int id1, id2;
				DPRINTF("Enter The First Student's ID : ");
				scanf("%d", &id1);
				DPRINTF("Enter The Second Student's ID : ");
				scanf("%d", &id2);
				Swap2NodesByID(&student_db, id1, id2);
				break;

			case 11:
				// Sort All Students By ID
				SortNodesByID(&student_db);
				break;

			case 12:
				// Delete a student by ID
				DPRINTF("Enter student ID to delete: ");
				scanf("%d", &id);
				DeleteStudent(&student_db, id);
				break;

			case 13:
				// Delete All Students
				DeleteAllStudents(&student_db);
				break;

			case 14:
				// Exit the program
				DPRINTF("Exiting the program.\n");
				return 0;
				break;

		}
	}

	return 0;
}



