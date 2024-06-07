/**
 * 错误的内存分配大小：请求的内存大小的计算错误，可能导致分配不足或过多，浪费资源或引发溢出。
 * 错误的分配内存大小通常发生在动态内存分配时，比如使用new或者malloc。如果分配的大小计算错误，
 * 可能会导致分配的内存块太小（无法满足需求）或太大（浪费资源）。
*/
#include <iostream>
using namespace std;

int* allcoateIncorrectlySizedMemory(int numElements, int elementSize) {
    // 假设elementSize是每个元素的实际大小（以字节为单位）
    // 但是这里的计算错误的假设numElements是以字节为单位的
    size_t totalSize = numElements * sizeof(int); // 正确的计算应该是 numEle * eleSize
    //// 十个字节就分配十个单位，这里分配了过多内存；
    // int* ptr = new int[totalSize]; // totalSize = 40, so allcoate 40 int -> 160 bytes

    int* ptr = (int*)new char[totalSize]; 
    // 或者正确的写法是 int* ptr = new int[numElements]
    return ptr;
}

int main() {
    int numElements = 10;
    int elementSize = 4; // 在64位操作系统，int大小为4
    int* incorrectMem = allcoateIncorrectlySizedMemory(numElements, elementSize);
    // using incorrectMem to operate
    // ...
    // release mem
    // delete[] incorrectMem;
    return 0;
}
/**
 * ==48360== Memcheck, a memory error detector
==48360== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==48360== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==48360== Command: ./a.out
==48360== 
==48360== 
==48360== HEAP SUMMARY:
关键信息：in use at exit部分，有40字节没有被释放（对应char那个代码）。内存泄漏是一个严重的浪费问题，应该避免。
==48360==     in use at exit: 40 bytes in 1 blocks
==48360==   total heap usage: 2 allocs, 1 frees, 72,744 bytes allocated
==48360== 
==48360== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==48360==    at 0x484A2F3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==48360==    by 0x1091B3: allcoateIncorrectlySizedMemory(int, int) (false_size_allocate.cpp:13)
==48360==    by 0x1091E6: main (false_size_allocate.cpp:21)
==48360== 
==48360== LEAK SUMMARY:
==48360==    definitely lost: 40 bytes in 1 blocks
==48360==    indirectly lost: 0 bytes in 0 blocks
==48360==      possibly lost: 0 bytes in 0 blocks
==48360==    still reachable: 0 bytes in 0 blocks
==48360==         suppressed: 0 bytes in 0 blocks
==48360== 
==48360== For lists of detected and suppressed errors, rerun with: -s
==48360== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

*/