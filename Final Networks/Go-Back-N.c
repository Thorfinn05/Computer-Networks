#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#define TIMEOUT 2

// Helper function for probability
int is_success(int probability) {
    return (rand() % 100) < probability;
}

int main() {
    int total_frame, window_size;
    int base = 0;
    int data_chance = 70;
    int ack_chance = 70;
    srand(time(NULL));

    printf("Enter total frame: ");
    scanf("%d", &total_frame);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    
    printf("\n--- Starting Go-Back-N ARQ Protocol ---\n\n");

    while (base < total_frame) {
        // 1. Sender transmits all frames in the current window
        for (int i = base; i < base + window_size && i < total_frame; i++) {
            printf("Sender: Sending Frame [%d]\n", i);
        }

        Sleep(TIMEOUT * 1000); // Simulate network delay / waiting for ACKs

        // 2. Receiver processes frames and sends ACKs
        int acked_this_round = 0;
        bool error_occurred = false;

        for (int i = base; i < base + window_size && i < total_frame; i++) {
            
            // In Go-Back-N, if a previous frame in this window was lost, 
            // the receiver discards all subsequent frames automatically.
            if (error_occurred) {
                printf(" -> [Receiver]: Frame [%d] DISCARDED (out of order!)\n", i);
                continue; 
            }

            // Check if Data successfully reaches Receiver
            if (is_success(data_chance)) {
                printf(" -> [Receiver]: Received Frame [%d]\n", i);
                
                // Check if ACK successfully reaches Sender
                if (is_success(ack_chance)) {
                    printf(" <- [Sender]: Received ACK for Frame [%d]\n", i);
                    acked_this_round++;
                } else {
                    printf(" <- [Sender]: ACK for Frame [%d] LOST!\n", i);
                    error_occurred = true; // Triggers the Go-Back-N mechanism
                }
            } else {
                printf(" -> [Receiver]: Frame [%d] DATA LOST!\n", i);
                error_occurred = true; // Triggers the Go-Back-N mechanism
            }
        }

        // 3. Slide the window forward or Go-Back-N
        base += acked_this_round; 

        if (error_occurred) {
            printf("\n--- Timeout! Going back to retransmit from Frame [%d] ---\n", base);
        } else {
            printf("\n--- Window Slid Forward: Frame [%d] is now the base ---\n", base);
        }
        
        printf("\n ----------- \n");
    }

    printf("\nSUCCESS: All %d frames were delivered.\n", total_frame);
    return 0;
}