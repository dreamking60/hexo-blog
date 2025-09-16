---
title: C++ 学习计划 - 第三周第18天：Lambda表达式
date: 2025-09-16 18:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
    - Lambda
    - Functional Programming
layout: page
menu_id: plan
permalink: /plan/week3/day18/
---

# 第18天：Lambda表达式

## 学习目标
掌握C++11引入的Lambda表达式，理解函数式编程思想，学会使用Lambda表达式简化代码和提高可读性。

## 核心知识点

### 1. Lambda表达式概述

#### 什么是Lambda表达式？
Lambda表达式是C++11引入的匿名函数，它允许在需要函数的地方内联定义函数，使代码更加简洁和灵活。

#### 基本语法
```cpp
[捕获列表](参数列表) -> 返回类型 { 函数体 }
```

#### 为什么使用Lambda？
- **简化代码**：减少函数对象的定义
- **就地定义**：在使用处直接定义逻辑
- **提高可读性**：逻辑更加集中
- **函数式编程**：支持函数式编程范式

#### 参考资料
- [Lambda表达式 - cppreference.com](https://en.cppreference.com/w/cpp/language/lambda)
- [C++ Lambda表达式详解](https://changkun.de/modern-cpp/zh-cn/03-runtime/#3-3-lambda-%E8%A1%A8%E8%BE%BE%E5%BC%8F)

### 2. 基本Lambda表达式

#### 简单示例
```cpp
// 最简单的Lambda表达式
auto lambda = []() { std::cout << "Hello Lambda!" << std::endl; };
lambda();

// 带参数的Lambda
auto add = [](int a, int b) { return a + b; };
int result = add(3, 4);

// 多行Lambda
auto complex = [](int x) {
    if (x > 0) {
        return x * 2;
    } else {
        return -x;
    }
};
```

#### 与STL算法结合
```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 过滤偶数
std::vector<int> evens;
std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens),
             [](int n) { return n % 2 == 0; });

// 转换元素
std::vector<int> squares;
std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares),
               [](int n) { return n * n; });

// 排序
std::sort(numbers.begin(), numbers.end(),
          [](int a, int b) { return a > b; });  // 降序
```

#### 参考资料
- [Lambda表达式与STL](https://www.fluentcpp.com/2018/03/30/is-stdfor_each-obsolete/)
- [C++ Lambda表达式实用指南](https://blog.csdn.net/weixin_43914604/article/details/105285000)

### 3. 捕获列表 (Capture List)

#### 值捕获
```cpp
int x = 10;
int y = 20;

// 值捕获
auto lambda1 = [x, y]() {
    std::cout << "x = " << x << ", y = " << y << std::endl;
};

// 修改外部变量不会影响Lambda中的值
x = 100;
y = 200;
lambda1();  // 仍然输出原来的值
```

#### 引用捕获
```cpp
int x = 10;
int y = 20;

// 引用捕获
auto lambda2 = [&x, &y]() {
    std::cout << "x = " << x << ", y = " << y << std::endl;
    x = 100;  // 修改外部变量
    y = 200;
};

lambda2();
std::cout << "修改后: x = " << x << ", y = " << y << std::endl;
```

#### 混合捕获
```cpp
int a = 1, b = 2, c = 3, d = 4;

// 混合捕获：a值捕获，b引用捕获
auto lambda3 = [a, &b, c, &d]() {
    std::cout << "a = " << a << ", b = " << b 
              << ", c = " << c << ", d = " << d << std::endl;
    b = 20;  // 可以修改
    d = 40;  // 可以修改
    // a = 10;  // 编译错误，不能修改值捕获的变量
};
```

#### 默认捕获
```cpp
int x = 10;
int y = 20;
int z = 30;

// 默认值捕获所有变量
auto lambda4 = [=]() {
    std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
};

// 默认引用捕获所有变量
auto lambda5 = [&]() {
    std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
    x = 100;  // 可以修改
};

// 混合默认捕获
auto lambda6 = [=, &x]() {  // 默认值捕获，但x引用捕获
    std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
    x = 200;  // 可以修改x
};
```

#### 参考资料
- [Lambda捕获详解](https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture)
- [C++ Lambda捕获最佳实践](https://www.fluentcpp.com/2018/09/28/capture-by-reference-and-capture-by-value-in-lambdas/)

### 4. 参数列表和返回类型

#### 参数列表
```cpp
// 无参数
auto lambda1 = []() { std::cout << "无参数Lambda" << std::endl; };

// 单参数
auto lambda2 = [](int x) { return x * 2; };

// 多参数
auto lambda3 = [](int a, int b, int c) { return a + b + c; };

// 与STL算法结合
std::vector<int> numbers = {1, 2, 3, 4, 5};
int sum = std::accumulate(numbers.begin(), numbers.end(), 0,
                          [](int acc, int n) { return acc + n * n; });
```

#### 返回类型
```cpp
// 自动推导返回类型
auto lambda1 = [](int x) { return x * 2; };

// 显式指定返回类型
auto lambda2 = [](int x) -> int { return x * 2; };
auto lambda3 = [](int x) -> double { return x * 2.5; };

// 复杂返回类型
auto lambda4 = [](int x) -> std::pair<int, int> {
    return {x, x * x};
};

// 条件返回
auto lambda5 = [](int x) -> int {
    if (x > 0) {
        return x * 2;
    } else {
        return -x;
    }
};
```

#### 参考资料
- [Lambda参数和返回类型](https://www.learncpp.com/cpp-tutorial/lambda-captures/)

### 5. 泛型Lambda (C++14)

#### 基本语法
```cpp
// 泛型Lambda
auto print = [](const auto& value) {
    std::cout << value << " ";
};

// 使用泛型Lambda
std::vector<int> numbers = {1, 2, 3, 4, 5};
std::vector<double> doubles = {1.1, 2.2, 3.3, 4.4, 5.5};

std::for_each(numbers.begin(), numbers.end(), print);
std::for_each(doubles.begin(), doubles.end(), print);
```

#### 泛型Lambda与STL算法
```cpp
// 泛型Lambda与STL算法
auto multiply = [](const auto& a, const auto& b) {
    return a * b;
};

std::cout << "multiply(3, 4) = " << multiply(3, 4) << std::endl;
std::cout << "multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << std::endl;
```

#### 参考资料
- [泛型Lambda详解](https://en.cppreference.com/w/cpp/language/lambda#Generic_lambdas)
- [C++14泛型Lambda](https://www.bfilipek.com/2016/02/notes-on-c-sfinae.html#generic-lambdas)

### 6. Lambda表达式与函数对象

#### 函数对象 vs Lambda
```cpp
// 传统函数对象
class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    int operator()(int x) const {
        return x * factor;
    }
};

// 使用函数对象
Multiplier multiplier(3);
std::transform(numbers.begin(), numbers.end(), result.begin(), multiplier);

// 使用Lambda表达式（更简洁）
std::transform(numbers.begin(), numbers.end(), result.begin(),
               [](int x) { return x * 3; });
```

#### std::function
```cpp
#include <functional>

// 存储Lambda表达式
std::function<int(int)> func = [](int x) { return x * 2; };
int result = func(5);

// 存储在容器中
std::vector<std::function<void()>> handlers;
handlers.push_back([]() { std::cout << "Handler 1" << std::endl; });
handlers.push_back([]() { std::cout << "Handler 2" << std::endl; });

for (const auto& handler : handlers) {
    handler();
}
```

#### 参考资料
- [std::function详解](https://en.cppreference.com/w/cpp/utility/functional/function)
- [Lambda vs 函数对象性能比较](https://www.fluentcpp.com/2018/05/15/how-to-store-a-lambda-in-a-variable-in-c/)

### 7. Lambda表达式高级应用

#### 递归Lambda
```cpp
// C++14递归Lambda
auto factorial = [](int n) {
    auto impl = [](int n, auto& self) -> int {
        return n <= 1 ? 1 : n * self(n - 1, self);
    };
    return impl(n, impl);
};

std::cout << "5! = " << factorial(5) << std::endl;
```

#### 立即调用Lambda
```cpp
// IIFE (Immediately Invoked Function Expression)
int result = [](int x, int y) {
    return x * x + y * y;
}(3, 4);

// 复杂初始化
const auto data = []() {
    std::vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i * i);
    }
    return vec;
}();
```

#### 参考资料
- [Lambda表达式高级技巧](https://www.fluentcpp.com/2017/01/05/curiously-recurring-c-bugs-in-lambdas/)

## 实用教程和文档

### 官方文档
- [Lambda表达式 - cppreference.com](https://en.cppreference.com/w/cpp/language/lambda)
- [C++ Lambda表达式 - Microsoft Docs](https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp)

### 优质教程
- [现代C++ Lambda表达式完全指南](https://changkun.de/modern-cpp/zh-cn/03-runtime/#3-3-lambda-%E8%A1%A8%E8%BE%BE%E5%BC%8F)
- [C++ Lambda表达式深入理解](https://blog.csdn.net/weixin_43914604/article/details/105285000)
- [Lambda表达式最佳实践](https://www.fluentcpp.com/2018/01/30/most-vexing-parse-lambdas/)

### 实战案例
- [Lambda在STL中的应用](https://www.cppstories.com/2014/07/lambdas-in-stl-algorithms/)
- [函数式编程与Lambda](https://www.bfilipek.com/2017/07/lambdas-story.html)

## 今日练习

### 基础练习
1. 实现一个函数式编程工具类，提供map、filter、reduce等功能
2. 编写一个事件处理器，使用Lambda表达式处理不同类型的事件
3. 实现一个配置管理器，使用Lambda表达式进行配置验证和处理

### 算法题推荐
1. [LeetCode 49. Group Anagrams](https://leetcode.com/problems/group-anagrams/) - 使用Lambda表达式进行字符串处理
2. [LeetCode 347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) - 使用Lambda表达式进行排序和比较
3. [LeetCode 451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) - 使用Lambda表达式进行字符频率排序
4. [LeetCode 692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/) - 使用Lambda表达式进行单词频率排序

## 学习要点总结

1. **语法结构**：掌握Lambda表达式的完整语法
2. **捕获列表**：理解值捕获、引用捕获和混合捕获
3. **与STL结合**：熟练使用Lambda表达式与STL算法
4. **泛型Lambda**：掌握C++14的泛型Lambda特性
5. **函数式编程**：理解函数式编程思想

## 下一天预告
明天我们将学习移动语义，包括左值与右值、移动构造函数、std::move等C++11的重要特性。

[上一天：智能指针](/plan/week3/day17/) | [返回第三周总览](/plan/week3/) | [下一天：移动语义](/plan/week3/day19/)
