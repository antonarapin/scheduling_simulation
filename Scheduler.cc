#include "Scheduler.h"
#include <iostream>

using namespace std;

RoundRobin::RoundRobin(){
	procQueue = new ArrayList<Process*>;
}
RoundRobin::~RoundRobin(){
	delete procQueue;
}
void RoundRobin::addProcess(Process* proc){
	procQueue->pushBack(proc);
}
Process* RoundRobin::popNext(int curCycle){
	Process* tmp = procQueue->getFront();
	procQueue->popFront();
	return tmp;
}
FastRoundRobin::FastRoundRobin():RoundRobin()
{
	delete procQueue;
	procQueue = new LinkedList<Process*>;
}
CompletelyFair::CompletelyFair(){
	procTree = new BSTMultimap<int,Process*>;
}
CompletelyFair::~CompletelyFair(){
	delete procTree;
}
void CompletelyFair::addProcess(Process* proc){
	procTree->insert(proc->getCPUTime(),proc);
}
Process* CompletelyFair::popNext(int curCycle){
	BSTForwardIterator<int, Process*> it1 = procTree->getMin();
	while(!it1.isPastEnd() && (it1.getValue()->isBlocked(curCycle))){
		it1.next();
	}
	Process* popped_proc = it1.getValue();

	BSTForwardIterator<int, Process*> it2 = procTree->remove(it1);
	//cout<<"removed, returning"<<endl;
	return popped_proc;
}
FastCompletelyFair::FastCompletelyFair(){
	delete procTree;
	procTree=new RBTMultimap<int,Process*>;
}

