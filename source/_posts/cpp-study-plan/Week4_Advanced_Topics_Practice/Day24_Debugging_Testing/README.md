# 第24天：调试与测试

## 学习目标
掌握C++调试技巧和测试方法，学会使用各种调试工具，建立完善的测试框架，提高代码质量和可靠性。

## 今日学习内容

### 1. GDB调试器使用
**概念：** GDB是GNU调试器，是C++开发中最重要的调试工具。

**基本命令：**
- `gdb program`: 启动调试
- `run`: 运行程序
- `break`: 设置断点
- `step/next`: 单步执行
- `print`: 打印变量值
- `backtrace`: 查看调用栈

**GDB使用示例：**
```cpp
// debug_example.cpp
#include <iostream>
#include <vector>

class Calculator {
private:
    std::vector<double> history;
    
public:
    double divide(double a, double b) {
        if (b == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        double result = a / b;
        history.push_back(result);
        return result;
    }
    
    void printHistory() const {
        std::cout << "History: ";
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << history[i];
            if (i < history.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    double getAverage() const {
        if (history.empty()) return 0.0;
        
        double sum = 0.0;
        for (double val : history) {
            sum += val;
        }
        return sum / history.size();
    }
};

int main() {
    Calculator calc;
    
    try {
        std::cout << calc.divide(10.0, 2.0) << std::endl;  // 断点1
        std::cout << calc.divide(15.0, 3.0) << std::endl;  // 断点2
        std::cout << calc.divide(8.0, 0.0) << std::endl;   // 会抛异常
        
        calc.printHistory();
        std::cout << "Average: " << calc.getAverage() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}

/*
GDB调试会话示例：

$ g++ -g -o debug_example debug_example.cpp
$ gdb debug_example

(gdb) break main                    # 在main函数设置断点
(gdb) break Calculator::divide      # 在成员函数设置断点
(gdb) run                          # 运行程序

(gdb) step                         # 单步进入
(gdb) next                         # 单步跳过
(gdb) print calc                   # 打印对象
(gdb) print calc.history           # 打印成员变量
(gdb) print a                      # 打印参数

(gdb) watch calc.history.size()    # 监视表达式
(gdb) backtrace                    # 查看调用栈
(gdb) info locals                  # 查看局部变量

(gdb) continue                     # 继续执行
(gdb) quit                        # 退出调试器
*/
```

### 2. Valgrind内存检查
**概念：** Valgrind是强大的内存错误检测工具。

**主要功能：**
- 内存泄漏检测
- 未初始化内存访问
- 数组越界访问
- 重复释放内存

**Valgrind使用示例：**
```cpp
// memory_bugs.cpp - 故意包含内存错误的代码
#include <iostream>
#include <memory>

class MemoryBugDemo {
public:
    void memoryLeak() {
        int* ptr = new int[100];  // 内存泄漏：没有delete[]
        *ptr = 42;
        std::cout << "Allocated memory: " << *ptr << std::endl;
        // delete[] ptr;  // 忘记释放内存
    }
    
    void uninitializedAccess() {
        int* ptr = new int;  // 未初始化
        std::cout << "Uninitialized value: " << *ptr << std::endl;  // 错误！
        delete ptr;
    }
    
    void bufferOverflow() {
        int* arr = new int[10];
        for (int i = 0; i <= 10; ++i) {  // 越界访问
            arr[i] = i;
        }
        delete[] arr;
    }
    
    void doubleFree() {
        int* ptr = new int(42);
        delete ptr;
        delete ptr;  // 重复释放
    }
    
    void useAfterFree() {
        int* ptr = new int(42);
        delete ptr;
        std::cout << *ptr << std::endl;  // 使用已释放的内存
    }
};

/*
Valgrind使用命令：

$ g++ -g -o memory_bugs memory_bugs.cpp
$ valgrind --tool=memcheck --leak-check=full ./memory_bugs

输出示例：
==12345== Memcheck, a memory error detector
==12345== Invalid read of size 4
==12345== Invalid write of size 4
==12345== 100 bytes in 1 blocks are definitely lost
*/
```

