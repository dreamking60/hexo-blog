---
title: C++ 学习计划 - 第13天:模板基础
date: 2025-09-16 10:23:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day13
layout: page
menu_id: plan
permalink: /plan/week2/day13/
---

# 第13天：模板基础

## 学习目标
掌握函数模板和类模板的基本概念，理解模板的编译过程，学会设计通用的代码。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Templates](https://en.cppreference.com/w/cpp/language/templates) - C++官方模板文档
- [LearnCpp - Templates](https://www.learncpp.com/cpp-tutorial/function-templates/) - 模板详解教程
- [GeeksforGeeks - Templates](https://www.geeksforgeeks.org/templates-cpp/) - 模板基础知识

### 🎥 视频教程
- [The Cherno C++ Templates](https://www.youtube.com/watch?v=I-hZkUa9mIs) - 模板概念深入讲解
- [C++ Templates Explained](https://www.youtube.com/watch?v=VNJ4wiuxJM4) - 模板实例演示

### 📖 深入阅读
- [C++ Templates: The Complete Guide](https://www.amazon.com/C-Templates-Complete-Guide-2nd/dp/0321714121) - 模板专门书籍
- [C++ Primer 第5版 - 第16章](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 模板与泛型编程
- [Effective C++ - 条款41-48](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 模板编程

## 学习内容

### 1. 模板基础概念
- 泛型编程思想
- 模板的编译过程
- 模板实例化
- 模板的优势和劣势

### 2. 函数模板
- 函数模板的定义
- 模板参数推导
- 显式模板实例化
- 函数模板特化

### 3. 类模板
- 类模板的定义
- 类模板的实例化
- 类模板的成员函数
- 类模板特化

### 4. 模板参数
- 类型参数
- 非类型参数
- 模板模板参数
- 默认模板参数

### 5. 模板高级特性
- 模板别名
- 变参模板基础
- SFINAE原理
- 模板元编程入门

## 重点概念和代码示例

### 函数模板基础
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 基本函数模板
template<typename T>
T maximum(T a, T b) {
    cout << "调用模板函数 maximum<" << typeid(T).name() << ">" << endl;
    return (a > b) ? a : b;
}

// 多个模板参数
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {  // C++11 尾置返回类型
    cout << "调用模板函数 add<" << typeid(T).name() 
         << ", " << typeid(U).name() << ">" << endl;
    return a + b;
}

// 带默认参数的模板
template<typename T = int, typename U = double>
void displayTypes(T a, U b) {
    cout << "T = " << typeid(T).name() << ", value = " << a << endl;
    cout << "U = " << typeid(U).name() << ", value = " << b << endl;
}

// 非类型模板参数
template<typename T, int Size>
class FixedArray {
private:
    T data[Size];
    
public:
    FixedArray() {
        cout << "创建 FixedArray<" << typeid(T).name() 
             << ", " << Size << ">" << endl;
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= Size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= Size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    int size() const { return Size; }
    
    void fill(const T& value) {
        for (int i = 0; i < Size; i++) {
            data[i] = value;
        }
    }
    
    void display() const {
        cout << "[";
        for (int i = 0; i < Size; i++) {
            cout << data[i];
            if (i < Size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// 函数模板特化
template<>
const char* maximum<const char*>(const char* a, const char* b) {
    cout << "调用特化版本 maximum<const char*>" << endl;
    return (strcmp(a, b) > 0) ? a : b;
}

void functionTemplateDemo() {
    cout << "=== 函数模板演示 ===" << endl;
    
    // 隐式实例化
    cout << "maximum(10, 20) = " << maximum(10, 20) << endl;
    cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << endl;
    cout << "maximum('a', 'z') = " << maximum('a', 'z') << endl;
    
    // 显式实例化
    cout << "maximum<double>(5, 7.5) = " << maximum<double>(5, 7.5) << endl;
    
    // 多参数模板
    cout << "add(10, 3.14) = " << add(10, 3.14) << endl;
    cout << "add(string(\"Hello\"), string(\" World\")) = " 
         << add(string("Hello"), string(" World")) << endl;
    
    // 默认模板参数
    displayTypes(42, 3.14);
    displayTypes<string, int>("Hello", 100);
    
    // 特化版本
    const char* str1 = "apple";
    const char* str2 = "banana";
    cout << "maximum(\"apple\", \"banana\") = " << maximum(str1, str2) << endl;
    
    // 非类型参数模板
    FixedArray<int, 5> intArray;
    intArray.fill(42);
    cout << "intArray: ";
    intArray.display();
    
    FixedArray<string, 3> strArray;
    strArray[0] = "Hello";
    strArray[1] = "Template";
    strArray[2] = "World";
    cout << "strArray: ";
    strArray.display();
}
```

### 类模板详解
```cpp
// 通用栈类模板
template<typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    Stack() {
        cout << "创建 Stack<" << typeid(T).name() << ">" << endl;
    }
    
    ~Stack() {
        cout << "销毁 Stack<" << typeid(T).name() << ">" << endl;
    }
    
    void push(const T& element) {
        elements.push_back(element);
    }
    
    void pop() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        elements.pop_back();
    }
    
    T& top() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    const T& top() const {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "Stack内容 (从底到顶): ";
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

// 类模板特化 - 针对bool类型的特殊实现
template<>
class Stack<bool> {
private:
    vector<bool> elements;
    
public:
    Stack() {
        cout << "创建特化的 Stack<bool>" << endl;
    }
    
    ~Stack() {
        cout << "销毁特化的 Stack<bool>" << endl;
    }
    
    void push(bool element) {
        elements.push_back(element);
        cout << "推入布尔值: " << (element ? "true" : "false") << endl;
    }
    
    void pop() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        bool value = elements.back();
        elements.pop_back();
        cout << "弹出布尔值: " << (value ? "true" : "false") << endl;
    }
    
    bool top() const {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "Stack<bool>内容: ";
        for (bool elem : elements) {
            cout << (elem ? "true" : "false") << " ";
        }
        cout << endl;
    }
};

void classTemplateDemo() {
    cout << "\n=== 类模板演示 ===" << endl;
    
    // 整数栈
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    
    cout << "栈顶元素: " << intStack.top() << endl;
    cout << "栈大小: " << intStack.size() << endl;
    
    intStack.pop();
    intStack.display();
    
    // 字符串栈
    Stack<string> stringStack;
    stringStack.push("First");
    stringStack.push("Second");
    stringStack.push("Third");
    stringStack.display();
    
    // 特化版本的布尔栈
    Stack<bool> boolStack;
    boolStack.push(true);
    boolStack.push(false);
    boolStack.push(true);
    boolStack.display();
    
    cout << "布尔栈顶: " << (boolStack.top() ? "true" : "false") << endl;
    boolStack.pop();
}
```

## 实践练习

### 练习1：通用容器类模板
```cpp
template<typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t count;
    
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        
        // 复制现有元素
        for (size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    // 构造函数
    explicit DynamicArray(size_t initialCapacity = 10) 
        : capacity(initialCapacity), count(0) {
        data = new T[capacity];
        cout << "创建 DynamicArray<" << typeid(T).name() 
             << ">, 初始容量: " << capacity << endl;
    }
    
    // 拷贝构造函数
    DynamicArray(const DynamicArray& other) 
        : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (size_t i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
        cout << "拷贝构造 DynamicArray<" << typeid(T).name() << ">" << endl;
    }
    
    // 赋值运算符
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            count = other.count;
            data = new T[capacity];
            
            for (size_t i = 0; i < count; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 析构函数
    ~DynamicArray() {
        delete[] data;
        cout << "销毁 DynamicArray<" << typeid(T).name() << ">" << endl;
    }
    
    // 添加元素
    void push_back(const T& element) {
        if (count >= capacity) {
            resize(capacity * 2);
        }
        data[count++] = element;
    }
    
    // 插入元素
    void insert(size_t index, const T& element) {
        if (index > count) {
            throw out_of_range("Index out of range");
        }
        
        if (count >= capacity) {
            resize(capacity * 2);
        }
        
        // 向后移动元素
        for (size_t i = count; i > index; i--) {
            data[i] = data[i - 1];
        }
        
        data[index] = element;
        count++;
    }
    
    // 删除元素
    void erase(size_t index) {
        if (index >= count) {
            throw out_of_range("Index out of range");
        }
        
        // 向前移动元素
        for (size_t i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
    }
    
    // 访问元素
    T& operator[](size_t index) {
        if (index >= count) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= count) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 查找元素
    int find(const T& element) const {
        for (size_t i = 0; i < count; i++) {
            if (data[i] == element) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
    
    // 获取信息
    size_t size() const { return count; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return count == 0; }
    
    // 清空
    void clear() {
        count = 0;
    }
    
    // 显示内容
    void display() const {
        cout << "DynamicArray<" << typeid(T).name() << "> [";
        for (size_t i = 0; i < count; i++) {
            cout << data[i];
            if (i < count - 1) cout << ", ";
        }
        cout << "] (size: " << count << ", capacity: " << capacity << ")" << endl;
    }
    
    // 迭代器支持（简化版本）
    T* begin() { return data; }
    T* end() { return data + count; }
    const T* begin() const { return data; }
    const T* end() const { return data + count; }
};

void exercise1() {
    cout << "\n=== 练习1：通用容器类模板 ===" << endl;
    
    // 整数数组
    DynamicArray<int> intArray;
    for (int i = 1; i <= 8; i++) {
        intArray.push_back(i * 10);
    }
    intArray.display();
    
    // 插入和删除
    intArray.insert(2, 999);
    intArray.display();
    
    intArray.erase(0);
    intArray.display();
    
    // 查找元素
    int index = intArray.find(40);
    cout << "元素40的索引: " << index << endl;
    
    // 字符串数组
    DynamicArray<string> strArray(5);
    strArray.push_back("Hello");
    strArray.push_back("Template");
    strArray.push_back("World");
    strArray.display();
    
    // 使用迭代器
    cout << "使用迭代器遍历字符串数组: ";
    for (const auto& str : strArray) {
        cout << str << " ";
    }
    cout << endl;
    
    // 拷贝构造
    DynamicArray<int> intArray2 = intArray;
    intArray2.display();
    
    // 修改原数组
    intArray[0] = 888;
    cout << "修改原数组后:" << endl;
    intArray.display();
    intArray2.display();
}
```

### 练习2：模板化的数据结构
```cpp
// 模板化的链表节点
template<typename T>
struct ListNode {
    T data;
    ListNode* next;
    
    ListNode(const T& value) : data(value), next(nullptr) {}
};

// 模板化的单链表
template<typename T>
class LinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    size_t count;
    
public:
    // 构造函数
    LinkedList() : head(nullptr), tail(nullptr), count(0) {
        cout << "创建 LinkedList<" << typeid(T).name() << ">" << endl;
    }
    
    // 拷贝构造函数
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        cout << "拷贝构造 LinkedList<" << typeid(T).name() << ">" << endl;
        ListNode<T>* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    // 赋值运算符
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            ListNode<T>* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    // 析构函数
    ~LinkedList() {
        clear();
        cout << "销毁 LinkedList<" << typeid(T).name() << ">" << endl;
    }
    
    // 在头部添加
    void push_front(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }
    
    // 在尾部添加
    void push_back(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }
    
    // 删除头部
    void pop_front() {
        if (head == nullptr) return;
        
        ListNode<T>* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        count--;
    }
    
    // 插入到指定位置
    void insert(size_t index, const T& value) {
        if (index == 0) {
            push_front(value);
            return;
        }
        
        if (index >= count) {
            push_back(value);
            return;
        }
        
        ListNode<T>* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = current->next;
        current->next = newNode;
        count++;
    }
    
    // 删除指定位置的元素
    void erase(size_t index) {
        if (index >= count) return;
        
        if (index == 0) {
            pop_front();
            return;
        }
        
        ListNode<T>* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        
        ListNode<T>* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        
        if (nodeToDelete == tail) {
            tail = current;
        }
        
        delete nodeToDelete;
        count--;
    }
    
    // 查找元素
    int find(const T& value) const {
        ListNode<T>* current = head;
        int index = 0;
        
        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }
    
    // 访问元素
    T& operator[](size_t index) {
        if (index >= count) {
            throw out_of_range("Index out of range");
        }
        
        ListNode<T>* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // 获取信息
    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    
    // 清空链表
    void clear() {
        while (head) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    
    // 显示链表
    void display() const {
        cout << "LinkedList<" << typeid(T).name() << ">: ";
        ListNode<T>* current = head;
        while (current) {
            cout << current->data;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << " (size: " << count << ")" << endl;
    }
    
    // 反转链表
    void reverse() {
        if (count <= 1) return;
        
        ListNode<T>* prev = nullptr;
        ListNode<T>* current = head;
        tail = head;  // 原来的头变成尾
        
        while (current) {
            ListNode<T>* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;  // 原来的尾变成头
    }
};

void exercise2() {
    cout << "\n=== 练习2：模板化的数据结构 ===" << endl;
    
    // 整数链表
    LinkedList<int> intList;
    for (int i = 1; i <= 5; i++) {
        intList.push_back(i * 10);
    }
    intList.display();
    
    // 头部插入
    intList.push_front(5);
    intList.display();
    
    // 指定位置插入
    intList.insert(3, 999);
    intList.display();
    
    // 删除元素
    intList.erase(0);
    intList.display();
    
    // 查找元素
    int index = intList.find(30);
    cout << "元素30的索引: " << index << endl;
    
    // 访问元素
    cout << "索引2的元素: " << intList[2] << endl;
    
    // 反转链表
    intList.reverse();
    cout << "反转后: ";
    intList.display();
    
    // 字符串链表
    LinkedList<string> strList;
    strList.push_back("First");
    strList.push_back("Second");
    strList.push_back("Third");
    strList.display();
    
    // 拷贝构造
    LinkedList<string> strList2 = strList;
    strList2.display();
    
    // 修改原链表
    strList.push_front("Zero");
    cout << "修改原链表后:" << endl;
    strList.display();
    strList2.display();
}
```

### 练习3：模板化的算法函数
```cpp
// 通用排序算法模板
template<typename Iterator, typename Compare>
void bubbleSort(Iterator begin, Iterator end, Compare comp) {
    for (Iterator i = begin; i != end; ++i) {
        for (Iterator j = begin; j != end - 1; ++j) {
            Iterator next = j;
            ++next;
            if (comp(*next, *j)) {
                swap(*j, *next);
            }
        }
    }
}

// 通用查找算法模板
template<typename Iterator, typename T>
Iterator linearSearch(Iterator begin, Iterator end, const T& value) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end;
}

// 通用二分查找模板（要求已排序）
template<typename Iterator, typename T>
Iterator binarySearch(Iterator begin, Iterator end, const T& value) {
    Iterator left = begin;
    Iterator right = end;
    
    while (left < right) {
        Iterator mid = left + (right - left) / 2;
        
        if (*mid == value) {
            return mid;
        } else if (*mid < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return end;
}

// 通用变换算法模板
template<typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, 
                        OutputIterator result, UnaryOperation op) {
    while (first != last) {
        *result = op(*first);
        ++first;
        ++result;
    }
    return result;
}

// 通用累积算法模板
template<typename Iterator, typename T, typename BinaryOperation>
T accumulate(Iterator first, Iterator last, T init, BinaryOperation op) {
    while (first != last) {
        init = op(init, *first);
        ++first;
    }
    return init;
}

// 通用过滤算法模板
template<typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator filter(InputIterator first, InputIterator last,
                     OutputIterator result, Predicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

void exercise3() {
    cout << "\n=== 练习3：模板化的算法函数 ===" << endl;
    
    // 测试数据
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90, 5};
    vector<string> words = {"banana", "apple", "orange", "grape", "cherry"};
    
    cout << "原始整数数组: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    
    // 冒泡排序
    bubbleSort(numbers.begin(), numbers.end(), [](int a, int b) { return a < b; });
    cout << "排序后: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    
    // 线性查找
    auto it = linearSearch(numbers.begin(), numbers.end(), 25);
    if (it != numbers.end()) {
        cout << "找到元素25，位置: " << (it - numbers.begin()) << endl;
    }
    
    // 二分查找
    it = binarySearch(numbers.begin(), numbers.end(), 34);
    if (it != numbers.end()) {
        cout << "二分查找找到元素34，位置: " << (it - numbers.begin()) << endl;
    }
    
    // 变换算法 - 计算平方
    vector<int> squares(numbers.size());
    transform(numbers.begin(), numbers.end(), squares.begin(), 
              [](int x) { return x * x; });
    cout << "平方数组: ";
    for (int sq : squares) cout << sq << " ";
    cout << endl;
    
    // 累积算法 - 计算和
    int sum = accumulate(numbers.begin(), numbers.end(), 0, 
                        [](int a, int b) { return a + b; });
    cout << "数组和: " << sum << endl;
    
    // 累积算法 - 计算乘积
    int product = accumulate(numbers.begin(), numbers.end(), 1,
                           [](int a, int b) { return a * b; });
    cout << "数组乘积: " << product << endl;
    
    // 过滤算法 - 筛选偶数
    vector<int> evens;
    evens.resize(numbers.size());
    auto end_it = filter(numbers.begin(), numbers.end(), evens.begin(),
                        [](int x) { return x % 2 == 0; });
    evens.resize(end_it - evens.begin());
    
    cout << "偶数: ";
    for (int even : evens) cout << even << " ";
    cout << endl;
    
    // 字符串排序
    cout << "\n原始字符串数组: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    bubbleSort(words.begin(), words.end(), 
               [](const string& a, const string& b) { return a < b; });
    cout << "排序后: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // 字符串变换 - 转换为大写
    vector<string> upperWords(words.size());
    transform(words.begin(), words.end(), upperWords.begin(),
              [](string s) {
                  for (char& c : s) c = toupper(c);
                  return s;
              });
    cout << "大写字符串: ";
    for (const string& word : upperWords) cout << word << " ";
    cout << endl;
}
```

## 学习检查点

- [ ] 理解模板的基本概念和编译过程
- [ ] 掌握函数模板的定义和使用
- [ ] 掌握类模板的定义和实例化
- [ ] 理解模板参数的不同类型
- [ ] 了解模板特化的概念和用法
- [ ] 能够设计通用的算法和数据结构
- [ ] 理解模板的优势和局限性
- [ ] 掌握模板编程的最佳实践

## 完整示例程序

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <cstring>
using namespace std;

int main() {
    cout << "=== C++ 模板基础学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        functionTemplateDemo();
        classTemplateDemo();
        
        exercise1();
        exercise2();
        exercise3();
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
    
    cout << "\n程序结束" << endl;
    return 0;
}
```

[返回第二周](/plan/week2/) | [上一天：运算符重载](/plan/week2/day12/) | [下一天：异常处理](/plan/week2/day14/)
