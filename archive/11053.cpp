#include <stdio.h>

int lis[1000]={0,}; // longest increasing subsequence

int main(){
    int N,A_i,flag=1;
    int ans=0;

    scanf(" %d",&N);

    for(int i=0;i<N;i++){
        scanf(" %d",&A_i);
        int j=ans;
        while(flag){
            if (j<0) break;
            if (ans == 0) {
                //initial\nanswer
                ans++;
                lis[0]=A_i;
                break;
            }
            else if (lis[ans-1]<A_i){
                // bigest number
                lis[ans]=A_i;
                ans++;
                break;
            }
            else if (lis[j-1]==A_i){
                break;
            }
            else if (lis[j-1]<A_i){
                lis[j]=A_i;
                break;
            }
            j--;
        }
    }
    printf("%d",ans);

    return 0;
}