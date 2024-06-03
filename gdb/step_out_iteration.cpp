/** 如何跳出当前循环 */
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {1,2,3,4,5};
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
        // mimic timeconsuming
        for (int j = 0; j < 1000; j++) {} // internal iteration, we want to skip
    }

    cout << "The sum of array elemtns is: " << sum << endl;
    return 0;
}
/**  注意我们要把第一个break point设在循环开始处 比如while，for这一句。而不是循环体内第一句
 * 要把跳出的循环点设在循环体外第一句。
 * (gdb) break 9
Breakpoint 1 at 0x122e: file step_out_iteration.cpp, line 9.
(gdb) break 15
Breakpoint 2 at 0x1263: file step_out_iteration.cpp, line 15.
 * (gdb)run
 * Breakpoint 1, main () at step_out_iteration.cpp:9
9           for (int i = 0; i < 5; i++) {
(gdb) next
10              sum += numbers[i];
(gdb) next
12              for (int j = 0; j < 1000; j++) {} // internal iteration, we want to skip
(gdb) next
9           for (int i = 0; i < 5; i++) {
(gdb) continue
Continuing.

Breakpoint 2, main () at step_out_iteration.cpp:15
15          cout << "The sum of array elemtns is: " << sum << endl;
(gdb) continue
Continuing.
The sum of array elemtns is: 15
[Inferior 1 (process 65024) exited normally]
(gdb) quit
*/