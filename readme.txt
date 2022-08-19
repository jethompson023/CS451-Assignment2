FILES
-rrScheduler.c
	main file of program
	parses command line arguments/options
-prime.c
	functionality file for each option

COMPILE
-Have all files in same directory
-Use gcc compiler enter the following
	gcc -o rrScheduler rrScheduler.c
	gcc -o prime prime.c

RUN:
-after compiling run the program in the same directory
-enter the following
	./rrScheduler input.txt <TimeSlice>
	
This program takes in processes via a text file and performs
a Round Robin scheduling algorithm to run each process for a specified time slice given
All processes will terminate when their burst time is 0.
	
OPTIONS and ARGUMENTS
file name with the PID arrival time(AT) and burst time(BT) of up to 10 processes
0 20

KNOWN ISSUES
-The input file must only have integers and cannot parse any headers
	The first column relates to process number
	The second column relates to burst time
	
