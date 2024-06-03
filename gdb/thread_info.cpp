/** 如何显示当前线程信息 */
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void thread_function(int id) {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Thread " << id << "is running" << endl;
}

int main() {
    thread t1(thread_function, 1);
    thread t2(thread_function, 2);

    t1.join();
    t2.join();

    return 0;
}
/**
 * 确保使用 -g 选项来编译程序，以包含调试信息，并开启 -pthread 标志来链接线程库。
 * $ g++ -g -pthread thread_info.cpp 
 * 
 * 启动 gdb
 * $ gdb ./a.out
 * 
 * //set break point
 * $ break main
 * $ run
 * 
 * // check all threads
 * $ info threads
 * $ next  // until line 13
 * $ 13          thread t2(thread_function, 2);
(gdb) info threads
  Id   Target Id                                 Frame 
* 1    Thread 0x7ffff7ea03c0 (LWP 57531) "a.out" main () at thread_info.cpp:13
  2    Thread 0x7ffff77ff640 (LWP 57789) "a.out" 0x00007ffff78e57f8 in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, 
    req=0x7ffff77fed00, rem=0x7ffff77fed00) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
(gdb) thread 2  // 用这个信息查看thread 2 的信息
[Switching to thread 2 (Thread 0x7ffff77ff640 (LWP 57789))]
#0  0x00007ffff78e57f8 in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff77fed00, rem=0x7ffff77fed00)
    at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.
*/