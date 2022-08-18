#include "sigHandler.h"
#include <stdbool.h>
struct itimerval timer;
struct sigaction sa;
int inputArray[100];
int inCounter = 0;
int interval;
int readyQueue[100];
int first = 0;
int NEW = 1;
int OLD = -1;
int currProc[4];
int nextProcIndex = 0;
int count = 0;

int processCount = 0;
int currRunningProcess = 0;
int currAT;
int currBT;
int currPID;
int isNew;

int initProc(int processNumber){
    int pid;
    switch(processNumber) {
        case 0:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "0", NULL};
                execvp("./prime", args);

            }
            break;
        case 1:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "1", NULL};
                execvp("./prime", args);

            }
            break;
        case 2:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "2", NULL};
                execvp("./prime", args);

            }
            break;
        case 3:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "3", NULL};
                execvp("./prime", args);

            }
            break;
        case 4:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "4", NULL};
                execvp("./prime", args);

            }
            break;
        case 5:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "5", NULL};
                execvp("./prime", args);

            }
            break;
        case 6:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "6", NULL};
                execvp("./prime", args);

            }
            break;
        case 7:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "7", NULL};
                execvp("./prime", args);

            }
            break;
        case 8:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "8", NULL};
                execvp("./prime", args);

            }
            break;
        case 9:
            if ((pid = fork()) < 0) {
                printf("Fork Failed\n");
            } else if (pid == 0) { //child

                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "9", NULL};
                execvp("./prime", args);

            }
            break;
        default:
            printf("Process limit exceeded!\n");
    }
    if(pid > 0){
        return pid;
    }
}

//inputArray[currRunningProcess] = ProcessNumber
//inputArray[currRunningProcess + 1] = Burst Time
//inputArray[currRunningProcess + 2] = PID
//inputArray[currRunningProcess + 3] = isNew
void contextSwitch(int clock) {
    printf("\nCONTEXT SWITCHING\n");
    
    if(currRunningProcess > inCounter - 2)
        currRunningProcess = 0;

    if (inputArray[currRunningProcess + 3] == NEW) {
        inputArray[currRunningProcess + 2] = initProc(inputArray[currRunningProcess]);
        inputArray[currRunningProcess + 3] = OLD;
    }
    //usleep(30000);
    kill(inputArray[currRunningProcess + 2], sigStart);
    
    
    currRunningProcess = currRunningProcess + 4;


/*
    if (processCount >= (inCounter/3)*5) {
        processCount = 0;
        currRunningProcess = processCount;
        printf("LOOPED THROUGH ALL PROCESSES\n");
    }

    if (readyQueue[currRunningProcess + 2] <= 0) {
        printf("\n\nTHE PROCESS NUMBER OF %d IS TERMINATED\n\n", readyQueue[currRunningProcess]);
    }

    if (currRunningProcess != -1 && readyQueue[currRunningProcess + 2] != 0 && currRunningProcess != processCount) {
        printf("SUSPENDING PROCESS %d\n", readyQueue[currRunningProcess]);
        kill(readyQueue[currRunningProcess + 4], sigSus);
    }
        currRunningProcess = processCount;
        if (readyQueue[currRunningProcess + 3] == NEW) {
            printf("INITING PROC %d\n", readyQueue[currRunningProcess]);
            readyQueue[currRunningProcess + 4] = initProc(readyQueue[currRunningProcess]); //PID
            readyQueue[currRunningProcess + 3] = OLD;
        }
        printf("Scheduler: Time Now: %d second\n", clock);

        printf("Scheduling to Process %d (PID %d) whose remaining time is %d\n",
                readyQueue[currRunningProcess], readyQueue[currRunningProcess + 4], readyQueue[currRunningProcess + 2]);

        //usleep(3);
        kill(readyQueue[currRunningProcess + 4], sigStart);
        processCount = processCount + 5; //go to next process in the ready queue*/
}

//inputArray[currRunningProcess] = ProcessNumber
//inputArray[currRunningProcess + 1] = Burst Time
//inputArray[currRunningProcess + 2] = PID
//inputArray[currRunningProcess + 3] = isNew
void saHandler(int signum) {
    static int clock = 0;

    inputArray[currRunningProcess + 1]--;
    if (clock % interval == 0)
        contextSwitch(clock);

    clock++;
    /*
    int printed = 0;


    //build the ready queue so basically a long term scheduler
    //enables rest of process handling
    //clock time <= arrival time and it already isnt in the ready queue, add to ready queue
    for (int processNum = 0; processNum < inCounter; processNum = processNum + 3) {
        if((inputArray[processNum+1] <= clock) && inputArray[processNum] != -1) {
            readyQueue[count] = inputArray[processNum];
            readyQueue[count + 1] = inputArray[processNum + 1];
            readyQueue[count + 2] = inputArray[processNum + 2];
            readyQueue[count + 3] = NEW;
            inputArray[processNum] = -1;
            if(printed == 0) {
                printf("Scheduler: Time Now: %d seconds\n", clock);
                printed = 1;
            }
            printf("New Process %d with remaining time of %d has arrived.\n",
               readyQueue[count], readyQueue[count + 2]);
            processNum = processNum + 3;
            count = count + 5;
        }
    }
    readyQueue[currRunningProcess + 2]--;
    if (readyQueue[currRunningProcess + 2] == 0 && currRunningProcess != -1) {
        printf("Terminating Process %d (PID %d) whose remaining time is %d\n",
            readyQueue[currRunningProcess], readyQueue[currRunningProcess + 4], readyQueue[currRunningProcess + 2]);
        //readyQueue[currRunningProcess] = -1;
        kill(readyQueue[currRunningProcess + 4], sigExit);
    }
        
    if (clock % interval == 0 && readyQueue[0] != -1)
        contextSwitch(clock);
    clock++;*/
}

void printInput() {
    for (int i = 0; i < inCounter; i++) {
        printf("%d ", inputArray[i]);
    }
}

int main(int argc, char* argv[]) {
    interval = atoi(argv[2]);
    //initialize readyQueue
    for(int r = 0; r < 100; r++){
        readyQueue[r] = -1;
    }

    //open input file
    FILE* inFile;
    inFile = fopen(argv[1], "r");
    if (inFile == NULL){
        printf("error oppening file\n");
        //sys exit
    }
    else{
        printf("input file opened\n");
    }

    //reading input file
    while(!feof(inFile)){
        fscanf(inFile, "%d", &inputArray[inCounter]);
        fscanf(inFile, "%d", &inputArray[inCounter + 1]);
        inputArray[inCounter + 3] = NEW;
        printf("PNUM: %d BT: %d\n",
               inputArray[inCounter], inputArray[inCounter+1]);
        inCounter = inCounter + 4;
    }

    //close input file
    fclose(inFile);

    //starting SIGALRM handler saHandler
    //memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &saHandler;
    sigaction (SIGALRM, &sa, NULL);

    //initializing timer variables
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    //starting timer
    setitimer (ITIMER_REAL, &timer, NULL);
    while(1) {

    }

    return 0;
}