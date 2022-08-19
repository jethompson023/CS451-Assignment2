/*
Author: Reis Ciaramitaro & Jeremiah Thompson
Assignment Number: 2
Date of Submission: 8/18/2022
Name of this file: prime
Short Description of contents:
   This program that computes larger and larger prime numbers
*/

// MAKE SURE YOU USE LONG LONG INT AN ALSO PRINT USING %llu to print it Otherwise
//negative numbers will appear.
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
    for(int i = 0; i <= process; i++) {
        long  low = 100;
        long  max = 999;
        prime = (rand() % (max - low + 1)) + low;
        prime = abs(prime * low * 10) + ((rand() % (max - low + 1)) + low);
        //printf("%ld\n", prime);
    }
    test = prime;
    
    printf("Process %d: My PID is %d: I just got started!!! \n"
            "I am starting with the number %llu to find the next prime number.\n", process, getpid(), test);
    bool = 1;
    
    while(1){
        if (bool == 1) {
            test = test + 1;
            check = 1;
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

/*
    Function Name: contHandler
    Input to the method:  
    Output(Return value): 
    
    Brief description of the task:
    This is a handler for the SIGCONT signal
*/
void contHandler(int signum){
    printf("Process %d: My PID is %d: I just got started. \n"
            "I am starting with the number %llu to find the next prime number.\n", process, getpid(), test);
    bool = 1;
    
}
/*
    Function Name: susHandler
    Input to the method:  
    Output(Return value): 
    
    Brief description of the task:
    This is a handler for the SIGTSTP signal
*/
void susHandler(int signum){
    bool = 0;
    printf("Process %d: my PID is %d: I am about to be suspended... Highest\n"
           "prime number I found is %llu.\n",process, getpid(), prime);
    
}
/*
    Function Name: exitHandler
    Input to the method:  
    Output(Return value): 
    
    Brief description of the task:
    This is a handler for the SIGTERM signal
*/
void exitHandler(int signum){
    bool = 2;
    printf("Process %d: my PID is %d: I completed my task and I am exiting.\n"
           "Highest prime number I found is %llu.\n",process, getpid(), prime);
}