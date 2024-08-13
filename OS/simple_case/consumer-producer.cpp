#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
using namespace std;

mutex mtx;
condition_variable cv;
queue<int> dataQueue;
bool done = false;

void producer(int id) {
    for (int i = 0; i < 5; i++) {
        this_thread::sleep_for(chrono::microseconds(100)); // mimic production
        unique_lock<mutex> lock(mtx);
        dataQueue.push(i);  // push data in queue
        cout << "Producer " << id << " produced " << i << endl;
        cv.notify_one();  
    }
    unique_lock<mutex> lock(mtx);
    done = true;
    cv.notify_all();
}
/** 在生产者-消费者模式中，notify_all() 在生产结束时非常重要，尤其是在有多个消费者线程的情况下。
1. 多个消费者线程的情况
当我们有多个消费者线程时，假设有以下情况：
生产者线程：已经生产完所有数据，并且设置了 done = true。
消费者线程：有可能有一些消费者线程正在等待条件变量，即使队列已经为空。
在这种情况下，如果我们只使用 notify_one()，那么只能唤醒一个等待的消费者线程。
这个消费者线程会检查队列是否为空，如果为空且 done = true，它会退出。
但其他正在等待的消费者线程可能会继续等待，永远不会被唤醒，因为队列已经为空，而生产者已经结束。 

所以done是用于在唤醒所有线程时，即时队列为空都可以退出的一个条件

被唤醒（notify）的线程在被唤醒后不会立即执行它后面的代码，而是首先重新获得互斥锁，并再次检查条件是否满足。
只有在条件满足的情况下，线程才会继续执行，否则它会再次进入等待状态。*/

void consumer(int id) {
    while (true) {  // event loop, keep detection
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !dataQueue.empty() || done; });
        if (!dataQueue.empty()) {
            // still have task
            int val = dataQueue.front();
            cout << "Consumer "<< id << " consumed " << val << endl;
            dataQueue.pop();
        } else if (done) { // dataQueue is empty and all producer finished 
        // 注意done要写在后面。否则及时queue不为空，done为true时也会直接break，那么有些数据就没读完
            break;
        }
    }
}

int main() {
    thread producer1(producer, 1);
    thread producer2(producer, 2);
    thread consumer1(consumer, 1);
    thread consumer2(consumer, 2);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    return 0;
}
/**
 * Producer 1 produced 0
Consumer 1 consumed 0
Producer 2 produced 0
Consumer 2 consumed 0
Producer 1 produced 1
Consumer 1 consumed 1
Producer 2 produced 1
Consumer 2 consumed 1
Producer 1 produced 2
Consumer 1 consumed 2
Producer 2 produced 2
Consumer 2 consumed 2
Producer 1 produced 3
Consumer 1 consumed 3
Producer 2 produced 3
Consumer 2 consumed 3
Producer 1 produced 4
Consumer 1 consumed 4
Producer 2 produced 4
 */