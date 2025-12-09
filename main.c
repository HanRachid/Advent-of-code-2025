#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"kernel32.lib")
typedef int(*day_fn)(void);
#include "main.h"


int main(void)
{
    day_fn days[] = {/* day1, day2, day3, day4, day5, day6, */ day7};

    for (int i = 0; i<sizeof(days)/sizeof(days[0]); i++){
        LARGE_INTEGER qpf;
        QueryPerformanceFrequency(&qpf);
        LARGE_INTEGER before;
        QueryPerformanceCounter(&before); 
        days[i]();
        LARGE_INTEGER after;
        QueryPerformanceCounter(&after);
        double result = (double)(after.QuadPart - before.QuadPart)*1000.0/qpf.QuadPart;
        printf("temps pour jour %d : %.4f ms\n",i+1,result);
    }
}