#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int day4(void){
    FILE *stream;
    stream = fopen("./Day4/day4.txt", "r");
    if (stream==NULL) {
        return 1;
    }
    fseek(stream,0,SEEK_END);
    int64_t size = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    char *buffer = (char *)malloc(10*size+1);
    buffer[size] = '\0';
    fread(buffer, size, 1, stream);
    
    int32_t width = 0;
    for (int i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            break;
        }
        width++;
    }
    
    int32_t height = 1;
    for (int i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            height++;
        }
    }
    for (int i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            for (int j = i; j < size; j++) {
                buffer[j] = buffer[j + 1];
            }
            size--;
            i--;
        }
    }
    int16_t *adj_arr = (int16_t *)malloc(size * sizeof(int16_t));
    for (int i = 0; i < size; i++) {
        adj_arr[i] = 0;
    }
    int k,l;
    int current_pos;
    // you cant check right if ur in a pos divisible by 10
    // you cant check bottom if  ur in the last line
    // you cant check bottom left if ur in first positiion of line.
    int32_t count = 0;
    int go_next = 1;
    while (go_next){    
        go_next = 0;
        
        for(k=0; k<height; k++){
            for(l=0; l<width; l++){
                current_pos  = k*width + l + 1;
                if (buffer[current_pos-1] == '.' || buffer[current_pos-1] == '0' ){
                    printf(".");
                    buffer[current_pos-1]  = '.';
                    continue;
                }
                // compter a droite a moins  d  etre  tout a droite 
                if (current_pos % width != 0 && buffer[current_pos] == '@'){
                    adj_arr[current_pos-1]+=1;
                    adj_arr[current_pos]+=1;
                }
                
                //  en dessous + en dessous a droite + en dessous a gauche a  moins d'etre tout au dessous
                
                if (k < height){

                    // en dessous
                    if(buffer[current_pos+width-1] == '@'){
                        adj_arr[current_pos-1]+=1;
                        adj_arr[current_pos+width-1]+=1;
                    }
                    
                    // en dessous a  droite a moins d etre  tout  a droite
                    if (current_pos % width != 0 && buffer[current_pos+width] == '@'){
                        adj_arr[current_pos-1]+=1;
                            adj_arr[current_pos+width]+=1;
                    }
                    // compter en dessous a gauche a moins d'etre  tout a gauche
                    if ((current_pos -1) % width != 0 && buffer[current_pos+width-2] == '@'){
                        adj_arr[current_pos-1]+=1;
                        adj_arr[current_pos+width-2]+=1;
                    }
                }
                if (adj_arr[current_pos-1]<4){
                    printf("0");
                    buffer[current_pos-1] = '0';
                    go_next=1;
                    count++;
                }else printf("@");
            }
            printf("\n");
        }
        memset(adj_arr, 0,size * sizeof(int16_t));
        printf("\n\n\n");
    }    
    printf("count  : %d\n\n\n", count);
    // printf("height %d width %d\n", height,width);
    fclose(stream);
    free(buffer);
    free(adj_arr);
    return 0;
}
