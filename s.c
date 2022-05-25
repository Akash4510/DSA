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

    if (n < 1) {
        printf("Invalid number.\n");
        return;
    }

    head = (struct Node *)malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("Memory allocation not possible.\n");
        return;
    }

    printf("Enter element %d: ", i++);
    scanf("%d", &data);

    head->data = data;
    head->next = NULL;
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
        newNode->next = NULL;
        temp->next = newNode;
        temp = newNode;
    }
}

void displayList() {
    struct Node *temp = head;

    if (head == NULL) {
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

int main(int argc, char const *argv[])
{
    createList();
    displayList();
    return 0;
}
