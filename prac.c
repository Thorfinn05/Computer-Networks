#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h> // Using unistd.h for Ubuntu
#include<windows.h>
#define MAX_FRAMES 100
#define TIMEOUT 2

int is_success(int prob){
    return (rand() % 100) < prob;
}

int main(){
    int total_frames, window_size;
    int sender_acked[MAX_FRAMES] = {0};
    int receiver_buffer[MAX_FRAMES] = {0};
    int base = 0;
    int data_chance = 70;
    int ack_chance = 70;
    srand(time(NULL));
    printf("ENter total frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    while(base<total_frames){
        for(int i=base; i<base+window_size && i<total_frames; i++){
            if(!sender_acked[i]){
                printf("SENDER: Sending Frame [%d]\n", i);
                if(is_success(data_chance)){
                    printf("-> RECEIVER: Received Frame [%d]\n", i);
                    receiver_buffer[i] = 1;
                    if(is_success(ack_chance)){
                        printf("<- SENDER: Received Ack for Frame [%d]\n", i);
                        sender_acked[i] = 1;
                    } else{
                        printf("<- SENDER: ACK for Frame [%d] LOST!\n", i);
                        printf(" <- SENDER: Will Retransmit Frame [%d]\n", i);
                    }
                } else{
                    printf("-> RECEIVER: Frame [%d] DATA LOST!\n", i);
                    printf("<- SENDER: Will retransmit Frame [%d]\n", i);
                }
            }
            printf("\n");
        }
        Sleep(TIMEOUT * 1000);
        while(base<total_frames && sender_acked[base]){
            printf("---WIndow Slid Forward! Frame [%d] is now the bottom boundary\n", base);
            base++;
        }
        printf("\n--------------\n");
    }

    printf("\nSUCCESS!\n");
    return 0;
}