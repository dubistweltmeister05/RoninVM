RoninVM
Overview
RoninVM is a stack-based virtual machine written in C, designed to execute a custom instruction set with basic arithmetic operations. It features a stack for handling computations and includes file I/O functionality to save and load program states from a binary file.

Features
Custom Instruction Set: Supports instructions for pushing, popping, and performing basic arithmetic (addition, subtraction, multiplication, and division).
Stack Management: Includes robust error handling for stack overflow and underflow.
File Persistence: Save and load program instructions to/from binary files, allowing for reusable program states.
Instruction Set
The virtual machine supports the following instructions:

Instruction	Description
INST_PUSH	Pushes a value onto the stack
INST_POP	Pops a value from the stack
INST_ADD	Adds the top two stack values
INST_SUB	Subtracts the top two values
INST_MUL	Multiplies the top two values
INST_DIV	Divides the top two values
INST_PRINT	Prints the current stack
Code Structure
The main components of the code are:

Instruction Definitions: Inst_set defines available instructions, while macros make it easy to create program instructions.
Stack Functions: push, pop, and print_stack handle the stack operations.
File I/O: write_prog_to_file and read_from_file allow the program to save/load instructions in binary format.
Execution Cycle: The main function interprets and executes each instruction in sequence.
Installation
Clone the repository to your local machine:

bash
Copy code
git clone https://github.com/dubistweltmeister05/RoninVM.git
cd RoninVM
Usage
Here's a brief example of how to run the virtual machine:

Define Program Instructions in program[]:

c
Copy code
Inst program[] = {
    DEF_INST_PUSH(5),
    DEF_INST_PUSH(10),
    DEF_INST_ADD(),
    DEF_INST_PRINT(),
};
Compile and Run:

bash
Copy code
gcc -o RoninVM RoninVM.c
./RoninVM
Output: The VM will print the result of the computation (e.g., 15 for the example above).

Example Output
With the example instructions:

c
Copy code
Inst program[] = {
    DEF_INST_PUSH(5),
    DEF_INST_PUSH(10),
    DEF_INST_ADD(),
    DEF_INST_PRINT(),
};
The program will push 5 and 10 onto the stack, add them, and then print the result (15).

Error Handling
The VM will handle:

Stack Overflow: If the stack exceeds MAX_STACK_SIZE.
Stack Underflow: If an operation tries to pop from an empty stack.
Contributing
Feel free to open issues, submit pull requests, or suggest improvements. Contributions are welcome!
