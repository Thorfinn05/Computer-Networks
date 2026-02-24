#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
// #include <unistd.h> // Replacement for windows.h

#define MAX_FRAMES 100

int main() {
    int total_frames, window_size;
    int acked[MAX_FRAMES] = {0}; // Track individual ACKs
    int base = 0; // The start of the window

    srand(time(NULL));

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("\n----- Starting Selective Repeat Simulation -----\n");

    while (base < total_frames) {
        // 1. "Send" all frames in the current window that haven't been ACKed yet
        for (int i = base; i < base + window_size && i < total_frames; i++) {
            if (!acked[i]) {
                printf("Sender: Sending Frame [%d]\n", i);
                
                // Simulate Receiver/Network (50% chance of success)
                if (rand() % 2) {
                    printf("Receiver: Frame [%d] received, sending ACK.\n", i);
                    acked[i] = 1;
                } else {
                    printf("Receiver: Frame [%d] lost/corrupted!\n", i);
                }
            }
        }

        // 2. "Slide" the window: Move base forward as long as the frames are ACKed
        while (base < total_frames && acked[base]) {
            printf("Window Slid: Frame [%d] confirmed.\n", base);
            base++;
        }

        printf("--------------------------------------------\n");
        Sleep(1); // Delay for readability
    }

    printf("SUCCESS: All frames received.\n");
    return 0;
}