/*
 * main.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Mohamed Elsayed
 */

#include "student.h"


int main() {
	char choice[3];
	const char FileName[] = "data.txt";

	while(1){
		DPRINTF("\nStudent Database Menu:\n");
		DPRINTF("1. Add Student Manually\n");
		DPRINTF("2. Add Student From Text File\n");
		DPRINTF("3. Search Student by ID\n");
		DPRINTF("4. Search Student by First Name\n");
		DPRINTF("5. Search Student by Course ID\n");
		DPRINTF("6. Get Number Of Students\n");
		DPRINTF("7. Delete Student by ID\n");
		DPRINTF("8. Update Student By ID\n");
		DPRINTF("9. Display All Students\n");
		DPRINTF("10. Exit\n");
		DPRINTF("Enter your choice: ");
		gets(choice);

		switch(atoi(choice)){
			case 1:
				AddStudentsManually();
				break;

			case 2:
				AddStudentsFromTextFile(FileName);
				break;

			case 3 :
				int id;
				DPRINTF("Enter Student ID : ");
				scanf("%d", &id);
				clearBuffer();
				SearchStudentByID(id);
				break;

			case 4:
				char FirstName[50];
				DPRINTF("Enter Student First Name : ");
				scanf("%s", FirstName);
				clearBuffer();
				SearchStudentByFirstName(FirstName);
				break;

			case 5:
				int courseID;
				DPRINTF("Enter Student Course ID : ");
				scanf("%d", &courseID);
				clearBuffer();
				SearchStudentByCourseID(courseID);

				break;

			case 6:
				int NumberOfStudents = GetNumberOfStudents();
				DPRINTF("\nNumber of students : %d\n", NumberOfStudents);
				break;

			case 7:
				int deletedID;
				DPRINTF("Enter Student ID : ");
				scanf("%d", &deletedID);
				clearBuffer();
				DeleteStudentById(deletedID);
				break;

			case 8:
				int updatedID;
				DPRINTF("Enter Student ID : ");
				scanf("%d", &updatedID);
				clearBuffer();
				UpdateStudentById(updatedID);
				break;

			case 9:
				DisplayStudents();
				break;

			case 10:
				// Exit the program
				DPRINTF("Exiting the program.\n");
				return 0;
				break;

		}
	}

    return 0;
}

