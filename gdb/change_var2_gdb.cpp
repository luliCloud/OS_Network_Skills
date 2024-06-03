#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;
    int sum = 0;
    for (int i = 0; i < 2; i++) {
        sum = x + y;
        cout << x << " " << y << " " << sum << endl; 
    }
    return 0;
}
/**
 * Breakpoint 1, main () at change_var2_gdb.cpp:9
9               cout << x << " " << y << " " << sum << endl; 
(gdb) info locals
i = 0
x = 10
y = 20
sum = 30
(gdb) set variable x = 11
(gdb) info locals
i = 0
x = 11
y = 20
sum = 30
(gdb) next
11 20 30
7           for (int i = 0; i < 2; i++) {
(gdb) next
8               sum = x + y;
(gdb) info locals
i = 1
x = 11
y = 20
sum = 30
(gdb) next

Breakpoint 1, main () at change_var2_gdb.cpp:9
9               cout << x << " " << y << " " << sum << endl; 
(gdb) info locals
i = 1
x = 11
y = 20
sum = 31
(gdb) next
11 20 31
7           for (int i = 0; i < 2; i++) {
(gdb) continue
Continuing.
[Inferior 1 (process 69171) exited normally]
(gdb) quit
*/