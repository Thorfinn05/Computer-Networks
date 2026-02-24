#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define MAX_FRAMES 100
int is_success(){
    return rand() % 100 < 70; // 70% chance of success
}
int main(){
    int total_frames, window_size;
    int sender_acked[MAX_FRAMES] = {0};
    int receiver_buffer[MAX_FRAMES] = {0};
    int base = 0;
    srand(time(NULL));
    printf("Enter total frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("\n---- Selective Repeat Simulation ----\n");
    while(base < total_frames){
        for(int i=base; i < base + window_size && i < total_frames; i++){
            if(!sender_acked[i]){
                printf("Sender: Sending Frame [%d]\n", i);
                if(is_success()){
                    printf(" -> [Receiver]: Received Frame [%d]\n", i);
                    receiver_buffer[i] = 1;
                    if(is_success()){
                        printf(" <- [Sender]: Ack for Frame [%d] received\n", i);
                        sender_acked[i] = 1;
                    } else{
                        printf(" -< [Sender]: Ack for Frame [%d] LOST\n", i);
                    }
                } else{
                    printf(" -> [Receiver]: Data LOST [%d]\n", i);
                }
            }
        }
        while(base < total_frames && sender_acked[base]){
            printf("--- Window Slide FWD! Frame [%d] is now RECEIVED ---\n", base);
            base++;
        }
        printf("-----------------------------------------------\n");
        Sleep(1);
    }
    printf("\nSUCCESS: All %d frames delivered and confirmed.\n", total_frames);
    return 0;
}