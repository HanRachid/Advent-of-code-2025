#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int64_t count_digits(int64_t n) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

int check_divisibility_combinations(int64_t n, int digits){

    if(digits == 2){
        if(n%11==0){
            return 1;
        }
    }else if (digits == 3){
        if(n%111==0){
            return 1;
        }
    }else if (digits == 5){
        if(n%11111==0){
            return 1;
        }
    }else if (digits == 6){
        if(n%10101==0){
            return 1;
        }
    }else if (digits == 7){
        if(n%1111111==0){
            return 1;
        }
    }else if (digits == 9){
        if(n%111111111==0||n%1001001==0||n%1010101==0){
            return 1;
        }
    }else if (digits == 10){
        if(n%1111111111==0||n%101010101==0){
            return 1;
        }
    }
   
    return 0;
}

int64_t pow(int64_t n, int pow){
    int i;
    int64_t mul = 1;
    for (int i = 0; i < pow ; i++) mul*=n;
    return mul;
}

int day2(void) {
    FILE *stream;
    int32_t n;
    fopen_s(&stream, "./Day2/day2.txt", "r");
    if (stream==NULL) {
        return 1;
    }
    fseek(stream,0,SEEK_END);
    int64_t size = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    char *buffer = (char *)malloc(size+1);
    buffer[size] = '\0';
    fread(buffer, size, 1, stream);
    
    int ptr = 0;
    int ptr_first = 0;
    int ptr_last = 0;
    char current_range_start[30]={0};
    char current_range_last[30]={0};
    int is_first = 1;
    int64_t i;
    int64_t sum_1 = 0;
    int64_t sum_2 = 0;
    int64_t current_id;
    while (1){
        if (buffer[ptr] == ','|| buffer[ptr] == '\0'){
            for (i = _atoi64(current_range_start); i <= _atoi64(current_range_last) ; i++){
                
                if ((i%(1+(pow(10,count_digits(i)/2))))==0 && count_digits(i)%2==0){
                    sum_1+=i;
                    sum_2+=i;
                    fflush(stdout);
                }else if(check_divisibility_combinations(i,count_digits(i))){
                    sum_2+=i;
                }

            }
            if (buffer[ptr] == '\0') break;
            ptr_first = 0;
            ptr_last = 0;
            memset(current_range_start, 0, 30);
            memset(current_range_last, 0, 30);
            is_first=1;
        }
        else if (buffer[ptr] == '-'){
            is_first = 0;
        } else{
            if (is_first){
                current_range_start[ptr_first++] = buffer[ptr];
            }
            else{
                current_range_last[ptr_last++] = buffer[ptr];
            }
        }
       
        ptr++;
        
    }
    printf("day 2 part 1 : %lld\n", sum_1);
    printf("day 2 part 2 : %lld\n", sum_2);
    fclose(stream);
    return 0;
}