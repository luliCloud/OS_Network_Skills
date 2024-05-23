/**
 * 未考虑线程安全性，虽然TCMalloc是线程安全的，但是在多线程环境中，如果不当的share或者pass
 * TCMalloc分配的内存指针，可能会导致数据竞争或者其他安全问题。
 * 以下是C++代码实例，展示在多线程环境中不当的共享由TCMalloc分配的内存指针可能导致的问题
*/
#include <iostream>
#include <thread>
#include <vector>
#include <gperftools/tcmalloc.h>
#include <mutex>
using namespace std;

// 共享的全局内存指针
void* shared_ptr = nullptr;
// 用于保护共享指针的互斥锁
mutex mtx;

/**
 * 在互斥锁锁定的情况下，线程可以安全地分配内存并将其指针赋值给 shared_ptr。
 * 因为互斥锁保证了同一时刻只有一个线程能够进入这段代码，因此多个线程不会同时修改 shared_ptr。
*/
void thread_function(int id) {
    // 锁定互斥锁，以确保安全的访问共享指针
    // 使用lock_gurad 自动管理锁。lock对象在作用域结束时自动解锁。无需unlock
    lock_guard<mutex> lock(mtx);

    // 假设这里使用TCMalloc分配内存，并将其赋给共享指针
    shared_ptr = tc_malloc(100);
    if (shared_ptr == nullptr) {
        cerr << "Memory allocation failed in thread" << id << "!" << endl;
        return;
    }

    // 在这里对共享内存进行一些操作

    // 解锁后，其他线程可能会访问并修改共享指针。注意，离开作用域时会自动解锁
}

int main() {
    // 创建多个线程，它们都尝试访问和修改共享指针
    vector<thread> threads;
    /**
     * 当一个 std::shared_ptr 指向新的内存空间时，如果它之前指向的内存空间没有其他 
     * std::shared_ptr 实例指向它，那么之前的内存空间将被释放。这是因为 std::shared_ptr 
     * 使用引用计数来管理所指向的对象，当引用计数变为零时，std::shared_ptr 会自动删除（释放）该对象。
     * 但是注意这里并不是智能指针，而是一个普通的void*，所以它之前指向的位置并没有自动释放掉
    */
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(thread_function, i); // thread 1，2，3.。。依次访问该函数
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 在所有线程完成后，释放共享内存
    lock_guard<mutex> lock(mtx);
    if (shared_ptr != nullptr) {
        tc_free(shared_ptr);
        shared_ptr = nullptr;
    }

    return 0;
}
/**
 * 在这个例子中，我们有一个全局的共享内存指针，他被多个线程访问和修改。
 * 我们使用了一个mutex来保护对这个指针的访问，以确保线程安全（在一个threadf访问thread_function
 * 并使用shared_ptr时，其他thread无法获取这个锁，对该程序进行访问/使用该shared ptr）。然而，
 * 即使我们使用了互斥锁，仍然存在潜在问题
 * 1. 数据竞争：如果其他部分的代码在没有正确锁定互斥锁的情况下访问或修改shared_ptr，
 * 比如另一段代码并没有锁定mutex，但有多个thread可以访问这段代码， 会导致数据竞争。
 * 2. 多次释放：如果某个线程在没有检查指针是否已经被释放的情况下尝试释放它，就会导致双重释放，通常
 * 导致程序崩溃
 * 3. 内存泄漏：如果某个线程在分配内存后崩溃，或者由于其他原因未能释放内存，会导致内存泄漏。所以这里
 * 更好的策略是使用智能指针：shared_ptr<void> shared_ptr = nullptr;
 * 为了避免这些问题，你应该：
 * 1. 确保在访问共享资源时总是使用适当的同步机制，比如互斥锁
 * 2. 避免在多个线程之间传递原始指针，如果必须这样做，确保传递的是智能指针，它们能够自动管理内存的生命周期
 * 3. 在释放内存之前，总是检查指针是否非空，并确保它不会多次释放
 * 4. 尽量减少在多线程环境中共享状态的需要。如果可能的话，使用线程局部存储或其他无锁技术来避免
 * 同步开销或潜在的线程安全问题。
*/