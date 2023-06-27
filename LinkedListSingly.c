#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 1000
typedef struct dataStructure {
	int a;
	char b[SIZE];
	struct dataStructure* next;
} DS;
void addNode(DS* newNode, DS** head) {
	DS* temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = newNode;
	newNode->next = NULL;
	return;
}
void printList(DS* head) {
	DS* curr = head;
	int i = 1;
	while (curr) {
		printf("node %d is: a= %d, b= %s",i,curr->a, curr->b);
		curr = curr->next;
		i++;
	}
	return;
}
void deleteNode(DS** head, int key) {
	/* Store head node */
	DS* temp = *head, *prev;
	/* If head node itself holds the key to be deleted */
	if (temp && temp->a == key) {
		*head = temp->next;
		free(temp);
		return;
	}
	/* Search for the key to be deleted */
	while (temp && temp->a != key) {
		prev = temp;
		temp = temp->next;
	}
	/* If key was not present in linked list */
	if (!temp) {
		printf("Given key was not found\n");
		return;
	}
	/* Unlink the node from linked list */
  	prev->next = temp->next;
	return;
}
void readFile(FILE* fp, DS** head) {
	char buf[SIZE];
	char* p;
	int isHead = 1;
	DS* temp = NULL;
	while (!feof(fp)) {
		if (!fgets(buf,SIZE,fp))
			continue;
		if (isHead)
			temp = *head;
		else {
			temp = (DS*) malloc(sizeof(DS));
			if (!temp) exit(1);
		}
		p = strtok(buf, ",");
		temp->a = atoi(p);
		p = strtok(NULL, ",");
		strcpy(temp->b, p);
		if (isHead)
			isHead = 0;
		else
			addNode(temp,head);
	}
	return;
}
void printLargest(int size, DS* head) {
	int count = 1;
	DS* current = head;
	while (current) {
		if (current->a == size)
			printf("At location %d, a= %d, b= %s", count, current->a, current->b);
		current = current->next;
		count++;
	}
	return;
}
int findLargest(DS* head) {
	DS* current = head;
	DS *largest = head;
	while (current) {
		if (current->a > largest->a)
			largest = current;
		current = current->next;
	}
	return largest->a;
}
void freeList(DS **head)  {
	DS* curr = *head;
	while (curr) {
		DS* next = curr->next;
		free(curr);
		curr = next;
	}
	return;
}
void assignHead(DS** dest, DS** source) {
	*dest = *source;
	if ((*source)->next) {
		*source = (*source)->next;
		(*dest)->next = NULL;
	}
	return;
}
void moveHead(DS** dest, DS** source) {
	if (!(*source)->next) {
		addNode(*source,&(*dest));
		*source = NULL;
	} else {
		DS* curr = *source;
		*source = (*source)->next;
		addNode(curr,&(*dest));
	}
	return;
}
void mergeLists(DS** headNew, DS** head1, DS** head2) {
	if ((*head1)->a < (*head2)->a)
		assignHead(&(*headNew), &(*head1));
	else
		assignHead(&(*headNew), &(*head2));
	while (*head1 && *head2) {
		if ((*head1)->a < (*head2)->a)
			moveHead(&(*headNew), &(*head1));
		else
			moveHead(&(*headNew), &(*head2));
	}
	while (*head1)
		moveHead(&(*headNew), &(*head1));
	while (*head2)
		moveHead(&(*headNew), &(*head2));
	return;
}
void reverse(DS** head) {
	DS* prev = NULL;
	DS* current = *head;
	DS* next;
	while (current) {
		next = current->next;  
	 	current->next = prev;   
	 	prev = current;
	 	current = next;
	}
	*head = prev;
}
int main(int argc, char* argv[]) {
	if (argc < 2) { printf("Missing file name\n"); exit(1); }
	else if (argc == 2) {
		DS* head = (DS*) malloc(sizeof(DS));
		FILE* fp;
		fp = fopen(argv[1],"r");
		readFile(fp, &head);
		fclose(fp);
		printf("List:\n");
		printList(head);
		int largest = findLargest(head);
		printLargest(largest,head);
		deleteNode(&head,largest);
		printList(head);
		freeList(&head);
	} else {
		DS* head1 = (DS*) malloc(sizeof(DS));
		DS* head2 = (DS*) malloc(sizeof(DS));
		DS* headNew;
		FILE* fp;
		fp = fopen(argv[1],"r");
		readFile(fp, &head1);
		fclose(fp);
		fp = fopen(argv[2],"r");
		readFile(fp, &head2);
		fclose(fp);
		printf("List 1:\n");
		printList(head1);
		printf("List 2:\n");
		printList(head2);
		mergeLists(&headNew,&head1, &head2);
		printf("ListNew:\n");
		printList(headNew);
		freeList(&head1);
		freeList(&head2);
		freeList(&headNew);
	}
	return EXIT_SUCCESS;
}
