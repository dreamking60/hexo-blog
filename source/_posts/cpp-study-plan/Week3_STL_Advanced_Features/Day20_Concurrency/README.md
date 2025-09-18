---
title: C++ 学习计划 - 第三周第20天:并发编程基础
date: 2025-09-16 20:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
    - Concurrency
    - Multithreading
layout: page
menu_id: plan
permalink: /plan/week3/day20/
---

# 第20天：并发编程基础

## 学习目标
掌握C++11引入的并发编程特性，理解线程、同步机制和异步编程，学会编写线程安全的代码。

## 核心知识点

### 1. 并发编程概述

#### 为什么需要并发编程？
- **性能提升**：利用多核处理器
- **响应性**：避免阻塞主线程
- **资源利用**：提高系统资源利用率
- **用户体验**：提供更好的交互体验

#### 并发 vs 并行
- **并发 (Concurrency)**：同时处理多个任务，可能在单核上通过时间片轮转
- **并行 (Parallelism)**：真正同时执行多个任务，需要多核支持

#### 参考资料
- [C++ 并发编程 - cppreference.com](https://en.cppreference.com/w/cpp/thread)
- [C++ 并发编程详解](https://changkun.de/modern-cpp/zh-cn/07-thread/)

### 2. std::thread

`std::thread`是C++11引入的线程类，用于创建和管理线程。

#### 基本线程创建
```cpp
#include <iostream>
#include <thread>
#include <chrono>

void threadFunction() {
    std::cout << "线程ID: " << std::this_thread::get_id() << std::endl;
    std::cout << "Hello from thread!" << std::endl;
}

void basicThreadExample() {
    std::cout << "主线程ID: " << std::this_thread::get_id() << std::endl;
    
    // 创建线程
    std::thread t(threadFunction);
    
    // 等待线程完成
    t.join();
    
    std::cout << "线程已完成" << std::endl;
}
```

#### 带参数的线程
```cpp
void threadWithParams(int id, const std::string& message) {
    std::cout << "线程 " << id << ": " << message << std::endl;
}

void parameterizedThreadExample() {
    // 创建带参数的线程
    std::thread t1(threadWithParams, 1, "Hello");
    std::thread t2(threadWithParams, 2, "World");
    
    t1.join();
    t2.join();
}
```

#### Lambda表达式与线程
```cpp
void lambdaThreadExample() {
    std::vector<std::thread> threads;
    
    // 使用Lambda表达式创建线程
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i]() {
            std::cout << "线程 " << i << " 正在运行" << std::endl;
        });
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
}
```

#### 参考资料
- [std::thread - cppreference.com](https://en.cppreference.com/w/cpp/thread/thread)
- [C++ std::thread详解](https://blog.csdn.net/weixin_43914604/article/details/105295000)

### 3. 线程同步

#### std::mutex

`std::mutex`用于保护共享资源，确保同一时间只有一个线程可以访问。

```cpp
#include <mutex>
#include <vector>

class Counter {
private:
    int count = 0;
    mutable std::mutex mtx;
    
public:
    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
    }
    
    int getCount() const {
        std::lock_guard<std::mutex> lock(mtx);
        return count;
    }
};

void mutexExample() {
    Counter counter;
    std::vector<std::thread> threads;
    
    // 创建多个线程同时修改计数器
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 1000; ++j) {
                counter.increment();
            }
        });
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "最终计数: " << counter.getCount() << std::endl;
}
```

#### std::lock_guard 和 std::unique_lock

```cpp
class SafeVector {
private:
    std::vector<int> data;
    mutable std::mutex mtx;
    
public:
    void add(int value) {
        std::lock_guard<std::mutex> lock(mtx);  // 自动管理锁
        data.push_back(value);
    }
    
    // 使用unique_lock进行更复杂的锁定
    void complexOperation() {
        std::unique_lock<std::mutex> lock(mtx);
        
        // 执行一些操作
        if (!data.empty()) {
            int sum = 0;
            for (int value : data) {
                sum += value;
            }
            std::cout << "总和: " << sum << std::endl;
        }
        
        // 可以手动解锁
        lock.unlock();
        
        // 执行不需要锁的操作
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
};
```

#### 参考资料
- [std::mutex - cppreference.com](https://en.cppreference.com/w/cpp/thread/mutex)
- [std::lock_guard - cppreference.com](https://en.cppreference.com/w/cpp/thread/lock_guard)

#### std::condition_variable

`std::condition_variable`用于线程间的条件同步。

```cpp
#include <condition_variable>
#include <queue>

class ThreadSafeQueue {
private:
    std::queue<int> queue;
    mutable std::mutex mtx;
    std::condition_variable cv;
    
public:
    void push(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(value);
        cv.notify_one();  // 通知等待的线程
    }
    
    int pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty(); });  // 等待条件满足
        
        int value = queue.front();
        queue.pop();
        return value;
    }
    
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }
};

void conditionVariableExample() {
    ThreadSafeQueue queue;
    
    // 生产者线程
    std::thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            queue.push(i);
            std::cout << "生产: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    
    // 消费者线程
    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            int value = queue.pop();
            std::cout << "消费: " << value << std::endl;
        }
    });
    
    producer.join();
    consumer.join();
}
```

#### 参考资料
- [std::condition_variable - cppreference.com](https://en.cppreference.com/w/cpp/thread/condition_variable)
- [生产者消费者模式详解](https://www.cnblogs.com/skyfsm/p/7050949.html)

### 4. 原子操作

`std::atomic`提供原子操作，无需锁即可保证线程安全。

#### 基本原子类型
```cpp
#include <atomic>

class AtomicCounter {
private:
    std::atomic<int> count{0};
    
public:
    void increment() {
        ++count;  // 原子操作
    }
    
    int getCount() const {
        return count.load();  // 原子读取
    }
    
    void setCount(int value) {
        count.store(value);  // 原子写入
    }
    
    // 比较并交换
    bool compareAndSwap(int expected, int desired) {
        return count.compare_exchange_strong(expected, desired);
    }
};

void atomicExample() {
    AtomicCounter counter;
    std::vector<std::thread> threads;
    
    // 创建多个线程同时修改原子计数器
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 1000; ++j) {
                counter.increment();
            }
        });
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "原子计数器最终值: " << counter.getCount() << std::endl;
}
```

#### 内存序 (Memory Order)
```cpp
std::atomic<bool> ready{false};
std::atomic<int> data{0};

void producer() {
    data.store(42, std::memory_order_relaxed);
    ready.store(true, std::memory_order_release);  // 释放语义
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) {  // 获取语义
        std::this_thread::yield();
    }
    std::cout << "Data: " << data.load(std::memory_order_relaxed) << std::endl;
}
```

#### 参考资料
- [std::atomic - cppreference.com](https://en.cppreference.com/w/cpp/atomic/atomic)
- [原子操作和内存模型](https://www.cnblogs.com/skyfsm/p/7050950.html)

### 5. 异步编程

#### std::async

`std::async`用于异步执行函数，返回`std::future`对象。

```cpp
#include <future>

int longRunningTask(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return n * n;
}

void asyncExample() {
    std::cout << "开始异步任务" << std::endl;
    
    // 异步执行任务
    auto future = std::async(std::launch::async, longRunningTask, 5);
    
    // 在等待结果时做其他工作
    std::cout << "等待结果时做其他工作..." << std::endl;
    
    // 获取结果
    int result = future.get();
    std::cout << "异步任务结果: " << result << std::endl;
}
```

#### std::future 和 std::promise

```cpp
void promiseFutureExample() {
    // 创建promise和future
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    // 在另一个线程中设置值
    std::thread t([&promise]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        promise.set_value(42);
    });
    
    // 等待结果
    std::cout << "等待结果..." << std::endl;
    int result = future.get();
    std::cout << "结果: " << result << std::endl;
    
    t.join();
}
```

#### std::packaged_task

```cpp
void packagedTaskExample() {
    // 创建packaged_task
    std::packaged_task<int(int)> task([](int n) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return n * n;
    });
    
    // 获取future
    std::future<int> future = task.get_future();
    
    // 在另一个线程中执行任务
    std::thread t(std::move(task), 5);
    
    // 获取结果
    int result = future.get();
    std::cout << "Packaged task结果: " << result << std::endl;
    
    t.join();
}
```

#### 参考资料
- [std::async - cppreference.com](https://en.cppreference.com/w/cpp/thread/async)
- [std::future - cppreference.com](https://en.cppreference.com/w/cpp/thread/future)
- [异步编程详解](https://blog.csdn.net/weixin_43914604/article/details/105296000)

### 6. 线程池

简单的线程池实现：

```cpp
#include <functional>

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
    
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        
                        if (stop && tasks.empty()) {
                            return;
                        }
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    
                    task();
                }
            });
        }
    }
    
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task] { (*task)(); });
        }
        
        condition.notify_one();
        return res;
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }
};
```

#### 参考资料
- [线程池设计模式](https://github.com/progschj/ThreadPool)
- [C++ 线程池实现详解](https://blog.csdn.net/weixin_43914604/article/details/105297000)

### 7. 并发编程最佳实践

#### 避免数据竞争
- **使用锁**：保护共享数据
- **原子操作**：简单数据类型的无锁操作
- **线程局部存储**：thread_local关键字

#### 避免死锁
- **锁顺序**：总是以相同顺序获取锁
- **超时锁**：使用try_lock_for
- **RAII**：使用lock_guard自动管理锁

#### 性能考虑
- **减少锁竞争**：细粒度锁、读写锁
- **无锁编程**：使用原子操作
- **线程数量**：通常等于CPU核心数

#### 参考资料
- [C++ 并发编程最佳实践](https://herbsutter.com/2013/02/11/atomic-weapons-the-c-memory-model-and-modern-hardware/)
- [多线程编程指南](https://www.cnblogs.com/skyfsm/p/7050951.html)

## 实用教程和文档

### 官方文档
- [C++ 线程支持库 - cppreference.com](https://en.cppreference.com/w/cpp/thread)
- [C++ 原子操作库 - cppreference.com](https://en.cppreference.com/w/cpp/atomic)

### 优质教程
- [现代C++并发编程详解](https://changkun.de/modern-cpp/zh-cn/07-thread/)
- [C++ 并发编程实战](https://github.com/xiaoweiChen/CPP-Concurrency-In-Action-2ed-2019)
- [多线程编程指南](https://blog.csdn.net/weixin_43914604/article/details/105295000)

### 实战案例
- [并发编程在实际项目中的应用](https://www.bfilipek.com/2017/08/cpp17-details-parallel-algorithms.html)
- [高性能服务器编程](https://github.com/huihut/interview#%E5%A4%9A%E7%BA%BF%E7%A8%8B)

## 今日练习

### 基础练习
1. 实现一个生产者-消费者模式的程序
2. 编写一个线程安全的单例模式
3. 实现一个并行计算程序，比较串行和并行的性能

### 算法题推荐
1. [LeetCode 1114. Print in Order](https://leetcode.com/problems/print-in-order/) - 使用条件变量控制线程执行顺序
2. [LeetCode 1115. Print FooBar Alternately](https://leetcode.com/problems/print-foobar-alternately/) - 使用互斥锁和条件变量实现交替打印
3. [LeetCode 1116. Print Zero Even Odd](https://leetcode.com/problems/print-zero-even-odd/) - 使用信号量控制线程执行
4. [LeetCode 1117. Building H2O](https://leetcode.com/problems/building-h2o/) - 使用条件变量实现H2O分子构建

## 学习要点总结

1. **线程创建**：掌握std::thread的基本使用
2. **同步机制**：理解mutex、condition_variable等同步工具
3. **原子操作**：学会使用std::atomic进行无锁编程
4. **异步编程**：掌握std::async和std::future的使用
5. **线程安全**：编写线程安全的代码

## 下一天预告
明天我们将学习文件操作与IO，包括文件流、二进制文件、字符串流等C++的IO处理技术。

[上一天：移动语义](/plan/week3/day19/) | [返回第三周总览](/plan/week3/) | [下一天：文件操作与IO](/plan/week3/day21/)
