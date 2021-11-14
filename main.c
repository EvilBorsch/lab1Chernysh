#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitmap.h"

#define OCCUPIED 1
#define NOT_OCCUPIED 0


void printCurrentEl(const uint16_t *current) {
    printf("Current el index: {%d}", *current);

}

char *dimaMalloc(char *buffer, bitmap_t *bitMap, uint16_t *currentEl, uint16_t size, const uint16_t bufferSize) {
    uint16_t countHoles = 0;
    printCurrentEl(currentEl);

    if (*currentEl >= bufferSize - 1) {
        *currentEl = 0;
        printf("\n");
        printf("Going to start: {%d}", *currentEl);

    }
    uint16_t endMallocPosition = 0;
    for (uint16_t i = *currentEl; i < bufferSize; i++) {

        if (getbit(bitMap, i) == NOT_OCCUPIED) {
            countHoles++;
        } else {
            countHoles = 0;
        }
        if (countHoles == size) {
            endMallocPosition = i;
            uint16_t startMallocPosition = endMallocPosition + 1 - size;
            for (uint16_t j = endMallocPosition; j > startMallocPosition; j--) {
                putbit(bitMap, j, OCCUPIED);
            }
            putbit(bitMap,startMallocPosition,OCCUPIED);
            *currentEl = endMallocPosition;
            return &buffer[startMallocPosition];
        }
    }
    return NULL;
}

void dimaFree(bitmap_t *bitMap, uint16_t from, uint16_t size) {
    for (uint16_t i = from; i < from + size; i++) {
        putbit(bitMap,i,NOT_OCCUPIED);
    }
}


void showArray(char *arr, uint16_t size) {
    printf("\n");
    for (uint16_t i = 0; i < size; i++) {
        printf("[%c] ", arr[i]);
    }
}


void showBitArray(const bitmap_t *arr, uint16_t size) {
    printf("\n");
    for (uint16_t i = 0; i < size; i++) {
        printf("[%c] ", getbit(arr, i));
    }
}


int main() {


    //////////////// init ///////////////////////
    const uint16_t buffSize = 20;
    uint16_t currentEl = 0;
    char *buffer = malloc(sizeof(char) * buffSize);

    bitmap_t bitMap[RESERVE_BITS(buffSize)];
    for (int i = 0; i < buffSize; i++) {
        putbit(bitMap, i, NOT_OCCUPIED);
    }

    printf("Data after initialization:");
    showArray(buffer, buffSize);
    showBitArray(bitMap, buffSize);
    printf("\n\n");
    ////////////////////////////////////////////////

    //////////// tests ///////////////////
    char *res = dimaMalloc(buffer, bitMap, &currentEl, 10, buffSize);
    for (int i = 0; i < 5; i++) {
        res[i] = 'a';
    }
    showArray(buffer, buffSize);
    showBitArray(bitMap, buffSize);
    printf("\n\n");
    char *res2 = dimaMalloc(buffer, bitMap, &currentEl, 3, buffSize);
    for (int i = 0; i < 3; i++) {
        res2[i] = 'b';
    }
    showArray(buffer, buffSize);
    showBitArray(bitMap, buffSize);
    printf("\n\n");
    char *res3 = dimaMalloc(buffer, bitMap, &currentEl, 7, buffSize);
    for (int i = 0; i < 7; i++) {
        res3[i] = 'q';
    }
    showArray(buffer, buffSize);
    showBitArray(bitMap, buffSize);
    printf("\n\n");

    printf("Free from 5 index 4 bytes");
    dimaFree(bitMap, 5, 4);
    showArray(buffer, buffSize);
    showBitArray(bitMap, buffSize);
    printf("\n\n");

    char *res4 = dimaMalloc(buffer, bitMap, &currentEl, 2, buffSize);
    for (int i = 0; i < 2; i++) {
        res4[i] = 'w';
    }
    showArray(buffer, buffSize);
    showBitArray(bitMap, buffSize);
    printf("\n\n");

    //////////////////////////////////////
    return 0;
}
