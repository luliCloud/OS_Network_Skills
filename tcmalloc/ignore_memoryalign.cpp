/**
 * 忽视内存对齐：某些硬件和编译器优化可能对内存对齐有特定要求；使用TCMalloc时，如果不考虑
 * 这些因素，可能导致性能下降或程序崩溃。
 * 忽视内存对齐是一个常见的性能瓶颈，甚至可能导致程序崩溃，特别是在处理硬件优化和编辑器优化时。
 * 如果你在代码中直接使用TCmalloc来分配内存，并且不遵守要求，那么仍然可能遇到问题。下面是一个
 * 代码示例，展示如何忽视了内存对齐，并可能导致潜在的问题。
*/
#include <iostream>
#include <gperftools/tcmalloc.h>
using namespace std;

// suppose we have a struct need memory align
struct AlignedStruct {
    // other members
    double value; // double requre 8 bytes aligned
};

int main() {
    // using tcmalloc allcoate memory, but not consider memory
    size_t size = sizeof(AlignedStruct);
    void* raw_memory = tcmalloc::MallocExtension::Malloc(size);
    if (raw_memory == nullptr) {
        cerr << "Memory allcoation failed!" << endl;
        return 1;
    } 

    // convert raw memory change to pointer to struct, ignoring alignment
    AlignedStruct* ptr = reinterpret_cast<AlignedStruct*>(raw_memory);

    // visit struct member, if memory not aligned correctly, may result in performance
    // decline or program crash
    ptr->value = 3.14;
    cout << "Value:" << ptr->value << endl;

    // release memory
    tcmalloc::ExtensinoMalloc::Free(raw_memory);
    return 0;
}
/**
 * 在这个例子中，我们尝试使用TCMalloc直接分配内存给一个需要特定内存对齐的结构体。我们没有使用
 * 任何机制来确保分配的内存时对齐的，而是简单的将原始内存指针转换为结构体指针。如果分配的内存没有
 * 正确对齐，访问ptr->value可能会导致性能问题，甚至在某些硬件和编译器上导致程序崩溃
 * 位了避免这些问题，我们应该：
 * 1. 确保老姐你的硬件和编译器对内存对齐的要求，如果使用struct or class并且它们包含需要特定对齐的类型
 * 如double，long double，某些SMID类型等，考虑使用编译器提供的特性来确保自动对齐。例如在GCC或
 * Clang中使用__attribute__((aligned(N))).
 * 2. 如果需要内存管理内存，并且要求特定对齐，使用posix_memalgin 或者 aligned_alloc函数来分配对齐的
 * 内存。
 * 3. 查阅TCMalloc文档，看是否有提供对齐相关的功能或者建议。
 * 记住，对齐通常是为了提高性能，因为某些处理器访问为对齐的数据时性能较差，甚至可能无法正常工作。
 * 因此，在编写高性能代码时，确保正确处理内存对齐时非常重要的。
*/