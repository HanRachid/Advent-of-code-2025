#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../main.h"
#include <inttypes.h>

int day6(void)
{
    Buffer buffer = read_entire_file("./Day6/day6_ex.txt");
    int64_t ptr = 0;
    int64_t height = 0;
    int64_t width = 0;
    while (buffer.data[ptr] != '\n'){
        width++,ptr++;
    }
    ptr = 0;
    while (ptr < buffer.size){
       if (buffer.data[ptr] == '\n')height++;
       ptr++;
    }

    int64_t operationptr = ptr ;
    
    while (buffer.data[operationptr] != '\n'){
        operationptr--;
    }
    operationptr++;
    int64_t operationptremp = operationptr ;
    int64_t i;
    int64_t currentvalue = 0;
    int64_t currenttotal = 0;
    int64_t total = 0;
    char currentoperation = '+';
    while (operationptr<buffer.size){
      for (i = 1; i <= height; i++){
        ptr = operationptr - (width+1)*(i);
        currentoperation = buffer.data[operationptr];
        if (currentoperation == '*' && currenttotal == 0)currenttotal = 1 ;
        while(buffer.data[ptr]==' ')ptr++;
        while(buffer.data[ptr]!=' ' && buffer.data[ptr] !='\n')currentvalue = currentvalue*10 + (buffer.data[ptr++] - '0');
        if(currentoperation=='*')currenttotal*=currentvalue;
        else currenttotal+=currentvalue;
       
      }
      currentvalue = 0;
        total+=currenttotal;
        currenttotal = 0;
        operationptr++;
        while (buffer.data[operationptr] == ' ')operationptr++;
    }
    printf(" total part 1 : %"PRId64"\n", total);
    
    // Part 2: Process column by column from right to left
    total = 0;
    int64_t col = width - 1; // Start from rightmost column index (0-based)
    
    while (col >= 0) {
        // Get operator at this column
        char op_at_col = buffer.data[operationptremp + col];
        
        // Skip space columns
        if (op_at_col == ' ') {
            col--;
            continue;
        }
        
        // Found an operator - this is a problem
        currentoperation = op_at_col;
        if (currentoperation == '*') currenttotal = 1;
        else currenttotal = 0;
        
        // Find the right boundary by checking data rows for digits
        int64_t prob_right = col;
        while (prob_right < width - 1) {
            int has_digit = 0;
            for (i = 1; i <= height; i++) {
                ptr = operationptremp + (prob_right + 1) - (width + 1) * i;
                if (buffer.data[ptr] >= '0' && buffer.data[ptr] <= '9') {
                    has_digit = 1;
                    break;
                }
            }
            if (!has_digit) break;
            prob_right++;
        }
        
        // Find the left boundary - look for separator column (all spaces including operator row)
        int64_t prob_left = col;
        while (prob_left > 0) {
            // Check if column to the left has ANY digit in data rows
            int has_content = 0;
            for (i = 1; i <= height; i++) {
                ptr = operationptremp + (prob_left - 1) - (width + 1) * i;
                if (buffer.data[ptr] >= '0' && buffer.data[ptr] <= '9') {
                    has_content = 1;
                    break;
                }
            }
            if (!has_content) break;
            prob_left--;
        }
        
        // Process each column in this problem from RIGHT to LEFT
        for (int64_t prob_col = prob_right; prob_col >= prob_left; prob_col--) {
            // Read DOWN this column (from TOP row to BOTTOM row)
            // height is number of newlines = number of data rows (operator row may not have newline)
            // i=height is the top row, i=1 is the bottom data row
            currentvalue = 0;
            for (i = height; i >= 1; i--) {
                ptr = operationptremp + prob_col - (width + 1) * i;
                
                if (buffer.data[ptr] >= '0' && buffer.data[ptr] <= '9') {
                    currentvalue = currentvalue * 10 + (buffer.data[ptr] - '0');
                } else if (buffer.data[ptr] == ' ') {
                    // Space - complete current number if exists
                    if (currentvalue > 0) {
                        if (currentoperation == '*') currenttotal *= currentvalue;
                        else currenttotal += currentvalue;
                        currentvalue = 0;
                    }
                }
            }
            
            // Complete last number in this column
            if (currentvalue > 0) {
                if (currentoperation == '*') currenttotal *= currentvalue;
                else currenttotal += currentvalue;
            }
        }
        
        total += currenttotal;
        col = prob_left - 1; // Move past this problem
    }
    
    printf(" total part 2 : %"PRId64"\n", total);


    return 0;
}
