/*
 * student.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Dubai Store
 */


#include "student.h"

static student_t std[STUDENTS_MAX_SIZE];
static int stdCount = 0;

// Function to clear input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Discard characters until newline or end-of-file
}


void AddStudentsManually(void) {
    int id;

    // Ensure we don't exceed the maximum number of students
    if (stdCount >= STUDENTS_MAX_SIZE) {
        DPRINTF("Can't add more students, limit reached.\n");
        return;
    }

    DPRINTF("Enter student id: ");
    scanf("%d", &id);
    clearBuffer();


    // Check if this ID is already taken
    if (IsStudentIDExist(id) >= 0) {
        DPRINTF("Can't add student, ID %d is already taken.\n", id);
        return;
    } else {
        std[stdCount].id = id;
    }

    DPRINTF("Enter student first name: ");
    fgets(std[stdCount].fName, sizeof(std[stdCount].fName), stdin);
    std[stdCount].fName[strcspn(std[stdCount].fName, "\n")] = '\0'; // Remove newline

    DPRINTF("Enter student last name: ");
    fgets(std[stdCount].lName, sizeof(std[stdCount].lName), stdin);
    std[stdCount].lName[strcspn(std[stdCount].lName, "\n")] = '\0'; // Remove newline

    DPRINTF("Enter student GPA: ");
    scanf("%f", &std[stdCount].gpa);
    getchar();  // Clear the newline from input buffer

    for (int i = 0; i < COURSES_MAX_SIZE; i++) {
        DPRINTF("Enter course %d ID: ", i + 1);
        scanf("%d", &std[stdCount].courseId[i]);
        getchar();  // Clear the newline from input buffer
    }

    DPRINTF("Student with ID (%d) has been added successfully!\n", std[stdCount].id);
    stdCount++;
}

void AddStudentsFromTextFile(char fileName[]){
	// Ensure we don't exceed the maximum number of students
	if (stdCount >= STUDENTS_MAX_SIZE) {
		DPRINTF("Can't add more students, limit reached.\n");
		return;
	}

	FILE *file = fopen(fileName, "r");
	if(file == NULL){
		printf("Error opening file!\n");
		return;
	}

	char line[100]; // buffer to store each line

	while(fgets(line, sizeof(line), file)){
		int id;
		char fname[50], lname[50];
		float gpa;
		int csid[5];
		int ret = sscanf(line, "%d %s %s %f %d %d %d %d %d", &id, fname, lname, &gpa, 
		&csid[0], &csid[1], &csid[2], &csid[3], &csid[4]);
		// Check if this ID is already taken
		if (IsStudentIDExist(id) >= 0) {
			DPRINTF("Can't add student, ID (%d) is already taken.\n", id);
			continue; // skip this student
		} else {
			std[stdCount].id = id;
			strcpy(std[stdCount].fName, fname);
			strcpy(std[stdCount].lName, lname);
			std[stdCount].gpa = gpa;
			for (int i = 0; i < COURSES_MAX_SIZE; i++) {
				std[stdCount].courseId[i] = csid[i];
			}
			DPRINTF("Student with ID (%d) has been added successfully!\n", std[stdCount].id);
			stdCount++;
		}
	}
	fclose(file); // Close the file after reading
}

int IsStudentIDExist(int id) {
    for (int i = 0; i < stdCount; i++) {
        if (std[i].id == id) {
            return i;  // Student with this ID exists
        }
    }
    return -1;  // No student found with this ID
}

void DisplayStudents(void){
	DPRINTF("\n--------------Students DataBase-------------\n");
	if(!stdCount){
		DPRINTF("DataBase is empty, No students have been added!\n");
	}
	for(int i = 0; i < stdCount; i++){
		DPRINTF("Student %d :\n", i+1);
		DPRINTF("\t Student ID : %d\n", std[i].id);
		DPRINTF("\t Student First Name : %s\n", std[i].fName);
		DPRINTF("\t Student Last Name : %s\n", std[i].lName);
		DPRINTF("\t Student GPA: %.2f\n", std[i].gpa);
		DPRINTF("\t Student Registered Courses IDs: %d %d %d %d %d\n", std[i].courseId[0],
																	std[i].courseId[1],
																	std[i].courseId[2],
																	std[i].courseId[3],
																	std[i].courseId[4]);
	}
	DPRINTF("---------------------------------------------\n\n");
}

void SearchStudentByID(int id){
	int stdIndex = IsStudentIDExist(id);
	if(stdIndex >= 0){
		DPRINTF("\nStudent with ID (%d) is found : \n", id);
		DPRINTF("\t Student ID : %d\n", std[stdIndex].id);
		DPRINTF("\t Student First Name : %s\n", std[stdIndex].fName);
		DPRINTF("\t Student Last Name : %s\n", std[stdIndex].lName);
		DPRINTF("\t Student GPA: %.2f\n", std[stdIndex].gpa);
		DPRINTF("\t Student Registered Courses IDs: %d %d %d %d %d\n", std[stdIndex].courseId[0],
																	std[stdIndex].courseId[1],
																	std[stdIndex].courseId[2],
																	std[stdIndex].courseId[3],
																	std[stdIndex].courseId[4]);
	}
	else{
		DPRINTF("\nStudent with ID (%d) is not found.\n", id);
	}
}

