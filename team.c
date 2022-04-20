#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define team_max 1000
#define reject_max 1000

struct Team
{
    int team_id;            // default -1
    char team_name[50];    // team name
    char project_name[50]; // project name
    char member[4][50];     // 0 index will be the Manager
    int numOfMember;        // for the member array
    int calendar[18][9];    // for check booking time overlap
    int accepted_request;
    int total_request;
} Team;

struct Team teams[team_max];
int team_size = 0;
char calendar[18][9][120];          // used for part 3 to store the info of booking
char reject[1000][150];             // used for part 3 to store the info of rejected booking
int reject_index = 0;               // index of rejected booking in part 3
char team_member_name[100][50];     //member record
int number_of_member = 0;           //number of member
int total_request = 0, total_received = 0, total_accepted = 0; // for cal performance


void Team_Init(){
    int i, j, k;
    for (i = 0; i < team_max; i++)
    {
        teams[i].team_id = -1;             // default value
        strcpy(teams[i].team_name, "");    // empty name
        strcpy(teams[i].project_name, ""); // empty name
        strcpy(teams[i].member[0], "");    // empty name
        strcpy(teams[i].member[1], "");    // empty name
        strcpy(teams[i].member[2], "");    // empty name
        strcpy(teams[i].member[3], "");    // empty name
        teams[i].numOfMember = -1;
        teams[i].accepted_request = 0;
        teams[i].total_request = 0;
        // init calendar
        for (j = 0; j < 18; j++)
        {
            for (k = 0; k < 9; k++)
            {
                teams[i].calendar[j][k] = -1;
            }
        }
    }
}


int find_tid(char *team_name){
    int tid = -1, i;
    for (i = 0; i < team_size; i++){
        if (!strcmp(teams[i].team_name, team_name)){
            tid = i;
            break;
        }
    }
    return tid;
}

void print_team(int i){ // debug use
    int j;
    printf("================debug use===============\n");
    printf("team id \t%d\n", teams[i].team_id);
    printf("team_name \t%s\n", teams[i].team_name);
    printf("project_name \t%s\n", teams[i].project_name);
    printf("numOfMember \t%d\n", teams[i].numOfMember);
    printf("manager \t%s\n", teams[i].member[0]);
    for (j = 1; j < teams[i].numOfMember; j++)
        printf("member \t\t%s\n", teams[i].member[j]);
    printf("========================================\n");
}

void create_team(char team_detail[7][100])
{
    int i, j, k, l, n = 0;
    if(strlen(team_detail[0]) == 0){         //if no input
        printf("Error: No input\n");
        return;
    }
    for (i = 0; i < team_size; i++){        // loop though all the teams to check duplicate team name and project name
        if (strcmp(team_detail[0], teams[i].team_name) == 0){
            printf("Error: same team name existed\n", team_detail[0], team_detail[1]);
            return;
        }
        if(strcmp(team_detail[1], teams[i].project_name) == 0){
            printf("Error: same project name existed\n", team_detail[0], team_detail[1]);
            return;
        }
    }
    // replace the newline with end of string
    for (i = 0; i < 4; i++)
        for (j = 0; j < 100; j++){
            if (team_detail[i + 2][j] == '\n')
                team_detail[i + 2][j] = '\0';
        }
    for (i = 0; i < 4; i++)
        for (j = i; j < 4; j++){
            if (i == j)
                continue;
            if (strcmp(team_detail[i + 2], team_detail[j + 2]) == 0 && strlen(team_detail[i + 2]) != 0 && strlen(team_detail[j + 2]) != 0){
                printf("Error: same name appear twice (%s)\n", team_detail[i + 2]);
                return;
            }
        }
    while (1){ // if the team id is equal to -1, need to add one until the team id is -1
        if (teams[team_size].team_id == -1){
            for (i = 2; i < 6; i++){ // member name will be inside the team_detail[2-5], while index 2 is the manager.
                if (strcmp(team_detail[i], "") == 0){
                    break;
                }
                else{
                    for (k = 0; k < team_size; k++)
                        if (strcmp(team_detail[2], teams[k].member[0]) == 0)
                        { // check for the user if he/she is other team's manager
                            printf("Error: %s already is the manager of %s\n", team_detail[2], teams[k].team_name);
                            return;
                        }
                    int counter = 0;
                    for (k = 0; k < team_size; k++)                // loop for every team
                        for (l = 0; l < teams[k].numOfMember; l++) // for each team loop for every member
                            if (strcmp(team_detail[i], teams[k].member[l]) == 0)
                            { // check for the user participate in other team
                                counter++;
                                if (counter == 3)
                                {
                                    printf("Error: %s already participate in three projects\n", team_detail[i]);
                                    return;
                                }
                            }
                    n++;
                }
            }
            if (n == 0)
            {
                printf("Error: No manager in the team\n");
                return;
            }
            teams[team_size].team_id = team_size;
            strcpy(teams[team_size].team_name, team_detail[0]);
            strcpy(teams[team_size].project_name, team_detail[1]);
            teams[team_size].numOfMember = n;
            for (i = 0; i < n; i++)
                strcpy(teams[team_size].member[i], team_detail[i + 2]);
            printf("Project Team %s is created.\n", teams[team_size].team_name);
            team_size += 1;
            break;
        }
        else
        {
            team_size += 1;
        }
    }
}

