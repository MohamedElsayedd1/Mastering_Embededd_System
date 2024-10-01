/*
 * StudentDataBase.c
 *
 *  Created on: Sep 30, 2024
 *      Author: Mohamed Elsayed
 */

#include "StudentDataBase.h"

// Function to clear the input buffer
void ClearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Consume all characters in the input buffer
}

void FillStudentData(student_t *st){
	char input[50];
	// Adding student to the linked list database
	DPRINTF("Enter student ID: ");
	gets(input);
	st->id = atoi(input);

	DPRINTF("Enter student name: ");
	gets(st->name);

	DPRINTF("Enter student GPA: ");
	gets(input);
	st->gpa = atof(input);
}

void AddStudentAtBeginning(student_t **head){
	student_t *newStudent = (student_t *)malloc(sizeof(student_t ));
	if(!newStudent){
		DPRINTF("Memory allocation failed!\n");
		return;
	}
	FillStudentData(newStudent);
	newStudent->next = *head;
	*head = newStudent;
}

void AddStudentAtEnd(student_t **head){
	student_t *newStudent = (student_t *)malloc(sizeof(student_t ));
	if(!newStudent){
		DPRINTF("Memory allocation failed!\n");
		return;
	}
	FillStudentData(newStudent);
	newStudent->next = NULL;
	// check is the list is empty
	if(!*head){
		*head = newStudent;
	}
	else{
		student_t *temp = *head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newStudent;
	}
}

void DisplayStudents(student_t *head){
	student_t *temp = head;
	int studentCounter = 1;
	if(!temp){
		DPRINTF("No students in the database.\n");
		return;
	}
	DPRINTF("\n=============== Student DataBase ==============\n");
	while(temp != NULL){
		DPRINTF("Student %d: \n", studentCounter);
		DPRINTF("\n\t ID : %d",temp->id);
		DPRINTF("\n\t Name : %s", temp->name);
		DPRINTF("\n\t GPA : %0.2f\n", temp->gpa);
		temp = temp->next;
		studentCounter++;
	}
	DPRINTF("==============================================\n");
}

student_t *SearchStudent(student_t *head, int id){
	student_t *current = head;
	if(!current){
		DPRINTF("No students in the database.\n");
		return NULL;
	}
	else{
		while(current != NULL){
			if(current->id == id){
				break;
			}
			current = current->next;
		}
		return current;
	}
}

void DeleteStudent(student_t **head, int id){
	student_t *current = *head;
	student_t *prev = *head;
	if(!current){
		DPRINTF("No students in the database.\n");
		return;
	}
	else{
		// If the student to delete is the head
		if(current->id == id){
			*head = current->next;
			free(current);
			DPRINTF("Student with ID %d deleted.\n", id);
			return;
		}

		while(current != NULL){
			if(current->id == id){
				break;
			}
			prev = current;
			current = current->next;
		}

		if(!current){
			DPRINTF("Student with ID %d not found.\n", id);
			return;
		}
		else{
			prev->next = current->next;
			free(current);
			DPRINTF("Student with ID %d deleted.\n", id);
		}

	}
}

void DeleteAllStudents(student_t **head){
	student_t *current = *head;
	student_t *prev = *head;
	if(!current){
		DPRINTF("No students in the database.\n");
		return;
	}
	else{
		while(current){
			prev = current;
			current = current->next;
			free(prev);
		}
		*head = NULL;
		DPRINTF("All students have been deleted.\n");
	}
}

int GetLength(student_t *head){
	student_t *NodeListCounter = head;
	int counter = 0;
	if(!NodeListCounter){
		//DPRINTF("No students in the database.\n");
		return counter;
	}
	else{
		while(NodeListCounter){
			counter++;
			NodeListCounter = NodeListCounter->next;
		}
		return counter;
	}
}

void GetNthStudentFromBeginning(student_t *head){
	student_t *NodeListCounter = head;
	int counter = 1, NodePosition = 0, NodeLength = 0;
	NodeLength = GetLength(head); // Get the length of the list
	// Check if the list is empty before proceeding
	if(!NodeListCounter){
		DPRINTF("No students in the database.\n");
		return;
	}
	DPRINTF("Enter The Number Of The Student From Beginning : ");
	scanf("%d", &NodePosition);
	if(NodePosition > NodeLength || NodePosition <= 0){
		DPRINTF("Invalid Node Position -> List has ( %i ) Nodes \n", NodeLength);
		return;
	}
	else{
		// Traverse the list to reach the desired node
		while(counter < NodePosition){
			counter++;
			NodeListCounter = NodeListCounter->next;
		}
		DPRINTF("Student %d From The Beginning : \n", NodePosition);
		DPRINTF("\n\t ID : %d",NodeListCounter->id);
		DPRINTF("\n\t Name : %s", NodeListCounter->name);
		DPRINTF("\n\t GPA : %0.2f\n", NodeListCounter->gpa);
	}
}

void GetNthStudentFromEnd1(student_t *head){
	student_t *NodeListCounter = head;
	// Check if the list is empty before proceeding
	if(!NodeListCounter){
		DPRINTF("No students in the database.\n");
		return;
	}
	int counter = 1, NodePosition = 0, NodeLength = 0;
	NodeLength = GetLength(head); // Get the length of the list
	DPRINTF("Enter The Number Of The Student From End : ");
	scanf("%d", &NodePosition);
	NodePosition = NodeLength - NodePosition + 1;
	if(NodePosition > NodeLength || NodePosition <= 0){
		DPRINTF("Invalid Node Position -> List has ( %i ) Nodes \n", NodeLength);
		return;
	}
	else{
		// Traverse the list to reach the desired node
		while(counter < NodePosition){
			counter++;
			NodeListCounter = NodeListCounter->next;
		}
		DPRINTF("Student %d From The End: \n", NodePosition);
		DPRINTF("\n\t ID : %d",NodeListCounter->id);
		DPRINTF("\n\t Name : %s", NodeListCounter->name);
		DPRINTF("\n\t GPA : %0.2f\n", NodeListCounter->gpa);
	}
}

