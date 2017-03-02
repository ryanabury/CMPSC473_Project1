//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

//////////////////////////////////////////////////
/* Authors: Ryan Bury, Tyler Bohrer, Sam Barnes */
//////////////////////////////////////////////////

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	ThreadDescriptorBlock* t = new ThreadDescriptorBlock();

	t->arriving_time = arriving_time;
	t->remaining_time = remaining_time;
	t->priority = priority;
	t->tid = tid;

	if (t->arriving_time == 0) {
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
		cout << "Added thread " << tid << " to Data structure\n";
	}
	else {
		notReadyQueue.push(*t);

		//cout << "Added thread " << tid << " to not_ready Queue\n";
	}
}

bool MyScheduler::Dispatch()
{
	// Check notReadyQueue to see if threads are ready
	while (!notReadyQueue.empty() && notReadyQueue.top().arriving_time <= timer) {
		int tid = notReadyQueue.top().tid;
		switch (policy) {
		case FCFS:
			myQueue.push(notReadyQueue.top());
			notReadyQueue.pop();
			break;

		case STRFwoP: case STRFwP: case PBS:
			myPriority_Queue.push(notReadyQueue.top());
			notReadyQueue.pop();
			break;

		default:
			cout << "Error: Invalid Policy";
			throw 0;
		}
		cout << "Thread " << tid << " has arrived and is waiting\n";
	}

	// Check if all the threads are finished; if so, return false
	bool done = true;
	for (int i = 0; i < num_cpu; ++i) {
		if (CPUs[i] != NULL)
			done = false;
		
	}
	if (!notReadyQueue.empty())
		done = false;
	switch (policy) {
		case FCFS:
			if (!myQueue.empty())
				done = false;
			break;
		case STRFwoP: case STRFwP: case PBS:
			if (!myPriority_Queue.empty())
				done = false;
			break;
		default:
			cout << "Error: Invalid policy";
			throw 0;
	}
	if (done) {
		return false;
	}

	// Define Policies here
	switch(policy)
	{
		case FCFS:		//First Come First Serve

			// Implemented most quickly with a regular queue, rather simple

			// USE myQueue

			for (int i = 0; i < num_cpu; ++i) {
				if (myQueue.empty())
					continue;
				if (CPUs[i] == NULL) {
					cout << "Adding thread " << myQueue.front().tid << " to CPU " << i << "\n";
					CPUs[i] = &(myQueue.front());
					myQueue.pop();
				}
			}

			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption

			// Implemented most quickly with priority queue (heap). 
			// w/o preemption meaning processes already running will 
			//	continue running until completion. 

			// USE myPriorityQueue

			for (int i = 0; i < num_cpu; ++i) {
				if (myPriority_Queue.empty())
					continue;
				if (CPUs[i] == NULL) {
					cout << "Adding thread " << myPriority_Queue.top().tid << " to CPU " << i << "\n";
					CPUs[i] = new ThreadDescriptorBlock(myPriority_Queue.top());
					myPriority_Queue.pop();
				}
			}

			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption

			// Implemented most quickly with priority queue (heap).
			// w/ preemption meaning if a new process with higher priority
			//	is inserted into the priority queue it will immediately 
			//	begin executing. 

			// USE myPriorityQueue

			for (int i = 0; i < num_cpu; ++i) {	
				// Make sure PriorityQueue isn't empty, otherwise errors. 
				if (myPriority_Queue.empty())
					continue;
				// Add highest priority thread to idle CPUs
				if (CPUs[i] == NULL) {
					cout << "Adding thread " << myPriority_Queue.top().tid << " to CPU " << i << "\n";
					CPUs[i] = new ThreadDescriptorBlock(myPriority_Queue.top());
					myPriority_Queue.pop();
				}
				// Implement Preemption 
				//	1. remove thread from CPU and insert back into Priority Queue
				//	2. Insert new thread into CPU and pop from Priority Queue
				else if (CPUs[i]->remaining_time > myPriority_Queue.top().remaining_time) {					
					ThreadDescriptorBlock *t;
					t = CPUs[i];
					myPriority_Queue.push(*t);
					cout << "Removing thread " << t->tid << " from CPU " << i << "\n";
					
					t = new ThreadDescriptorBlock(myPriority_Queue.top());
					cout << "Adding thread " << t->tid << " to CPU " << i << "\n";
					CPUs[i] = t;
					myPriority_Queue.pop();
				}
			}

			break;
		case PBS:		//Priority Based Scheduling, with preemption

			// Implemented most quickly with priority queue (heap).
			// w/ preemption means if a new process with higher priority is 
			//	inserted into the queue it is run immediately. 

			// USE myPriorityQueue

			for (int i = 0; i < num_cpu; ++i) {
				if (myPriority_Queue.empty())
					continue;
				if (CPUs[i] == NULL) {
					cout << "Adding thread " << myPriority_Queue.top().tid << " to CPU " << i << "\n";
					CPUs[i] = new ThreadDescriptorBlock(myPriority_Queue.top());
					myPriority_Queue.pop();
				}
				else if (CPUs[i]->priority > myPriority_Queue.top().priority) {
					ThreadDescriptorBlock *t;
					t = CPUs[i];
					myPriority_Queue.push(*t);
					cout << "Removing thread " << t->tid << " from CPU " << i << "\n";

					t = new ThreadDescriptorBlock(myPriority_Queue.top());
					cout << "Adding thread " << t->tid << " to CPU " << i << "\n";
					CPUs[i] = t;
					myPriority_Queue.pop();
				}
			}

			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}
	return true;
}