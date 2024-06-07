/**
 * 数组越界：访问数组的索引超出了其实际中小，是一个常见的编程错误，
 * 它发生在尝试访问数组的一个不存在的索引时。可能会损坏其他内存区域的数据。
*/
#include <iostream>
using namespace std;

void arrayBoundsViolation() {
    int array[5] = {1, 2, 3, 4, 5}; 
    for (int i = 0; i < 10; i++) {
        cout << "Element at index" << i << ": " << array[i] << endl; 
    }
}

int main() {
    arrayBoundsViolation();
    return 0;
}
/**
 * 在这个例子中，我们创建了一个包含5个元素的整数数组array。然后，我们用一个循环来尝试访问索引从0
 * 到10的元素，但是数组的有效索引范围是从0到4。因此，当i的值超过4时，我们就在访问数组界限之外的内存，
 * 这会导致未定义行为，可能损坏内存中的其他数据。
 * 如果你使用valgrind来运行这个程序，并启用内存检查工具
 * 
 * Element at index0: 1
Element at index1: 2
Element at index2: 3
Element at index3: 4
Element at index4: 5

==46077== Conditional jump or move depends on uninitialised value(s)
==46077==    at 0x499CA4E: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x49AB119: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x109283: arrayBoundsViolation() (boundsViolation.cpp:11)
==46077==    by 0x1092C3: main (boundsViolation.cpp:16)
==46077== 
关键信息：这里我跟老师的有不同。错误消息表明
这一行说明程序中存在对一个尺寸为8字节（在64位系统中通常指一个指针或某些类型的整数，
如 long）的未初始化值的使用。使用未初始化的变量可以导致不可预测的行为，因为它们的值是未定义的。
这些行描述了错误发生时程序调用堆栈中的函数。错误发生在 C++ 标准库的一部分中，
涉及到 std::ostream 和数字的插入操作。
具体来说，错误发生在尝试将一个 long 类型的值插入到输出流中。由于这个值未初始化，因此触发了错误报告。
==46077== Use of uninitialised value of size 8
==46077==    at 0x499C92B: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x499CA78: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x49AB119: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x109283: arrayBoundsViolation() (boundsViolation.cpp:11)
==46077==    by 0x1092C3: main (boundsViolation.cpp:16)
==46077== 
==46077== Conditional jump or move depends on uninitialised value(s)
==46077==    at 0x499C93D: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x499CA78: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x49AB119: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x109283: arrayBoundsViolation() (boundsViolation.cpp:11)
==46077==    by 0x1092C3: main (boundsViolation.cpp:16)
==46077== 
==46077== Conditional jump or move depends on uninitialised value(s)
==46077==    at 0x499CAAE: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x49AB119: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==46077==    by 0x109283: arrayBoundsViolation() (boundsViolation.cpp:11)
==46077==    by 0x1092C3: main (boundsViolation.cpp:16)
==46077== 
Element at index5: 0
Element at index6: 175024896
Element at index7: 1874095466
Element at index8: -16777904
Element at index9: 31
==46077== 
==46077== HEAP SUMMARY:
==46077==     in use at exit: 0 bytes in 0 blocks
==46077==   total heap usage: 2 allocs, 2 frees, 73,728 bytes allocated
==46077== 
==46077== All heap blocks were freed -- no leaks are possible
==46077== 
==46077== Use --track-origins=yes to see where uninitialised values come from
==46077== For lists of detected and suppressed errors, rerun with: -s
==46077== ERROR SUMMARY: 4 errors from 4 contexts (suppressed: 0 from 0)
请注意，数组越界可能导致程序崩溃，数据损坏或者其他不可预测的行为。为了避免数组越界，应该始终确保
你的代码只访问数组的有效索引。你可以使用循环边界检查，静态分析工具或现代C++特性（如范围基础的for
循环或vector）来帮助防止这类错误。
*/