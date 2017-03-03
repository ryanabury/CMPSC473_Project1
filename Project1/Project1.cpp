/*// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"

int main(int argc, char* argv[])
{
	return 0;
}
*/

// Via Alexandar Devic

#include "myscheduler.h"
#include "stdlib.h" /* this is for rand */
#include "time.h"	/* used to set a more random start and numbers */
#include "vector"	/* used for getting rand vals for TID and Priority*/
#include "iterator" /* used for iterating over the vector */

struct start0 { // used for thread id
	int x;
	int operator()() { return x++; }
	start0() :x(0) {}


};
struct start1 {// used for priority

	int x;
	int operator()() { return x+=1; }
	start1() :x(0) {}

};


int main(int argc, char* argv[])
{
	/*
	cout << "Testbench via Alexandar Devic\n\n";

	cout << "\tUsing FCFS, no priority\n";
	MyScheduler ms = MyScheduler(Policy::FCFS, 4);
	ms.CreateThread(0, 1, 2, 00);
	ms.CreateThread(1, 128, 3, 07);
	ms.CreateThread(31, 2, 5, 01);
	ms.CreateThread(31, 4, 6, 02);
	ms.CreateThread(30, 64, 1, 06);
	ms.CreateThread(31, 8, 7, 03);
	ms.CreateThread(31, 16, 4, 04);
	ms.CreateThread(31, 32, 8, 05);		

	ms.Go();
	// starting the random generator for the test bench
	*/
	//(int arriving_time, int remaining_time, int priority, int tid) this is the parameters for createThread
	srand(time(NULL)); // set a rand seed
	for (int x = 0; x < 1000; x++) // will generate 1000 random test cases for myscheduler
	{
		int type = rand() % 4 + 1; // set the policy
		int nodes = rand() % 1000 + 1; // anywhere near 30 nodes should test must cases
		int AOT = rand() % 100 + 1; // anywhere between 100 and 1 theads should be good priority will use this AOT= amount of threads
		vector<int> tID,priority;
		generate_n(back_inserter(tID), AOT, start0()); // generate an array from 0 to AOT for tID
		generate_n(back_inserter(priority), AOT, start1()); // generate an array from 1 to AOT for priority
		if (type == 1) {
			cout << "Set up in FCFS with " << nodes << " nodes and time of " << AOT<<"\n";
			MyScheduler ms1 = MyScheduler(Policy::FCFS, nodes);
			cout << "START BEGIN FCFS" << endl;
			for (int y = 0; y < AOT; y++)
			{

				int arrive = rand() % 100 + 0; // arrive
				int remaining = rand() % 500 + 1; // remaining time
				int tPlace = rand() % (AOT - y) + 0; // will remove this item after createThread so only one of each in it
				int pPlace = rand() % (AOT - y) + 0;
				cout << "ARRIVE: " << arrive << "; Time Remaining: " << remaining << "; priority: " << priority[pPlace] << "; TID: " << tID[tPlace] << endl;
				ms1.CreateThread(arrive, remaining, tID[tPlace], priority[pPlace]); // create thread
				tID.erase(tID.begin() + tPlace);
				priority.erase(priority.begin() + pPlace); // erease entries so cant be used twice
			}
			cout << "Started with " << AOT << " of threads" << endl;
			ms1.Go();
			cout << "FINISHED on turn: " << x + 1 << endl;
		}
		else if (type == 2) {
				cout << "Set up in STRFwoP with " << nodes << " nodes\n";
				MyScheduler ms1 = MyScheduler(Policy::STRFwoP, nodes);
				cout << "START BEGIN STRFwoP" << endl;
				for (int y = 0; y < AOT; y++)
				{

					int arrive = rand() % 100 + 0; // arrive
					int remaining = rand() % 500 + 1; // remaining time
					int tPlace = rand() % (AOT - y) + 0; // will remove this item after createThread so only one of each in it
					int pPlace = rand() % (AOT - y) + 0;
					cout << "ARRIVE: " << arrive << "; Time Remaining: " << remaining << "; priority: " << priority[pPlace] << "; TID: " << tID[tPlace] << endl;
					ms1.CreateThread(arrive, remaining, tID[tPlace], priority[pPlace]); // create thread
					tID.erase(tID.begin() + tPlace);
					priority.erase(priority.begin() + pPlace); // erease entries so cant be used twice
				}
				cout << "Started with " << AOT << " of threads" << endl;
				ms1.Go();
				cout << "FINISHED on turn: " << x + 1 << endl;
		}
		else if(type==3){
			cout << "Set up in STRFwP with " << nodes << " nodes\n";
			MyScheduler ms1 = MyScheduler(Policy::STRFwP, nodes);
			cout << "START BEGIN STRFwP" << endl;
			for (int y = 0; y < AOT; y++)
			{

				int arrive = rand() % 100 + 0; // arrive
				int remaining = rand() % 500 + 1; // remaining time
				int tPlace = rand() % (AOT - y) + 0; // will remove this item after createThread so only one of each in it
				int pPlace = rand() % (AOT - y) + 0;
				cout << "ARRIVE: " << arrive << "; Time Remaining: " << remaining << "; priority: " << priority[pPlace] << "; TID: " << tID[tPlace] << endl;
				ms1.CreateThread(arrive, remaining, tID[tPlace], priority[pPlace]); // create thread
				tID.erase(tID.begin() + tPlace);
				priority.erase(priority.begin() + pPlace); // erease entries so cant be used twice
			}
			cout << "Started with " << AOT << " of threads" << endl;
			ms1.Go();
			cout << "FINISHED on turn: " << x + 1 << endl;
		}
		else if (type == 4) {
			cout << "Set up in PBS with " << nodes << " nodes\n";
			MyScheduler ms1 = MyScheduler(Policy::PBS, nodes);
			cout << "START BEGIN PBS" << endl;
			for (int y = 0; y < AOT; y++)
			{

				int arrive = rand() % 100 + 0; // arrive
				int remaining = rand() % 500 + 1; // remaining time
				int tPlace = rand() % (AOT - y) + 0; // will remove this item after createThread so only one of each in it
				int pPlace = rand() % (AOT - y) + 0;
				cout << "ARRIVE: " << arrive << "; Time Remaining: " << remaining << "; priority: " << priority[pPlace] << "; TID: " << tID[tPlace] << endl;
				ms1.CreateThread(arrive, remaining, tID[tPlace], priority[pPlace]); // create thread
				tID.erase(tID.begin() + tPlace);
				priority.erase(priority.begin() + pPlace); // erease entries so cant be used twice
			}
			cout << "Started with " << AOT << " of threads" << endl;
			ms1.Go();
			cout << "FINISHED on turn: " << x + 1 << endl;
		}else{
				cout << "Howd this happen\n";
			}

	
	}


	/*Results should be:
	Thread ID : 0 Finishing Time : 1 CPU No. : 1
	Thread ID : 1 Finishing Time : 3 CPU No. : 1
	Thread ID : 2 Finishing Time : 7 CPU No. : 1
	Thread ID : 3 Finishing Time : 15 CPU No. : 1
	Thread ID : 4 Finishing Time : 31 CPU No. : 1
	Thread ID : 5 Finishing Time : 63 CPU No. : 1
	Thread ID : 6 Finishing Time : 127 CPU No. : 1
	Thread ID : 7 Finishing Time : 255 CPU No. : 1
	*/



	return 0;
}
