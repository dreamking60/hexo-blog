# 第24天：调试与测试 - LeetCode算法题

## 今日算法练习 (4道Medium/Hard题目)

### 题目1：错误处理和边界条件测试
**LeetCode 1286. Iterator for Combination (Medium)**
- **链接：** https://leetcode.com/problems/iterator-for-combination/
- **难度：** Medium
- **知识点：** 迭代器设计、边界条件处理、状态管理
- **描述：** 设计一个迭代器，按字典序生成给定字符串的所有长度为k的组合
- **调试重点：**
  - 边界条件：k=0, k>字符串长度
  - 状态一致性：迭代器状态的正确维护
  - 内存管理：避免不必要的内存分配

**测试要求：**
- 编写完整的单元测试
- 测试所有边界条件
- 验证迭代器的正确性

### 题目2：复杂状态调试
**LeetCode 1348. Tweet Counts Per Frequency (Medium)**
- **链接：** https://leetcode.com/problems/tweet-counts-per-frequency/
- **难度：** Medium
- **知识点：** 数据结构设计、时间处理、状态调试
- **描述：** 设计一个系统记录推文时间，并能按不同频率查询推文数量
- **调试重点：**
  - 时间边界处理
  - 数据结构状态的正确性
  - 并发访问的线程安全

**调试技巧：**
- 使用断言验证时间边界
- 日志记录关键状态变化
- 单步调试复杂的时间计算

### 题目3：内存管理和性能调试 (Hard)
**LeetCode 1157. Online Majority Element In Subarray (Hard)**
- **链接：** https://leetcode.com/problems/online-majority-element-in-subarray/
- **难度：** Hard
- **知识点：** 数据结构设计、内存优化、性能分析
- **描述：** 设计数据结构支持在线查询子数组中的多数元素
- **调试重点：**
  - 内存使用优化
  - 时间复杂度分析
  - 大数据量下的性能表现

**性能测试：**
- 基准测试不同实现方案
- 内存使用分析
- 缓存命中率测试

### 题目4：并发和线程安全调试 (Hard)
**LeetCode 1188. Design Bounded Blocking Queue (Medium)**
- **链接：** https://leetcode.com/problems/design-bounded-blocking-queue/
- **难度：** Medium (但涉及并发，实际难度较高)
- **知识点：** 多线程、同步机制、死锁预防
- **描述：** 设计一个有界阻塞队列，支持多线程安全的入队和出队操作
- **调试重点：**
  - 死锁检测和预防
  - 竞态条件识别
  - 线程同步的正确性

**并发测试：**
- 多线程压力测试
- 死锁检测
- 性能基准测试

## 调试和测试框架实现