void project_booking(char team_name[100], char date[11], char time[6], int duration){
    total_request++;   //counting the reveived request
    char stryear[4];
    char strmonth[2];
    char strday[2];
    char strhour[2];
    char strmin[2];
    strncpy(stryear, &date[0], 4);  // substring
    strncpy(strmonth, &date[5], 2); // substring
    strncpy(strday, &date[8], 2);   // substring
    strncpy(strhour, &time[0], 2);  // substring
    strncpy(strmin, &time[3], 2);   // substring
    int year = atoi(stryear);       // string to int
    int month = atoi(strmonth);     // string to int
    int day = atoi(strday);         // string to int
    int hour = atoi(strhour);       // string to int
    int min = atoi(strmin);         // string to int

    //char line[100];
    char temp[100];
    //printf("temp: %s\n", temp);
    memset(temp, 0, sizeof temp);
    strcat(temp,team_name);
    strcat(temp, " ");
    strcat(temp, date);
    strcat(temp, " ");
    strcat(temp, time);
    strcat(temp, " ");
    //char dur[8];
    char temp_dur[8];
    sprintf(temp_dur, "%d", duration);
    strcat(temp, temp_dur);
    printf("\nIn line: %s\n", temp);

    // error checking
    int error = 0;
    if (year != 2022)
        error = 1;
    if (month == 4)
    {
        if (25 > day || day > 30)
            error = 1;
    }
    else if (month == 5)
    {
        if (1 > day || day > 14)
            error = 1;
    }
    else
    {
        error = 1;
    }
    if (error)
    {
        printf("Rejected due to assumptions 3\n");
        return;
    }
    if (month == 5 && day == 1)
        error = 1;
    if (month == 5 && day == 8)
        error = 1;
    if (error)
    {
        printf("Rejected due to assumptions 4\n");
        return;
    }
    if (hour * 60 < 540 || hour * 60 + duration * 60 > 1080 || min != 0 || duration == 0)
    { // assumptions 5
        printf("Rejected due to assumptions 5\n");
        return;
    }
    if (duration > 5)
    {
        printf("Rejected due to time limit exceeded\n");
        return;
    }
    int day_index;
    if (month == 4)
        day_index = day - 25;
    if (month == 5)
    {
        day_index = day + 5;
        if (day > 0)
            day_index--;
        if (day > 6)
            day_index--;
    }
    int time_index = hour - 9;
    int i;
    int tid = -1;
    for (i = 0; i < team_size; i++)
    {
        if (strcmp(teams[i].team_name, team_name) == 0)
        {
            tid = i;
        }
    }
    if (tid == -1)
    {
        printf("team name not found!\n");
        return;
    }

    // check lunch time
    if (time_index < 4){
        if (time_index + duration > 4)
        {
            printf("The booking is include the lunch time!\n");
            return;
        }
    }

    for (i = 0; i < duration; i++)
    {
        if (teams[tid].calendar[day_index][time_index + i] != -1){
            error = 1;
            break;
        }
    }
    if (error)
    {
        printf("Rejected due to time overlap!\n");
        return;
    }
    int total_hour = 0;
    for (i = 0; i < 9; i++)
    {
        if (teams[tid].calendar[day_index][i] == tid)
            total_hour++;
    }
    if (total_hour + duration > 5)
    {
        printf("Rejected due to time limit exceeded!\n");
        return;
    }
    for (i = 0; i < duration; i++)
    {
        teams[tid].calendar[day_index][time_index + i] = tid;
    }
    printf("Accepted!!\n");
    total_received++;   //counting the reveived booking

    // write the valid book to the .dat
    char line[100];
    strcat(team_name, " ");
    strcat(team_name, date);
    strcat(team_name, " ");
    strcat(team_name, time);
    strcat(team_name, " ");
    char dur[8];
    sprintf(dur, "%d", duration);
    strcat(team_name, dur);
    strcpy(line,"");
    strcpy(line, team_name);

    FILE *booking;
    booking = fopen("booking.dat", "a+");
    fputs(line, booking);
    fputs("\n", booking);
    fclose(booking);
}

