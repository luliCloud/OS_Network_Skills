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
/**
 * noting: need to compile using linker:
 * g++ ignoreError.cpp -ltcmalloc
*/
int main() {
    // try to allocate large amount of memory space
    /**
     * 为什么这里分配了系统一半的资源：
     * size_t 是一个无符号整数类型，专门用于表示对象的大小和数组的索引。在大多数系统上，它通常与
     * 机器的字长一致，即64位系统上64位，32位系统上为32位
     * size_t(-1)代表一个无符号整数类型的最大值。这是因为当我们将-1转换为无符号整数时，它会变成
     * 所有位都为1的最大值。
     * 在64位系统，它等于2^64 -1; 32-digit system: 2^32 - 1
     * 如果将它除以2，我们得到了系统地址空间的中间点。
    */
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
/**
 * 在上面的代码中，我们尝试分配大概一半系统内存。如果tc_malloc分配失败，我们知道内存分配失败了，
 * 并且应该采取适当的错误处理措施。在这个例子中，我们简单的打印了一条错误消息并返回了一个非0退出码。
 * 在实际应用中，我们可能需要执行更复杂的错误处理逻辑。
 * 应该注意的是，TCmalloc提供了配置选项来定制当内存失败时的行为。比如，我们可以通过设置环境变量
 * TCMALLOC_NEW_MODE来改变new操作符在内存分配失败时的行为。但是，直接在代码中检查tc_malloc的返回值
 * 仍然是最直接和可控的方式来处理内存失败的情况。
*/
