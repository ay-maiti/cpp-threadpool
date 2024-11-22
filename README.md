# ThreadPool - A Simple C++ Thread Pool Implementation

This is a simple C++ implementation of a **ThreadPool** that allows you to run tasks asynchronously using a pool of worker threads. The thread pool is a common concurrency pattern used to efficiently manage a set of threads that can execute multiple tasks in parallel.

## Key Features:

- **Multithreading**: Manages multiple threads to execute tasks concurrently.
- **Task Scheduling**: Tasks are queued and executed by the available threads in the pool.
- **Graceful Shutdown**: Proper cleanup of threads once tasks are completed or when the pool is destroyed.
- **Customizable**: The number of threads in the pool can be set at the time of instantiation.

## Getting Started

To get started with this project, clone the repository and build the code using CMake. Below are the steps to set up and run the project:

### Prerequisites

- **C++17** or later
- **CMake** for building the project
- A C++ compiler such as **g++** or **MSVC** that supports C++17

### Clone the repository

```bash
git clone https://github.com/yourusername/threadpool.git
cd threadpool
```

### Building the project

1. Create a build directory:

```bash
mkdir build
cd build
```

2. Generate the build files using CMake:

```bash
cmake ..
```

3. Build the project:

```bash
cmake --build .
```

4. Run the executable:

```bash
./mlt  # On Linux/macOS
mlt.exe  # On Windows
```

### Example Usage

The code demonstrates how to use the ThreadPool class by creating a pool of 8 threads and executing 10 simple tasks. Below is the example code:

```cpp
#include <iostream>
#include <thread>
#include "threadpool.h"
#include <chrono>

void fun() {
    std::cout << "Just for fun\n";
}

int main() {
    ThreadPool t(8);  // Create a thread pool with 8 worker threads

    // Simulate task submission with a maximum number of tasks or some exit condition
    for (int i = 0; i < 10; ++i) {
        t.executeTask(fun);  // Submit a task to the thread pool
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Optional: Slow down task submission
    }

    return 0;
}

```

### How it works

- ThreadPool Initialization: When the ThreadPool object is created, a set number of threads are spawned (based on the argument passed to the constructor).
- Task Execution: Tasks are submitted to the pool using the executeTask method, where tasks are queued and picked up by the threads for execution.
- Graceful Shutdown: The destructor ensures that all threads are joined and properly cleaned up when the thread pool goes out of scope or is destroyed.

### Features To Add (Future Improvements)

This project will be updated gradually with the following features:

- Priority Queue for tasks
- Error handling and exceptions management
- Graceful exit with task completion tracking
- Unit tests for thread pool functionality
- Dynamic thread management based on task load
- Performance benchmarking
