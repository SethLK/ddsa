#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* create(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
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
    newNode->prev = temp;
}

void printForward(struct Node* current) {
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("Null\n");
}

void printBackward(struct Node* current) {
    while (current->next != NULL) {
        current = current->next;
    }
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("Null\n");
}

void freeList(struct Node* current) {
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

void deleteNode(struct Node** headRef, struct Node* nodeToDelete) {
    if (*headRef == NULL || nodeToDelete == NULL) {
        return;
    }

    if (*headRef == nodeToDelete) {
        *headRef = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    }

    free(nodeToDelete);
}

int main() {
    struct Node* head = create(1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);

    printf("Forward: ");
    printForward(head);

    printf("Reverse: ");
    printBackward(head);

    // Delete the node with data = 3
    struct Node* nodeToDelete = head->next->next;
    deleteNode(&head, nodeToDelete);
    printf("After deleting node with data = 3:\n");
    printf("Forward: ");
    printForward(head);
    printf("Reverse: ");
    printBackward(head);

    // Free the memory
    freeList(head);
    
    return 0;
}