### 1. 单元测试框架
```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <exception>

class TestFramework {
private:
    struct TestCase {
        std::string name;
        std::function<void()> test_func;
        bool passed = false;
        std::string error_message;
    };
    
    std::vector<TestCase> test_cases;
    
public:
    void addTest(const std::string& name, std::function<void()> test) {
        test_cases.push_back({name, test});
    }
    
    // 断言方法
    template<typename T>
    void assertEqual(const T& expected, const T& actual, const std::string& message = "") {
        if (expected != actual) {
            throw TestFailure("Expected: " + toString(expected) + 
                            ", Actual: " + toString(actual) + 
                            (message.empty() ? "" : " (" + message + ")"));
        }
    }
    
    void assertTrue(bool condition, const std::string& message = "") {
        if (!condition) {
            throw TestFailure("Assertion failed" + 
                            (message.empty() ? "" : ": " + message));
        }
    }
    
    void assertFalse(bool condition, const std::string& message = "") {
        assertTrue(!condition, message);
    }
    
    template<typename Exception>
    void assertThrows(std::function<void()> func, const std::string& message = "") {
        bool threw = false;
        try {
            func();
        } catch (const Exception&) {
            threw = true;
        } catch (...) {
            throw TestFailure("Wrong exception type thrown" + 
                            (message.empty() ? "" : ": " + message));
        }
        
        if (!threw) {
            throw TestFailure("Expected exception was not thrown" + 
                            (message.empty() ? "" : ": " + message));
        }
    }
    
    // 性能测试
    template<typename Func>
    void assertPerformance(Func&& func, int max_milliseconds, const std::string& message = "") {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start).count();
        
        if (duration > max_milliseconds) {
            throw TestFailure("Performance test failed: took " + 
                            std::to_string(duration) + "ms, expected < " + 
                            std::to_string(max_milliseconds) + "ms" +
                            (message.empty() ? "" : " (" + message + ")"));
        }
    }
    
    void runTests() {
        int passed = 0;
        int failed = 0;
        
        std::cout << "Running " << test_cases.size() << " tests...\n" << std::endl;
        
        for (auto& test : test_cases) {
            try {
                std::cout << "Running: " << test.name << "... ";
                test.test_func();
                test.passed = true;
                std::cout << "PASSED" << std::endl;
                ++passed;
            } catch (const TestFailure& e) {
                test.passed = false;
                test.error_message = e.what();
                std::cout << "FAILED - " << e.what() << std::endl;
                ++failed;
            } catch (const std::exception& e) {
                test.passed = false;
                test.error_message = "Unexpected exception: " + std::string(e.what());
                std::cout << "ERROR - " << e.what() << std::endl;
                ++failed;
            }
        }
        
        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << failed << std::endl;
        std::cout << "Success Rate: " << std::fixed << std::setprecision(1) 
                  << (100.0 * passed / (passed + failed)) << "%" << std::endl;
    }
    
private:
    class TestFailure : public std::exception {
    private:
        std::string message;
    public:
        TestFailure(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
    
    template<typename T>
    std::string toString(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};
```

### 2. 内存泄漏检测器
```cpp
#include <unordered_map>
#include <mutex>
#include <iostream>

class MemoryTracker {
private:
    struct AllocationInfo {
        size_t size;
        const char* file;
        int line;
        std::chrono::system_clock::time_point timestamp;
    };
    
    std::unordered_map<void*, AllocationInfo> allocations;
    std::mutex mutex;
    size_t total_allocated = 0;
    size_t peak_usage = 0;
    
public:
    static MemoryTracker& getInstance() {
        static MemoryTracker instance;
        return instance;
    }
    
    void recordAllocation(void* ptr, size_t size, const char* file, int line) {
        std::lock_guard<std::mutex> lock(mutex);
        allocations[ptr] = {size, file, line, std::chrono::system_clock::now()};
        total_allocated += size;
        if (total_allocated > peak_usage) {
            peak_usage = total_allocated;
        }
    }
    
    void recordDeallocation(void* ptr) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = allocations.find(ptr);
        if (it != allocations.end()) {
            total_allocated -= it->second.size;
            allocations.erase(it);
        }
    }
    
    void printReport() {
        std::lock_guard<std::mutex> lock(mutex);
        
        std::cout << "\n=== Memory Usage Report ===" << std::endl;
        std::cout << "Peak Usage: " << peak_usage << " bytes" << std::endl;
        std::cout << "Current Usage: " << total_allocated << " bytes" << std::endl;
        std::cout << "Active Allocations: " << allocations.size() << std::endl;
        
        if (!allocations.empty()) {
            std::cout << "\nMemory Leaks Detected:" << std::endl;
            for (const auto& [ptr, info] : allocations) {
                std::cout << "  " << ptr << " (" << info.size << " bytes) "
                          << "at " << info.file << ":" << info.line << std::endl;
            }
        }
    }
};

// 重载全局new/delete操作符进行内存跟踪
#ifdef MEMORY_TRACKING
void* operator new(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    MemoryTracker::getInstance().recordAllocation(ptr, size, file, line);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    MemoryTracker::getInstance().recordDeallocation(ptr);
    free(ptr);
}

#define new new(__FILE__, __LINE__)
#endif
```

