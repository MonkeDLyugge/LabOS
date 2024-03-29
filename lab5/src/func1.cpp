#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lab5.hpp"

void IntSwap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
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
        ((char*) str)[p] = '0' + x % 2;
        x = x / 2;
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

    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = 0; j < size - 1; ++j) {
            if (array[j] > array[j + 1]) {
                IntSwap(array + j, array + j + 1);
            }
        }
    }
}