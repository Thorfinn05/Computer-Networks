#include<stdio.h>

int main(){
    int n;
    printf("Enter number of bits: ");
    scanf("%d", &n);

    int data[n], transmitted[n+1], received[n+1];

    printf("PARITY GENERATOR\n");
    int parity = 0;
    printf("Enter %d databits(0 or 1): ", n);
    for(int i=0; i<n; i++){
        scanf("%1d", &data[i]);
        transmitted[i] = data[i];
        parity ^= data[i];
    }

    int choice;
    printf("Enter 1 for Even and 2 for Odd Parity: ");
    scanf("%d", &choice);
    if(choice == 1){
        printf("Even chosen\n");
    } else{
        parity = 1-parity;
        printf("Odd Chosen\n");
    }
    printf("Actual Data: ");
    for(int i=0; i<n; i++){
        printf("%d", data[i]);
    }
    printf("\n");

    printf("Transmitted Data: ");
    transmitted[n] = parity;
    for(int i=0; i<=n; i++){
        printf("%d", transmitted[i]);
    }
    printf("\n");

    printf("\n---PARITY CHECKER---\n");
    int rparity = 0;
    printf("Enter received %d bits (including parity bit): ", n+1);
    for(int i=0; i<n+1; i++){
        scanf("%1d", &received[i]);
    }
    int ones = 0;
    for(int i=0; i<n+1; i++){
        if(received[i] == 1){
            ones++;
        }
    }
    rparity = ones % 2;
    int parity_type;
    printf("Enter 1 if Eevn and 2 if Odd: \n");
    scanf("%d", &parity_type);

    if(parity_type == 1){
        if(rparity == 0){
            printf("NO ERROR\n");
        } else{
            printf("ERROR\n");
        }
    } else if(parity_type == 2){
        if(rparity == 0){
            printf("ERROR\n");
        } else{
            printf("NO ERROR\n");
        }
    } else{
        printf("Invalid parity!\n");
    }
    return 0;
}