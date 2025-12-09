#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../main.h"


int day7(void)
{
    Buffer buffer = read_entire_file("./Day7/day7_ex.txt");
    Dimension dimension = get_dimension(buffer);
    print_buffer(buffer);
    uint64_t ptr = 0;
    return 0;
}