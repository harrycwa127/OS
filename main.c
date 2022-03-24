#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct Team{
    char *team_name;                 // the name of the teams
    // struct Project projects[];  // the list of project in the teams
    char *project_name;     // name of the project
    char *manager;  // only 1 manage
    char *member[3];    // three member
    time_t dateTime;
    float duration;
};

struct Team *teams[];

int main(int argc, char *argv[]){
    printf("hi");
}

// void create_project(char *project_name){
//     teams.projects.name = project_name;
// }
