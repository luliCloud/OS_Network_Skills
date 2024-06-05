/**
 * 访问未初始化或者已被释放的指针，导致程序崩溃或数据损坏。用C++实现代码，并且
 * 写出用valgrind跑会出现什么错误。
 * 野指针是一个常见的变成错误，它指的是一个指针变量指向了一个已经被释放的内存地址，
 * 或者指向一个未初始化的内存地址（int* ptr，但没有初始化指向nullptr或者int变量）。
 * 这样的指针如果被访问或操作，很可能会导致程序崩溃或数据损坏。
*/
#include <iostream>
using namespace std;
int main() {
    int* ptr = new int(5); // allocate memory and initialize
    cout << "Value before deletion: " << *ptr << endl;

    delete ptr; // release memory
    ptr = nullptr; // best practical, set ptr to nullptr immediatly after release

    // intentionally to make wild pointer mistake, cancel the setting of ptr as nullptr
    // ptr = nullptr;

    // visit the released memory, wild pointer problem
    cout << "Value after deletion: " << *ptr << endl;

    return 0;
}
/***
 * 在这个例子中，我们首先分配了一个int类型的内存，并将其初始化为5.然后我们打印了这个内存的值，
 * 接着释放了这块内存，并将指针ptr设置为nullptr。这是最佳时间，但是为了演示野指针，我们注释掉
 * 这行代码。最后我们尝试访问已经被释放的内存，这将导致野指针问题。
 * 如果你是用valgrind工具来检测内存泄漏和未初始化的内存访问等问题，运行上面的代码（取消
 * 将ptr设置为nullptr的那行代码），你可能会看到类似于以下的错误信息。
 * 
 * 如何运行valgrind 进行 memory-leak 检测
 * $ g++ -g wild_pointer.cpp
 * $ valgrind --leak-check=full ./a.out //运行valgrind 的memcheck 工具运行你的程序。
 * 它是valgrind的默认工具，专门用于检测内存管理问题。
 * 
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --leak-check=full ./a.out
==23686== Memcheck, a memory error detector
==23686== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==23686== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==23686== Command: ./a.out
==23686== 
Value before deletion: 5
==23686== Invalid read of size 4  // 表示发生了一个无效读取操作，大小为4bytes，即一个int大小
==23686==    at 0x1092A5: main (wild_pointer.cpp:21)
==23686==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
表示你尝试访问的地址位于一个已经被释放的内存块内存。

==23686== Process terminating with default action of signal 11 (SIGSEGV)
==23686==  Access not within mapped region at address 0x0
==23686==    at 0x1092A5: main (wild_pointer.cpp:21)
ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

请注意，野指针行为是不确定的，实际运行程序可能遇到的情况（比如崩溃，数据损坏，或其他为定义行为）
会比valgrind报告的更加严重和复杂。此外，不同的编辑器，操作系统和内存管理策略也可能导致不同表现。
因此，便携代码是应该始终避免野指针，在可能的情况下使用智能指针等现代C++特性来管理内存。
*/
