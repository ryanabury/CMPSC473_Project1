///////////////////////////////////
// File: FixCircularWait.cpp
// Author: Ryan Bury

#include "FixCircularWait.h"

/*
By re-ordering the mutexes we can ensure a resource ordering of increasing numeration, 
	in this case A then B
*/

using namespace std;

mutex mtx4;
mutex m4A;
mutex m4B;

void protected_print4(string str) {
	mtx4.lock();
	cout << str;
	this_thread::sleep_for(0.5s);
	mtx4.unlock();
}

// Relies on mB then mA
void fun4A(int tid) {
	m4A.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex A\n";
	protected_print4(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex B\n";
	protected_print4(str);
	m4B.lock();

	m4B.unlock();
	m4A.unlock();
}

// Relies on mA then mB
void fun4B(int tid) {
	m4A.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex A\n";
	protected_print4(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex B\n";
	protected_print4(str);
	m4B.lock();

	m4B.unlock();
	m4A.unlock();
}