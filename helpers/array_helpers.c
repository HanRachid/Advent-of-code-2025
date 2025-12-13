#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "../main.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}


Buffer read_entire_file(char *filepath){
    FILE *stream;
    stream = fopen(filepath, "r");
    if (stream == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        exit(1);
    }

    fseek(stream, 0, SEEK_END);
    int64_t size = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    char *buffer = (char *)malloc(size+1);
    buffer[size] = '\0';
    fread(buffer, size, 1, stream);
    Buffer buf;
    buf.data = buffer;
    buf.size = size;
    return buf;
}

Dimension get_dimension(Buffer buffer){
    int64_t ptr = 0;
    int64_t height = 0;
    int64_t width = 0;
    Dimension dimension;
    while (buffer.data[ptr] != '\n'){
        width++,ptr++;
    }
    width++;
    ptr = 0;
    while (ptr < buffer.size){
       if (buffer.data[ptr] == '\n')height++;
       ptr++;
    }
    dimension.height = height;
    dimension.width =  width;

    return dimension;
}

void print_buffer(Buffer buffer){
    int64_t i;
    for (i=0;i<buffer.size;i++){
        printf("%c",buffer.data[i]);
    }
    printf("\n");
}
