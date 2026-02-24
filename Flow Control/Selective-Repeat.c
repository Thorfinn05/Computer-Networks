#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//#include<unistd.h>
#define TIMEOUT 2
#define MAX_FRAMES 100
#include<time.h>

int is_frame_received(){
    return rand() % 2;
}

int main(){
    int total_frames, window_size;
    int sent[MAX_FRAMES] = {0};
    int ack[MAX_FRAMES] = {0};

    srand(time(NULL));

    printf("Enter total number of frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("\n -----Starting------\n");

    int i=0;
    while(1){
        int sent_in_this_round = 0;
        for(int j=0; j<window_size && i+j <total_frames; j++){
            int frame_index = i+j;
            if(!ack[frame_index]){
                printf("Sending Frame[%d] ", frame_index);
                sent[frame_index] = 1;
                if(is_frame_received()){
                    printf("Received\n");
                    ack[frame_index] = 1;
                }
                else{
                    printf("Lost! Will be resend.\n");
                }
                sent_in_this_round++;
            }
        }
        while(ack[i] && i<total_frames){
            i++;
        }
        if(i>=total_frames){
            break;
        }
        printf("\n---------------\n");
    }
    printf("All frames are sent and received successfully.\n");
    return 0;
}
