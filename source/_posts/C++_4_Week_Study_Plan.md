---
title: C++ 4周复习计划
date: 2025-09-16 10:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Review
---

# C++ 4周复习计划

## 计划概述
本计划旨在系统性地复习C++核心知识点，每天专注一个主题，通过理论学习和实践练习相结合的方式，巩固和提升C++编程能力。

## 第一周：基础语法与内存管理

### 第1天：变量、数据类型与基本语法
**学习目标：** 复习C++基础语法和数据类型
**学习内容：**
- 基本数据类型：int, float, double, char, bool
- 变量声明与初始化
- 常量与字面量
- 运算符优先级
- 控制结构（if-else, switch, for, while）

**实践练习：**
```cpp
// 编写一个程序，计算不同数据类型的范围
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "int范围: " << INT_MIN << " 到 " << INT_MAX << endl;
    cout << "float范围: " << FLT_MIN << " 到 " << FLT_MAX << endl;
    // 更多练习...
    return 0;
}
```

### 第2天：函数与作用域
**学习目标：** 掌握函数定义、调用和作用域规则
**学习内容：**
- 函数声明与定义
- 参数传递（值传递、引用传递、指针传递）
- 函数重载
- 默认参数
- 作用域与生存期
- 递归函数

**实践练习：**
```cpp
// 实现一个递归的斐波那契数列函数
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```

### 第3天：数组与字符串
**学习目标：** 掌握数组和字符串的使用
**学习内容：**
- 一维数组和多维数组
- 数组的初始化与访问
- 字符数组与字符串
- C风格字符串函数
- 数组作为函数参数

**实践练习：**
```cpp
// 实现一个字符串反转函数
void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        swap(str[i], str[len - 1 - i]);
    }
}
```

### 第4天：指针基础
**学习目标：** 深入理解指针的概念和使用
**学习内容：**
- 指针的声明与初始化
- 指针运算
- 指针与数组的关系
- 指针作为函数参数
- 指针的指针

**实践练习：**
```cpp
// 实现一个函数，使用指针交换两个变量的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

### 第5天：引用
**学习目标：** 掌握引用的概念和使用场景
**学习内容：**
- 引用的定义与初始化
- 引用与指针的区别
- 引用作为函数参数
- 引用作为返回值
- 常量引用

**实践练习：**
```cpp
// 使用引用实现一个函数，返回两个数中的较大值
int& max(int& a, int& b) {
    return (a > b) ? a : b;
}
```

### 第6天：动态内存分配
**学习目标：** 掌握动态内存的分配与释放
**学习内容：**
- new和delete操作符
- new[]和delete[]操作符
- 内存泄漏的预防
- 野指针问题
- 内存对齐

**实践练习：**
```cpp
// 实现一个动态数组类
class DynamicArray {
private:
    int* data;
    size_t size;
public:
    DynamicArray(size_t s) : size(s) {
        data = new int[size];
    }
    ~DynamicArray() {
        delete[] data;
    }
    // 更多方法...
};
```

### 第7天：const关键字
**学习目标：** 深入理解const的各种用法
**学习内容：**
- 常量变量
- 常量指针与指向常量的指针
- 常量引用
- 常量成员函数
- const_cast的使用

**实践练习：**
```cpp
// 实现一个常量安全的类
class SafeClass {
private:
    int value;
public:
    SafeClass(int v) : value(v) {}
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
};
```

## 第二周：面向对象编程

### 第8天：类与对象基础
**学习目标：** 掌握类的基本概念和对象的创建
**学习内容：**
- 类的定义与声明
- 对象的创建与销毁
- 成员变量与成员函数
- 访问控制（public, private, protected）
- this指针

**实践练习：**
```cpp
// 实现一个简单的银行账户类
class BankAccount {
private:
    double balance;
    string accountNumber;
public:
    BankAccount(string accNum, double initialBalance = 0.0);
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
};
```

### 第9天：构造函数与析构函数
**学习目标：** 掌握对象的构造和析构过程
**学习内容：**
- 构造函数的定义与调用
- 析构函数的作用
- 拷贝构造函数
- 移动构造函数
- 初始化列表

**实践练习：**
```cpp
// 实现一个资源管理类
class ResourceManager {
private:
    int* resource;
public:
    ResourceManager(int size);
    ResourceManager(const ResourceManager& other); // 拷贝构造
    ResourceManager(ResourceManager&& other);      // 移动构造
    ~ResourceManager();
    ResourceManager& operator=(const ResourceManager& other);
    ResourceManager& operator=(ResourceManager&& other);
};
```

### 第10天：继承
**学习目标：** 掌握面向对象的继承机制
**学习内容：**
- 基类与派生类
- 继承方式（public, private, protected）
- 派生类的构造与析构
- 函数重写
- 多重继承

**实践练习：**
```cpp
// 实现一个图形类的继承体系
class Shape {
protected:
    double x, y;
public:
    Shape(double x, double y) : x(x), y(y) {}
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double x, double y, double r) : Shape(x, y), radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
};
```

### 第11天：虚函数与多态
**学习目标：** 深入理解多态机制
**学习内容：**
- 虚函数的概念
- 虚函数表（vtable）
- 纯虚函数与抽象类
- 虚析构函数
- 动态绑定

**实践练习：**
```cpp
// 实现一个多态的动物类体系
class Animal {
public:
    virtual void makeSound() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void makeSound() const override { cout << "Woof!" << endl; }
};

