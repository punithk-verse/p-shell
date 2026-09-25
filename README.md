# P-Shell

P-Shell is a small Unix-style shell written in C.

It takes commands from the user, runs programs using processes, and supports basic shell features such as pipes and file redirection.

## Features

- Command execution with `fork()` and `execvp()`
- Built-in `cd`
- Built-in `exit`
- Current working directory in the prompt
- Single pipe (`|`)
- Output redirection (`>`)
- Append redirection (`>>`)
- `:explain` mode for tracing shell operations

## Build

Go to the `src` directory:

```bash
cd P-shell/src
