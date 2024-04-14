#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
void password_menu();
void Ragister();
void Login();
void forget_password();
void menu();
void Quiz();
void password();
void add_que();
void who();
bool play(int);
struct ques{
    char Que[200];
    char A[30],B[30],C[30],D[30];
    char Ans[2];
};
struct ques Q;
struct user{
    char username[20];
    char gender[2];
    char phone[11];
    char userId[11];
    char Password[12];
};
struct user user;
int main(){
    printf("\n================================\n\n");
    printf(" >>>>> Welcome to GAME  Window <<<\n\n");
    printf("\n=================================\n\n");
    printf("press any key to continue....");
    getch();
    who();
}
void who(){
    int choice ;
    printf("\n\n>> 1: PLAYER \n\n");
    printf(">> 2: MAKER \n\n");
    printf(" WHO ARE YOU : ");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        password_menu();
        break;
        case 2:
        password();
        break;
        default:
        printf("\n Invalid Entry .. ");
    }
}
void password(){

    char user[8];
    char userid[8]={"Admin"};
    char pwd[255];
    char code[255]={"Admin"};

    printf("--------------------\n");
    printf(">>> Login First <<<\n");
    printf("--------------------\n\n");
    printf("Enter your username: ");
    scanf("%s", user);
	printf("Enter your password: ");
    scanf("%s", pwd);

    // verifies the password 
    if(!strcmp(user, userid)){
        if(!strcmp(pwd, code)){
            add_que();
        }
        else{
            printf("\nInvaild Password!\n");
            password();
        }
    }
    else{
        printf("\nInvaild Username!\n");
        password();
    }
}
void password_menu(){
    int choice;
    printf(">> 1. ragister  \n");
    printf(">> 2. Login  \n");
    printf(">> 3. forget password \n");
    fflush(stdin);
    printf("enter choice : ");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        Ragister();
        break;
        case 2:
        Login();
        break;
        case 3:
        forget_password();
        break;
        default:
        printf("Invalid entry ..");
    }
}
void Ragister(){
    struct user user;
    printf("--------------------\n");
    printf(">>> Ragister Yourself <<<\n");
    printf("--------------------\n\n");
    FILE *pF = fopen("temp.txt", "ab");
    if(pF != NULL)
    {
        fflush(stdin);
        printf("Enter the  Name: ");
        gets(user.username);
        printf("Enter Gender [M/F]: ");
        gets(user.gender);
        printf("Enter Phone Number: ");
        gets(user.phone);
        printf("Enter User ID: ");
        gets(user.userId);
        printf("Enter password : ");
        gets(user.Password);
        fwrite(&user,sizeof(user),1,pF);

        printf("\n>>> you Ragister Successfully <<< \n");
    }
    else{
        printf("\n >>>> you have somthing error <<<< \n");
    }
    fclose(pF);
    fflush(stdin);
    printf("Press any key to continue .. ");
    getch();
    password_menu();

}
void Login(){
    struct user user;
    char uid[12];
    char pass[12];
    int found=0;
    printf("--------------------\n");
    printf(">>> Login Yourself <<<\n");
    printf("--------------------\n\n");
    fflush(stdin);
    printf("USERNAME : ");
    gets(uid);

    printf("PASSWORD : ");
    gets(pass);
    FILE *pF = fopen("temp.txt", "rb");
    if(pF == NULL){
        printf("\n You are enable to login ");
    }
    while(fread(&user,sizeof(user),1,pF)==1){
        if(strcmp(user.userId,uid)==0 && strcmp(user.Password,pass)==0){
            printf(" \n\n >> you login succesfully << \n");
            found=1;
           
        }

    }
    fclose(pF);
    if(found==0){
        printf("\n\n >>> You have enterd wrong password or username <<<< \n");
        fflush(stdin);
        printf("press any key to continue : ");
        getch();
        password_menu();
    }
    else{
        fflush(stdin);
        printf("press any key to continue : ");
        getch();
        menu();
    }

    

}
void forget_password(){
    printf("--------------------\n");
    printf(">>> Forget password <<<\n");
    printf("--------------------\n\n");
    struct user user;
    char  pass[12] ,pass1[12];
    int flag=0;
    char find[9];
    srand(time(NULL));
    int n = 1000 + rand()%100;
    printf("CAPTCHA CODE \n  %d \n",n);
    int captcha;
    printf("Enetr captcha value : ");
    scanf("%d",&captcha);
    fflush(stdin);
    if(captcha == n){
        printf("Enter the user ID for forget password : ");
        gets(find);

        FILE *pF = fopen("temp.txt", "rb");
        FILE *pT = fopen("temporary.txt", "ab");

        while(fread(&user,sizeof(struct user),1,pF)==1){
            if(strcmp(find,user.userId)==0){
                fflush(stdin);
                printf(">> Enetr password : ");
                gets(pass);
                printf(">> Confirm password : ");
                gets(pass1);
                if(strcmp(pass , pass1)==0){
                    strcpy(user.Password,pass);
                    fwrite(&user,sizeof(user),1,pT);
                    printf("\n\nProcessing your changes....");
                }
                else{
                    printf("\n password not matched \n"); 
                }
                flag = 1;
            }
            else{
                fwrite(&user,sizeof(user),1,pT);
            }
        }
        fflush(stdin);
        fclose(pF);
        fclose(pT);

        if(flag == 0){
            printf("\n\n-------------------------------\n");
            printf(">>> Record Not Found <<<\n");
            printf("-------------------------------\n\n");
            printf("Redirecting to User Panel...");
            pT = fopen("temporary.txt", "wb");
            fclose(pT);
            printf("\n press key to continue \n");
            getch();
            menu();
        }

        pF = fopen("temp.txt", "wb");
        fclose(pF);

        pF = fopen("temp.txt", "ab");
        pT = fopen("temporary.txt", "rb");

        while(fread(&user,sizeof(user),1,pT)==1){
            fwrite(&user,sizeof(user),1,pF);
        }
        fclose(pF);
        fclose(pT);
        pT = fopen("temporary.txt", "wb");
        fclose(pT);
    }
    else{
        printf("\n Invalid captcha code \n");
    }
    printf("\n press any key to continue ");
    getch();
    password_menu();
}
void menu(){
    int choice;
    system("cls");
    printf("\n---------------------------------------------\n");
    printf("\t\t\t\t>>> GAME MENU <<<\n");
    printf("-----------------------------------------------\n\n");
    printf("------------------------------------------------\n");
    printf(" 1 : Quiz Game ");
    printf("\n-----------------------------------------------\n");
    printf("Enter Choice : "); 
    scanf("%d",&choice);
    switch(choice){
        case 1:
        Quiz();
        break;
        default:
        printf("\n Invalid Entry .....\n");
    }
}
void Quiz(){
    int choice;
    int counter =0;
    int points=0;
    int Wans=0,Rans=0;
    char choose[2];
    printf("\n PLAY GAME ");
    printf("\n press 1 : ");
    printf("\n Quit Game ");
    scanf("%d",&choice);
    if(play(choice)){
        FILE *fptr;
        fptr = fopen("Question.txt","rb");
        if(fptr == NULL){
            printf("\n Somthing Went Wrong .....");
        }
        while(fread(&Q,sizeof(Q),1,fptr)==1){
            printf("\n---------------------------------------------------------------\n");
            printf("Q %d : %s \n",counter,Q.Que);
            printf("(A) %s \n",Q.A);
            printf("(B) %s \n",Q.B);
            printf("(C) %s \n",Q.C);
            printf("(D) %s \n",Q.D);
            printf("\n----------------------------------------------------------------\n");
            printf("Choose Answer : ");
            fflush(stdin);
            gets(choose);
	    strupr(choose);
            if(strcmp(choose,Q.Ans)==0){
                printf("Correct Answer : %s \n",Q.Ans);
                points+=5;
                Rans++;
            }
            else{
                points--;
                Wans++;
            }
            fflush(stdin);
            counter++;
            printf("\t\t>>>> EXIT <<<< press 1 \n");
            printf("\n\t\t >>> NEXT <<<< \n");
            int n;
            scanf("%d",&n);
            if(n==1){
                fclose(fptr);
                printf("\n====================================\n\n");
                printf("\n\t\t YOU SCORED  : %d \n",points);
                printf("\n\t\t YOU ATTEMPT : %d \n",counter);
                printf("\n\t\t CORRECT ANSWER : %d \n",Rans);
                printf("\n\t\t WRONG ANSWER : %d \n",Wans);
                printf("\n=====================================\n\n");
                printf(" \n Press any key to Exit ");
                getch();
                menu();
            }            
        }
        fclose(fptr);
    }
    else{
        exit(0);
    }
    fflush(stdin);
    printf("\n====================================\n\n");
    printf("\n\t\t YOU SCORED  : %d \n",points);
    printf("\n\t\t YOU ATTEMPT : %d \n",counter);
    printf("\n\t\t CORRECT ANSWER : %d \n",Rans);
    printf("\n\t\t WRONG ANSWER : %d \n",Wans);
    printf("\n=====================================\n\n");
    printf("press any key to continue ..");
    getch();
    menu();

}
bool play(int choice){
    if(choice==1){
        printf("\n===============\n");
        printf("||  PLAY GAME  ||");
        printf("\n==================\n");
        printf("\n\n\n===================\n");
        printf("||   START     ||");
        printf("\n======================\n\n");
        getch();
        return true;
    }
    else{
        printf("\n==============\n");
        printf("\n||     EXIT   ||\n");
        printf("\n================\n\n");
        getch();
        return false;
    }
}
void add_que(){
    char another='Y';
    FILE *fptr;
    fptr=fopen("Question.txt","ab");
    fflush(stdin);
    while(another=='Y' || another=='y'){
        printf("Enter Question ");
        gets(Q.Que);
        printf("Enter Option (A) ");
        gets(Q.A);
        printf("Enter Option (B) ");
        gets(Q.B);
        printf("Enter Option (C) ");
        gets(Q.C);
        printf("Enter Option (D) ");
        gets(Q.D);
        printf("Enter Option (Ans) ");
        gets(Q.Ans);
        fwrite(&Q,sizeof(Q),1,fptr);
        fflush(stdin);
        printf("DO YOU WANT TO ADD MORE QUESTION : ");
        scanf("%c",&another);

    }
    fclose(fptr);
    fflush(stdin);
    printf("press any key to continue .....");
    getch();
    who();
}
