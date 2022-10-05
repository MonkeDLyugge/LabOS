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

    if (dup2(firstPipe, 0) == -1 || dup2(fd, 1) == -1) {
        // Dup2 error
        return -1;
    }

    float ans = 0;
    
    float num;

    while (std::cin >> num) {      
        ans += num;
    }

    printf("%f", ans);

    close(firstPipe);
    close(secondPipe);
    close(fd);
    return 0;
}