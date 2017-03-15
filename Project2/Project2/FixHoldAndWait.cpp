///////////////////////////////////
// File: FixHoldAndWait.cpp
// Author: Ryan Bury

#include "FixHoldAndWait.h"

/*
By Guaranteeing that the thread acquires both locks at the same time before execution
	we remove the Hold and Wait issue. 
	Use std::lock function to ensure the thread gains both locks simultaneously before execution
*/

using namespace std;

mutex mtx2;
mutex m2A;
mutex m2B;

void protected_print2(string str) {
	mtx2.lock();
	cout << str;
	this_thread::sleep_for(0.5s);
	mtx2.unlock();
}

// Relies on mB then mA
void fun2A(int tid) {

	lock(m2A, m2B);

	string str = "Thread " + to_string(tid) + " acquired mutex A and B\n";
	protected_print2(str);

	m2A.unlock();
	m2B.unlock();
}

// Relies on mA then mB
void fun2B(int tid) {

	lock(m2A, m2B);

	string str = "Thread " + to_string(tid) + " acquired mutex A and B\n";
	protected_print2(str);

	m2A.unlock();
	m2B.unlock();
}