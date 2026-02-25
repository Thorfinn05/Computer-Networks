#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define TIMEOUT 2
#define MAX_FRAMES 100

int is_success(){
    return rand() % 100 < 70;
}

int main(){
    int total_frames, window_size;
    // int sender_acked[MAX_FRAMES] = {0};
    // int receiver_buffer[MAX_FRAMES] = {0};
    int base = 0;
    int next_seq_num = 0;
    srand(time(0));
    printf("Enter total frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("\n--- Selective Repeat: Data vs ACK Loss Simulation ---\n\n");
    while(base < total_frames){
        while(next_seq_num < base + window_size && next_seq_num < total_frames){
            printf("Sender: Sending Frame [%d]\n", next_seq_num);
            next_seq_num++;
        }
        printf("Timer for Frame [%d] started\n", base);
        Sleep(TIMEOUT *1000);
        int receiver_expected = base;
        int last_ack = base;
        for(int i=base; i< next_seq_num; i++){
            if(is_success()){
                printf("Receiver: Frame [%d] received\n", i);
                receiver_expected++;
                last_ack = receiver_expected;
            } else{
                printf("Receiver:Frame [%d] LOST\n", i);
                break;
            }
        }
        if(last_ack > base) {
            if(is_success()){
                printf("Sender: ACK  upto [%d] Rceived", last_ack -1);
                base = last_ack;
            } else{
                printf("ACK LOST! TIMEOUT occured\n");
            }
        }
        if(base< next_seq_num){
            printf("TIMEOUT!\n");
            printf("Retransmitting from Frame [%d]\n", base);
            next_seq_num = base;
        }
        printf("\n----------\n");
    }
    printf("\nSUCCESS\n");
    return 0;
}