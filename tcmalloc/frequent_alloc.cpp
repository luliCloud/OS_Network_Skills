/**
 * 频繁申请和释放小块内存：虽然TCMalloc在处理小块内存分配时非常高效，但是如果程序中频繁申请和释放
 * 极小的内存块，仍可能导致内存碎片和性能下降。这是因为每次分配和释放都会涉及到一定的管理开销，
 * 并且过多的碎片可能导致内存利用率下降，进而影响性能。
 * 以下是C++ example，展示频繁申请和释放小块内存可能导致的问题。
*/
#include <iostream>
#include <gperftools/tcmalloc.h>
#include <vector>
#include <stack>
#include <memory>
using namespace std;

/** MyObj and ObjPool is for Object Pooling */
class MyObj {
public:
    MyObj() { cout << "MyObj created." << endl; }
    ~MyObj() { cout << "MyObj destryoed." << endl; }
    void reset() { cout << "MyObj reset" << endl; }
};

/* this is to manage the MyObj */
class ObjPool {
public:
    shared_ptr<MyObj> acquire() {
        if (pool.empty()) {
            // if pool is empty, create a new obj
            return shared_ptr<MyObj>(new MyObj(), [this](MyObj* p) {
                release(p);
            });
        } else {
            auto obj = move(pool.top()); // cause are all unique_ptr, can only move
            pool.pop();
            // release函数会让unique ptr释放它对该空间的所有权，让这块空间可以被shared ptr持有
            return shared_ptr<MyObj>(obj.release(), [this](MyObj* p) {
                release(p);
            });
        }
    }

    ~ObjPool() {
        while (!pool.empty()) {
            pool.pop();  // unique_ptr destructor will auto relase the obj created 
            // by new or make_shared key word (using its own destructor).
            // however, if the MyObj has its 'new' members, then it needs to have 
            // correct destructor to release these 'new' member inside class 
        }
    }

    void release(MyObj* obj) {
        obj->reset();
        pool.push(unique_ptr<MyObj>(obj));
    }
private:
    stack<unique_ptr<MyObj>> pool;
};

int main() {
    // suppose there is a loop in the program, the program will apply and release space
    // in every ieteration. 
    for (int i = 0; i < 1000000; i++) {
        // apply for space about 100 bytes
        void* ptr = tc_malloc(100);
        if (ptr == nullptr) {
            cerr << "Memeory allocation failed." << endl;
            return 1;
        }
        // if there are some operations on the memory 

        // release space
        tc_free(ptr);
    }

    /** this is for object pool */
    ObjPool pool;
    {
        auto obj1 = pool.acquire();
    }
    // obj1 离开作用域，自动返回池中
    {
        auto obj2 = pool.acquire();
    }
    
    // when two objects is used up, they will not be return to memory but return
    // back to the pool. When the whole main function finish, the pool will be destroyed
    // automatically. 

    cout << "All memory blocks have been allocated and freed." << endl;

    return 0;
}
/**
 * 在上面的代码中，我们有一个包含一百万次迭代的循环。在每次迭代中，我们都申请100bytes的内存，
 * 然后立即释放它。尽管TCmalloc对小块内存进行了优化，但如此频繁的申请和释放操作仍然可能导致性能问题，
 * 尤其在高并发或内存压力较大的环境下。
 * 为了缓解这个问题，可以考虑以下几种策略
 * 1. 合并小块内存申请。如果可能的话，尝试合并多个小块内存申请位一个较大的内存块申请，并在内部进行管理
 * 2. 对象池（object pooling）：对于频繁申请和释放的同类型对象，可以用对象池来盂县分配并缓存一定数量的
 * 对象。减少内存分配和释放的次数。
 * 3. 减少临时变量，尽量避免在循环或函数中创建大量临时变量，减少内存分配的需求
 * 4. 延迟释放：如果可能，考虑延迟释放不再使用的内存块（比如对象池或者空闲列表），
 * 可以等到达到一定大小再一起释放，减少内存碎片和分配/释放的频率。
 * 5. 使用智能指针，自动管理内存的生命周期，减少手动调用delete或者tc_free的机会，避免内存泄漏和错误
 * 
*/