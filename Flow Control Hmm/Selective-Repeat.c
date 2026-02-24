#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h> // Using unistd.h for Ubuntu
#include<windows.h>
#define MAX_FRAMES 100
#define TIMEOUT 2

// Helper to simulate a percentage chance of success
int is_success(int probability) {
    return (rand() % 100) < probability;
}

int main() {
    int total_frames, window_size;
    int sender_acked[MAX_FRAMES] = {0};   // Sender's knowledge
    int receiver_buffered[MAX_FRAMES] = {0}; // Receiver's actual storage
    int base = 0;
    
    int data_chance = 70; // 70% chance data arrives
    int ack_chance = 70;  // 70% chance ACK arrives

    srand(time(NULL));

    printf("Enter total frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("\n--- Selective Repeat: Data vs ACK Loss Simulation ---\n\n");

    while (base < total_frames) {
        // 1. Sender sends everything in the current window that isn't ACKed
        for (int i = base; i < base + window_size && i < total_frames; i++) {
            if (!sender_acked[i]) {
                printf("Sender: Sending Frame [%d]\n", i);
                
                // --- STEP A: FORWARD PATH (DATA) ---
                if (is_success(data_chance)) {
                    printf("  -> [Receiver]: Received Frame [%d] successfully.\n", i);
                    receiver_buffered[i] = 1; // Receiver now has it

                    // --- STEP B: REVERSE PATH (ACK) ---
                    if (is_success(ack_chance)) {
                        printf("  <- [Sender]: Received ACK for Frame [%d].\n", i);
                        Sleep(TIMEOUT * 500); // Readability delay
                        sender_acked[i] = 1;
                    } else {
                        printf("  <- [Sender]: ACK for Frame [%d] LOST!\n", i);
                        printf("  <- [Sender]: Will retransmit Frame[%d]\n", i);
                    }
                } else {
                    printf("  -> [Receiver]: Frame [%d] DATA LOST!\n", i);
                    printf("  <- [Sender]: Will retransmit Frame[%d]\n", i);
                }
            }
            printf("\n");
        }

        // 2. Window Sliding Logic
        // The window only slides if the 'base' frame is confirmed at the SENDER
        while (base < total_frames && sender_acked[base]) {
            printf("--- Window Slid Forward! Frame [%d] is now the bottom boundary ---\n", base);
            base++;
        }

        printf("\n-------------\n");
        Sleep(TIMEOUT * 1000); // Readability delay
    }

    printf("\nSUCCESS: All %d frames delivered and confirmed.\n", total_frames);
    return 0;
}