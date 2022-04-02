#include <stdio.h>
#include <string.h>
#include "team.c"

void PrintMenu(){
    printf("\n\t~~ WELCOME TO PolyStar ~~\n\n");
    printf("1.\tCreate Project Team\n\n");
    printf("2.\tProject Meeting Request\n");
    printf("\t2a.  Single input\n");
    printf("\t2b.  Batch input\n");
    printf("\t2c.  Meeting Attendance\n\n");
    printf("3.\tPrint Meeting Schedule\n");
    printf("\t3a.  FCFS (First Come First Served)\n");
    printf("\t3b.  XXXX (Another algorithm implemented)\n");
    printf("\t3c.  YYYY (Attendance Report)\n\n");
    printf("4.\tExit\n");
}

int main(){
    Team_Init();
    while(1){
        char choice[2];
        PrintMenu();
        printf("  Enter an option: ");
        scanf("%s", choice);
        if (strcmp(choice, "0") == 0){

        }else if (strcmp(choice, "1") == 0){
            printf("choice %s\n", choice);      //debug use
            while(1){
                char team_name[50], project_name[50], manager[50], member[3][50];
                printf("Enter> ");
                scanf("%s", team_name);
                if (strcmp(team_name, "0") == 0) break;
                scanf("%s", project_name);
                scanf("%s", manager);
                scanf("%s", member[0]);
                scanf("%s", member[1]);
                scanf("%s", member[2]);
                // printf("%s %s %s %s %s %s\n", team_name, project_name, manager, member[0], member[1], member[2]);
                create_team(team_name, project_name, manager, member);
            }
        }else if (strcmp(choice, "2a") == 0){
            printf("choice %s\n", choice);      //debug use
        }else if (strcmp(choice, "2b") == 0){
            printf("choice %s\n", choice);      //debug use
        }else if (strcmp(choice, "2c") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "3a") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "3b") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "3c") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "4") == 0){
            printf("choice %s\n", choice);      //debug use
            break;
        } else{ printf("Unaccepted input, please input the correct input.\n"); }
    }   
    return(0);
}
