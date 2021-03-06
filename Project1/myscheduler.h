#pragma once
//myscheduler.h
/* Students need to define their own data structure to contain
   and access objects from 'thread class'. The 'CreateThread()' 
   function should insert the threads into the student defined
   data structure after creating them.
   They are allowed to add any additional functionality (only 
   declaration in this file, define in 'myschedule.cpp')
   which they might find helpful.*/

   //////////////////////////////////////////////////
   /* Authors: Ryan Bury, Tyler Bohrer, Sam Barnes */
   //////////////////////////////////////////////////

#include "scheduler.h"
#include <queue>
#include <vector>

//Define your data structure here.
struct OrderByArrivalTime {
	bool operator() (const ThreadDescriptorBlock& lhs, const ThreadDescriptorBlock& rhs) {
		// Uses greater than sign to implement min_heap because reasons
		return lhs.arriving_time > rhs.arriving_time;
	}
};

class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {}
	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure

	//Declare additional methods(s) below if needed.

	friend bool operator<(const ThreadDescriptorBlock& lhs, const ThreadDescriptorBlock& rhs) {
		// Considers priority first (to handle PBS) then considers remaining_time (to handle STRFwP and STRFwoP)
		if (lhs.priority == rhs.priority) {
			// Uses greater than sign to implement min_heap because reasons
			return lhs.remaining_time > rhs.remaining_time;
		}
		else {
			// Uses greater than sign to implement min_heap because reasons
			return lhs.priority > rhs.priority;
		}
	}


private:
	// Use in STRFwoP, STRFwP, PBS
	std::priority_queue<ThreadDescriptorBlock> myPriority_Queue;

	// Use in FCFS
	std::queue<ThreadDescriptorBlock> myQueue;

	// Used in implementing "arrival_time" feature
	std::priority_queue<ThreadDescriptorBlock, vector<ThreadDescriptorBlock>, OrderByArrivalTime> notReadyQueue;

};