#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/**
 *errno 是一个全局变量，用来存储最近一次发生错误时的错误代码。
它在标准库 <errno.h> 中定义，几乎所有系统调用（如 stat()）或者库函数在发生错误时都会设errno。
当 stat() 函数执行失败时，它会将错误代码存储在 errno 中，
例如文件未找到可能会设置为 ENOENT，权限不足可能会设置为 EACCES。
strerror(errno) 解释错误代码
strerror() 函数用于将 errno 中存储的错误代码转换为对应的错误描述字符串。
例如，如果 errno 的值是 ENOENT（代表文件不存在），strerror(ENOENT) 会返回 "No such file or directory" 这样的错误描述字符串。
*/

int main () {
    // sys/stat.h manual
    // https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
    struct stat buff;
    // int stat(const char *path, struct stat *buf);
    int r = stat("myfile", &buff);  // noting here is &, not buff

    if (r != 0) {
        printf("The the error is: %d, %s\n", r, strerror(errno));
    } else {
        printf("Works well %d\n", r);
    }
    

    return 0;
}