# Simple UNIX Shell (hsh)

A simplified UNIX command-line interpreter written in C. `./hsh` replicates the basic behaviour of `sh`: it reads a command, locates the corresponding executable, and runs it in a child process.

## Description

`hsh` is a lightweight shell that supports:

- **Interactive mode** — displays a prompt and waits for user input.
- **Non-interactive mode** — reads commands piped in.
- Execution of any command found in the directories listed in the `PATH` environment variable.
- Execution of commands given with an absolute or relative path (e.g. `/bin/ls`).
- Two built-in commands.

## Getting Started

### Installation

- Clone [Holberton Simple Shell Repo](https://github.com/DziRare/holbertonschool-simple_shell) locally.
`git clone https://github.com/DziRare/holbertonschool-simple_shell`

- Change current directory to holbertonschool-simple_shell
`cd holberton_simple-shell`

- Compile using gcc
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh` 


## Usage

### Interactive Mode

```bash
school@holbertonschool-simple-shell:/# ./hsh
╚( ⚆ ⌂ ☉)╝ ls
ABOUT yasmin_file zac_file jonathan_file brendan_file sebastion_file uliana_file aladar_file munya_file hsh
```

### Non-Interactive Mode
```bash
school@holbertonschool-simple-shell:/# echo "ls" | ./hsh
ABOUT yasmin_file zac_file jonathan_file brendan_file sebastion_file uliana_file aladar_file munya_file hsh
```

### Misc

If a command cannot be found, `hsh` prints an error similar to `sh`:

```
./hsh: 1: <command>: not found
```

or, if a path was given ('/'):

```
./hsh: 1: <command>: No such file or directory
```

## Testing

Run the included test script to compile the project and compare `hsh`'s behavior against the system `sh` across several scenarios (valid commands, invalid commands, absolute paths, empty input, whitespace-only input, and `exit`):

```bash
./tests
```

## Limitations

- Piping is not an added feature.
- Limited built-in commands.
- Cannot access previous commands via cursor.
- Cannot use special characters E.g. `ls *.c` results in an error.
- Cannot use arguments when starting shell.
- Signals are not handled properly.

## Author(s)

- Munyaradzi Murare — mmurare@yahoo.com.au
- Yasmin So — yasmin@yasmin.so

This project was created for educational purposes as part of the Holberton School curriculum.
