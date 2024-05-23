/**
 * 不匹配的内存管理函数：混用tc_malloc和其他内存管理库（比如标准库的malloc和free）的内存分配
 * 和释放函数，导致内存管理混乱，内存泄漏，或其他未定义行为。
 * 因为不同的内存管理库可能使用不同的内存管理策略和数据结构，混用它们可能会导致内存块被错误的追踪或释放
 * 以下是C++代码例子，展示了混用TCmalloc和标准库malloc/free可能导致的问题
*/
#include <iostream>
#include <gperftools/tcmalloc.h>
#include <cstdlib>  // for malloc and free
using namespace std;

int main() {
    // using TCmalloc allocate memory
    void* ptr_tc = tc_malloc(100);
    if (ptr_tc == nullptr) {
        cerr << "Memory allocation failed using tc_malloc." << endl;
        return 1;
    }

    // try to used standard lib free to release the TCMalloc allocated memeory
    // this is the wrong way, may lead to memory leak or other undefined behavior
    free(ptr_tc);  // wrong, please use tc_free to release teh TCMalloc aollcoated memeory


    // using standard lib to allocate memory
    void* ptr_malloc = malloc(100);
    if (ptr_malloc == nullptr) {
        cerr << "Memeory allocation failed using malloc" << endl;
        return 1;
    }

    // try to use TCMalloc tc_free to release the memory allocated by malloc
    // this is wrong way, lead to lead or undefined behavior
    tc_free(ptr_malloc);
    return 0;
}
/**
 * 首先，这个代码是可以编译通过的，但请不要运行
 * 在上面的代码中，我们错误的mix不同的内存管理库来申请和释放同一块内存。
 * 为了避免这类问题，确保对于使用TCMalloc分配的内存，只使用TCMalloc提供的释放函数。标准库分配的
 * 内存也类似。此外，如果你的程序使用了TCMalloc，最好完全避免使用吧靠准哭的内存管理函数，以保持
 * 内存管理的一致性。
 * 可以在同一个程序中同时使用 tc_malloc/tc_free 和 new/delete，但必须确保分配和释放的配对正确。
*/