#include <iostream>
#include <thread>
#include <mutex>
#include <string>

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

void call_from_thread(int tid) {
	string str = "Hello, World From thread " + to_string(tid) + "\n";
	protected_print(str);
}

int main() {
	thread t[num_threads];

	t[0] = thread(funA, 0);
	t[1] = thread(funB, 1);

	/*for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread(call_from_thread, i);
	}*/

	protected_print("Hello, world from Main \n");

	/*for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}*/
	t[0].join();
	t[1].join();

	int i;
	cin >> i;

	return 0;
}