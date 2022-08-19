/*
Author: Reis Ciaramitaro & Jeremiah Thompson
Assignment Number: 2
Date of Submission: 8/18/2022
Name of this file: rrScheduler
Short Description of contents:
   This program takes in processes via a text file and performs
    a Round Robin scheduling algorithm to run each process for a specified time slice given
    All processes will terminate when their burst time is 0.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>


struct itimerval timer;
struct sigaction sa;
int inputArray[100];
int inCounter = 0;
int interval;
int NEW = 1;
int OLD = -1;

//int count = 0;

int currRunningProcess = 0;
int prevProcess = -1;
int totalNumProc = 0;


/*
    Function Name: initProc
    Input to the method: processNumber  
    Output(Return value): pid
    
    Brief description of the task:
    This process we are going throguh each case and reading the process id then
    performing a fork command to create the child process.
*/
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

/*
    Function Name: contextSwitch
    Input to the method: clock  
    Output(Return value): message to the user showing the the next scheduled process along with teh remaining time
    
    Brief description of the task:
    This process we are going throguh each case and reading the process id then
    performing a fork command to create the child process.
*/
void contextSwitch(int clock) {
        int cycles = 0;

        //initialize a new process if we havent already 
        if (inputArray[currRunningProcess + 3] == NEW) {
            inputArray[currRunningProcess + 2] = initProc(inputArray[currRunningProcess]);
            inputArray[currRunningProcess + 3] = OLD;
        }

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
 
    prevProcess = currRunningProcess; //set previous process
    do {
        cycles++;
        currRunningProcess = currRunningProcess + 4; //next current process number is 4 more in the array than the last

        //if current running process reached end of array, reset back to first process in array
        if(currRunningProcess > inCounter - 2)
            currRunningProcess = 0;

        //all processes are terminated, exit
        if (cycles == totalNumProc) {
            kill(inputArray[prevProcess + 2],  SIGTERM);
            exit(0);
        }

    } while (inputArray[currRunningProcess + 1] == 0);
}

/*
    Function Name: saHandler
    Input to the method: signum  
    Output(Return value): clock 
    
    Brief description of the task:
    This process we are going throguh each case and reading the process id then
    performing a fork command to create the child process.
*/
void saHandler(int signum) {
    static int clock = 0;
    int cycles = 0;

    printf("SCHEDULING TIME IS %d\n", clock);
    //decrement burst only if the current process isnt new
    if (inputArray[currRunningProcess + 3] != NEW)
        inputArray[currRunningProcess + 1]--;

    //only context switch if time quantum is met
    if (clock % interval == 0) {
        int test = currRunningProcess;
        while (inputArray[currRunningProcess + 1] <= 0) {
            cycles++;
            currRunningProcess = currRunningProcess + 4; //next current process number is 4 more in the array than the last

            //if current running process reached end of array, reset back to first process in array
            if(currRunningProcess > inCounter - 2)
                currRunningProcess = 0;

            //all processes are terminated, exit
            if (cycles == totalNumProc) {
                kill(inputArray[prevProcess + 2],  SIGTERM);
                exit(0);
            }
        }
        if (test != currRunningProcess)
            inputArray[currRunningProcess + 1] = inputArray[currRunningProcess + 1] - 2;
        contextSwitch(clock);
    }

    //printf("Scheduler Time is %d\n", clock);
    clock++;
}

/*
    Function Name: contextSwitch
    Input to the method:   
    Output(Return value): clock 
    
    Brief description of the task:
    This process we are going throguh each case and reading the process id then
    performing a fork command to create the child process.
*/

void printInput() {
    for (int i = 0; i < inCounter; i++) {
        printf("%d ", inputArray[i]);
    }
}



int main(int argc, char* argv[]) {
    interval = atoi(argv[2]);

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

    //starting SIGALRM handler saHandler
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