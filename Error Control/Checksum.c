#include <stdio.h>

int main() {
    int n;
    printf("Enter number of data segments: ");
    scanf("%d", &n);

    int segment_size;
    printf("Enter segment size (bits): ");
    scanf("%d", &segment_size);

    int segments[10][16];
    int sum[16] = {0};

    // ── INPUT SEGMENTS ────────────────────────────────
    for (int i = 0; i < n; i++) {
        printf("Enter segment %d (%d bits): ", i+1, segment_size);
        for (int j = 0; j < segment_size; j++)
            scanf("%d", &segments[i][j]);
    }

    // ── SENDER SIDE ───────────────────────────────────
    // Step 1: Add all segments using binary addition
    // Start with first segment
    for (int j = 0; j < segment_size; j++)
        sum[j] = segments[0][j];

    // Add remaining segments one by one
    for (int i = 1; i < n; i++) {
        int carry = 0;
        // Add from right to left (LSB to MSB)
        for (int j = segment_size - 1; j >= 0; j--) {
            int total  = sum[j] + segments[i][j] + carry;
            sum[j]     = total % 2;
            carry      = total / 2;
        }
        // wraparound carry - add carry back to sum
        if (carry) {
            for (int j = segment_size - 1; j >= 0; j--) {
                int total = sum[j] + carry;
                sum[j]    = total % 2;
                carry     = total / 2;
                if (!carry) break;
            }
        }
    }

    printf("\nSum of segments : ");
    for (int j = 0; j < segment_size; j++)
        printf("%d", sum[j]);

    // Step 2: Checksum = 1s complement of sum (flip all bits)
    int checksum[16];
    for (int j = 0; j < segment_size; j++)
        checksum[j] = sum[j] ^ 1;   // flip each bit

    printf("\nChecksum (1s complement): ");
    for (int j = 0; j < segment_size; j++)
        printf("%d", checksum[j]);

    // ── RECEIVER SIDE ─────────────────────────────────
    // Add all segments + checksum
    // If result is all 1s → no error
    int recv_sum[16];
    for (int j = 0; j < segment_size; j++)
        recv_sum[j] = sum[j];   // sum already has all segments added

    // Add checksum to sum
    int carry = 0;
    for (int j = segment_size - 1; j >= 0; j--) {
        int total    = recv_sum[j] + checksum[j] + carry;
        recv_sum[j]  = total % 2;
        carry        = total / 2;
    }
    // wraparound carry
    if (carry) {
        for (int j = segment_size - 1; j >= 0; j--) {
            int total   = recv_sum[j] + carry;
            recv_sum[j] = total % 2;
            carry       = total / 2;
            if (!carry) break;
        }
    }

    printf("\n\nReceiver sum (segments + checksum): ");
    for (int j = 0; j < segment_size; j++)
        printf("%d", recv_sum[j]);

    // Check if all 1s
    int error = 0;
    for (int j = 0; j < segment_size; j++)
        if (recv_sum[j] != 1) { error = 1; break; }

    if (error)
        printf("\nResult: ERROR detected!\n");
    else
        printf("\nResult: NO ERROR - Data is correct!\n");

    return 0;
}