#include <stdio.h>
#include <stdlib.h>
int main()
{
    system("clear");
    printf("\t\t\t\tLRU REPLACEMENT ALGORITHM\n\n");
    int nf,np,fault;
    printf("Enter the number of frames: ");
    scanf("%d",&nf);
    printf("No. of page reads: ");
    scanf("%d",&np);
    printf("\nPages to be accessed:\n");
    int page[np];
    for(int i=0;i<np;i++){
        scanf("%d",&page[i]);
    }
    printf("\n");
    int uni[np];
    for(int i=0;i<np;i++){
        uni[i]=page[i];
    }
    int size=np,i,j,k;
    for(i=0; i<size; i++){
        for(j=i+1; j<size; j++){
            if(uni[i] == uni[j]){
                for(k=j; k<size; k++)
                {
                    uni[k] = uni[k + 1];
                }
                size--;
                j--;
            }
        }
    }
    int access[size];
    for(int m=0;m<size;m++){
        access[m]=0;
    }
    int t=0;
    int fill=0;
    int frame[nf];
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
        t+=1;
        alr=0;
        for(j=0;j<nf;j++){
          if (frame[j]==page[i]){
            hit+=1;
            for(int m=0;m<size;m++){
              if (uni[m]==page[i]){
                access[m]=t;
                }
            }
            alr=1;
            break;
          }
        }
        if(alr==1){
          //Nothing
        }
        else {
          ind=fill;
          if ((fill!=nf)&&(frame[ind]==-1)&&(alr!=1)){
              frame[ind]=page[i];
              for(int m=0;m<size;m++){
                  if (uni[m]==page[i]){
                      access[m]=t;
                      break;
                    }
                }
                fault+=1;
                fill+=1;
          }
          else if ((fill==nf)&&(frame[ind]!=-1) && (alr!=-1)){
              int lru=1000;
              int pn;
              for(int n=0;n<nf;n++){
                  for(int m=0;m<size;m++){
                      if (uni[m]==frame[n]){
                          if (access[m]<lru){
                              lru=access[m];
                              pn=uni[m];
                          } 
                      }
                  }
              }
              for(int m=0;m<nf;m++){
                  if (pn==frame[m]){
                    ind=m;
                  }
              }
              frame[ind]=page[i];
              for(int m=0;m<size;m++){
                  if (uni[m]==page[i]){
                      access[m]=t;
                  }
              }
              fault+=1;
          }
      }
      printf("Access %d -->  ",page[i]);
      for(int s=0;s<nf;s++){
          printf("%d  ",frame[s]);
        }
      printf("\n");
      printf("\n");
      }
      printf("Faults : %d \n",fault);
      printf("Hits : %d\n\n",hit);
    return 0;
}

