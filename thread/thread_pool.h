#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <functional>


// Cоздаем thread_pool с указанием количества процессов
//
// Вызываем функцию add_task класса thread_pool, где первый аргумент - название void функции, 
// остальные - набор аргументов, от которых надо вызвать эту функцию
//
// P.S.
// Все пишется в отдельном блоке
// {
//     thread_pool tp(5);
//
//     tp.add_task(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
// }


class thread_pool {
    public:
        thread_pool(int threads_count);
        
        ~thread_pool();
        
        void add_task(std::function<void()> task);

        template<typename F, typename First, typename... Args>
        void add_task(F f, First first, Args... args){
            add_task(std::bind(f, first));
            add_task(f, args...);
        }
        
        template<typename F, typename Arg>
        void add_task(F f, Arg arg){
            add_task(std::bind(f, arg));
        }
        
    private:
    
        class Worker {

            thread_pool* owner;
            bool quit = false;
            
            std::thread thr;
        public:            
            Worker(thread_pool* owner);
            
            ~Worker();
            
            void work();
            
            void Quit();
        };
        
        std::mutex m;
        std::condition_variable v;
        std::queue<std::function<void()>> tasks;
        std::vector<std::unique_ptr<Worker>> threads;
};