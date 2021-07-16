#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
struct details
    {
        int accno;
        char name[100];
        float balance;
    }u1,u2,u3;
void open()
{
    system("CLS");
    int flag=0;
    int no;
    char name[100];
    FILE *fp;
    fp=fopen("bankdet.bin","ab+");
    printf("\n\nEnter the account number:");
    scanf("%d",&no);
    printf("Enter the account name:");
    scanf("%s",name);
    while((fread(&u1,sizeof(struct details),1,fp)))
 {
   if(strcmpi(name,u1.name)==0 && no==u1.accno)
   {
    flag=1;
    break;
   }
 }
 if(flag==1)
 {
  printf("\nThe person already has an account.");
  fclose(fp);
  getch();
  return;
 }
 else
 {
   u1.accno=no;
   strcpy(u1.name,name);
   u1.balance=0;
   fwrite(&u1,sizeof(struct details),1,fp);
   printf("\n\nAccount number:%d",u1.accno);
   printf("\nAccount name:%s",u1.name);
 }
 fclose(fp);
 }

void deposit()
{
    system("CLS");
    FILE *fp;
    int no,flag=0;
    float amount;
    fp=fopen("bankdet.bin","rb+");
    printf("\nEnter Account number:");
    scanf("%d",&no);
    while((fread(&u1,sizeof(struct details),1,fp)))
    {
        if(u1.accno==no)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("\nNo account available.");
    }
    else
    {
        printf("\nEnter Amount to be deposited:");
        scanf("%f",&amount);
        u1.balance+=amount;
        fseek(fp,-1*sizeof(struct details),SEEK_CUR);
        fwrite(&u1,sizeof(struct details),1,fp);
        printf("Amount has been deposited successfully.\nBalance:%f",u1.balance);

    }
    fclose(fp);


}
void withdraw()
{
    system("CLS");
    FILE *fp;
    int no,flag=0;
    float amount;
    fp=fopen("bankdet.bin","rb+");
    printf("\nEnter Account number:");
    scanf("%d",&no);
    while((fread(&u1,sizeof(struct details),1,fp)))
    {
        if(u1.accno==no)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("\nNo account available.");
    }
    else
    {
         printf("\nEnter Amount to be withdrawn:");
         scanf("%f",&amount);
         if(amount>u1.balance)
         {
             printf("Insufficient balance");
             fclose(fp);
         }
         else
        {
            u1.balance-=amount;
            fseek(fp,-1*sizeof(struct details),SEEK_CUR);
            fwrite(&u1,sizeof(struct details),1,fp);
            printf("Amount has been withdrawn successfully.\nBalance:%f",u1.balance);
            fclose(fp);


         }

    }

}
void transfer()
{
    system("CLS");
    printf("AMOUNT TRANSFER\n");
    FILE *fp;
    fp=fopen("bankdet.bin","rb+");
    int no1,no2,flag1=0,flag2=0;
    float amount;
    char name1[100],name2[100];
    printf("Enter the account number of Payer:\n");
    scanf("%d",&no1);
    printf("Enter the account name of payer:\n");
    scanf("%s",name1);
    printf("Enter the account number of Payee:\n");
    scanf("%d",&no2);
    printf("Enter the account name of payee:\n");
    scanf("%s",name2);
    while(fread(&u1,sizeof(struct details),1,fp))
    {
        if(u1.accno==no1 && strcmp(u1.name,name1)==0)
        {
            flag1=1;
            break;
        }
    }
    if(flag1==0)
    {
        printf("Payer account not found");
    }
    while(fread(&u2,sizeof(struct details),1,fp))
    {
        if(u2.accno==no2 && strcmp(u2.name,name2)==0)
        {
            flag2=1;
            break;
        }
    }
    if(flag2==0)
    {
        printf("Payee account not found");
    }
    if(flag1==1 && flag2==1)
    {
        printf("\nEnter Amount to be transferred:");
        scanf("%f",&amount);
        if(amount<u1.balance)
        {u1.balance-=amount;
        u2.balance+=amount;
        printf("Payer balance:%f",u1.balance);
        printf("Payee balance:%f",u2.balance);
        }
        else{
            printf("insufficient balance");
        }
        fseek(fp,-1*sizeof(struct details),SEEK_CUR);
        fwrite(&u2,sizeof(struct details),1,fp);
        fseek(fp,0,SEEK_SET);
        while(fread(&u3,sizeof(struct details),1,fp))
        {
            if(u3.accno==no1)
            {
                fseek(fp,-1*sizeof(struct details),SEEK_CUR);
                fwrite(&u1,sizeof(struct details),1,fp);
            }
        }
    }
    fclose(fp);

}
void info()
{
     FILE *fp;
     int no,flag=0;
    fp=fopen("bankdet.bin","rb+");
    printf("\n\nEnter the account number:");
    scanf("%d",&no);
    while((fread(&u1,sizeof(struct details),1,fp)))
 {
   if(no==u1.accno)
   {
    flag=1;
    break;
   }

 }
 if(flag==1)
 {
     printf("Your account name: %s\n",u1.name);
     printf("Your account number: %d\n",u1.accno);
     printf("current balance: %f\n",u1.balance);
     fclose(fp);
 }
 else
 {
    printf("Account not found");
    fclose(fp);

}
}
void aclose()
{
    FILE *fp,*tp;
    fp=fopen("bankdet.bin","rb+");
    tp=fopen("temp.bin","ab+");
    int no,flag=0;
    char name[100];
    printf("Enter your account number");
    scanf("%d",&no);
    printf("enter your account name");
    scanf("%s",&name);
    while((fread(&u1,sizeof(struct details),1,fp)))
    {
        if(strcmpi(name,u1.name)==0 && no==u1.accno)
   {
    flag=1;
    continue;
   }
   fwrite(&u1,sizeof(struct details),1,tp);
    }
    if(flag==0)
    {
        printf("There is no such existing account");
    }
    fclose(tp);
    fclose(fp);
    remove("bankdet.bin");
    rename("temp.bin","bankdet.bin");
    printf("Your Account has been successfully closed");
}
int main()
{
    FILE *fp;
    fp=fopen("bankdet.bin","rb");
    fclose(fp);
    int flag=0,choice,i,j,b;
    while(flag==0)
    {
          printf("Welcome to Aravind's Bank Of India\n");
          printf(" Action to be performed : \n 1.Open account \n 2. Deposit money \n 3. Withdraw money \n 4. Amount transfer\n 5. Account details \n 6.close account\n\n");
          scanf("%d",&choice);
          switch(choice)
          {
              case 1: open();break;
              case 2: deposit();break;
              case 3: withdraw();break;
              case 4: transfer();break;
              case 5: info();break;
              case 6: aclose();break;
              default:printf("invalid choice");
          }
          printf("\n If any other tasks to be done press 0 to continue:\n");
          scanf("%d",&b);
          flag=b;
    }


    return 0;
}
