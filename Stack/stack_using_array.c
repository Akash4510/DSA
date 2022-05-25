#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int TOP = -1;
int stack[MAX];

void push(int data) {
    if (TOP == MAX - 1) {
        printf("Stack Overflow.\n");
        return;
    }
    stack[++TOP] = data;
}

void pop() {
    if (TOP == -1) {
        printf("Stack Underflow.\n");
        return;
    }
    printf("Popped element: %d\n", stack[TOP--]);;
}

void peek() {
    if (TOP == -1) {
        printf("Stack Underflow.\n");
        return;
    }
    printf("The top element is: %d\n", stack[TOP]);
}

void display() {
    printf("\nDisplaying Stack:\n");

    if (TOP == -1) {
        printf("No data found.\n");
        return;
    }

    for (int i = TOP; i >= 0; i--) {
        printf("\n| %-2d|\n", stack[i]);
        printf("-----");
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
