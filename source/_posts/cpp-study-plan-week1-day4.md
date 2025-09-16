---
title: C++ 学习计划 - 第4天：指针基础
date: 2025-09-16 10:14:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week1
    - Day4
layout: page
menu_id: plan
permalink: /plan/week1/day4/
---

# 第4天：指针基础

## 学习目标
深入理解指针的概念和使用，掌握指针运算和内存管理基础。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Pointers](https://en.cppreference.com/w/cpp/language/pointer) - C++官方指针文档
- [LearnCpp - Pointers](https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/) - 指针入门教程
- [GeeksforGeeks - Pointers in C++](https://www.geeksforgeeks.org/pointers-in-c-and-cpp-set-1-introduction-arithmetic-and-array/) - 指针详解

### 🎥 视频教程
- [The Cherno C++ Pointers](https://www.youtube.com/watch?v=DTxHyVn0ODg) - 指针概念讲解
- [C++ Pointers Explained](https://www.youtube.com/watch?v=zuegQmMdy8M) - 指针使用实例

### 📖 深入阅读
- [C++ Primer 第5版 - 第2.3节](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 指针和引用
- [Effective C++ - 条款13](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 以对象管理资源

## 学习内容

### 1. 指针基础概念
- 指针的定义和声明
- 指针与内存地址
- 解引用操作符
- 空指针和野指针

### 2. 指针运算
- 指针算术运算
- 指针比较
- 指针的递增和递减
- 指针与数组的关系

### 3. 指针与数组
- 数组名作为指针
- 指针访问数组元素
- 指针遍历数组
- 多维数组的指针操作

### 4. 指针作为函数参数
- 指针参数传递
- 通过指针修改变量值
- 函数返回指针
- 指针参数的安全性

### 5. 指针的指针
- 二级指针概念
- 指针数组
- 数组指针
- 多级指针的应用

## 重点概念和代码示例

### 指针声明与初始化
```cpp
#include <iostream>
using namespace std;

void pointerBasics() {
    // 指针声明
    int* ptr;           // 声明一个指向int的指针
    int value = 42;
    
    // 指针初始化
    ptr = &value;       // ptr指向value的地址
    
    // 解引用
    cout << "value = " << value << endl;        // 输出: 42
    cout << "*ptr = " << *ptr << endl;          // 输出: 42
    cout << "ptr = " << ptr << endl;            // 输出: 地址值
    cout << "&value = " << &value << endl;      // 输出: 地址值
    
    // 通过指针修改值
    *ptr = 100;
    cout << "value after *ptr = 100: " << value << endl;  // 输出: 100
}
```

### 指针运算
```cpp
void pointerArithmetic() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // 指向数组第一个元素
    
    cout << "指针运算演示：" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "ptr + " << i << " = " << ptr + i 
             << ", value = " << *(ptr + i) << endl;
    }
    
    // 指针递增
    ptr++;
    cout << "ptr++ 后指向: " << *ptr << endl;  // 输出: 20
    
    // 指针减法
    int* ptr2 = &arr[4];
    cout << "两指针差值: " << ptr2 - ptr << endl;  // 输出: 3
}
```

### 指针与数组
```cpp
void pointerAndArray() {
    int arr[] = {1, 2, 3, 4, 5};
    
    // 数组名就是指向第一个元素的指针
    cout << "arr = " << arr << endl;
    cout << "&arr[0] = " << &arr[0] << endl;
    cout << "arr == &arr[0]: " << (arr == &arr[0]) << endl;
    
    // 用指针访问数组
    int* ptr = arr;
    for (int i = 0; i < 5; i++) {
        cout << "arr[" << i << "] = " << arr[i] 
             << ", *(ptr + " << i << ") = " << *(ptr + i) << endl;
    }
    
    // 指针遍历数组
    cout << "指针遍历: ";
    for (int* p = arr; p < arr + 5; p++) {
        cout << *p << " ";
    }
    cout << endl;
}
```

### 指针作为函数参数
```cpp
// 交换两个变量的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 查找数组中的最大值
int* findMax(int* arr, int size) {
    if (size <= 0) return nullptr;
    
    int* maxPtr = arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *maxPtr) {
            maxPtr = arr + i;
        }
    }
    return maxPtr;
}

void pointerParameters() {
    int x = 10, y = 20;
    cout << "交换前: x = " << x << ", y = " << y << endl;
    swap(&x, &y);
    cout << "交换后: x = " << x << ", y = " << y << endl;
    
    int arr[] = {3, 7, 2, 9, 1};
    int* maxPtr = findMax(arr, 5);
    if (maxPtr) {
        cout << "最大值: " << *maxPtr << ", 位置: " << (maxPtr - arr) << endl;
    }
}
```

### 二级指针
```cpp
void doublePointer() {
    int value = 100;
    int* ptr = &value;
    int** pptr = &ptr;  // 指向指针的指针
    
    cout << "二级指针演示：" << endl;
    cout << "value = " << value << endl;
    cout << "*ptr = " << *ptr << endl;
    cout << "**pptr = " << **pptr << endl;
    
    // 通过二级指针修改值
    **pptr = 200;
    cout << "通过**pptr修改后，value = " << value << endl;
    
    // 修改指针指向
    int newValue = 300;
    *pptr = &newValue;  // 让ptr指向newValue
    cout << "*ptr现在指向newValue: " << *ptr << endl;
}
```

## 实践练习

### 练习1：指针基础操作
```cpp
void exercise1() {
    cout << "\n=== 练习1：指针基础操作 ===" << endl;
    
    // 创建变量和指针
    int a = 10, b = 20, c = 30;
    int* ptr1 = &a;
    int* ptr2 = &b;
    
    // 1. 输出变量值和地址
    cout << "a = " << a << ", 地址: " << &a << endl;
    cout << "b = " << b << ", 地址: " << &b << endl;
    cout << "c = " << c << ", 地址: " << &c << endl;
    
    // 2. 通过指针访问和修改值
    cout << "*ptr1 = " << *ptr1 << endl;
    *ptr1 = 100;
    cout << "修改后 a = " << a << endl;
    
    // 3. 指针重新赋值
    ptr1 = &c;
    cout << "ptr1现在指向c: " << *ptr1 << endl;
}
```

### 练习2：数组指针操作
```cpp
void exercise2() {
    cout << "\n=== 练习2：数组指针操作 ===" << endl;
    
    int numbers[] = {5, 15, 25, 35, 45};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // 1. 用指针计算数组元素之和
    int sum = 0;
    for (int* ptr = numbers; ptr < numbers + size; ptr++) {
        sum += *ptr;
    }
    cout << "数组元素之和: " << sum << endl;
    
    // 2. 反转数组
    int* start = numbers;
    int* end = numbers + size - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    
    cout << "反转后的数组: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
}
```

### 练习3：字符串指针操作
```cpp
int stringLength(const char* str) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

void stringCopy(char* dest, const char* src) {
    while ((*dest++ = *src++) != '\0') {
        // 空循环体，所有工作在条件中完成
    }
}

void exercise3() {
    cout << "\n=== 练习3：字符串指针操作 ===" << endl;
    
    const char* message = "Hello, Pointers!";
    cout << "字符串: " << message << endl;
    cout << "长度: " << stringLength(message) << endl;
    
    char buffer[50];
    stringCopy(buffer, message);
    cout << "复制的字符串: " << buffer << endl;
}
```

## 算法练习题

### LeetCode相关题目
1. **[两数之和](https://leetcode.cn/problems/two-sum/)** - 使用指针优化查找
2. **[删除排序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)** - 双指针技巧
3. **[移动零](https://leetcode.cn/problems/move-zeroes/)** - 指针操作数组

### 练习4：实现简单的动态数组
```cpp
class SimpleVector {
private:
    int* data;
    int size;
    int capacity;
    
public:
    SimpleVector(int cap = 10) : size(0), capacity(cap) {
        data = new int[capacity];
    }
    
    ~SimpleVector() {
        delete[] data;
    }
    
    void push_back(int value) {
        if (size >= capacity) {
            // 简单的扩容策略
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }
    
    int& operator[](int index) {
        return data[index];
    }
    
    int getSize() const { return size; }
    
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void exercise4() {
    cout << "\n=== 练习4：简单动态数组 ===" << endl;
    
    SimpleVector vec;
    for (int i = 1; i <= 15; i++) {
        vec.push_back(i * i);
    }
    
    cout << "动态数组内容: ";
    vec.print();
    cout << "大小: " << vec.getSize() << endl;
}
```

## 常见错误与注意事项

### 1. 野指针问题
```cpp
void dangerousPointer() {
    int* ptr;  // 未初始化的指针
    // *ptr = 10;  // 危险！可能导致程序崩溃
    
    // 正确做法
    ptr = nullptr;  // 或者立即初始化
    if (ptr != nullptr) {
        *ptr = 10;
    }
}
```

### 2. 指针越界
```cpp
void pointerBounds() {
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr = arr;
    
    // 危险的操作
    // *(ptr + 10) = 100;  // 越界访问
    
    // 安全的做法
    for (int i = 0; i < 5; i++) {
        *(ptr + i) = i + 1;
    }
}
```

## 学习检查点

- [ ] 理解指针的基本概念和内存模型
- [ ] 掌握指针的声明、初始化和解引用
- [ ] 熟练使用指针进行算术运算
- [ ] 理解指针与数组的关系
- [ ] 能够使用指针作为函数参数
- [ ] 掌握多级指针的概念和使用
- [ ] 了解常见的指针错误和避免方法

## 完整示例程序

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== C++ 指针基础学习 ===" << endl;
    
    // 运行所有练习
    pointerBasics();
    pointerArithmetic();
    pointerAndArray();
    pointerParameters();
    doublePointer();
    
    exercise1();
    exercise2();
    exercise3();
    exercise4();
    
    return 0;
}
```

[返回第一周](/plan/week1/) | [上一天：数组与字符串](/plan/week1/day3/) | [下一天：引用](/plan/week1/day5/)
