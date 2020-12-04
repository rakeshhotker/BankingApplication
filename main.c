#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//this is verhoeff's algo for checking whether a number qualifies as an aadhar Number.
static int verhoeff_d[10][10]  = {
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  {1, 2, 3, 4, 0, 6, 7, 8, 9, 5},
  {2, 3, 4, 0, 1, 7, 8, 9, 5, 6},
  {3, 4, 0, 1, 2, 8, 9, 5, 6, 7},
  {4, 0, 1, 2, 3, 9, 5, 6, 7, 8},
  {5, 9, 8, 7, 6, 0, 4, 3, 2, 1},
  {6, 5, 9, 8, 7, 1, 0, 4, 3, 2},
  {7, 6, 5, 9, 8, 2, 1, 0, 4, 3},
  {8, 7, 6, 5, 9, 3, 2, 1, 0, 4},
  {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
};
static int verhoeff_p[8][10] = {
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  {1, 5, 7, 6, 2, 8, 3, 0, 9, 4},
  {5, 8, 0, 3, 7, 9, 6, 1, 4, 2},
  {8, 9, 1, 6, 0, 4, 3, 5, 2, 7},
  {9, 4, 5, 3, 1, 2, 6, 8, 7, 0},
  {4, 2, 8, 6, 5, 7, 3, 9, 0, 1},
  {2, 7, 9, 3, 8, 0, 6, 4, 1, 5},
  {7, 0, 4, 6, 9, 1, 3, 2, 5, 8}
};

static int verhoeff_inv[] = {0, 4, 3, 2, 1, 5, 6, 7, 8, 9};

/*static int generate_verhoeff(const char* num)
{
  int c;
  int len;
  c = 0;
  len = strlen(num);
  for(int i = 0; i < len; i++)
    c = verhoeff_d[c][verhoeff_p[((i + 1) % 8)][num[len - i -1] - '0']];
  return verhoeff_inv[c];
}
*/
static int validate_verhoeff(const char* num)
{
    int c;
    int len;
    c=0;
    len=strlen(num);
    for(int i=0;i<len;i++)
    {
        c=verhoeff_d[c][verhoeff_p[(i%8)][num[len-i-1]-'0']];
    }
    return (c==0);
}
struct customer
{
    char fileName[30];
    char aadharNumber[12];
    char password[8];
    int deposit;
    int withdraw;
    int balance;
}create,retrieve;

void fordelay(int j)
{
    int i,k;
    for(i=0;i<j;i++)
    {
        k=i;
    }
}
void new_acc()
{
    char aadharNumber[12];
    printf("Enter your aadhar Number(Remember it's 12 digits)");
    scanf("%s",&aadharNumber);
    int len=strlen(aadharNumber);
    if(len<12)
    {
        printf("You didn't enter 12 digit aadhar Number!");
        menu();
    }
    int a=validate_verhoeff(aadharNumber);
    if(a==0)
    {
        printf("Incorrect aadhar Number!");
        menu();
    }
    printf("\nAadhar Verified Successfully!");
    for(int i=0;i<12;i++)
    {
        create.aadharNumber[i]=aadharNumber[i];
    }
    for(int i=0;i<10;i++)
    {
        create.fileName[i]=create.aadharNumber[i];
    }
    FILE *check;
    check=fopen(create.fileName,"r");
    if(check!=NULL)
    {
        printf("Account already exists!");
        menu();
    }
    printf("Set your password:");
    for(int i=0;i<8;i++)
    {
        create.password[i]=getch();
        printf("*");
    }
    create.balance=0;
    FILE *ptr;
    ptr=fopen(create.fileName,"w");
    fwrite(&create,sizeof(struct customer),1,ptr);
    fclose(ptr);
    struct customer showcase;
    FILE *read;
    read=fopen(create.fileName,"r");
    printf("\n\nAccount created successfully\t(Note down your account number and remember your password for future reference)");
    while(fread(&showcase,sizeof(struct customer),1,read))
    {
        printf("\nAccountNumber=%s",showcase.fileName);
    }
    fclose(read);
    int choice;
    printf("\nChoose 1 to return to main menu or 0 to exit:\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        menu();
    }
    else
    {
        printf("Be aware bank never calls you to ask for any details\n");
        exit(0);
    }
}
void transact(char *accountNumber)
{
    int deposit,withdraw;
    FILE *ptr;
    ptr=fopen(accountNumber,"r");
    if(ptr==NULL)
    {
        printf("Account doesn't exist!");
        return;
    }
    fclose(ptr);
    int choice;
    printf("\nChoose:\n\4 1 for deposit\n\4 2 for withdraw\n\4 3 for account_balance\n\4 4 for transferring funds\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        ptr=fopen(accountNumber,"r");
        printf("\nEnter the amount you want to deposit");
        scanf("%d",&deposit);
        fread(&create,sizeof(struct customer),1,ptr);
        create.balance+=deposit;
        //create.deposit+=deposit;
        fclose(ptr);
        ptr=fopen(accountNumber,"w");
        fwrite(&create,sizeof(struct customer),1,ptr);
        fclose(ptr);
        break;
    case 2:
        ptr=fopen(accountNumber,"r");
        printf("\nEnter the amount you want to withdraw");
        scanf("%d",&withdraw);
        fread(&create,sizeof(struct customer),1,ptr);
        if(withdraw>create.balance)
        {
            printf("\nYou don't have sufficient balance, try something below %d",create.balance);
        }
        else{
            create.balance-=withdraw;
            printf("\n\t%d Withdrawn successfully",withdraw);
            fclose(ptr);
            ptr=fopen(accountNumber,"w");
            fwrite(&create,sizeof(struct customer),1,ptr);
            fclose(ptr);
        }
        break;
    case 3:
        ptr=fopen(accountNumber,"r");
        printf("\nBalance in your account");
        fread(&retrieve,sizeof(struct customer),1,ptr);
        printf("\t$%d",retrieve.balance);
        fclose(ptr);
        break;
    case 4:
        transfer_funds(accountNumber);
        break;
    }
    int options;
    printf("\n\t\t\t\tChoose 1 to continue transacting or 0 to return to main menu.");
    scanf("%d",&options);
    if(options==1)
    {
        transact(accountNumber);
    }
    else
    {
        menu();
    }

    /*Testing phase code*/
    /*struct customer showcase;
    FILE *read;
    read=fopen(accountNumber,"r");
    fread(&showcase,sizeof(struct customer),1,read);
    printf("%d",showcase.balance);
    fclose(read);*/
}
void login()
{
    char accountNumber[20];
    char password[8];
    printf("\t\t\t\t\tEnter your 10 digit account Number:");
    scanf("%s",&accountNumber);
    printf("\t\t\t\t\tEnter your password:");
    for(int i=0;i<8;i++)
    {
        password[i]=getch();
        printf("*");
    }
    FILE *ptr;
    ptr=fopen(accountNumber,"r");
    fread(&retrieve,sizeof(struct customer),1,ptr);
    if(strncmp(accountNumber,retrieve.fileName,sizeof(retrieve.fileName))==0 && strncmp(password,retrieve.password,sizeof(retrieve.password))==0)
    {
        printf("\n\n\t\t\t\tLogin successful\n");
        int choice;
        printf("\n\n\t\t\t\tChoose 1 to do transactions or 0 to go back to main menu:\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            transact(accountNumber);
        }
        else
        {
            menu();
        }
    }
    else
    {
        printf("\n\n\t\t\t\tWrong Credentials mate! you got to go!");
        menu();
    }
}
void transfer_funds(char * User_accountNumber)
{
    char accountNumber[10];
    printf("\n\t\t\t\tEnter the account number, you want to transfer funds to.");
    scanf("%s",&accountNumber);
    if(strncmp(accountNumber,User_accountNumber,sizeof(User_accountNumber))==0)
    {
        printf("You have entered your own number,");
        transact(User_accountNumber);
    }
    FILE *ptr;
    ptr=fopen(accountNumber,"r");
    if(ptr==NULL)
    {
        printf("\t\t\t\tAccount doesn't exist");
        menu();
    }
    else
    {
        int amount;
        printf("\n\t\t\t\tEnter the amount you want to transfer:\n");
        scanf("%d",&amount);
        /*Need to check if the user account has enough balance*/
        FILE *ptr2;
        ptr2=fopen(User_accountNumber,"r");
        fread(&retrieve,sizeof(struct customer),1,ptr2);
        if(retrieve.balance<=amount)
        {
            printf("\t\t\t\tInsufficient balance in your account:");
            fclose(ptr2);
            transact(User_accountNumber);
        }
        else
        {
            /*adding amount to the other user*/
            fread(&create,sizeof(struct customer),1,ptr);
            create.balance+=amount;
            fclose(ptr);
            FILE *ptr1;
            ptr1=fopen(accountNumber,"w");
            fwrite(&create,sizeof(struct customer),1,ptr);
            fclose(ptr1);
            /*substracting from the current_user*/
            retrieve.balance-=amount;
            fclose(ptr2);
            ptr2=fopen(User_accountNumber,"w");
            fwrite(&retrieve,sizeof(struct customer),1,ptr2);
            fclose(ptr2);
            printf("Funds Transferred Successfully");
        }

    }
    int choice;
    printf("\n\t\t\t\tChoose 1 to return to menu\t2 to exit");
    scanf("%d",&choice);
    if(choice==1)
    {
        menu();
    }
    else
    {
        printf("\n\t\t\t\tHave a nice day!");
    }
}
void menu()
{
    int choice;
    printf("\n\n\n\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO YOUR BANK \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\n\t\t\t\t\t\xB1\xB1\xB1\xB1\xB1\xB1\xB1 Choose your options \xB1\xB1\xB1\xB1\xB1\xB1\xB1");
    printf("\n\n\t\t\t\t\t\4 1.Create new Account\t\t\4 2.Login\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:new_acc();
        break;
        case 2:login();
        break;
        default:exit(0);
        break;
    }
}
int main()
{
    menu();
    fordelay(100000);
    return 0;
}
