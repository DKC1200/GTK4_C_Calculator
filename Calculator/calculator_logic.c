#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    double *data;
    int size;
    int capacity;
} DoubleStack;

typedef struct {
    char *data;
    int size;
    int capacity;
} CharStack;

static DoubleStack* double_stack_new(void) {
    DoubleStack *stack = malloc(sizeof(DoubleStack));
    stack->capacity = 10;
    stack->size = 0;
    stack->data = malloc(sizeof(double) * stack->capacity);
    return stack;
}

static void double_stack_push(DoubleStack *stack, double value) {
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, sizeof(double) * stack->capacity);
    }
    stack->data[stack->size++] = value;
}

static double double_stack_pop(DoubleStack *stack) {
    if (stack->size > 0) {
        return stack->data[--stack->size];
    }
    return 0.0;
}

static double double_stack_top(DoubleStack *stack) {
    if (stack->size > 0) {
        return stack->data[stack->size - 1];
    }
    return 0.0;
}

static int double_stack_size(DoubleStack *stack) {
    return stack->size;
}

static int double_stack_empty(DoubleStack *stack) {
    return stack->size == 0;
}

static void double_stack_free(DoubleStack *stack) {
    free(stack->data);
    free(stack);
}

static CharStack* char_stack_new(void) {
    CharStack *stack = malloc(sizeof(CharStack));
    stack->capacity = 10;
    stack->size = 0;
    stack->data = malloc(sizeof(char) * stack->capacity);
    return stack;
}

static void char_stack_push(CharStack *stack, char value) {
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, sizeof(char) * stack->capacity);
    }
    stack->data[stack->size++] = value;
}

static char char_stack_pop(CharStack *stack) {
    if (stack->size > 0) {
        return stack->data[--stack->size];
    }
    return '\0';
}

static char char_stack_top(CharStack *stack) {
    if (stack->size > 0) {
        return stack->data[stack->size - 1];
    }
    return '\0';
}

static int char_stack_empty(CharStack *stack) {
    return stack->size == 0;
}

static void char_stack_free(CharStack *stack) {
    free(stack->data);
    free(stack);
}

static double base_calc(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;
    }
    return 0;
}

static int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

static void process(DoubleStack *nums, CharStack *ops) {
    if (double_stack_size(nums) < 2) return;
    
    double n2 = double_stack_top(nums);
    double_stack_pop(nums);
    
    double n1 = double_stack_top(nums);
    double_stack_pop(nums);
    
    char op = char_stack_top(ops);
    char_stack_pop(ops);
    
    double_stack_push(nums, base_calc(n1, n2, op));
}

char* solve_problem(const char* problem) {
    if (!problem || strlen(problem) == 0) {
        return strdup("");
    }
    
    DoubleStack *numbers = double_stack_new();
    CharStack *operations = char_stack_new();
    
    size_t len = strlen(problem);
    for (size_t i = 0; i < len; i++) {
        if (isspace(problem[i])) continue;
        
        if (isdigit(problem[i]) || problem[i] == '.') {
            char *endptr;
            double num = strtod(&problem[i], &endptr);
            double_stack_push(numbers, num);
            i += (endptr - &problem[i]) - 1;
        }
        else {
            while (!char_stack_empty(operations) && 
                   priority(char_stack_top(operations)) >= priority(problem[i])) {
                process(numbers, operations);
            }
            char_stack_push(operations, problem[i]);
        }
    }
    
    while (!char_stack_empty(operations)) {
        process(numbers, operations);
    }
    
    char *result;
    if (!double_stack_empty(numbers)) {
        double res = double_stack_top(numbers);
        
        char temp[64];
        
        if (res == (long long)res) {
            snprintf(temp, sizeof(temp), "%.0f", res);
        } else {
            snprintf(temp, sizeof(temp), "%.10g", res);
        }
        
        result = strdup(temp);
    } else {
        result = strdup("Error");
    }
    
    double_stack_free(numbers);
    char_stack_free(operations);
    
    return result;
}