### 3. 断言和错误处理
**概念：** 使用断言进行运行时检查，建立健壮的错误处理机制。

**断言使用示例：**
```cpp
#include <cassert>
#include <stdexcept>
#include <iostream>

class SafeArray {
private:
    std::unique_ptr<int[]> data;
    size_t size_;
    
public:
    SafeArray(size_t size) : size_(size) {
        assert(size > 0);  // 调试时检查
        if (size == 0) {
            throw std::invalid_argument("Size must be positive");
        }
        data = std::make_unique<int[]>(size);
    }
    
    int& at(size_t index) {
        // 调试版本的检查
        assert(index < size_);
        
        // 发布版本的检查
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        
        return data[index];
    }
    
    const int& at(size_t index) const {
        assert(index < size_);
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t size() const noexcept { return size_; }
};

// 自定义断言宏
#ifdef DEBUG
    #define SAFE_ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                std::cerr << "Assertion failed: " << #condition \
                         << " - " << message << std::endl; \
                std::abort(); \
            } \
        } while(0)
#else
    #define SAFE_ASSERT(condition, message) ((void)0)
#endif

void testSafeArray() {
    try {
        SafeArray arr(10);
        
        // 正常使用
        arr.at(0) = 42;
        std::cout << "arr[0] = " << arr.at(0) << std::endl;
        
        // 测试边界检查
        SAFE_ASSERT(arr.size() == 10, "Array size should be 10");
        
        // 这会抛出异常
        arr.at(10) = 100;
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
```

### 4. 单元测试框架
**概念：** 使用测试框架系统性地测试代码功能。

**简单测试框架实现：**
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

// 简单的测试框架
class TestFramework {
private:
    struct TestCase {
        std::string name;
        std::function<void()> test_func;
    };
    
    std::vector<TestCase> tests;
    int passed = 0;
    int failed = 0;
    
public:
    void addTest(const std::string& name, std::function<void()> test) {
        tests.push_back({name, test});
    }
    
    void assertEqual(int expected, int actual, const std::string& message = "") {
        if (expected != actual) {
            std::stringstream ss;
            ss << "Expected " << expected << ", got " << actual;
            if (!message.empty()) {
                ss << " (" << message << ")";
            }
            throw std::runtime_error(ss.str());
        }
    }
    
    void assertTrue(bool condition, const std::string& message = "") {
        if (!condition) {
            throw std::runtime_error("Assertion failed: " + message);
        }
    }
    
    void assertThrows(std::function<void()> func, const std::string& message = "") {
        bool threw = false;
        try {
            func();
        } catch (...) {
            threw = true;
        }
        if (!threw) {
            throw std::runtime_error("Expected exception was not thrown: " + message);
        }
    }
    
    void runTests() {
        std::cout << "Running " << tests.size() << " tests...\n" << std::endl;
        
        for (const auto& test : tests) {
            try {
                std::cout << "Running: " << test.name << "... ";
                test.test_func();
                std::cout << "PASSED" << std::endl;
                ++passed;
            } catch (const std::exception& e) {
                std::cout << "FAILED - " << e.what() << std::endl;
                ++failed;
            }
        }
        
        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << failed << std::endl;
        std::cout << "Total:  " << (passed + failed) << std::endl;
    }
};

// 使用测试框架测试Calculator类
void setupCalculatorTests(TestFramework& framework) {
    framework.addTest("Test Division", []() {
        Calculator calc;
        TestFramework tf;
        
        double result = calc.divide(10.0, 2.0);
        tf.assertEqual(5.0, result, "10/2 should equal 5");
    });
    
    framework.addTest("Test Division by Zero", []() {
        Calculator calc;
        TestFramework tf;
        
        tf.assertThrows([&]() {
            calc.divide(10.0, 0.0);
        }, "Division by zero should throw exception");
    });
    
    framework.addTest("Test History", []() {
        Calculator calc;
        TestFramework tf;
        
        calc.divide(10.0, 2.0);
        calc.divide(15.0, 3.0);
        
        double avg = calc.getAverage();
        tf.assertTrue(std::abs(avg - 4.0) < 0.001, "Average should be 4.0");
    });
}
```

### 5. 性能测试和基准测试
**概念：** 系统性地测试代码性能，建立性能基准。

**基准测试框架：**
```cpp
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

