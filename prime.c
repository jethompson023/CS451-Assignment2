/*// MAKE SURE YOU USE LONG LONG INT AN ALSO PRINT USING %llu to print it Otherwise
//negative numbers will appear.
#include"sigHandler.h"

long unsigned int calculatedPrime = 123400003;
void handler(int signum);
int checkPrimeAndPrint(unsigned long int toCheck);
void resume();
void suspend();
void terminate();

long long prime;
long long test;
int process;
int bool = 0;
int check;

int main(int argc, char* argv[]){

// Set up handlers here
    signal(sigStart, handler);
    signal(sigSus, handler);
    signal(sigExit, handler);

    //generate random number based on process number given

    process = atoi(argv[1]);

    //printf("Process: %d\tPID: %d\n", process, getpid());
    for(int i = 0; i <= process; i++) {
        long  low = 10000;
        long  max = 99999;
        prime = (rand() % (max - low + 1)) + low;
        prime = abs(prime * low * 10) + ((rand() % (max - low + 1)) + low);
        //printf("%ld\n", prime);
    }
    test = prime;
    while(1){
        //printf("TEST\n");
        if(bool == 2) {
            //printf("EXITING\n");
            exit(0);
        }
    }
}


void handler(int signum){
// Write handler code here.

        if (signum == sigStart) {
            bool =1;
            resume();
        }
        if (signum == sigSus) {
            bool = 0;
            //resume();
            //sleep(.4);
            suspend();
        }
        if (signum == sigExit) {
            //sleep(.3);
            terminate();
        }
}

void resume(){
    //start
    if (bool == 1) {
        printf("Process %d: My PID is %d: I just got started. \n"
               "I am starting with the number %llu to find the next prime number.\n", process, getpid(), test);
    }

    while(bool == 1){
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
}
void suspend(){
    printf("Process %d: my PID is %d: I am about to be suspended... Highest\n"
           "prime number I found is %llu.\n",process, getpid(), prime);

}
void terminate(){
    printf("Process %d: my PID is %d: I completed my task and I am exiting.\n"
           "Highest prime number I found is %llu.\n",process, getpid(), prime);
    bool = 2;
}*/


// MAKE SURE YOU USE LONG LONG INT AN ALSO PRINT USING %llu to print it Otherwise
//negative numbers will appear.
#include"sigHandler.h"

long unsigned int calculatedPrime = 123400003;
void handler(int signum);
int checkPrimeAndPrint(unsigned long int toCheck);
void checkPrimes();
void resume();
void suspend();
void terminate();

long long prime;
long long test;
int process;
int bool = 0;
int check;

int main(int argc, char* argv[]){
// Set up handlers here
    signal(sigStart, handler);
    signal(sigSus, handler);
    signal(sigExit, handler);

    //generate random number based on process number given

    process = atoi(argv[1]);

    //printf("Process: %d\tPID: %d\n", process, getpid());
    for(int i = 0; i <= process; i++) {
        long  low = 10000;
        long  max = 99999;
        prime = (rand() % (max - low + 1)) + low;
        prime = abs(prime * low * 10) + ((rand() % (max - low + 1)) + low);
        //printf("%ld\n", prime);
    }
    test = prime;
    while(1){
        if(bool == 2)
            return 0;
        else if (bool == 1) {
            checkPrimes();
        }
    }
}


void handler(int signum){
// Write handler code here.

        if (signum == sigStart) {
            bool =1;
            resume();
        }
        if (signum == sigSus) {
            bool = 0;
            //resume();
            //sleep(.4);
            suspend();
        }
        if (signum == sigExit) {
            //sleep(.3);
            terminate();
        }
}

void checkPrimes() {
    //while(bool == 1){
        test = test + 1;
        check = 1;
        printf("TESTING %llu\n", test);
        for( int b = 2; b < test; b++){
            if ((test % b) == 0) {
                check = 0;
                break;
            }
        }
        if (check == 1) {
            prime = test;
        }

    //}
}

void resume(){
    //start
    if (bool == 1) {
        printf("Process %d: My PID is %d: I just got started. \n"
               "I am starting with the number %llu to find the next prime number.\n", process, getpid(), test);
    }
}
void suspend(){
    printf("Process %d: my PID is %d: I am about to be suspended... Highest\n"
           "prime number I found is %llu.\n",process, getpid(), prime);

}
void terminate(){
    printf("Process %d: my PID is %d: I completed my task and I am exiting.\n"
           "Highest prime number I found is %llu.\n",process, getpid(), prime);
    bool = 2;
}