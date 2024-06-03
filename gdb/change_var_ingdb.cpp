/** 在gdb调试过程中改变变量的值 */
#include <iostream>
using namespace std;
int main() {
    int value = 20;
    cout << "Initial value is: " << value << endl;

    // stop the program, for debug
    cout << "Press enter to continue...";
    cin.get(); // 等待用户按下enter，输入的字符会被丢弃，用于让程序暂停等待用户操作
    /**
     * 这两行其实是一起执行的，输入statement的同时cin.get开始让程序暂停，知道用户按下enter键，
     * 才会继续后面的程序（cout<<）
    */

    cout << "Modified value: " << value << endl;
    return 0;
}
/**
 * (gdb) break 9
Breakpoint 1 at 0x1237: file change_var_ingdb.cpp, line 9.
(gdb) run
Starting program: /home/lu/greenpear/OSlearn/gdb/a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Initial value is: 20

Breakpoint 1, main () at change_var_ingdb.cpp:9
9           cout << "Press enter to continue...";
(gdb) print value
$1 = 20
(gdb) set variable value = 42
(gdb) print value
$2 = 42
(gdb) continue
Continuing.
Press enter to continue...
Modified value: 42
[Inferior 1 (process 67737) exited normally]
(gdb) quit
*/