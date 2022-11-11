#include "parent.hpp"

#include <stdio.h>
#include <stdlib.h>

int main() {
    ParentProcess(stdin, "child.out");
    return 0;
}