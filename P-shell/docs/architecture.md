# P-Shell Architecture

## 1. Overview

P-Shell is a minimal Unix-like command-line shell written in C.

The purpose of the project is not to recreate Bash completely, but to understand how a shell interacts with the Linux operating system.

P-Shell currently supports:

- Interactive command input
- Command parsing
- External Linux programs
- Process creation
- Program execution
- Parent/child process synchronization
- Built-in commands
- Directory navigation

The project is being developed incrementally to understand Unix/Linux systems programming concepts.

---

# 2. Current Features

P-Shell currently implements:

- `fgets()` based input
- Input newline removal using `strcspn()`
- Tokenization using `strtok()`
- Argument arrays using `char *args[]`
- External command execution
- Process creation using `fork()`
- Program replacement using `execvp()`
- Parent synchronization using `wait()`
- Built-in `exit`
- Built-in `cd`
- Directory changes using `chdir()`
- Modular source-file architecture
- Git/GitHub version control

---

# 3. Architecture

The shell follows a simple processing pipeline:

User Input
    |
    v
shell_loop()
    |
    v
parse_command()
    |
    v
Argument / Command Representation
    |
    +------------------+
    |                  |
    v                  v
builtin_command()   execute_command()
    |                  |
    |                  v
    |               fork()
    |                  |
    |                  v
    |               execvp()
    |                  |
    |                  v
    |              Linux Kernel
    |
    v
Command completed


The main design principle is separation of concerns.

The parser is responsible for understanding command input.

The built-in command module handles commands that must execute inside the shell process.

The executor handles external programs and process management.

---

# 4. Source Files

## main.c

Responsible for starting the shell.

Its primary responsibility is to enter the shell loop.

---

## shell.c

Contains the main interactive shell loop.

Responsibilities:

1. Display the prompt.
2. Read user input.
3. Remove the newline.
4. Parse the command.
5. Check for `exit`.
6. Check for built-in commands.
7. Execute external commands.

Conceptually:

    while (shell is running) {

        read input

        parse input

        if exit:
            terminate shell

        if builtin:
            execute builtin

        else:
            execute external command
    }

---

## parser.c

Responsible for converting raw input into command arguments.

Example:

    ls -l

becomes:

    args[0] = "ls"
    args[1] = "-l"
    args[2] = NULL

The parser currently uses `strtok()` for tokenization.

The parser does not create processes or execute commands.

Its responsibility is command representation.

---

## execute.c

Responsible for executing external programs.

The current execution model is:

    shell
      |
      +-- fork()
            |
            +-- child
                  |
                  +-- execvp()

The parent waits for the child using `wait()`.

---

## builtin.c

Contains commands that must be handled by the shell itself.

Current built-ins:

- `cd`

The built-in function returns an integer indicating whether the command was handled.

Conceptually:

    builtin_command(args)

        command is builtin
            |
            +-- execute it
            |
            +-- return 1

        command is not builtin
            |
            +-- return 0

This allows the shell loop to decide whether an external execution is required.

---

## shell.h

Contains declarations shared between source files.

This allows the project to remain modular instead of placing all implementation in one source file.

---

# 5. Why `cd` Is a Built-in

`cd` cannot normally be implemented as an ordinary external program executed by the current shell.

Reason:

`fork()` creates a child process with its own process state.

If a child changes its working directory using:

    chdir()

the parent shell's working directory does not change.

Therefore:

    shell
      |
      +-- fork()
            |
            +-- child
                  |
                  +-- chdir()

would only change the child's directory.

The shell itself must execute `chdir()`.

Therefore `cd` is a built-in command.

---

# 6. Why `exit` Is a Built-in

`exit` must terminate the shell process itself.

If it were executed in a separate child process, only the child would terminate.

The shell would continue running.

Therefore the shell handles `exit` directly.

---

# 7. External Command Execution

For a command such as:

    ls -l

P-Shell approximately performs:

    User
      |
      v
    fgets()
      |
      v
    parse_command()
      |
      v
    args[]
      |
      v
    execute_command()
      |
      v
    fork()
      |
      +----------------+
      |                |
      v                v
    Parent           Child
      |                |
      |             execvp()
      |                |
      |                v
      |           Linux Kernel
      |                |
      |                v
      |               ls
      |
      +---- wait() <---+
      |
      v
    prompt again

