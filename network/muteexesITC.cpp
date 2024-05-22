/* 在此示例中，我们将创建两个线程：生产者（Producer）和消费者（Consumer）。生产者将数据放入一个共享缓冲区，
而消费者则从中读取数据。我们将使用互斥锁来保护对共享数据的访问，并使用条件变量来协调生产者和消费者之间的活动。 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;
mutex mtx;  // muteexe, protect sharing data
condition_variable cv; // conditional var, coordinate producer and consumer
bool ready = false; // signal, indicating whether data is ready
vector<int> shared_data;  // sharing data

// producer
void producer() {
    unique_lock<mutex> lck(mtx);
    // producing some data
    for (int i = 0; i < 20; i++) {
        shared_data.push_back(i);
    }
    ready = true;  // indicating data is ready
    cv.notify_one(); // inform consumer
}

// consumer
void consumer() {
    unique_lock<mutex> lck(mtx);
    // waiting for data ready
    /*cv：一个std::condition_variable对象，用于在不同线程之间同步特定条件的变化。
    .wait()：是std::condition_variable的成员函数，它使当前线程等待一个特定条件成立。这个函数需要传递一个已锁定的std::unique_lock<std::mutex>对象作为参数。
    lck：一个std::unique_lock<std::mutex>对象，它管理一个互斥量（mutex）的锁。在cv.wait()调用期间，lck内部管理的互斥量会被自动解锁，允许其他线程获取该互斥量并修改条件。当条件变量被通知（通过cv.notify_one()或cv.notify_all()），并且等待的条件为真时，或者发生虚假唤醒时，线程被唤醒并重新锁定互斥量。
    []{return ready;}：一个lambda表达式，用作谓词（predicate），指定了wait()函数等待的条件。在这个例子中，它等待ready变量变为true。wait()函数将反复检查这个条件，如果条件为false，当前线程将继续等待。当条件为true时，wait()操作结束，线程继续执行。*/
    cv.wait(lck, []{return ready;});
    for (int n : shared_data) {
        cout << "Consumed: " << n << endl;
    }
}

int main() {
    thread producer_thread(producer);
    thread consumer_thread(consumer);
    producer_thread.join();
    consumer_thread.join();

    return 0;
}
/*
在C++中，std::unique_lock是一个模板类，用于提供对互斥量（mutex）的所有权管理，允许更灵活的锁定和解锁操作。
与std::lock_guard相比，std::unique_lock提供了更多的控制和功能，
例如可以在生命周期内多次锁定和解锁，还可以将锁的所有权从一个unique_lock对象转移到另一个。*/