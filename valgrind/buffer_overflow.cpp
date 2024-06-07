/**
 * 缓冲区溢出：向固定大小的缓冲区写入过多数据，ke可能覆盖相邻内存，引发安全问题。
 * 缓冲区溢出是一种常见的安全漏洞，攻击者可以利用它执行恶意代码。
*/
#include <iostream>
#include <cstring>
using namespace std;

void bufferOverflow() {
    char buffer[128]; // create a fixed size buffer
    cout << "Enter some text: ";
    cin.getline(buffer, sizeof(buffer)); // read text from cin，for only a single line

    // now will write more char than the size we assigned before. 
    // strcpy是覆盖原内容，strcat才是衔接
    strcpy(buffer, "This is a very long string that will cuase a buffer overflow, \
    because it is much longer tghan the buffer sdize. This is a very long string that will cuase a buffer overflow, \
    because it is much longer tghan the buffer sdize.");
}

int main() {
    bufferOverflow();
    return 0;
}
/**
 * valgrind --leak-check=full --track-origin=yes ./a.out
 * Enter some text: this is short
*** stack smashing detected ***: terminated
==45169== 
==45169== Process terminating with default action of signal 6 (SIGABRT)
==45169==    at 0x4B309FC: __pthread_kill_implementation (pthread_kill.c:44)
==45169==    by 0x4B309FC: __pthread_kill_internal (pthread_kill.c:78)
==45169==    by 0x4B309FC: pthread_kill@@GLIBC_2.34 (pthread_kill.c:89)
==45169==    by 0x4ADC475: raise (raise.c:26)
==45169==    by 0x4AC27F2: abort (abort.c:79)
==45169==    by 0x4B23675: __libc_message (libc_fatal.c:155)
==45169==    by 0x4BD0599: __fortify_fail (fortify_fail.c:26)
==45169==    by 0x4BD0565: __stack_chk_fail (stack_chk_fail.c:24)
关键信息；这个错误消息告诉我们有一个无效的写操作，即试图写入一个不允许写入的内存地址。
valgrind还会告诉我们这个写操作是通过operator new[]分配的，并且提供了分配时的内存地址
在我的系统中没有发生，不知道是什么参数用的不对。
==45169==    by 0x1093F5: bufferOverflow() (buffer_overflow.cpp:18)
==45169==    by 0x612065736175631F: ???
==45169==    by 0x207265666675621F: ???
==45169==    by 0x776F6C667265766E: ???
==45169==    by 0x656220202020202B: ???
==45169==    by 0x7469206573756162: ???
==45169== 
==45169== HEAP SUMMARY:
==45169==     in use at exit: 74,752 bytes in 3 blocks
==45169==   total heap usage: 3 allocs, 0 frees, 74,752 bytes allocated
==45169== 
==45169== LEAK SUMMARY:
==45169==    definitely lost: 0 bytes in 0 blocks
==45169==    indirectly lost: 0 bytes in 0 blocks
==45169==      possibly lost: 0 bytes in 0 blocks
==45169==    still reachable: 74,752 bytes in 3 blocks
==45169==         suppressed: 0 bytes in 0 blocks
==45169== Reachable blocks (those to which a pointer was found) are not shown.
==45169== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==45169== 
==45169== For lists of detected and suppressed errors, rerun with: -s
==45169== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Aborted (core dumped)
请注意，在实际情况中，缓冲区溢出可能导致程序崩溃，数据损坏或更严重的安全问题，
如代码执行（如果攻击者能够精确控制溢出的内容并覆盖程序的控制流）。因此，编写安全的代码时，
应始终避免缓冲区溢出，使用肉strncpy之类的安全函数，并确保不会写入超过缓冲区大小的
数据。
*/