void print_calendar(char *algorithm){
    char temp[200], temp2[200], line_temp[200], file_name[100];
    char info[5][50], time_temp[5], member_name[50];
    int end_hour, team_count, member_count;
    strcpy(file_name, "G28_Schedule_");
    strcat(file_name, algorithm);
    strcat(file_name, ".txt");
    FILE* file = fopen(file_name, "w+");
    fclose(file);
    file = fopen(file_name, "a+");

    // for check period
    int period[4] = {-1, -1, -1, -1}, i, j, k;
    for(i = 0; i < 18; i++){
        for(j = 0; j < 9; j++){
            if(calendar[i][j][0] != '\0'){
                // check for start of period
                if(period[0] == -1 && period[1] == -1){
                    period[0] = i;
                    period[1] = j;
                }

                // check for end of period
                period[2] = i;
                period[3] = j;
            }
        }
    }
    strcpy(temp, calendar[period[0]][period[1]]);
    strcpy(temp2, calendar[period[2]][period[3]]);

    fputs("*** Project Meeting ***\n\n", file);
    sprintf(line_temp, "Algorithm used: %s\n", algorithm);
    fputs(line_temp, file);

    sprintf(line_temp, "Period: %s to %s\n\n", strtok(temp, "|"), strtok(temp2, "|"));
    fputs(line_temp, file);

    // check calendar and print the booking info
    // int k, col_size[] = {13, 7, 7, 50, 50};
    temp[0] = '\0';     //clear temp

    for(team_count = 0; team_count < team_size; team_count++) {
        if(teams[team_count].team_id == -1)  break;

        sprintf(line_temp, "%13s %7s %7s %50s %50s\n", "Date", "Start", "End", "Team", "Project");
        fputs(line_temp, file);
        fputs("==========================================================================================================================================================\n", file);

        for(i = 0; i < period[2]+1; i++){
            for(j = 0; j < 9; j++){
                if(calendar[i][j][0] != '\0'){
                    if(strcmp(temp, calendar[i][j])){   //check temp and the booking info is not same
                        strcpy(temp, calendar[i][j]);
                        strcpy(info[0], strtok(temp, "|"));
                        for(k = 1; k < 5; k++){
                            strcpy(info[k], strtok(NULL, "|"));
                        }

                        if(!strcmp(info[3], teams[team_count].team_name)){
                            //convert duration to end datetime
                            strncpy(time_temp, &info[1][0], 2);       // substring
                            end_hour = atoi(time_temp) + atoi(info[2]);           // start time + duration
                            sprintf(info[2], "%d:00", end_hour);

                            sprintf(line_temp, "%13s %7s %7s %50s %50s\n", info[0], info[1], info[2], info[3], info[4]);
                            fputs(line_temp, file);
                        }

                        strcpy(temp, calendar[i][j]);
                    }
                }
            }
        }
        fputs("==========================================================================================================================================================\n", file);
        sprintf(line_temp, "Team: %s\n\n", teams[team_count].team_name);
        fputs(line_temp, file);  //team name
    }


    //print Staff

    char s[100];
    char temp_member[100];
    int l,m;
    int added = 0; // 0 = false, 1 = true


    for (i = 0; i < team_size; i++){               // loop for every team
        for (j = 0; j < teams[i].numOfMember; j++){ // for each team loop for every member
            strcpy(temp_member , teams[i].member[j]);       //assign the name of member
            added = 0;
            if(number_of_member != 0){
                for (k = 0; k < number_of_member; k++){
                    if (strcmp(temp_member, team_member_name[k]) == 0){ // check for the user in the member list
                        added = 1;
                        break;
                    }
                }
            }
            if(added != 1){
                strcpy(team_member_name[number_of_member] , temp_member);
                number_of_member++;
            }
        }
    }
    //sort names in Alphabetical order
    for(i=0;i<number_of_member;i++){
        for(j=i+1;j<number_of_member;j++){
            if(strcmp(team_member_name[i],team_member_name[j])>0){
                strcpy(s,team_member_name[i]);
                strcpy(team_member_name[i],team_member_name[j]);
                strcpy(team_member_name[j],s);
            }
        }
    }

    for (i = 0; i < number_of_member; i++){             //loop each member
        sprintf(line_temp, "%13s %7s %7s %50s %50s\n", "Date", "Start", "End", "Team", "Project");
        fputs(line_temp, file);
        fputs("==========================================================================================================================================================\n", file);
        for (j = 0; j < team_size; j++){               // loop for every team
            for (k = 0; k < teams[j].numOfMember; k++){ // for each team loop for every member
                if (strcmp(team_member_name[i], teams[j].member[k]) == 0){ // check for the member in the team
                    //print team time list
                        for(team_count = 0; team_count < team_size; team_count++) {
                            if(teams[team_count].team_id == -1)  break;
                            if(strcmp(teams[j].team_name, teams[team_count].team_name) == 0){
                                for(l = 0; l < period[2]+1; l++){
                                    for(m = 0; m < 9; m++){
                                        if(calendar[l][m][0] != '\0'){
                                            if(strcmp(temp, calendar[l][m])){   //check temp and the booking info is not same
                                                strcpy(temp, calendar[l][m]);
                                                strcpy(info[0], strtok(temp, "|"));
                                                for(k = 1; k < 5; k++){
                                                    strcpy(info[k], strtok(NULL, "|"));
                                                }
                                                if(!strcmp(info[3], teams[team_count].team_name)){
                                                    //convert duration to end datetime
                                                    strncpy(time_temp, &info[1][0], 2);       // substring
                                                    end_hour = atoi(time_temp) + atoi(info[2]);           // start time + duration
                                                    sprintf(info[2], "%d:00", end_hour);

                                                    sprintf(line_temp, "%13s %7s %7s %50s %50s\n", info[0], info[1], info[2], info[3], info[4]);
                                                    fputs(line_temp, file);
                                                }
                                                strcpy(temp, calendar[l][m]);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                }
            }
        }
        fputs("==========================================================================================================================================================\n", file);
        sprintf(line_temp,"Staff: %s\n\n",team_member_name[i]);
        fputs(line_temp, file);
    }

    //print rejected booking info
    fputs("*** Meeting Request ***\n\n", file);
    sprintf(line_temp, "There are %d requested rejected for the required period.\n\n", reject_index+1);
    fputs(line_temp, file);
    fputs("==========================================================================================================================================================\n", file);

    for(i = 0; i < reject_index; i++){
        sprintf(line_temp, "%d. %s\n", i+1, reject[i]);
        fputs(line_temp, file);
    }
    fputs("==========================================================================================================================================================\n\n", file);

    sprintf(line_temp, "%70s\n\n", "- End -");
    fputs(line_temp, file);

    // performance
    fputs("Performance:\n\n", file);
    sprintf(line_temp, "Total Number of Requests Received: %d (%2.1f%%)\n", total_received, ((float)total_received/(float)total_request)*100);
    fputs(line_temp, file);
    sprintf(line_temp, "Total Number of Requests Accepted: %d (%2.1f%%)\n", total_accepted, ((float)total_accepted/(float)total_received)*100);
    fputs(line_temp, file);
    sprintf(line_temp, "Total Number of Requests Rejected: %d (%2.1f%%)\n\n", reject_index, ((float)reject_index/(float)total_received)*100);
    fputs(line_temp, file);

    fputs("Utilization of Time Slot:\n\n", file);
    sprintf(line_temp, "\tAccepted request\t\t- %2.1f%%\n\n", ((float)total_accepted/(float)total_request)*100);
    fputs(line_temp, file);

    //team
    fputs("\tTeam:\n", file);
    for(i = 0; i < team_size; i++){
        sprintf(line_temp, "\t%50s - %2.1f%%\n", teams[i].team_name, ((float)teams[i].accepted_request/(float)teams[i].total_request)*100);
        fputs(line_temp, file);
    }

    //staff
    int member_total = 0, member_accepted = 0;
    fputs("\tStaff:\n", file);
    for(i = 0; i < number_of_member; i++){
        //reset request counter
        member_total = 0;
        member_accepted = 0;

        // find all request
        for(j = 0; j < team_size; j ++){
            for(k = 0; k < teams[j].numOfMember; k++){
                if(!strcmp(team_member_name[i], teams[j].member[k])){
                    member_total += teams[j].total_request;
                    member_accepted += teams[j].accepted_request;
                }
            }
        }

        // print results
        sprintf(line_temp, "\t%50s - %2.1f%%\n", team_member_name[i], ((float)member_accepted/(float)member_total)*100);
        fputs(line_temp, file);
    }



    fclose(file);
    printf("Printed. Export file name: %s\n", file_name);
}

void schedule_FCFS(){
    static int max_week = 3;  // max week
    static int max_buf = 200; // max length of buffer

    int booking_count;                  // for counting the numbers of booking
    int pid, week, i, j;                // comment var for child to use, and be counter
    int fd[max_week * 2][2];                       // for pipe, each week 2 pipes
    char storage[4][50], buffer[200];   // buffer for store data from file
    char time_buf[3];                   // buffer for store the substring in datetime
    int day;                            // store int of booking
    int tid;                            // for get the tid

    // reset counter
    total_accepted = 0;
    for(i = 0; i < team_size; i++) {
        teams[i].accepted_request = 0;
        teams[i].total_request = 0;
    }

    // init pipe, i*2 for parent to child, 1*2+1 for child to parent
    for (i = 0; i < max_week; i++){
        if (pipe(fd[i * 2]) < 0 || pipe(fd[i * 2 + 1]) < 0){
            printf("Pipe creation error\n");
            exit(1);
        }
    }

    // init calendar
    for (i = 0; i < 18; i++){
        for (j = 0; j < 9; j++){
            calendar[i][j][0] = '\0';
        }
    }

    //init reject
    for(i = 0; i < reject_index; i++){
        reject[i][0] = '\0';
    }
    reject_index = 0;

    //check booking.dat exit
    if( access("booking.dat", F_OK ) != 0 ) {
        printf("There are not exist booking record!");
    }

    pid = fork();
    if (pid < 0){
        printf("Fork failed\n");
        exit(1);
    }else if (pid == 0){             // child
        int hour; // store the int of hour
        int day_offset[] = {-25, 4, 3};
        char pro_name[50];  //store the project name of team

        for (week = 0; week < max_week; week++){ // child for 3 week sechulding
            pid = fork();
            if (pid < 0){
                printf("Fork failed\n");
                exit(1);
            }
            else if (pid == 0){ // child

                // close unused pipe
                close(fd[week * 2][1]);     // close parent to child input
                close(fd[week * 2 + 1][0]); // close child to parent output
                for (i = 0; i < max_week; i++){
                    if (i != week){
                        close(fd[i * 2][0]);
                        close(fd[i * 2][1]);
                        close(fd[i * 2 + 1][0]);
                        close(fd[i * 2 + 1][1]);
                    }
                }

                while(1){
                    buffer[0] = '\0';
                    while(strcmp(buffer, "") == 0) read(fd[week*2][0], buffer, max_buf);  //wait for read and read booking

                    if(!strcmp(buffer, "no-booking")){
                        // return the reuslt to parent
                        for (i = 0; i < 18; i++){
                            for (j = 0; j < 9; j++){
                                if (calendar[i][j][0] != '\0'){
                                    sprintf(buffer, "%d %d %s", i, j, calendar[i][j]);
                                    write(fd[week * 2 + 1][1], buffer, max_buf);
                                }
                            }
                        }

                        write(fd[week*2+1][1], "end", max_buf);

                        close(fd[week*2][0]); // close parent to child output
                        close(fd[week*2+1][1]); // close child to parent intput
                        exit(0);
                    }

                    strcpy(storage[0], strtok(buffer, " "));

                    for (i = 1; i < 4; i++){
                        strcpy(storage[i], strtok(NULL, " "));
                    }

                    //get the  and hour for compare
                    strncpy(time_buf, &storage[1][8], 2);       // substring
                    day = atoi(time_buf) + day_offset[week];
                    strncpy(time_buf, &storage[2][0], 2);       // substring
                    hour = atoi(time_buf)-9;           // string to int

                    strcpy(pro_name, teams[find_tid(storage[0])].project_name);

                    sprintf(buffer, "%s|%s|%s|%s|%s", storage[1], storage[2], storage[3], storage[0], pro_name);        //store booking info to buffer for copy
                    //set clander timeslot to team_id
                    for(i = 0; i < atoi(storage[3]); i++){
                        // check for time slot whether used
                        if(calendar[day][hour+i][0] == '\0'){
                            strcpy(calendar[day][hour+i], buffer);
                        }else{
                            for(j = 0; j < i; j++){
                                calendar[day][hour+j][0] = '\0';
                            }

                            sprintf(buffer, "reject %s %s %s %s", storage[0], storage[1], storage[2], storage[3]);
                            write(fd[week * 2 + 1][1], buffer, max_buf);
                            break;
                        }
                    }
                }
            }
        }

        while (wait(NULL) > 0); // wait for all child finish
        exit(0);
    }else{                                           // parent to sorting all booking and assign to the child
        FILE *file = fopen("booking.dat", "r+");      // to open the booking file
        // variable for convert message from child to int
        char temp[200];                         // temp is copy of for get substring
        int date, time;

        for (i = 0; i < max_week; i++){
            close(fd[i * 2][0]);     // close parent to child output
            close(fd[i * 2 + 1][1]); // close child to parent intput
        }
        // read file line by line
        while (fgets(buffer, max_buf, file)){   // have bug, dont know why
            strcpy(temp, buffer);
            strcpy(storage[0], strtok(temp, " "));
            for (i = 1; i < 4; i++)
            {
                strcpy(storage[i], strtok(NULL, " "));
            }

            // get the day for compare
            strncpy(time_buf, &storage[1][8], 2); // substring
            day = atoi(time_buf);

            // check for week
            if (day >= 25 && day <= 30)
            {
                write(fd[0][1], buffer, max_buf); // write the booking to week 0
            }
            else if (day >= 2 && day <= 7)
            {
                write(fd[2][1], buffer, max_buf); // write the booking to week 1
            }
            else if (day >= 9 && day <= 14)
            {
                write(fd[4][1], buffer, max_buf); // write the booking to week 2
            }
            else
            {
                printf("Parent: Error, 【%s】 date not in range", buffer);
            }
        }

        for(i = 0 ; i < max_week ; i++){
            write(fd[i*2][1], "no-booking", max_buf);                             // write the no-booking to all week
        }

        for(i = 0; i < max_week; i++){
            while(1){
                buffer[0] = '\0';   //clear buffer
                while(!strcmp(buffer, "")) read(fd[i*2+1][0], buffer, max_buf);

                if(!strcmp(buffer, "end")) break;  //check end of booking

                // find tid
                strcpy(temp, buffer);
                strtok(temp, "|");
                for(j = 1; j < 3; j ++) strtok(NULL, "|");
                strcpy(temp, strtok(NULL, "|"));
                tid = find_tid(temp);

                if(tid != -1){
                    if(!strncmp(buffer, "reject", 6)){
                        strtok(buffer, " ");

                        strcpy(reject[reject_index], strtok(NULL, "|"));
                        reject_index++;
                        teams[tid].total_request++;
                    }else{          // success booking
                        // get date
                        strcpy(temp, strtok(buffer, " "));
                        date = atoi(temp);

                        // get time
                        strcpy(temp, strtok(NULL, " "));
                        time = atoi(temp);

                        strcpy(calendar[date][time], strtok(NULL, " "));
                        total_accepted++;   // count accepted booking

                        teams[tid].accepted_request++;
                        teams[tid].total_request++;
                    }
                }else{ // tid error
                    printf("Error, team name 【%s】 not found!\n", temp);
                }
            }
        }
        wait(NULL);
        print_calendar("FCFS");
        return;
    }
}

void schedule_Priority()
{
    FILE *sorted;
    FILE *booking;

    char bookingArray[162][100];
    char buffer[100];
    int bookingNum = 0;

    booking = fopen("booking.dat", "r");
    while (fgets(buffer, 100, booking) != NULL)
    {
        strcpy(bookingArray[bookingNum], buffer);
        bookingNum++;
    }
    fclose(booking);

    // Start sorting
    char date1[10], date2[10];
    char time1[4], time2[4];
    char name1[50], name2[50];
    char duration1, duration2;

    int i, j;
    char temp[100], temp2[100];
    for (i = 0; i < bookingNum; i++)
    {
        for (j = 0; j < bookingNum - 1 - i; j++)
        {
            bool needSort = false;

            // j
            duration1 = bookingArray[j][strlen(bookingArray[j]) - 1];

            strcpy(temp, bookingArray[j]);

            strcpy(temp, strtok(temp, " "));
            strcpy(name1, temp);

            strcpy(temp, strtok(NULL, " "));
            strcpy(date1, temp);

            strcpy(temp, strtok(NULL, " "));
            strcpy(time1, temp);

            // j + 1
            duration2 = bookingArray[j + 1][strlen(bookingArray[j + 1]) - 1];

            strcpy(temp2, bookingArray[j + 1]);

            strcpy(temp2, strtok(temp2, " "));
            strcpy(name2, temp2);

            strcpy(temp2, strtok(NULL, " "));
            strcpy(date2, temp2);

            strcpy(temp2, strtok(NULL, " "));
            strcpy(time2, temp2);

            if (strcmp(date1, date2) > 0) // return >0 means date2 is earlier than date1
            {
                needSort = true;
            }
            else if (strcmp(date1, date2) == 0 && strcmp(time1, time2) == 0) // same date and same starting time -> compare team name
            {
                if (strcmp(name1, name2) > 0) // greater means name2 has a smaller letter
                {
                    needSort = true;
                }
            }

            if (needSort == true)
            {
                char sortingTemp[100];
                strcpy(sortingTemp, bookingArray[j]);
                strcpy(bookingArray[j], bookingArray[j + 1]);
                strcpy(bookingArray[j + 1], sortingTemp);
            }
        }
    }

    // Put the sorting result in the .dat
    sorted = fopen("sorted.dat", "a+");
    for (i = 0; i < bookingNum; i++)
    {
        fputs(bookingArray[i], sorted);
    }
    fclose(sorted);

    // Start scheduling
    int toParent[3][2], toChild[3][2];

    total_accepted = 0;
    for(i = 0; i < team_size; i++) {
        teams[i].accepted_request = 0;
        teams[i].total_request = 0;
    }

    for(i = 0; i < reject_index; i++){
        reject[i][0] = '\0';
    }
    reject_index = 0;

    // Pipe initiation
    for (i=0;i<3;i++)
    {
        if (pipe(toParent[i]) < 0){
            printf("toParent Pipe error\n");
        }
        if (pipe(toChild[i]) < 0 ){
            printf("toChild pipe error\n");
        }
    }

    // child calendar initiation
    // calendar[18][9][120]
    for (i = 0; i < 18; i++){
        for (j = 0; j < 9; j++){
            calendar[i][j][0] = '\0';
        }
    }

    int pid;
    pid = fork();
    if (pid<0)
    {
        printf("Fork error\n");
    }
    else if (pid == 0)
    {
        for (i=0;i<3;i++)
        {
            pid = fork();
            if (pid<0)
            {
                printf("Fork error: grandchild\n");
            }
            else if (pid == 0) // Child process: scheduling
            {
                // close not use pipe
                close(toParent[i][0]);
                close(toChild[i][1]);

                int n;

                buffer[0] = '\0';
                while ((n=read(toChild[i][0], buffer, 100)) > 0)
                {
                    if (strcmp(buffer, "receive job")==0)
                    {
                        break;
                    }
                    buffer[0] = '\0';
                }

                char receivedJobs[1000][100];
                int jobNum = 0;

                buffer[0] = '\0';
                // Start receive jobs
                while((n=read(toChild[i][0], buffer, 100)) > 0)
                {
                    if (strcmp(buffer, "no jobs to receive") ==0 )
                    {
                        break;
                    }
                    else
                    {
                        strcpy(receivedJobs[jobNum], buffer);
                        jobNum++;
                    }
                    buffer[0] = '\0';
                }

                // Start scheduling

                // exit when no job assigned
                if (jobNum == 0)
                {
                    buffer[0] = '\0';
                    strcpy(buffer, "empty");
                    write(toParent[i][1], buffer, 100);
                }

                // Get the team name, date, time, duration
                date1[0] = '\0';
                time1[0] = '\0';
                name1[0] = '\0';
                duration1 = ' ';
                temp[0] = '\0';
                char hour[2], actualDate[2];
                int day;

                char rejectedList[54][100];
                int rejectedSize = 0;
                for (j = 0; j<jobNum;j++)
                {
                    strcpy(temp, receivedJobs[j]);
                    // Team_A 2022-04-25 09:00 2
                    strcpy(temp, strtok(temp, " ")); // get team name
                    strcpy(name1, temp); // Team_A

                    strcpy(temp, strtok(NULL, " ")); // get date
                    strcpy(date1, temp); // 2022-04-25
                    actualDate[0] = date1[8];
                    actualDate[1] = date1[9]; // actualDate = 25
                    day = atoi(actualDate);
                    // Convert to the correct date index according to the child's week
                    switch (i)
                    {
                        case 0:
                            day = day - 25;
                            break;
                        case 1:
                            day = day + 4 ;
                            break;
                        case 2:
                            day = day + 3;
                            break;
                    }

                    strcpy(temp, strtok(NULL, " ")); // get time
                    strcpy(time1, temp); // 09:00


                    hour[0] = time1[0];
                    hour[1] = time1[1]; // hour = 09

                    int startTimeslot = atoi(hour) - 9;

                    int l = strlen(receivedJobs[j]) - 2;

                    duration1 = receivedJobs[j][l];

                    int dur = duration1 - '0';

                    // strncpy(time1, time1, 5);

                    // put the job to the child calendar
                    // char childCalendar[6][9][100];
                    // Team_A 2022-04-25 09:00 2
                    // name1 = Team_A, calendar index = 0, startTimeslot = 0, dur = 2
                    int k;
                    bool used = false;
                    for (k = startTimeslot; k < startTimeslot + dur; k++)
                    {
                        if (calendar[day][k][0] != '\0')
                        {
                            used = true;
                        }
                    }

                    // find project name
                    char pro_name[50];
                    for (k = 0; k < team_size; k++){
                        if (!strcmp(teams[k].team_name, name1)){
                            strcpy(pro_name, teams[k].project_name);
                            break;
                        }
                    }

                    // date|start_time|duration|team_name|project_name
                    if (used == false)
                    {
                        for (k = startTimeslot; k < startTimeslot + dur; k++)
                        {
                            char cat[100];
                            sprintf(cat, "%s|%s|%c|%s|%s", date1, time1, duration1, name1, pro_name);

                            strcpy(calendar[day][k], cat);
                        }
                    }
                    if (used == true)
                    {
                        strcpy(rejectedList[rejectedSize], receivedJobs[j]);
                        rejectedSize++;
                    }
                } // end of jobs for loop

                // Tell parent result
                buffer[0] = '\0';
                if (jobNum != 0)
                {
                    strcpy(buffer, "receive results");
                    write(toParent[i][1], buffer, 100);
                }
                else if (jobNum == 0)
                {
                    strcpy(buffer, "empty");
                    write(toParent[i][1], buffer, 100);
                }


                int k;
                j = i*6; // to loop the child's processing week
                for (j=i*6; j < i+6; j++)
                {
                    for (k=0;k<9;k++)
                    {
                        if (calendar[j][k][0] != '\0') // calendar[j][k] 0
                        {
                            buffer[0] = '\0';
                            temp[0] = '\0';
                            strcpy(buffer, calendar[j][k]); // i j date|start_time|duration|team_name|project_name

                            sprintf(temp, "%d %d ", j, k);

                            strcat(temp, buffer);
                            write(toParent[i][1], temp, 100);
                        }
                    }
                }

                // tell parent completed reporting results
                buffer[0] = '\0';
                strcpy(buffer, "complete results");
                write(toParent[i][1], buffer, 100);

                // Add wait parent signal to send rejected list
                buffer[0] = '\0';
                while ((n=read(toChild[i][0], buffer, 100)) > 0)
                {
                    if (strcmp(buffer, "give rejected list") == 0)
                    {
                        break;
                    }
                }


                buffer[0] = '\0';
                strcpy(buffer, "receive rejectedList");
                write(toParent[i][1], buffer, 100);

                // tell parent rejected booking
                for (j = 0; j < rejectedSize; j++)
                {
                    buffer[0] = '\0';
                    strcpy(buffer, rejectedList[j]);
                    write(toParent[i][1], buffer, 100);
                }

                buffer[0] = '\0';
                strcpy(buffer, "complete rejectedList");
                write(toParent[i][1], buffer, 100);

                exit(0);
            } // Child process: scheduling end

        } // end of child for loop
        while (wait(NULL)>0); // no need parent processing for scheduling
        exit(0);
    }
    else // Parent processing: grand parent
    {
        for (i=0;i<3;i++)
        {
            close(toChild[i][0]);
        }


        // Read the sorted.dat to distribute jobs to grandchildren
        FILE *sortedBooking;
        sortedBooking = fopen("sorted.dat", "r");
        int day;

        buffer[0] = '\0';
        // Tell child to receive jobs
        for (i=0;i<3;i++)
        {
            strcpy(buffer, "receive job");
            write(toChild[i][1], buffer, 100);
            buffer[0] = '\0';
        }

        buffer[0] = '\0';
        while (fgets(buffer, 100, sortedBooking) != NULL)
        {
            // temp is copy of for get substring
            strcpy(temp, buffer);

            // Get the date from temp
            strcpy(temp, strtok(temp, " "));
            strcpy(temp, strtok(NULL, " "));
            strcpy(date1, temp);

            char d[2];
            d[0] = date1[8];
            d[1] = date1[9];


            day = atoi(d);
            // check for week
            if (day >= 25 && day <= 30)
            {
                write(toChild[0][1], buffer, 100); // write the booking to week 0
            }
            else if (day >= 2 && day <= 7)
            {
                write(toChild[1][1], buffer, 100); // write the booking to week 1
            }
            else if (day >= 9 && day <= 14)
            {
                write(toChild[2][1], buffer, 100); // write the booking to week 2
            }
            else
            {
                printf("Parent: Error, 【%s】 date not in range\n", buffer);
            }
            buffer[0] = '\0';
        }

        buffer[0] = '\0';

        // Tell grand children job distribution complete
        for (i=0;i<3;i++){
            strcpy(buffer, "no jobs to receive");
            write(toChild[i][1], buffer,100);
            buffer[0] = '\0';
        }

        // Receive results from children
        for (i=0; i<3;i++)
        {
            while (true)
            {
                buffer[0] = '\0';
                read(toParent[i][0], buffer, 100);
                if (strcmp(buffer, "empty")==0){
                    break;
                }
                if (strcmp(buffer, "receive results") ==0 )
                {
                    break;
                }
            }
        }

        // Start receiving success results
        char previousStart[5];
        strcpy(previousStart, "00:00");
        for (i=0; i<3; i++)
        {
            while (true)
            {
                buffer[0] = '\0';
                temp[0] = '\0';
                read(toParent[i][0], buffer, 100);
                if (strcmp(buffer, "complete results") == 0 || strcmp(buffer, "empty") == 0) // add empty
                {
                    break;
                }

                char copy[100];
                strcpy(copy, buffer);
                // get date
                strcpy(temp, strtok(buffer, " "));
                int d = atoi(temp);

                // get time
                strcpy(temp, strtok(NULL, " "));
                int t = atoi(temp);

                strcpy(calendar[d][t], strtok(NULL, " "));


                char currentStart[5];
                temp[0] = '\0';
                strcpy(temp, strtok(copy, " "));
                strcpy(temp, strtok(NULL, " "));
                strcpy(temp, strtok(NULL, "|"));
                strcpy(temp, strtok(NULL, "|"));

                strcpy(currentStart, temp); // currentStart = 09:00

                strcpy(temp, strtok(NULL, "|"));
                strcpy(temp, strtok(NULL, "|"));
                // d t date|start_time|duration|team_name|project_name

                // int total_request = 0, total_accepted = 0; // for cal performance GLOBAL
                // int accepted_request; // Class var
                // int total_request; // Class var

                int tid = find_tid(temp);
                if (strcmp(previousStart, currentStart) != 0)
                {
                    teams[tid].total_request++;
                    teams[tid].accepted_request++;
                    total_accepted++;
                }
                strcpy(previousStart, currentStart);
            }
        }

        // Start receiving rejected results
        // char reject[1000][120];
        // int reject_index = 0;

        for (i = 0; i < 3; i++)
        {
            // ask child to give rejected list
            buffer[0] = '\0';
            strcpy(buffer, "give rejected list");
            write(toChild[i][1], buffer, 100);
            while (true)
            {
                buffer[0] = '\0';
                read(toParent[i][0], buffer, 100);
                if (strcmp(buffer, "receive rejectedList")==0)
                {
                    while (true)
                    {
                        buffer[0] = '\0';
                        read(toParent[i][0], buffer, 100);
                        if (strcmp(buffer, "complete rejectedList")==0)
                        {
                            break;
                        }
                        strcpy(reject[reject_index], buffer);
                        reject_index++;

                        // add team.total request
                        temp[0] = '\0';
                        strcpy(temp, strtok(buffer, " "));
                        int tid = find_tid(temp);
                        teams[tid].total_request++;
                    }
                    break;
                }
            }
        }

        print_calendar("Priority_of_alphabet");
        wait(NULL);

    } // parent processing end
    // close the remaining pipe
    for(i=0;i<3;i++){
        close(toChild[i][1]);
        close(toParent[i][1]);
    }

    return;

}