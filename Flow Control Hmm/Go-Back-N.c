#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define TIMEOUT 2
// #define DATA_PROB 70
// #define ACK_PROB 70

int is_success(){
    return (rand() % 100) < 70;
}

int main(){

    int total_frames, window_size;
    int base = 0;
    int next_seq_num = 0;

    srand(time(0));

    printf("Enter total number of frames: ");
    scanf("%d",&total_frames);

    printf("Enter window size: ");
    scanf("%d",&window_size);

    printf("\n------ GO BACK N SIMULATION START ------\n\n");

    while(base < total_frames){

        // 1️⃣ Send frames until window is full
        while(next_seq_num < base + window_size && next_seq_num < total_frames){
            printf("Sender: Sending Frame %d\n", next_seq_num);
            next_seq_num++;
        }

        // 2️⃣ Start single timer for base frame
        printf("Timer started for Frame %d\n", base);
        Sleep(TIMEOUT * 1000);

        // 3️⃣ Simulate receiver behavior
        int receiver_expected = base;
        int last_ack = base;

        for(int i = base; i < next_seq_num; i++){

            if(is_success()){
                printf("Receiver: Frame %d received correctly\n", i);
                receiver_expected++;
                last_ack = receiver_expected;
            }
            else{
                printf("Receiver: Frame %d LOST!\n", i);
                break;  // GBN stops at first loss
            }
        }

        // 4️⃣ Simulate ACK transmission
        if(last_ack > base){

            if(is_success()){
                printf("Sender: ACK received up to %d (Cumulative)\n", last_ack - 1);
                base = last_ack;
            }
            else{
                printf("ACK LOST! Timeout will occur.\n");
            }
        }

        // 5️⃣ Timeout condition
        if(base < next_seq_num){
            printf("TIMEOUT! Go-Back-N triggered.\n");
            printf("Retransmitting from Frame %d\n", base);
            next_seq_num = base;  // Go back
        }

        printf("------------------------------------------\n");
    }

    printf("\nAll frames successfully transmitted!\n");
    return 0;
}