Minishell



A custom shell implementation created in C that mimics basic functionalities of Bash. This project provides hands-on experience with processes, file descriptors, memory management, and command-line interface development.


Overview

Minishell is a small, interactive shell that can execute commands, manage processes, and handle input/output redirections. This project was built to learn more about low-level system programming, with a focus on memory handling, managing processes, and interacting with the operating system.

Features

Command Prompt: Displays a prompt and waits for user input.
History Management: Tracks previously executed commands.
Executable Search: Finds and runs executables from the PATH or via relative/absolute paths.
Quoting Support:

    Single quotes (') to prevent interpretation of metacharacters.
    Double quotes (") to prevent interpretation of metacharacters except for $.

Redirection:

    <: Redirect input.
    >: Redirect output.
    <<: Here-document, reading input until a specified delimiter is encountered.
    >>: Append mode for output redirection.

Pipelines: Allows piping the output of one command as input to the next.
Environment Variables: Expands variables prefixed by $.
Exit Status Handling: $? expands to the exit status of the last executed command.
Signal Handling:

    ctrl-C: Displays a new prompt on a new line.
    ctrl-D: Exits the shell.
    ctrl-\: Does nothing.

Built-in Commands:

    echo: Supports the -n option.
    cd: Changes directories.
    pwd: Prints the current working directory.
    export and unset: Manage environment variables.
    env: Lists all environment variables.
    exit: Exits the shell.
Getting Started
Prerequisites

    C Compiler: Ensure gcc or a compatible C compiler is installed.
    GNU Readline Library: Used for command-line editing and history capabilities. Install using:

    sudo apt-get install libreadline-dev

Installation

    Clone the repository:

git clone https://github.com/yourusername/minishell.git
cd minishell

Build the Project:

make

Run Minishell:

    ./minishell

Usage

Simply start the shell by running the executable. Minishell will present a prompt, where you can enter commands as you would in Bash.

$ ./minishell
minishell> echo Hello, World!
Hello, World!
minishell> ls | grep minishell
minishell
minishell> exit
$

Project Structure

    Makefile: Builds the project, providing commands like make, make clean, and make fclean.
    Source Files: .c files implementing the main logic for handling commands, processes, and built-in functions.
    Headers: .h files defining structures and function prototypes.

Development Guidelines

    Follow the project’s coding norms.
    Avoid undefined behaviors, memory leaks, and segmentation faults.
    Only a single global variable is allowed, which should be used judiciously.
