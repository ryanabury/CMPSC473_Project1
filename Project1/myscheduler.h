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
class MyThread {
public:
	MyThread(int a, int r, int p, int t) {
		this->arriving_time = a;
		this->remaining_time = r;
		this->priority = p;
		this->tid = t;
	}

	void update_remaining_time(int r) {
		this->remaining_time = r;
	}

	friend bool operator<(const MyThread& lhs, const MyThread& rhs) {
		return lhs.priority < rhs.priority;
	}
private:
	int arriving_time, remaining_time, priority, tid;
};

class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {
		create_DataStructure();
	}
	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure

	//Declare additional methods(s) below if needed.
	void create_DataStructure() {

	}
};