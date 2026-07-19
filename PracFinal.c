#include<stdio.h>
#include<string.h>

int data[100], divisor[20], remainder[20];
int data_len, div_len;

void xor(int a[], int b[], int len){
    for(int i=0; i<len; i++){
        a[i] = a[i] ^ b[i];
    }
}

void crc_divide(int dividend[], int dlen){
    int temp[20];
    for(int i=0; i<div_len; i++){
        temp[i] = dividend[i];
    }
    int pos = div_len;
    while(pos <= dlen){
        if(temp[0] == 1){
            xor(temp, divisor, div_len);
        } else{
            int zeros[] = {0};
            xor(temp, zeros, div_len);
        }
        if(pos < dlen){
            for(int i=0; i<div_len; i++){
                temp[i] = temp[i+1];
            }
            temp[div_len - 1] = dividend[pos];
        }
        pos++;
    }
    for(int i=0; i<div_len - 1; i++){
        remainder[i] = temp[i+1];
    }
}

int main(){
    char d[100], g[20];
    printf("Enter data: ");
    scanf("%s", d),
    printf("Enter divisor: ");
    scanf("%s", g);

    data_len = strlen(d);
    div_len = strlen(g);

    for(int i=0; i<data_len; i++) data[i] = d[i] - '0';
    for(int i=0; i<div_len; i++) divisor[i] = g[i] - '0';

    int crc_len = div_len - 1;
    int augmented[20];

    for(int i=0; i<data_len; i++) augmented[i] = data[i];
    for(int i=0; i<crc_len; i++) augmented[data_len + i] = 0;

    printf("Augmented data: ");
    for(int i=0; i<data_len+crc_len; i++){
        printf("%d", augmented[i]);
    }

    crc_divide(augmented, data_len+crc_len);
    printf("\nCRC Remainder: ");
    for(int i=0; i<crc_len; i++){
        printf("%d", remainder[i]);
    }

    int transmitted[20];
    for(int i=0; i<data_len; i++) transmitted[i] = data[i];
    for(int i=0; i<crc_len; i++) transmitted[data_len + i] = remainder[i];

    printf("\nTransmitted data: ");
    for(int i=0; i<data_len+crc_len; i++){
        printf("%d", transmitted[i]);
    }

    crc_divide(transmitted, data_len + crc_len);

    printf("\nRemainder at receiver: ");
    for(int i=0; i<crc_len; i++){
        printf("%d", remainder[i]);
    }
    int error = 0;
    for(int i=0; i<crc_len; i++){
        if(remainder[i] != 0) {error = 1; break;}
    }
    if(error){
        printf("\nResult: ERROR\n");
    } else{
        printf("\nNO ERROR\n");
    }
    return 0;

}