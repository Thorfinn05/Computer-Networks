#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<windows.h>
#define TIMEOUT 2
#define MAX_FRAMES 100

int is_success(int probability){
    return (rand() % 100) < probability;
}

int main(){
    int total_frame, window_size;
    int base = 0;
    int data_chance = 90;
    int ack_chance = 90;
    srand(time(NULL));

    printf("Enter total frame: ");
    scanf("%d", &total_frame);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    
    while(base < total_frame){
        for(int i=base; i< base + window_size && i<total_frame; i++){
            printf("Sender: Sending Frame [%d]\n", i);
        }
        Sleep(TIMEOUT * 1000);
        
        int acked_this_round = 0;
        bool error_occured = false;

        for(int i=base; i< base+window_size && i<total_frame; i++){
            if(error_occured){
                printf("-> [Receiver]: Frame [%d] DISCARDED (out of order!)\n", i);
                continue;
            }
            if(is_success(data_chance)){
                printf("-> [Receiver]: Received frame [%d]\n", i);
                if(is_success(ack_chance)){
                    printf("<- [Sender]: Received ACK for Frame [%d]\n", i);
                    acked_this_round++;
                }
                else{
                    printf("<- [Sender]: ACK for Frame [%d] LOST!\n", i);
                    error_occured = true;
                }
            }
            else{
                printf(" -> [Receiver]: Frame [%d] DATA LOST!\n", i);
                error_occured = true;
            }
        }
        base += acked_this_round;
        if(error_occured){
            printf("\n--- Timeout! Going back to retransmit from Frame [%d] ---\n", base);
        }
        else {
            printf("\n --- Window Slid Forward: Frame [%d] is now the base ---\n", base);
        }
        printf("\n ----------- \n");
    }
    printf("\nSUCCESS: All frame [%d] are delivered.\n", total_frame);
    return 0;
}