class Cat : public Animal {
public:
    void makeSound() const override { cout << "Meow!" << endl; }
};
```

### 第12天：运算符重载
**学习目标：** 掌握运算符重载的方法
**学习内容：**
- 可重载的运算符
- 运算符重载的规则
- 友元函数与成员函数
- 特殊运算符重载（++, --, [], (), ->）
- 类型转换运算符

**实践练习：**
```cpp
// 实现一个复数类，重载基本运算符
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    friend ostream& operator<<(ostream& os, const Complex& c);
};
```

### 第13天：模板基础
**学习目标：** 掌握函数模板和类模板
**学习内容：**
- 函数模板的定义与使用
- 类模板的定义与使用
- 模板参数
- 模板特化
- 模板实例化

**实践练习：**
```cpp
// 实现一个通用的栈类模板
template<typename T>
class Stack {
private:
    vector<T> elements;
public:
    void push(const T& element);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;
};
```

### 第14天：异常处理
**学习目标：** 掌握C++异常处理机制
**学习内容：**
- try-catch-throw机制
- 异常类型
- 异常规范
- RAII与异常安全
- 标准异常类

**实践练习：**
```cpp
// 实现一个异常安全的资源管理
class SafeResource {
private:
    int* resource;
public:
    SafeResource(size_t size) {
        resource = new int[size];
        if (!resource) throw std::bad_alloc();
    }
    ~SafeResource() { delete[] resource; }
    // 禁止拷贝，只允许移动
    SafeResource(const SafeResource&) = delete;
    SafeResource& operator=(const SafeResource&) = delete;
    SafeResource(SafeResource&& other) noexcept;
};
```

## 第三周：STL与高级特性

### 第15天：STL容器
**学习目标：** 掌握STL容器的使用
**学习内容：**
- vector, list, deque
- set, multiset, map, multimap
- stack, queue, priority_queue
- 容器的选择原则
- 迭代器

**实践练习：**
```cpp
// 使用STL容器实现一个简单的学生管理系统
class StudentManager {
private:
    map<int, string> students; // 学号->姓名
    vector<pair<int, double>> grades; // 学号->成绩
public:
    void addStudent(int id, const string& name);
    void addGrade(int id, double grade);
    double getAverageGrade(int id) const;
    void printAllStudents() const;
};
```

### 第16天：STL算法
**学习目标：** 掌握STL算法的使用
**学习内容：**
- 查找算法（find, find_if, binary_search）
- 排序算法（sort, stable_sort, partial_sort）
- 修改算法（transform, replace, remove）
- 数值算法（accumulate, inner_product）
- 自定义比较器

**实践练习：**
```cpp
// 使用STL算法处理数据
void processData() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 找出所有偶数
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(), 
            back_inserter(evens), 
            [](int n) { return n % 2 == 0; });
    
    // 计算平方和
    int sum = accumulate(numbers.begin(), numbers.end(), 0,
                        [](int acc, int n) { return acc + n * n; });
}
```

### 第17天：智能指针
**学习目标：** 掌握现代C++的内存管理
**学习内容：**
- unique_ptr的使用
- shared_ptr的使用
- weak_ptr的使用
- make_unique和make_shared
- 循环引用问题

**实践练习：**
```cpp
// 实现一个使用智能指针的树结构
struct TreeNode {
    int value;
    unique_ptr<TreeNode> left;
    unique_ptr<TreeNode> right;
    
    TreeNode(int v) : value(v) {}
};

