#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "rvm.h"
// int stack[MAX_STACK_SIZE];

Inst program[] = {
	DEF_INST_PUSH(1),
	DEF_INST_PUSH(4),
	DEF_INST_PUSH(6),
	DEF_INST_PUSH(8),
	DEF_INST_PUSH(10),
	DEF_INST_PUSH(12),
	DEF_INST_PUSH(14),
	DEF_INST_INDUP(3),
	// DEF_INST_PRINT(),
};

#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))

void push(Machine *machine, int val)
{
	if (machine->stack_size >= MAX_STACK_SIZE)
	{
		fprintf(stderr, "ERROR : STACK OVERFLOW\n");
		exit(1);
	}
	machine->stack[machine->stack_size] = val;
	machine->stack_size++;
}

int pop(Machine *machine)
{
	if (machine->stack_size <= 0)
	{
		fprintf(stderr, "ERROR : STACK UNDERFLOW\n");
		exit(1);
	}
	machine->stack_size--;
	return machine->stack[machine->stack_size];
}

void index_swap(Machine *machine, int index)
{
	if (index > machine->stack_size || index < 0)
	{
		fprintf(stderr, "ERROR: Index is out of range\n");
		exit(1);
	}
	int temp = machine->stack[index];
	machine->stack[index] = pop(machine);
	push(machine, temp);
}
void index_dup(Machine *machine, int index)
{
	if (index > machine->stack_size || index < 0)
	{
		fprintf(stderr, "ERROR: Index is out of range\n");
		exit(1);
	}
	push(machine, machine->stack[index]);
}
void print_stack(Machine *machine)
{
	// printf("This is what the stack contains for far\n");
	printf("---------Stack---------\n");
	for (int temp = machine->stack_size - 1; temp >= 0; temp--)
	{
		printf("%d\n", machine->stack[temp]);
	}
	printf("---------End of Stack---------\n");
}

void write_prog_to_file(Machine *machine, char *file_path)
{
	FILE *file = fopen(file_path, "wb");
	if (file == NULL)
	{
		fprintf(stderr, "Error : Could not write to the file%s\n", file_path);
		exit(1);
	}
	fwrite(machine->instructions, sizeof machine->instructions[0], PROGRAM_SIZE, file);

	fclose(file);
}

Machine *read_from_file(Machine *machine, char *file_path)
{
	FILE *file = fopen(file_path, "rb");

	if (file == NULL)
	{
		fprintf(stderr, "Error : Could not read from the file%s\n", file_path);
		exit(1);
	}
	Inst *instructions = malloc(sizeof(Inst) * MAX_STACK_SIZE);
	// Machine * machine = malloc(sizeof(Machine));

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	length = length - ftell(file);
	length = fread(instructions, sizeof(*instructions), length, file);

	machine->program_size = length;
	fclose(file);
	// printf("File_Read is a success\n");
	return (machine);
}

void run_instructions(Machine *machine)
{
	int a, b;

	for (size_t ip = 0; ip < machine->program_size; ip++)
	{
		// print_stack(machine);
		switch (machine->instructions[ip].type)
		{
		case INST_NOP:
			continue;
			break;
		case INST_PUSH:
			push(machine, machine->instructions[ip].value);
			break;
		case INST_POP:
			pop(machine);
			break;
		case INST_ADD:
			a = pop(machine);
			b = pop(machine);
			push(machine, a + b);
			break;
		case INST_DUP:
			a = pop(machine);
			push(machine, a);
			push(machine, a);
			break;
		case INST_INDUP:
			index_dup(machine, machine->instructions[ip].value);
			break;
		case INST_SUB:
			a = pop(machine);
			b = pop(machine);
			push(machine, a - b);
			break;
		case INST_DIV:
			a = pop(machine);
			b = pop(machine);
			if (b == 0)
			{
				fprintf(stderr, "ERROR: CANNOT DIVIDE BY 0");
				exit(1);
			}
			push(machine, a / b);
			break;
		case INST_MOD:
			a = pop(machine);
			b = pop(machine);
			if (b == 0)
			{
				fprintf(stderr, "ERROR: CANNOT DIVIDE BY 0");
				exit(1);
			}
			push(machine, a % b);
			break;
		case INST_MUL:
			a = pop(machine);
			b = pop(machine);
			push(machine, a * b);
			break;
		case INST_SWAP:
			a = pop(machine);
			b = pop(machine);
			push(machine, a);
			push(machine, b);
			break;
		case INST_INSWAP:
			index_swap(machine, machine->instructions[ip].value);
			break;
		case INST_CMPE:
			a = pop(machine);
			b = pop(machine);
			push(machine, b);
			push(machine, a);
			push(machine, (a == b ? 1 : 0));
			break;
		case INST_CMPG:
			a = pop(machine);
			b = pop(machine);
			push(machine, b);
			push(machine, a);
			push(machine, (a > b ? 1 : 0));
			break;
		case INST_CMPL:
			a = pop(machine);
			b = pop(machine);
			push(machine, b);
			push(machine, a);
			push(machine, (a < b ? 1 : 0));
			break;
		case INST_CMPGE:
			a = pop(machine);
			b = pop(machine);
			push(machine, b);
			push(machine, a);
			push(machine, (a >= b ? 1 : 0));
			break;
		case INST_CMPLE:
			a = pop(machine);
			b = pop(machine);
			push(machine, b);
			push(machine, a);
			push(machine, (a <= b ? 1 : 0));
			break;
		case INST_CMPNE:
			a = pop(machine);
			b = pop(machine);
			push(machine, b);
			push(machine, a);
			push(machine, (a == b ? 0 : 1));
			break;
		case INST_NZJMP:
			if (pop(machine) != 0)
			{
				// printf("IP: %zu\n", ip);
				ip = machine->instructions[ip].value - 1;
				if (ip + 1 >= machine->program_size)
				{
					fprintf(stderr, "ERROR: Jumping out of bounds\n");
				}
				// printf("IP: %zu\n", ip);
			}
			else
			{
				continue;
			}
			break;
		case INST_ZJMP:
			if (pop(machine) == 0)
			{
				// printf("IP: %zu\n", ip);
				ip = machine->instructions[ip].value - 1;
				if (ip + 1 >= machine->program_size)
				{
					fprintf(stderr, "ERROR: Jumping out of bounds\n");
				}
				// printf("IP: %zu\n", ip);
			}
			else
			{
				continue;
			}
			break;
		case INST_JMP:
			ip = machine->instructions[ip].value - 1;
			if (ip + 1 >= machine->program_size)
			{
				fprintf(stderr, "ERROR: Jumping out of bounds\n");
			}
			break;
		case INST_PRINT:
			print_stack(machine);
			printf("%d\n", pop(machine));
			break;
		case INST_HALT:
			ip = machine->program_size;
			break;
		}
	}
};
int main()
{

	Machine *loaded_machine = malloc(sizeof(Machine) * MAX_STACK_SIZE);
	loaded_machine->instructions = program;
	write_prog_to_file(loaded_machine, "test.rvm");
	loaded_machine = read_from_file(loaded_machine, "test.rvm");
	run_instructions(loaded_machine);

	print_stack(loaded_machine);
	return 0;
}
