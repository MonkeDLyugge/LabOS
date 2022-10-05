// Parent process would provide data collecting and transmission to the child process
#include <cstdlib>
#include <iostream>

#include "unistd.h"
#include "stdio.h"
#include "sys/stat.h"
#include "sys/wait.h"
#include "fcntl.h"

#include "../include/parent.hpp"

int parentProcess(FILE* standartInput) {
    // The entry point to the parent process

    // If last execution complited with no closing/deleting pipes
    unlink("firstPipe");
    unlink("secondPipe");

    // Creating new pipes
    if (mkfifo("firstPipe", S_IREAD | S_IWRITE) == -1 || mkfifo("secondPipe", S_IREAD | S_IWRITE) == -1) {
        // Creating pipes error
        return -1;
    }
    
    size_t n = 0;
    char* fileName;

    // Reading file name
    int charactersCount = getline(&fileName, &n, standartInput);

    if (charactersCount <= 0) {
        // Reading file name error
        return -1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        // Fork error
        return -1;
    }
    if (pid != 0) {
        // Opening pipes
        int firstPipe = open("firstPipe", O_WRONLY);
        int secondPipe = open("secondPipe", O_RDONLY);
        if (firstPipe == -1 || secondPipe == -1) {
            // Opening pipes error
            return -1;
        }

        char* str = nullptr;
        size_t k = 0;

        charactersCount = getline(&str, &k, standartInput);
        while (charactersCount > 0) {
            if (write(firstPipe, str, charactersCount) == -1) {
                // Sending data from parent process error
                return -1;
            }
            free(str);
            k = 0;
            charactersCount = getline(&str, &k, standartInput);
        }

        // Closing/deleting pipes
        wait(nullptr);
        close(firstPipe);
        close(secondPipe);
        unlink("firstPipe");
        unlink("secondPipe");
    } else {
        // Deleting \n from file name
        fileName[charactersCount - 1] = '\0';

        char* argv[3];
        sprintf(argv[0], "%s", "child.cpp");
        argv[1] = fileName;
        argv[2] = nullptr;

        return execv("child", argv);
    }
    return 0;
}