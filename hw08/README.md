#### 8.9
| Process pair | Concurrent? |
| :----------: | :---------: |
|      AB      |      N      |
|      AC      |      Y      |
|      AD      |      Y      |
|      BC      |      Y      |
|      BD      |      Y      |
|      CD      |      Y      |

#### 8.10
A. `execve`

B. `unsetenv`

C. `getenv`

(`setenv` returns 0 if OK; returns -1 on error.)

#### 8.11
In this example, the number of times "Example" is printed is 2<sup>3</sup> = 8, due to the way fork() creates new processes at each iteration of the loop, and each of these processes also goes through the loop.

Visualization:
```
1st iteration: P (Parent)
               |
               C (Child created by fork)

2nd iteration: P       C
              / \     / \
             P   C   C   C

3rd iteration: P       C       C       C
              / \     / \     / \     / \
             P   C   C   C   C   C   C   C
```


#### 8.12
##### Initial Call to `try()`
1. `main()` calls `try()`.
2. Inside `try()`, the first `Fork()` is called, creating one child process. So, we have:
   - Parent (P1)
   - Child (C1)
   Both P1 and C1 will print "Example" once after the first `Fork()`.
3. Then, the second `Fork()` is called inside `try()`, creating a new child process for both P1 and C1. So, we have:
   - Parent (P1)
   - Child of Parent (C1)
   - Child of P1 (C2)
   - Child of C1 (C3)
   All four processes (P1, C1, C2, C3) will print "Example" once after the second `Fork()`.

Visualization after `try()`:
```
P1
| \
C1 C2
| 
C3
```
Each of the four processes has printed "Example" once, totaling 4 prints.

##### Call to `Fork()` in `main()`
4. After returning from `try()`, `main()` calls `Fork()`, creating a new child process for each of the four existing processes. So, we have:
   - Original Parent (P1)
   - Child of Parent (C1)
   - Child of P1 (C2)
   - Child of C1 (C3)
   - Child of P1 due to `Fork()` in `main()` (C4)
   - Child of C1 due to `Fork()` in `main()` (C5)
   - Child of C2 due to `Fork()` in `main()` (C6)
   - Child of C3 due to `Fork()` in `main()` (C7)

Visualization after `Fork()` in `main()`:
```
    P1
   /| \
  C1 C2 C4
 /|   | \
C3 C5 C6 C7
```
Each of the eight processes will print "Example" once after the `Fork()` in `main()`, totaling 8 prints.

### Total Prints:
- 4 prints from the `try()` function.
- 8 prints from the `main()` function after the `try()` function.

So, the total number of "Example" printed is 4 + 8 = 12.

#### 8.13
The child executes both `printf` statements. After the `fork` returns, it executes the `printf` in line 8. Then it falls out of the `if` statement and executes the `printf` in line 10. Here is one possible output produced by the program:\
a = 6<br/> a = 4<br/> a = 5<br/>

#### 8.14
##### Initial Call to `try()`
1. `main()` calls `try()`.
2. Inside `try()`, the first `Fork()` is called, creating one child process. So, we have:
   - Parent (P1)
   - Child (C1)

3. The `if (Fork() != 0)` condition checks whether the process is a child  or a parent.
   - For P1, the condition is true, so it calls another `Fork()`, creating a new child (C2), and both P1 and C2 print "Example" and then exit.
   - For C1, the condition is false, so it returns from `try()` without printing "Example`.

Visualization after `try()`:
```
P1 (Exited)
| \
C1 C2 (Exited)
```
So far, "Example" has been printed 2 times.

##### Call to `fork()` in `main()`
4. After returning from `try()`, `main()` calls `fork()`, creating a new child process for C1. So, we have:
   - Original Child (C1)
   - Child of C1 due to `fork()` in `main()` (C3)

Visualization after `fork()` in `main()`:
```
C1
| 
C3
```
Both C1 and C3 will print "Example" once after the `fork()` in `main()`, totaling 2 prints.

