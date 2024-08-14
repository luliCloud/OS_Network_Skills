#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <mutex> // for unique lock
using namespace std;

shared_mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    shared_lock<shared_mutex> lock(rw_mutex);
    cout << "Reader " << id << " read value: " << shared_data << endl;
}

void writer(int id) {
    unique_lock<shared_mutex> lock(rw_mutex);
    shared_data = id;
    cout << "Writer " << id << " wrote value: " << shared_data << endl;
}
/** 写操作会等待读操作完成，如果有多个读操作几乎同时持有，则全部读完在开始写操作。写操作则会占有控制权，知道写完读操作才能读取 */
int main() {
    vector<thread> threads;
    // 创建多个读线程
    for (int i = 0; i < 3; ++i) {
        threads.push_back(std::thread(reader, i));
    }

    // 创建写线程
    threads.push_back(std::thread(writer, 100));

    // 创建更多读线程
    for (int i = 3; i < 6; ++i) {
        threads.push_back(std::thread(reader, i));
    }
    
    // wait for all thread finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
/**
 * Reader 0 read value: 0
 * Reader 1 read value: 0
Reader 2 read value: 0
Writer 100 wrote value: 100
Reader 3 read value: 100
Reader 4 read value: 100
Reader 5 read value: 100
 */