#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sched.h>
#define N 100000
int main(){
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    sched_setaffinity(0, sizeof(set), &set);

    char a = 'a';
    pid_t pid = fork();
    if(pid < 0) return 1;
    else if(pid == 0) {
        for (int i = 0; i < N; i++) {
            read(p1[0], &a, sizeof(a));
            write(p2[1], &a, sizeof(a));
        }
    } else {
        struct timeval before, after;
        gettimeofday(&before, NULL);
        for (int i = 0; i < N; i++) {
            write(p1[1], &a, sizeof(a));
            read(p2[0], &a, sizeof(a));
        }
        gettimeofday(&after, NULL);
        double total = (after.tv_sec - before.tv_sec) * 1e6 + (after.tv_usec - before.tv_usec);

        printf("Total time: %.2f us\n", total);
        printf("Average per context switch: %.4f us\n", total / (2 * N));
        return 0;
    }
}

/*
Result: 
    Total time: 397904.00 us
    Average per context switch: 1.9895 us
*/

/*
Note:
    - Both processes must be pinned to the same CPU core to ensure that real context switches occur
    - Each loop causes two context switches:
        1) Parent → Child
        2) Child → Parent
      So the total measured time should be divided by (2 * N)
*/