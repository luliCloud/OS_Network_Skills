/** we need to use C++20 standard or higher to support semaphore 
 * remember to change the setting in tasks.json. add 
 * "-std=c++20", before "-g"
*/
/** this is for ITC */
#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>

using namespace std;

/*create a counting semaphore, allowing max 2 threads visit 
at same time. So semaphore count should be 2 */ 
counting_semaphore semaphore(2);

void worker(int id) {
    // waiting for semaphore count
    /* 当一个线程成功地从信号量中"获取"（acquire）一个单位时，信号量的计数会减少。
    如果信号量的计数已经是0 （acquire之前），那么尝试获取信号量的线程将会阻塞，直到信号量的计数再次
    变为大于0（这通常是因为另一个线程释放（release）了信号量）。*/
    semaphore.acquire();

    // execute the action procted from semaphore, not blocked now if semaphore >= 0
    cout << "Worker " << id << " is working..." << endl;
    // this_thread: namespace of this thread. 
    // this one mimic the execute of this thread for 1 sec
    this_thread::sleep_for(chrono::seconds(1)); // sleep for 1 second

    // release the signal: after this thread finish task, should release CPU source
    cout << "release worker " << id << endl; 
    semaphore.release();
}

int main() {
    vector<thread> threads;


    for (int i = 0; i < 5; i++) {
        /* basic constructor of thread:
        template <class Function, class... Args>
        explicit thread(Functions&& f, Args&&... args) -> all args will be transferred to f
        emplace_back allows to create a obj in side of the (). so here we call 
        thread constructor and pass two arg to it */
        threads.emplace_back(worker, i);
    }

    /* ensure main process (int main) blocked until all threads finish their work*/
    for (auto& t : threads) {
        t.join();  // thread.join() is make main process wait this thread finish
    }
    return 0;
}

/* similar output:
Worker 0 is working...
Worker 1 is working...
release worker 0
release worker 1
Worker Worker 4 is working...
2 is working...
release worker 4
release worker 2
Worker 3 is working...
release worker 3
*/