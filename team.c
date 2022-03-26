#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

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
void create_team(char team_name[100], char project_name[100], char manager[100], char member[3][50]){

    // findout the last element for append
    int i = 0;
    while(teams[i].team_id != NULL){
        i++;
    }

    teams[i].team_id = i;
    strcpy( teams[i].team_name,team_name);
    strcpy( teams[i].project_name,project_name);
    strcpy( teams[i].manager,manager);
    strcpy( teams[i].member[0],member[0]);
    strcpy( teams[i].member[1],member[1]);
    strcpy( teams[i].member[2],member[2]);
    print_team_name(i);
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


void print_team_name(int i){
    printf("Project Team %s is created\n", teams[i].team_name);

    //testing
    printf("Detail: %i %s %s %s %s %s", teams[i].team_id + 1, teams[i].project_name, teams[i].manager, teams[i].member[0], teams[i].member[1], teams[i].member[2]);
}

