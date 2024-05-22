/**
 * 忽视错误处理，当使用TCMalloc进行内存分配时，如果系统内存不足，分配可能失败，忽视这种错误
 * 不进行适当处理，可能导致程序崩溃或者不可预知的行为。以下的C++代码例子
 * 
 * TCMalloc是Google开发的一个高性能多线程内存分配器，通常与glibc的malloc行为类似
 * 即当内存分配失败时（通常由内存不足引起），默认行为是调用abort()函数使程序崩溃。但
 * TC malloc也提供一些配置选择和API来允许更精细的错误处理。
 * 以下是一个简单的C++代码，演示如何在TCMalloc中处理内存分配失败的情况：
 * 
*/
#include <iostream>
#include <gperftools/tcmalloc.h>
using namespace std;

int main() {
    // try to allocate large amount of memory space
    size_t large_size = size_t(-1) / 2; // allocate about half of system memory space
    void* ptr = tc_malloc(large_size);

    if (ptr == nullptr) {
        // allocate failed
        cerr << "Memory allocation failed, cannot acquired." << endl;
        /* 在这里，你可以选择错误处理，比如释放其他资源，记录错误日志，或者尝试其他恢复策略 
           然后 优雅的退出程序，而不是让程序崩溃 */
        return -1;
    }

    // if allcoate succeeded, continue other operations
    // ...
    // don't forget to release space
    tc_free(ptr);

    return 0;
}
