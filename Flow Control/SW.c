#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Required for sleep() on Ubuntu/Linux

#define TIMEOUT 1

void send_frames(int start, int window_size, int total_frames) {
    printf("Sending frames: ");
    for (int i = start; i < start + window_size && i < total_frames; i++) {
        printf("[%d] ", i);
    }
    printf("\n");
}

int receive_ack(int start, int window_size, int total_frames) {
    // Simulate random success/failure
    int loss_index = rand() % (window_size + 1); 
    int ack = start + loss_index;
    
    if (ack >= total_frames) {
        ack = total_frames;
    }
    
    if (ack == start) {
        printf("No new ACKs received (Timeout simulated).\n");
    } else {
        printf("Ack received up to frame %d\n", ack - 1);
    }
    return ack;
}

int main() {
    int window_size, total_frames;
    int base = 0;
    
    srand(time(NULL));
    
    printf("Enter total number of frames to send: ");
    if (scanf("%d", &total_frames) != 1) return 1;
    
    printf("Enter window size: ");
    if (scanf("%d", &window_size) != 1) return 1;
    
    printf("\n----- Starting Go-Back-N Protocol Simulation -----\n");
    
    while (base < total_frames) {
        int current_window = window_size;
        if (base + current_window > total_frames) {
            current_window = total_frames - base;
        }
        
        send_frames(base, current_window, total_frames);
        
        // Use lower-case sleep() for Linux (seconds)
        sleep(TIMEOUT); 
        
        int next_base = receive_ack(base, current_window, total_frames);
        
        if (next_base == base + current_window) {
            printf("Window successful. Sliding window...\n");
            base = next_base;
        } else {
            printf("Timeout/Partial Ack! Resending from frame %d\n", next_base);
            base = next_base;
        }
        printf("--------------------------------------------------\n");
    }
    
    printf("All frames sent and acknowledged successfully!\n");
    return 0;
}