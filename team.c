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
    int i, j, k;
    for(i=0;i<team_max;i++){
        teams[i].team_id = -1;              // default value
        strcpy(teams[i].team_name, "");     // empty name
        strcpy(teams[i].project_name, "");  // empty name
        strcpy(teams[i].member[0], "");     // empty name
        strcpy(teams[i].member[1], "");     // empty name
        strcpy(teams[i].member[2], "");     // empty name
        strcpy(teams[i].member[3], "");     // empty name
        teams[i].numOfMember = -1;
        // init calendar
        for(j=0;j<18;j++){
            for(k=0;k<9;k++){
                teams[i].calendar[j][k]=-1; 
            }
        }  
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

    // write the valid book to the .txt
    char line[100];
    strcat(team_name, " ");
    strcat(team_name, date);
    strcat(team_name, " ");
    strcat(team_name, time);
    strcat(team_name, " ");
    char dur[8];
    sprintf(dur, "%d", duration);
    strcat(team_name, dur);
    strcpy(line, team_name);
    printf("line: %s\n",line);

    FILE *booking;
    booking = fopen("booking.txt", "a+");
    fputs(line, booking);
    fputs("\n",booking);
    fclose(booking);
}

void schedule_FIFC(){
    static int max_week = 3;    // max week
    static int max_buf = 200;   // max length of buffer

    int booking_count;      //for counting the numbers of booking
    int calendar[18][9];    // for check all teambooking time overlap
    int pid, week, i, j;    // comment var for child to use, and be counter
    int fd[6][2];           //for pipe, each week 2 pipes
    char storage[4][50], buffer[200];   //buffer for store data from file
    char time_buf[10];      // buffer for store the substring in datetime
    int day, tid;    //store int of booking 

    // init pipe, i*2 for parent to child, 1*2+1 for child to parent
    for(i = 0; i < max_week; i++){
        if (pipe(fd[i*2]) < 0 || pipe(fd[i*2+1]) < 0 ) {
            printf("Pipe creation error\n");
            exit(1);
        }
    }

    // init calendar
    for(i=0;i<18;i++){
        for(j=0;j<9;j++){
            calendar[i][j] = -1; 
        }
    }
    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) { // child
        int hour;   // store the int of hour
        int day_offset[] = {-25, 4, 3};

        for(week = 0; week < max_week; week++){    //child for 3 week sechulding
            pid = fork();
            if (pid < 0) {
                printf("Fork failed\n");
                exit(1);

            } else if (pid == 0) { // child

                //close unused pipe
                close(fd[week*2][1]); // close parent to child input
                close(fd[week*2+1][0]); // close child to parent output
                for(i=0; i < max_week; i++){
                    if(i != week){
                        close(fd[i*2][0]);
                        close(fd[i*2][1]);
                        close(fd[i*2+1][0]);
                        close(fd[i*2+1][1]);
                    }
                }

                while(1){

                    while(strcmp(buffer, "") == 0) read(fd[week*2][0], buffer, max_buf);  //wait for read and read booking

                    if(!strcmp(buffer, "no-booking")){
                        // return the reuslt to parent
                        for(i = 0; i < 18; i++){
                            for(j = 0; j < 9; j++){
                                if(calendar[i][j] != -1){
                                    sprintf(buffer, "%d %d %d", i, j, calendar[i][j]);
                                    write(fd[week*2+1][1], buffer, max_buf);
                                }
                            }
                        }

                        close(fd[week*2][0]); // close parent to child output
                        close(fd[week*2+1][1]); // close child to parent intput
                        exit(0);
                    }

                    strcpy(storage[0], strtok(buffer, " "));

                    for(i = 1 ; i < 4; i++){
                        strcpy(storage[i], strtok(NULL, " "));
                    }


                    //get the  and hour for compare
                    strncpy(time_buf, &storage[1][8], 2);       // substring
                    day = atoi(time_buf);
                    strncpy(time_buf, &storage[2][0], 2);       // substring
                    hour = atoi(time_buf);           // string to int

                    tid = -1;
                    for(i=0; i<team_size;i++){
                        if(strcmp(teams[i].team_name, storage[0])==0){
                            tid = i;
                        }
                    }
                    if (tid == -1){
                        printf("team name not found!\n");
                        return;
                    }


                    //set clander timeslot to team_id
                    for(i = 0; i < atoi(storage[3]); i++){
                        // check for time slot whether used
                        if(calendar[day + day_offset[week]][hour-9+i] == -1){
                            calendar[day + day_offset[week]][hour-9+i] = tid;
                        }
                    }
                }
            }
        }

        while(wait(NULL) > 0);  //wait for all child finish

    } else {         //parent to sorting all booking and assign to the child
        FILE *file = fopen("booking.dat", "r");     //to open the booking file
        //variable for convert message from child to int
        char temp[200];
        int date, time;

        for(i = 0; i < max_week; i++){
            close(fd[i*2][0]); // close parent to child output
            close(fd[i*2+1][1]); // close child to parent intput
        }

        //read file line by line
        while(fgets(buffer, max_buf, file)!=NULL){
            // temp is copy of for get substring
            strcpy(temp, buffer);
            strcpy(storage[0], strtok(temp, " "));
            for(i = 1 ; i < 4; i++){
                strcpy(storage[i], strtok(NULL, " "));
            }

            //get the day for compare
            strncpy(time_buf, &storage[1][8], 2);       // substring
            day = atoi(time_buf);

            //check for week
            if(day >= 25 && day <= 30){
                write(fd[0][1], buffer, max_buf);                                 // write the booking to week 0
            }else if(day >= 2 && day <= 7){
                write(fd[2][1], buffer, max_buf);                                 // write the booking to week 1
            }else if(day >= 9 && day <= 14){
                write(fd[4][1], buffer, max_buf);                                 // write the booking to week 2
            }else{
                printf("Parent: Error, 【%s】 date not in range", buffer);
            }
        }

        for(i = 0 ; i < max_week ; i++){
            write(fd[i*2][1], "no-booking", max_buf);                                 // write the no-booking to all week
        }

        wait(NULL);

        for(i = 0; i < max_week; i++){
            buffer[0] = '\0';   //clear buffer
            while(1){
                read(fd[i*2+1][0], buffer, max_buf);
                if(!strcmp(buffer, "")) break;  //check if pipe is null then break

                //get date
                strcpy(temp, strtok(buffer, " "));
                date = atoi(temp);

                //get time
                strcpy(temp, strtok(NULL, " "));
                time = atoi(temp);

                //get tid
                strcpy(temp, strtok(NULL, " "));
                tid = atoi(temp);

                calendar[date][time] = tid;
            }
        }
    }
}