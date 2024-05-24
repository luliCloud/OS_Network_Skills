/**
 * 不恰当的配置，TCMalloc有一些可配置的选项，如内存也大小，缓存大小等。不恰当的配置可能导致新能
 * 下降或者资源浪费。
*/
#include <iostream>
#include <gperftools/tcmalloc.h>
using namespace std;

// suppose we have a funciton, depending on the performance of memory allocation
void memoryIntensiveFunction() {
    // execute some operations need big amounts of memory allocation...
}

int main() {
    // initializa TCMalloc and set inappropriate config.
    // e.g., seeting a big size of cache, may waste of system source.
    const size_t largeCacheSize = 1024 * 1024 * 102;  // 1GB cache
    if (!tcmalloc::MallocExtension::SetCacheSize(largeCacheSize)) {
        // noting this is a pseudo code, that tcmalloc is a fake class.
        // we assume that we have this class and realize MallocExtension class
        // this is to set a cache with given class
        cerr << "Fail to set cache size!" << endl;
        return 1;
    }
    // setting a large memory page, is highly possible that not every app needs
    const size_t largePageSize = 4 * 1024 * 1024; // 4 MB page
    if (!tcmalloc::MallocExtension::SetSystemPageSize(largePageSize)) {
        cerr << "Failed to set system page size!" << endl;
        return 1;
    } 

    // execute memory intensive function
    memoryIntensiveFunction();

    // other code

    return 0;
}
/**
 * 在这个例子中，我们尝试通过SetCacheSize和SetSystempageSize函数来射者TCmalloc的缓存大小和
 * 内存页大小。然而，这些值被设置的非常大，可能并不适合所有的应用程序。过大的缓存大小可能会导致系统
 * 资源的浪费，尤其在内存有限的环境中。同样，设置过大的page大小可能并不总是能提高性能，相反kennel
 * 增加内存碎片，降低缓存利用率。或者在某些情况下甚至导致性能下降。
 * 为了避免不恰当的config，我们应该“
 * 1. 在调整任何配置选项之前，先了解它们的作用和潜在影响。
 * 2. 根据应用程序的实际需求和性能特点来选择合适的配置值。
 * 3. 使用性能分析工具来评估不同配置选项对应用程序性能的影响。
 * 4. 查阅TCmalloc的官方文档和相关资源，以获取关于配置选项的更多讯息和最佳时间建议。
 * 5. 对于大多数app来说，使用tcmalloc的默认配置通常是一个安全且合理的选择。只有在
 * 确实需要优化新能，并且已经通过性能分析确定了具体的瓶颈时，才应该考虑调整配置选项。
*/