#pragma once
//myscheduler.h
/* Students need to define their own data structure to contain
   and access objects from 'thread class'. The 'CreateThread()' 
   function should insert the threads into the student defined
   data structure after creating them.
   They are allowed to add any additional functionality (only 
   declaration in this file, define in 'myschedule.cpp')
   which they might find helpful.*/

#include "scheduler.h"
#include <queue>
#include <vector>

//Define your data structure here.

class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {}
	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure

	//Declare additional methods(s) below if needed.

	friend bool operator<(const ThreadDescriptorBlock& lhs, const ThreadDescriptorBlock& rhs) {
		switch (policy) {
		case FCFS:
			break;

		case STRFwoP: case STRFwP: case PBS:

			break;

		default:
			cout << "ERROR: Invallid policy";
			throw 0;
		}
	}


private:
	// Use in STRFwoP, STRFwP, PBS
	std::priority_queue<MyThread> myPriority_Queue;

	// Use in FCFS
	std::queue<MyThread> myQueue;

};