#include "sigHandler.h"
struct itimerval timer;
struct sigaction sa;
int inputArray[100];
int inCounter = 0;
int readyQueue[100];
int i = 0;
int first = 0;
int currProc[4];
int nextProcIndex = 0;

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

void saHandler(int signum) {
    static int clock = 0;
    int printed = 0;

    //build the ready queue so basically a long term scheduler
    //enables rest of process handling
    //if havent processed everything and clock time = arrival time add to ready queue
    if((i < inCounter) && (inputArray[i+1] <= clock)) {
        readyQueue[i] = inputArray[i];
        readyQueue[i + 1] = inputArray[i + 1];
        readyQueue[i + 2] = inputArray[i + 2];
        readyQueue[i + 3] = inputArray[i + 3];
        if(clock == 1 && printed == 0){
            printf("Scheduler: Time Now: %d second\n", clock);
            printed = 1;
        }
        else if(printed == 0) {
            printf("Scheduler: Time Now: %d seconds\n", clock);
            printed = 1;
        }
        printf("New Process %d with remaining time of %d has arrived.\n",
               readyQueue[i], readyQueue[i + 2]);
        i = i + 4;
    }
    //initializeing first process when clock hits AT 1
    if(first == 0 && readyQueue[0] != -1){
        currProc[0] = readyQueue[0];
        currProc[1] = readyQueue[1];
        currProc[2] = readyQueue[2];
        readyQueue[3] = initProc(currProc[0]);
        usleep(300000);
        currProc[3] = readyQueue[3];
        first = 1;
        if(printed == 0){
            printf("Scheduler: Time Now: %d second\n", clock);
            printed = 1;
        }

        printf("Scheduling to Process %d (PID %d) whose remaining time is %d\n",
               currProc[0], currProc[3], currProc[2]);
        kill(currProc[3], sigStart);
    }
    //start processing the readyQueue
    //if already processing
    else if(readyQueue[0] > -1){
        //index
        int j = 0;
        int terminated = 0;
        //decrease bt of current process
        currProc[2] = currProc[2] - 1;

        //-------------------------------TERMINATE-------------------------
        //if if BT is 0 end it by setting variables out of bounds
        if(currProc[2] == 0){
            if(clock == 1 && printed == 0){
                printf("Scheduler: Time Now: %d second\n", clock);
                printed = 1;
            }
            else if(printed == 0) {
                printf("Scheduler: Time Now: %d seconds\n", clock);
                printed = 1;
            }
            printf("Terminating Process %d\n", currProc[0]);
            terminated = 1;
            kill(currProc[3], sigExit);
            //readyQueue[(currProc[0] * 3)] = 99;
            readyQueue[(currProc[0] * 4 + 1)] = 99;
            readyQueue[(currProc[0] * 4 + 2)] = 99;
            readyQueue[(currProc[0] * 4 + 3)] = 99;
            currProc[1] = 99;
            currProc[2] = 99;
            currProc[3] = 99;
        }

        int processedBT = currProc[2];
        int lowestbt = 0;
        int currIndex = 0;
        currIndex = currProc[0] * 4;
        readyQueue[currIndex + 2] = processedBT;

        //compare current process finished or not to rest of readyQueue
        //will reach -1 when finished scanning ready queue
        //------------------------------PROCESS-------------------------
        while(readyQueue[j] >= 0) {
            //if ready process BT is less than current process BT
            //find context switch is needed
            if ((readyQueue[j + 2] < currProc[2] || (readyQueue[j + 2] == currProc[2] && readyQueue[j] < currProc[0]))&& readyQueue[j + 2] != 99) { // && readyQueue[j + 2] != 99
                //printf("p0 bt: %d\n", readyQueue[2]);
                lowestbt = readyQueue[j + 2];
                nextProcIndex = (readyQueue[j] * 4);
            }
            //printf("nextProcIndex: %d\n", nextProcIndex);
            j = j + 4;

        }

        //IF CONTEXT SWITCHING
        if(currProc[0] != readyQueue[nextProcIndex]) {
            //main context switch

            if(printed == 0) {
                printf("Scheduler: Time Now: %d seconds\n", clock);
                printed = 1;
            }

            //first time switching to process
            if(readyQueue[nextProcIndex + 3] == -1){
                if(terminated != 1) {
                    printf("Suspending Process %d with remaining time of %d seconds and\n", currProc[0], currProc[2]);
                }
                currProc[0] = readyQueue[nextProcIndex];
                printf("Scheduling Process %d\n", currProc[0]);
                currProc[1] = readyQueue[nextProcIndex + 1];
                currProc[2] = readyQueue[nextProcIndex + 2];
                kill(currProc[3], sigSus);
                readyQueue[nextProcIndex + 3] = initProc(currProc[0]);
                currProc[3] = readyQueue[nextProcIndex + 3];
                //no touch give time for process to start
                usleep(300000);
                kill(currProc[3], sigStart);
            }
            //resuming process
            else {
                if(terminated != 1) {
                    printf("Suspending Process %d with remaining time of %d seconds and\n", currProc[0], currProc[2]);
                }
                currProc[0] = readyQueue[nextProcIndex];
                currProc[1] = readyQueue[nextProcIndex + 1];
                currProc[2] = readyQueue[nextProcIndex + 2];
                printf("Resuming Process %d whose remaing time is %d seconds\n", currProc[0], currProc[2]);
                //kill the old process
                kill(currProc[3], sigSus);
                currProc[3] = readyQueue[nextProcIndex + 3];
                //start new process
                kill(currProc[3], sigStart);
            }
        }
    }
    //increment clock
    clock++;
}

int main(int argc, char* argv[]) {
    //printf("Hello, World!\n");
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
        fscanf(inFile, "%d", &inputArray[inCounter + 2]);
        inputArray[inCounter + 3] = -1;
        printf("PID: %d    AT: %d    BT: %d    init %d\n",
               inputArray[inCounter], inputArray[inCounter+1], inputArray[inCounter+2], inputArray[inCounter+3]);
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