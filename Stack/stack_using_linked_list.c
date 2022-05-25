#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} *TOP = NULL;

void push(int data) {
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Stack Overflow.\n");
        return;
    }

    newNode->data = data;
    newNode->next = TOP;
    TOP = newNode;
}

void pop() {
    if (TOP == NULL) {
        printf("Stack Underflow.\n");
        return;
    }

    struct Node *temp = TOP;
    printf("Popped item: %d\n\n", TOP->data);
    TOP = TOP->next;
    temp->next = NULL;
    free(temp);
}

void peek() {
    if (TOP == NULL) {
        printf("Stack Underflow.\n");
        return;
    }

    printf("The top element is: %d\n", TOP->data);
}

void display() {
    printf("\nDisplaying Stack:\n");

    if (TOP == NULL) {
        printf("No data found.\n");
        return;
    }

    struct Node *temp = TOP;

    while(temp != NULL) {
        printf("\n| %-2d|\n", temp->data);
        printf("-----");
        temp = temp->next;
    }
    printf("\n\n");
}

int main(int argc, char const *argv[])
{
    int ch, data;
    printf("\n\nPress 1 to push.");
    printf("\nPress 2 to pop.");
    printf("\nPress 3 to peek.");
    printf("\nPress 4 to display.\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            printf("Enter the data: ");
            scanf("%d", &data);
            push(data);
            display();
            break;

        case 2:
            pop();
            display();
            break;

        case 3:
            peek();
            break;

        case 4:
            display();
            break;

        default:
            exit(0);
        }
    }

    return 0;
}
