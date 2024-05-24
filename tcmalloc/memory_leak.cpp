/**
 * 内存泄漏： 忘记释放已分配的内存，或由于代码逻辑错误导致某些内存块无法被释放，从而造成内存泄漏
 * 长时间运行后，可能会耗尽系统资源。
 * 内存泄漏是一种常见的变成错误，通常发生在动态分配的内存没有被正确释放时。在C++中，如果忘记调用
 * delete 或者delete[]来释放通过new或者new[]分配的内存时，就会导致内存泄漏。一下是一个简单的
 * C++例子，展示了如何因为忘记释放内存造成的内存泄漏
*/
#include <iostream>
#include <vector>
using namespace std;

class LeakyClass {
public:
    LeakyClass() {
        // suppose we dynamically allocate some memeory here
        data = new int[100];
        cout << "Allocate memory for LeakyClass instance" << endl;
    }

    ~LeakyClass() {
        // generally, we should release memory allcoated dynamically
        // however, in this case, we intentionally comment out the releasing code
        delete[] data;  // 这一句必须要写。即使我们在main里delete了所有obj。也需要写正确的析构函数
        cout << "Destroyed LeakyClass instance (Memory was NOT freed)." << endl;
    }
private:
    int* data;
};

int main() {
    // create a vector to store LeakyClass obj pointer
    vector<LeakyClass*> leakyObjects;
    // create LeakyClass instances and push them to vector in the iterations
    for (int i= 0; i < 1000; i++) {
        leakyObjects.push_back(new LeakyClass());
    }
    // 这一句必须要写，任何new都要对应delete
    for (auto ob : leakyObjects) {
        delete ob;
    }

    leakyObjects.clear(); // 这一句可以不写，vector会复杂帮你清空向量。

    // here, we intentionally not release what stored in the vector
    // this will lead to memory leak, as memeory obtained by every LeakyClass instance
    // has not been released.
    return 0; 
}
/**
 * 在这个例子中，我们创建了一个LeakyClass，它在构造函数中分配了一个动态数组。但在析构函数中故意没有释放
 * 这个数组。然后我们在卖弄函数中创建了一个包含1000个LeakyClass实力指针的vector实例指针的vector。
 * 由于我们忘记了在程序结束前释放这些实例，因此发生了内存泄漏。随着时间推移，如果程序持续运行并不断创建新的
 * LeakyClass实例而不释放，最终会耗尽系统资源，导致程序崩溃或程序变得不稳定。
 * 为了避免内存泄漏：我们应该确保每个通过new或new[]分配的内存块最终都被delete或者delete[]释放。
 * 使用指针指针，来自动管理内存的生命周期。
 * 定期检查代码以寻找潜在的内存泄口。并使用内存泄漏检测工具来帮助识别问题。
 * 在对象的析构函数中确保释放所有由该对象分配的资源
 * 避免在全局或静态变量的构造函数和析构函数中分配和释放内存，因为这可能导致难以调试的问题，特鄙视在程序
 * 启动和结束时。
*/