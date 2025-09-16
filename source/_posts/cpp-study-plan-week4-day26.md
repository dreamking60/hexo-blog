---
title: C++ 学习计划 - 第26天：C++20新特性
date: 2025-09-16 10:29:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week4
    - Day26
layout: page
menu_id: plan
permalink: /plan/week4/day26/
---

# 第26天：C++20新特性

## 学习目标
了解和掌握C++20标准引入的重要新特性，学会使用最新的现代C++特性来编写更安全、更高效、更易维护的代码。

## 学习资源链接

### 📚 官方文档和教程
- [C++20 Reference](https://en.cppreference.com/w/cpp/20) - C++20官方参考文档
- [C++20 Features](https://www.modernescpp.com/index.php/c-20-core-language) - C++20核心特性介绍
- [C++20 in Detail](https://leanpub.com/cpp20indetail) - C++20详细指南
- [ISO C++20 Standard](https://www.iso.org/standard/79358.html) - C++20标准文档

### 🎥 视频教程
- [C++20 Overview](https://www.youtube.com/watch?v=FRkJCvHWdwQ) - C++20特性概览
- [CppCon C++20 Talks](https://www.youtube.com/results?search_query=cppcon+c%2B%2B20) - CppCon C++20演讲
- [C++20 Concepts](https://www.youtube.com/watch?v=HddFGPTAmtU) - C++20概念详解
- [C++20 Coroutines](https://www.youtube.com/watch?v=_fu0gx-xseY) - C++20协程教程

### 📖 深入阅读
- [C++20 Recipes](https://www.amazon.com/C-20-Recipes-Problem-Solution-Approach/dp/1484257871) - C++20实战指南
- [Beginning C++20](https://www.amazon.com/Beginning-C-20-Introduction-Professional-Programming/dp/1484258835) - C++20入门
- [Professional C++](https://www.amazon.com/Professional-C-Marc-Gregoire/dp/1119695406) - 专业C++编程(包含C++20)

### 🔧 编译器支持
- [GCC C++20 Support](https://gcc.gnu.org/projects/cxx-status.html#cxx20) - GCC对C++20的支持
- [Clang C++20 Support](https://clang.llvm.org/cxx_status.html#cxx20) - Clang对C++20的支持
- [MSVC C++20 Support](https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance) - MSVC对C++20的支持

## 学习内容

### 1. 概念 (Concepts)

概念是C++20引入的重要特性，用于约束模板参数，提供更好的错误信息和更清晰的接口。

```cpp
#include <concepts>
#include <iostream>
#include <vector>
#include <type_traits>

// 基本概念定义
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept Arithmetic = Integral<T> || FloatingPoint<T>;

// 使用概念约束函数模板
template<Arithmetic T>
T add(T a, T b) {
    return a + b;
}

// 更复杂的概念
template<typename T>
concept Printable = requires(T t) {
    std::cout << t; // 要求类型T可以输出到cout
};

template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::iterator;
    t.begin();
    t.end();
    t.size();
};

template<typename T>
concept Sortable = Container<T> && requires(T t) {
    std::sort(t.begin(), t.end());
};

// 自定义概念示例
template<typename T>
concept Drawable = requires(T obj, int x, int y) {
    obj.draw();
    obj.move(x, y);
    { obj.getPosition() } -> std::convertible_to<std::pair<int, int>>;
};

class Circle {
public:
    void draw() const {
        std::cout << "Drawing circle at (" << x_ << ", " << y_ << ")\n";
    }
    
    void move(int x, int y) {
        x_ = x;
        y_ = y;
    }
    
    std::pair<int, int> getPosition() const {
        return {x_, y_};
    }
    
private:
    int x_ = 0, y_ = 0;
};

template<Drawable T>
void render(const T& shape) {
    shape.draw();
}

// 概念的组合和特化
template<typename T>
concept Number = Integral<T> || FloatingPoint<T>;

template<Number T>
constexpr T abs(T value) {
    if constexpr (std::is_signed_v<T>) {
        return value < 0 ? -value : value;
    } else {
        return value;
    }
}

void concepts_examples() {
    // 基本使用
    std::cout << add(5, 3) << std::endl;        // OK: int
    std::cout << add(2.5, 1.5) << std::endl;   // OK: double
    // add("hello", "world");                   // 编译错误：不满足Arithmetic概念
    
    // 容器概念
    std::vector<int> vec = {3, 1, 4, 1, 5};
    static_assert(Container<decltype(vec)>);
    static_assert(Sortable<decltype(vec)>);
    
    // 图形对象
    Circle circle;
    render(circle);
    
    // 数值概念
    std::cout << "abs(-5) = " << abs(-5) << std::endl;
    std::cout << "abs(3.14) = " << abs(-3.14) << std::endl;
}
```

### 2. 协程 (Coroutines)

协程提供了一种编写异步代码的新方式，使得异步编程更加直观和易于理解。

```cpp
#include <coroutine>
#include <iostream>
#include <thread>
#include <chrono>
#include <optional>

// 简单的协程返回类型
struct Task {
    struct promise_type {
        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    Task(std::coroutine_handle<promise_type> h) : coro(h) {}
    ~Task() {
        if (coro) coro.destroy();
    }
    
    // 禁止拷贝，允许移动
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&& other) noexcept : coro(other.coro) {
        other.coro = {};
    }
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = {};
        }
        return *this;
    }
};

// 生成器协程
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
    ~Generator() {
        if (coro) coro.destroy();
    }
    
    // 禁止拷贝，允许移动
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) noexcept : coro(other.coro) {
        other.coro = {};
    }
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = {};
        }
        return *this;
    }
    
    bool next() {
        coro.resume();
        return !coro.done();
    }
    
    T value() {
        return coro.promise().current_value;
    }
};

// 简单协程示例
Task simple_coroutine() {
    std::cout << "Coroutine started\n";
    co_await std::suspend_always{};
    std::cout << "Coroutine resumed\n";
}

// 生成器协程示例
Generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        auto temp = a;
        a = b;
        b = temp + b;
    }
}

Generator<int> range(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

// 异步任务协程
struct AsyncTask {
    struct promise_type {
        std::optional<int> result;
        
        AsyncTask get_return_object() {
            return AsyncTask{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        void return_value(int value) {
            result = value;
        }
        
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    AsyncTask(std::coroutine_handle<promise_type> h) : coro(h) {}
    ~AsyncTask() {
        if (coro) coro.destroy();
    }
    
    bool is_ready() const {
        return coro.done();
    }
    
    int get_result() {
        return coro.promise().result.value_or(0);
    }
};

AsyncTask async_computation(int n) {
    std::cout << "Starting async computation for " << n << std::endl;
    
    // 模拟异步工作
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    int result = n * n;
    std::cout << "Computation completed: " << result << std::endl;
    
    co_return result;
}

void coroutines_examples() {
    // 1. 简单协程
    auto task = simple_coroutine();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // 2. 生成器协程
    std::cout << "\nFibonacci sequence:\n";
    auto fib = fibonacci();
    for (int i = 0; i < 10 && fib.next(); ++i) {
        std::cout << fib.value() << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nRange 5-10:\n";
    auto r = range(5, 10);
    while (r.next()) {
        std::cout << r.value() << " ";
    }
    std::cout << std::endl;
    
    // 3. 异步任务
    std::cout << "\nAsync computation:\n";
    auto async_task = async_computation(7);
    
    // 等待完成
    while (!async_task.is_ready()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "Final result: " << async_task.get_result() << std::endl;
}
```

### 3. 模块 (Modules)

模块是C++20引入的新的代码组织方式，用于替代传统的头文件包含机制。

```cpp
// math_module.cpp - 模块实现文件
export module math_utils;

import <iostream>;
import <cmath>;

// 导出函数
export namespace math_utils {
    double add(double a, double b) {
        return a + b;
    }
    
    double multiply(double a, double b) {
        return a * b;
    }
    
    double power(double base, double exp) {
        return std::pow(base, exp);
    }
    
    // 导出类
    export class Calculator {
    private:
        double memory = 0.0;
        
    public:
        void store(double value) {
            memory = value;
        }
        
        double recall() const {
            return memory;
        }
        
        double calculate(double a, double b, char op) {
            switch (op) {
                case '+': return add(a, b);
                case '*': return multiply(a, b);
                case '^': return power(a, b);
                default: return 0.0;
            }
        }
    };
}

// 内部实现（不导出）
namespace {
    void internal_function() {
        std::cout << "This is internal to the module\n";
    }
}
```

```cpp
// string_module.cpp - 另一个模块示例
export module string_utils;

import <string>;
import <vector>;
import <algorithm>;
import <sstream>;

export namespace string_utils {
    // 字符串分割
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    // 字符串连接
    std::string join(const std::vector<std::string>& strings, const std::string& separator) {
        if (strings.empty()) return "";
        
        std::string result = strings[0];
        for (size_t i = 1; i < strings.size(); ++i) {
            result += separator + strings[i];
        }
        
        return result;
    }
    
    // 字符串转换
    std::string to_upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    
    std::string to_lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}
```

```cpp
// main.cpp - 使用模块
import math_utils;
import string_utils;
import <iostream>;
import <vector>;

int main() {
    // 使用数学模块
    std::cout << "Math operations:\n";
    std::cout << "2 + 3 = " << math_utils::add(2, 3) << std::endl;
    std::cout << "4 * 5 = " << math_utils::multiply(4, 5) << std::endl;
    std::cout << "2^8 = " << math_utils::power(2, 8) << std::endl;
    
    math_utils::Calculator calc;
    calc.store(100);
    std::cout << "Calculator memory: " << calc.recall() << std::endl;
    
    // 使用字符串模块
    std::cout << "\nString operations:\n";
    std::string text = "hello,world,cpp20";
    auto parts = string_utils::split(text, ',');
    
    std::cout << "Split result: ";
    for (const auto& part : parts) {
        std::cout << "[" << part << "] ";
    }
    std::cout << std::endl;
    
    std::string joined = string_utils::join(parts, " | ");
    std::cout << "Joined: " << joined << std::endl;
    
    std::cout << "Uppercase: " << string_utils::to_upper(joined) << std::endl;
    std::cout << "Lowercase: " << string_utils::to_lower(joined) << std::endl;
    
    return 0;
}
```

### 4. 范围 (Ranges)

C++20引入了ranges库，提供了更强大和易用的算法和视图。

```cpp
#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

namespace ranges = std::ranges;
namespace views = std::views;

void ranges_examples() {
    // 1. 基本范围操作
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 使用ranges算法
    std::cout << "Original: ";
    ranges::copy(numbers, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 查找
    auto it = ranges::find(numbers, 5);
    if (it != numbers.end()) {
        std::cout << "Found 5 at position " << std::distance(numbers.begin(), it) << std::endl;
    }
    
    // 2. 视图 (Views) - 惰性求值
    std::cout << "\nViews examples:\n";
    
    // 过滤偶数
    auto even_numbers = numbers | views::filter([](int n) { return n % 2 == 0; });
    std::cout << "Even numbers: ";
    for (int n : even_numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 变换（映射）
    auto squared = numbers | views::transform([](int n) { return n * n; });
    std::cout << "Squared: ";
    for (int n : squared) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 组合视图
    auto even_squares = numbers 
                       | views::filter([](int n) { return n % 2 == 0; })
                       | views::transform([](int n) { return n * n; });
    
    std::cout << "Even squares: ";
    for (int n : even_squares) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 3. 取前N个元素
    auto first_five = numbers | views::take(5);
    std::cout << "First 5: ";
    ranges::copy(first_five, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 4. 跳过前N个元素
    auto skip_three = numbers | views::drop(3);
    std::cout << "Skip first 3: ";
    ranges::copy(skip_three, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 5. 反转视图
    auto reversed = numbers | views::reverse;
    std::cout << "Reversed: ";
    ranges::copy(reversed, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 6. 字符串处理
    std::string text = "Hello World C++20";
    
    // 分割字符串视图
    auto words = text | views::split(' ');
    std::cout << "\nWords in text:\n";
    for (const auto& word : words) {
        std::cout << "- ";
        ranges::copy(word, std::ostream_iterator<char>(std::cout));
        std::cout << std::endl;
    }
    
    // 7. 生成范围
    auto iota_range = views::iota(1, 11); // 1到10
    std::cout << "Iota 1-10: ";
    ranges::copy(iota_range, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 8. 复杂的范围操作
    std::vector<std::string> words_vec = {"apple", "banana", "cherry", "date", "elderberry"};
    
    auto long_words_upper = words_vec
                           | views::filter([](const std::string& s) { return s.length() > 5; })
                           | views::transform([](const std::string& s) {
                               std::string upper = s;
                               ranges::transform(upper, upper.begin(), ::toupper);
                               return upper;
                           });
    
    std::cout << "Long words (uppercase): ";
    for (const auto& word : long_words_upper) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}
```

### 5. 三路比较运算符 (Spaceship Operator <=>)

三路比较运算符简化了比较操作的实现，可以自动生成所有比较运算符。

```cpp
#include <compare>
#include <iostream>
#include <string>

// 基本使用
struct Point {
    int x, y;
    
    // 默认三路比较
    auto operator<=>(const Point&) const = default;
    
    // 如果需要自定义比较逻辑
    /*
    std::strong_ordering operator<=>(const Point& other) const {
        if (auto cmp = x <=> other.x; cmp != 0) {
            return cmp;
        }
        return y <=> other.y;
    }
    */
};

// 更复杂的示例
class Person {
private:
    std::string name;
    int age;
    double salary;
    
public:
    Person(std::string n, int a, double s) : name(std::move(n)), age(a), salary(s) {}
    
    // 自定义比较逻辑：首先按年龄，然后按姓名，最后按薪水
    std::strong_ordering operator<=>(const Person& other) const {
        if (auto cmp = age <=> other.age; cmp != 0) {
            return cmp;
        }
        if (auto cmp = name <=> other.name; cmp != 0) {
            return cmp;
        }
        return salary <=> other.salary;
    }
    
    // 相等比较可以单独定义，或者依赖于<=>
    bool operator==(const Person& other) const {
        return (*this <=> other) == 0;
    }
    
    void print() const {
        std::cout << name << " (age: " << age << ", salary: " << salary << ")";
    }
};

// 部分比较示例
struct Temperature {
    double celsius;
    
    std::partial_ordering operator<=>(const Temperature& other) const {
        // 处理NaN情况
        if (std::isnan(celsius) || std::isnan(other.celsius)) {
            return std::partial_ordering::unordered;
        }
        return celsius <=> other.celsius;
    }
    
    bool operator==(const Temperature& other) const {
        return (*this <=> other) == 0;
    }
};

void spaceship_examples() {
    // 1. 基本点比较
    Point p1{1, 2};
    Point p2{1, 3};
    Point p3{1, 2};
    
    std::cout << "Point comparisons:\n";
    std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
    std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
    std::cout << "p1 > p2: " << (p1 > p2) << std::endl;
    
    // 2. 人员比较
    Person alice("Alice", 30, 50000);
    Person bob("Bob", 25, 45000);
    Person charlie("Charlie", 30, 55000);
    
    std::cout << "\nPerson comparisons:\n";
    
    std::cout << "Alice vs Bob: ";
    alice.print();
    std::cout << " vs ";
    bob.print();
    if (alice > bob) {
        std::cout << " -> Alice is greater\n";
    } else {
        std::cout << " -> Bob is greater or equal\n";
    }
    
    std::cout << "Alice vs Charlie: ";
    alice.print();
    std::cout << " vs ";
    charlie.print();
    if (alice < charlie) {
        std::cout << " -> Alice is less\n";
    } else {
        std::cout << " -> Charlie is less or equal\n";
    }
    
    // 3. 温度比较（部分排序）
    Temperature t1{20.0};
    Temperature t2{25.0};
    Temperature t3{std::numeric_limits<double>::quiet_NaN()};
    
    std::cout << "\nTemperature comparisons:\n";
    std::cout << "20°C < 25°C: " << (t1 < t2) << std::endl;
    std::cout << "20°C == NaN: " << (t1 == t3) << std::endl;
    
    auto cmp = t1 <=> t3;
    if (cmp == std::partial_ordering::unordered) {
        std::cout << "20°C and NaN are unordered\n";
    }
}
```

## 其他C++20特性

### 指定初始化器 (Designated Initializers)
```cpp
struct Config {
    std::string name;
    int port = 8080;
    bool debug = false;
};

void designated_initializers() {
    // C++20指定初始化器
    Config cfg{
        .name = "MyServer",
        .port = 9000,
        .debug = true
    };
    
    std::cout << "Config: " << cfg.name << ":" << cfg.port 
              << " (debug: " << cfg.debug << ")\n";
}
```

### consteval 函数
```cpp
// consteval确保函数在编译时求值
consteval int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

void consteval_example() {
    constexpr int fact5 = factorial(5); // 编译时计算
    std::cout << "5! = " << fact5 << std::endl;
    
    // int runtime_n = 5;
    // factorial(runtime_n); // 编译错误：不能在运行时调用
}
```

## 实践练习

### 练习1：概念驱动设计
使用concepts设计一个通用的容器算法库：
- 定义不同类型的容器概念
- 实现基于概念的算法重载
- 提供清晰的错误信息

### 练习2：协程异步框架
实现一个简单的异步任务框架：
- 支持异步任务链
- 实现简单的任务调度器
- 支持错误处理

### 练习3：模块化数学库
使用modules创建一个数学计算库：
- 分离接口和实现
- 支持复数运算
- 提供统计函数

### 练习4：范围处理管道
使用ranges实现数据处理管道：
- 文本处理管道
- 数值计算管道
- 支持自定义视图

## 今日总结
通过学习C++20新特性，你应该掌握：
1. 使用concepts约束模板参数，提供更好的错误信息
2. 使用协程编写异步和生成器代码
3. 使用modules组织大型项目代码
4. 使用ranges简化算法和数据处理
5. 使用三路比较运算符简化比较操作

## 明天预告
明天我们将进行项目实战，实现常用的数据结构，包括链表、栈、队列、二叉搜索树和哈希表等。

[返回第四周](/plan/week4/) | [上一天：第25天](/plan/week4/day25/) | [下一天：第27天](/plan/week4/day27/)
