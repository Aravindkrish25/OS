#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("\t\t\tRound Robin Scheduling\n");
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    int tq;
    printf("Enter the time quantum:");
    scanf("%d",&tq);
    int arr[n],bur[n],com[n],tt[n],wt[n],b[n],ind[n],temp;
    for(int i=0;i<n;i++){
        printf("Arrival time for process %d\n",i+1);
        scanf("%d",&arr[i]);
        printf("Burst time of process %d\n",i+1);
        scanf("%d",&bur[i]);
        b[i]=bur[i];
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
            temp=b[i];
            b[i]=b[i+1];
            b[i+1]=temp;
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
    int finish=0,time=0;
    int a=-1,front=-1,rear=-1;
    int readyq[1000], already[n];
    for(int i=0;i<n;i++){
        already[i]=0;
    }
    for(;finish<n;){
        if ((front== -1) && (rear==-1)){
            time=arr[a+1];
            readyq[++front]=a+1;
            readyq[++rear]=a+1;
            already[a+1]=1;
        }
        else if (rear < front){
            rear=-1;
            front=-1;
        }
        else{
            a=readyq[front];
            front+=1;
            if (bur[a]>0){
                if (bur[a]>tq){
                    time=time+tq;
                    bur[a]-=tq;
                    for(int i=a+1;i<n;i++){
                        if (arr[i]<=time && already[i]==0){
                            readyq[++rear]=i;
                            already[i]=1;
                        }
                    }
                    readyq[++rear]=a;
                }
                else if(bur[a]<=tq){
                    time+=bur[a];
                    bur[a]=0;
                    com[a]=time;
                    finish+=1;
                    for(int j=a+1;j<n;j++){
                        if(arr[j]<=time && already[j]==0){
                            readyq[++rear]=j;
                            already[j]=1;
                        }
                    }
                }
            }
        }
    }
     float att=0,awt=0;
    for(int i=0;i<n;i++){
        tt[i]=abs(com[i]-arr[i]);
        att+=tt[i];
        wt[i]=abs(tt[i]-b[i]);
        awt+=wt[i];
    }
    awt=awt/n;
    att=att/n;
     printf("process\tAT\tBT\tCT\tTT\tWT\n");
    for(int i=0;i<n;i++){
        printf("p%d\t\t",ind[i]);
        printf("%d\t%d\t%d\t%d\t%d\t\n",arr[i],b[i],com[i],tt[i],wt[i]);
    }
    printf("\nAverage Turn around time :%.3f",att);
    printf("\nAverage Waiting time: %.3f",awt);
    return 0;
}

