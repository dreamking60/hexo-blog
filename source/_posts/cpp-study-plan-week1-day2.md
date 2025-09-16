---
title: C++ 学习计划 - 第2天：函数与作用域
date: 2025-09-16 10:12:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week1
    - Day2
layout: page
menu_id: plan
permalink: /plan/week1/day2/
---

# 第2天：函数与作用域

## 学习目标
掌握函数定义、调用和作用域规则，理解参数传递机制和函数重载。

## 学习内容

### 1. 函数声明与定义
- 函数声明（函数原型）
- 函数定义
- 函数重载
- 默认参数
- 内联函数

### 2. 参数传递机制
- **值传递**：传递参数的副本
- **引用传递**：传递参数的别名
- **指针传递**：传递参数的地址
- 参数传递的性能考虑

### 3. 函数重载
- 重载的条件
- 重载解析过程
- 重载与类型转换
- 重载的注意事项

### 4. 作用域与生存期
- 局部作用域
- 全局作用域
- 块作用域
- 命名空间作用域
- 静态变量

### 5. 递归函数
- 递归的基本概念
- 递归的终止条件
- 递归的性能考虑
- 尾递归优化

## 重点概念

### 函数声明与定义
```cpp
// 函数声明（在头文件中）
int add(int a, int b);
double calculateArea(double radius);

// 函数定义（在源文件中）
int add(int a, int b) {
    return a + b;
}

double calculateArea(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}
```

### 参数传递方式
```cpp
// 值传递
void passByValue(int x) {
    x = 100;  // 不影响原变量
}

// 引用传递
void passByReference(int& x) {
    x = 100;  // 影响原变量
}

// 指针传递
void passByPointer(int* x) {
    *x = 100;  // 影响原变量
}

// 常量引用传递（推荐用于大对象）
void passByConstReference(const string& str) {
    // 不能修改str，但避免了拷贝
}
```

### 函数重载
```cpp
// 参数个数不同
int add(int a, int b);
int add(int a, int b, int c);

// 参数类型不同
int add(int a, int b);
double add(double a, double b);

// 参数顺序不同
void print(int a, double b);
void print(double a, int b);
```

### 默认参数
```cpp
// 默认参数必须从右到左连续
void printInfo(string name, int age = 18, string city = "Unknown") {
    cout << "Name: " << name << ", Age: " << age << ", City: " << city << endl;
}

// 调用示例
printInfo("Alice");           // 使用默认参数
printInfo("Bob", 25);         // 部分使用默认参数
printInfo("Charlie", 30, "Beijing");  // 不使用默认参数
```

### 递归函数
```cpp
// 斐波那契数列（递归实现）
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 阶乘（递归实现）
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 尾递归优化版本
int factorialTail(int n, int acc = 1) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, n * acc);
}
```

## 作用域详解

### 局部作用域
```cpp
void function() {
    int localVar = 10;  // 局部变量
    {
        int blockVar = 20;  // 块作用域变量
        // blockVar 在这里可见
    }
    // blockVar 在这里不可见
    // localVar 在这里可见
}
```

### 全局作用域
```cpp
int globalVar = 100;  // 全局变量

void function1() {
    globalVar = 200;  // 可以修改全局变量
}

void function2() {
    cout << globalVar << endl;  // 可以访问全局变量
}
```

### 静态变量
```cpp
void counter() {
    static int count = 0;  // 静态局部变量
    count++;
    cout << "Count: " << count << endl;
}

// 每次调用counter()，count都会保持之前的值
```

## 实践练习

### 练习1：基本函数操作
实现各种数学运算函数，包括加减乘除、幂运算等。

### 练习2：参数传递比较
比较值传递、引用传递和指针传递的性能差异。

### 练习3：函数重载应用
实现一个字符串处理类，支持多种参数类型的构造函数。

### 练习4：递归算法实现
实现常见的递归算法，如汉诺塔、快速排序等。

## 常见错误与注意事项

1. **函数声明与定义不匹配**：参数类型、个数、顺序必须一致
2. **递归没有终止条件**：会导致栈溢出
3. **引用传递未初始化**：会导致编译错误
4. **函数重载歧义**：编译器无法确定调用哪个函数
5. **默认参数位置错误**：默认参数必须从右到左连续

## 性能考虑

1. **小对象使用值传递**：避免不必要的间接访问
2. **大对象使用引用传递**：避免拷贝开销
3. **只读参数使用const引用**：既避免拷贝又防止修改
4. **频繁调用的小函数使用内联**：减少函数调用开销

## 学习检查点

- [ ] 能够正确声明和定义函数
- [ ] 理解不同参数传递方式的区别和适用场景
- [ ] 掌握函数重载的规则和使用方法
- [ ] 理解作用域和生存期的概念
- [ ] 能够编写递归函数并理解其工作原理
- [ ] 了解函数调用的性能考虑

## 扩展阅读

- C++ Primer 第6章：函数
- Effective C++ 条款20-25：函数设计
- 了解函数指针和函数对象的概念

[返回第一周](/plan/week1/) | [上一天：变量与数据类型](/plan/week1/day1/) | [下一天：数组与字符串](/plan/week1/day3/)