### Total Prints:
- 2 prints from the `try()` function.
- 2 prints from the `main()` function after the `try()` function.

So, the total number of "Example" printed is 2 + 2 = 4.

#### 8.15
##### Initial Call to `try()`
1. `main()` calls `try()`.
2. Inside `try()`, the first `Fork()` is called, creating one child process. So, we have:
   - Parent (P1)
   - Child (C1)

3. The `if (Fork() == 0)` condition is true for the child process (C1) because `Fork()` returns 0 to the child process. So, C1 will execute the inner block of the `if` statement, and P1 will skip it and return to `main()`.

4. Inside the `if` block, C1 calls `Fork()` twice, creating three more child processes. So, we have:
   - Original Child (C1)
   - Child of C1 (C2)
   - Child of C1 (C3)
   - Child of C1 (C4)

Visualization after `try()`:
```
    P1 (Continues in main)
    |
    C1
   /| \
  C2 C3 C4
```

Each of the four processes (C1, C2, C3, C4) has printed "Example" once, totaling 4 prints.

##### Call to `printf()` in `main()`
5. After returning from `try()`, all five processes (P1, C1, C2, C3, C4) will continue to execute the `main()` function and will call `printf("Example\n");`.

Total Prints:
- 4 prints from the child processes created in the `try()` function.
- 5 prints from all processes (P1, C1, C2, C3, C4) in the `main()` function after the `try()` function.

So, the corrected total number of "Example" printed is 4 + 5 = 9.

#### 8.16
1. The program initializes a global variable `counter` with a value of 1.

2. The `main()` function calls `fork()`. This creates a child process.

3. The child process checks the condition `(fork() == 0)`, which is true for the child. So, the child process increments the `counter` by 1. Now, in the child's memory space, `counter` becomes 2. The child process then exits.

4. The parent process checks the condition `(fork() == 0)`, which is false for the parent. So, it goes to the `else` block. The parent waits for the child process to finish using `Wait(NULL)`.

5. After the child process has finished, the parent process increments the `counter` by 1. Since the parent process has its own memory space (separate from the child), the original value of `counter` in the parent's memory space is still 1. After incrementing, `counter` becomes 2 in the parent's memory space.

6. The parent process then prints the value of `counter`, which is 2.

So, the output of the program is `counter = 2`.

#### 8.17
Any output sequence corresponding to a topological sort of the graph is possible.
```
1. Start, 0, 1, Child, Stop, 2, Stop
2. Start, 1, 0, Child, Stop, 2, Stop
3. Start, 0, Child, Stop, 1, 2, Stop
4. Start, 0, Child, 1, Stop, 2, Stop
```

#### 8.18

##### Process Tree Visualization:
```
    P (Parent)
   / \
  C1  P
 /|   |\
C3 C1 P C2
```

- P is the original parent process.
- C1 is the child process created by the first `Fork()`.
- C3 and another C1 are the child processes created by the second `Fork()` in C1.
- P and C2 are the processes created by the second `Fork()` in the original parent.

1. The first `Fork()` is called.
   - Parent and Child1 are created.
   - Child1 registers `end()` to be called at exit.
   
2. The second `Fork()` is called.
   - Parent creates Child2.
   - Child1 creates Child3.
   - Child2 and Child3 print `0`.
   - Parent and Child1 print `1`.

3. The `exit(0)` is called.
   - For Child1, the `end()` function is also called, printing `2`.

So, the possible sequences of printing are:
- Parent: `1`
- Child1: `12` (1 from the second `Fork()`, and 2 from the `end()` function)
- Child2: `0`
- Child3: `02` (the same as the above)

So, the possible outputs from the given list are A, C and E.

#### 8.19
2<sup>3</sup> = 8

Loop Iterations:
- Iteration 1: `i = 5`, `Fork()` is called.
- Iteration 2: `i = 3`, `Fork()` is called.
- Iteration 3: `i = 1`, `Fork()` is called.

