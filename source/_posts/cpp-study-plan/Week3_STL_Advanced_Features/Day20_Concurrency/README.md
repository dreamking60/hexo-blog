# 第20天：并发编程基础复习

## 学习目标
掌握C++11引入的并发编程特性，理解线程、同步机制和异步编程，学会编写线程安全的代码。

## 学习内容

### 1. 并发编程概述

并发编程允许程序同时执行多个任务，提高程序性能和响应性。

#### 为什么需要并发编程？
- **性能提升**：利用多核处理器
- **响应性**：避免阻塞主线程
- **资源利用**：提高系统资源利用率
- **用户体验**：提供更好的交互体验

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
#include <iostream>
#include <thread>
#include <string>

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
#include <iostream>
#include <thread>
#include <vector>

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

### 3. 线程同步

#### std::mutex
`std::mutex`用于保护共享资源，确保同一时间只有一个线程可以访问。

```cpp
#include <iostream>
#include <thread>
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
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class SafeVector {
private:
    std::vector<int> data;
    mutable std::mutex mtx;
    
public:
    void add(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        data.push_back(value);
    }
    
    int get(int index) const {
        std::lock_guard<std::mutex> lock(mtx);
        return data[index];
    }
    
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.size();
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

void lockGuardExample() {
    SafeVector vec;
    std::vector<std::thread> threads;
    
    // 添加数据
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&vec, i]() {
            for (int j = 0; j < 100; ++j) {
                vec.add(i * 100 + j);
            }
        });
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "向量大小: " << vec.size() << std::endl;
}
```

#### std::condition_variable
`std::condition_variable`用于线程间的条件同步。

```cpp
#include <iostream>
#include <thread>
#include <mutex>
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
        cv.notify_one();
    }
    
    int pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty(); });
        
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

### 4. 原子操作

`std::atomic`提供原子操作，无需锁即可保证线程安全。

```cpp
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

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

### 5. 异步编程

#### std::async
`std::async`用于异步执行函数，返回`std::future`对象。

```cpp
#include <iostream>
#include <future>
#include <chrono>
#include <vector>

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
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

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

### 6. 线程池

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <future>

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

void threadPoolExample() {
    ThreadPool pool(4);
    
    // 提交任务
    auto result1 = pool.enqueue([](int answer) { return answer; }, 42);
    auto result2 = pool.enqueue([]() { return 3.14; });
    
    std::cout << "结果1: " << result1.get() << std::endl;
    std::cout << "结果2: " << result2.get() << std::endl;
}
```

## 实践练习

### 练习1：生产者-消费者模式
```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

template<typename T>
class ProducerConsumer {
private:
    std::queue<T> queue;
    mutable std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
    
public:
    void produce(T item) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(item);
        }
        cv.notify_one();
    }
    
    bool consume(T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty() || stop; });
        
        if (queue.empty() && stop) {
            return false;
        }
        
        item = queue.front();
        queue.pop();
        return true;
    }
    
    void stopProducing() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
    }
};

void producerConsumerExample() {
    ProducerConsumer<int> pc;
    
    // 生产者线程
    std::thread producer([&pc]() {
        for (int i = 0; i < 10; ++i) {
            pc.produce(i);
            std::cout << "生产: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        pc.stopProducing();
    });
    
    // 消费者线程
    std::thread consumer([&pc]() {
        int item;
        while (pc.consume(item)) {
            std::cout << "消费: " << item << std::endl;
        }
    });
    
    producer.join();
    consumer.join();
}
```

### 练习2：线程安全的单例模式
```cpp
#include <iostream>
#include <mutex>
#include <memory>

class Singleton {
private:
    static std::unique_ptr<Singleton> instance;
    static std::mutex mtx;
    
    Singleton() = default;
    
public:
    static Singleton& getInstance() {
        if (!instance) {
            std::lock_guard<std::mutex> lock(mtx);
            if (!instance) {
                instance = std::unique_ptr<Singleton>(new Singleton);
            }
        }
        return *instance;
    }
    
    void doSomething() {
        std::cout << "单例对象正在工作" << std::endl;
    }
    
    // 禁止拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

std::unique_ptr<Singleton> Singleton::instance = nullptr;
std::mutex Singleton::mtx;

void singletonExample() {
    // 多线程访问单例
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([]() {
            Singleton::getInstance().doSomething();
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}
```

### 练习3：并行计算
```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <chrono>
#include <future>

class ParallelCalculator {
public:
    static long long parallelSum(const std::vector<int>& data, int numThreads) {
        int chunkSize = data.size() / numThreads;
        std::vector<std::future<long long>> futures;
        
        for (int i = 0; i < numThreads; ++i) {
            int start = i * chunkSize;
            int end = (i == numThreads - 1) ? data.size() : (i + 1) * chunkSize;
            
            futures.push_back(std::async(std::launch::async, [&data, start, end]() {
                return std::accumulate(data.begin() + start, data.begin() + end, 0LL);
            }));
        }
        
        long long total = 0;
        for (auto& future : futures) {
            total += future.get();
        }
        
        return total;
    }
    
    static long long sequentialSum(const std::vector<int>& data) {
        return std::accumulate(data.begin(), data.end(), 0LL);
    }
};

void parallelCalculationExample() {
    // 创建大量数据
    std::vector<int> data(1000000);
    std::iota(data.begin(), data.end(), 1);
    
    // 顺序计算
    auto start = std::chrono::high_resolution_clock::now();
    long long seqResult = ParallelCalculator::sequentialSum(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto seqDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // 并行计算
    start = std::chrono::high_resolution_clock::now();
    long long parResult = ParallelCalculator::parallelSum(data, 4);
    end = std::chrono::high_resolution_clock::now();
    auto parDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "顺序计算结果: " << seqResult << " (耗时: " << seqDuration.count() << "ms)" << std::endl;
    std::cout << "并行计算结果: " << parResult << " (耗时: " << parDuration.count() << "ms)" << std::endl;
}
```

## 学习要点总结

1. **线程创建**：掌握std::thread的基本使用
2. **同步机制**：理解mutex、condition_variable等同步工具
3. **原子操作**：学会使用std::atomic进行无锁编程
4. **异步编程**：掌握std::async和std::future的使用
5. **线程安全**：编写线程安全的代码

## 今日算法题

完成以下4道LeetCode题目，巩固并发编程的使用：

1. [LeetCode 1114. Print in Order](https://leetcode.com/problems/print-in-order/) - 使用条件变量控制线程执行顺序
2. [LeetCode 1115. Print FooBar Alternately](https://leetcode.com/problems/print-foobar-alternately/) - 使用互斥锁和条件变量实现交替打印
3. [LeetCode 1116. Print Zero Even Odd](https://leetcode.com/problems/print-zero-even-odd/) - 使用信号量控制线程执行
4. [LeetCode 1117. Building H2O](https://leetcode.com/problems/building-h2o/) - 使用条件变量实现H2O分子构建

每道题目都涉及并发编程的使用，是很好的实践机会！