`fork()` creates the child process.

`execvp()` replaces the child process's program with the requested program.

`wait()` allows the parent shell to wait for the child to finish.

---

# 8. Shell vs Linux Kernel

P-Shell is a user-space program.

It does not implement the operating system.

The Linux kernel provides mechanisms such as:

- Process management
- Memory management
- File descriptors
- File systems
- Scheduling
- Inter-process communication
- Networking
- Device management

P-Shell uses these mechanisms through system-call interfaces exposed through the C/POSIX environment.

The shell interprets user-facing syntax and translates the user's request into operations performed using operating-system facilities.

---

# 9. Important Design Principle

The shell does not implement everything itself.

For example:

P-Shell does not implement process creation from scratch.

Instead, it uses:

    fork()

Similarly, P-Shell does not implement program loading from scratch.

It uses:

    execvp()

The shell's responsibility is to correctly coordinate these existing operating-system mechanisms.

This distinction is important:

    Shell logic
        +
    Operating-system primitives
        =
    Shell functionality

---

# 10. Pipes — Planned Feature

The next major feature is:

    ls | grep .c

The pipe operator is shell syntax.

The Linux kernel does not interpret the literal `|` character.

Instead, P-Shell must:

1. Detect `|` during command parsing.
2. Split the input into separate commands.
3. Create a Linux pipe using `pipe()`.
4. Create processes for the commands.
5. Connect the output of the first process to the input of the second.
6. Execute both programs.
7. Wait for the required processes.

Conceptually:

    ls
     |
     | stdout
     v
    +------------------+
    | Linux pipe       |
    | kernel buffer    |
    +------------------+
             |
             | stdin
             v
          grep .c
             |
             v
          terminal

The pipe buffer is maintained by the Linux kernel.

It is not an ordinary `malloc()` buffer belonging to either process.

---

# 11. Why Not Simply Use malloc() for Pipes?

A normal heap allocation belongs to a process.

For example:

    char *buffer = malloc(...);

After creating independent processes with `fork()`, each process has its own virtual address space.

Therefore one process cannot simply access another process's ordinary heap memory.

A Linux pipe provides controlled inter-process communication through a kernel-managed buffer.

---

# 12. Streaming vs Temporary Storage

An alternative implementation could theoretically be:

    ls
     |
     v
    temporary file / memory
     |
     v
    grep

However, Unix pipes provide streaming communication:

    ls
     |
     +---- data ----+
     |              |
     v              v
    pipe          grep

`grep` can process data while `ls` is still producing it.

Advantages include:

- Lower memory requirements
- No need to store the complete output
- Producer and consumer can run concurrently
- Natural composition of Unix programs

---

# 13. Current Limitations

P-Shell is intentionally minimal.

It does not yet implement:

- Pipes
- Input redirection
- Output redirection
- Append redirection
- Background processes
- Signals
- Job control
- Multiple pipelines
- Quoting
- Escaping
- Environment variable expansion
- Wildcard expansion
- Command substitution
- Advanced error handling

These will be implemented incrementally.

---

# 14. Engineering Goals

The goal of P-Shell is not feature parity with Bash.

The primary goals are:

1. Understand Unix process architecture.
2. Understand system calls.
3. Understand process isolation.
4. Understand inter-process communication.
5. Understand file descriptors.
6. Understand signals.
7. Understand process synchronization.
8. Understand how shells are architected.
9. Practice modular C systems programming.
10. Develop the ability to design systems rather than merely copy implementations.

---

# 15. Current Development Model

Each feature should be developed through the following process:

    Problem
       |
       v
    Requirements
       |
       v
    Design
       |
       v
    Research / Documentation
       |
       v
    Implementation
       |
       v
    Testing
       |
       v
    Debugging
       |
       v
    Documentation
       |
       v
    Git commit

The implementation should be understood before being considered complete.

---

# 16. Current Next Step

Next feature:

    PIPE SUPPORT

First target:

    ls | grep .c

Before implementing it, we need to understand:

- File descriptors
- Standard input
- Standard output
- How `pipe()` works
- How file descriptors are inherited across `fork()`
- `dup2()`
- Closing unused pipe ends
- Blocking behavior
- Parent/child synchronization

Only after understanding these concepts should the implementation begin.
