# SimpleLang Compiler

## Overview

SimpleLang is a minimalistic high-level language designed to run on an 8-bit CPU. The language includes basic constructs such as variable declarations, assignments, arithmetic operations, and conditional statements. This project implements a compiler for SimpleLang in C++, translating SimpleLang code into assembly code for an 8-bit CPU.

## Key Features

- **Variable Declarations**: Syntax to declare integer variables.
- **Assignments**: Assign expressions to variables.
- **Arithmetic Operations**: Supports addition (`+`) and subtraction (`-`).
- **Conditionals**: Basic `if` and `else` statements.

## Example Program in SimpleLang

```simplelang
// Variable declaration
int a;
int b;
int c;

// Assignment
a = 10;
b = 20;
c = a + b;

// Conditional
if (c == 30) {
    c = c + 1;
}
```

## Assignment Objective

The goal of this project is to implement a compiler for SimpleLang, which translates its high-level constructs into assembly code compatible with an 8-bit CPU.

## Project Components

### 1. **Lexer**
- Tokenizes the SimpleLang code.
- Recognizes keywords, operators, identifiers, and literals.

### 2. **Parser**
- Builds an Abstract Syntax Tree (AST) from the tokens.
- Validates the syntax and detects errors gracefully.

### 3. **Code Generator**
- Converts the AST into assembly code for the 8-bit CPU.
- Maps high-level operations to the CPU's instruction set.

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., `g++`).
- **8-bit CPU Simulator**: Clone and set up the 8-bit CPU simulator from [lightcode/8bit-computer](https://github.com/lightcode/8bit-computer).

### Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/simplelang-compiler.git
   cd simplelang-compiler
   ```

2. Build the project:
   ```bash
   g++ -o simplelang_compiler main.cpp
   ```

3. Run the compiler with a SimpleLang file:
   ```bash
   ./simplelang_compiler example.simple
   ```

## Usage

### Input
The compiler accepts SimpleLang code files with constructs like:

```simplelang
int a;
a = 10;
if (a == 10) {
    a = a + 1;
}
```

### Output
The compiler outputs the corresponding 8-bit CPU assembly code.

### Error Handling
The compiler reports syntax errors and undeclared variable usage.

## Architecture

- **Scanner (Lexer)**: Converts the input file into a series of tokens.
- **SyntaxAnalyzer (Parser)**: Parses tokens to construct an AST and validates the syntax.
- **Code Generator**: Traverses the AST to generate the target assembly code.

## Example Assembly Code Output

For the above SimpleLang code, the generated assembly might look like this:

```assembly
LOAD 10
STORE a
LOAD a
SUB 10
JNZ ELSE
LOAD a
ADD 1
STORE a
JMP ENDIF
ELSE:
; No operation for else
ENDIF:
```

## How It Works

1. **Tokenization**: The lexer scans the input file and generates tokens based on the language constructs.
2. **Parsing**: The parser processes the tokens to validate syntax and builds the AST.
3. **Code Generation**: The AST is traversed to produce equivalent assembly code.

## Directory Structure

```
.
├── main.cpp        # Main driver code for the compiler
├── example.simple  # Sample SimpleLang code file
├── README.md       # Documentation (this file)
```


- **8-bit CPU Simulator**: [lightcode/8bit-computer](https://github.com/lightcode/8bit-computer)
- **Assignment Guide**: Provided by Vicharak.

## Contact

For any queries or suggestions, please reach out to [your email/contact info].
