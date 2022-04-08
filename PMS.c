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
            schedule_FIFC();
            
        } else if (strcmp(choice, "3b") == 0){
            schedule_Priority();
        } else if (strcmp(choice, "3c") == 0){
            printf("choice %s\n", choice);      //debug use
        } else if (strcmp(choice, "4") == 0){
            // delete the booking.txt           
            if (remove("booking.txt") == 0 && remove("sorted.dat") == 0){
                printf("booking.txt and sorted removed!\n");
            }
            
            printf("bye\n");
            break;
        } else{ printf("Unaccepted input, please input the correct input.\n"); }
    }   
    return(0);
}