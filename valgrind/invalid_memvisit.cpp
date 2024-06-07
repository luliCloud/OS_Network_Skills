/**
 * 无效的内存访问：访问已经释放的内存，访问越界的数组元素，访问未初始化的指针等
*/
#include <iostream>
using namespace std;

void invalidMemoryAccess() {
    int* ptr = new int(10);
    cout << "Allcoated memory: " << *ptr << endl;

    delete ptr; // release mem

    // invalid memory access 
    cout << "Trying to access freed memory " << *ptr << endl;
    return;
}

int main() {
    invalidMemoryAccess();
    return 0;
}
/**
 * Allcoated memory: 10
 * 关键信息；表示发生了一个无效的内存读取操作，大小为4字节。
==43086== Invalid read of size 4
==43086==    at 0x10929D: invalidMemoryAccess() (invalid_memvisit.cpp:14)
==43086==    by 0x1092CA: main (invalid_memvisit.cpp:19)
表明这个地址是在一个已经被释放的内存块内。此外，还会给出这个错误的具体调用栈信息。以及分配
分配这块额你村的原始调用栈信息。
==43086==  Address 0x4de0c80 is 0 bytes inside a block of size 4 free'd
==43086==    at 0x484BB6F: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==43086==    by 0x10927C: invalidMemoryAccess() (invalid_memvisit.cpp:11)
==43086==    by 0x1092CA: main (invalid_memvisit.cpp:19)
==43086==  Block was alloc'd at
==43086==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==43086==    by 0x10921E: invalidMemoryAccess() (invalid_memvisit.cpp:8)
==43086==    by 0x1092CA: main (invalid_memvisit.cpp:19)
==43086== 
Trying to access freed memory 10
==43086== 
==43086== HEAP SUMMARY:
==43086==     in use at exit: 0 bytes in 0 blocks
==43086==   total heap usage: 3 allocs, 3 frees, 73,732 bytes allocated
==43086== 
==43086== All heap blocks were freed -- no leaks are possible
==43086== 
==43086== For lists of detected and suppressed errors, rerun with: -s
==43086== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/