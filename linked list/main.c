#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* create(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void show(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("Null\n");
}

void append(struct Node** headRef, int data) {
    struct Node* newNode = create(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    struct Node* temp = *headRef;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteLast(struct Node** headRef){
    if(*headRef == NULL){
        printf("There is no list");
    }
    
    if ((*headRef)->next == NULL) {
        free(*headRef);
        *headRef = NULL;
        return;
    }

    /*
    FIrst I need to store previouse data
    after that delete next of previous
    */

   struct Node* prev;
   struct Node* current = *headRef;
    while (current->next != NULL)
    {
        prev = current;
        current = current->next;
    }
    free(current);
    prev->next = NULL;
}

void addFirst(struct Node** headRef, int data){
    struct Node* newNode = create(data);
    newNode->next = *headRef;
    *headRef = newNode;
}

void deleteFirst(struct Node** headRef){
    struct Node* temp = (*headRef)->next;
    free((*headRef));
    (*headRef) = temp;
}

int main() {
    struct Node* head = create(1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    addFirst(&head, 0);
    show(head);
    deleteFirst(&head);
    deleteFirst(&head);
    deleteFirst(&head);
    deleteFirst(&head);
    show(head);

    // Free memory
    struct Node* current = head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
