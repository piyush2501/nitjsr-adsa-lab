#include <stdio.h>
#include <ctype.h>   // for isdigit()
#include <string.h>  // for strlen()

#define MAX 100

char stack[MAX];
int top = -1;

// Push onto stack
void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

// Pop from stack
char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return -1;
}

// Peek stack top
char peek() {
    if (top >= 0)
        return stack[top];
    return -1;
}

// Check precedence of operators
int precedence(char op) {
    if (op == '/' || op == '*')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

// Function to convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;

    for (i = 0; i < strlen(infix); i++) {
        c = infix[i];

        // If operand (single digit), add to postfix
        if (isdigit(c)) {
            postfix[k++] = c;
        }
        // If '(', push to stack
        else if (c == '(') {
            push(c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        // Operator
        else {
            while (top != -1 && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; // Null terminate
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);  // Note: no spaces allowed

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
