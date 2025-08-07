
# RoninVM

This project is a simple stack-based virtual machine (VM) implemented in C. The VM can interpret and execute a set of basic instructions like arithmetic operations, conditional jumps, and stack manipulations, allowing you to simulate a basic computing environment.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
- [Instruction Set](#instruction-set)
- [Example Program](#example-program)
- [Contributing](#contributing)

## Features
- Supports arithmetic operations: addition, subtraction, multiplication, division, and modulus.
- Stack operations: push, pop, duplicate, and swap.
- Comparison and conditional jump instructions.
- Simple file-based program reading and writing.

## Requirements
- C compiler (e.g., GCC)
- `make` (optional for building)

## Usage

1. **Clone the repository**:
   ```bash
   git clone https://github.com/dubistweltmeister05/RoninVM
   cd RoninVM
   
   ```

2. **Compile the Code**:
   ```bash
   gcc vm.c -o vm
   ```

3. **Run the Program**:
   ```bash
   ./vm
   ```

4. **Example Output**:
   The program outputs the content of the stack after each operation, helping you trace the execution.

## Instruction Set
The VM supports the following instructions:

| Instruction  | Description                                      |
|--------------|--------------------------------------------------|
| `INST_NOP`   | No operation                                     |
| `INST_PUSH`  | Push a value onto the stack                      |
| `INST_POP`   | Pop a value from the stack                       |
| `INST_ADD`   | Pop two values, add, and push the result         |
| `INST_SUB`   | Pop two values, subtract, and push the result    |
| `INST_MUL`   | Pop two values, multiply, and push the result    |
| `INST_DIV`   | Pop two values, divide, and push the result      |
| `INST_MOD`   | Pop two values, modulus, and push the result     |
| `INST_DUP`   | Duplicate the top value of the stack             |
| `INST_SWAP`  | Swap the top two values on the stack             |
| `INST_PRINT` | Pop and print the top value on the stack         |
| `INST_JMP`   | Unconditional jump to a specific instruction     |
| `INST_CJMP`  | Conditional jump if the top stack value is `1`   |

## Example Program
An example program that demonstrates the VM’s functionality:

```c
Inst program[] = {
    DEF_INST_PUSH(3),
    DEF_INST_JMP(6),
    DEF_INST_PUSH(15),
    DEF_INST_NOP(),
    DEF_INST_NOP(),
    DEF_INST_CMPLE(),
    DEF_INST_PRINT(),
};
```

This example pushes `3` to the stack, jumps to a specific instruction, and then conditionally evaluates and prints stack contents.

## Contributing
Feel free to open issues or submit pull requests to improve the VM. Contributions are welcome!

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
