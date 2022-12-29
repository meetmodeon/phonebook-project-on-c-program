/*A computer Phone Book containing name of persons, their home, office and mobile phone numbers has to 
be prepared. This book should have the necessary provision for adding,editing and deleting phone numbers and display the phone
number of any person from the Phone Book as and when required*/
/*The following program keeps a track of the telephone numbers of different persons. It works like a telephone index. Through the
program,telephone numbers of a person can be added, edited, and deleted. Three telephone numbers(home, office, and mobile)
are maintained along with the name of the person. All the records can be displayed page wise. The searching of a record can also be
performed be inputting the name of the person. Here a binary file is used to store the records. The access method is chosen as 
as random Careful study of the program will clarify the following*/
/*
>>The use of fread(),fwrite(),rewind()
>>the concept of binary files with random access
>>Sorting of records stored in a file.
*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
struct student
{
    char name[75];
    double home_ph,off_ph,mob_ph;
}s,arr[100],temp;
long int recsize;
FILE *fp,*ft;
void add(void);
void display(void);
void end(void);
void search(void);
void modify(void);
void delet(void);
int i,c,k;
int main(void)
{
    int ch,i,c,k,flag,dis,no;
    recsize=sizeof(s);
    fp=fopen("pbook.dat","rb+");
    if(fp==NULL)
    {
        fp=fopen("pbook.dat","wb+");
        if(fp==NULL)
        {
        printf("\n\n\tFile Opening error!");
        getch();
        exit(0);
        }
    }
    while(1)
    {
        printf("\n\t 1 : ADD");
        printf("\n\t 2 : MODIFY");
        printf("\n\t 3 : DELETE");
        printf("\n\t 4 : SEARCH");
        printf("\n\t 5 : DISPLAY ALL");
        printf("\n\t 6 : EXIT");
        printf("\n\t Enter your choice(1-6)?");
        fflush(stdin);
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            add();
            break;
            case 2:
            modify();
            break;
            case 4:
            search();
            break;
            case 3:
            delet();
            break;
            case 5:
            display();
            break;
            case 6:
            exit(0);
            break;

        }
    }
    return 0;
}
void add(void)
{
    fseek(fp,0,2);
    printf("\n\n\tEnter Name :");
    scanf("%[^\n]",s.name);
    fflush(stdin);
    printf("\tEnter Phone Numbers(0 if a phone number does not exist)\n");
    printf("\t\tHome Phone :");
    scanf("%lf",&s.home_ph);
    fflush(stdin);
    printf("\t\tOffice Phone :");
    scanf("%lf",&s.off_ph);
    fflush(stdin);
    printf("\t\tMobile Number :");
    scanf("%lf",&s.mob_ph);
    fflush(stdin);
    fwrite(&s,recsize,1,fp);
    i=0;
    rewind(fp);
    while(fread(&s,recsize,1,fp)==1)
    {
        arr[i]=s;
        i++;
    }
    for(c=0;c<i-1;c++)
    {
        for(k=0;k<i-1;k++)
        {
            if(strcmp(arr[k].name,arr[k+1].name)>0)
            {
                temp=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=temp;
            }
        }
    }
    rewind(fp);
    for(k=0;k<i;k++)
    fwrite(&arr[k],recsize,1,fp);
}
void end(void)
{
    fclose(fp);
    getch();
    exit(0);
}
void display(void)
{
    int no,dis;
    rewind(fp);
    no=1;
    dis=0;
    printf("\n____________________________________\n");
    printf(" __ __N A M E __ __ __ __ __ | __ __ __H O M E_________|_________W O R K__________| _______M O B I L E ______|\n");
    while(fread(&s,recsize,1,fp)==1)
    {
        printf("\n");
        printf("%2d)%-13s\t\t|",no,s.name);
        no++;
        printf("%-12.0lf |",s.home_ph);
        printf("%-12.0lf|",s.off_ph);
        printf("%-12.0lf|\n",s.mob_ph);
        dis++;
        if(dis==15)
        {
            dis=0;
            printf("\n\t\t\t Press ENTER to continue");
            getch();
            printf("\n\n_________________________\n");
            printf("____NAME_________________|_________HOME__________|_____MOBILE________|\n");

        }
    }
}
void search(void)
{
    int flag=0;
    char nm[75];
    rewind(fp);
    printf("\n\n\tEnter the name to be searched :");
    printf("\n\t\tEnter Name :");
    scanf("%[^\n]",nm);
    fflush(stdin);
    while(fread(&s,recsize,1,fp)==1)
    {
        if(strcmp(s.name,nm)==0)
        {
            flag=1;
            printf("\n\t___________Record found__________\n");
            printf("\n\tName : %-15s \n",s.name);
            printf("\tHome Phone :%-12.0lf",s.home_ph);
            printf("\n\tOffice Phone :%-12.0lf",s.off_ph);
        }
    }
    if(flag==0)
    printf("\n\n____RECORD DOES NOT EXIST _______\n\n");
}
void modify(void)
{
    int flag;
    char nm[75];
    rewind(fp);
    printf("\n\n\tEnter the name of the record to be edited :");
    printf("\n\t\tEnter Name :");
    scanf("%[^\n]",nm);
    fflush(stdin);
    flag=0;
    while(fread(&s,recsize,1,fp)==1)
    if(strcmp(s.name,nm)==0)
    flag=1;
    if(flag==0)
    {
        printf("\n\n\t_____RECORD DOES NOT EXIST _____\n\n");
        return;
    }
    rewind(fp);
    while(fread(&s,recsize,1,fp)==1)
    {
        if(strcmp(s.name,nm)==0)
        {
            printf("\n\nEnter new data :");
            printf("\n\n\tEnter Name :");
            scanf("%[^\n]",s.name);
            fflush(stdin);
            printf("\n\n\tEnter Phone Numbers(0 if a phone number does not exist)\n");
            printf("\t\tHome Phone :");
            scanf("%lf",&s.home_ph);
            fflush(stdin);
            printf("\t\tOffice Phone :");
            scanf("%lf",&s.off_ph);
            fflush(stdin);
            printf("\t\tMobile Number :");
            scanf("%lf",&s.mob_ph);
            fflush(stdin);
            fseek(fp,-recsize,1);
            fwrite(&s,recsize,1,fp);
            break;
        }
    }
    i=0;
    rewind(fp);
    while(fread(&s,recsize,1,fp)==1)
    {
        arr[i]=s;
        i++;
    }
    for(c=0;c<i-1;c++)
    {
        for(k=0;k<i-1;k++)
        {
            if(strcmp(arr[k].name,arr[k+1].name)>0)
            {
                temp=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=temp;
            }
        }
    }
    rewind(fp);
    for(k=0;k<i;k++)
    fwrite(&arr[k],recsize,1,fp);
}
void delet(void)
{
    int flag;
    char nm[75];
    rewind(fp);
    ft=fopen("temp.dat","wb+");
    printf("\n\n\tEnter the name to be deleted :");
    printf("\n\t\tEnter Name :");
    scanf("%[^\n]",nm);
    fflush(stdin);
    flag=0;
    while(fread(&s,recsize,1,fp)==1)
    if(strcmp(s.name,nm)==0)
    flag=1;
    if(flag==0)
    {
        printf("\n\t\t____RECORD DOES NOT EXIST _____\n\n");
        return;
    }
    rewind(fp);
    while(fread(&s,recsize,1,fp)==1)
    {
        if(strcmp(s.name,nm)!=0)
        fwrite(&s,recsize,1,ft);
    }
    if(flag==1)
    printf("\n\t\t___________RECORD DELETED_________");
    getch();
    fclose(fp);
    fclose(ft);
    remove("pbook.dat");
    rename("temp.dat","pbook.dat");
    fp=fopen("pbook.dat","rb++");
    i=0;
    rewind(fp);
    while(fread(&s,recsize,1,fp)==1)
    {
        arr[i]=s;
        i++;
    }
    for(c=0;c<i-1;c++)
    {
        for(k=0;k<i-1;k++)
        {
            if(strcmp(arr[k].name,arr[k+1].name)>0)
            {
                temp=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=temp;
            }
        }
    }
    rewind(fp);
    for(k=0;k<i;k++)
    fwrite(&arr[k],recsize,1,fp);
}