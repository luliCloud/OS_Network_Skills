/** an example showing allocate memory using char* */
#include <iostream>
#include <gperftools/tcmalloc.h>
// #include <tcmalloc.h>
#include <string.h>
using namespace std;

int main() {
    // initialize tcmalloc
    // tc_init();  // may include in the tcmalloc.h, we don't have this header file
    // using TCMalloc allocating mem
    char* str = (char*)tc_malloc(10 * sizeof(char));
    if (str != nullptr) {
        strcpy(str, "Hello TCMalloc");
        /**
         * 这里分配给 str 的内存只有 10 个字符的空间，但是使用 strcpy() 函数
         * 来复制 "Hello TCMalloc" 这个字符串时，
         * 实际上复制了超过 10 个字符（实际为 15 个字符加上结尾的 null 字符），这导致了缓冲区溢出。
        */
        cout << str << endl;
        tc_free(str);
    } else {
        cerr << "Memory allocation failed!" << endl;
    }

    // tc_finalize(); // optional
    
    return 0;
}