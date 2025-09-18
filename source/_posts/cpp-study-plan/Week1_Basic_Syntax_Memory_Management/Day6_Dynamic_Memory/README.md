---
title: C++ 学习计划 - 第6天:动态内存分配
date: 2025-09-16 10:16:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week1
    - Day6
layout: page
menu_id: plan
permalink: /plan/week1/day6/
---

# 第6天：动态内存分配

## 学习目标
掌握动态内存的分配与释放，理解内存管理的重要性，学会避免内存泄漏和野指针问题。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Dynamic Memory](https://en.cppreference.com/w/cpp/memory) - C++官方内存管理文档
- [LearnCpp - Dynamic Memory](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/) - 动态内存教程
- [GeeksforGeeks - Dynamic Memory](https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/) - new和delete操作符

### 🎥 视频教程
- [The Cherno C++ Memory Management](https://www.youtube.com/watch?v=DTxHyVn0ODg) - 内存管理概念
- [C++ Dynamic Memory Allocation](https://www.youtube.com/watch?v=CSVRA4_xOkw) - 动态内存分配实例

### 📖 深入阅读
- [C++ Primer 第5版 - 第12章](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 动态内存管理
- [Effective C++ - 条款16-18](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 资源管理
- [More Effective C++ - 条款6-8](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X) - 内存管理技巧

## 学习内容

### 1. 动态内存基础
- 栈内存 vs 堆内存
- new和delete操作符
- new[]和delete[]操作符
- 内存分配失败处理

### 2. 内存管理问题
- 内存泄漏
- 野指针和悬空指针
- 重复释放内存
- 内存碎片

### 3. 动态数组
- 动态数组的创建和销毁
- 多维动态数组
- 动态数组的扩容
- 与静态数组的对比

### 4. 内存对齐
- 内存对齐的概念
- 对齐要求和性能
- 结构体内存布局
- 自定义对齐

### 5. 内存调试
- 常用内存调试工具
- 内存泄漏检测
- 内存访问错误
- 最佳实践

## 重点概念和代码示例

### 基本的new和delete
```cpp
#include <iostream>
#include <new>
using namespace std;

void basicNewDelete() {
    cout << "=== 基本new和delete操作 ===" << endl;
    
    // 分配单个对象
    int* ptr = new int(42);  // 分配并初始化
    cout << "分配的值: " << *ptr << endl;
    cout << "内存地址: " << ptr << endl;
    
    // 修改值
    *ptr = 100;
    cout << "修改后的值: " << *ptr << endl;
    
    // 释放内存
    delete ptr;
    ptr = nullptr;  // 避免悬空指针
    
    // 分配未初始化的对象
    double* dptr = new double;  // 未初始化
    cout << "未初始化的double值: " << *dptr << endl;  // 可能是随机值
    
    *dptr = 3.14159;
    cout << "赋值后: " << *dptr << endl;
    delete dptr;
    dptr = nullptr;
    
    // 分配零初始化的对象
    int* zeroPtr = new int();  // 零初始化
    cout << "零初始化的int值: " << *zeroPtr << endl;  // 输出: 0
    delete zeroPtr;
}
```

### 动态数组操作
```cpp
void dynamicArrays() {
    cout << "\n=== 动态数组操作 ===" << endl;
    
    // 分配动态数组
    int size = 5;
    int* arr = new int[size];
    
    // 初始化数组
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }
    
    // 输出数组
    cout << "动态数组内容: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 释放数组内存
    delete[] arr;  // 注意使用delete[]
    arr = nullptr;
    
    // 分配并初始化数组（C++11）
    int* arr2 = new int[3]{10, 20, 30};
    cout << "初始化的数组: ";
    for (int i = 0; i < 3; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    delete[] arr2;
    
    // 零初始化数组
    int* zeroArr = new int[4]();  // 所有元素初始化为0
    cout << "零初始化数组: ";
    for (int i = 0; i < 4; i++) {
        cout << zeroArr[i] << " ";
    }
    cout << endl;
    delete[] zeroArr;
}
```

### 内存分配异常处理
```cpp
void memoryExceptionHandling() {
    cout << "\n=== 内存分配异常处理 ===" << endl;
    
    try {
        // 尝试分配大量内存
        size_t hugeSize = SIZE_MAX / 2;  // 可能导致分配失败
        int* hugeArray = new int[hugeSize];
        
        cout << "成功分配大量内存" << endl;
        delete[] hugeArray;
        
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
    }
    
    // 使用nothrow版本
    int* ptr = new(nothrow) int[1000000];
    if (ptr == nullptr) {
        cout << "nothrow版本分配失败" << endl;
    } else {
        cout << "nothrow版本分配成功" << endl;
        delete[] ptr;
    }
    
    // 设置new_handler
    set_new_handler([]() {
        cout << "内存不足，尝试清理..." << endl;
        throw bad_alloc();
    });
}
```

### 动态二维数组
```cpp
void dynamic2DArray() {
    cout << "\n=== 动态二维数组 ===" << endl;
    
    int rows = 3, cols = 4;
    
    // 方法1：指针数组
    int** matrix1 = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix1[i] = new int[cols];
    }
    
    // 初始化矩阵
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = i * cols + j + 1;
        }
    }
    
    // 输出矩阵
    cout << "二维数组内容:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix1[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 释放内存
    for (int i = 0; i < rows; i++) {
        delete[] matrix1[i];
    }
    delete[] matrix1;
    
    // 方法2：连续内存分配
    int* matrix2 = new int[rows * cols];
    
    // 使用宏或函数访问元素
    auto getElement = [&](int r, int c) -> int& {
        return matrix2[r * cols + c];
    };
    
    // 初始化
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            getElement(i, j) = (i + 1) * (j + 1);
        }
    }
    
    cout << "\n连续内存二维数组:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << getElement(i, j) << "\t";
        }
        cout << endl;
    }
    
    delete[] matrix2;
}
```

## 实践练习

### 练习1：动态字符串处理
```cpp
class DynamicString {
private:
    char* data;
    size_t length;
    size_t capacity;
    
public:
    // 构造函数
    DynamicString(const char* str = "") {
        length = strlen(str);
        capacity = length + 1;
        data = new char[capacity];
        strcpy(data, str);
    }
    
    // 拷贝构造函数
    DynamicString(const DynamicString& other) {
        length = other.length;
        capacity = other.capacity;
        data = new char[capacity];
        strcpy(data, other.data);
    }
    
    // 赋值操作符
    DynamicString& operator=(const DynamicString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            capacity = other.capacity;
            data = new char[capacity];
            strcpy(data, other.data);
        }
        return *this;
    }
    
    // 析构函数
    ~DynamicString() {
        delete[] data;
    }
    
    // 获取长度
    size_t getLength() const { return length; }
    
    // 获取C字符串
    const char* c_str() const { return data; }
    
    // 追加字符串
    void append(const char* str) {
        size_t newLength = length + strlen(str);
        if (newLength + 1 > capacity) {
            // 扩容
            capacity = (newLength + 1) * 2;
            char* newData = new char[capacity];
            strcpy(newData, data);
            delete[] data;
            data = newData;
        }
        strcat(data, str);
        length = newLength;
    }
    
    // 输出操作符
    friend ostream& operator<<(ostream& os, const DynamicString& str) {
        os << str.data;
        return os;
    }
};

void exercise1() {
    cout << "\n=== 练习1：动态字符串处理 ===" << endl;
    
    DynamicString str1("Hello");
    cout << "str1: " << str1 << " (长度: " << str1.getLength() << ")" << endl;
    
    DynamicString str2 = str1;  // 拷贝构造
    cout << "str2 (拷贝): " << str2 << endl;
    
    str1.append(" World!");
    cout << "str1 追加后: " << str1 << " (长度: " << str1.getLength() << ")" << endl;
    cout << "str2 未变: " << str2 << endl;
    
    str2 = str1;  // 赋值操作
    cout << "str2 赋值后: " << str2 << endl;
}
```

### 练习2：动态栈实现
```cpp
template<typename T>
class DynamicStack {
private:
    T* data;
    int top;
    int capacity;
    
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i <= top; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    
public:
    DynamicStack(int initialCapacity = 10) 
        : capacity(initialCapacity), top(-1) {
        data = new T[capacity];
    }
    
    ~DynamicStack() {
        delete[] data;
    }
    
    void push(const T& value) {
        if (top + 1 >= capacity) {
            resize();
        }
        data[++top] = value;
    }
    
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return data[top--];
    }
    
    T peek() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return data[top];
    }
    
    bool isEmpty() const {
        return top == -1;
    }
    
    int size() const {
        return top + 1;
    }
    
    int getCapacity() const {
        return capacity;
    }
};

void exercise2() {
    cout << "\n=== 练习2：动态栈实现 ===" << endl;
    
    DynamicStack<int> stack;
    
    // 推入元素
    for (int i = 1; i <= 15; i++) {
        stack.push(i);
        cout << "推入 " << i << ", 栈大小: " << stack.size() 
             << ", 容量: " << stack.getCapacity() << endl;
    }
    
    // 弹出元素
    cout << "\n弹出元素: ";
    while (!stack.isEmpty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;
}
```

### 练习3：内存池简单实现
```cpp
class SimpleMemoryPool {
private:
    struct Block {
        Block* next;
    };
    
    char* pool;
    Block* freeList;
    size_t blockSize;
    size_t poolSize;
    
public:
    SimpleMemoryPool(size_t blockSize, size_t blockCount) 
        : blockSize(max(blockSize, sizeof(Block))) {
        poolSize = this->blockSize * blockCount;
        pool = new char[poolSize];
        
        // 初始化自由链表
        freeList = reinterpret_cast<Block*>(pool);
        Block* current = freeList;
        
        for (size_t i = 1; i < blockCount; i++) {
            current->next = reinterpret_cast<Block*>(
                pool + i * this->blockSize);
            current = current->next;
        }
        current->next = nullptr;
    }
    
    ~SimpleMemoryPool() {
        delete[] pool;
    }
    
    void* allocate() {
        if (freeList == nullptr) {
            return nullptr;  // 内存池已满
        }
        
        Block* block = freeList;
        freeList = freeList->next;
        return block;
    }
    
    void deallocate(void* ptr) {
        if (ptr == nullptr) return;
        
        Block* block = static_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }
    
    bool isFromPool(void* ptr) const {
        char* charPtr = static_cast<char*>(ptr);
        return charPtr >= pool && charPtr < pool + poolSize;
    }
};

void exercise3() {
    cout << "\n=== 练习3：内存池实现 ===" << endl;
    
    SimpleMemoryPool pool(sizeof(int), 10);
    
    // 分配内存
    vector<void*> allocatedBlocks;
    for (int i = 0; i < 10; i++) {
        void* ptr = pool.allocate();
        if (ptr) {
            *static_cast<int*>(ptr) = i + 1;
            allocatedBlocks.push_back(ptr);
            cout << "分配块 " << i + 1 << ", 地址: " << ptr << endl;
        } else {
            cout << "分配失败" << endl;
            break;
        }
    }
    
    // 使用分配的内存
    cout << "分配的值: ";
    for (void* ptr : allocatedBlocks) {
        cout << *static_cast<int*>(ptr) << " ";
    }
    cout << endl;
    
    // 释放部分内存
    for (size_t i = 0; i < allocatedBlocks.size() / 2; i++) {
        pool.deallocate(allocatedBlocks[i]);
    }
    
    // 重新分配
    void* newPtr = pool.allocate();
    if (newPtr) {
        *static_cast<int*>(newPtr) = 999;
        cout << "重新分配的值: " << *static_cast<int*>(newPtr) << endl;
        pool.deallocate(newPtr);
    }
    
    // 清理剩余内存
    for (size_t i = allocatedBlocks.size() / 2; i < allocatedBlocks.size(); i++) {
        pool.deallocate(allocatedBlocks[i]);
    }
}
```

## 算法练习题

### LeetCode相关题目
1. **[合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/)** - 动态创建链表节点
2. **[删除链表的倒数第N个节点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)** - 链表内存管理
3. **[复制带随机指针的链表](https://leetcode.cn/problems/copy-list-with-random-pointer/)** - 复杂内存分配

### 练习4：动态链表实现
```cpp
template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t size;
    
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~LinkedList() {
        clear();
    }
    
    // 拷贝构造函数
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    // 赋值操作符
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    void pop_front() {
        if (head == nullptr) return;
        
        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        size--;
    }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    
    bool empty() const { return size == 0; }
    size_t getSize() const { return size; }
    
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};

void exercise4() {
    cout << "\n=== 练习4：动态链表实现 ===" << endl;
    
    LinkedList<int> list;
    
    // 添加元素
    for (int i = 1; i <= 5; i++) {
        list.push_back(i);
    }
    
    cout << "链表内容: ";
    list.print();
    cout << "大小: " << list.getSize() << endl;
    
    // 头部添加
    list.push_front(0);
    cout << "头部添加0后: ";
    list.print();
    
    // 删除头部
    list.pop_front();
    cout << "删除头部后: ";
    list.print();
    
    // 拷贝链表
    LinkedList<int> list2 = list;
    cout << "拷贝的链表: ";
    list2.print();
    
    // 清空原链表
    list.clear();
    cout << "原链表清空后大小: " << list.getSize() << endl;
    cout << "拷贝链表仍存在: ";
    list2.print();
}
```

## 常见错误与注意事项

### 1. 内存泄漏
```cpp
void memoryLeakExample() {
    // 错误：忘记释放内存
    void badFunction() {
        int* ptr = new int(42);
        if (someCondition) {
            return;  // 内存泄漏！
        }
        delete ptr;
    }
    
    // 正确：使用RAII或确保所有路径都释放内存
    void goodFunction() {
        int* ptr = new int(42);
        // ... 使用ptr ...
        delete ptr;  // 确保释放
    }
}
```

### 2. 悬空指针
```cpp
void danglingPointerExample() {
    int* ptr = new int(42);
    delete ptr;
    // ptr = nullptr;  // 应该设置为nullptr
    
    // *ptr = 100;  // 错误：使用悬空指针
    
    // 正确做法
    ptr = nullptr;
    if (ptr != nullptr) {
        *ptr = 100;
    }
}
```

### 3. 重复释放
```cpp
void doubleFreeExample() {
    int* ptr = new int(42);
    delete ptr;
    // delete ptr;  // 错误：重复释放
    
    // 正确做法
    ptr = nullptr;  // 防止重复释放
}
```

## 学习检查点

- [ ] 理解栈内存和堆内存的区别
- [ ] 掌握new/delete和new[]/delete[]的使用
- [ ] 了解内存分配失败的处理方法
- [ ] 能够识别和避免内存泄漏
- [ ] 理解野指针和悬空指针的危害
- [ ] 掌握动态数组的创建和管理
- [ ] 了解内存对齐的基本概念
- [ ] 能够实现简单的动态数据结构

## 完整示例程序

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
#include <new>
#include <cstring>
using namespace std;

int main() {
    cout << "=== C++ 动态内存分配学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        basicNewDelete();
        dynamicArrays();
        memoryExceptionHandling();
        dynamic2DArray();
        
        exercise1();
        exercise2();
        exercise3();
        exercise4();
        
    } catch (const exception& e) {
        cout << "异常: " << e.what() << endl;
    }
    
    return 0;
}
```

[返回第一周](/plan/week1/) | [上一天：引用](/plan/week1/day5/) | [下一天：const关键字](/plan/week1/day7/)
