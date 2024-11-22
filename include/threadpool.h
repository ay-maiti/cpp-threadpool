#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<functional>
#include<mutex>
#include<condition_variable>
#include<future>

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
                    while(true){
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(mtx);
                            cv.wait(lock, [this](){
                                return  !tasks.empty() || stop;
                            });
                            if(stop && tasks.empty()){
                                return;
                            }
                            task = std::move(tasks.front());
                            tasks.pop();
                        }
                        try{
                            task();
                        }
                        catch(const std::exception& e){
                            std::cerr<<"Task threw an exception: "<<e.what()<<"\n";
                        }
                        catch(...){
                            std::cerr<<"Task threw an unknown exception.\n";
                        }
                    }
                });
            }
        }
        template<class F, class... Args>
        auto executeTask(F&& func, Args&&... args)->std::future<decltype(func(args...))>{
            using return_type = decltype(func(args...));
            auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(mtx);
                tasks.emplace([task](){(*task)();});
            }
            cv.notify_one();
            return res;
        }
        ~ThreadPool(){
            {
                std::unique_lock<std::mutex> lock(mtx);
                stop = true;
            }
            cv.notify_all();
            for(auto &th: threads){
                th.join();
            }
        }
};