/**
 * 内存泄漏：动态分配的内存没有得到正确释放，会导致程序占用的内存持续增加，长期运行会耗尽系统资源。
 * 最终导致程序崩溃或系统变得不稳定。
*/
#include <iostream>
using namespace std;
void leakMemory() {
    int* ptr = new int(5); // allocate mem but forget to release
    cout << "Allocated memory and leaked it." << endl;
    // not delete ptr, leading to mem leak
}

int main() {
    leakMemory();
    return 0;
}
/**
 * 在这个例子中，leakMemory函数分配了一块int类型的动态内存，并打印了value，但是忘记释放这块内存
 * 因此 每次调用leakMemeory函数时，都会有一块内存被泄漏。
 * 如果你是用valgrind来检测内存泄漏，运行上面代码
 * 
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --leak-check=full --track-origins=yes ./a.out
==24575== Memcheck, a memory error detector
==24575== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24575== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==24575== Command: ./a.out
==24575== 
Allocated memory and leaked it.
==24575== 
关键信息：HEAP SUMMaRY告诉你一共有4 字节被分配，以及3 heap被分配，2 heap释放。
==24575== HEAP SUMMARY:
==24575==     in use at exit: 4 bytes in 1 blocks
==24575==   total heap usage: 3 allocs, 2 frees, 73,732 bytes allocated
==24575== 
==24575== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==24575==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==24575==    by 0x1091DE: leakMemory() (memory_leak.cpp:8)
==24575==    by 0x109223: main (memory_leak.cpp:14)
==24575== 
关键信息：详细列出了泄漏的内存，包括definitely lost（确定丢失的）内存块大小，以及块数。
==24575== LEAK SUMMARY:
==24575==    definitely lost: 4 bytes in 1 blocks
==24575==    indirectly lost: 0 bytes in 0 blocks
==24575==      possibly lost: 0 bytes in 0 blocks
==24575==    still reachable: 0 bytes in 0 blocks
==24575==         suppressed: 0 bytes in 0 blocks
==24575== 
==24575== For lists of detected and suppressed errors, rerun with: -s
==24575== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

实际的内存泄漏可能会更加复杂，可能涉及多个分配和释放操作。以及不同生命周期的对象
因此，在编写代码时，应该始终确保动态分配的内存得到正确释放，或者使用智能指针等
现代C++特性来自动管理内存。
*/