#include <stdio.h>
#include "team.c"

void print_main_menu(){
    printf("~~ WELCOME TO PolyStar\n\n");
    printf("1. Create Project Team\n\n");
    printf("2. Project Meeting Request\n");
    printf("\t2a. Single input\n");
    printf("\t2b. Batch input\n");
    printf("\t2c. Meeting Attendance\n\n");
    printf("3. Print Meeting Schedule\n");
    printf("\t3a. FCFS (First Come First Served)\n");
    printf("\t3b. XXXX (Another algorithm implemented)\n");
    printf("\t3c. YYYY (Attendance Report) (if implemented)\n\n");
    printf("4. exit\n");
}

int main(){
    char choice[3];
    do{
        print_main_menu();
        printf("Enter an option:");
        scanf("%s", choice);
        
        if (strcmp(choice, "1") == 0){
            int error = 0; // 0 = false 1 = true
            do{
                error = input_team();
                if(error == 1){
                    do{
                    printf("Fail to creat team, do you want to create again\n");
                    printf("\"0\" to go back to menu ,Input \"1\" to create again\n");
                    scanf("%d", &error);
                    }while(error != 0 && error != 1);
                }else{
                    do{
                    printf("Craetion success, do you want to create new one?\n");
                    printf("\"0\" to go back to menu ,Input \"1\" to create new one\n");
                    scanf("%d", &error);
                    }while(error != 0 && error != 1);
                }
            }while(error != 0);
        } 
        else if (strcmp(choice, "2a") == 0){
            printf("choice %s", choice);
        }
        else if (strcmp(choice, "2b") == 0){
            printf("choice %s", choice);
        }
        else if (strcmp(choice, "2c") == 0){
            printf("choice %s", choice);
        }
        else if (strcmp(choice, "3a") == 0){
            printf("choice %s", choice);
        }
        else if (strcmp(choice, "3b") == 0){
            printf("choice %s", choice);
        }
        else if (strcmp(choice, "3c") == 0){
            printf("choice %s", choice);
        }
        else if (strcmp(choice, "4") == 0)
        {
            printf("choice %s", choice);
            return 0;
        }
        else{
            printf("Unaccepted input, please input the correct input.\n");
            printf("If you chooces the option 2a, please input \"2a\" instead of \"2\" only\n");
            do{
            printf("Enter> ");
            scanf("%s", choice);
            }while(strcmp(choice, "0") == 0);
        }

        // wait for input 0 to back to main <-- ????????
        /*
        do{
            printf("Enter> ");
            scanf("%s", choice);
        }while(strcmp(choice, "0") == 0);
        */
    }while(1);
    return 0;
}