void GetNthStudentFromEnd2(student_t *head){
	if(!head){
		DPRINTF("No students in the database.\n");
		return;
	}
	else{
		int NodePosition = 0;
		int counter = 1;
		student_t *pFast = head;
		student_t *pSlow = head;
		student_t *wantedNode = NULL;
		DPRINTF("Enter The Number Of The Student From End : ");
		scanf("%d", &NodePosition);
		while(counter <= NodePosition - 1){
			pFast = pFast->next;
			counter++;
		}
		while(pFast->next != NULL){
			pFast = pFast->next;
			pSlow = pSlow->next;
		}
		wantedNode = pSlow;
		DPRINTF("Student %d From The End : \n", NodePosition);
		DPRINTF("\n\t ID : %d",wantedNode->id);
		DPRINTF("\n\t Name : %s", wantedNode->name);
		DPRINTF("\n\t GPA : %0.2f\n", wantedNode->gpa);
	}
}

void GetTheMiddleStudent1(student_t *head){
	student_t *NodeListCounter = head;
	// Check if the list is empty before proceeding
	if(!NodeListCounter){
		DPRINTF("No students in the database.\n");
		return;
	}
	int counter = 1, NodeMiddle = 0;
	NodeMiddle = (GetLength(head) + 1) / 2;
	if(NodeMiddle <= 0){
		DPRINTF("Invalid Node Position -> List has ( %i ) Nodes \n", GetLength(head));
		return;
	}
	else{
		// Traverse the list to reach the desired node
		while(counter < NodeMiddle){
			counter++;
			NodeListCounter = NodeListCounter->next;
		}
		DPRINTF("The Middle Student In The DataBase : \n");
		DPRINTF("Student %d: \n", counter);
		DPRINTF("\n\t ID : %d",NodeListCounter->id);
		DPRINTF("\n\t Name : %s", NodeListCounter->name);
		DPRINTF("\n\t GPA : %0.2f\n", NodeListCounter->gpa);
	}
}


void GetTheMiddleStudent2(student_t *head){
	student_t *pSlow = head;
	student_t *pFast = head;
	student_t *Middle = NULL;
	// Check if the list is empty before proceeding
	if(!pSlow){
		DPRINTF("No students in the database.\n");
		return;
	}

	while(pFast && pFast->next){
		pSlow = pSlow->next;
		pFast = pFast->next->next;
	}
	Middle = pSlow;
	DPRINTF("The Middle Student In The DataBase : \n");
	DPRINTF("Student %d: \n", (GetLength(head) + 1) / 2);
	DPRINTF("\n\t ID : %d",Middle->id);
	DPRINTF("\n\t Name : %s", Middle->name);
	DPRINTF("\n\t GPA : %0.2f\n", Middle->gpa);
}

void ReverseLinkedList(student_t **head){
	// Check if the list is empty before proceeding
	if(!*head){
		DPRINTF("No students in the database.\n");
		return;
	}
	student_t *prev = NULL;
	student_t *next = NULL;
	while(*head){
		next = (*head)->next;
		(*head)->next = prev;
		prev = *head;
		*head = next;
	}
	*head = prev;
	DPRINTF("The linked list has been reversed successfully.\n");
}

void Swap2NodesByID(student_t **head, int ID1, int ID2){
	// Check if the list is empty before proceeding
	if(!*head){
		DPRINTF("No students in the database.\n");
		return;
	}
	else{
		student_t *prevX = NULL, *currX = *head;
		student_t *prevY = NULL, *currY = *head;

		// Edge case: If x and y are the same, no need to swap
		if (ID1 == ID2) {
			DPRINTF("Both nodes have the same ID, no need to swap.\n");
			return;
		}

		// Search for 2 nodes by ID
		while(currX){
			if(currX->id == ID1){
				break;
			}
			prevX = currX;
			currX = currX->next;
		}

		while(currY){
			if(currY->id == ID2){
				break;
			}
			prevY = currY;
			currY = currY->next;
		}

		// cheack if the 2 nodes are exist
		if (!currX || !currY) {
			DPRINTF("One or both of the nodes are not present in the list.\n");
			return;
		}

		// If currX is not head of the list, link prevX to currY
		if(prevX){
			prevX->next = currY;
		}
		else{ // Else make currY the new head
			*head = currY;
		}
		// If currY is not head of the list, link prevY to currX
		if(prevY){
			prevY->next = currX;
		}
		else{ // Else make currX the new head
			*head = currX;
		}

		// Swap 2 Nodes
		student_t *temp = currX->next;
		currX->next = currY->next;
		currY->next = temp;
		DPRINTF("Nodes with IDs %d and %d have been swapped.\n", ID1, ID2);
	}
}

void SortNodesByID(student_t **head){
	// Check if the list is empty before proceeding
	if(!*head || !(*head)->next){
		DPRINTF("No students or only one student in the database.\n");
		return;
	}
	else{
		student_t *i;
		student_t *j;
		for(i = *head; i != NULL; i= i->next){
			for(j = i->next; j != NULL; j=j->next){
				if(j->id < i->id){
					Swap2NodesByID(head, j->id, i->id);
				}
			}
		}
	}
	DPRINTF("Students sorted by ID.\n");
}
