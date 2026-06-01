#include<stdio.h>
#define SIZE 4
void binaryAddition(int a[],int b[],int result[]){
    int carry = 0;
    for(int i=SIZE-1;i>=0;i--){
        int sum = a[i]+b[i]+carry;
        result[i] = sum%2;
        carry = sum/2;
    }
    //carry wrapping
    while(carry){
        for(int i=SIZE-1;i>=0;i--){
            int sum = result[i]+carry;
            result[i] = sum%2;
            carry = sum/2;
            if(carry == 0){
                break;
            }
        }
    }
}
int main(){
    int n,i,j;
    printf("\nEnter the number of groups to which the databits will be divided : ");
    scanf("%d",&n);
    int data[n][SIZE];


    // Sender side
    
    for(i=0;i<n;i++){
        printf("\n Enter the databits of %d %d-bit groups : ",n,SIZE);
        for(j=0;j<SIZE;j++){
            scanf("%d",&data[i][j]);
        }
    }
    // perform the binary addition between each groups of databits
    int sum[SIZE] = {0};
    for(i=0;i<n;i++){
        binaryAddition(sum,data[i],sum);
    }
    // calculate the checksum by complementing the sum
    int checksum[SIZE] = {0};
    for(i=0;i<SIZE;i++){
        checksum[i] = 1-sum[i];
    }
    printf("\nChecksum = ");
    for(i=0;i<SIZE;i++){
        printf("%d",checksum[i]);
    }

    // Receiver side
    int received[n+1][SIZE];
    printf("\nEnter the received databits along with the checksum bits : ");
    for(i=0;i<n+1;i++){
        for(j=0;j<SIZE;j++){
            scanf("%d",&received[i][j]);
        }
    }
    int rsum[SIZE] = {0};
    for(i=0;i<n+1;i++){
        binaryAddition(rsum,received[i],rsum);
    }
    int rchecksum[SIZE];
    for(i=0;i<SIZE;i++){
        rchecksum[i] = 1-rsum[i];
    }

    int error = 0;
    for(i=0;i<SIZE;i++){
        if(rchecksum[i] != 0){
            error = 1;
            break;
        }
    }
    if(error){
        printf("\nError Detected!!!\n");
    }
    else{
        printf("\nNo Error Detected!!!\n");
    }

    return 0;

}