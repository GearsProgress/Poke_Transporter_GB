#include "global_frame_counter.h"

int global_frame_count = 0;

void global_next_frame(){
    global_frame_count++;
}

int get_frame_count(){
    return global_frame_count;
}