#include "thread_pool.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <functional>

thread_pool::thread_pool(int threads_count) {
    for (int i = 0; i < threads_count; ++i) {
        threads.push_back(
            std::make_unique<Worker>(this)
        );
    }
}
        
thread_pool::~thread_pool() {
    for(auto& w: threads){
        add_task(std::bind(&Worker::Quit, w.get()));
    }
}
        
void thread_pool::add_task(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> l(m);
        tasks.push(std::move(task));
    }
    v.notify_one();
}
        
                 
thread_pool::Worker::Worker(thread_pool* owner): owner(owner), thr(&Worker::work, this) {}
            
thread_pool::Worker::~Worker() {
    thr.join();
}
            
void thread_pool::Worker::work(){
    for (;!quit;) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> l(owner->m);
            owner->v.wait(l, [this]() {return !owner->tasks.empty();});
            task = std::move(owner->tasks.front());
            owner->tasks.pop();
        }
        task();
    }
}
            
void thread_pool::Worker::Quit(){
    quit = true;
}