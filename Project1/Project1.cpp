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


int main(int argc, char* argv[])
{

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
