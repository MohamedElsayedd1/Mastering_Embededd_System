/*
 * student.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STUDENTS_MAX_SIZE 50
#define COURSES_MAX_SIZE  5
#define DPRINTF(...)   { fflush(stdin); fflush(stdout); \
							printf(__VA_ARGS__); \
								fflush(stdin); fflush(stdout); }

typedef struct{
	char fName[50];
	char lName[50];
	int id;
	int courseId[COURSES_MAX_SIZE];
	float gpa;
}student_t;

/**
 * @brief Clears the input buffer.
 *
 * This function is used to flush the input buffer to prevent unwanted characters
 * from being read in future input operations.
 */
void clearBuffer();

/**
 * @brief Adds students manually to the student records.
 *
 * This function prompts the user to input student details manually, including
 * ID, first name, last name, GPA, and course IDs. The function ensures that
 * the maximum student limit is not exceeded and that the ID is unique before
 * adding the student.
 */
void AddStudentsManually(void);

/**
 * @brief Adds students from a text file to the student records.
 *
 * This function reads student details from a specified text file and adds them
 * to the student records. It checks for duplicate IDs and ensures the maximum
 * student limit is not exceeded.
 *
 * @param fileName The name of the text file containing student details.
 */
void AddStudentsFromTextFile(char fileName[]);

/**
 * @brief Checks if a student ID already exists in the records.
 *
 * This function searches through the student records to determine if a given
 * student ID is already present.
 *
 * @param id The student ID to check.
 * @return Returns 1 if the ID exists, 0 otherwise.
 */
int IsStudentIDExist(int id);

/**
 * @brief Displays all students' details.
 *
 * This function prints the details of all students in the records, including
 * ID, first name, last name, GPA, and registered course IDs.
 */
void DisplayStudents(void);

/**
 * @brief Searches for a student by their ID.
 *
 * This function searches for a student with the given ID and displays their
 * details if found. If the ID does not exist, an appropriate message is shown.
 *
 * @param id The student ID to search for.
 */
void SearchStudentByID(int id);

/**
 * @brief Converts a string to lowercase.
 *
 * This function takes a string as input and converts all characters to
 * lowercase, modifying the original string.
 *
 * @param s The string to be converted to lowercase.
 */
void ToLowerCase(char *s);

/**
 * @brief Searches for a student by their first name.
 *
 * This function searches for students with the specified first name and
 * displays their details. If no students are found, an appropriate message is shown.
 *
 * @param fname The first name of the student to search for.
 */
void SearchStudentByFirstName(char fname[]);

/**
 * @brief Searches for students by a course ID.
 *
 * This function searches through all students to find those registered for a
 * specific course ID and displays their details. If no students are found,
 * an appropriate message is shown.
 *
 * @param cId The course ID to search for.
 */
void SearchStudentByCourseID(int cId);

/**
 * @brief Gets the total number of students currently in the records.
 *
 * This function returns the number of students that have been added to the
 * records.
 *
 * @return The number of students.
 */
int GetNumberOfStudents(void);

/**
 * @brief Deletes a student by their ID.
 *
 * This function searches for a student with the given ID and removes them
 * from the records. If the ID does not exist, an appropriate message is shown.
 *
 * @param id The student ID to delete.
 */
void DeleteStudentById(int id);

/**
 * @brief Updates a student's details by their ID.
 *
 * This function searches for a student with the given ID and prompts the user
 * to update the student's details. If the ID does not exist, an appropriate
 * message is shown.
 *
 * @param id The student ID whose details are to be updated.
 */
void UpdateStudentById(int id);

#endif /* STUDENT_H_ */
