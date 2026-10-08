# P-Shell

P-Shell is a small Unix-style shell written in C, built as a learning tool for understanding how a shell works underneath.
Instead of only running commands, P-Shell makes some of the underlying Unix concepts visible — processes, pipes, file descriptors, redirection, and process states.

<img width="700" alt="P-Shell architecture and process experiments" src="https://github.com/user-attachments/assets/1d82ce12-4b35-486f-ad76-fcc482026e4e" />

## What it does

P-Shell supports basic shell operations:

* Command execution using `fork()` and `execvp()`
* Built-in `cd` and `exit`
* Current working directory in the prompt
* Single pipes (`|`)
* Output redirection (`>`)
* Append redirection (`>>`)
* `:explain` mode for tracing shell operations

It also includes a few commands for experimenting with processes:

* `:process` — inspect the tracked child process
* `:zombie` — create a real zombie process
* `:reap` — collect the zombie using `waitpid()`
* Process information is read from `/proc`

The idea is simple: **use the shell, but also see what is happening underneath.**

## Build

Go to the `src` directory:

```bash
cd P-shell/src
```

Compile:

```bash
gcc *.c -o pshell
```

Run:

```bash
./pshell
```

## Example

A normal command:

```text
/home/punith/P-shell/P-shell/src > ls
```

A pipe:

```text
/home/punith/P-shell/P-shell/src > ls | wc
```

With `:explain`, P-Shell can show the operations involved:

```text
[pipe] created
       read end  = fd 3
       write end = fd 4

[fork] parent=3772 created child=3849
[fork] parent=3772 created child=3850

[stdout] ls -> pipe
         fd 4 -> stdout (fd 1)

[stdin]  wc <- pipe
         fd 3 -> stdin (fd 0)

[exec] child=3849 -> running "ls"
[exec] child=3850 -> running "wc"
```

This makes concepts such as `fork()`, `exec()`, pipes, and file descriptors easier to connect with what actually happens when a command is executed.

## Process experiments

P-Shell also allows process behaviour to be observed directly.

Create a zombie:

```text
:zombie
```

Inspect it:

```text
:process
```

Example:

```text
[process]
  PID   : 7604
  PPID  : 7603
  State : Z (zombie)
```

Then reap it:

```text
:reap
```

The zombie is collected using `waitpid()`.

P-Shell is still a small shell. The focus is on using that small implementation to understand the mechanisms behind Unix shells and processes.
