#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int queue[MAX], front = -1, rear = -1;

void enqueue(int data) {
    if (((rear + 1) % MAX) == front) {
        printf("Overflow.\n");
        return;
    }

    if (front == -1 || rear == -1) {
        front++;
    }
    rear = (rear + 1) % MAX;
    queue[rear] = data;
}

void dequeue() {
    if (front == rear) {
        printf("Deleted data: %d\n", queue[front]);
        front = rear = -1;
        return;
    }

    if (front == -1) {
        printf("Underflow.\n");
        return;
    }

    printf("Deleted data: %d\n", queue[front]);
    front = (front + 1) % MAX;
}

void display() {
    printf("\nDisplaying Queue:\n");
    printf("Front: %d\nRear: %d\n\n", front, rear);

    if (front == -1) {
        printf("Underflow.\n");
        return;
    }

    if (rear >= front) {
        for (int i = front; i <= rear; i++) {
            printf("%-4d", queue[i]);
        }
    } else {
        for (int i = 0; i <= rear; i++) {
            printf("%-4d", queue[i]);
        }
        for (int i = front; i < MAX; i++) {
            printf("%-4d", queue[i]);
        }
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
