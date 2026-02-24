#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_FRAMES 100
#define TIMEOUT 2
#define DATA_PROB 70
#define ACK_PROB 70

int is_success(int probability) {
    return (rand() % 100) < probability;
}

int main() {

    int total_frames, window_size;
    int sender_acked[MAX_FRAMES] = {0};
    int receiver_buffered[MAX_FRAMES] = {0};
    int timer[MAX_FRAMES] = {0};

    int sender_base = 0;
    int receiver_base = 0;

    srand(time(NULL));

    printf("Enter total frames: ");
    scanf("%d", &total_frames);

    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("\n----- Selective Repeat Simulation -----\n\n");

    while(sender_base < total_frames){

        // 1️⃣ Sender sends frames in window
        for(int i = sender_base; i < sender_base + window_size && i < total_frames; i++){

            if(!sender_acked[i]){

                printf("Sender: Sending Frame [%d]\n", i);
                timer[i] = 1;

                // DATA transmission
                if(is_success(DATA_PROB)){

                    printf("  -> Receiver: Frame [%d] received\n", i);

                    // Check if within receiver window
                    if(i >= receiver_base && i < receiver_base + window_size){
                        receiver_buffered[i] = 1;
                    }

                    // ACK transmission
                    if(is_success(ACK_PROB)){
                        printf("  <- Sender: ACK [%d] received\n", i);
                        sender_acked[i] = 1;
                        timer[i] = 0;
                    }
                    else{
                        printf("  <- Sender: ACK [%d] LOST\n", i);
                    }
                }
                else{
                    printf("  -> Receiver: Frame [%d] LOST\n", i);
                }
            }
            printf("\n");
        }

        // 2️⃣ Simulated Timeout
        Sleep(TIMEOUT * 1000);

        for(int i = sender_base; i < sender_base + window_size && i < total_frames; i++){
            if(timer[i] && !sender_acked[i]){
                printf("!!! TIMEOUT for Frame [%d] - Retransmitting\n", i);
            }
        }

        // 3️⃣ Slide sender window
        while(sender_acked[sender_base] && sender_base < total_frames){
            printf("--- Window Slid Forward! Frame [%d] is now the bottom boundary ---\n", sender_base);
            sender_base++;
        }

        // 4️⃣ Deliver in-order at receiver
        while(receiver_buffered[receiver_base] && receiver_base < total_frames){
            printf("Receiver: Delivering Frame [%d] to upper layer\n", receiver_base);
            receiver_base++;
        }

        printf("----------------------------------------\n");
    }

    printf("\nAll frames successfully delivered using Selective Repeat!\n");
    return 0;
}