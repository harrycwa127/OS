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
            static int week_num = 3;// max week
            int booking_count;      //for counting the numbers of booking
            int calendar[18][9];    // for check all teambooking time overlap
            int pid, mypid, week, i, j, k;  // comment var for child to use, and be counter
            int fd[6][2];           //for pipe, each week 2 pipes

            // init pipe, i*2 for parent to child, 1*2+1 for child to parent
            for(i = 0; i < week_num; i++){
                if (pipe(fd[i*2]) < 0 || pipe(fd[i*2+1]) < 0 ) {
                    printf("Pipe creation error\n");
                    exit(1);
                }
            }

            if (pid = fork() < 0) {
                printf("Fork failed\n");
                exit(1);
            } else if (pid == 0) { // child
                for(week = 0; week < week_num; week++){    //child for 3 week sechulding
                    if (pid = fork() < 0) {
                        printf("Fork failed\n");
                        exit(1);

                    } else if (pid == 0) { // child

                        //close unused pipe
                        close(fd[week*2][1]); // close parent to child input
                        close(fd[week*2+1][0]); // close child to parent output
                        for(i=0; i < week_num; i++){
                            if(i != week){
                                close(fd[i*2][0]);
                                close(fd[i*2][1]);
                                close(fd[i*2+1][0]);
                                close(fd[i*2+1][1]);
                            }
                        }

                    }
                }

                while(wait(NULL) > 0);  //wait for all child finish
            } else {                                //parent to sorting all booking and assign to the child
                FILE *file = fopen("booking.dat", "r");     //to open the booking file
                char storage[4][50], buffer[200];   //buffer for store data from file

                //read file line by line
                while(fgets(buffer, 200, file)!=NULL){
                    strcpy(storage[0], strtok(buffer, " "));
                    for(i = 1 ; i < 4; i++){
                        strcpy(storage[i], strtok(NULL, " "));
                    }
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