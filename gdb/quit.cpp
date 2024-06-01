/** for gdb quit test
*/
#include <iostream>
using namespace std;

int main() {
    cout << "Hello world" << endl;
    return 0;
}

/**
 * (base) lu@lu-t3610:~/greenpear/OSlearn/gdb$ gdb ./a.out
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
--Type <RET> for more, q to quit, c to continue without paging--c
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./a.out...
(No debugging symbols found in ./a.out)
(gdb) break main   // lu: I set break point here
Breakpoint 1 at 0x11b1
(gdb) run  // run the main funciton
Starting program: /home/lu/greenpear/OSlearn/gdb/a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, 0x00005555555551b1 in main ()
(gdb) next  // go to next line
Single stepping until exit from function main,
which has no line number information.
Hello world
__libc_start_call_main (main=main@entry=0x5555555551a9 <main>, argc=argc@entry=1, argv=argv@entry=0x7fffffffded8) at ../sysdeps/nptl/libc_start_call_main.h:74
74      ../sysdeps/nptl/libc_start_call_main.h: No such file or directory.
(gdb) next
[Inferior 1 (process 45857) exited normally]
(gdb) next
The program is not being run.
(gdb) continue
The program is not being run.
(gdb) quit  // tell the program to leave
(base) lu@lu-t3610:~/greenpear/OSlearn/gdb$ 
*/