#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// #include<unistd.h>
#include<windows.h>
#define TIMEOUT 2

int window_size, total_frames;

void send_frames(int start, int end){
    for (int i = start; i < end; i++){
        printf("Sending frame: %d\n", i);
    }
}

int main(){
    int base = 0;
    srand(time(0));
    printf("Enter total number of frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("\n -----Starting------\n");
    if(window_size > total_frames){
        printf("Invalid input!\n");
        return 1;
    }
    while(base < total_frames){
        int end = (base + window_size < total_frames) ? base + window_size : total_frames;
        send_frames(base, end);
        int ack = base + (rand() % (window_size + 1));
        Sleep(TIMEOUT * 1000);
        if(ack >= end){
            printf("All frames in acknowledgement\n");
            base = end;
        }
        else{
            printf("Ack lost or frame %d lost! Resending from frame %d\n", base, end-1);
            base = ack;
        }
        printf("-----------\n");
    }
    printf("All frame sent acknowledgements successfully\n");
    return 0;
}
