#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("clear");
    printf("\t\t\t\t\t\t\t BANKER's SAFTEY ALGORITHM\n\n");
    int i,j,nop,nor;
    printf("Enter the number of processes  :  ");
    scanf("%d",&nop);
    printf("\nEnter the number of resources  :  ");
    scanf("%d",&nor);
    int max[nop][nor],alloc[nop][nor],need[nop][nor],total[nor],avail[nor],used[nor],safe[nop],comp[nop],finish=0;
    int dead=0;
    for(i=0;i<nor;i++){
        used[i]=0;
    }
    for(i=0;i<nop;i++){
        safe[i]=-1;
        comp[i]=0;
    }
    printf("\nEnter the maximum matrix [%d][%d] : \n",nop,nor);

    for(i=0;i<nop;i++){
        for(j=0;j<nor;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nEnter the allocated matrix [%d][%d] : \n",nop,nor);
    for(i=0;i<nop;i++){
        for(j=0;j<nor;j++){
            scanf("%d",&alloc[i][j]);
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("\nTotal resources  [%d]: \n",nor);
    for(i=0;i<nor;i++){
        scanf("%d",&total[i]);
    }
    for(i=0;i<nor;i++){
        for(j=0;j<nop;j++){
            used[i]+=alloc[j][i];
        }
        avail[i]=total[i]-used[i];
    }
    int count=0;
    i=0;
    while (finish<nop && dead+finish!=nop){
        if(comp[i]==0){
        int d=0;
        for(j=0;j<nor;j++){
            if (avail[j]>=need[i][j]){
            d+=1;
            }
        }
        if(d==nor){
            dead=0;
            d=0;
            safe[count++]=i;
            comp[i]=1;
            finish+=1;
            for(int k=0;k<nor;k++){
                avail[k]+=alloc[i][k];
            }

        }
        else{
            dead+=1;
        }
    }
    i=(i+1)%nop;
    }
    if (dead+finish==nop && finish < nop){
        printf("Deadlock!!!");
        printf("No Safe Sequence Possible");
    }
    else{
    printf("\nSafe sequence : ");
    for(i=0;i<nop;i++){
        if (i!=nop-1){
        printf("p%d -->  ",safe[i]);
        }
        else{
            printf("p%d \n\n\n",safe[i]);
        }
    }
}

    return 0;

}
