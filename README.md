### This project contains one program named schedulesim. his program needs to be compiled using the directions listed below.

## Schedulesim

To compile: `make schedulesim`

To run: `./schedulesim <numbercpu> <numberio> <numbercycles>`

The schedulesim program takes in three numbers as command line arguments. It creates a desired number of CPU-bound processes contained in the <numbercpu> command line argument and a desired number of IO-bound processes containd in <numberio> command line argument. It also takes in the number of CPU cycles as <numbercycles> command line argument. The schedulesim program simulates a process scheduler in four different ways. It creates a Round Robin scheduler, Fast Round Robin scheduler, Completely Fair scheduler and a Fast Completely Fair scheduler. These four schedulers get distribute the time for the use of each process in a given number of IO-bound and CPU-bound processes for a given total number of CPU cycles. Program prints to the terminal the statistics for each of the four schedulers. The generated statistics include the average number of nanoseconds per scheduler's use, average CPU time for CPU-bound processes, average wait time for CPU-bound processes, average CPU time for IO-bound processes and average wait time for IO-bound processes.


### Test results are provided in cputimes.pdf and timing.pdf 
