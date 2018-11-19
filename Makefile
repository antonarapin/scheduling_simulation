OPTS = -Wall -g -std=c++11

schedulesim: schedulesim.cc Scheduler.o Process.o simulate.o RBTNode.h RBTMultimap.h BSTForwardIterator.h BSTMultimap.h
	g++ ${OPTS} -o schedulesim schedulesim.cc Scheduler.o Process.o simulate.o

Process.o: Process.cc Process.h
	g++ ${OPTS} -c Process.cc

Scheduler.o: Scheduler.cc Scheduler.h Process.h ArrayList.h LinkedList.h List.h LinkedListNode.h
	g++ ${OPTS} -c Scheduler.cc

simulate.o: simulate.cc simulate.h Scheduler.h Process.h ArrayList.h LinkedList.h List.h LinkedListNode.h
	g++ ${OPTS} -c simulate.cc