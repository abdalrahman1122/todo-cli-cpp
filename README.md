# Todo-CLI-CPP

A simple command-line task manager written in C++17. Tasks are saved in a text file, so they are still there the next time you run the program.

## Commands
```bash
./todo add Buy milk      # add a task
./todo list              # show all tasks
./todo done 1            # mark task 1 as done
./todo delete 1          # delete task 1
```

## Example
```
$ ./todo add Study data structures
Added task 1
$ ./todo done 1
OK
$ ./todo list
1. [x] Study data structures
```

## Build
```bash
make
```

## How it works
- Tasks are stored in `tasks.txt`, one per line (`0|title` or `1|title`).
- Every command loads the file, changes the tasks in memory, and saves the file again.
- Invalid input (empty title, wrong task number) shows an error message.
