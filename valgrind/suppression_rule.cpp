/**
 * 如何忽略valgrind报告中的某些错误
*/
#include <iostream>
using namespace std;

int* allcoateIncorrectlySizedMemory(int numElements, int elementSize) {
    // 假设elementSize是每个元素的实际大小（以字节为单位）
    // 但是这里的计算错误的假设numElements是以字节为单位的
    size_t totalSize = numElements * sizeof(int); // 正确的计算应该是 numEle * eleSize
    //// 十个字节就分配十个单位，这里分配了过多内存；
    // int* ptr = new int[totalSize]; // totalSize = 40, so allcoate 40 int -> 160 bytes

    int* ptr = (int*)new char[totalSize]; 
    // 或者正确的写法是 int* ptr = new int[numElements]
    return ptr;
}

int main() {
    int numElements = 10;
    int elementSize = 4; // 在64位操作系统，int大小为4
    int* incorrectMem = allcoateIncorrectlySizedMemory(numElements, elementSize);
    // using incorrectMem to operate
    // ...
    // release mem
    // delete[] incorrectMem;
    return 0;
}
/**
 * 1. 生成 Suppression 文件
通常，你可以让 Valgrind 在运行时自动生成 suppression 规则，这些规则将会匹配当前运行中产生的所有错误：

$ valgrind --gen-suppressions=all --leak-check=full --show-leak-kinds=all ./your_program
--gen-suppressions=all：告诉 Valgrind 为所有遇到的内存错误生成 suppression 规则。
--leak-check=full：启用详尽的内存泄漏检查。
--show-leak-kinds=all：显示所有类型的内存泄漏信息。
执行后，Valgrind 会输出错误报告，并为每个错误提供一个 suppression 块。这些块可以直接复制到你的 suppression 文件中。

比如我们执行这个cpp文件后：得到
(base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ valgrind --gen-suppressions=all --leak-check=full --show-l
eak-kinds=all ./a.out
==59917== Memcheck, a memory error detector
==59917== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==59917== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==59917== Command: ./a.out
==59917== 
==59917== 
==59917== HEAP SUMMARY:
==59917==     in use at exit: 40 bytes in 1 blocks
==59917==   total heap usage: 2 allocs, 1 frees, 72,744 bytes allocated
==59917== 
==59917== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==59917==    at 0x484A2F3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==59917==    by 0x1091B3: allcoateIncorrectlySizedMemory(int, int) (suppression_rule.cpp:14)
==59917==    by 0x1091E6: main (suppression_rule.cpp:22)
==59917== 
这里就是suppresion块
{
   <insert_a_suppression_name_here> 这里是应该输入一个描述性名称的地方，以帮助你识别这个suppression规则
   Memcheck:Leak  这个suppression是针对内存泄漏
   match-leak-kinds: definite  这表示suppression匹配definite类型的内存泄漏
   fun:_Znam 这意味着错误发生在调用_Znam函数过程中
   fun:_Z30allcoateIncorrectlySizedMemoryii  这意味着错误发生在调用 allocateIncorrectlySizeofMemory函数过程中
   fun:main 这意味着错误发生在调用main函数过程中
}
你可以修改这个suppresion规则，比如将首行命名为
suppression_rule_change
如果我们不关心由_Z30allcoateIncorrectlySizedMemoryii引起的错误，
我们可以将其他两个fun去掉（其他两个错误会被关注），而在suppresion中的规则是会被关注的
如果我们只关心由特定库文件引起的错误的错误，我们需要指定obj(add after fun)
obj: /usr/lib/libthirdparty.so 
这样我们会忽略从obj路径中_Z30allcoateIncorrectlySizedMemoryii产生的错误
然后我们可以将这个新的suppression规则复制到<name>.supp文件中
然后运行
valgrind --suppression=<name>.supp ./a.out
==59917== LEAK SUMMARY:
==59917==    definitely lost: 40 bytes in 1 blocks
==59917==    indirectly lost: 0 bytes in 0 blocks
==59917==      possibly lost: 0 bytes in 0 blocks
==59917==    still reachable: 0 bytes in 0 blocks
==59917==         suppressed: 0 bytes in 0 blocks
==59917== 
==59917== For lists of detected and suppressed errors, rerun with: -s
==59917== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/
