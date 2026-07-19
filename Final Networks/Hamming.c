#include<stdio.h>
#include<math.h>

int main(){
    int m;
    printf("Enter number of data bits: ");
    scanf("%d", &m);
    int data[m];
    printf("Enter %d data bits: ", m);
    for(int i=0; i<m; i++){
        scanf("%d", &data[i]);
    }

    // #1
    // ── STEP 1: Find number of parity bits ────────────
    // r parity bits needed if: 2^r >= m + r + 1
    int r = 0;
    while((int)pow(2, r) < m + r + 1)
        r++;
    printf("\nNumber of parity bits needed: %d\n", r);
    int total = m + r; // total bits in hamming code

    // #2
    // ── STEP 2: Place data bits in correct positions ──
    // Parity bits go at positions that are powers of 2: 1,2,4,8...
    // Data bits fill the remaining positions
    int hamming[total + 1]; // 1-indexed
    for(int i=0; i<=total; i++){
        hamming[i] = 0;
    }

    // fill data bits into non-parity positions
    int j = 0;
    for(int i=total; i>=1; i--){
        // check if i is a power of 2 (parity position)
        int is_parityPos = 0;
        for(int p = 0; p < r; p++){
            if((int)pow(2, p) == i) {is_parityPos = 1; break;}
        }
        if(!is_parityPos)
            hamming[i] = data[j++];
    }
    // printf("Hamming Code: ");
    // for(int i=total; i>=1; i--){
    //     printf("%d", hamming[i]);
    // }

    // #3
    // ── STEP 3: Calculate parity bits ─────────────────
    // Each parity bit at position 2^p covers positions where bit p is set
    for(int p=0; p<r; p++){
        int parity_pos = (int)pow(2, p); // 1, 2, 4, 8...
        int xor_sum = 0;
        for(int i=total; i>=1; i--){
            if(i == parity_pos) continue; // skip parity bit itself
            if(i & parity_pos)            // check if position i has bit p set
                xor_sum ^= hamming[i];
        }
        hamming[parity_pos] = xor_sum;
    }

    printf("\nHamming Code (1-indexed):\n");
    printf("Position: ");
    for(int i=total; i>=1; i--) printf("%d ", i);
    printf("\nBits:    ");
    for(int i=total; i>=1; i--) printf("%d ", hamming[i]);

    printf("\nTransmitted: ");
    for(int i=total; i>=1; i--) printf("%d", hamming[i]);

    // #4
    // ── STEP 4: ERROR DETECTION & CORRECTION ──────────
    int received[total + 1];
    printf("\nEnter received bits (%d bits): ", total);
    for(int i=total; i>=1; i--)
        scanf("%d", &received[i]);

    // recalculate parity bits on received data
    int syndrome = 0;
    for(int p=0; p<r; p++){
        int parity_pos = (int)pow(2, p);
        int xor_sum = 0;

        for(int i=total; i>=1; i--){
            if(i & parity_pos)
                xor_sum ^= received[i];
        }
        // if xor_sum != 0, this parity bit position contributes to error
        if(xor_sum != 0){
            syndrome += parity_pos;
        }
    }
    printf("\nSyndrome: %d\n", syndrome);
    if(syndrome == 0){
        printf("\nNO ERROR\n");
    } else {
        printf("Error at position %d\n", syndrome);
        // flip the error bit
        received[syndrome] ^= 1;
        printf("Corrected Code: ");
        for(int i=total; i>=1; i--){
            printf("%d", received[i]);
        }
        printf("\n");
    }
    return 0;
}