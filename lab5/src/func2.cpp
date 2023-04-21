#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/lab5.hpp"

int Compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void CharSwap(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

char* Translation(long x){
    void* str = malloc(sizeof(int)*8);
    int p = 0;

    while(x > 0){
        ((char*)str)[p] = '0' + x % 3;
        x = x / 3;
        p++;
    }
    
    ((char*)str)[p] = '\0';
    int i = 0;

    while(i < p){
        p--;
        CharSwap((char*)str + i, (char*)str + p);
        i++;
        
    }

    return (char*)str;   
}

void Sort(int* array, unsigned long size) {
    qsort(array, size, sizeof(int), Compare);
}