#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../main.h"
#include <inttypes.h>
#include <string.h>

int64_t splitcounts = 0;

void beam_down_count_splits(Buffer buffer, int64_t width, int64_t ptr){
    if ((ptr+width < buffer.size) && (buffer.data[ptr+width]=='.')){
        ptr = ptr+width;
        buffer.data[ptr] = '|';
        beam_down_count_splits(buffer,width,ptr);
    }else if(buffer.data[ptr+width]=='^'){
        splitcounts++;
        beam_down_count_splits(buffer, width, ptr-1);
        beam_down_count_splits(buffer, width, ptr+1);
    }else{
        return;
    }
}

int64_t count_timelines_bottom_up(Buffer buffer, int64_t width, int64_t height){
    int64_t *paths = calloc(width, sizeof(int64_t));
    int64_t *new_paths = calloc(width, sizeof(int64_t));
    
    int64_t bottom_row = height - 1;
    while (bottom_row > 0) {
        int has_content = 0;
        for (int64_t col = 0; col < width; col++) {
            char cell = buffer.data[bottom_row * width + col];
            if (cell == '|' || cell == '^') {
                has_content = 1;
                break;
            }
        }
        if (has_content) break;
        bottom_row--;
    }
    
    int has_splits_at_bottom = 0;
    for (int64_t col = 0; col < width; col++) {
        char cell = buffer.data[bottom_row * width + col];
        if (cell == '^') {
            has_splits_at_bottom = 1;
            break;
        }
    }
    
    for (int64_t col = 0; col < width; col++) {
        char cell = buffer.data[bottom_row * width + col];
        if (cell == '|') {
            paths[col] = 1;
        } else if (cell == '^' && has_splits_at_bottom) {
            paths[col] = 2;
        }
    }
    
    for (int64_t row = bottom_row - 1; row >= 0; row--) {
        memset(new_paths, 0, width * sizeof(int64_t));
        
        for (int64_t col = 0; col < width; col++) {
            char cell = buffer.data[row * width + col];
            
            if (cell == '^') {
                if (col > 0) new_paths[col] += paths[col-1];
                if (col < width-1) new_paths[col] += paths[col+1];
            } else if (cell == '|' || cell == 'S') {
                new_paths[col] = paths[col];
            }
        }
        
        int64_t *temp = paths;
        paths = new_paths;
        new_paths = temp;
    }
    
    int64_t result = 0;
    for (int64_t col = 0; col < width; col++) {
        if (buffer.data[col] == 'S') {
            result = paths[col];
            break;
        }
    }
    
    free(paths);
    free(new_paths);
    return result;
}

int day7(void){
    Buffer buffer = read_entire_file("./Day7/day7.txt");
    Dimension dimension = get_dimension(buffer);
    int64_t actual_height = dimension.height + 1;
    int64_t ptr = 0;
    while (buffer.data[ptr] != 'S') ptr++;
    
    beam_down_count_splits(buffer, dimension.width, ptr); 
    int64_t timelines = count_timelines_bottom_up(buffer, dimension.width, actual_height);
    
    printf("split counts: %"PRId64"\n", splitcounts);
    printf("timelines : %"PRId64"\n", timelines); 
    return 0;
}

