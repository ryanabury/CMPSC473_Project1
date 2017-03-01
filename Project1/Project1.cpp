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
	MyScheduler ms = MyScheduler(Policy::STRFwP, 1);
	ms.CreateThread(0, 1, 0, 00);
	ms.CreateThread(0, 128, 0, 07);
	ms.CreateThread(0, 2, 0, 01);
	ms.CreateThread(0, 4, 0, 02);
	ms.CreateThread(0, 64, 0, 06);
	ms.CreateThread(0, 8, 0, 03);
	ms.CreateThread(0, 16, 0, 04);
	ms.CreateThread(0, 32, 0, 05);		

	ms.Go();
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
