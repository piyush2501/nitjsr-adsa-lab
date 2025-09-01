#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for integers
int values[MAX];
int topVal = -1;

void pushVal(int v) { values[++topVal] = v; }
int popVal() { return values[topVal--]; }
int peekVal() { return values[topVal]; }

// Stack for operators
char ops[MAX];
int topOp = -1;

void pushOp(char op) { ops[++topOp] = op; }
char popOp() { return ops[topOp--]; }
char peekOp() { return ops[topOp]; }
int isEmptyOp() { return topOp == -1; }

// Precedence of operators
int precedence(char op) {
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Apply operator to two values
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // integer division
    }
    return 0;
}

// Evaluate expression
int evaluate(char *expr) {
    int i = 0;
    while (expr[i] != '\0') {
        // Skip spaces
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // If '(', push to ops stack
        if (expr[i] == '(') {
            pushOp(expr[i]);
            i++;
        }
        // If number (multi-digit allowed)
        else if (isdigit(expr[i])) {
            int val = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            pushVal(val);
        }
        // If ')', solve till '('
        else if (expr[i] == ')') {
            while (!isEmptyOp() && peekOp() != '(') {
                int b = popVal();
                int a = popVal();
                char op = popOp();
                pushVal(applyOp(a, b, op));
            }
            popOp(); // remove '('
            i++;
        }
        // Operator
        else {
            while (!isEmptyOp() && precedence(peekOp()) >= precedence(expr[i])) {
                int b = popVal();
                int a = popVal();
                char op = popOp();
                pushVal(applyOp(a, b, op));
            }
            pushOp(expr[i]);
            i++;
        }
    }

    // Entire expression parsed, apply remaining ops
    while (!isEmptyOp()) {
        int b = popVal();
        int a = popVal();
        char op = popOp();
        pushVal(applyOp(a, b, op));
    }

    return popVal();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    // Join all arguments into one expression string
    char expr[MAX] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expr, argv[i]);
        strcat(expr, " ");
    }

    int result = evaluate(expr);
    printf("%d\n", result);

    return 0;
}
