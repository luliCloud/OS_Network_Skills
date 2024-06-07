/**
 * 错误的内存分配大小：请求的内存大小的计算错误，可能导致分配不足或过多，浪费资源或引发溢出。
 * 错误的分配内存大小通常发生在动态内存分配时，比如使用new或者malloc。如果分配的大小计算错误，
 * 可能会导致分配的内存块太小（无法满足需求）或太大（浪费资源）。
*/
#include <iostream>
using namespace std;

int* allcoateIncorrectlySizedMemory(int numElements, int elementSize) {
    // 假设elementSize是每个元素的实际大小（以字节为单位）
    // 但是这里的计算错误的假设numElements是以字节为单位的
    size_t totalSize = numElements * sizeof(int); // 正确的计算应该是 numEle * eleSize
    int* ptr = (int*)new char[totalSize]; // 十个字节就分配十个单位，这里分配了过多内存；
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
    delete[] incorrectMem;
    return 0;
}