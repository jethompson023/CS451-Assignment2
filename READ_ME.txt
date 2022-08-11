CS Assignment 2: Round Robin Scheduling using Timer

Objective
Write a scheduler called "rrScheduler" to schedule processes to run, using the round robin scheduling algorithm in
which each process gets equal amount of time (called time slice given in seconds) on the CPU


rrScheduler program Process Flow

    1) Creates one child process for each process in the file
        1a) Schedules them according to the round robin algorithm
            Requirements to run:
            a) It ensures that, at every instant of time, there is
              only one process running
            b) the running process is the one chosen by round robin scheduling algorithm. 
   
   2) A process is taken off the CPU either when the running process finishes its time slice
        2a) or, the process finishes its CPU burst.

Program Inputs
The input to the scheduler consists of:
    1) m (m <=10) lines
    2) Each line contains a process id (0 to m-1)
    3) the CPU burst of each process, separated by one or more spaces. 
    4) There will be a header line in the input file which is not processed.
    IMPORTANT NOTE: Some process id’s may be missing due to those processes having completed already.

Order of the Process ID's: The process IDs will be in the order of increasing values.