### 3. 性能基准测试
```cpp
class BenchmarkSuite {
private:
    struct BenchmarkResult {
        std::string name;
        double avg_time_ns;
        double min_time_ns;
        double max_time_ns;
        int iterations;
    };
    
    std::vector<BenchmarkResult> results;
    
public:
    template<typename Func>
    void benchmark(const std::string& name, Func&& func, int iterations = 1000) {
        std::vector<double> times;
        times.reserve(iterations);
        
        // 热身
        for (int i = 0; i < 10; ++i) {
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
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
        double min_time = *std::min_element(times.begin(), times.end());
        double max_time = *std::max_element(times.begin(), times.end());
        
        results.push_back({name, avg, min_time, max_time, iterations});
    }
    
    void printResults() {
        std::cout << "\n=== Benchmark Results ===" << std::endl;
        for (const auto& result : results) {
            std::cout << result.name << ":" << std::endl;
            std::cout << "  Average: " << std::fixed << std::setprecision(2) 
                      << result.avg_time_ns << " ns" << std::endl;
            std::cout << "  Min: " << result.min_time_ns << " ns" << std::endl;
            std::cout << "  Max: " << result.max_time_ns << " ns" << std::endl;
            std::cout << "  Iterations: " << result.iterations << std::endl << std::endl;
        }
    }
};
```

## 解题要求

### 调试技巧应用
1. **使用GDB调试**：设置断点，检查变量状态
2. **内存检查**：使用Valgrind或自定义内存跟踪
3. **断言使用**：在关键位置添加断言
4. **日志记录**：记录关键状态和操作

### 测试覆盖
1. **正常情况测试**：验证基本功能正确性
2. **边界条件测试**：测试极端输入情况
3. **异常情况测试**：验证错误处理
4. **性能测试**：确保满足时间复杂度要求

### 代码质量
1. **防御性编程**：检查输入参数有效性
2. **异常安全**：确保异常情况下的资源清理
3. **线程安全**：多线程环境下的正确性
4. **内存安全**：避免内存泄漏和越界访问

## 调试工具使用

### GDB调试会话示例
```bash
# 编译时加入调试信息
g++ -g -o solution solution.cpp

# 启动GDB
gdb ./solution

# GDB命令
(gdb) break main                    # 在main函数设断点
(gdb) break Solution::method        # 在类方法设断点
(gdb) run                          # 运行程序
(gdb) step                         # 单步进入
(gdb) next                         # 单步跳过
(gdb) print variable               # 打印变量值
(gdb) watch variable               # 监视变量变化
(gdb) backtrace                    # 查看调用栈
(gdb) info locals                  # 查看局部变量
(gdb) continue                     # 继续执行
```

### Valgrind内存检查
```bash
# 编译
g++ -g -o solution solution.cpp

# 内存泄漏检查
valgrind --tool=memcheck --leak-check=full ./solution

# 缓存性能分析
valgrind --tool=cachegrind ./solution
```

## 学习目标检查

完成今天的算法题后，你应该能够：

1. ✅ **熟练使用调试工具**：GDB、Valgrind等
2. ✅ **编写完整的测试套件**：单元测试、集成测试
3. ✅ **进行性能分析**：基准测试、性能优化
4. ✅ **处理内存问题**：内存泄漏、越界访问
5. ✅ **调试并发问题**：死锁、竞态条件
6. ✅ **建立质量保证流程**：自动化测试、持续集成

## 提交要求

1. 每道题提供完整的解决方案和测试代码
2. 包含调试过程记录和问题分析
3. 性能测试报告和优化建议
4. 内存使用分析和安全性验证
5. 总结调试技巧和最佳实践心得

## 调试检查清单

- [ ] 是否添加了充分的断言检查
- [ ] 是否处理了所有边界条件
- [ ] 是否进行了内存泄漏检查
- [ ] 是否测试了异常情况
- [ ] 是否验证了线程安全性
- [ ] 是否进行了性能基准测试
- [ ] 是否添加了适当的日志记录
