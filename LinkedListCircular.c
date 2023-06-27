#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct dataStructure {
	int a;
	char b[200];
	struct dataStructure* next;
} DS;
void addNode(DS* newDS, DS** head) {
	DS* temp = *head;
	while (temp->next != *head) {
		temp = temp->next;
	}
	temp->next = newDS;
	newDS->next = *head;
	return;
}
void printList(DS* head) {
	DS* curr = head;
	int i = 1;
	do {
		printf("node %d is: a= %d, b= %s",i,curr->a, curr->b);
		curr = curr->next;
		i++;
	} while (curr != head);
}
void deleteNode(DS** head, int key) {
	if (head == NULL)
		return;
	/* Find the required node */
	DS* curr = *head;
	DS* prev;
	while (curr->a != key) {
		if (curr->next == *head) {
			printf("Given node is not found in the list!!!\n");
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	/* Check if node is only node */
	if ((*head)->next == *head) {
		*head = NULL;
		free(curr);
		return;
	}
	/* If more than one node, check if it is first node */
	if (curr == *head) {
		prev = *head;
		while (prev->next != *head)
			prev = prev->next;
		*head = curr->next;
		prev->next = *head;
		free(curr);
		return;
    }
	/* check if node is last node */
	else if (curr->next == *head) {
		prev->next = *head;
		free(curr);
		return;
	}
	else {
		prev->next = curr->next;
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
		if (isHead) {
			temp->next = temp;
			isHead = 0;
		} else
			addNode(temp,head);
	}
	return;
}
void printLargest(int size, DS* head) {
	int count = 1;
	DS* current = head;
	do {
		if (current->a == size)
			printf("At location %d, a= %d, b= %s", count, current->a, current->b);
		current = current->next;
		count++;
	} while (current != head);
}
int findLargest(DS* head) {
	DS* current = head;
	DS *largest = head;
	do {
		if (current->a > largest->a)
			largest = current;
		current = current->next;
	} while (current != head);
	return largest->a;
}
void freeList(DS **head)  {
	if (head && *head) {
		DS* next = (*head)->next;
		while (head && (next != *head)) {
			DS *tmp = next;
			next = next->next;
			free(tmp);
		}
		free(*head);
		*head = NULL;
	}
	return;
}
void assignHead(DS** dest, DS** source) {
	if ((*source)->next == *source) {
		*dest = *source;
	} else {
		DS* curr = *source;
		DS* prev = *source;
		while (prev->next != *source)
			prev = prev->next;
		prev->next = (*source)->next;
		*source = prev->next;
		*dest = curr;
		(*dest)->next = *dest;
	}
}
void moveHead(DS** dest, DS** source) {
	if ((*source)->next == *source) {
		addNode(*source,&(*dest));
		*source = NULL;
	} else {
		DS* curr = *source;
		DS* prev = *source;
		while (prev->next != *source)
			prev = prev->next;
		prev->next = (*source)->next;
		*source = prev->next;
		addNode(curr,&(*dest));
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
