#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t lock1, lock2;

void* thread1_function(void* arg) {
    pthread_mutex_lock(&lock1);
    cout << "Thread 1 has acquired lock 1, sleeping..." << endl;
    sleep(1); // sleep to ensure that thread2 can lock thread2

    cout << "Thread 1 attempting to acquire lock 2 ..." << endl;
    pthread_mutex_lock(&lock2);

    cout << "Thread 1 has lock 1 and lock 2" << endl;

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

void* thread2_function(void* arg) {
    pthread_mutex_lock(&lock2);
    cout << "Thread 2 has acquired lock 2, sleeping..." << endl;
    sleep(1); // sleep to ensure that thread1 can lock thread2

    cout << "Thread 2 attempting to acquire lock 1 ..." << endl;
    pthread_mutex_lock(&lock1);

    cout << "Thread 2 has lock 2 and lock 1" << endl;

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1_function, NULL);
    pthread_create(&t2, NULL, thread2_function, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    cout << "Finished" << endl;
    return 0;
}
/**
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --tool=helgrind ./a.out
==60845== Helgrind, a thread error detector
==60845== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==60845== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==60845== Command: ./a.out
==60845== 
Thread 1 has acquired lock 1, sleeping...
==60845== ---Thread-Announcement------------------------------------------
==60845== 
==60845== Thread #3 was created
==60845==    at 0x4BC89F3: clone (clone.S:76)
==60845==    by 0x4BC98EE: __clone_internal (clone-internal.c:83)
==60845==    by 0x4B376D8: create_thread (pthread_create.c:295)
==60845==    by 0x4B381FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==60845==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094E1: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845== 
==60845== ---Thread-Announcement------------------------------------------
==60845== 
==60845== Thread #2 was created
==60845==    at 0x4BC89F3: clone (clone.S:76)
==60845==    by 0x4BC98EE: __clone_internal (clone-internal.c:83)
==60845==    by 0x4B376D8: create_thread (pthread_create.c:295)
==60845==    by 0x4B381FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)
==60845==    by 0x4853767: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094C4: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
关键信息：这里指出了可能在那些代码行出现死锁错误（Possible data race during）
==60845== Possible data race during read of size 8 at 0x10C058 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3A22: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093BE: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 8 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092E0: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x10c058 is 24 bytes inside data symbol "_ZSt4cout@GLIBCXX_3.4"
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
关键信息
==60845== Possible data race during write of size 1 at 0x4DE9E08 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x4859796: mempcpy (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B2E664: _IO_new_file_xsputn (fileops.c:1235)
==60845==    by 0x4B2E664: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==60845==    by 0x4B22FD6: fwrite (iofwrite.c:39)
==60845==    by 0x49B3B64: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093BE: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x4de9e08 is 40 bytes inside a block of size 1,024 alloc'd
==60845==    at 0x484A919: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B21BA3: _IO_file_doallocate (filedoalloc.c:101)
==60845==    by 0x4B30CDF: _IO_doallocbuf (genops.c:347)
==60845==    by 0x4B2FF5F: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:744)
==60845==    by 0x4B2E6D4: _IO_new_file_xsputn (fileops.c:1243)
==60845==    by 0x4B2E6D4: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==60845==    by 0x4B22FD6: fwrite (iofwrite.c:39)
==60845==    by 0x49B3B64: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092E0: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Block was alloc'd by thread #2
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during write of size 8 at 0x10C058 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093BE: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 8 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092E0: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x10c058 is 24 bytes inside data symbol "_ZSt4cout@GLIBCXX_3.4"
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during read of size 1 at 0x4AA17F8 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B37FE: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093D0: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 1 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x494DFBC: std::ctype<char>::_M_widen_init() const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B382F: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092F2: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x4aa17f8 is in the BSS segment of /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during read of size 1 at 0x4AA1803 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3807: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093D0: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 2 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x494DEE1: std::ctype<char>::_M_widen_init() const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B382F: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092F2: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x4aa1803 is in the BSS segment of /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
==60845== 
Thread 2 has acquired lock 2, sleeping...
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845== Possible data race during read of size 8 at 0x10C058 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x49B3A22: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x109315: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 8 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093BE: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x10c058 is 24 bytes inside data symbol "_ZSt4cout@GLIBCXX_3.4"
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845== Possible data race during write of size 8 at 0x10C058 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x109315: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 8 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093BE: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x10c058 is 24 bytes inside data symbol "_ZSt4cout@GLIBCXX_3.4"
==60845== 
Thread 1 attempting to acquire lock 2 ...
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during read of size 8 at 0x10C058 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3A22: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093F3: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 8 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092E0: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x10c058 is 24 bytes inside data symbol "_ZSt4cout@GLIBCXX_3.4"
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during write of size 8 at 0x10C058 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1093F3: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 8 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x49B3AE0: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B3EBA: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092E0: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x10c058 is 24 bytes inside data symbol "_ZSt4cout@GLIBCXX_3.4"
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during read of size 1 at 0x4AA17F8 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B37FE: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x109405: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 1 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x494DFBC: std::ctype<char>::_M_widen_init() const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B382F: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092F2: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x4aa17f8 is in the BSS segment of /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845==  Lock at 0x10C1A0 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094A7: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c1a0 is 0 bytes inside data symbol "lock2"
==60845== 
==60845==  Lock at 0x10C160 was first observed
==60845==    at 0x4854BFE: pthread_mutex_init (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109493: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==  Address 0x10c160 is 0 bytes inside data symbol "lock1"
==60845== 
==60845== Possible data race during read of size 1 at 0x4AA1803 by thread #3
==60845== Locks held: 1, at address 0x10C1A0
==60845==    at 0x49B3807: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x109405: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== This conflicts with a previous write of size 2 by thread #2
==60845== Locks held: 1, at address 0x10C160
==60845==    at 0x494DEE1: std::ctype<char>::_M_widen_init() const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x49B382F: std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==60845==    by 0x1092F2: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845==  Address 0x4aa1803 is in the BSS segment of /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
==60845== 
Thread 2 attempting to acquire lock 1 ...
^C==60845== 
==60845== Process terminating with default action of signal 2 (SIGINT)
==60845==    at 0x4B34117: __futex_abstimed_wait_common64 (futex-internal.c:57)
==60845==    by 0x4B34117: __futex_abstimed_wait_common (futex-internal.c:87)
==60845==    by 0x4B34117: __futex_abstimed_wait_cancelable64 (futex-internal.c:139)
==60845==    by 0x4B39623: __pthread_clockjoin_ex (pthread_join_common.c:105)
==60845==    by 0x48508F5: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x1094F2: main (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845== ----------------------------------------------------------------
==60845== 
==60845== Thread #2: Exiting thread still holds 1 lock
==60845==    at 0x4B342C0: futex_wait (futex-internal.h:146)
==60845==    by 0x4B342C0: __lll_lock_wait (lowlevellock.c:49)
==60845==    by 0x4B3B001: lll_mutex_lock_optimized (pthread_mutex_lock.c:48)
==60845==    by 0x4B3B001: pthread_mutex_lock@@GLIBC_2.2.5 (pthread_mutex_lock.c:93)
==60845==    by 0x4850C66: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109336: thread1_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== ----------------------------------------------------------------
==60845== 
==60845== Thread #3: Exiting thread still holds 1 lock
==60845==    at 0x4B342C0: futex_wait (futex-internal.h:146)
==60845==    by 0x4B342C0: __lll_lock_wait (lowlevellock.c:49)
==60845==    by 0x4B3B001: lll_mutex_lock_optimized (pthread_mutex_lock.c:48)
==60845==    by 0x4B3B001: pthread_mutex_lock@@GLIBC_2.2.5 (pthread_mutex_lock.c:93)
==60845==    by 0x4850C66: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x109414: thread2_function(void*) (in /home/lu/greenpear/OSlearn/valgrind/a.out)
==60845==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==60845==    by 0x4B37AC2: start_thread (pthread_create.c:442)
==60845==    by 0x4BC8A03: clone (clone.S:100)
==60845== 
==60845== 
==60845== Use --history-level=approx or =none to gain increased speed, at
==60845== the cost of reduced accuracy of conflicting-access information
==60845== For lists of detected and suppressed errors, rerun with: -s
==60845== ERROR SUMMARY: 135 errors from 13 contexts (suppressed: 59 from 33)
ctrl + c
(base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ 
*/