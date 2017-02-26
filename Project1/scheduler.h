#pragma once

//schedule.h

////////////////////////////////////////////////////
/*This file should not be modified by the students*/
////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
using namespace std;


/* Thread Structure, to be used to create thread obects
which will be processed by the scheduler. Students should 
use their own data structure to store threads whic should
be defined in 'myschedule.h'.*/
struct ThreadDescriptorBlock {
	int tid;
	int remaining_time;
	int arriving_time;
	int priority;
};

enum Policy {
	FCFS,		//First Come First Serve
	STRFwoP,	//Shortest Time Remaining First, without preemption
	STRFwP,		//Shortest Time Remaining First, with preemption
	PBS			//Priority Based Scheduling, with preemption
};

/*The 'schedule' class is an abstract class which will be
extended by 'myschedule' class in 'myschedule.h'. 
Please note, the minimum number of CPUs allowed is 2.
*/
class Scheduler{
public:
	Scheduler(Policy p, unsigned int n) : policy(p), num_cpu(n){
		timer = 0;
		assert(n >= 1);

		CPUs = new ThreadDescriptorBlock*[n]();
	}

	void Go() //This function initializes the scheduling process once all the threads are created.
	{
		while(Dispatch())
		{
			++timer;
			for(unsigned int i = 0; i < num_cpu; ++i)
			{
				if(CPUs[i] != NULL)
					--CPUs[i]->remaining_time;

				if (CPUs[i]->remaining_time == 0) //Prints Thread ID, Finishing Time and Processor Number if a thread has finished executing
					{
						cout << "Thread ID : " << CPUs[i]->tid << " Finishing Time : " << timer << " CPU No. : " << i <<'\n';
						CPUs[i] = NULL;
					}
			}	
		}
		cout << "All the Threads have been executed !! .. Exiting Scheduler ..\n";
		system("pause");
	}

	///Dispatch schedules the next thread to execute based on scheduler policy and current work load
	virtual bool Dispatch() = 0; 

	///Method to create a new thread with initial conditions as defined.
	///all threads must be called before the test bench invokes the Go() method to start simulation of the scheduler.
	virtual void CreateThread(int arriving_time, int remaining_time, int priority, int tid) = 0; 

protected:
	const Policy policy; //To denote the scheduling policy

private:
	unsigned int num_cpu; //To denote number of processors
	ThreadDescriptorBlock **CPUs; //Pointer array to let processors access the threads
	int timer; //Global Timer for all the processors, single increment in timer equals one cpu cycle.

};