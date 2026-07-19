#include <stdio.h>
#include <string.h>

int data[100], divisor[20], remainder[20];
int data_len, div_len;

// XOR operation
void xor(int a[], int b[], int len) {
    for (int i = 0; i < len; i++)
        a[i] = a[i] ^ b[i];
}

// CRC Division
void crc_divide(int dividend[], int dlen) {
    // copy first chunk equal to divisor length
    int temp[20];
    for (int i = 0; i < div_len; i++)
        temp[i] = dividend[i];

    int pos = div_len;  // next bit to bring down

    while (pos <= dlen) {
        // if leading bit is 1 → XOR with divisor
        // if leading bit is 0 → XOR with 0s (no change)
        if (temp[0] == 1)
            xor(temp, divisor, div_len);
        else {
            int zeros[20] = {0};
            xor(temp, zeros, div_len);
        }

        // shift left and bring next bit down
        if (pos < dlen) {
            for (int i = 0; i < div_len - 1; i++)
                temp[i] = temp[i + 1];
            temp[div_len - 1] = dividend[pos];
        }
        pos++;
    }

    // remainder is what's left in temp (skip first bit)
    for (int i = 0; i < div_len - 1; i++)
        remainder[i] = temp[i + 1];
}

int main() {
    // ── INPUT ─────────────────────────────────────────
    char d[100], g[20];

    printf("Enter data bits (e.g. 10110011): ");
    scanf("%s", d);
    printf("Enter divisor/generator (e.g. 1101): ");
    scanf("%s", g);

    data_len = strlen(d);
    div_len  = strlen(g);

    for (int i = 0; i < data_len; i++) data[i]    = d[i] - '0';
    for (int i = 0; i < div_len;  i++) divisor[i] = g[i] - '0';

    // ── SENDER SIDE ───────────────────────────────────
    // Append (div_len - 1) zeros to data
    int crc_len = div_len - 1;
    int augmented[120];

    for (int i = 0; i < data_len; i++)   augmented[i] = data[i];
    for (int i = 0; i < crc_len;  i++)   augmented[data_len + i] = 0;

    printf("\nAugmented data (data + zeros): ");
    for (int i = 0; i < data_len + crc_len; i++)
        printf("%d", augmented[i]);

    crc_divide(augmented, data_len + crc_len);

    printf("\nCRC remainder : ");
    for (int i = 0; i < crc_len; i++)
        printf("%d", remainder[i]);

    // Transmitted frame = data + remainder
    int transmitted[120];
    for (int i = 0; i < data_len; i++)  transmitted[i] = data[i];
    for (int i = 0; i < crc_len;  i++)  transmitted[data_len + i] = remainder[i];

    printf("\nTransmitted   : ");
    for (int i = 0; i < data_len + crc_len; i++)
        printf("%d", transmitted[i]);

    // ── RECEIVER SIDE ─────────────────────────────────
    // Divide received frame by same divisor
    // If remainder = 0 → no error
    crc_divide(transmitted, data_len + crc_len);

    printf("\n\nRemainder at receiver: ");
    for (int i = 0; i < crc_len; i++)
        printf("%d", remainder[i]);

    int error = 0;
    for (int i = 0; i < crc_len; i++)
        if (remainder[i] != 0) { error = 1; break; }

    if (error)
        printf("\nResult: ERROR detected!\n");
    else
        printf("\nResult: NO ERROR - Data is correct!\n");

    return 0;
}