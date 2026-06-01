#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

void xorStrings(char *remainder, const char *divisor, int len)
{
    for (int i = 0; i < len; i++)
        remainder[i] = (remainder[i] == divisor[i]) ? '0' : '1';
}

void binaryDivision(const char *dividend, int dividendLen,
                    const char *divisor,  int divisorLen,
                    char *remainder)
{
    char temp[MAX_LEN];
    strncpy(temp, dividend, dividendLen);
    temp[dividendLen] = '\0';

    for (int i = 0; i <= dividendLen - divisorLen; i++) {
        if (temp[i] == '1') {
            xorStrings(&temp[i], divisor, divisorLen);
        }
    }

    int remLen = divisorLen - 1;
    strncpy(remainder, &temp[dividendLen - remLen], remLen);
    remainder[remLen] = '\0';
}

int isValidBinary(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (s[i] != '0' && s[i] != '1')
            return 0;
    return 1;
}

void crcGenerate(void)
{
    char data[MAX_LEN], generator[MAX_LEN];
    char augmented[MAX_LEN], remainder[MAX_LEN];

    printf("\n========== CRC GENERATION ==========\n");

    printf("Enter binary data word       : ");
    scanf("%s", data);
    if (!isValidBinary(data)) {
        printf("[ERROR] Input must be a binary string (0s and 1s only).\n");
        return;
    }

    printf("Enter generator polynomial   : ");
    scanf("%s", generator);
    if (!isValidBinary(generator)) {
        printf("[ERROR] Generator must be a binary string (0s and 1s only).\n");
        return;
    }

    int dataLen = (int)strlen(data);
    int genLen  = (int)strlen(generator);
    int remLen  = genLen - 1;

    strcpy(augmented, data);
    for (int i = 0; i < remLen; i++)
        augmented[dataLen + i] = '0';
    augmented[dataLen + remLen] = '\0';

    binaryDivision(augmented, dataLen + remLen, generator, genLen, remainder);

    char codeword[MAX_LEN];
    strcpy(codeword, data);
    strcat(codeword, remainder);

    printf("\n--- Results ---\n");
    printf("Data word (original)         : %s\n", data);
    printf("Generator polynomial         : %s\n", generator);
    printf("Augmented data (data + 0s)   : %s\n", augmented);
    printf("CRC remainder                : %s\n", remainder);
    printf("Transmitted codeword         : %s\n", codeword);
    printf("====================================\n\n");
}

void crcCheck(void)
{
    char received[MAX_LEN], generator[MAX_LEN], remainder[MAX_LEN];

    printf("\n========== CRC CHECKING ==========\n");

    printf("Enter received codeword      : ");
    scanf("%s", received);
    if (!isValidBinary(received)) {
        printf("[ERROR] Input must be a binary string (0s and 1s only).\n");
        return;
    }

    printf("Enter generator polynomial   : ");
    scanf("%s", generator);
    if (!isValidBinary(generator)) {
        printf("[ERROR] Generator must be a binary string (0s and 1s only).\n");
        return;
    }

    int recvLen = (int)strlen(received);
    int genLen  = (int)strlen(generator);

    if (recvLen < genLen) {
        printf("[ERROR] Received codeword is shorter than the generator.\n");
        return;
    }

    binaryDivision(received, recvLen, generator, genLen, remainder);

    int errorFree = 1;
    for (int i = 0; remainder[i]; i++) {
        if (remainder[i] != '0') {
            errorFree = 0;
            break;
        }
    }

    printf("\n--- Results ---\n");
    printf("Received codeword            : %s\n", received);
    printf("Generator polynomial         : %s\n", generator);
    printf("Remainder after division     : %s\n", remainder);

    if (errorFree)
        printf("Status                       : NO ERROR DETECTED (data accepted)\n");
    else
        printf("Status                       : ERROR DETECTED (data rejected)\n");

    printf("==================================\n\n");
}

int main(void)
{
    int choice;

    printf("*********************************************\n");
    printf("*   CRC Generation & Checking Program       *\n");
    printf("*********************************************\n");

    while (1) {
        printf("\n------------- MENU -------------\n");
        printf("  1. CRC Generation\n");
        printf("  2. CRC Checking\n");
        printf("  3. Exit\n");
        printf("--------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                crcGenerate();
                break;
            case 2:
                crcCheck();
                break;
            case 3:
                printf("Exiting. Goodbye!\n");
                return 0;
            default:
                printf("[ERROR] Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}
