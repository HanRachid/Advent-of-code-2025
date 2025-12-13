#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int count_line_chars(char *buffer){
    int i = 0;
    while (buffer[i]!='\0' && buffer[i] != '\n' ){
        i++;
    }
    return i;
}

int64_t pow_10(int val, int pow){
    int i;
    int64_t result = val;
    for (i = 1; i<pow; i++){
        result = result*10;
    }
    return result;
}

int day3(void){
    FILE *stream;
    char buffer[256];
    stream = fopen("./Day3/day3_ex.txt", "r");
    int curr_max_ptr;
    int ptr;
    int curr_max;
    int64_t sum_1 = 0;
    int64_t sum_2 = 0;

    while (fgets(buffer, sizeof(buffer), stream))
    {
        ptr=0;
        curr_max_ptr=0;
        curr_max=(buffer[ptr++]  - '0');
        while(1){
            if(buffer[ptr+2] == '\0')break;
            if (curr_max<buffer[ptr]- '0'){
                curr_max = buffer[ptr] - '0';
                curr_max_ptr = ptr;
            }
            ptr++;
        }
        int i;
        int curr_second_max = buffer[curr_max_ptr+1] - '0';
        for(i=curr_max_ptr+1;i<ptr+1;i++){
            if (curr_second_max< buffer[i] - '0') curr_second_max = buffer[i] - '0';
        }
        sum_1+= curr_max*10 + curr_second_max;
    
        int j=0;
        int k;
        int current = 0;
        int ptr = 0; 
        int range_start = 0; 
        int range_end = 0; 
        int possible_values = 0;
        int buffer_size = count_line_chars(buffer);
        for (j = 0 ; j < 12; j++){
            current=0;
            possible_values = (buffer_size - range_start) - (11-j) ;
            range_end = range_start + possible_values;
            for (k = range_start; k < range_end; k++){
                if(current < buffer[k]  - '0'){
                    current = buffer[k]  - '0';
                    ptr = k;
                }
            }
            range_start = ptr+1;
            printf("%d",current);
            int64_t current_exp = pow_10(current,12-j);
            sum_2 = sum_2 +  current_exp; 
         }
            printf("\n");

    }
    printf("day 3 part 1 : %"PRId64"\n", sum_1);
    printf("day 3 part 2 : %"PRId64"\n", sum_2);


    fseek(stream, 0, SEEK_SET);
    fclose(stream);
    return 0;
}
