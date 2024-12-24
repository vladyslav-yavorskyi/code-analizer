# Code Analyzer Project

## Overview
The Code Analyzer is a modular, multithreaded tool designed to scan and analyze source code for various potential issues. Currently, the tool supports memory-related checks, including detection of memory leaks and improper use of `malloc` and `free`. Its flexible design allows for easy extension to other types of code analysis, such as vulnerability detection or code quality checks.

## Features
- **Memory Analysis**: Detects memory leaks and improper usage of memory allocation/deallocation functions.
- **Modular Design**: Each type of analysis is handled by a separate thread, making the tool extensible.
- **Scalable**: Capable of handling large codebases with efficient memory management.
- **Customizable Rules**: Extend the analyzer to include checks for security vulnerabilities, style adherence, or specific code patterns.

## Build System
-  `Makefile`: Simplifies the process of building the project and managing dependencies.

## Prerequisites
- **Compiler**: GCC or any modern C compiler supporting C11.
- **Environment**: POSIX-compliant system for thread and file handling.
- **Libraries**: Standard C library, `pthread` for multithreading.

## Usage
1. Clone the repository and navigate to the project directory.
2. Build the project using the provided `Makefile`:
3. Run the analyzer with a source code file:
4. The tool outputs detected issues, such as memory leaks or allocation problems, to `stderr`.

## Future Enhancements
- Implement checks for:
- Security vulnerabilities (e.g., buffer overflows, dangling pointers).
- Code style adherence and best practices.
- Resource management (e.g., file descriptor leaks).
- Add configuration options for custom rules.
- Enhance performance for extremely large codebases.

## Contribution
Contributions are welcome! Feel free to open issues or submit pull requests to improve the tool or add new analysis modules.