class BenchmarkFramework {
private:
    struct BenchmarkResult {
        std::string name;
        double min_time;
        double max_time;
        double avg_time;
        double std_dev;
        int iterations;
    };
    
    std::vector<BenchmarkResult> results;
    
    double calculateStdDev(const std::vector<double>& times, double mean) {
        double sum_sq_diff = 0.0;
        for (double time : times) {
            double diff = time - mean;
            sum_sq_diff += diff * diff;
        }
        return std::sqrt(sum_sq_diff / times.size());
    }
    
public:
    template<typename Func>
    void benchmark(const std::string& name, Func&& func, int iterations = 100) {
        std::vector<double> times;
        times.reserve(iterations);
        
        // 热身运行
        for (int i = 0; i < 5; ++i) {
            func();
        }
        
        // 正式测试
        for (int i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            func();
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - start).count();
            times.push_back(duration);
        }
        
        double min_time = *std::min_element(times.begin(), times.end());
        double max_time = *std::max_element(times.begin(), times.end());
        double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
        double std_dev = calculateStdDev(times, avg_time);
        
        results.push_back({name, min_time, max_time, avg_time, std_dev, iterations});
    }
    
    void printResults() {
        std::cout << "\n=== Benchmark Results ===" << std::endl;
        std::cout << std::left << std::setw(30) << "Test Name"
                  << std::setw(12) << "Min (ns)"
                  << std::setw(12) << "Max (ns)"
                  << std::setw(12) << "Avg (ns)"
                  << std::setw(12) << "Std Dev"
                  << std::setw(8) << "Iters" << std::endl;
        std::cout << std::string(86, '-') << std::endl;
        
        for (const auto& result : results) {
            std::cout << std::left << std::setw(30) << result.name
                      << std::setw(12) << std::fixed << std::setprecision(1) << result.min_time
                      << std::setw(12) << result.max_time
                      << std::setw(12) << result.avg_time
                      << std::setw(12) << result.std_dev
                      << std::setw(8) << result.iterations << std::endl;
        }
    }
    
    // 比较两个基准测试结果
    void compare(const std::string& baseline, const std::string& comparison) {
        auto baseline_it = std::find_if(results.begin(), results.end(),
            [&](const BenchmarkResult& r) { return r.name == baseline; });
        auto comparison_it = std::find_if(results.begin(), results.end(),
            [&](const BenchmarkResult& r) { return r.name == comparison; });
            
        if (baseline_it != results.end() && comparison_it != results.end()) {
            double speedup = baseline_it->avg_time / comparison_it->avg_time;
            std::cout << "\nComparison: " << comparison << " vs " << baseline << std::endl;
            std::cout << "Speedup: " << std::fixed << std::setprecision(2) << speedup << "x" << std::endl;
        }
    }
};

// 性能测试示例
void runPerformanceTests() {
    BenchmarkFramework benchmark;
    
    // 测试不同的排序算法
    const size_t size = 10000;
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 1);
    
    benchmark.benchmark("std::sort", [&]() {
        std::vector<int> copy = data;
        std::random_shuffle(copy.begin(), copy.end());
        std::sort(copy.begin(), copy.end());
    });
    
    benchmark.benchmark("std::stable_sort", [&]() {
        std::vector<int> copy = data;
        std::random_shuffle(copy.begin(), copy.end());
        std::stable_sort(copy.begin(), copy.end());
    });
    
    benchmark.printResults();
    benchmark.compare("std::sort", "std::stable_sort");
}
```

### 6. 日志系统
**概念：** 建立完善的日志系统，帮助调试和监控程序运行。

**日志系统实现：**
```cpp
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>
#include <iomanip>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

