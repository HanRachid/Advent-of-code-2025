#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../main.h"


int day5(void)
{
    Buffer buffer = read_entire_file("./Day5/day5.txt");
    uint64_t rangeptr = 0;
    while (!(buffer.data[rangeptr] == '\n' && buffer.data[rangeptr + 1] == '\n'))
    {
        rangeptr++;
    }
    uint64_t firstpartend = rangeptr;
    
    int max_ranges = 1000;
    Range *ranges = (Range*)malloc(max_ranges * sizeof(Range));
    int range_count = 0;
    rangeptr = 0;
    
    while (rangeptr < firstpartend)
    {
        int64_t start = 0, end = 0;
        
        while (buffer.data[rangeptr] != '-')
        {
            start = start * 10 + buffer.data[rangeptr] - '0';
            rangeptr++;
        }
        rangeptr++;
        
        while (buffer.data[rangeptr] != '\n')
        {
            end = end * 10 + buffer.data[rangeptr] - '0';
            rangeptr++;
        }
        rangeptr++;
        
        ranges[range_count].start = start;
        ranges[range_count].end = end;
        range_count++;
    }
    
    clock_t start_time = clock();
    
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < range_count; i++)
        {
            if (ranges[i].start == -1) continue;
            
            for (int j = i + 1; j < range_count; j++)
            {
                if (ranges[j].start == -1) continue;
                
                int64_t s1 = ranges[i].start, e1 = ranges[i].end;
                int64_t s2 = ranges[j].start, e2 = ranges[j].end;
                
                if (s1 <= s2 && e1 >= e2)
                {
                    ranges[j].start = -1;
                    changed = 1;
                }
                else if (s2 <= s1 && e2 >= e1)
                {
                    ranges[i].start = s2;
                    ranges[i].end = e2;
                    ranges[j].start = -1;
                    changed = 1;
                }
                else if (s1 <= e2 && e1 >= s2)
                {
                    ranges[i].start = (s1 < s2) ? s1 : s2;
                    ranges[i].end = (e1 > e2) ? e1 : e2;
                    ranges[j].start = -1;
                    changed = 1;
                }
            }
        }
    }
    
    uint64_t countfreshsecond = 0;
    for (int i = 0; i < range_count; i++)
    {
        if (ranges[i].start != -1)
        {
            countfreshsecond += (ranges[i].end - ranges[i].start + 1);
        }
    }
    
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
    
    printf("\nfreshsecond: %lld (took %.3f ms)\n", countfreshsecond, time_taken);
    
    free(ranges);
    free(buffer.data);
    return 0;
}