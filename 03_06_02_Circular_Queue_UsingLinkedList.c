#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *front = NULL, *rear = NULL;

int isEmpty() {
    return (front == NULL);
}

void enqueue(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    if (front == NULL) {
        front = rear = newNode;
        rear->next = front; // circular link
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
    printf("%d enqueued\n", value);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is Empty!\n");
        return;
    }
    if (front == rear) {
        printf("%d dequeued\n", front->data);
        free(front);
        front = rear = NULL;
    } else {
        Node *temp = front;
        printf("%d dequeued\n", temp->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void display() {
    if (isEmpty()) {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Queue: ");
    Node *temp = front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();

    dequeue();
    dequeue();
    display();

    enqueue(50);
    enqueue(60);
    display();

    return 0;
}
