#include "simulate.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles){
	double* double_arr = new double[5];
	stack<Process*> procContainer;
	stack<Process*> deleteContainer;
	long long sym_cycles=0;
	long long num_pops = 0;
	long long CPUB_cpuT=0;
	long long CPUB_waitT=0;
	long long IOB_cpuT=0;
	long long IOB_waitT=0;
	long long numCPUB=0;
	long long numIOB=0;
	long long cycCPU=0;
	long long cycIO=0;
	for(int i = 0; i<numCPUBound; i++){
		Process* newproc = new CPUBoundProcess(1);
		sched->addProcess(newproc);
		procContainer.push(newproc);
	}
	for(int j = 0; j<numIOBound; j++){
		Process* newproc = new IOBoundProcess(2);
		sched->addProcess(newproc);
		procContainer.push(newproc);
	}
	auto t_s = chrono::system_clock::now();
	while (sym_cycles<=numCycles){
		Process* curr_proc = sched->popNext(sym_cycles);
		num_pops+=1;
		int cyc_now;
		cyc_now=curr_proc->simulate(sym_cycles, 10);
		sym_cycles+=cyc_now;
		sched->addProcess(curr_proc);
		if(curr_proc->getID()==1){
			cycCPU+=cyc_now;
		} else{
			cycIO+=cyc_now;
		}
		
	
	}
	auto t_f = chrono::system_clock::now();
	auto dur=t_f-t_s;
	auto durationMS = chrono::duration_cast<chrono::nanoseconds>(dur);
	for(int i =0; i<(numCPUBound+numIOBound); i++){
		Process* curr_proc = procContainer.top();
		procContainer.pop();
		if(curr_proc->getID()==1){
			CPUB_cpuT+=curr_proc->getCPUTime();
			CPUB_waitT+=curr_proc->getWaitTime(sym_cycles);
			numCPUB+=1;
		} else{
			IOB_cpuT+=curr_proc->getCPUTime();
			IOB_waitT+=curr_proc->getWaitTime(sym_cycles);
			numIOB+=1;
		}
		deleteContainer.push(curr_proc);
	}
	double_arr[0] = ((durationMS.count())/num_pops); 
	double_arr[1] = (CPUB_cpuT/numCPUB);
	double_arr[2] = (CPUB_waitT/numCPUB);
	double_arr[3] = (IOB_cpuT/numIOB);
	double_arr[4] = (IOB_waitT/numIOB);
	
	// delete all of the dynamically allocated processes
	for(int i =0; i<(numCPUBound+numIOBound); i++){
		Process* curr_proc = deleteContainer.top();
		deleteContainer.pop();
		delete curr_proc;
	}


	return double_arr;

}
