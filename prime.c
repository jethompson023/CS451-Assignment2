
// MAKE SURE YOU USE LONG LONG INT AN ALSO PRINT USING %llu to print it Otherwise
//negative numbers will appear.
//#include"sigHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

long unsigned int calculatedPrime = 123400003;
void contHandler(int signum);
void susHandler(int signum);
void exitHandler(int signum);
int checkPrimeAndPrint(unsigned long int toCheck);
void checkPrimes();

long long prime;
long long test;
int process;
int bool = 0;
int check;

int main(int argc, char* argv[]){
// Set up handlers here

    process = atoi(argv[1]);

    signal(SIGCONT, contHandler);
    signal(SIGTSTP, susHandler);
    signal(SIGTERM, exitHandler);

    //generate random number based on process number given

 

    //printf("Process: %d\tPID: %d\n", process, getpid());
    for(int i = 0; i <= process; i++) {
        long  low = 100;
        long  max = 999;
        prime = (rand() % (max - low + 1)) + low;
        prime = abs(prime * low * 10) + ((rand() % (max - low + 1)) + low);
        //printf("%ld\n", prime);
    }
    //prime = 2;
    test = prime;
    
    printf("Process %d: My PID is %d: I just got started!!! \n"
            "I am starting with the number %llu to find the next prime number.\n", process, getpid(), test);
    bool = 1;
    
    while(1){
        if (bool == 1) {
            test = test + 1;
            check = 1;
            //printf("TESTING %llu\n", test);
            for( int b = 2; b < test; b++){
                if ((test % b) == 0) {
                    check = 0;
                    break;
                }
            }
            if (check == 1) {
                prime = test;
            }
        }
        else if (bool == 0) {
        }
        else if (bool == 2)
            exit(0);
    }
}


void contHandler(int signum){
// Write handler code here.
    printf("Process %d: My PID is %d: I just got started. \n"
            "I am starting with the number %llu to find the next prime number.\n", process, getpid(), test);
    bool = 1;
    
}

void susHandler(int signum){
// Write handler code here.
    bool = 0;
    printf("Process %d: my PID is %d: I am about to be suspended... Highest\n"
           "prime number I found is %llu.\n",process, getpid(), prime);
    
}

void exitHandler(int signum){
// Write handler code here.
    bool = 2;
    printf("Process %d: my PID is %d: I completed my task and I am exiting.\n"
           "Highest prime number I found is %llu.\n",process, getpid(), prime);
}