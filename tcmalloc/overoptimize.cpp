/**
 * 过度优化：在没有明确性能瓶颈的情况下，过度使用TCMalloc的特定功能或过度优化内存分配策略，
 * 可能会导致代码复杂性增加，而性能提升并不明显。
 * 过度优化是一个常见的编程陷阱，它发生在发开者没有明确性能瓶颈的情况下，尝试通过复杂的优化手段
 * 来提升程序的性能，这样做通常会增加代码的复杂性，并可能导致难以维护和理解问题，而且性能提升
 * 往往并不明显。
 * 在C++中，使用特定的内存分配器（比如TCMalloc）来进行内存管理是一种常见的优化手段。然而，
 * 如果没有明确的性能需求或瓶颈， 过度依赖TCmalloc的特定功能可能会导致不必要的复杂性。
 * 下面是一个例子，展示了如何过度优化内存分配，在即使没有明显性能瓶颈的情况下：
 * 
*/
#include <iostream>
#include <vector>
#include <gperftools/tcmalloc.h>
#include <gperftools/malloc_extension.h>
using namespace std;

// suppose we have a simple class
class MyData {
public:
    MyData(size_t size) : data(new char[size]) {}
    ~MyData() { delete[] data; }
    char* getData() const { return data; }
private:
    char* data;
};

// over-optimization, using TCMalloc specific function to allcoate memory
MyData* overOptimizedAllocate(size_t size) {
    // using TCmalloc to allcoate memory
    void* raw_memory = tc_memalign(size, 64);  // size 是分配的内存大小，64是对其要求
    if (raw_memory == nullptr) {
        cerr << "Memory allcoation failed!" << endl;
        return nullptr;
    }
    /**
     * 使用 new (raw_memory) MyData(size); 
     * 这种方法实际上是在指定的内存位置构造对象，这种技术称为 定位 new（placement new）。
     * 你需要为定位 new 提供一个指向已分配内存的指针，new 操作符会在这个内存位置上调用对象的构造函数。
    */
    return new (raw_memory) MyData(size);  // 注意在预先分配好的内存上create 新对象后
    //在释放这块内存时，需要显式调用destructor来释放申请到的空间。因为obj的内部还有申请的内存
    // free 或者 tcfree 并不知道这一类内存的存在，所以不会在释放时管理它
}

int main() {
    // 创建一个大的数据数组
    vector<MyData*> dataArray;
    const size_t numItems = 10000;
    const size_t itemSize = 1024;  // suppose every data size is 1KB

    // 使用过度优化的函数来分配内存
    for (size_t i = 0; i < numItems; i++) {
        dataArray.push_back(overOptimizedAllocate(itemSize));
    }

    // 使用数据

    // 释放内存
    /**
     * 定位 new 和析构函数
定位 new：在预先分配好的内存上构造对象时不会分配新的内存，仅仅是调用对象的构造函数。
显式析构：当你显式使用定位 new 构造对象时，必须显式调用对象的析构函数来释放对象的资源。
这是因为标准库的内存释放函数（如 free 或 tc_free）只释放内存，但不会调用对象的析构函数。
为什么 tc_free 不会调用析构函数
tc_free 只是释放由 tc_malloc 或 tc_memalign 分配的内存块。
它并不知道内存块上是否存在 C++ 对象（以及应该调用哪个析构函数）。这与 free 函数类似：
    */
    for (MyData* data : dataArray) {
        data->~MyData();
        tc_free(data);
    }
    return 0;
}
/**
 * 在这个例子中，overOptimizedAllocate 函数使用TCMalloc的ALlocate Aligned Memory？函数
 * 来分配对齐的内存块，并直接在分配的内存上构造MyData对象。这种做法确实可以控制内存的对齐，
 * 但如果没有明确的性能要求（比如需要特定的对齐来优化硬件访问），这种做法可能是不必要的
 * 此外，代码中显式管理了对象的构造和析构，一集内存的释放，这增加了代码的复杂性。通常情况下使用
 * 标准库提供的new和delete 操作符或者智能指针来管理动态内存是更简洁，安全的方式。为了避免过度优化
 * 我们应该：
 * 1. 只在确实存在性能瓶颈时才进行优化
 * 2. 在进行优化前，使用性能分析工具来识别瓶颈。
 * 3. 优先使用标准库提供的工具和功能，它们是经过优化的，并且易于使用和维护。
 * 4. 保持代码的简洁和清晰，避免不必要的重复性。
*/