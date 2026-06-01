#include<stdio.h>
#include<string.h>

int calculate_parity(const char *binary){
    int count = 0;
    for(int i=0; binary[i] != '\0'; i++){
        if(binary[i] == '1'){
            count++;
        }
    }
    return count % 2 == 0 ? 0 : 1;
}

int main(){
    char binary[50];
    printf("Enter the binary data: ");
    scanf("%s", binary);

    int parity_bit = calculate_parity(binary);
    printf("Transmitted with parity: %s%d\n", binary, parity_bit);

    char received_data[51];
    printf("Enter the recieved data with parity: \n");
    scanf("%s", received_data);
    // return 0;

    int received_parity = received_data[strlen(received_data) - 1] - '0';
    received_data[strlen(received_data) - 1] = '\0';
    
    if(received_parity == calculate_parity(received_data)){
        printf("Parity check passed: NO ERROR\n");
    } else{
        printf("Parity check failed: ERROR\n");
    }

    return 0;
}