void ToLowerCase(char *s){
	while(*s != '\0'){
		*s = tolower(*s);
		s++;
	}
}

void SearchStudentByFirstName(char fname[]){
	int found = 0;
	char SearchName[50];
	strcpy(SearchName, fname);
	ToLowerCase(SearchName); // Convert search string to lower case

	for(int i = 0; i < stdCount; i++){
		char StudentName[50];
		strcpy(StudentName, std[i].fName);
		ToLowerCase(StudentName); // Convert student string to lower case
		if(strcmp(StudentName, SearchName) == 0){
			DPRINTF("\n\t Student ID : %d\n", std[i].id);
			DPRINTF("\t Student First Name : %s\n", std[i].fName);
			DPRINTF("\t Student Last Name : %s\n", std[i].lName);
			DPRINTF("\t Student GPA: %.2f\n", std[i].gpa);
			DPRINTF("\t Student Registered Courses IDs: %d %d %d %d %d\n", std[i].courseId[0],
																		std[i].courseId[1],
																		std[i].courseId[2],
																		std[i].courseId[3],
																		std[i].courseId[4]);
			found = 1;
		}
	}
	if(!found){
		DPRINTF("\nStudent with First Name \"%s\" is not found.\n", fname);
	}
}

void SearchStudentByCourseID(int cId) {
    int found = 0;
    for (int i = 0; i < stdCount; i++) {
        // Check each course ID for the student
        for (int j = 0; j < COURSES_MAX_SIZE; j++) {
            if (cId == std[i].courseId[j]) {
                // Print student details if course ID matches
                DPRINTF("\n\t Student ID : %d\n", std[i].id);
                DPRINTF("\t Student First Name : %s\n", std[i].fName);
                DPRINTF("\t Student Last Name : %s\n", std[i].lName);
                DPRINTF("\t Student GPA: %.2f\n", std[i].gpa);
                DPRINTF("\t Student Registered Courses IDs:");
                for (int k = 0; k < COURSES_MAX_SIZE; k++) {
                    if (std[i].courseId[k] != 0) { // Check if course ID is valid
                        DPRINTF(" %d", std[i].courseId[k]);
                    }
                }
                DPRINTF("\n");
                found = 1; // Mark that we found at least one student
                break; // Break out of inner loop to check next student
            }
        }
    }
    if (!found) {
        DPRINTF("\nStudent with Course ID \"%d\" is not found.\n", cId);
    }
}

int GetNumberOfStudents(void){
	return stdCount;
}

void DeleteStudentById(int id){
	int stdIndex = IsStudentIDExist(id);
	if(stdIndex >= 0){
		// Shift all student to right
		for(int i = stdIndex; i < stdCount-1; i++){
			std[i] = std[i+1];
		}
		stdCount--;
		DPRINTF("\nStudent with ID (%d) is deleted \n", std[stdIndex].id);
	}
	else{
		DPRINTF("\nStudent with ID (%d) is not found.\n", id);
	}
}

void UpdateStudentById(int id){
	int stdIndex = IsStudentIDExist(id);
	if(stdIndex >= 0){
		int choice;
		DPRINTF("1. First Name \n");
		DPRINTF("2. Last Name \n");
		DPRINTF("3. ID \n");
		DPRINTF("4. GPA \n");
		DPRINTF("5. Courses \n");
		DPRINTF("What do you want to update ? ");
		scanf("%d", &choice);
		clearBuffer();
		switch(choice){
			case 1 :
				char fname[50];
				DPRINTF("Enter student first name: ");
				scanf("%s", fname);
				clearBuffer();
				strcpy(std[stdIndex].fName, fname);
				DPRINTF("\nFirst name of student with ID (%d) has been updated.\n", std[stdIndex].id);
			break;

			case 2:
				char lname[50];
				DPRINTF("Enter student last name: ");
				scanf("%s", lname);
				clearBuffer();
				strcpy(std[stdIndex].lName, lname);
				DPRINTF("\nLast name of student with ID (%d) has been updated.\n", std[stdIndex].id);
			break;

			case 3:
				int newID;
				DPRINTF("Enter student new ID: ");
				scanf("%d", &newID);
				clearBuffer();
				std[stdIndex].id = newID;
				DPRINTF("\nStudent with ID (%d) has been updated to ID (%d).\n", newID, std[stdIndex].id);
			break;

			case 4:
				float newGpa;
				DPRINTF("Enter student GPA: ");
				scanf("%f", &newGpa);
				clearBuffer();
				std[stdIndex].gpa = newGpa;
				DPRINTF("\nGPA of student with ID (%d) has been updated.\n", std[stdIndex].id);
			break;

			case 5:
				for (int i = 0; i < COURSES_MAX_SIZE; i++) {
					DPRINTF("Enter course %d ID: ", i + 1);
					scanf("%d", &std[stdIndex].courseId[i]);
					clearBuffer();  // Clear the newline from input buffer
				}
			break;

			default:
				DPRINTF("\nWrong input, Please enter valid choice.\n", std[stdIndex].id);
			break;
		}
	}
	else{
		DPRINTF("\nStudent with ID (%d) is not found.\n", id);
	}
}
