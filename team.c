#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct Team{
    char *team_name;                 // the name of the teams
    // struct Project projects[];   // the list of project in the teams
    char *project_name;             // name of the project
    char *manager;                  // only 1 manage
    char *member[3];                // three member
    time_t dateTime;
    float duration;
};

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

struct Team *teams[1000];

void create_team(char *team_name, char *project_name, char *manager, char *member[3]){
    struct Team temp = { .team_name=team_name, .project_name=project_name, .manager=manager, .member=member };  // decalre new Team for append

    // findout the last element for append
    int i = 0;
    while(teams[i] != NULL){
        i++;
    }

    //append
    teams[i] = &temp;
}