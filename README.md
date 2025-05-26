# Recursive Descent Parser - CSC 461 Assignment

## Overview

This project implements a **Recursive Descent Parser** in **C** for parsing control structures (`if-else`, `while`), arithmetic expressions, and a special identifier `LTD`. It validates syntax including nested blocks and expressions with proper error handling.

## Compilation & Running

1. Open CodeBlocks or any C compiler.
2. Copy-paste the code into `main.c`.
3. Build and run the program.
4. Enter your code inside `{}` when prompted.
5. Type `exit` to quit.

## Valid Test Cases

```c
{ a + b; }
{ if (x == LTD) { y + 1; } else { y - 1; } }
{ while (x > LTD) { x - 1; } }
```

## Invalid Test Cases

```c
{ x = 5 }               // Missing semicolon
{ if (x > 3 { y = 1; }  // Unmatched parentheses
{ x = $5; }             // Invalid token
```

## Features

- Supports `if`, `else`, `while` statements.
- Parses arithmetic expressions with `+`, `-`, `*`, `/`.
- Recognizes relational operators (`==`, `!=`, `<`, `<=`, `>`, `>=`).
- Handles a special token `LTD`.
- Reports syntax errors with clear messages.

## Conclusion

The parser successfully analyzes structured code snippets with nested control flows and expressions, enforcing syntax correctness with detailed error feedback.
