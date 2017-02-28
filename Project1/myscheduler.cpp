//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	MyThread* t = new MyThread(arriving_time, remaining_time, priority, tid);

	switch (policy) {
	case FCFS:
		myQueue.push(*t);
		break;

	case STRFwoP: case STRFwP: case PBS:
		myPriority_Queue.push(*t);
		break;

	default:
		cout << "Error: Invalid Policy";
		throw 0;
	}
}

bool MyScheduler::Dispatch()
{
	// Check and remove finished threads
	

	//Todo: Check if all the threads are finished; if so, return false


	switch(policy)
	{
		case FCFS:		//First Come First Serve

			// Implemented most quickly with a regular queue, rather simple

			// USE myQueue

			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption

			// Implemented most quickly with priority queue (heap). 
			// w/o preemption meaning processes already running will 
			//	continue running until completion. 

			// USE myPriorityQueue

			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption

			// Implemented most quickly with priority queue (heap).
			// w/ preemption meaning if a new process with higher priority
			//	is inserted into the priority queue it will immediately 
			//	begin executing. 

			// USE myPriorityQueue

			break;
		case PBS:		//Priority Based Scheduling, with preemption

			// Implemented most quickly with priority queue (heap).
			// w/ preemption means if a new process with higher priority is 
			//	inserted into the queue it is run immediately. 

			// USE myPriorityQueue

			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}
	return true;
}