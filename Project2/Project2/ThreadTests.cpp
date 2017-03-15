///////////////////////////////////
// File: ThreadTests.cpp
// Author: Ryan Bury


#include "ThreadTests.h"
#include "FixMutualExclusion.h"
#include "FixHoldAndWait.h"
#include "FixPreemption.h"
#include "FixCircularWait.h"

//////////////////////////////////////////
// Main Entry Point:                    //
//  - Also used to demonstrate Deadlock //
//////////////////////////////////////////

using namespace std;

static const int num_threads = 10;
mutex mtx;
mutex mA;
mutex mB;

void protected_print(string str) {
	mtx.lock();
	cout << str;
	this_thread::sleep_for(0.5s);
	mtx.unlock();
}

// Relies on mB then mA
void funA(int tid) {
	mA.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex A\n";
	protected_print(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex B\n";
	protected_print(str);
	mB.lock();

	mA.unlock();
	mB.unlock();
}

// Relies on mA then mB
void funB(int tid) {
	mB.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex B\n";
	protected_print(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex A\n";
	protected_print(str);
	mA.lock();

	mB.unlock();
	mA.unlock();
}

int main() {
	int input = 0;
	thread t[num_threads];

	cout << "Select one: " << "\n"
		<< "0. Demonstrate Deadlock" << "\n"
		<< "1. Fix Mutual Exclusion Issue" << "\n"
		<< "2. Fix \"Hold and wait\" Issue" << "\n"
		<< "3. Fix Preemption Issue" << "\n"
		<< "4. Fix Circular Wait Issue" << "\n";
	cin >> input;
	switch (input) {
	case 0: 
		cout << "Demonstrating Deadlock..." << "\n";
		t[0] = thread(funA, 0);
		t[1] = thread(funB, 1);

		protected_print("Hello, world from Main \n");

		t[0].join();
		t[1].join();
		cout << "Successfully rejoined!" << "\n";
		break;
	case 1:
		cout << "Demonstrating Mutual Exclusion Fix..." << "\n";
		t[0] = thread(fun1A, 0);
		t[1] = thread(fun1B, 1);

		protected_print("Hello, world from Main \n");

		t[0].join();
		t[1].join();
		cout << "Successfully rejoined!" << "\n";
		break;
	case 2:
		cout << "Demonstrating Hold And Wait Fix..." << "\n";
		t[0] = thread(fun2A, 0);
		t[1] = thread(fun2B, 1);

		protected_print("Hello, world from Main \n");

		t[0].join();
		t[1].join();
		cout << "Successfully rejoined!" << "\n";
		break;
	case 3:
		cout << "Demonstrating Preemption Fix..." << "\n";
		t[0] = thread(fun3A, 0);
		t[1] = thread(fun3B, 1);

		protected_print("Hello, world from Main \n");

		t[0].join();
		t[1].join();
		cout << "Successfully rejoined!" << "\n";
		break;
	case 4:
		cout << "Demonstrating Circular Wait Fix..." << "\n";
		t[0] = thread(fun4A, 0);
		t[1] = thread(fun4B, 1);

		protected_print("Hello, world from Main \n");

		t[0].join();
		t[1].join();
		cout << "Successfully rejoined!" << "\n";
		break;
	}

	
	cout << "Enter -1 to Exit" << "\n";
	cin >> input;

	return 0;
}