#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define team_size 1000

struct Team{
    int team_id;
    char team_name[50];
    char project_name[50];
    char manager[50];
    char member[3][50];
    time_t dateTime;
    float duration;
} Team;

struct Team teams[team_size];

void Team_Init(){
    int i;
    for(i=0;i<team_size;i++){
        teams[i].team_id = -1;
        strcpy(teams[i].team_name, "");
        strcpy(teams[i].project_name, "");
        strcpy(teams[i].manager, "");
        strcpy(teams[i].member[0], "");
        strcpy(teams[i].member[1], "");
        strcpy(teams[i].member[2], "");
        teams[i].dateTime = 0;
        teams[i].duration = -1;
    }
}

void print_team_name(int i){
    printf("team id %d\n", teams[i].team_id);
    printf("team_name %s\n", teams[i].team_name);
    printf("project_name %s\n", teams[i].project_name);
    printf("manager %s\n", teams[i].manager);
    printf("member %s\n", teams[i].member[0]);
    printf("member %s\n", teams[i].member[1]);
    printf("member %s\n", teams[i].member[2]);
}

void create_team(char team_name[50], char project_name[50], char manager[50], char member[3][50]){
    int i;
    for(i=0;i<sizeof(teams);i++)
        if(teams[i].team_id == -1){
            teams[i].team_id = i;
            strcpy(teams[i].team_name, team_name);
            strcpy(teams[i].project_name, project_name);
            strcpy(teams[i].manager, manager);
            strcpy(teams[i].member[0], member[0]);
            strcpy(teams[i].member[1], member[1]);
            strcpy(teams[i].member[2], member[2]);
            // print_team_name(i);
            printf("Project Team %s is created.\n", team_name);
            break;
        }
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