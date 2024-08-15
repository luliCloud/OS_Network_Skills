#include <iostream>
#include <future>
#include <thread>
using namespace std;

future<string> async_read_file() {
    return async(launch::async, [] () {
        this_thread::sleep_for(chrono::seconds(2)); // mimic long time operation
        return string("File content");  // this is the future content, 
        // future is a template with string as data type
    });
}

int main() {
    auto future = async_read_file(); // initialize asynchronous ope
    cout << "Do other work while waiting for the file read" << endl;
    string content = future.get();
    cout << "File content: " << content << endl;
    return 0;
}
/**
 * Do other work while waiting for the file read
 * [... after 2 seconds ... ]
File content: File content
 */