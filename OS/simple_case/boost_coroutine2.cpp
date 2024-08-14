/** stack saving and restoring 
 * 在更低层次的实现中，协程可以通过手动保存和恢复堆栈的方式实现。这种方法更复杂，通常需要操作汇编语言或特定的平台 API。
 * 
 * compile:
 * g++ boost_coroutine2.cpp -lboost_context -lboost_coroutine
-lboost_context：链接 Boost.Context 库，这个库是 boost::coroutine2 的一个依赖。
-lboost_coroutine：链接 Boost.Coroutine 库。

*/
#include <iostream>
#include <boost/coroutine2/all.hpp>
using namespace std;

void coroutine_example(boost::coroutines2::coroutine<void>::pull_type& source) {
    /** coroutine<void> 是一个模版类，用于定义协程的类型。void表示协程没有返回值。模版类有两个主要嵌套类型：pull & push-type
     * &source 指向需要拉去或者推送的协程。
     * pull-type：表示协程的一端，允许从协程中拉取控制权。每次pull type的对象被调用时，协程江执行到下一个source。然后暂停并返回
     * 控制权给pull type。注意这个函数的执行就是一个协程
     * push-type：表示协程的另一端，向协程中推送数据或控制权。当push type的对象被调用时，会将控制权推送到协程的主体部分，开始或继续执行
     */
    cout << "Step 1" << endl;
    source(); // 暂停协程，等待恢复
    cout << "Step 2" << endl;
    source();
    cout << "Step 3" << endl;
}

int main() {
    // sink对象在主程序中控制协程的执行。每次调用sink，协程将从上次暂停的地方继续执行。
    boost::coroutines2::coroutine<void>::push_type sink(coroutine_example);
    sink(); // 开始协程，执行到第一个source
    sink(); // 从第一个source恢复协程，执行到第二个source
    sink(); // 从第二个source恢复，执行完协程
    return 0;
}