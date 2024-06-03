/** 如何查看当前line */
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10,20,30,40,50};
    int sum = 0;
    int count = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }

    double average = sum / count;
    cout << "Ave is : " << average << endl;
    return 0;
}
/**
 * (gdb) break check_curr_line.cpp:11  // 设置break point 在1行
Breakpoint 1 at 0x123e: file check_curr_line.cpp, line 11.
(gdb) run
Starting program: /home/lu/greenpear/OSlearn/gdb/a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at check_curr_line.cpp:11
11              sum += numbers[i];
(gdb) list  // 显示上下各五行
6           int numbers[] = {10,20,30,40,50};
7           int sum = 0;
8           int count = sizeof(numbers) / sizeof(numbers[0]);
9
10          for (int i = 0; i < count; i++) {
11              sum += numbers[i];
12          }
13
14          double average = sum / count;
--Type <RET> for more, q to quit, c to continue without paging--RET
15          cout << "Ave is : " << average << endl;
(gdb) info line  // 显示当前行信息
Line 6 of "check_curr_line.cpp" starts at address 0x555555555204 <main()+27>
   and ends at 0x555555555227 <main()+62>.
(gdb) print average  // 显示在目前状态下average 的值
$1 = 0
(gdb) print numbers
$2 = {10, 20, 30, 40, 50}
(gdb) where  // 显示目前在哪一行
#0  main () at check_curr_line.cpp:11
(gdb) bt  // 显示当前函数调用栈
#0  main () at check_curr_line.cpp:11
(gdb) frame 1
No frame at level 1.
(gdb) list check_curr_line.cpp:14  // 调整list 命令的显示范围，直接查看特定文件的特定行
9
10          for (int i = 0; i < count; i++) {
11              sum += numbers[i];
12          }
13
14          double average = sum / count;
15          cout << "Ave is : " << average << endl;
16          return 0;
17      }
(gdb) quit
A debugging session is active.

        Inferior 1 [process 65718] will be killed.

Quit anyway? (y or n) y
*/