readme

intructions and limitations of strfScheduler Lab 2

FILES
-main.c
	main file of program
	parses command line arguments/options
-prime.c
	functionality file for each option
-sigHandler.h
	header file
	includes all C labraries used in program

COMPILE
-Have all files in same directory
-Use gcc compiler enter the following
	gcc -o main main.c sigHandler.h
	gcc -o prime prime.c sigHandler.h

RUN:
-after compiling run the program in the same directory
-enter the following with or without the optional parameters
	./main input.txt
-program will error out on the following conditions
	unable to open/read input file
	
OPTIONS and ARGUMENTS
file name with the PID arrival time(AT) and burst time(BT) of up to 10 processes
PID AT BT
0 1 7

KNOWN ISSUES
-Will struggle past 5 different processes
	
