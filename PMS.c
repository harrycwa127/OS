#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "team.c"

void PrintMenu(){
    printf("\n\t~~ WELCOME TO PolyStar ~~\n\n");
    printf("1.\tCreate Project Team\n\n");
    printf("2.\tProject Meeting Request\n");
    printf("\t2a.  Single input\n");
    printf("\t2b.  Batch input\n");
    printf("\t2c.  Meeting Attendance\n\n");
    printf("3.\tPrint Meeting Schedule\n");
    printf("\t3a.  FCFS (First Come First Served)\n");
    printf("\t3b.  XXXX (Another algorithm implemented)\n");
    printf("\t3c.  YYYY (Attendance Report)\n\n");
    printf("4.\tExit\n");
}

int main(){
    Team_Init();
    while(1){
        char choice[2];
        PrintMenu();
        printf("  Enter an option: ");
        scanf("%s", choice);
        if (strcmp(choice, "0") == 0){}
        else if (strcmp(choice, "1") == 0){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            while(1){
                char input[606];
                printf("Enter> ");
                fgets(input,305,stdin);
                if(input[0] == '0') break;
                char *ptr = strtok(input, " ");
                char storage[7][100];
                int i;
                //splite input
                for(i=0;i<7;i++){ strcpy(storage[i], "");}
                for(i=0;i<7;i++){
                    strcpy(storage[i], ptr);
                    ptr = strtok(NULL, " ");
                    if(ptr == NULL) break;
                }
                //if more than 6 parameter
                if(strcmp(storage[6], "") != 0){
                    printf("Error: Too many parameter\n");
                }else{
                    for(i=3;i<6;i++)
                        if(strcmp(storage[i], "\0") == 0){
                            storage[i-1][strlen(storage[i-1]) - 1] = '\0';
                            break;
                        }
                    create_team(storage);
                }
            }
        }else if (strcmp(choice, "2a") == 0){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            while(1){
                char input[70];
                printf("For %s, ", choice);
                fgets(input,70,stdin);
                if(input[0] == '0') break;
                char *ptr = strtok(input, " ");
                char storage[4][50];
                int i;
                for(i=0;i<4;i++){ strcpy(storage[i], "");}
                for(i=0;i<4;i++){
                    strcpy(storage[i], ptr);
                    ptr = strtok(NULL, " ");
                    if(ptr == NULL) break;
                }
                if(strlen(storage[1]) == 10 && strlen(storage[2]) == 5){
                    char date[11];
                    char time[6];
                    strcpy(date, storage[1]);
                    strcpy(time, storage[2]);
                    date[10] = '\0';
                    time[5] = '\0';
                    project_booking(storage[0], date, time,atoi(storage[3]));
                }else{
                    printf("Unaccepted input, please input the correct input.\n");
                }
            }
        }else if (strcmp(choice, "2b") == 0){
            FILE* file;
            char file_name[40];

            // ask for file_name
            printf("For %s, ", choice);
            scanf("%s", &file_name);
            printf("Filename: %s\n", file_name);
            file = fopen(file_name, "r");

            // check file
            if (file == NULL) exit(EXIT_FAILURE);

            char buffer[200];
            // int lineNum = 0;
            while(fgets(buffer, 200, file)!=NULL)
            {                

                char *ptr = strtok(buffer, " ");
                char storage[4][50];
                int i;
                
                for(i=0;i<4;i++){
                    strcpy(storage[i], ptr);
                    ptr = strtok(NULL, " ");
                    if(ptr == NULL) break;
                }

                // Start booking
                if(strlen(storage[1]) == 10 && strlen(storage[2]) == 5){
                    char date[11];
                    char time[6];
                    strcpy(date, storage[1]);
                    strcpy(time, storage[2]);
                    date[10] = '\0';
                    time[5] = '\0';
                    project_booking(storage[0], date, time,atoi(storage[3]));
                }else{
                    printf("Unaccepted input, please input the correct input.\n");
                }
            }
            


            //close file after read done
            fclose(file);

            char input[70];
            printf("Enter 0 to back to main menu ");
            while (1)
            {
                fgets(input,70,stdin);
                if(input[0] == '0') break;
            }
            
            
                
        }else if (strcmp(choice, "2c") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "3a") == 0){
            static int max_week = 3;// max week
            static int max_buf = 50;// max length of buffer

            int booking_count;      //for counting the numbers of booking
            int calendar[18][9];    // for check all teambooking time overlap
            int pid, week, i, j;  // comment var for child to use, and be counter
            int fd[6][2];           //for pipe, each week 2 pipes
            char storage[4][50], buffer[200];   //buffer for store data from file
            char time_buf[10];    // buffer for store the substring in datetime
            int day;    //store int of booking day

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

            if (pid = fork() < 0) {
                printf("Fork failed\n");
                exit(1);
            } else if (pid == 0) { // child
                int hour;   // store the int of hour
                int tid;    // store the team_id find from name

                for(week = 0; week < max_week; week++){    //child for 3 week sechulding
                    if (pid = fork() < 0) {
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
                    }

                    while(1){
                        while(strcmp(buffer, "") && strcmp(buffer, "no-booking")) read(fd[i*2+1][0], buffer, max_buf);  //wait for read and read booking

                        if(!strcmp(buffer, "no-booking")){
                            exit(0);
                        }

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
                            if(calendar[day-25][hour-9+i] == -1){
                                calendar[day-25][hour-9+i] = tid;
                            }
                        }
                    }
                }

                while(wait(NULL) > 0);  //wait for all child finish
            } else {         //parent to sorting all booking and assign to the child
                FILE *file = fopen("booking.dat", "r");     //to open the booking file

                for(i = 0; i < max_week; i++){
                    close(fd[i*2][0]); // close parent to child output
                    close(fd[i*2+1][1]); // close child to parent intput
                }

                //read file line by line
                while(fgets(buffer, 200, file)!=NULL){
                    strcpy(storage[0], strtok(buffer, " "));
                    for(i = 1 ; i < 4; i++){
                        strcpy(storage[i], strtok(NULL, " "));
                    }

                    //get the day for compare
                    strncpy(time_buf, &storage[2][8], 2);       // substring
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
            }
            
        } else if (strcmp(choice, "3b") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "3c") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "4") == 0){
            printf("bye\n");
            break;
        } else{ printf("Unaccepted input, please input the correct input.\n"); }
    }   
    return(0);
}