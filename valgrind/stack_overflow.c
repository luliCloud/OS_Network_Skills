#include <stdio.h>

void function(int a, int b, int c) {
    char buffer1[5];
    char buffer2[10];
    int *ret;
    ret = (int*)(buffer1 + 12);
    (*ret) += 8;
}

int main() {
    int x = 0; 
    function(1,2,3);
    x = 1;
    printf("%d\n", x);
    return 0;
}
/**
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ gcc -g -O0 stack_overflow.c 
 * -O0确保编译器没有优化
(base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out
==63587== Memcheck, a memory error detector
==63587== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==63587== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==63587== Command: ./a.out
==63587== 
关键信息：
*** stack smashing detected ***: terminated 
这是GCC compiler插入的堆栈保护代码（-fstack-protector）检测到堆栈破坏并终止程序的信号。

==63587== 
==63587== Process terminating with default action of signal 6 (SIGABRT) 
程序由于前述堆栈破坏终止，操作系统发送了SIGABRT信号来终止进程

==63587==    at 0x49069FC: __pthread_kill_implementation (pthread_kill.c:44)
==63587==    by 0x49069FC: __pthread_kill_internal (pthread_kill.c:78)
==63587==    by 0x49069FC: pthread_kill@@GLIBC_2.34 (pthread_kill.c:89)
==63587==    by 0x48B2475: raise (raise.c:26)
==63587==    by 0x48987F2: abort (abort.c:79)
==63587==    by 0x48F9675: __libc_message (libc_fatal.c:155)
==63587==    by 0x49A6599: __fortify_fail (fortify_fail.c:26)
关键信息：__stack_chk_fail 表示堆栈保护检查失败，这是堆栈破坏被检测到的直接指示。
==63587==    by 0x49A6565: __stack_chk_fail (stack_chk_fail.c:24)
function 和 main 显示 function 函数中发生了堆栈破坏，具体位于 stack_overflow.c 文件的第 9 行。
==63587==    by 0x1091BC: function (stack_overflow.c:9)
==63587==    by 0x1091E5: main (stack_overflow.c:13)
==63587== 
==63587== HEAP SUMMARY:
==63587==     in use at exit: 0 bytes in 0 blocks
==63587==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==63587== 
==63587== All heap blocks were freed -- no leaks are possible
==63587== 
==63587== For lists of detected and suppressed errors, rerun with: -s
==63587== ERROR SUMMARY: 0 errors from 0 con
*/