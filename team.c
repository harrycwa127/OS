#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define team_max 1000

struct Team{
    int team_id;            // default -1
    char team_name[100];     // team name
    char project_name[100];  // project name
    char member[4][50];     // 0 index will be the Manager
    int numOfMember;        // for the member array
    int calendar[18][9];    // for check booking time overlap
} Team;

struct Team teams[team_max];
int team_size = 0;

void Team_Init(){
    int i, j;
    for(i=0;i<team_max;i++){
        teams[i].team_id = -1;              // default value
        strcpy(teams[i].team_name, "");     // empty name
        strcpy(teams[i].project_name, "");  // empty name
        strcpy(teams[i].member[0], "");     // empty name
        strcpy(teams[i].member[1], "");     // empty name
        strcpy(teams[i].member[2], "");     // empty name
        strcpy(teams[i].member[3], "");     // empty name
        teams[i].numOfMember = -1;
        for(i=0;i<18;i++) for(j=0;j<9;j++) teams[i].calendar[i][j]=-1;
    }
}

void print_team(int i){  // debug use
    int j;
    printf("================debug use===============\n");
    printf("team id \t%d\n", teams[i].team_id);
    printf("team_name \t%s\n", teams[i].team_name);
    printf("project_name \t%s\n", teams[i].project_name);
    printf("numOfMember \t%d\n", teams[i].numOfMember);
    printf("manager \t%s\n", teams[i].member[0]);
    for(j=1;j<teams[i].numOfMember;j++)
        printf("member \t\t%s\n", teams[i].member[j]);
    printf("========================================\n");
}

void print_calendar(int tid){
    int i, j;
    printf("\\\t");
    for(j=0;j<9;j++){
        int num = j+9;
        printf("%d-%d\t", num, num+1);
    } printf("\n");
    for(i=0;i<18;i++){
        int num = i + 25;
        if (num > 30){
            num -= 30;
            if(num > 0) num++;
            if(num > 7) num++;
        }
        printf("%d\t", num);
        for(j=0;j<9;j++){
            printf("%d\t", teams[tid].calendar[i][j]);
        } printf("\n");
    }
}

void create_team(char team_detail[7][100]){
    int i, j, k, l, n = 0;
    for(i=0;i<team_size;i++){       // loop though all the teams to check duplicate team name and project name
        if(strcmp(team_detail[0], teams[i].team_name)==0 && strcmp(team_detail[1], teams[i].project_name)==0){
            printf("Error: same team name with same project name existed\n", team_detail[0], team_detail[1]);
            return;
        }
    }
    // replace the newline with end of string
    for(i=0;i<4;i++) for(j=0;j<100;j++){ if(team_detail[i+2][j] == '\n') team_detail[i+2][j] = '\0'; }
    for(i=0;i<4;i++)
        for(j=i;j<4;j++){
            if(i==j) continue;
            if(strcmp(team_detail[i+2], team_detail[j+2])==0){
                printf("Error: same name appear twice (%s)\n",team_detail[i+2]);
                return;
            }
        }
    while(1){   // if the team id is equal to -1, need to add one until the team id is -1
        if(teams[team_size].team_id == -1){
            for(i=2;i<6;i++){       // member name will be inside the team_detail[2-5], while index 2 is the manager.
                if(strcmp(team_detail[i], "")==0){
                    break;
                }else{
                    for(k=0;k<team_size;k++)
                        if(strcmp(team_detail[2], teams[k].member[0])==0){ // check for the user if he/she is other team's manager
                            printf("Error: %s already is the manager of %s\n",team_detail[2], teams[k].team_name);
                            return;
                        }
                    int counter = 0;
                    for(k=0;k<team_size;k++) // loop for every team
                        for(l=0;l<teams[k].numOfMember;l++) // for each team loop for every member
                            if(strcmp(team_detail[i], teams[k].member[l])==0){ // check for the user participate in other team
                                printf("Testing: %s in %s\n", teams[k].member[l], teams[k].team_name);
                                counter++;
                                if(counter==3){
                                    printf("Error: %s already participate in three projects\n",team_detail[i]);
                                    return;
                                }
                            }
                    n++;
                }
            }
            if(n<2){
                printf("Error: No manager in the team\n");
                return;
            }
            teams[team_size].team_id = team_size;
            strcpy(teams[team_size].team_name, team_detail[0]);
            strcpy(teams[team_size].project_name, team_detail[1]);
            teams[team_size].numOfMember = n;
            for(i=0;i<n;i++)
            strcpy(teams[team_size].member[i], team_detail[i+2]);
            // print_team(team_size);
            printf("Project Team %s is created.\n", teams[team_size].team_name);
            team_size += 1;
            break;
        }else{
            team_size += 1;
        }
    }
}

void project_booking(char team_name[100], char date[11], char time[6], int duration){
    char stryear[4];
    char strmonth[2];
    char strday[2];
    char strhour[2];
    char strmin[2];
    strncpy(stryear, &date[0], 4);      // substring
    strncpy(strmonth, &date[5], 2);     // substring
    strncpy(strday, &date[8], 2);       // substring
    strncpy(strhour, &time[0], 2);      // substring
    strncpy(strmin, &time[3], 2);       // substring
    int year = atoi(stryear);           // string to int
    int month = atoi(strmonth);         // string to int
    int day = atoi(strday);             // string to int
    int hour = atoi(strhour);           // string to int
    int min = atoi(strmin);             // string to int

    // error checking
    int error = 0;
    if(year != 2022) error = 1;
    if(month == 4){
        if(25 > day || day > 30) error = 1;
    }else if (month == 5){
        if(1 > day || day > 14) error = 1;
    }else{
        error = 1;
    }
    if (error){
        printf("Rejected due to assumptions 3\n");
        return;
    }
    if(month == 5 && day == 1) error = 1;
    if(month == 5 && day == 8) error = 1;
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
    int day_index;
    if (month == 4) day_index = day -25;
    if (month == 5){
        day_index = day + 5;
        if(day > 0) day_index --;
        if(day > 6) day_index --;
    }
    int time_index = hour - 9;
    int i;
    int tid = -1;
    for(i=0; i<team_size;i++){
        if(strcmp(teams[i].team_name, team_name)==0){
            tid = i;
        }
    }
    if (tid == -1){
        printf("team name not found!\n");
        return;
    }
    for(i=0; i<duration; i++){
        if(teams[tid].calendar[day_index][time_index + i] != -1)
            error = 1;
            break;
    }
    if (error){
        printf("Rejected due to time overlap!\n");
        return;
    }
    int total_hour = 0;
    for(i=0; i < 9; i++){
        if(teams[tid].calendar[day_index][i] == tid)
            total_hour ++;
    }
    printf("Total hours: %d\n", total_hour);
    if (total_hour + duration > 5){
        printf("Rejected due to time limit exceeded!\n");
        return;
    }
    for(i=0; i<duration; i++){
        teams[tid].calendar[day_index][time_index + i] = tid;
    }
    printf("Accepted!!\n");
    // print_calendar();
}