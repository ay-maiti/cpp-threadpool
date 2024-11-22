#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<functional>
#include<mutex>
#include<condition_variable>

class ThreadPool{
    private:
        int numThreads;
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        bool stop;
        std::mutex mtx;
        std::condition_variable cv;
    public:
        ThreadPool(int numThreads):numThreads(numThreads), stop(false){
            for(int i=0; i<numThreads; i++){
                threads.emplace_back([this]{
                    std::function<void()> task;
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this](){
                        return  !tasks.empty() || stop;
                    });
                    if(stop && tasks.empty()){
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();
                    task();
                });
            }
        }
        void executeTask(std::function<void()> task){
            {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.push(task);
            }
            cv.notify_one();
        }
        ~ThreadPool(){
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
            lock.unlock();
            cv.notify_all();
            for(auto &th: threads){
                th.join();
            }
        }
};