class Logger {
private:
    std::ofstream log_file;
    LogLevel min_level;
    std::mutex log_mutex;
    
    std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::CRITICAL: return "CRIT";
            default: return "UNKNOWN";
        }
    }
    
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }
    
public:
    Logger(const std::string& filename, LogLevel level = LogLevel::INFO)
        : min_level(level) {
        log_file.open(filename, std::ios::app);
        if (!log_file.is_open()) {
            throw std::runtime_error("Cannot open log file: " + filename);
        }
    }
    
    ~Logger() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }
    
    template<typename... Args>
    void log(LogLevel level, const std::string& format, Args&&... args) {
        if (level < min_level) return;
        
        std::lock_guard<std::mutex> lock(log_mutex);
        
        std::stringstream ss;
        formatString(ss, format, std::forward<Args>(args)...);
        
        std::string message = "[" + getCurrentTime() + "] "
                            + "[" + levelToString(level) + "] "
                            + "[Thread-" + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) % 10000) + "] "
                            + ss.str();
        
        log_file << message << std::endl;
        log_file.flush();
        
        // 同时输出到控制台（错误级别）
        if (level >= LogLevel::ERROR) {
            std::cerr << message << std::endl;
        }
    }
    
    // 便利方法
    template<typename... Args>
    void debug(const std::string& format, Args&&... args) {
        log(LogLevel::DEBUG, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void info(const std::string& format, Args&&... args) {
        log(LogLevel::INFO, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void warning(const std::string& format, Args&&... args) {
        log(LogLevel::WARNING, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void error(const std::string& format, Args&&... args) {
        log(LogLevel::ERROR, format, std::forward<Args>(args)...);
    }
    
private:
    void formatString(std::stringstream& ss, const std::string& format) {
        ss << format;
    }
    
    template<typename T, typename... Args>
    void formatString(std::stringstream& ss, const std::string& format, T&& value, Args&&... args) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            ss << format.substr(0, pos) << value;
            formatString(ss, format.substr(pos + 2), std::forward<Args>(args)...);
        } else {
            ss << format;
        }
    }
};

// 全局日志器
extern Logger g_logger("application.log");

#define LOG_DEBUG(...) g_logger.debug(__VA_ARGS__)
#define LOG_INFO(...) g_logger.info(__VA_ARGS__)
#define LOG_WARNING(...) g_logger.warning(__VA_ARGS__)
#define LOG_ERROR(...) g_logger.error(__VA_ARGS__)
```

## 实践练习

### 练习1：调试复杂的内存问题
```cpp
// 创建包含各种内存错误的程序
// 使用GDB和Valgrind进行调试
```

### 练习2：建立完整的测试套件
```cpp
// 为之前实现的数据结构编写完整的单元测试
// 包括边界条件、异常情况、性能测试
```

### 练习3：性能分析和优化
```cpp
// 使用性能分析工具找出程序瓶颈
// 实施优化并验证效果
```

## 重点总结

1. **调试工具**：熟练使用GDB、Valgrind等调试工具
2. **断言和错误处理**：建立健壮的错误检查机制
3. **单元测试**：系统性测试代码功能
4. **性能测试**：建立性能基准，监控性能变化
5. **日志系统**：完善的日志记录和分析
6. **内存安全**：避免内存泄漏和访问错误

## 调试最佳实践

1. **预防胜于治疗**：编写防御性代码
2. **早期测试**：在开发过程中持续测试
3. **自动化测试**：建立自动化测试流程
4. **代码审查**：通过代码审查发现问题
5. **持续集成**：在CI/CD中集成测试和分析工具

## 注意事项

1. **调试版本vs发布版本**：使用不同的编译选项
2. **测试覆盖率**：确保测试覆盖所有重要代码路径
3. **性能回归**：监控性能变化，防止性能退化
4. **内存管理**：特别关注内存相关问题
5. **多线程调试**：注意线程安全和竞态条件

## 拓展阅读

- 《Effective Debugging》
- 《Google Test框架文档》
- GDB官方文档
- Valgrind用户手册
- 《Clean Code》测试章节
