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
int prevProcess = -1;
int currAT;
int currBT;
int currPID;
int isNew;
int totalTime = 0;
int totalNumProc = 0;

int initProc(int processNumber){
    pid_t pid;
    switch(processNumber) {
        case 0:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "0", NULL};
                execvp("./prime", args);
            }
            break;
        case 1:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "1", NULL};
                execvp("./prime", args);
            }
            break;
        case 2:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "2", NULL};
                execvp("./prime", args);
            }
            break;
        case 3:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "3", NULL};
                execvp("./prime", args);
            }
            break;
        case 4:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "4", NULL};
                execvp("./prime", args);
            }
            break;
        case 5:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "5", NULL};
                execvp("./prime", args);
            }
            break;
        case 6:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "6", NULL};
                execvp("./prime", args);
            }
            break;
        case 7:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "7", NULL};
                execvp("./prime", args);
            }
            break;
        case 8:
            if ((pid = fork()) == 0) { //child
                //printf("attempting to start prime.c\n");
                char *args[] = {"./prime", "8", NULL};
                execvp("./prime", args);
            }
            break;
        case 9:
            if ((pid = fork()) == 0) { //child
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
        //printf("\nCONTEXT SWITCHING\n");

        //initialize a new process if we havent already 
        if (inputArray[currRunningProcess + 3] == NEW) {
            inputArray[currRunningProcess + 2] = initProc(inputArray[currRunningProcess]);
            inputArray[currRunningProcess + 3] = OLD;
        }
        
        //printf("TESTING PROCESS NUMBER %d with time %d\n", inputArray[currRunningProcess], inputArray[currRunningProcess + 1]);

        //start process if it still has burst
        if (inputArray[currRunningProcess + 1] > 0) {
            //process has a burst left, suspend, otherwise terminate
            if (inputArray[prevProcess] != -1) {
                if (inputArray[prevProcess + 1] > interval)
                    kill(inputArray[prevProcess + 2],  SIGTSTP);
                else {
                    kill(inputArray[prevProcess + 2],  SIGTERM);
                }
            }
            usleep(100);

            printf("Scheduling to Process %d (PID %d) whose remaining time is %d\n",
                inputArray[currRunningProcess], inputArray[currRunningProcess + 2], inputArray[currRunningProcess + 1]);
            kill(inputArray[currRunningProcess + 2],  SIGCONT);
        }

        /*
        if (clock % 2 == 0)
            kill(inputArray[currRunningProcess + 2],  SIGCONT);

        if (clock % 3 == 0)
            kill(inputArray[currRunningProcess + 2],  SIGTSTP);

        
        if (clock % 5 == 0)
            kill(inputArray[currRunningProcess + 2],  SIGTERM);*/

 
    prevProcess = currRunningProcess; //set previous process
    do {
        currRunningProcess = currRunningProcess + 4; //next current process number is 4 more in the array than the last

        //if current running process reached end of array, reset back to first process in array
        if(currRunningProcess > inCounter - 2)
            currRunningProcess = 0;

    } while (inputArray[currRunningProcess + 1] == 0);

    //printf("FOUND PROCESS NUMBER %d with time %d AT THE END OF CONTEXT SWITCH\n", inputArray[currRunningProcess], inputArray[currRunningProcess + 1]);

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

    if (clock == totalTime) {
        kill(inputArray[prevProcess + 2],  SIGTERM);
        exit(0);
    }
    

    printf("SCHEDULING TIME IS %d\n", clock);
    //decrement burst only if the current process isnt new
    if (inputArray[currRunningProcess + 3] != NEW)
        inputArray[currRunningProcess + 1]--;
    

    //only context switch if time quantum is met
    if (clock % interval == 0) {
        int test = currRunningProcess;
        while (inputArray[currRunningProcess + 1] == 0) {
            currRunningProcess = currRunningProcess + 4; //next current process number is 4 more in the array than the last

            //if current running process reached end of array, reset back to first process in array
            if(currRunningProcess > inCounter - 2)
                currRunningProcess = 0;
        }
        if (test != currRunningProcess)
            inputArray[currRunningProcess + 1] = inputArray[currRunningProcess + 1] - 2;
        contextSwitch(clock);
    }
        

    //printf("Scheduler Time is %d\n", clock);
    clock++;
}

void printInput() {
    for (int i = 0; i < inCounter; i++) {
        printf("%d ", inputArray[i]);
    }
}

void addAllBT() {
    for (int i = 0; i < totalNumProc*4; i = i+4) {
        printf("TEST NUMBER IS %d\n", inputArray[i + 1]);
        totalTime = totalTime + inputArray[i + 1];
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
        totalNumProc++;
        fscanf(inFile, "%d", &inputArray[inCounter]);
        fscanf(inFile, "%d", &inputArray[inCounter + 1]);
        inputArray[inCounter + 3] = NEW;
        printf("PNUM: %d BT: %d\n",
               inputArray[inCounter], inputArray[inCounter+1]);
        inCounter = inCounter + 4;
    }

    //close input file
    fclose(inFile);

    //add all the burst times
    addAllBT();

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