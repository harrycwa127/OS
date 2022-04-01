#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

struct Team{
    int team_id;
    char team_name[100];                 // the name of the teams
    // struct Project projects[];   // the list of project in the teams
    char project_name[100];             // name of the project
    char manager[100];                  // only 1 manage
    char member[3][50];                // three member
    time_t dateTime;
    float duration;
};

struct Team teams[1000];
int team_counter;
char t_team_name[100], t_project_name[100], t_manager[100], t_member[3][50];

void print_team_name(int i){
    printf(">>>>>> Project Team %s is created\n", teams[i].team_name);
}

void create_team(){
    int i;
    teams[team_counter].team_id = team_counter + 1;
    strcpy( teams[team_counter].team_name,t_team_name);
    strcpy( teams[team_counter].project_name,t_project_name);
    strcpy( teams[team_counter].manager,t_manager);
    for (i = 0; i < 3; i++){
        strcpy(teams[team_counter].member[i],t_member[i]);
    }
    print_team_name(team_counter);
    team_counter++;
}

int input_team(){
    char str[100];
    char temp; //for clear buffer
    int i;
    int fail_create = 0; //0 = false(input is correct) 1 = true
    printf("Enter: ");
    scanf("%c",&temp);
    scanf("%[^\n]s",str);
    char * token = strtok(str, " ");
    strcpy(t_team_name,token);
    token = strtok(NULL, " ");
    strcpy(t_project_name,token);
    for(i = 0; i < team_counter; i++){
        //printf("Project name[]: %s Project name:%s\n", teams[i].project_name,project_name);
        if(strcmp(teams[i].project_name, t_project_name) == 0){
            printf("Project name: %s has been created\n", t_project_name);
            fail_create = 1;
        }
    }
       
    token = strtok(NULL, " ");
    strcpy(t_manager,token);
    token = strtok(NULL, " ");
    i = 0;
    //
    while (token != NULL){
        if(i > 3){
            break;
        }
        strcpy(t_member[i],token);
        token = strtok(NULL, " ");
        i++;
    }
    //error handle :the number of member more than 3
    if (i < 1 || i > 3){
        printf("Not accepcted the number of member more than 3 or less than 1\n");
        fail_create = 1;
    }
    if(fail_create == 0){
        create_team();
    }
    return fail_create;
}

time_t dateTimeFormatter(char date[10], char time[5])
{
    int year = 0, month = 0, day = 0, hour = 0, min = 0;
    time_t dateTime = 0;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) == 3 && sscanf(time, "%2d:%2d", &hour, &min) == 2){
        struct tm t = {0};
        t.tm_year = year - 1900; /* years since 1900 */
        t.tm_mon = month - 1;
        t.tm_mday = day;
        t.tm_hour = hour;
        t.tm_min = min;
        if ((dateTime = mktime(&t)) == (time_t)-1) 
            printf("Could not convert time input to time_t\n");
    } else printf("The input was not a valid time format\n");
    return dateTime;
}
