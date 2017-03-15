///////////////////////////////////
// File: FixPreemption.cpp
// Author: Ryan Bury

#include "FixPreemption.h"

/*
This fix enforces the rule that if another resource cannot be immediately allocated by a thread
	it releases all currently held resources and tries again to lock all necessary 
	resources, thus removing deadlock. 
*/

using namespace std;

mutex mtx3;
mutex m3A;
mutex m3B;

void protected_print3(string str) {
	mtx3.lock();
	cout << str;
	this_thread::sleep_for(0.5s);
	mtx3.unlock();
}

// Relies on mB then mA
void fun3A(int tid) {
	m3A.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex A\n";
	protected_print3(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex B\n";
	protected_print3(str);
	if (!m3B.try_lock()) {
		m3A.unlock();
		
		lock(m3A, m3B);
	}

	m3A.unlock();
	m3B.unlock();
}

// Relies on mA then mB
void fun3B(int tid) {
	m3B.lock();
	string str = "Thread " + to_string(tid) + " acquired mutex B\n";
	protected_print3(str);

	str = "Thread " + to_string(tid) + " trying to acquire mutex A\n";
	protected_print3(str);
	if (!m3A.try_lock()) {
		m3B.unlock();
		
		lock(m3A, m3B);
	}

	m3B.unlock();
	m3A.unlock();
}