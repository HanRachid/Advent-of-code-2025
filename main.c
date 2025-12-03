#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"kernel32.lib")
typedef int(*day_fn)(void);

int day1(void);
int day2(void);
int day3(void);

int main(void)
{
    day_fn days[] = {day1,day2,day3};
    for (int i = 0; i<sizeof(days)/sizeof(days[0]); i++){
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency(&qpf);
    LARGE_INTEGER before;
    QueryPerformanceCounter(&before); 
    days[i]();
    LARGE_INTEGER after;
    QueryPerformanceCounter(&after);
    double result = (double)(after.QuadPart - before.QuadPart)*1000/qpf.QuadPart;
    printf("temps pour jour %d : %.2f ms\n",i+1,result);
    }
    
    
}