#include "Process.h"
#include <iostream>
#include "Scheduler.h"
#include "simulate.h"

using namespace std;

int main(int argc, char * argv[]){
	string str_arr[] = {"Round Robin Scheduler","Fast Round Robin Scheduler","Completely Fair Scheduler","Fast Completely Fair Scheduler"};
	FastRoundRobin frr;
	RoundRobin rr;
	CompletelyFair cf;
	FastCompletelyFair fcf;
	Scheduler* sch_arr[] = {&rr,&frr,&cf,&fcf};

	for(int i =0; i<4; i++){
		cout<<" *** Statistics for "<<str_arr[i]<<" ***"<<"\n"<<endl;
		double* n = simulate(sch_arr[i],atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
		cout<<"Number of CPU-bound processes: "<<atoi(argv[1])<<"\n"<<"Number of IO-bound processes: "<<atoi(argv[2])<<"\n"<<"Number of Cycles: "<<atoi(argv[3])<<endl;
		cout<<"The number of nanoseconds per scheduler use: "<<n[0]<<endl;
		cout<<"Average CPU time of all CPU-bound processes: "<<n[1]<<endl;
		cout<<"Average Wait time of all CPU-bound processes: "<<n[2]<<endl;
		cout<<"Average CPU time of all IO-bound processes: "<<n[3]<<endl;
		cout<<"Average Wait time of all IO-bound processes: "<<n[4]<<endl;
		cout<<endl;
		delete[] n;
	}
	

	return 0;
}
