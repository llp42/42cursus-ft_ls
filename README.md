*This project has been created as part of the 42 curriculum by lepereir.*

# ft_ls

## Description

A recode of the system's `ls` command in C: list directory contents with the
same behavior as the original, including the `-l`, `-R`, `-a`, `-r` and `-t`
options, plus the bonus `-u`, `-f`, `-g`, `-d` and `-G`. The program walks the
file system with the POSIX directory and stat
APIs — permissions, owners, sizes, dates and all — and must never crash, leak,
or lose information relative to the real `ls`.

## Instructions

```bash
make all     # compile (default target)
make clean   # remove the object files
make fclean  # remove the object files and the binary
make re      # fclean, then all
```

Only a C compiler and the standard library are needed. Builds with
`-Wall -Wextra -Werror`.

```console
$ ./ft_ls            # list the current directory
$ ./ft_ls -lR src    # long format, recursive, on src/
```

## Options

| Option | Description                                      |
|--------|--------------------------------------------------|
| `-l`   | Long listing format                              |
| `-R`   | List subdirectories recursively                  |
| `-a`   | Include entries whose names start with a dot     |
| `-r`   | Reverse the sort order                           |
| `-t`   | Sort by modification time, newest first          |
| `-u`   | Sort and show access time instead of mtime       |
| `-f`   | Unsorted output, implies `-a`                    |
| `-g`   | Like `-l` without the owner, implies `-l`        |
| `-d`   | List directory operands, not their contents      |
| `-G`   | Colorize the output                              |

## Author

Leonardo Lopes Pereira <lepereir@student.42.fr>
