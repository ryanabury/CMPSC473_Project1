///////////////////////////////////
// File: FixMutualExclusion.cpp
// Author: Ryan Bury

/*
By relying on separate mutexes, this fix allows both functions to access
	the shared "protected_print1" function
*/

#include "FixMutualExclusion.h"

using namespace std;

mutex mtx1;
mutex m1A;
mutex m1B;

void protected_print1(string str) {
	mtx1.lock();
	cout << str;
	this_thread::sleep_for(0.5s);
	mtx1.unlock();
}

// Relies on mA
void fun1A(int tid) {
	m1A.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex A\n";
	protected_print1(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex B\n";
	protected_print1(str);
	//m1B.lock();

	m1A.unlock();
	//m1B.unlock();
}

// Relies on mB
void fun1B(int tid) {
	m1B.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex B\n";
	protected_print1(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex A\n";
	protected_print1(str);
	//m1A.lock();

	m1B.unlock();
	//m1A.unlock();
}