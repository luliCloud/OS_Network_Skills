/**
 * 双重释放，对同一块内存执行了两次释放操作，这种操作是非法的， 因为该内存块已经
 * 回还给系统了，因此会引发程序崩溃或未定义行为。
*/
#include <iostream>
using namespace std;

void doubleFree() {
    int* ptr = new int(10);
    cout << "Allocated memory: " << *ptr << endl; 
    delete ptr;
    delete ptr;
}
/**
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --leak-check=full ./a.out
==41992== Memcheck, a memory error detector
==41992== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==41992== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==41992== Command: ./a.out
==41992== 
Allocated memory: 10
关键信息，表明发生了无效的释放操作，同时还会显示双重释放的地址，以及这个地址对应的内存块
时如何被分配的。在这个例子中，0x4de0c80 is 0 bytes inside a block of size 4 free'd
指出被释放的内存地址在一个已经被释放过的块内。此外，还会给出分配这块内存的调用栈信息。
==41992== Invalid free() / delete / delete[] / realloc()
==41992==    at 0x484BB6F: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==41992==    by 0x109292: doubleFree() (double_release.cpp:12)
==41992==    by 0x1092A2: main (double_release.cpp:16)
==41992==  Address 0x4de0c80 is 0 bytes inside a block of size 4 free'd
==41992==    at 0x484BB6F: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==41992==    by 0x10927C: doubleFree() (double_release.cpp:11)
==41992==    by 0x1092A2: main (double_release.cpp:16)
==41992==  Block was alloc'd at
==41992==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==41992==    by 0x10921E: doubleFree() (double_release.cpp:9)
==41992==    by 0x1092A2: main (double_release.cpp:16)
==41992== 
==41992== 
==41992== HEAP SUMMARY:
==41992==     in use at exit: 0 bytes in 0 blocks
==41992==   total heap usage: 3 allocs, 4 frees, 73,732 bytes allocated
==41992== 
==41992== All heap blocks were freed -- no leaks are possible
==41992== 
==41992== For lists of detected and suppressed errors, rerun with: -s
==41992== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/

int main() {
    doubleFree();
    return 0;
}
