#include "stdio.h"
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <x86intrin.h>
#include <stdint.h>

#define N 100000
#define FILE_NAME "test.txt"

//calculate the frequency of the CPU in GHz
double calculate_cpu_freq(){
    uint64_t start = __rdtsc();
    sleep(1);
    uint64_t end = __rdtsc();
    return (end - start) / 1e9; //GHz
}

int main() {
    struct timeval before;
    struct timeval after;
    uint64_t start, end;
    char s[10];
    int fd = open(FILE_NAME, O_CREAT | O_RDONLY | O_APPEND, 0666);
    if(fd < 0) {perror("open"); return 1;}
    start = __rdtsc();
    for(int i = 0; i < N; i++)
        read(fd, s, 0);             //read 0 byte to measure system call time cost
    end = __rdtsc();
    close(fd);

    uint64_t total_cycles = end - start;
    double total_time = (total_cycles * 1.0) / (calculate_cpu_freq() * 1000);    //us
    printf("Total cycle: %ld\n", total_cycles);
    printf("Total time: %.6f us\n", total_time);
    printf("Time per call: %.6f us\n", total_time / N);
    return 0;
}


/*  
Result: 
    Total cycle: 57302043
    Total time: 19759.325172 us
    Time per call: 0.197593 us
*/

/*
Note:
    - __rdtsc() macro returns the number of clock cycles since the system starts
    so it needs to be divided by the CPU freq to calculate the time cost
    - Formula: time = cycle / CPU_Freq (ns)
*/