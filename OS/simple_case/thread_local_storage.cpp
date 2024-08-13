#include <iostream>
#include <thread>
using namespace std;

thread_local int localVar = 0; // noting still have data type

void threadFunction(int id) {
    localVar = id;
    cout << "Thread " << id << " has localVar " << localVar << endl;
}

int main() {
    thread t1(threadFunction, 1);
    thread t2(threadFunction, 2);

    t1.join();
    t2.join();

    return 0;
}
/**
 * Thread 1 has localVar 1
Thread 2 has localVar 2
 */