Visualization:
```
    P
   / \
  C1  P
 / \ / \
C2 C1 C3 P
   / \ / \
  C2 C1 C3 C4
```

#### 8.20
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    // The path to the ls program
    char *path = "/bin/ls";

    // If COLUMNS environment variable is unset, set it to 80
    if (getenv("COLUMNS") == NULL) {
        setenv("COLUMNS", "80", 1);
    }

    // Execute the ls program with the given arguments and environment variables
    if (execve(path, argv, envp) == -1) {
        perror("execve");
        exit(1);
    }

    // This line will never be reached if execve is successful
    return 0;
}
```

#### 8.21
1. The `main()` function starts by printing "p".
2. It then calls `fork()`, creating a child process.
3. If the process is the parent, it prints "q" and returns, thus exiting.
4. If the process is the child, it prints "r" and waits for the parent to finish.

Visualization:
```
    P (prints "p", then "q", then exits)
   / 
  C (prints "r", then waits for P to exit)
```

Given the sequence of operations, the possible output sequences from the given program are "pqr" and "prq".

#### 8.22
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int mysystem(char *command) {
    pid_t pid;
    int status;

    if (command == NULL)
      return 1;

    if ((pid = fork()) < 0) {
        // fork failed
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        char *argv[] = {"/bin/sh", "-c", command, NULL};
        extern char **environ;
        if (execve(argv[0], argv, environ) < 0) {
            // execve failed
            perror("execve");
            exit(1);
        }
    } else {
        // Parent process
        if (waitpid(pid, &status, 0) < 0) {
            // waitpid failed
            perror("waitpid");
            exit(1);
        }
        if (WIFEXITED(status)) {
            // Child exited normally
            return WEXITSTATUS(status);
        } else {
            return -1;
        }
    }

    return -1;
}

int main() {
    int ret = mysystem("ls -l");
    printf("mysystem returned: %d\n", ret);
    return 0;
}
```

#### 8.23
The issue in this program is related to the fact that signals of the same type are not queued in most Unix systems. If a signal of type k is already pending for a process, and another signal of type k is delivered to the process, the second signal is typically discarded. This is known as signal coalescing.

**Detailed Explanation:**\
In the given program, the child process is sending SIGUSR2 signals to the parent process in a loop. The parent process has a signal handler for SIGUSR2 that increments a global counter variable and then sleeps for 1 second.

Since the child process is sending signals in quick succession, and the handler in the parent takes 1 second to handle each signal, subsequent signals arrive while the previous one is still pending or being handled. Due to signal coalescing, these subsequent signals are discarded, and as a result, the counter variable does not get incremented for every signal sent by the child.

#### 8.24
Original program:
```c
#include "csapp.h"
#define N 2

int main()
{
	int status, i;
	pid_t pid;

	/* Parent creates N children */
	for (i = 0; i < N; i++)
		if ((pid = Fork()) == 0) /* Child */
			exit(100 + i);

	/* Parent reaps N children in no particular order */
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally\n", pid);
	}

	/* The only normal termination is if there are no more children */
	if (errno != ECHILD)
		unix_error("waitpid error");

	exit(0);
}
```
To meet the conditions, we need to modify the child process to perform an illegal memory write, causing a segmentation fault, and then modify the parent process to print the appropriate message using `psignal`.

Modified program:
```c
#include "csapp.h"
#include <signal.h> // For psignal
#define N 2

int main() {
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)
        if ((pid = Fork()) == 0) { /* Child */
            /* Attempt to write to a location in the read-only text segment */
            *((int *)main) = 0;
            exit(100 + i);
        }

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        else if (WIFSIGNALED(status)) {
            printf("child %d terminated by signal %d: ", pid, WTERMSIG(status));
            psignal(WTERMSIG(status), "Segmentation fault"); // Use psignal to print the description of the signal
            printf("\n");
        }
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}
```

#### 8.25
Run the command ```gcc tfgets.c -o tfgets```

#### 8.26
Run the command ```gcc -o tish tish.c csapp.c -lpthread```