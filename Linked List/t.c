#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} *head = NULL;

void createList() {
    int n, data, i = 1;
    struct Node *temp, *newNode;

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
    head->next = head;
    temp = head;

    for (i; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &data);

        newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation not possible.\n");
            return;
        }

        newNode->data = data;
        newNode->next = head;
        temp->next = newNode;
        temp = newNode;
    }
}

void displayList() {
    struct Node *temp = head;
    if (temp == NULL) {
        printf("No data found.\n");
        return;
    }

    printf("\n");
    do {
        printf("%-4d", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n\n");
}


int main(int argc, char const *argv[])
{
    int ch;
    printf("\n\nPress 1 to create list.");
    printf("\nPress 2 to display list.\n");

    while (1) {
        displayList();
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            createList();
            break;

        case 2:
            displayList();
            break;

        default:
            exit(0);
        }
    }

    return 0;
}
