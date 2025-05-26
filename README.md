# Recursive Descent Parser - CSC 461 Assignment

## Overview

This project implements a **Recursive Descent Parser (RDP)** in **C** to parse control structures like `if-else`, `while` loops, and arithmetic expressions with nested brackets. The parser also handles a special identifier, `LTD`, which represents the last three digits of a student's ID.

## Compilation Instructions (Using CodeBlocks)

1. **Open CodeBlocks** and create a **new Console Application** project in C.
2. **Copy and paste** the code into the `main.c` file.
3. **Build the project** by pressing `Ctrl+F9`.
4. **Run the project** by pressing `Ctrl+F10`.

## Runtime Instructions

1. **Enter code** inside `{}` when prompted, for example:

   { if (a == LTD) { a + b; } }

The program will parse the code and show either a success message or an error.

## Test Cases

Valid Test Cases:

Simple Arithmetic Expression:
{ a + b; }

If Statement with LTD:
{ if (LTD == 123) { a + b; } }

While Loop with LTD:
{ while (a < 100) { a * LTD; } }

Invalid Test Cases:

Missing Semicolon:
{ a + b }
Error: Missing semicolon.

Mismatched Brackets:
{ if (a == b) { a + b; }
Error: Mismatched brackets.

Conclusion
This project implements a Recursive Descent Parser that handles control structures, arithmetic expressions, and a special identifier LTD. The parser performs error checking and evaluates expressions correctly. It has been tested with various valid and invalid test cases to ensure its functionality
