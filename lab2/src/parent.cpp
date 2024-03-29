// Parent process would provide data collecting and transmission to the child process
#include <cstdlib>
#include <iostream>

#include "unistd.h"
#include "stdio.h"
#include "sys/stat.h"
#include "sys/wait.h"
#include "fcntl.h"

#include "parent.hpp"

int ParentProcess(FILE* standartInput, const std::string& path) {
    // The entry point to the parent process

    // If last execution complited with no closing/deleting pipe
    unlink("pipe");

    // Creating new pipes
    if (mkfifo("pipe", S_IREAD | S_IWRITE) == -1) {
        // Creating pipe error
        perror("file didnt create");
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

    int pid = fork();
    if (pid == -1) {
        // Fork error
        return -1;
    }
    if (pid != 0) {
        // Opening pipe
        int pipe = open("pipe", O_WRONLY);

        if (pipe == -1) {
            // Opening pipe error
            return -1;
        }

        char* str = nullptr;
        size_t k = 0;

        charactersCount = getline(&str, &k, standartInput);
        while (charactersCount > 0) {
            if (write(pipe, str, charactersCount) == -1) {
                // Sending data from parent process error
                return -1;
            }
            free(str);
            str = nullptr;
            charactersCount = getline(&str, &k, standartInput);
        }

        // Closing/deleting pipe
        close(pipe);
        wait(NULL);
    } else {
        // Deleting \n from file name
        fileName[charactersCount - 1] = '\0';
        
        int pipe = open("pipe", O_RDONLY);

        dup2(pipe, 0);

        char* argv[3];
        sprintf(argv[0], "%s", "child.cpp");
        argv[1] = fileName;
        argv[2] = NULL;

        return execv(path.c_str(), argv);
    }
    return 0;
}
