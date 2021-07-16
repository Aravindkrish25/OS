#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *adder(float *ar)
{
    printf("\n\nAdder Thread is called\n");
    printf("\n%f + %f = _____\n",ar[0],ar[1]);
    printf("\nThe result is %f  \n",ar[0]+ar[1]);
    printf("\nAddition thread executed \n");
    ar[0]=ar[0]+ar[1];
    return NULL;
}
void *subtract(float * ar)
{
    printf("\n\nSubtracter Thread is called\n");
    printf("\n%f - %f = _____\n",ar[0],ar[1]);
    printf("\nThe result is %f  \n",ar[0]-ar[1]);
    printf("\nSubtract thread executed \n");
    ar[0]=ar[0]-ar[1];
    return NULL;
}
void *multiply(float * ar)
{
    printf("\n\nMultiplier Thread is called\n");
    printf("\n%f x %f = _____\n",ar[0],ar[1]);
    printf("\nThe result is %f  \n",ar[0] *ar[1]);
    ar[0]*=ar[1];
    printf("\nMultiplier thread executed \n");
    return NULL;
}
void * divide(float * ar)
{
    printf("\n\nDivider Thread is called\n");
    printf("\n%f / %f = _____\n",ar[0],ar[1]);
    if(ar[1]!=0)
    {
    printf("\nThe result is %f  \n",ar[0]/ar[1]);
    ar[0]=ar[0]/ar[1];
    printf("\nDivision thread executed \n");
    }
    else
    {
        printf("\nZero division error!!!");
        exit(0);
    }
    return NULL;
}

int main()
{
    system("clear");
    pthread_t add,sub,mul,div;
    printf("\t\t\t\t\tThreaded Calculator\n\n");
    float a[2];
    int d=1;
    char c;
    printf("Enter the operand:");
    scanf("%f",&a[0]);
    printf("\nOperand and operator (+,-,*,/)\n");
    scanf("%f\n",&a[1]);
    c=getchar();
    loop:
    while (d!=0)
    {
        if (c=='+')
        {
            pthread_create(&add, NULL, adder,&a);
            pthread_join(add, NULL);
        }
        else if(c=='-')
        {
            pthread_create(&sub, NULL,subtract,&a);
            pthread_join(sub, NULL);
        }
        else if( c=='*')
        {
            pthread_create(&mul, NULL,multiply,&a);
            pthread_join(mul, NULL);
        }
        else if(c=='/')
        {
            pthread_create(&div, NULL,divide,&a);
            pthread_join(div, NULL);
        }
        else if ((c!='+')||(c!='-')||(c!='*')||(c!='/')){

            printf("\nInvalid Operator\n");
        }
        printf("\n\nEnter 0 to end calculator, press any number to continue\n");
        scanf("%d",&d);
        if(d==0)
        {
            system("clear");
            printf(" \n\nFinal Result = %f",a[0]);
            exit(0);
        }
        else
        {
        printf("\033[0;0H\033[2J");
        printf("\nResult = %f",a[0]);
        printf("\nOperand and operator (+,-,*,/) \n");
        scanf("%f\n",&a[1]);
        c=getchar();
        }
    }
}

