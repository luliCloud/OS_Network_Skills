#include <iostream>
#include <gperftools/tcmalloc.h>
#include <gperftools/malloc_extension.h>
#include <gperftools/heap-checker.h>
#include <cstdlib> // for setenv
using namespace std;
/** using MallocExtension to check */
void malloc_extension_supervise() {
    void* ptr1 = tc_malloc(128);
    void* ptr2 = tc_malloc(256);

    // if we add ptr3 here, will the thread heap increase to 3?
    cout << "adding ptr3 here" << endl;
    void* ptr3 = tc_malloc(512);
    /**
     * 根据stats，不管我们开启一个tc_malloc()还是三个，thread heap都是两个。因此所有
     * tc_malloc开启的新内存理论上都是在main这个线程上复用thread cache， 而不是开辟了
     * 自己的新cache。但是span数量貌似和tc_malloc()的数量成正比。
     * 如何开启新线程:
     * void* ptr = tc_malloc(100);
     * thread t(ptr);  // thread receive a ptr or lambda func
     * t.join();  // don't terminate the main thread until t finish its program
     * tc_free(ptr);
    */

    // obtain memory stats
    size_t buff_size = 1024 * 1024; // large enough. 这里跟application bytes use 相对
    // 1024*1024-> 1.1MB inuse
    // 1024*10240 -> 10.1MB inuse
    char* buffer = new char[buff_size];
    MallocExtension::instance()->GetStats(buffer, buff_size);
    cout << "Current TCMalloc stats: \n" << buffer << endl;
    tc_free(ptr1);
    tc_free(ptr2);
    tc_free(ptr3);
}

int main(int argc, char** argv) {
    malloc_extension_supervise();
    /* using Heap checker to check */
    // set HEAPCHECK env variable
    setenv("HEAPCHECK", "normal", 1);
    HeapLeakChecker heap_checker("main");
    void* ptr1 = tc_malloc(512);
    void* ptr2 = tc_malloc(128);

    // intense to not release ptr2 to mimic memory lead
    tc_free(ptr1);
    if (!heap_checker.NoLeaks()) {
        cerr << "Memory lead detected!" << endl;
    }
    return 0;
}
/**
 * MallocExtension:
 * Current TCMalloc stats: 
------------------------------------------------
MALLOC:        1123256 (    1.1 MiB) Bytes in use by application
MALLOC: +       917504 (    0.9 MiB) Bytes in page heap freelist
MALLOC: +        56280 (    0.1 MiB) Bytes in central cache freelist
MALLOC: +            0 (    0.0 MiB) Bytes in transfer cache freelist
MALLOC: +          112 (    0.0 MiB) Bytes in thread cache freelists
MALLOC: +      2621440 (    2.5 MiB) Bytes in malloc metadata
MALLOC:   ------------
MALLOC: =      4718592 (    4.5 MiB) Actual memory used (physical + swap)
MALLOC: +            0 (    0.0 MiB) Bytes released to OS (aka unmapped)
MALLOC:   ------------
MALLOC: =      4718592 (    4.5 MiB) Virtual address space used
MALLOC:
MALLOC:             12              Spans in use
MALLOC:              2              Thread heaps in use
MALLOC:           8192              Tcmalloc page size
------------------------------------------------
Call ReleaseFreeMemory() to release freelist memory to the OS (via madvise()).
Bytes released to the OS take up virtual address space but no physical memory.
------------------------------------------------
Total size of freelists for per-thread caches,
transfer cache, and central cache, by size class
------------------------------------------------
class   1 [        8 bytes ] :     1023 objs;   0.0 MiB;   0.0 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
class   2 [       16 bytes ] :      511 objs;   0.0 MiB;   0.0 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
class   3 [       32 bytes ] :      252 objs;   0.0 MiB;   0.0 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
class   4 [       48 bytes ] :      170 objs;   0.0 MiB;   0.0 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
class   9 [      128 bytes ] :       63 objs;   0.0 MiB;   0.0 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
class  17 [      256 bytes ] :       31 objs;   0.0 MiB;   0.0 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
class  22 [      416 bytes ] :       18 objs;   0.0 MiB;   0.1 cum MiB;    0.000 overhead MiB;    0.000 cum overhead MiB
------------------------------------------------
PageHeap: 1 sizes;    0.9 MiB free;    0.0 MiB unmapped
------------------------------------------------
   112 pages *      1 spans ~    0.9 MiB;    0.9 MiB cum; unmapped:    0.0 MiB;    0.0 MiB cum
>128   large *      0 spans ~    0.0 MiB;    0.9 MiB cum; unmapped:    0.0 MiB;    0.0 MiB cum

HEAPCHECK
$ export HEAPCHECK=normal
$ ./a.out
Have memory regions w/o callers: might report false leaks
No leaks found for check "main" (but no 100% guarantee that there aren't any): found 19 reachable heap objects of 1123101 bytes
Have memory regions w/o callers: might report false leaks
Leak check _main_ detected leaks of 1048576 bytes in 1 objects
The 1 largest leaks:
*** WARNING: Cannot convert addresses to symbols in output below.
*** Reason: Cannot find 'pprof' (is PPROF_PATH set correctly?)
*** If you cannot fix this, try running pprof directly.
Leak of 1048576 bytes in 1 objects allocated from:
        @ 5acfbc86d325 
        @ 5acfbc86d3c9 
        @ 71b92d429d90 
        @ 71b92d429e40 
        @ 5acfbc86d225 


If the preceding stack traces are not enough to find the leaks, try running THIS shell command:

pprof ./a.out "/tmp/a.out.3789._main_-end.heap" --inuse_objects --lines --heapcheck  --edgefraction=1e-10 --nodefraction=1e-10 --gv

If you are still puzzled about why the leaks are there, try rerunning this program with HEAP_CHECK_TEST_POINTER_ALIGNMENT=1 and/or with HEAP_CHECK_MAX_POINTER_OFFSET=-1
If the leak report occurs in a small fraction of runs, try running with TCMALLOC_MAX_FREE_QUEUE_SIZE of few hundred MB or with TCMALLOC_RECLAIM_MEMORY=false, it might help find leaks more repeatabl
Exiting with error code (instead of crashing) because of whole-program memory leaks
*/