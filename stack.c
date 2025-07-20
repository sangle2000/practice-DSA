#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int cap;
    int top;
    char* data;
} Stack;

void init(Stack *s, int maxLength) {
    s->top = -1;
    s->cap = maxLength;
    s->data = malloc(maxLength*sizeof(char));
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == s->cap - 1;
}

void push(Stack *s, char value) {
    if (!isFull(s)) {
        s->top++;
        s->data[s->top] = value;
        return;
    }

    printf("Stack overflow\n");
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        char value = s->data[s->top];
        s->top--;
        return value;
    }

    printf("Stack underflow");
    return '\0';
}

char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }

    printf("Stack underflow");
    return '\0';
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void fromInfix2Postfix(Stack s, char input[]) {
    char result[100];
    int k = 0;
    char c;
    for (int i = 0; input[i] != '\0'; i++) {
        c = input[i];
        if (isdigit(c)) {
            result[k] = c;
            k++;
        } else if (c == '(') {
            push(&s, c);
        } else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                result[k] = pop(&s);
                k++;
            }
            pop(&s);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!isEmpty(&s) && priority(peek(&s)) >= priority(c)) {
                result[k] = pop(&s);
                k++;
            }
            push(&s, c);
        }
    }

    while (!isEmpty(&s)) {
        result[k] = pop(&s);
        k++;
    }

    result[k] = '\0';

    for (int i = 0; result[i] != '\0'; i++) {
        printf("%c", result[i]);
    }
}

int main() {
    Stack s;

    init(&s, 100);

    fromInfix2Postfix(s, "2+(3*1)-9");

    return 0;
}
