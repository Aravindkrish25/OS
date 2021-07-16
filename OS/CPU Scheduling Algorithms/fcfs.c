#include <stdio.h>
#include <stdlib.h>
int main(){
int n;
printf("\t\t\tFirst Come First Serve Scheduling\n");
printf("Enter the number of processes\n");
scanf("%d",&n);
int arr[n],bur[n],com[n],tt[n],wt[n],ind[n],temp;
for(int i=0;i<n;i++){
    printf("Arrival time for process %d\n",i+1);
    scanf("%d",&arr[i]);
    printf("Burst time of process %d\n",i+1 );
    scanf("%d",&bur[i]);
    ind[i]=i+1;
}
for(int j=0;j<n;j++){
    int f=0;
    for(int i=0;i<n-j-1;i++){
        if (arr[i]>arr[i+1]){
            temp=arr[i];
            arr[i]=arr[i+1];
            arr[i+1]=temp;
            temp=bur[i];
            bur[i]=bur[i+1];
            bur[i+1]=temp;
            temp=ind[i];
            ind[i]=ind[i+1];
            ind[i+1]=temp;
            f=1;
        }
    }
    if(f==0){
        break;
    }
}
int t=0,c=0;
com[c++]=bur[0]+arr[0];
for(int i=1;i<n;i++){
    if (arr[i]<=com[i-1]){
        com[c++]=com[i-1]+bur[i];
    }
    else{
        com[c++]=arr[i]+bur[i];
    }
}
for(int i=0;i<n;i++){
    tt[i]=com[i]-arr[i];
    wt[i]=abs(tt[i]-bur[i]);
}
printf("process\tAT\tBT\tCT\tTT\tWT\n");
for(int i=0;i<n;i++){
    printf("p%d\t\t",ind[i]);
    printf("%d\t%d\t%d\t%d\t%d\t\n",arr[i],bur[i],com[i],tt[i],wt[i]);
}
return 0;
}
