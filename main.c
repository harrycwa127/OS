#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Team{
    char *team_name;                 // the name of the teams
    // struct Project projects[];  // the list of project in the teams
    char *project_name;     // name of the project
    char *manager;  // only 1 manage
    char *member[3];    // three member
};

struct Team *teams[1000];

int main(int argc, char *argv[]){
    printf("hi");
}

void create_team(char *team_name, char *project_name, char *manager, char *member[3]){
    struct Team temp = { .team_name=team_name, .project_name=project_name, .manager=manager, .member=member };

    int i = 0;
    while(teams[i] != NULL){
        i++;
    }

    teams[i] = &temp;
}
