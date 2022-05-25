#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} *front = NULL, *rear = NULL;

void enqueue(int data) {
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Overflow.\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue() {
    struct Node *temp = front;
    if (front == NULL) {
        printf("Underflow.\n");
        return;
    }

    printf("Deleted element: %d\n", front->data);
    if (front == rear) {
        front= rear = NULL;
    } else {
        front = front->next;
    }
    free(temp);
}

void display() {
    printf("\nDisplaying Queue:\n");
    
    struct Node *temp = front;
    if (front == NULL) {
        printf("No data found.\n");
        return;
    }

    while (temp != NULL) {
        printf("%-4d", temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

int main(int argc, char const *argv[])
{
    int ch, data;
    printf("\n\nPress 1 to enqueue.");
    printf("\nPress 2 to dequeue.");
    printf("\nPress 3 to display.\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            printf("Enter the data: ");
            scanf("%d", &data);
            enqueue(data);
            display();
            break;

        case 2:
            dequeue();
            display();
            break;

        case 3:
            display();
            break;

        default:
            exit(0);
        }
    }

    return 0;
}
