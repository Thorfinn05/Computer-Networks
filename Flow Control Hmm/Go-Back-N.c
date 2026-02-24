#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h>
#include<windows.h>

#define TIMEOUT 1

void send_window(int base, int window_size, int total_frames) {
    printf("Sender: Sending Frames -> ");
    for (int i = 0; i < window_size && (base + i) < total_frames; i++) {
        printf("[%d] ", base + i);
    }
    printf("\n");
}

int main() {
    int window_size, total_frames;
    int base = 0; // The first unacknowledged frame
    int next_frame = 0; 

    srand(time(NULL));

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("\n--- Starting Go-Back-N ARQ Simulation ---\n\n");

    while (base < total_frames) {
        // 1. Send the current window
        send_window(base, window_size, total_frames);

        // 2. Simulate network behavior (Random ACK)
        // We simulate that 'n' frames were received correctly before an error occurs
        int frames_received_ok = rand() % (window_size + 1);
        
        // Ensure we don't "receive" more frames than are actually in the current window
        if (base + frames_received_ok > total_frames) {
            frames_received_ok = total_frames - base;
        }

        Sleep(TIMEOUT); // Simulate propagation delay

        if (frames_received_ok == window_size || (base + frames_received_ok == total_frames)) {
            // Success Case
            printf("Receiver: All frames in window acknowledged.\n");
            base += frames_received_ok;
        } 
        else if (frames_received_ok == 0) {
            // Total Failure Case
            printf("Receiver: TIMEOUT! No ACKs received. Resending from [%d]\n", base);
        } 
        else {
            // Partial Success / GBN Case
            printf("Receiver: ACK received up to [%d]. Frame [%d] was lost/corrupted.\n", 
                    base + frames_received_ok - 1, base + frames_received_ok);
            printf("Sender: Go-Back-N logic triggered. Resending window from [%d]\n", base + frames_received_ok);
            base += frames_received_ok;
        }

        printf("--------------------------------------------------\n");
    }

    printf("SUCCESS: All %d frames sent and acknowledged.\n", total_frames);
    return 0;
}