#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define team_max 1000

struct Team{
    int team_id;
    char team_name[50];
    char project_name[50];
    char member[4][50];
    char date[11];
    char time[6];
    int duration;
    int numOfMember;
} Team;

struct Team teams[team_max];
int team_size = 0;

void Team_Init(){
    int i;
    for(i=0;i<team_max;i++){
        teams[i].team_id = -1;
        strcpy(teams[i].team_name, "");
        strcpy(teams[i].project_name, "");
        strcpy(teams[i].member[0], "");
        strcpy(teams[i].member[1], "");
        strcpy(teams[i].member[2], "");
        strcpy(teams[i].member[3], "");
        strcpy(teams[i].date, "");
        strcpy(teams[i].time, "");
        teams[i].duration = -1;
        teams[i].numOfMember = -1;
    }
}

void print_team(int i){
    int j;
    printf("=========================================\n");
    printf("team id %d\n", teams[i].team_id);
    printf("team_name %s\n", teams[i].team_name);
    printf("project_name %s\n", teams[i].project_name);
    printf("numOfMember %d\n", teams[i].numOfMember);
    printf("manager %s\n", teams[i].member[0]);
    for(j=1;j<teams[i].numOfMember;j++)
        printf("member %s\n", teams[i].member[j]);
    printf("date %s\n", teams[i].date);
    printf("time %s\n", teams[i].time);
    printf("duration %d\n", teams[i].duration);
    printf("=========================================\n");
}

void create_team(char team_detail[6][50]){
    int i, j, k, l, n = 0;
    for(i=0;i<team_size;i++){
        if(strcmp(team_detail[0], teams[i].team_name)==0 && strcmp(team_detail[1], teams[i].project_name)==0){
            printf("Error: same team name with same project name existed\n", team_detail[0], team_detail[1]);
            return;
        }
    }
    while(1){
        if(teams[team_size].team_id == -1){
            teams[team_size].team_id = team_size;
            strcpy(teams[team_size].team_name, team_detail[0]);
            strcpy(teams[team_size].project_name, team_detail[1]);
            for(i=2;i<6;i++){
                if(strcmp(team_detail[i], "")==0){
                    break;
                }else{
                    for(k=0;k<team_size;k++)
                        if(strcmp(team_detail[2], teams[k].member[0])==0){
                            printf("Error: %s already is the manager of %s\n",team_detail[2], teams[k].team_name);
                            return;
                        }
                    
                    int counter = 0;
                    for(k=0;k<team_size;k++)
                        for(l=0;l<teams[k].numOfMember;l++)
                            if(strcmp(team_detail[i], teams[k].member[l])==0){
                                counter++;
                                if(counter==3){
                                    printf("Error: %s already participate in three projects\n",team_detail[i]);
                                    return;
                                }
                            }
                    
                    n++;
                    for(j=0; j<50;j++){
                        if(team_detail[i][j] == '\n')
                            team_detail[i][j] = '\0';
                    }
                    strcpy(teams[team_size].member[i-2], team_detail[i]);
                }
            }
            teams[team_size].numOfMember = n;
            print_team(team_size);
            printf("Project Team %s is created.\n", teams[team_size].team_name);
            team_size += 1;
            break;
        }else{
            team_size += 1;
        }
    }
}

void project_booking(char team_name[50], char date[11], char time[6], int duration){
    char stryear[4];
    char strmonth[2];
    char strday[2];
    char strhour[2];
    char strmin[2];
    strncpy(stryear, &date[0], 4);
    strncpy(strmonth, &date[5], 2);
    strncpy(strday, &date[8], 2);
    strncpy(strhour, &time[0], 2);
    strncpy(strmin, &time[3], 2);
    int year;
    int month;
    int day;
    int hour;
    int min;
    year = atoi(stryear);
    month = atoi(strmonth);
    day = atoi(strday);
    hour = atoi(strhour);
    min = atoi(strmin);
    int error = 0;
    if(month == 4){
        if(day < 25 || day > 30) error = 1;
    }else if (month == 5){
        if(day < 1 || day > 14) error = 1;
    }else{
        error = 1;
    }
    if (error){
        printf("Rejected due to assumptions 3\n");
        return;
    }
    if(month == 4 && day == 30) error = 1;
    if(month == 5 && day == 7) error = 1;
    if(month == 5 && day == 14) error = 1;
    if (error){
        printf("Rejected due to assumptions 4\n");
        return;
    }
    if(hour*60 < 540 || hour*60+duration*60 > 1080 || min != 0 || duration == 0){ // assumptions 5
        printf("Rejected due to assumptions 5\n");
        return;
    }
    if(duration > 5){
        printf("Rejected due to time limit exceeded\n");
        return;
    }
    int tid, i, j, k;
    for(tid=0;tid<team_size+1;tid++) if(strcmp(teams[tid].team_name, team_name)==0) break;
    int accept = 1;
    for(i=0;i<team_size+1;i++){
        if(i == tid) continue;
        for(j=0;j<teams[i].numOfMember;j++) // check member time overlap
            for(k=0;k<teams[tid].numOfMember;k++)
                if(strcmp(teams[i].member[j], teams[tid].member[k])==0){
                    if(strcmp(teams[i].date, date)==0){ // check overlap
                        strncpy(strhour, &teams[i].time[0], 2);
                        int Ahour = atoi(strhour);
                        int StartA = Ahour * 60; 
                        int EndA = Ahour * 60 + teams[i].duration * 60;
                        int StartB = hour * 60;
                        int EndB = hour * 60 + duration * 60;
                        if (StartA < EndB && EndA > StartB){
                            printf("Rejected due to time overlap\n");
                            return;
                        }
                    }
                }
    }
    if(accept == 1){ // no overlap
        printf("Accepted!\n");
        strcpy(teams[tid].date, date);
        strcpy(teams[tid].time, time);
        teams[tid].duration = duration;
        print_team(tid);
    }
}