#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
} *head = NULL, *last = NULL;

void createList() {
    int n, data, i = 1;
    struct Node *newNode;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter element %d: ", i);
    scanf("%d", &data);
    i++;

    head = (struct Node *)malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("Memory allocation not possible.\n");
        return;
    }

    head->data = data;
    head->prev = NULL;
    head->next = NULL;
    last = head;

    for (i; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &data);

        newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation not possible.\n");
            return;
        }

        newNode->data = data;
        newNode->prev = last;
        newNode->next = NULL;
        last->next = newNode;
        last = newNode;
    }
}

void displayFromFirst() {
    struct Node *temp = head;
    if (temp == NULL) {
        printf("No data found.\n");
        return;
    }

    printf("\n");
    while (temp != NULL) {
        printf("%-4d", temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

void displayFromLast() {
    struct Node *temp = last;
    if (head == NULL) {
        printf("No data found.\n");
        return;
    }

    printf("\n");
    while (temp != NULL) {
        printf("%-4d", temp->data);
        temp = temp->prev;
    }
    printf("\n\n");
}

void insertAtFirst(int data) {
    struct Node *temp;

    temp = (struct Node *)malloc(sizeof(struct Node));
    if (temp == NULL) {
        printf("Memory allocation not possible.\n");
        return;
    }

    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void insertAtLast(int data) {
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation not possible.\n");
        return;
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (last == NULL) {
        head = newNode;
        last = head;
    } else {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
}

int getLengthOfList() {
    int c = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        c++;
        temp = temp->next;
    }
    return c;
}

void insertAtPos(int data, int pos) {
    int len = getLengthOfList();
    if (pos < 1 || pos > len + 1) {
        printf("Invalid position.\n");
        return;
    }

    if (pos == 1) {
        insertAtFirst(data);
        return;
    } else if (pos == len + 1) {
        insertAtLast(data);
        return;
    }

    struct Node *prevNode, *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation not possible.\n");
        return;
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    prevNode = head;
    for (int i = 2; i <= pos - 1; i++) {
        prevNode = prevNode->next;
    }

    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    newNode->next->prev = newNode;
    prevNode->next = newNode;
}

void deleteFromFirst() {
    struct Node *temp = head;
    if (head == NULL) {
        printf("No data found.\n");
        return;
    }

    if (head->next == NULL) {
        head = NULL;
        free(temp);
        return;
    }

    head = temp->next;
    head->prev = NULL;
    temp->next = NULL;
    free(temp);
}

void deleteFromLast() {
    struct Node *temp = last;
    if (head == NULL) {
        printf("No data found.\n");
        return;
    }

    last = temp->prev;
    last->next = NULL;
    temp->prev = NULL;
    free(temp);
}

void deleteFromPos(int pos) {
    int len = getLengthOfList();
    if (pos < 1 || pos > len) {
        printf("Invalid position.\n");
        return;
    }

    if (pos == 1) {
        deleteFromFirst();
        return;
    } else if (pos == len) {
        deleteFromLast();
        return;
    }

    struct Node *temp, *prevNode = head;
    for (int i = 2; i <= pos - 1; i++) {
        prevNode = prevNode->next;
    }

    temp = prevNode->next;
    prevNode->next = temp->next;
    temp->next->prev = prevNode;
    temp->next = NULL;
    temp->prev = NULL;
    free(temp);
}

void deleteAll() {
    struct Node *temp;

    if (head == NULL) {
        printf("No data found.\n");
        return;
    }

    int len = getLengthOfList();
    for (int i = 0; i < len; i++) {
        deleteFromFirst();
    }
}

int main(int argc, char const *argv[])
{
    int ch, data, pos;
    printf("\n\nPress 1 to create list.");
    printf("\nPress 2 to display from first.");
    printf("\nPress 3 to display from last.");
    printf("\nPress 4 to insert at first.");
    printf("\nPress 5 to insert at last.");
    printf("\nPress 6 to insert at any pos.");
    printf("\nPress 7 to delete from first.");
    printf("\nPress 8 to delete from last.");
    printf("\nPress 9 to delete from any pos.\n");

    while (1) {
        // displayFromFirst();
        // displayFromLast();

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            createList();
            break;

        case 2:
            displayFromFirst();
            break;

        case 3:
            displayFromLast();
            break;

        case 4:
            printf("Enter the data: ");
            scanf("%d", &data);
            insertAtFirst(data);
            break;

        case 5:
            printf("Enter the data: ");
            scanf("%d", &data);
            insertAtLast(data);
            break;

        case 6:
            printf("Enter the data: ");
            scanf("%d", &data);
            printf("Enter the position: ");
            scanf("%d", &pos);
            insertAtPos(data, pos);
            break;

        case 7:
            deleteFromFirst();
            break;

        case 8:
            deleteAll();
            break;

        case 9:
            printf("Enter the position you want to delete from: ");
            scanf("%d", &pos);
            deleteFromPos(pos);
            break;

        default:
            exit(0);
        }
    }

    return 0;
}
