#include <unistd.h>  // For sleep function

#include <iostream>

#include "threadpool.h"  // Include your thread pool header

class MyTask {
public:
    MyTask(int id) : task_id(id) {}

    void process() {
        std::cout << "Task " << task_id << " is being processed by thread " << pthread_self() << std::endl;
        sleep(1);  // Simulate some work
    }

private:
    int task_id;
};

int main() {
    threadpool<MyTask> pool(4, 2);  // Create a thread pool with 4 threads and max 10 requests

    for (int i = 0; i < 20; ++i) {
        MyTask* task = new MyTask(i);
        if (!pool.append(task)) {
            std::cout << "Task " << i << " was rejected due to full queue." << std::endl;
        }
    }

    sleep(5);  // Allow some time for tasks to be processed

    return 0;
}
