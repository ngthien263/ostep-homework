#include "stdio.h"
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#define N 100000
#define FILE_NAME "test.txt"

int main() {
    struct timeval before;
    struct timeval after;
    char s[10];
    int fd = open(FILE_NAME, O_CREAT | O_RDONLY | O_APPEND, 0666);
    if(fd < 0) {perror("open"); return 1;}
    gettimeofday(&before, NULL);
    for(int i = 0; i < N; i++)
        read(fd, s, 0);             //read 0 byte to measure system call time cost
    gettimeofday(&after, NULL);
    close(fd);

    double total = (after.tv_sec - before.tv_sec) * 1e6 + (after.tv_usec - before.tv_usec);

    printf("Total time: %.2f us\n", total);
    printf("Time per call: %.2f us\n", total / N);
    return 0;
}


/*  
Result: 
    Total time: 19161.00 us
    Time per call: 0.19 us
*/