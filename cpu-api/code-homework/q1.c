#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
    int x = 100;
    pid_t pid = fork();

    if (pid < 0) {
        printf("Error\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child before change: x = %d\n", x);
        x = 200;
        printf("Child after change:  x = %d\n", x);
    } else {
        // Parent process
        printf("Parent before change: x = %d\n", x);
        x = 300;
        printf("Parent after change:  x = %d\n", x);;
    }

    return 0;
}


/*
Note:
- After fork(), the value of x in the child process is copied from the parent.
- When both processes modify x, each sees a different value.
  => This shows that the parent and child have separate memory spaces
     (each has its own copy of x, stored at different memory addresses).
*/