class BinaryTree {
private:
    unique_ptr<TreeNode> root;
public:
    void insert(int value);
    bool search(int value) const;
    void printInOrder() const;
};
```

### 第18天：Lambda表达式
**学习目标：** 掌握现代C++的Lambda表达式
**学习内容：**
- Lambda表达式的语法
- 捕获列表
- 参数列表与返回类型
- 泛型Lambda
- Lambda与STL的结合使用

**实践练习：**
```cpp
// 使用Lambda表达式实现各种功能
void lambdaExamples() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 使用Lambda过滤偶数
    auto evens = numbers | 
        views::filter([](int n) { return n % 2 == 0; });
    
    // 使用Lambda进行转换
    vector<int> squares;
    transform(numbers.begin(), numbers.end(), 
              back_inserter(squares),
              [](int n) { return n * n; });
}
```

### 第19天：移动语义
**学习目标：** 掌握C++11的移动语义
**学习内容：**
- 左值与右值
- 移动构造函数与移动赋值运算符
- std::move的使用
- 完美转发
- 移动语义的性能优势

**实践练习：**
```cpp
// 实现一个支持移动语义的字符串类
class MyString {
private:
    char* data;
    size_t size;
public:
    MyString(const char* str = "");
    MyString(const MyString& other);        // 拷贝构造
    MyString(MyString&& other) noexcept;    // 移动构造
    MyString& operator=(const MyString& other);  // 拷贝赋值
    MyString& operator=(MyString&& other) noexcept; // 移动赋值
    ~MyString();
    
    const char* c_str() const { return data; }
    size_t length() const { return size; }
};
```

### 第20天：并发编程基础
**学习目标：** 掌握C++11的并发编程
**学习内容：**
- std::thread的使用
- 线程同步（mutex, condition_variable）
- 原子操作
- 线程安全
- 异步编程（async, future）

**实践练习：**
```cpp
// 实现一个线程安全的计数器
class ThreadSafeCounter {
private:
    mutable std::mutex mtx;
    int count = 0;
public:
    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
    }
    
    int get() const {
        std::lock_guard<std::mutex> lock(mtx);
        return count;
    }
};
```

### 第21天：文件操作与IO
**学习目标：** 掌握C++的文件操作
**学习内容：**
- 文件流（ifstream, ofstream, fstream）
- 文本文件与二进制文件
- 文件定位
- 错误处理
- 字符串流

**实践练习：**
```cpp
// 实现一个简单的文件管理器
class FileManager {
public:
    static bool copyFile(const string& source, const string& destination);
    static bool moveFile(const string& source, const string& destination);
    static vector<string> readLines(const string& filename);
    static void writeLines(const string& filename, const vector<string>& lines);
    static size_t getFileSize(const string& filename);
};
```

## 第四周：高级主题与实战

### 第22天：设计模式
**学习目标：** 学习常用的设计模式
**学习内容：**
- 单例模式
- 工厂模式
- 观察者模式
- 策略模式
- RAII模式

**实践练习：**
```cpp
// 实现一个单例模式的日志管理器
class Logger {
private:
    static Logger* instance;
    ofstream logFile;
    Logger() { logFile.open("app.log"); }
public:
    static Logger* getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }
    
    void log(const string& message) {
        logFile << getCurrentTime() << ": " << message << endl;
    }
    
private:
    string getCurrentTime() const;
};
```

### 第23天：性能优化
**学习目标：** 学习C++性能优化技巧
**学习内容：**
- 编译器优化选项
- 内联函数
- 缓存友好的代码
- 避免不必要的拷贝
- 内存池技术

**实践练习：**
```cpp
// 实现一个高性能的字符串拼接类
class FastStringBuilder {
private:
    vector<char> buffer;
    size_t currentSize = 0;
    
public:
    void reserve(size_t capacity) {
        buffer.reserve(capacity);
    }
    
    void append(const string& str) {
        if (currentSize + str.length() > buffer.size()) {
            buffer.resize(buffer.size() * 2);
        }
        memcpy(buffer.data() + currentSize, str.c_str(), str.length());
        currentSize += str.length();
    }
    
