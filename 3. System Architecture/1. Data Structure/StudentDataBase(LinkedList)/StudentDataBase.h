/*
 * StudentDataBase.h
 *
 *  Created on: Sep 30, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef STUDENTDATABASE_H_
#define STUDENTDATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define DPRINTF(...) {fflush(stdin); \
	fflush(stdout);\
	printf(__VA_ARGS__); \
	fflush(stdin); \
	fflush(stdout);}

typedef struct student{
	char name[50];
	int id;
	float gpa;
	struct student *next;
}student_t;


/**
 * @brief Clears the input buffer to prevent issues with reading inputs.
 */
void ClearInputBuffer();

/**
 * @brief Fills in the details for a student including ID, name, and GPA.
 * @param st Pointer to the student structure to be filled with data.
 */
void FillStudentData(student_t *st);

/**
 * @brief Adds a new student to the beginning of the linked list.
 * @param head Double pointer to the head of the student linked list.
 */
void AddStudentAtBeginning(student_t **head);

/**
 * @brief Adds a new student to the end of the linked list.
 * @param head Double pointer to the head of the student linked list.
 */
void AddStudentAtEnd(student_t **head);

/**
 * @brief Displays all students currently in the linked list.
 * @param head Pointer to the head of the student linked list.
 */
void DisplayStudents(student_t *head);

/**
 * @brief Searches for a student by their ID in the linked list.
 * @param head Pointer to the head of the student linked list.
 * @param id ID of the student to search for.
 * @return Pointer to the student structure if found, otherwise NULL.
 */
student_t *SearchStudent(student_t *head, int id);

/**
 * @brief Deletes a student from the linked list by their ID.
 * @param head Double pointer to the head of the student linked list.
 * @param id ID of the student to delete.
 */
void DeleteStudent(student_t **head, int id);

/**
 * @brief Deletes all students in the linked list and frees memory.
 * @param head Double pointer to the head of the student linked list.
 */
void DeleteAllStudents(student_t **head);

/**
 * @brief Gets the length (number of nodes) of the student linked list.
 * @param head Pointer to the head of the student linked list.
 * @return The number of students in the list.
 */
int GetLength(student_t *head);

/**
 * @brief Retrieves the N-th student from the beginning of the list.
 * @param head Pointer to the head of the student linked list.
 */
void GetNthStudentFromBeginning(student_t *head);

/**
 * @brief Retrieves the N-th student from the end of the list (method 1).
 * @param head Pointer to the head of the student linked list.
 */
void GetNthStudentFromEnd1(student_t *head);

/**
 * @brief Retrieves the N-th student from the end of the list (method 2).
 * @param head Pointer to the head of the student linked list.
 */
void GetNthStudentFromEnd2(student_t *head);

/**
 * @brief Retrieves the middle student from the linked list (method 1).
 * @param head Pointer to the head of the student linked list.
 */
void GetTheMiddleStudent1(student_t *head);

/**
 * @brief Retrieves the middle student from the linked list (method 2).
 * @param head Pointer to the head of the student linked list.
 */
void GetTheMiddleStudent2(student_t *head);

/**
 * @brief Reverses the linked list of students.
 * @param head Double pointer to the head of the student linked list.
 */
void ReverseLinkedList(student_t **head);

/**
 * @brief Swaps the positions of two students in the linked list by their IDs.
 * @param head Double pointer to the head of the student linked list.
 * @param ID1 ID of the first student.
 * @param ID2 ID of the second student.
 */
void Swap2NodesByID(student_t **head, int ID1, int ID2);

/**
 * @brief Sorts the students in the linked list by their ID in ascending order.
 * @param head Double pointer to the head of the student linked list.
 */
void SortNodesByID(student_t **head);


#endif /* STUDENTDATABASE_H_ */
