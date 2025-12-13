#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

typedef struct Buffer
{
    char *data;
    int64_t size;
} Buffer;

typedef struct Range {
    int64_t start;
    int64_t end;
} Range;

typedef struct Dimension {
  int64_t width;
  int64_t height;
} Dimension;

Buffer read_entire_file(char *filepath);
Dimension get_dimension(Buffer buffer);
void print_buffer(Buffer buffer);

int day1(void);
int day2(void);
int day3(void);
int day4(void);
int day5(void);
int day6(void);
int day7(void);

#endif 
