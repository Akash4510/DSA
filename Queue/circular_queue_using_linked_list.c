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
        printf("Memory allocation not possible.\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
        rear->next = front;
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
}

void dequeue() {
    if (front == NULL) {
        printf("Underflow.\n");
        return;
    }

    struct Node *temp = front;
    printf("Deleted data: %d\n", front->data);

    if (front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
        rear->next = front;
        temp->next = NULL;
    }
    free(temp);
}

void display() {
    printf("\nDisplaying Queue:\n");
    if (front == NULL) {
        printf("No data found.\n");
        return;
    }

    struct Node *temp = front;
    do {
        printf("%-4d", temp->data);
        temp = temp->next;
    } while (temp != front);
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
