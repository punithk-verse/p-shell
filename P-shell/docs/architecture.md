# P-Shell

P-Shell is a small Unix-style shell written in C.

It reads commands, parses them, creates processes, runs programs, and waits for them to finish.

## Current Features

- Command execution using `fork()` and `execvp()`
- `cd` for changing the current directory
- `exit` for leaving the shell
- Current working directory in the prompt
- Single pipe (`|`) between two commands
- Output redirection using `>`
- Append redirection using `>>`
- `:explain` mode for showing process and file-descriptor operations

## How It Works

```text
Input
  ↓
Parser
  ↓
Built-in command?
  ├── Yes → execute in shell
  └── No  → execute_command()
                ↓
             fork()
                ↓
             execvp()
