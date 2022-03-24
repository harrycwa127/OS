#include <stdio.h>
#include <string.h>
#include "team.c"

int main(){
    char choice[2], team_name[50], project_name[50], manager[50], member[3][50];
    int boolean = 1; //0 = flase, 1 = true

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
    
    do{
    printf("  Enter an option: ");
    scanf("%s", choice);

    if (strcmp(choice, "1") == 0){
        printf("choice %s\n", choice);
        boolean = 1;

        scanf("%s %s %s %s %s %s", team_name, project_name, manager, member[0], member[1], member[2]);
        printf("testing: %s %s %s\n", &member[0], &member[1], &member[2]);
        create_team(team_name, project_name, manager, member);
    }
    else if (strcmp(choice, "2a") == 0){
        printf("choice %s\n", choice);
        boolean = 1;
    }
    else if (strcmp(choice, "2b") == 0){
        printf("choice %s\n", choice);
        boolean = 1;
    }
    else if (strcmp(choice, "2c") == 0){
        printf("choice %s\n", choice);
        boolean = 1;
    }
    else if (strcmp(choice, "3a") == 0){
        printf("choice %s\n", choice);
        boolean = 1;
    }
    else if (strcmp(choice, "3b") == 0){
        printf("choice %s\n", choice);
        boolean = 1;
    }
    else if (strcmp(choice, "3c") == 0){
        printf("choice %s\n", choice);
        boolean = 1;
    }
    else if (strcmp(choice, "4") == 0)
    {
        printf("choice %s\n", choice);
        return 0;
    }
    else{
        printf("Unaccepted input, please input the correct input.\n");
        printf("If you chooces the option 2a, please input \"2a\" instead of \"2\" only\n");
        boolean = 0;
    }
    }while(boolean == 0);
    return 0;
}