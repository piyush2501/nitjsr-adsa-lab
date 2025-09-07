#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
struct Stack {
    int arr[MAX];
    int top;
};

// Initialize stack
void initStack(struct Stack* s) {
    s->top = -1;
}

// Check empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Check full
int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

// Push element
void push(struct Stack* s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++(s->top)] = x;
}

// Pop element
int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// Peek
int peek(struct Stack* s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}

/* ---------------- Method 1: Push costly ---------------- */
struct Queue1 {
    struct Stack s1, s2;
};

void initQueue1(struct Queue1* q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

// Enqueue (costly)
void enqueue1(struct Queue1* q, int x) {
    // Move all elements from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push new element to s1
    push(&q->s1, x);

    // Move back elements from s2 to s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }
}

// Dequeue (O(1))
int dequeue1(struct Queue1* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return pop(&q->s1);
}

/* ---------------- Method 2: Pop costly ---------------- */
struct Queue2 {
    struct Stack s1, s2;
};

void initQueue2(struct Queue2* q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

// Enqueue (O(1))
void enqueue2(struct Queue2* q, int x) {
    push(&q->s1, x);
}

// Dequeue (costly O(n))
int dequeue2(struct Queue2* q) {
    int x;
    if (isEmpty(&q->s1) && isEmpty(&q->s2)) {
        printf("Queue is empty!\n");
        return -1;
    }

    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }

    x = pop(&q->s2);
    return x;
}

/* ---------------- Main ---------------- */
int main() {
    struct Queue1 q1;
    struct Queue2 q2;

    initQueue1(&q1);
    initQueue2(&q2);

    printf("Method 1 (Push costly):\n");
    enqueue1(&q1, 10);
    enqueue1(&q1, 20);
    enqueue1(&q1, 30);
    printf("Dequeued: %d\n", dequeue1(&q1));
    printf("Dequeued: %d\n", dequeue1(&q1));

    printf("\nMethod 2 (Pop costly):\n");
    enqueue2(&q2, 100);
    enqueue2(&q2, 200);
    enqueue2(&q2, 300);
    printf("Dequeued: %d\n", dequeue2(&q2));
    printf("Dequeued: %d\n", dequeue2(&q2));

    return 0;
}
