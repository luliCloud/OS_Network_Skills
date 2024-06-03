/** 如何查看当前line */
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10,20,30,40,50};
    int* p = numbers;

    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        cout << numbers[i] << endl;
    }

    cout << "Press enter to continue..." << endl;
    cin.get();

    return 0;
}
/**
 * (gdb) break check_memory.cpp:10
Breakpoint 1 at 0x1258: file check_memory.cpp, line 10.
(gdb) run
Starting program: /home/lu/greenpear/OSlearn/gdb/a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at check_memory.cpp:10
10              cout << numbers[i] << endl;
(gdb) print p  // 查看p指向的内存地址
$1 = (int *) 0x7fffffffdda0
(gdb) x/5dw 0x7fffffffdda0 // 显示该内存地址的储存内容
// 使用x命令查看内容，5表示查看5个整数，d表示十进制格式，w表示word 大小
// x/5dw 中的 w 指示符表示显示内存内容的单位大小为一个 "word"。在 32 位系统上，
一个 word 通常是 32 位（4 字节），而在 64 位系统上，一个 word 通常是 64 位（8 字节）。
这个命令帮助你从指定地址开始查看连续的内存内容，以理解程序的内存布局和数据分布。
（gdb）x/4xb // 这将显示指针 p 指向的地址开始的四个字节，每个字节以十六进制格式显示。

0x7fffffffdda0: 10      20      30      40
0x7fffffffddb0: 50
(gdb) continue
*/