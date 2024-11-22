#include <iostream>
#include <thread>
#include "..\include\threadpool.h"
#include <chrono>

void fun(){
    std::cout << "Just for fun\n";
}

int main() {
    ThreadPool t(8);
    
    // Simulate task submission with a maximum number of tasks or some exit condition
    for (int i = 0; i < 10; ++i) { // Example: Submit 10 tasks
        t.executeTask(fun);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Optional: Slow down task submission
    }

    // Optional: Graceful exit mechanism after tasks are done (if needed)
    // Could add more logic here to shut down the thread pool gracefully.
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait for tasks to finish before exiting

    return 0;
}
