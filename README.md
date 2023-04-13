# Holberton Simple Shell
A simple shell implementation created for the Holberton School.

## Description

The Holberton Simple Shell is a command-line interpreter that allows users to execute commands and interact with their operating system. It was created as a group project by Josh Davis and Alton Andrews.

## Features
- Executes basic shell commands
- Handles command-line arguments
- Supports PATH environment variable
- Supports exit status
- Handles signal handling
- Supports comments

## Getting Started

1. Clone the repository: `git clone https://github.com/jdavis916/simple_shell.git`
2. Compile the program: `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
3. Run the shell: `./hsh`

## Usage

After running the shell, users can enter commands and execute them by pressing enter. For example:

$ ls -l
total 4
-rw-rw-r-- 1 vagrant vagrant 283 Apr 10 19:39 AUTHORS
-rw-rw-r-- 1 vagrant vagrant 1222 Apr 10 19:41 README.md
-rw-rw-r-- 1 vagrant vagrant 1756 Apr 10 19:41 shell.c
$

To exit the shell, users can use the `exit` command or press `Ctrl-D`.

## License

