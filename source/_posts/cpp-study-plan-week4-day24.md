---
title: C++ 学习计划 - 第24天：调试与测试
date: 2025-09-16 10:27:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week4
    - Day24
layout: page
menu_id: plan
permalink: /plan/week4/day24/
---

# 第24天：调试与测试

## 学习目标
掌握C++程序的调试技巧和测试方法，学会使用调试工具和测试框架，提高代码质量和开发效率。

## 学习资源链接

### 📚 官方文档和教程
- [GDB User Manual](https://www.gnu.org/software/gdb/documentation/) - GDB官方文档
- [Valgrind Documentation](https://valgrind.org/docs/manual/) - Valgrind内存检查工具
- [Google Test Documentation](https://google.github.io/googletest/) - Google测试框架
- [Catch2 Documentation](https://github.com/catchorg/Catch2/blob/devel/docs/Readme.md) - Catch2测试框架

### 🎥 视频教程
- [GDB Tutorial](https://www.youtube.com/watch?v=bWH-nL7v5F4) - GDB调试教程
- [Valgrind Memory Debugging](https://www.youtube.com/watch?v=bb1bTJtgXrI) - Valgrind使用教程
- [C++ Unit Testing](https://www.youtube.com/watch?v=16FI1-d2P4E) - C++单元测试
- [Debug vs Release](https://www.youtube.com/watch?v=2BuJjaGuInI) - 调试版本vs发布版本

### 📖 深入阅读
- [Effective Debugging](https://www.amazon.com/Effective-Debugging-Specific-Software-Hardware/dp/0134394909) - 高效调试技巧
- [Modern C++ Testing](https://leanpub.com/modern-cpp-testing) - 现代C++测试
- [The Art of Debugging](https://www.amazon.com/Art-Debugging-GDB-DDD-Eclipse/dp/1593271743) - 调试艺术

### 🔧 调试和测试工具
- [Visual Studio Debugger](https://docs.microsoft.com/en-us/visualstudio/debugger/) - VS调试器
- [CLion Debugger](https://www.jetbrains.com/help/clion/debugging-code.html) - CLion调试器
- [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer) - 内存错误检测
- [ThreadSanitizer](https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual) - 线程错误检测

## 学习内容

### 1. GDB调试器使用

#### 基本GDB命令
```bash
# 编译带调试信息的程序
g++ -g -O0 program.cpp -o program

# 启动GDB
gdb ./program

# 基本调试命令
(gdb) run                    # 运行程序
(gdb) break main             # 在main函数设置断点
(gdb) break 15               # 在第15行设置断点
(gdb) info breakpoints       # 查看断点信息
(gdb) continue              # 继续执行
(gdb) step                  # 单步执行（进入函数）
(gdb) next                  # 单步执行（不进入函数）
(gdb) print variable        # 打印变量值
(gdb) watch variable        # 监视变量变化
(gdb) backtrace            # 查看调用栈
(gdb) info locals          # 查看局部变量
(gdb) quit                 # 退出GDB
```

#### 高级GDB技巧
```cpp
// 示例程序：debug_example.cpp
#include <iostream>
#include <vector>
#include <memory>

class DebugExample {
private:
    std::vector<int> data;
    
public:
    void process() {
        data = {1, 2, 3, 4, 5};
        
        for (size_t i = 0; i <= data.size(); ++i) { // 故意的越界错误
            std::cout << "data[" << i << "] = " << data[i] << std::endl;
        }
    }
    
    void memory_leak_example() {
        int* ptr = new int[100]; // 内存泄漏
        // 忘记delete[] ptr;
    }
};

int main() {
    DebugExample example;
    example.process();
    example.memory_leak_example();
    return 0;
}
```

```bash
# GDB调试会话示例
gdb ./debug_example
(gdb) set print pretty on           # 美化输出
(gdb) break DebugExample::process   # 在成员函数设置断点
(gdb) run
(gdb) print this                    # 打印this指针
(gdb) print data                    # 打印STL容器
(gdb) print data.size()             # 调用成员函数
(gdb) watch data[i]                 # 监视数组元素
```

### 2. Valgrind内存检查

#### Memcheck工具
```bash
# 编译程序（保留调试信息）
g++ -g -O0 program.cpp -o program

# 使用Valgrind检查内存错误
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./program

# 详细内存检查
valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes ./program
```

#### 常见内存错误检测
```cpp
// 内存错误示例
#include <iostream>
#include <cstring>

void memory_errors_example() {
    // 1. 内存泄漏
    int* leak = new int[100];
    // delete[] leak; // 忘记释放
    
    // 2. 重复释放
    int* ptr = new int(42);
    delete ptr;
    // delete ptr; // 重复释放
    
    // 3. 使用已释放的内存
    int* dangling = new int(10);
    delete dangling;
    // std::cout << *dangling; // 使用悬空指针
    
    // 4. 数组越界
    int arr[10];
    // arr[10] = 5; // 越界访问
    
    // 5. 未初始化内存
    int uninitialized;
    // if (uninitialized == 0) { } // 使用未初始化变量
}
```

### 3. 单元测试框架

#### Google Test (gtest) 框架
```cpp
// test_example.cpp
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// 被测试的类
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    double divide(double a, double b) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        return a / b;
    }
};

// 测试夹具
class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        calc = std::make_unique<Calculator>();
    }
    
    void TearDown() override {
        // 清理资源
    }
    
    std::unique_ptr<Calculator> calc;
};

// 基本测试
TEST_F(CalculatorTest, Addition) {
    EXPECT_EQ(calc->add(2, 3), 5);
    EXPECT_EQ(calc->add(-1, 1), 0);
    EXPECT_EQ(calc->add(0, 0), 0);
}

TEST_F(CalculatorTest, Subtraction) {
    EXPECT_EQ(calc->subtract(5, 3), 2);
    EXPECT_EQ(calc->subtract(0, 5), -5);
}

TEST_F(CalculatorTest, Multiplication) {
    EXPECT_EQ(calc->multiply(3, 4), 12);
    EXPECT_EQ(calc->multiply(-2, 3), -6);
    EXPECT_EQ(calc->multiply(0, 100), 0);
}

TEST_F(CalculatorTest, Division) {
    EXPECT_DOUBLE_EQ(calc->divide(10, 2), 5.0);
    EXPECT_DOUBLE_EQ(calc->divide(7, 2), 3.5);
    
    // 测试异常
    EXPECT_THROW(calc->divide(1, 0), std::invalid_argument);
}

// 参数化测试
class AdditionTest : public ::testing::TestWithParam<std::tuple<int, int, int>> {};

TEST_P(AdditionTest, ParameterizedAddition) {
    auto [a, b, expected] = GetParam();
    Calculator calc;
    EXPECT_EQ(calc.add(a, b), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AdditionValues,
    AdditionTest,
    ::testing::Values(
        std::make_tuple(1, 2, 3),
        std::make_tuple(-1, 1, 0),
        std::make_tuple(100, 200, 300)
    )
);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

#### Catch2 测试框架
```cpp
// catch2_example.cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <stdexcept>

class StringProcessor {
public:
    std::string reverse(const std::string& str) {
        return std::string(str.rbegin(), str.rend());
    }
    
    bool isPalindrome(const std::string& str) {
        return str == reverse(str);
    }
    
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
};

TEST_CASE("StringProcessor tests", "[string]") {
    StringProcessor processor;
    
    SECTION("Reverse function") {
        REQUIRE(processor.reverse("hello") == "olleh");
        REQUIRE(processor.reverse("") == "");
        REQUIRE(processor.reverse("a") == "a");
    }
    
    SECTION("Palindrome detection") {
        REQUIRE(processor.isPalindrome("racecar") == true);
        REQUIRE(processor.isPalindrome("hello") == false);
        REQUIRE(processor.isPalindrome("") == true);
        REQUIRE(processor.isPalindrome("a") == true);
    }
    
    SECTION("String splitting") {
        auto result = processor.split("a,b,c", ',');
        REQUIRE(result.size() == 3);
        REQUIRE(result[0] == "a");
        REQUIRE(result[1] == "b");
        REQUIRE(result[2] == "c");
        
        auto empty_result = processor.split("", ',');
        REQUIRE(empty_result.size() == 1);
        REQUIRE(empty_result[0] == "");
    }
}

// 基准测试
TEST_CASE("Performance benchmark", "[benchmark]") {
    StringProcessor processor;
    std::string large_string(10000, 'a');
    
    BENCHMARK("String reversal") {
        return processor.reverse(large_string);
    };
}
```

### 4. 断言的使用

#### 标准断言
```cpp
#include <cassert>
#include <iostream>

class SafeArray {
private:
    std::vector<int> data;
    
public:
    SafeArray(size_t size) : data(size) {}
    
    int& at(size_t index) {
        // 调试版本中检查边界
        assert(index < data.size() && "Index out of bounds");
        return data[index];
    }
    
    const int& at(size_t index) const {
        assert(index < data.size() && "Index out of bounds");
        return data[index];
    }
    
    size_t size() const { return data.size(); }
};

// 自定义断言宏
#ifdef DEBUG
    #define ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                std::cerr << "Assertion failed: " << #condition \
                         << " - " << message \
                         << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
                std::abort(); \
            } \
        } while (0)
#else
    #define ASSERT(condition, message) do { } while (0)
#endif
```

### 5. 日志系统

#### 简单日志实现
```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    std::ofstream file;
    LogLevel min_level;
    
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
    
public:
    Logger(const std::string& filename, LogLevel level = LogLevel::INFO) 
        : file(filename), min_level(level) {}
    
    template<typename... Args>
    void log(LogLevel level, Args&&... args) {
        if (level >= min_level) {
            std::stringstream ss;
            ss << "[" << getCurrentTime() << "] "
               << "[" << levelToString(level) << "] ";
            
            ((ss << std::forward<Args>(args) << " "), ...);
            
            std::string message = ss.str();
            file << message << std::endl;
            std::cout << message << std::endl;
        }
    }
    
    template<typename... Args>
    void debug(Args&&... args) {
        log(LogLevel::DEBUG, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void info(Args&&... args) {
        log(LogLevel::INFO, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void warning(Args&&... args) {
        log(LogLevel::WARNING, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void error(Args&&... args) {
        log(LogLevel::ERROR, std::forward<Args>(args)...);
    }
};

// 使用示例
void logging_example() {
    Logger logger("app.log", LogLevel::DEBUG);
    
    logger.info("Application started");
    logger.debug("Debug information:", 42, "items processed");
    logger.warning("Low memory warning");
    logger.error("Failed to open file:", "data.txt");
}
```

## 实践练习

### 练习1：调试复杂程序
创建一个包含多种错误的程序并使用GDB调试：
- 逻辑错误
- 内存错误
- 性能问题

### 练习2：内存检查实战
使用Valgrind检查程序的内存问题：
- 内存泄漏检测
- 越界访问检测
- 未初始化内存使用

### 练习3：完整测试套件
为一个数据结构类编写完整的测试套件：
- 单元测试
- 集成测试
- 性能测试

### 练习4：日志系统设计
设计和实现一个生产级的日志系统：
- 多线程安全
- 不同输出目标
- 日志轮转功能

## 今日总结
通过学习调试与测试，你应该掌握：
1. GDB调试器的基本和高级用法
2. Valgrind内存检查工具的使用
3. 单元测试框架的应用
4. 断言和日志在调试中的作用
5. 调试和测试的最佳实践

## 明天预告
明天我们将学习C++17的新特性，包括结构化绑定、if constexpr、std::optional等现代C++特性。

[返回第四周](/plan/week4/) | [上一天：第23天](/plan/week4/day23/) | [下一天：第25天](/plan/week4/day25/)
