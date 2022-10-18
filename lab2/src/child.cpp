#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "fcntl.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>                    

int main(int argc, char* argv[]) {    
    int pipe = open("pipe", O_RDONLY);
    if (argc < 2) {
        // Missing some arguments
        return -1;
    }
    if (pipe == -1) {
        // Opening pipe error
        return -1;
    }
    unlink(argv[1]);
    int fd = open(argv[1], O_CREAT | O_WRONLY, S_IREAD | S_IWRITE); 
    if (fd == -1) {
        // Opening file error
        return -1;
    }

    if (dup2(pipe, 0) == -1 || dup2(fd, 1) == -1) {
        // Dup2 error
        return -1;
    }

    float ans = 0;
    
    float num;

    while (std::cin >> num) {      
        ans += num;
    }

    printf("%.3f", ans);

    close(pipe);
    close(fd);
}