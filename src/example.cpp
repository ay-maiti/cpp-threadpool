#include <iostream>
#include <thread>
#include <vector>
#include "..\include\threadpool.h"

int add(int a, int b) {
    return a + b;
}

int main() {
    ThreadPool t(8);

    std::vector<std::future<int>> results;

    for (int i = 0; i < 100; ++i) { // Limit to 100 iterations
        results.emplace_back(t.executeTask(add, i, i + 1));
    }

    for (auto& result : results) {
        std::cout << "Result is " << result.get() << "\n";
    }

    return 0;
}
