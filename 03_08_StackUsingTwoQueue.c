#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
struct Queue {
    int arr[MAX];
    int front, rear, size;
};

// Initialize queue
void initQueue(struct Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check empty
int isEmpty(struct Queue* q) {
    return q->size == 0;
}

// Enqueue
void enqueue(struct Queue* q, int x) {
    if (q->size == MAX) {
        printf("Queue Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
    q->size++;
}

// Dequeue
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return val;
}

/* ---------------- Method 1: EnQueue costly ---------------- */
struct Stack1 {
    struct Queue q1, q2;
};

void initStack1(struct Stack1* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

// Push (costly)
void push1(struct Stack1* s, int x) {
    enqueue(&s->q2, x);  
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// Pop (O(1))
int pop1(struct Stack1* s) {
    if (isEmpty(&s->q1)) return -1;
    return dequeue(&s->q1);
}

/* ---------------- Method 2: DeQueue costly ---------------- */
struct Stack2 {
    struct Queue q1, q2;
};

void initStack2(struct Stack2* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

// Push (O(1))
void push2(struct Stack2* s, int x) {
    enqueue(&s->q1, x);
}

// Pop (costly)
int pop2(struct Stack2* s) {
    if (isEmpty(&s->q1)) return -1;

    while (s->q1.size > 1) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    int val = dequeue(&s->q1);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return val;
}

/* ---------------- Main ---------------- */
int main() {
    struct Stack1 s1;
    struct Stack2 s2;

    initStack1(&s1);
    initStack2(&s2);

    printf("Method 1 (EnQueue costly):\n");
    push1(&s1, 5);
    push1(&s1, 42);
    push1(&s1, 17);
    push1(&s1, 89);
    printf("Popped: %d\n", pop1(&s1));
    printf("Popped: %d\n", pop1(&s1));
    printf("Popped: %d\n", pop1(&s1));

    printf("\nMethod 2 (DeQueue costly):\n");
    push2(&s2, 91);
    push2(&s2, 63);
    push2(&s2, 28);
    push2(&s2, 74);
    push2(&s2, 36);
    printf("Popped: %d\n", pop2(&s2));
    printf("Popped: %d\n", pop2(&s2));
    printf("Popped: %d\n", pop2(&s2));

    return 0;
}
