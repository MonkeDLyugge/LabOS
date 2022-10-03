#include "unistd.h"
// First process would provides data collecting and transmission to the second process

#include "stdio.h"
#include "sys/stat.h"
#include "fcntl.h"

#include "parent.hpp"

int parentProcess(FILE* file) {
    // The entry point to the parent process
}