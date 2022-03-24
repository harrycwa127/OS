#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct Team{
    char *team_name;                 // the name of the teams
    // struct Project projects[];   // the list of project in the teams
    char *project_name;             // name of the project
    char *manager;                  // only 1 manage
    char member [3][50];                // three member
    time_t dateTime;
    float duration;
};

struct Team *teams[1000];

void create_team(char *team_name, char *project_name, char *manager, char member[3][50]){
    struct Team temp = { .team_name=team_name, .project_name=project_name, .manager=manager, .member=*member };  // decalre new Team for append

    // findout the last element for append
    int i = 0;
    while(teams[i] != NULL){
        i++;
    }

    //append
    teams[i] = &temp;
}
