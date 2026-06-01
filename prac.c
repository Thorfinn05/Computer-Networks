#include<stdio.h>

int main(){
    int n;
    printf("Enter number of data segments: ");
    scanf("%d", &n);

    int segment_size;
    printf("Enter segment size(bits): ");
    scanf("%d", &segment_size);

    int segments[10][16];
    int sum[16] = {0};

    for(int i=0; i<n; i++){
        printf("Enter segment %d (%d bits): ", n, segment_size);
        for(int j=0; j<segment_size; j++){
            scanf("%d", &segments[i][j]);
        }
    }
    //SENDER
    for(int j=0; j<segment_size; j++){
        sum[j] = segments[0][j];
    }
    for (int i=0; i<n; i++){
        int carry = 0;
        for(int j=segment_size; j>=0; j--){
            int total = sum[j] + segments[i][j] + carry;
            sum[j] = total % 2;
            carry = total / 2;
        }
        if(carry){
            for(int j=segment_size; j>=0; j--){
                int total = sum[j] + carry;
                sum[j] = total % 2;
                carry = total / 2;
                if(!carry) break;
            }
        }
    }

    printf("\nSum of segments: ");
    for(int j=0; j<segment_size; j++){
        printf("%d", sum[j]);
    }
    int checksum[16];
    for(int j = 0; j<segment_size; j++){
        checksum[j] = sum[j] ^ 1;
    }
    printf("\nChecksum (1s complement of Sum): ");
    for(int j=0; j<segment_size; j++){
        printf("%d", checksum[j]);
    }

    //RECEIVER
    int rec_sum[16];
    for(int j=0; j<segment_size; j++){
        rec_sum[j] = sum[j];
    }
    int carry = 0;
    for(int j=segment_size; j>=0; j--){
        int total = rec_sum[j] + checksum[j] + carry;
        rec_sum[j] = total % 2;
        carry = total / 2;
    }
    if(carry){
        for(int j=segment_size; j>=0; j--){
            int total = rec_sum[j] + carry;
            rec_sum[j] = total % 2;
            carry = total / 2;
            if(!carry) break;
        }
    }

    printf("\nReceiver sum: ");
    for(int j=0; j<segment_size; j++){
        printf("%d", rec_sum[j]);
    }
    int error=0;
    for(int j=0; j,segment_size; j++){
        if(rec_sum[j] != 1) { error = 1; break;}
    }
    if(error){
        printf("ERROR\n");
    } else {
        printf("NO ERROR\n");
    }

    return 0;
}