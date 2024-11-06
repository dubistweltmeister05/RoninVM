#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum
{
	INST_PUSH,
	INST_POP,
	INST_ADD,
	INST_SUB,
	INST_MUL,
	INST_DIV,
	INST_PRINT,
} Inst_set;

typedef struct
{
	Inst_set type;
	int value;
} Inst;

#define DEF_INST_PUSH(x) {.type = INST_PUSH, .value = x}
#define DEF_INST_POP() {.type = INST_POP}
#define DEF_INST_ADD() {.type = INST_ADD}
#define DEF_INST_SUB() {.type = INST_SUB}
#define DEF_INST_MUL() {.type = INST_MUL}
#define DEF_INST_DIV() {.type = INST_DIV}
#define DEF_INST_PRINT() {.type = INST_PRINT}

Inst program[] = {
	DEF_INST_PUSH(11),
	DEF_INST_PUSH(13),
	DEF_INST_PUSH(15),
	DEF_INST_PUSH(17),
	DEF_INST_PRINT(),
};

#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))
#define MAX_STACK_SIZE 1024
int stack[MAX_STACK_SIZE];
int stack_size = 0; // this has been changed by us

void push(int val)
{
	if (stack_size >= MAX_STACK_SIZE)
	{
		fprintf(stderr, "ERROR : STACK OVERFLOW\n");
		exit(1);
	}
	stack[stack_size] = val;
	stack_size++;
}

int pop()
{
	if (stack_size <= 0)
	{
		fprintf(stderr, "ERROR : STACK UNDERFLOW\n");
		exit(1);
	}
	return stack[--stack_size];
}

void print_stack()
{
	printf("This is what the stack contains for far\n");
	for (int temp = stack_size - 1; temp >= 0; temp--)
	{
		printf("%d\n", stack[temp]);
	}
}
int main()
{
	int a, b;
	for (size_t ip = 0; ip < PROGRAM_SIZE; ip++)
	{
		switch (program[ip].type)
		{
		case INST_PUSH:
			push(program[ip].value);
			break;
		case INST_POP:
			pop();
			break;
		case INST_ADD:
			a = pop();
			b = pop();
			push(a + b);
			break;
		case INST_SUB:
			a = pop();
			b = pop();
			push(a - b);
			break;
		case INST_DIV:
			a = pop();
			b = pop();
			push(a / b);
			break;
		case INST_MUL:
			a = pop();
			b = pop();
			push(a * b);
			break;
		case INST_PRINT:
			print_stack();
			// printf("%d\n", pop());
			break;
		}
	}

	// print_stack();
	return 0;
}
