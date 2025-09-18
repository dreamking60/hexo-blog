---
title: C++ 学习计划 - 第5天:引用
date: 2025-09-16 10:15:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week1
    - Day5
layout: page
menu_id: plan
permalink: /plan/week1/day5/
---

# 第5天：引用

## 学习目标
掌握引用的概念和使用场景，理解引用与指针的区别，学会在函数中正确使用引用。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - References](https://en.cppreference.com/w/cpp/language/reference) - C++官方引用文档
- [LearnCpp - References](https://www.learncpp.com/cpp-tutorial/references/) - 引用详解教程
- [GeeksforGeeks - References in C++](https://www.geeksforgeeks.org/references-in-c/) - 引用基础知识

### 🎥 视频教程
- [The Cherno C++ References](https://www.youtube.com/watch?v=sxHng1iufQE) - 引用概念讲解
- [C++ References vs Pointers](https://www.youtube.com/watch?v=IzoFn3dfsPA) - 引用与指针对比

### 📖 深入阅读
- [C++ Primer 第5版 - 第2.3.1节](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 引用详解
- [Effective C++ - 条款21](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 必须返回对象时别返回其reference

## 学习内容

### 1. 引用基础概念
- 引用的定义和声明
- 引用的初始化规则
- 引用与别名的概念
- 引用的限制

### 2. 引用与指针的区别
- 语法差异
- 内存占用差异
- 安全性对比
- 使用场景选择

### 3. 引用作为函数参数
- 引用参数的优势
- 避免拷贝开销
- 修改原始变量
- 常量引用参数

### 4. 引用作为返回值
- 返回引用的条件
- 左值引用返回
- 链式调用
- 返回引用的陷阱

### 5. 常量引用
- const引用的作用
- 临时对象绑定
- 参数传递优化
- 只读访问保护

## 重点概念和代码示例

### 引用基础
```cpp
#include <iostream>
using namespace std;

void referenceBasics() {
    cout << "=== 引用基础 ===" << endl;
    
    // 引用的声明和初始化
    int value = 42;
    int& ref = value;  // ref是value的引用（别名）
    
    cout << "value = " << value << endl;        // 输出: 42
    cout << "ref = " << ref << endl;            // 输出: 42
    cout << "&value = " << &value << endl;      // 地址相同
    cout << "&ref = " << &ref << endl;          // 地址相同
    
    // 通过引用修改值
    ref = 100;
    cout << "修改ref后，value = " << value << endl;  // 输出: 100
    
    // 引用不能重新绑定
    int another = 200;
    // int& ref = another;  // 错误！引用必须在声明时初始化
    ref = another;  // 这是赋值，不是重新绑定
    cout << "赋值后，value = " << value << endl;  // 输出: 200
}
```

### 引用与指针对比
```cpp
void referenceVsPointer() {
    cout << "\n=== 引用与指针对比 ===" << endl;
    
    int x = 10, y = 20;
    
    // 指针方式
    int* ptr = &x;
    cout << "指针: *ptr = " << *ptr << endl;
    ptr = &y;  // 指针可以重新指向
    cout << "重新指向后: *ptr = " << *ptr << endl;
    *ptr = 30;
    cout << "修改后 y = " << y << endl;
    
    // 引用方式
    int& ref = x;
    cout << "引用: ref = " << ref << endl;
    // ref = &y;  // 错误！引用不能重新绑定
    ref = y;  // 这是赋值，x的值变为y的值
    cout << "赋值后 x = " << x << endl;
    
    // 空指针 vs 引用
    int* nullPtr = nullptr;  // 指针可以为空
    // int& nullRef = nullptr;  // 错误！引用必须绑定到对象
    
    cout << "指针大小: " << sizeof(ptr) << " bytes" << endl;
    cout << "引用大小: " << sizeof(ref) << " bytes (与所引用对象相同)" << endl;
}
```

### 引用作为函数参数
```cpp
// 值传递
void passByValue(int x) {
    x = 100;  // 不影响原变量
}

// 引用传递
void passByReference(int& x) {
    x = 100;  // 影响原变量
}

// 常量引用传递
void passByConstReference(const int& x) {
    // x = 100;  // 错误！不能修改const引用
    cout << "常量引用值: " << x << endl;
}

// 大对象的引用传递
void processString(const string& str) {
    cout << "字符串长度: " << str.length() << endl;
    // 避免了字符串的拷贝开销
}

void referenceParameters() {
    cout << "\n=== 引用作为函数参数 ===" << endl;
    
    int value = 42;
    cout << "原始值: " << value << endl;
    
    passByValue(value);
    cout << "值传递后: " << value << endl;  // 不变
    
    passByReference(value);
    cout << "引用传递后: " << value << endl;  // 改变
    
    passByConstReference(value);
    
    string longString = "这是一个很长的字符串，用来演示引用传递的效率优势";
    processString(longString);
}
```

### 引用作为返回值
```cpp
class IntArray {
private:
    int data[10];
    int size;
    
public:
    IntArray() : size(0) {}
    
    // 返回引用，支持链式调用和左值使用
    int& operator[](int index) {
        if (index >= 0 && index < 10) {
            return data[index];
        }
        throw out_of_range("Index out of range");
    }
    
    // 常量版本，返回常量引用
    const int& operator[](int index) const {
        if (index >= 0 && index < 10) {
            return data[index];
        }
        throw out_of_range("Index out of range");
    }
    
    // 返回引用支持链式操作
    IntArray& push_back(int value) {
        if (size < 10) {
            data[size++] = value;
        }
        return *this;
    }
    
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void referenceReturns() {
    cout << "\n=== 引用作为返回值 ===" << endl;
    
    IntArray arr;
    
    // 链式调用
    arr.push_back(1).push_back(2).push_back(3);
    cout << "链式添加后: ";
    arr.print();
    
    // 通过引用返回修改元素
    arr[0] = 100;
    arr[1] = 200;
    cout << "修改后: ";
    arr.print();
}
```

### 常量引用的特殊用法
```cpp
void constReferenceSpecial() {
    cout << "\n=== 常量引用特殊用法 ===" << endl;
    
    // 常量引用可以绑定到临时对象
    const int& ref1 = 42;  // 临时对象
    const int& ref2 = 3 + 4;  // 表达式结果
    
    cout << "临时对象引用: " << ref1 << endl;
    cout << "表达式引用: " << ref2 << endl;
    
    // 常量引用可以绑定到不同类型（会发生隐式转换）
    double pi = 3.14159;
    const int& intRef = pi;  // double转换为int
    cout << "类型转换引用: " << intRef << endl;
    
    // 延长临时对象生命周期
    const string& tempStr = string("Hello") + " World";
    cout << "临时字符串: " << tempStr << endl;
}
```

## 实践练习

### 练习1：引用基础操作
```cpp
void exercise1() {
    cout << "\n=== 练习1：引用基础操作 ===" << endl;
    
    // 1. 创建变量和引用
    int a = 10, b = 20;
    int& refA = a;
    
    cout << "初始值 a = " << a << ", refA = " << refA << endl;
    
    // 2. 通过引用修改值
    refA += 5;
    cout << "refA += 5 后，a = " << a << endl;
    
    // 3. 引用赋值（实际是值赋值）
    refA = b;
    cout << "refA = b 后，a = " << a << ", b = " << b << endl;
    
    // 4. 验证引用和原变量地址相同
    cout << "&a = " << &a << ", &refA = " << &refA << endl;
    cout << "地址相同: " << (&a == &refA) << endl;
}
```

### 练习2：函数参数优化
```cpp
// 低效版本 - 值传递
double calculateDistance1(pair<double, double> p1, pair<double, double> p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return sqrt(dx * dx + dy * dy);
}

// 高效版本 - 常量引用传递
double calculateDistance2(const pair<double, double>& p1, const pair<double, double>& p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return sqrt(dx * dx + dy * dy);
}

void exercise2() {
    cout << "\n=== 练习2：函数参数优化 ===" << endl;
    
    pair<double, double> point1 = {0.0, 0.0};
    pair<double, double> point2 = {3.0, 4.0};
    
    double dist1 = calculateDistance1(point1, point2);
    double dist2 = calculateDistance2(point1, point2);
    
    cout << "距离计算结果1: " << dist1 << endl;
    cout << "距离计算结果2: " << dist2 << endl;
    cout << "结果相同: " << (dist1 == dist2) << endl;
    
    // 在实际应用中，引用版本避免了pair对象的拷贝
}
```

### 练习3：实现swap函数
```cpp
template<typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void exercise3() {
    cout << "\n=== 练习3：实现swap函数 ===" << endl;
    
    // 交换整数
    int x = 100, y = 200;
    cout << "交换前: x = " << x << ", y = " << y << endl;
    mySwap(x, y);
    cout << "交换后: x = " << x << ", y = " << y << endl;
    
    // 交换字符串
    string s1 = "Hello", s2 = "World";
    cout << "交换前: s1 = " << s1 << ", s2 = " << s2 << endl;
    mySwap(s1, s2);
    cout << "交换后: s1 = " << s1 << ", s2 = " << s2 << endl;
}
```

### 练习4：链式操作类
```cpp
class Calculator {
private:
    double value;
    
public:
    Calculator(double initial = 0) : value(initial) {}
    
    Calculator& add(double x) {
        value += x;
        return *this;
    }
    
    Calculator& subtract(double x) {
        value -= x;
        return *this;
    }
    
    Calculator& multiply(double x) {
        value *= x;
        return *this;
    }
    
    Calculator& divide(double x) {
        if (x != 0) {
            value /= x;
        }
        return *this;
    }
    
    double getValue() const {
        return value;
    }
    
    void reset(double newValue = 0) {
        value = newValue;
    }
};

void exercise4() {
    cout << "\n=== 练习4：链式操作类 ===" << endl;
    
    Calculator calc(10);
    
    // 链式计算: ((10 + 5) * 2 - 3) / 4
    double result = calc.add(5).multiply(2).subtract(3).divide(4).getValue();
    
    cout << "链式计算结果: " << result << endl;
    
    // 重置并进行新计算
    calc.reset(100);
    result = calc.subtract(20).multiply(0.5).add(10).getValue();
    cout << "第二次计算结果: " << result << endl;
}
```

## 算法练习题

### LeetCode相关题目
1. **[反转字符串](https://leetcode.cn/problems/reverse-string/)** - 使用引用交换字符
2. **[移动零](https://leetcode.cn/problems/move-zeroes/)** - 引用优化数组操作
3. **[两数之和 II](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/)** - 引用返回结果

### 练习5：实现高效的数组操作
```cpp
class EfficientArray {
private:
    vector<int> data;
    
public:
    // 返回引用，支持修改
    int& at(size_t index) {
        if (index >= data.size()) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 常量版本
    const int& at(size_t index) const {
        if (index >= data.size()) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 添加元素，返回引用支持链式调用
    EfficientArray& push_back(int value) {
        data.push_back(value);
        return *this;
    }
    
    // 查找并返回引用
    int& find(int value) {
        for (auto& element : data) {
            if (element == value) {
                return element;
            }
        }
        throw runtime_error("Value not found");
    }
    
    size_t size() const { return data.size(); }
    
    void print() const {
        for (const auto& element : data) {
            cout << element << " ";
        }
        cout << endl;
    }
};

void exercise5() {
    cout << "\n=== 练习5：高效数组操作 ===" << endl;
    
    EfficientArray arr;
    
    // 链式添加
    arr.push_back(1).push_back(2).push_back(3).push_back(4).push_back(5);
    cout << "初始数组: ";
    arr.print();
    
    // 通过引用修改元素
    arr.at(2) = 100;
    cout << "修改索引2后: ";
    arr.print();
    
    // 查找并修改
    try {
        arr.find(4) = 400;
        cout << "查找并修改4为400后: ";
        arr.print();
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}
```

## 常见错误与注意事项

### 1. 引用未初始化
```cpp
void referenceErrors() {
    // int& ref;  // 错误！引用必须初始化
    
    // 正确做法
    int value = 10;
    int& ref = value;
}
```

### 2. 返回局部变量的引用
```cpp
// 危险的做法
int& dangerousFunction() {
    int local = 42;
    return local;  // 错误！返回局部变量的引用
}

// 正确的做法
int& safeFunction(int& param) {
    return param;  // 返回参数的引用是安全的
}
```

### 3. 常量引用绑定
```cpp
void constReferenceBinding() {
    int value = 10;
    const int& constRef = value;  // 可以
    // constRef = 20;  // 错误！不能修改常量引用
    
    // 临时对象绑定
    const int& tempRef = 42;  // 可以
    // int& tempRef2 = 42;  // 错误！非常量引用不能绑定临时对象
}
```

## 学习检查点

- [ ] 理解引用的基本概念和语法
- [ ] 掌握引用与指针的区别和使用场景
- [ ] 熟练使用引用作为函数参数
- [ ] 理解引用作为返回值的用法和注意事项
- [ ] 掌握常量引用的特殊用法
- [ ] 了解引用的限制和常见错误
- [ ] 能够使用引用优化程序性能

## 完整示例程序

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
using namespace std;

int main() {
    cout << "=== C++ 引用学习 ===" << endl;
    
    // 运行所有示例和练习
    referenceBasics();
    referenceVsPointer();
    referenceParameters();
    referenceReturns();
    constReferenceSpecial();
    
    exercise1();
    exercise2();
    exercise3();
    exercise4();
    exercise5();
    
    return 0;
}
```

[返回第一周](/plan/week1/) | [上一天：指针基础](/plan/week1/day4/) | [下一天：动态内存分配](/plan/week1/day6/)
