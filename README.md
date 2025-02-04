# minishell - As Beautiful as a Shell

minishell is a custom shell implemented in C as part of our group project. It replicates many features of bash, providing an interactive command-line environment with robust error handling, built-in commands, redirections, pipes, and more.

---
### Features

- Interactive Prompt & History

   - Displays a prompt for new commands.
   - Maintains command history using readline functions.

- Command Execution

   - Searches for and launches executables based on the PATH variable, or via relative/absolute paths.
   - Supports proper interpretation of quotes (single and double) to control meta-character behavior.

- Redirections & Pipes

   - Implements input (<), output (>), append (>>), and here-document (<<) redirections.
   - Enables piping commands with the | operator.

- Environment Variable Expansion

   - Expands variables prefixed with $.
   - Handles $? to represent the exit status of the most recent foreground command.

- Built-in Commands

   - echo (with -n option)
   - cd
   - pwd
   - export
   - unset
   - env
   - exit

- Signal Handling

   - Handles ctrl-C, ctrl-D, and ctrl-\ in interactive mode similarly to bash.

- Bonus Features

   - Logical Operators: Support for && and || with parentheses for grouping and priority.
   - Wildcard Expansion: Implements wildcard * expansion for matching files in the current working directory.

---

### Install

Clone the repository and build the project using the provided Makefile:
```
git clone https://github.com/toagne/minishell
cd minishell
make
```
---

### Usage

Launch the shell with:
```
./minishell
```
Once running, the shell will display a prompt where you can execute commands, use redirections and pipes, expand environment variables, and utilize built-in commands—all with behavior closely mimicking bash.
