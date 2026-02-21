#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define TIMEOUT 2

void send_frames (int start, int window_size, int total_frames){
    printf("Sending frames: ");
    for (int i = start; i < start + window_size && total_frames; i++){
        printf("[%d]", i);
    }
}

int receive_ack(int start, int window_size, int total_frames){
    int loss_index = rand() % window_size;
    int ack = start + loss_index;
    if(ack >= total_frames){
        ack = total_frames - 1;
    }
    printf("Ack received upto frame %d\n", ack);
    return ack + 1;
}

int main(){
    int window_size, total_frames;
    int base = 0;
    srand(time(NULL));
    printf("Enter total number of frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("\n -----Starting------\n");
    while(base < total_frames){
        if(base + window_size > total_frames){
            window_size = total_frames - base;
        }
        send_frames(base, window_size, total_frames);
        int ack = receive_ack(base, window_size, total_frames);
        Sleep(TIMEOUT * 1000);
        if(ack == base + window_size){
            printf("All frames in acknowledgement\n");
            base = ack;
        }
        else{
            printf("Timeout Error! Resending frome frame %d\n", ack);
            base = ack;
        }
        printf("-----------\n");
    }
    printf("All frame sent acknowledgements successfully\n");
    return 0;
}