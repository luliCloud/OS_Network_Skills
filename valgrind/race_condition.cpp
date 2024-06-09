/**
 * race conditions 发生在程序的行为依赖于多个线程的交错执行时许，导致程序的行为依赖于多个
 * 线程的交错执行时序。下面展示了两个线程尝试修改同一个变量而没有适当的同步机制
*/
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int shared_var = 0;
// mutex mtx;  // to address the race condition

void increment() {
    for (int i = 0; i < 100; i++) {
        // mtx.lock();  // address race condition
        shared_var++;
        // mtx.unlock(); // same
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Expected value: 200" << endl;
    cout << "Actual value: " << shared_var << endl;

    return 0;
}
/**
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ g++ race_condition.cpp -lpthread
(base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --tool=helgrind ./a.out
==62527== Helgrind, a thread error detector
==62527== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==62527== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==62527== Command: ./a.out
==62527== 
==62527== ---Thread-Announcement------------------------------------------
==62527== 
==62527== Thread #3 was created
==62527==    at 0x4BE89F3: clone (clone.S:76)
==62527==    by 0x4BE98EE: __clone_internal (clone-internal.c:83)
==62527==    by 0x4B576D8: create_thread (pthread_create.c:295)
==62527==    by 0x4B581FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==62527==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==62527==    by 0x4953328: std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==62527==    by 0x1095DF: std::thread::thread<void (&)(), , void>(void (&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x10933E: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527== 
==62527== ---Thread-Announcement------------------------------------------
==62527== 
==62527== Thread #2 was created
==62527==    at 0x4BE89F3: clone (clone.S:76)
==62527==    by 0x4BE98EE: __clone_internal (clone-internal.c:83)
==62527==    by 0x4B576D8: create_thread (pthread_create.c:295)
==62527==    by 0x4B581FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==62527==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==62527==    by 0x4953328: std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==62527==    by 0x1095DF: std::thread::thread<void (&)(), , void>(void (&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109328: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527== 
==62527== ----------------------------------------------------------------
==62527== 
关键信息
==62527== Possible data race during read of size 4 at 0x10C154 by thread #3
==62527== Locks held: none
==62527==    at 0x1092DA: increment() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109C46: void std::__invoke_impl<void, void (*)()>(std::__invoke_other, void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109BF2: std::__invoke_result<void (*)()>::type std::__invoke<void (*)()>(void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B93: void std::thread::_Invoker<std::tuple<void (*)()> >::_M_invoke<0ul>(std::_Index_tuple<0ul>) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B63: std::thread::_Invoker<std::tuple<void (*)()> >::operator()() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B43: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::_M_run() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x4953252: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==62527==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==62527==    by 0x4B57AC2: start_thread (pthread_create.c:442)
==62527==    by 0x4BE8A03: clone (clone.S:100)
==62527== 
==62527== This conflicts with a previous write of size 4 by thread #2
==62527== Locks held: none
==62527==    at 0x1092E3: increment() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109C46: void std::__invoke_impl<void, void (*)()>(std::__invoke_other, void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109BF2: std::__invoke_result<void (*)()>::type std::__invoke<void (*)()>(void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B93: void std::thread::_Invoker<std::tuple<void (*)()> >::_M_invoke<0ul>(std::_Index_tuple<0ul>) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B63: std::thread::_Invoker<std::tuple<void (*)()> >::operator()() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B43: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::_M_run() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x4953252: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==62527==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==62527==  Address 0x10c154 is 0 bytes inside data symbol "shared_var"
==62527== 
==62527== ----------------------------------------------------------------
==62527== 
==62527== Possible data race during write of size 4 at 0x10C154 by thread #3
==62527== Locks held: none
==62527==    at 0x1092E3: increment() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109C46: void std::__invoke_impl<void, void (*)()>(std::__invoke_other, void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109BF2: std::__invoke_result<void (*)()>::type std::__invoke<void (*)()>(void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B93: void std::thread::_Invoker<std::tuple<void (*)()> >::_M_invoke<0ul>(std::_Index_tuple<0ul>) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B63: std::thread::_Invoker<std::tuple<void (*)()> >::operator()() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B43: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::_M_run() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x4953252: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==62527==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==62527==    by 0x4B57AC2: start_thread (pthread_create.c:442)
==62527==    by 0x4BE8A03: clone (clone.S:100)
==62527== 
==62527== This conflicts with a previous write of size 4 by thread #2
==62527== Locks held: none
==62527==    at 0x1092E3: increment() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109C46: void std::__invoke_impl<void, void (*)()>(std::__invoke_other, void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109BF2: std::__invoke_result<void (*)()>::type std::__invoke<void (*)()>(void (*&&)()) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B93: void std::thread::_Invoker<std::tuple<void (*)()> >::_M_invoke<0ul>(std::_Index_tuple<0ul>) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B63: std::thread::_Invoker<std::tuple<void (*)()> >::operator()() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x109B43: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::_M_run() (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==62527==    by 0x4953252: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==62527==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==62527==  Address 0x10c154 is 0 bytes inside data symbol "shared_var"
==62527== 
Expected value: 200
Actual value: 200
==62527== 
==62527== Use --history-level=approx or =none to gain increased speed, at
==62527== the cost of reduced accuracy of conflicting-access information
==62527== For lists of detected and suppressed errors, rerun with: -s
==62527== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)


如果我们把mutex部分去掉commnet
(base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ g++ race_condition.cpp -lpthread
(base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --tool=helgrind ./a.out
==62687== Helgrind, a thread error detector
==62687== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==62687== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==62687== Command: ./a.out
==62687== 
Expected value: 200
Actual value: 200
==62687== 
==62687== Use --history-level=approx or =none to gain increased speed, at
==62687== the cost of reduced accuracy of conflicting-access information
==62687== For lists of detected and suppressed errors, rerun with: -s
==62687== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 304 from 7)
*/

