#include <stdio.h>
#include <stdlib.h>
int main()
{
    system("CLS");
    printf("\t\t\t\tFIFO REPLACEMENT ALGORITHM\n\n");
    int nf,np,fault;
    printf("No. of page reads\n");
    scanf("%d",&np);
    printf( "Pages to be accessed:\n");
    int page[np];
    for(int i=0;i<np;i++){
        scanf("%d",&page[i]);
    }
    printf("\nEnter the number of frames:");
    scanf("%d",&nf);
    printf("Frame Size :  %d\n\n",nf);
    int fill=0;
    int frame[nf],i,j;
    for(i=0;i<nf;i++){
        frame[i]=-1;
    }
    printf("\n");
    int ind=0;
    int alr;
    int hit=0;
    fault=0;
    printf("Request -->   Frame\n");
    for(i=0;i<np;i++){
        alr=0;
        for(j=0;j<nf;j++){
            if (frame[j]==page[i]){
                hit+=1;
                alr=1;
                break;
            }
        }
        if(alr==1){
        }
        else if ((fill!=nf)&&(frame[ind]==-1)&&(alr!=1)){
            frame[ind]=page[i];
            fault+=1;
            fill+= 1;
            ind=(ind+1)%nf;
        }
        else if ((fill==nf)&&(frame[ind]!=-1) && (alr!=-1)){
            frame[ind]=page[i];
            fault+=1;
            ind=(ind+1)%nf;
        }
        printf("Access %d -->  ",page[i]);
        for(int s=0;s<nf;s++){
            printf("%d  ",frame[s]);
        }
        printf("\n");
    }
    printf("Faults : %d \n",fault);
    printf("Hits : %d\n\n",hit);
return 0;
}
