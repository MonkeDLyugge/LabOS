#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "fcntl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>                    

float sum(float* array) {
    return array[0] + array[1] + array[2];
}

int main(int argc, char** argv) {    
    int firstPipe = open("firstPipe", O_RDONLY);
    int secondPipe = open("secondPipe", O_WRONLY);
    if (argc < 2) {
        // Missing some arguments
        return -1;
    }
    if (firstPipe == -1 || secondPipe == -1) {
        // Opening pipes error
        return -1;
    }
    unlink(argv[1]);
    int fd = open(argv[1], O_CREAT | O_WRONLY, S_IREAD | S_IWRITE); 
    if (fd == -1) {
        // Opening file error
        return -1;
    }

    float* array = {};
    size_t n = 0;
    int s = read(firstPipe, array, n);
    
    float ans = 0;
    char* ansStr = {};

    while (s > 0) {
        ans = sum(array);
        sprintf(ansStr, "%f\n", ans);
        if (write(fd, ansStr, sizeof(float)) == -1) {
            // Writing sum to file from child error
            return -1;
        }
        s = read(firstPipe, array, n);
    } 
    close(firstPipe);
    close(secondPipe);
    close(fd);
    return 0;
}