    string toString() const {
        return string(buffer.data(), currentSize);
    }
};
```

### 第24天：调试与测试
**学习目标：** 掌握调试和测试技巧
**学习内容：**
- GDB调试器使用
- Valgrind内存检查
- 单元测试框架
- 断言的使用
- 日志系统

**实践练习：**
```cpp
// 使用断言和异常处理实现一个安全的除法函数
double safeDivide(double a, double b) {
    assert(b != 0.0);  // 调试时检查
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

// 简单的单元测试
void testSafeDivide() {
    assert(safeDivide(10, 2) == 5.0);
    assert(safeDivide(0, 5) == 0.0);
    
    try {
        safeDivide(10, 0);
        assert(false); // 不应该到达这里
    } catch (const std::invalid_argument& e) {
        // 预期的异常
    }
}
```

### 第25天：C++17新特性
**学习目标：** 了解C++17的新特性
**学习内容：**
- 结构化绑定
- if constexpr
- std::optional
- std::variant
- 文件系统库

**实践练习：**
```cpp
// 使用C++17特性实现一个配置管理器
class ConfigManager {
private:
    map<string, variant<int, string, bool>> config;
    
public:
    template<typename T>
    void set(const string& key, const T& value) {
        config[key] = value;
    }
    
    template<typename T>
    optional<T> get(const string& key) const {
        auto it = config.find(key);
        if (it != config.end()) {
            if (holds_alternative<T>(it->second)) {
                return get<T>(it->second);
            }
        }
        return nullopt;
    }
    
    // 使用结构化绑定
    auto getAll() const {
        vector<pair<string, string>> result;
        for (const auto& [key, value] : config) {
            // 处理不同类型的值...
        }
        return result;
    }
};
```

### 第26天：C++20新特性
**学习目标：** 了解C++20的新特性
**学习内容：**
- 概念（Concepts）
- 协程（Coroutines）
- 模块（Modules）
- 范围（Ranges）
- 三路比较运算符

**实践练习：**
```cpp
// 使用C++20概念实现一个排序算法
template<typename T>
concept Sortable = requires(T a, T b) {
    a < b;
    a > b;
    a == b;
};

template<Sortable T>
void bubbleSort(vector<T>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

### 第27天：项目实战 - 数据结构实现
**学习目标：** 实现常用的数据结构
**学习内容：**
- 链表实现
- 栈和队列实现
- 二叉搜索树实现
- 哈希表实现
- 图的基本操作

**实践练习：**
```cpp
// 实现一个简单的哈希表
template<typename K, typename V>
class HashMap {
private:
    static const size_t BUCKET_SIZE = 16;
    vector<list<pair<K, V>>> buckets;
    size_t size_ = 0;
    
    size_t hash(const K& key) const {
        return hash<K>{}(key) % BUCKET_SIZE;
    }
    
public:
    HashMap() : buckets(BUCKET_SIZE) {}
    
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        
        bucket.emplace_back(key, value);
        size_++;
    }
    
    bool find(const K& key, V& value) const {
        size_t index = hash(key);
        const auto& bucket = buckets[index];
        
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }
    
    size_t size() const { return size_; }
};
```

### 第28天：综合项目 - 小型系统设计
**学习目标：** 综合运用所学知识设计一个小型系统
**学习内容：**
- 系统架构设计
- 模块化编程
- 错误处理策略
- 性能考虑
- 代码组织

**实践练习：**
```cpp
// 设计一个简单的任务管理系统
class Task {
public:
    enum Priority { LOW, MEDIUM, HIGH };
    enum Status { PENDING, IN_PROGRESS, COMPLETED };
    
private:
    string id;
    string description;
    Priority priority;
    Status status;
    chrono::system_clock::time_point created;
    
public:
    Task(string desc, Priority p) 
        : id(generateId()), description(desc), priority(p), 
          status(PENDING), created(chrono::system_clock::now()) {}
    
    // 各种getter和setter方法...
    string getId() const { return id; }
    void setStatus(Status s) { status = s; }
    Priority getPriority() const { return priority; }
};

class TaskManager {
private:
    map<string, unique_ptr<Task>> tasks;
    mutex taskMutex;
    
public:
    string addTask(const string& description, Task::Priority priority);
    bool updateTaskStatus(const string& id, Task::Status status);
    vector<Task*> getTasksByPriority(Task::Priority priority) const;
    void removeTask(const string& id);
    void printAllTasks() const;
    
private:
    string generateId() const;
};
```

## 学习建议

### 每日学习流程
1. **理论学习**（30-45分钟）：阅读相关概念和语法
2. **代码实践**（45-60分钟）：完成当天的实践练习
3. **总结复习**（15分钟）：整理笔记，总结重点

### 学习资源推荐
- **书籍**：《C++ Primer》、《Effective C++》、《More Effective C++》
- **在线资源**：cppreference.com、Stack Overflow
- **编译器**：GCC、Clang、MSVC
- **IDE**：Visual Studio、CLion、VS Code

### 实践建议
1. **每天都要写代码**：理论必须与实践结合
2. **做笔记**：记录重要概念和易错点
3. **多思考**：理解为什么这样设计，而不是死记硬背
4. **多练习**：通过不同角度的练习加深理解
5. **及时复习**：定期回顾之前学过的内容

### 评估标准
- **第1周结束**：能够熟练使用基本语法和内存管理
- **第2周结束**：能够设计和实现简单的类体系
- **第3周结束**：能够使用STL和现代C++特性
- **第4周结束**：能够独立设计和实现中等复杂度的项目

记住：学习编程是一个持续的过程，不要急于求成。每天坚持练习，逐步提升，最终你会成为一个优秀的C++程序员！
