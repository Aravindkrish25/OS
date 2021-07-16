#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("\t\t\t\t\tShortest Job First Scheduling\n");
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    int arr[n],bur[n],com[n],tt[n],wt[n],b[n],ind[n],temp;
    for(int i=0;i<n;i++){
        printf("Arrival time for process %d\n",i+1);
        scanf("%d",&arr[i]);
        printf("Burst time of process %d\n",i+1 );
        scanf("%d",&bur[i]);
        b[i]=bur[i];
        ind[i]=i+1;
    }
    int finish=0,time=0;
    int a=0;
    for(time=0;finish<n;){
        int f=0;
        int mb=100000;
        for(int j=0;j<n;j++){
            if ((arr[j]<=time)&&(bur[j]>0)&&(bur[j]<mb)){
                a=j;
                mb=bur[j];
                f=1;
            }
        }
        if (f==1){
            com[a]=time+bur[a];
            time=time+bur[a];
            bur[a]=0;
            finish=finish+1;

        }
        else{
            time=time+1;
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
