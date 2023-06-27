#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct dataStructure {
	int a;
	char b[200];
	struct dataStructure* next;
	struct dataStructure* prev;
} DS;
void addNode(DS* newDS, DS** head) {
	DS* temp = *head;
	while (temp->next) {
		temp = temp->next;
	}
	newDS->prev = temp;
	newDS->next = NULL;
	temp->next = newDS;
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
}
void deleteNode(DS** head, int key) {
	if (!head)
		return;
	/* Find the required node */
	DS* curr = *head;
	DS* prev;
	while (curr->a != key) {
		if (!curr->next) {
			printf("Given node is not found in the list!!!\n");
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	/* Check if node is only node */
	if (!(*head)->next) {
		*head = NULL;
		free(curr);
		return;
	}
	/* If more than one node, check if it is first node */
	if (curr == *head) {
		*head = (*head)->next;
		free((*head)->prev);
		(*head)->prev = NULL;
		return;
    }
	/* check if node is last node */
	else if (!curr->next) {
		free(prev->next);
		prev->next = NULL;
		return;
	}
	else {
		prev->next = curr->next;
		curr->next->prev = prev;
		free(curr);
		return;
	}
}
void readFile(FILE* fp, DS** head) {
	char buf[200];
	char* p;
	int isHead = 1;
	DS* temp = NULL;
	while (!feof(fp)) {
		if (!fgets(buf,200,fp))
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
	while (curr)
	{
		DS* next = curr->next;
		free(curr);
		curr = next;
	}
	return;
}
void assignHead(DS** dest, DS** source) {
	if (!(*source)->next) {
		*dest = *source;
	} else {
		*source = (*source)->next;
		*dest = (*source)->prev;
		(*source)->prev = NULL;
		(*dest)->next = NULL;
	}
}
void moveHead(DS** dest, DS** source) {
	if (!(*source)->next) {
		addNode(*source,&(*dest));
		*source = NULL;
	} else {
		*source = (*source)->next;
		addNode((*source)->prev,&(*dest));
		(*source)->prev = NULL;
	}
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
