#pragma once
#ifndef CPP_TOOLS_MULTITHREAD_H
#define CPP_TOOLS_MULTITHREAD_H

#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#define eazy_multithread_functions(code_block, should_join) \
    { \
        eazy_start_multithread_functions([&]() { \
            code_block \
        }, should_join); \
    }


template<typename Func>
void eazy_start_multithread_functions(Func func, bool should_join) {
    std::thread thread_obj(func);

    if (should_join) {
        thread_obj.join();
    } else {
        thread_obj.detach();
    }
}

//template<typename Func>
//void multithread_functions(const std::vector<Func> &funcs, bool should_join) {
//    std::vector<std::thread> threads;
//
//    for (const auto &func: funcs) {
//        threads.emplace_back(func);
//    }
//
//    for (auto &thread: threads) {
//        if (should_join) {
//            thread.join();
//        } else {
//            thread.detach();
//        }
//    }
//}
//
//template<typename... Funcs>
//void complex_multithread_functions(bool isJoin, bool multithread, Funcs... funcs) {
//    if (multithread) {
//        std::vector<std::function<void()>> func_list = {funcs...};
//        multithread_functions(func_list, isJoin); // 使用 thread_join = true
//    } else {
//        (funcs(), ...); // 依次执行传入的函数
//    }
//}


// 使用案例
//std::vector<std::function<void()>> test = {
//        []() {
//            std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 1 << std::endl;
//        },
//        []() {
//            std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 2 << std::endl;
//        },
//        []() {
//            std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 3 << std::endl;
//        },
//        []() {
//            std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 4 << std::endl;
//        }
//};


#define get_function_running_time(code_block) \
    { \
        get_function_run_time([&]() { \
            code_block \
        }); \
    }

template<typename Func>
void get_function_run_time(Func func) {

    auto startTime = std::chrono::high_resolution_clock::now();

    func();
    auto endTime = std::chrono::high_resolution_clock::now();
    // 计算时间间隔
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "函数" << "的执行时间: " << duration.count() << "ms" << std::endl;
}

#endif
