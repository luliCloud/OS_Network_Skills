/**
 * 内存碎片化：频繁的分配和释放内存导致内存空间不连续。降低内存使用效率
 * 通常valgrind是没办法检测内存碎片的，因为valgrind更加关注的是内存泄漏，非法读写等问题。
 * 而内存碎片通常是性能问题，它不会导致系统崩溃或产生运行时错误，但会导致内存使用率下降。
*/
#include <iostream>
#include <list>
using namespace std;

void createAndDelete() {
    list<int*> memoryChunks;
    // allocate many small size mem objects
    for (size_t i = 0; i < 10000; i++) {
        int* ptr = new int(1);
        memoryChunks.push_back(ptr);
    }
    
    // release these mem, but not as the allcoated order
    // 注意rbegin指向最后一个元素，而不是最后一个元素的真实后一位。rend则是第一个元素的前一位
    for (auto it = memoryChunks.rbegin(); it != memoryChunks.rend(); it++) {
        delete it; // release mem
        /**
         * 首先我们从chunk的最后一个元素开始循环，这样就不是按顺序释放内存块。it是反向迭代器
         * next（）是指向it的前一个位置（名义上的next）。它依然是反向迭代器，而vector和list
         * 的erase只支持正向迭代器，所以我们需要base来返回一个正向迭代器。base就是返回一个ite
         * 的真正的下一个位置。所以删除了it自己。
        */
        memoryChunks.ereae(next(it).base());
    }
}

int main() {
    createAndDelete();
    return 0;
}
/**
 * 在这个例子中，我们创建了一个包含整数指针的list，我们在这个列表中分配了许多小块内存，并且不是
 * 按照分配顺序来释放他们的。这可能导致内存碎片化，因为小块内存被频繁的分配和释放，并且在内存中的位置
 * 可能不再连续。然而， 如果你用valgrind运行这个代码，它可能不会报告任何错误。因为代码本身并没有
 * 进行任何非法的内存访问。但是， 如果你使用诸如massif这样的valgrind工具来分析内存使用情况，
 * 你可能会发现内存使用率较低，因为存在很多小的，不连续的内存块。
 * 为了检查内存碎片化，你通常需要查看程序运行时的内存使用模式，比如使用valgrind --tool=massif
 * 来分析堆内存分配的模式，或者使用专门的性能分析工具如perf来检查内存碎片化的影响
 * 在实际情况中，内存碎片化可能影响到内存分配器的性能，导致分配新内存块的速度变慢，甚至在某些情况下
 * 可能导致分配失败，即使系统总体上还有足够的可用内存。
 * 要减少内存碎片化，可以考虑以下策略：
 * 1. 尽量减少不必要的内存分配和释放
 * 2. 使用内存池或者对象池来管理小块内存的分配和释放
 * 3. 尝试按照相同的顺序分配和释放内存块
 * 4. 使用更高高级的内存管理策略 （jemalloc？），比如分块分配或伙伴系统。
 * jemalloc 特别设计了一些策略来控制内存碎片，这使得它在长时间运行的应用中表现更佳。
 * 5. 在长时间运行的程序中，定期重启以清除内存碎片
*/