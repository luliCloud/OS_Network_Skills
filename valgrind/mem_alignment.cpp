/**
 * 内存对齐问题：特定平台对数据对齐有特殊要求。内存对齐时计算机硬件为了提高访问速度的一种优化手段。
 * 当数据在内存中的地址是其大小的整数倍时，处理齐访问该数据会更快。在C++中，编译器通常会处理内存对齐
 * 问题，但有时程序员可能需要手动对齐，尤其是在处理特定硬件或者性能敏感的代码时
 * 如果不满足特定平台的内存对齐要求，程序可能会崩溃或产生不可预测的行为。
*/
#include <iostream>
#include <cstdint>
using namespace std;

/**
 * 在 C++ 中，alignas 关键字是用来指定一个变量或类型的对齐要求。这是 C++11 引入的特性，
 * 目的是提供更细致的控制 over the memory alignment of data structures，
 * 从而可能优化性能，或满足特定硬件平台上的对齐要求。

alignas 的基本用途和解释
语法：alignas(expression)
目的：指定变量或类型的最小对齐字节数。
这里的 alignas(8) 指示 AlignedStruct 结构体应该按 8 字节对齐。这意味着结构体的起始内存地址将是 8 字节的倍数。这通常是为了确保其中包含的数据类型（如 double）能够满足其自然对齐要求，从而获得最佳的访问性能。
在现代处理器和编译器上，double 类型通常需要 8 字节对齐，以便快速访问。
*/
struct alignas(8) AlignedStruct {
    int a;
    double b;
};

struct NotAlignedStruct {
    int a;
    double b;
};

int main() {
    // correct aligners
    AlignedStruct alignedObj;
    cout << "AlignedStruct size: " << sizeof(alignedObj) << ", alignment: "
    << alignof(alignedObj) << endl; //alignof 返回一个表示参数类型或对象对齐要求的整数，
    // 即该类型或对象在内存中最小的对齐字节数。
    // 这是 C++11 引入的特性，旨在与 alignas 一起使用，以提供对数据对齐更精确的控制。

    // 尝试手动分配未对齐的内存
    char* rawMemory = new char[sizeof(NotAlignedStruct)]; // 12 bytes

    NotAlignedStruct* unalignedObj = reinterpret_cast<NotAlignedStruct*>(rawMemory);
    unalignedObj->a = 1; 
    unalignedObj->b = 2;

    // 假设我们对这个未对齐的对象进行操作
    // 提前让它析构，清理掉这个地址上的数据。
    unalignedObj->~NotAlignedStruct(); // 调用析构函数，假设有资源需要清理
    
    /**
     * 在 C++ 中，使用 new 关键字结合定位 new 表达式（placement new）是一种高级功能，
     * 允许开发者在已分配的内存上直接构造对象。
     * 这样做可以提供对内存管理的精确控制，并允许在特定的内存位置初始化对象，
     * 而无需进行额外的内存分配。
     * 定位 new 的基本语法如下：new (address) Type(arguments);
    */
    //new (unalignedObj) NotAlignedStruct(); // 在unaligneObj地址上直接放置新对象
    AlignedStruct* resPtr =  new (unalignedObj) AlignedStruct(); // 如果struct 16 bytes，访问越界。如果strcut 是 8 bytes， 内存泄漏

    // 使用对象。。
    resPtr->a = 10;

    // 再次调用析构函数
    // delete[] rawMemory;  // this is correct way to delete

    resPtr->~AlignedStruct();
    delete resPtr;  // 释放内存

    return 0;
}
/**
 * 在这个例子中，AlignedStruct使用了alignas关键字来指定对其要求（这里是8字节对齐），而NotAlignedStruct
 * 则没有指定对齐。我们尝试手动分配NotAlignedStruct的内存，但不保证其对齐。
 * 如果平台要求double 类型数据以8字节对齐，而NotAlignedStruct中的double成员没有正确对齐，那么
 * 访问这个double成员可能会引发未定义行为，包括程序崩溃
 * 使用Valgrind运行这个程序可能会看到不同的错误，具体取决平台的实现和访问未对齐内存的方式。
 * 可能的错误包括：
 * Invalid read of size 8: 尝试读取一个未对齐的double类型变量
 * Address not stack'd, malloc'd or (recently) free'd: 如果访问未对齐内存导致了
 * 段错误哦（segmentation fault），valgrind可能会报告这个错误。
 * conditional jump or move depends on uninitialized value(s): 如果未对齐的内存访问
 * 导致了未初始化的值被使用，可能会看到这个错误。
 * 这些错误并不一定是会出现的，因为未对齐访问的行为是未定义的，它可能在不同的平台和编译器下产生不同的
 * 结果，在某些情况下，程序可能看起来运行正常，但实际上存在潜在的风险。因此，确保正确的对齐数据是非常重要
 * 
 * AlignedStruct size: 16, alignment: 8
==49107== 
==49107== HEAP SUMMARY:
==49107==     in use at exit: 0 bytes in 0 blocks
==49107==   total heap usage: 3 allocs, 3 frees, 73,744 bytes allocated
==49107== 
==49107== All heap blocks were freed -- no leaks are possible
==49107== 
==49107== For lists of detected and suppressed errors, rerun with: -s
==49107== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

第二个才是内存泄漏的方式  AlignedStruct 只有int， 8 字节
change to AlignedPtr, don't delete raw memory. meaningless. Always delete correct size of mem
==49486== Memcheck, a memory error detector
==49486== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==49486== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==49486== Command: ./a.out
==49486== 
AlignedStruct size: 8, alignment: 8
关键信息：alignedStruct 8 bytes
==49486== Mismatched free() / delete / delete []
==49486==    at 0x484BB6F: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49486==    by 0x1092DA: main (mem_alignment.cpp:66)
==49486==  Address 0x4de10c0 is 0 bytes inside a block of size 16 alloc'd
==49486==    at 0x484A2F3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49486==    by 0x109278: main (mem_alignment.cpp:41)
==49486== 
==49486== 
==49486== HEAP SUMMARY:
==49486==     in use at exit: 0 bytes in 0 blocks
==49486==   total heap usage: 3 allocs, 3 frees, 73,744 bytes allocated
==49486== 
==49486== All heap blocks were freed -- no leaks are possible
==49486== 
==49486== For lists of detected and suppressed errors, rerun with: -s
==49486== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

第三个是指针越界。AlignedStruct，int ，double 16bytes
==49576== Memcheck, a memory error detector
==49576== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==49576== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==49576== Command: ./a.out
==49576== 
AlignedStruct size: 16, alignment: 8
==49576== Mismatched free() / delete / delete []
==49576==    at 0x484BB6F: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49576==    by 0x1092E3: main (mem_alignment.cpp:68)
==49576==  Address 0x4de10c0 is 0 bytes inside a block of size 16 alloc'd
==49576==    at 0x484A2F3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==49576==    by 0x109278: main (mem_alignment.cpp:41)
==49576== 
==49576== 
==49576== HEAP SUMMARY:
==49576==     in use at exit: 0 bytes in 0 blocks
==49576==   total heap usage: 3 allocs, 3 frees, 73,744 bytes allocated
==49576== 
==49576== All heap blocks were freed -- no leaks are possible
==49576== 
==49576== For lists of detected and suppressed errors, rerun with: -s
==49576== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/