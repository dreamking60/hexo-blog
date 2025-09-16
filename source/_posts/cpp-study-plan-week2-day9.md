---
title: C++ 学习计划 - 第9天：构造函数与析构函数
date: 2025-01-27 10:19:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day9
layout: page
menu_id: plan
permalink: /plan/week2/day9/
---

# 第9天：构造函数与析构函数

## 学习目标
掌握对象的构造和析构过程，理解RAII原则，学会编写各种类型的构造函数和析构函数。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Constructors](https://en.cppreference.com/w/cpp/language/constructor) - 构造函数官方文档
- [C++ Reference - Destructors](https://en.cppreference.com/w/cpp/language/destructor) - 析构函数官方文档
- [LearnCpp - Constructors](https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/) - 构造函数详解

### 🎥 视频教程
- [The Cherno C++ Constructors](https://www.youtube.com/watch?v=FXhALMsHwEY) - 构造函数深入讲解
- [C++ RAII Explained](https://www.youtube.com/watch?v=7Qgd9B1KuMQ) - RAII原则详解

### 📖 深入阅读
- [Effective C++ - 条款5-12](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 构造、析构与赋值运算
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-ctor) - 构造函数设计指南
- [More Effective C++ - 条款6](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X) - 自增自减操作符

## 学习内容

### 1. 构造函数基础
- 默认构造函数
- 参数化构造函数
- 拷贝构造函数
- 移动构造函数（C++11）
- 委托构造函数（C++11）

### 2. 初始化列表
- 成员初始化列表的语法
- 初始化顺序
- 必须使用初始化列表的情况
- 性能优势

### 3. 析构函数
- 析构函数的作用
- 虚析构函数
- RAII原则
- 异常安全

### 4. 特殊成员函数
- 三/五/零法则
- 显式删除函数
- 显式默认函数
- 编译器生成的函数

### 5. 对象生命周期
- 构造顺序
- 析构顺序
- 局部对象和全局对象
- 异常处理中的对象管理

## 重点概念和代码示例

### 构造函数基础
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
private:
    string name;
    int age;
    double height;
    vector<string> hobbies;
    
public:
    // 默认构造函数
    Person() {
        cout << "默认构造函数被调用" << endl;
        name = "Unknown";
        age = 0;
        height = 0.0;
    }
    
    // 参数化构造函数
    Person(const string& n, int a, double h) {
        cout << "参数构造函数被调用: " << n << endl;
        name = n;
        age = a;
        height = h;
    }
    
    // 使用初始化列表的构造函数（推荐）
    Person(const string& n, int a, double h, const vector<string>& hobbiesList) 
        : name(n), age(a), height(h), hobbies(hobbiesList) {
        cout << "初始化列表构造函数被调用: " << name << endl;
    }
    
    // 拷贝构造函数
    Person(const Person& other) 
        : name(other.name), age(other.age), height(other.height), hobbies(other.hobbies) {
        cout << "拷贝构造函数被调用: " << name << endl;
    }
    
    // 委托构造函数（C++11）
    Person(const string& n) : Person(n, 0, 0.0) {
        cout << "委托构造函数被调用: " << name << endl;
    }
    
    // 析构函数
    ~Person() {
        cout << "析构函数被调用: " << name << endl;
    }
    
    // 成员函数
    void displayInfo() const {
        cout << "姓名: " << name << ", 年龄: " << age << ", 身高: " << height;
        if (!hobbies.empty()) {
            cout << ", 爱好: ";
            for (const auto& hobby : hobbies) {
                cout << hobby << " ";
            }
        }
        cout << endl;
    }
    
    const string& getName() const { return name; }
};

void constructorDemo() {
    cout << "=== 构造函数演示 ===" << endl;
    
    // 不同的构造方式
    Person p1;  // 默认构造
    Person p2("Alice", 25, 165.5);  // 参数构造
    
    vector<string> hobbies = {"阅读", "游泳", "编程"};
    Person p3("Bob", 30, 175.0, hobbies);  // 初始化列表构造
    
    Person p4("Charlie");  // 委托构造
    
    Person p5 = p2;  // 拷贝构造（注意：这不是赋值！）
    Person p6(p3);   // 显式拷贝构造
    
    cout << "\n对象信息:" << endl;
    p1.displayInfo();
    p2.displayInfo();
    p3.displayInfo();
    p4.displayInfo();
    p5.displayInfo();
    p6.displayInfo();
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 初始化列表详解
```cpp
class InitializationDemo {
private:
    const int constantMember;      // 必须在初始化列表中初始化
    int& referenceMember;          // 必须在初始化列表中初始化
    string name;
    vector<int> numbers;
    
    // 静态成员
    static int objectCount;
    
public:
    // 错误的构造方式示例（注释掉的代码）
    /*
    InitializationDemo(int value, int& ref, const string& n) {
        constantMember = value;  // 错误！const成员不能赋值
        referenceMember = ref;   // 错误！引用不能重新绑定
        name = n;               // 可以，但效率低（先默认构造再赋值）
    }
    */
    
    // 正确的初始化列表构造函数
    InitializationDemo(int value, int& ref, const string& n) 
        : constantMember(value),    // const成员必须这样初始化
          referenceMember(ref),     // 引用成员必须这样初始化
          name(n),                  // 直接构造，效率更高
          numbers(10, 0)            // 调用vector的构造函数
    {
        ++objectCount;
        cout << "InitializationDemo构造完成，对象编号: " << objectCount << endl;
    }
    
    // 拷贝构造函数
    InitializationDemo(const InitializationDemo& other)
        : constantMember(other.constantMember),
          referenceMember(other.referenceMember),
          name(other.name),
          numbers(other.numbers)
    {
        ++objectCount;
        cout << "拷贝构造完成，对象编号: " << objectCount << endl;
    }
    
    ~InitializationDemo() {
        cout << "析构对象编号: " << objectCount-- << endl;
    }
    
    void displayInfo() const {
        cout << "常量成员: " << constantMember 
             << ", 引用成员: " << referenceMember
             << ", 名称: " << name 
             << ", 数组大小: " << numbers.size() << endl;
    }
    
    // 演示初始化顺序
    static void showInitializationOrder() {
        cout << "\n=== 初始化顺序演示 ===" << endl;
        cout << "成员初始化顺序由声明顺序决定，而非初始化列表顺序！" << endl;
    }
};

// 静态成员定义
int InitializationDemo::objectCount = 0;

void initializationListDemo() {
    cout << "\n=== 初始化列表演示 ===" << endl;
    
    int refTarget = 42;
    InitializationDemo obj1(100, refTarget, "Object1");
    obj1.displayInfo();
    
    InitializationDemo obj2 = obj1;  // 拷贝构造
    obj2.displayInfo();
    
    InitializationDemo::showInitializationOrder();
}
```

### RAII和资源管理
```cpp
class RAIIDemo {
private:
    int* data;
    size_t size;
    string resourceName;
    
public:
    // 构造函数 - 获取资源
    RAIIDemo(const string& name, size_t s) : resourceName(name), size(s) {
        cout << "获取资源: " << resourceName << endl;
        data = new int[size];
        
        // 初始化数据
        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i + 1);
        }
    }
    
    // 拷贝构造函数 - 深拷贝
    RAIIDemo(const RAIIDemo& other) 
        : resourceName(other.resourceName + "_copy"), size(other.size) {
        cout << "拷贝资源: " << resourceName << endl;
        data = new int[size];
        
        // 复制数据
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // 赋值操作符
    RAIIDemo& operator=(const RAIIDemo& other) {
        cout << "赋值操作: " << resourceName << " = " << other.resourceName << endl;
        
        if (this != &other) {  // 自赋值检查
            // 释放旧资源
            delete[] data;
            
            // 复制新资源
            size = other.size;
            resourceName = other.resourceName + "_assigned";
            data = new int[size];
            
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 析构函数 - 释放资源
    ~RAIIDemo() {
        cout << "释放资源: " << resourceName << endl;
        delete[] data;  // 自动释放资源
    }
    
    // 访问数据
    int& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t getSize() const { return size; }
    const string& getName() const { return resourceName; }
    
    void display() const {
        cout << resourceName << " [";
        for (size_t i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

void raiiDemo() {
    cout << "\n=== RAII演示 ===" << endl;
    
    try {
        RAIIDemo resource1("Resource1", 5);
        resource1.display();
        
        // 拷贝构造
        RAIIDemo resource2 = resource1;
        resource2.display();
        
        // 修改数据
        resource1[0] = 100;
        resource2[1] = 200;
        
        cout << "修改后:" << endl;
        resource1.display();
        resource2.display();
        
        // 赋值操作
        RAIIDemo resource3("Resource3", 3);
        resource3 = resource1;
        resource3.display();
        
        // 异常测试
        cout << "\n测试异常安全性:" << endl;
        try {
            int value = resource1[10];  // 越界访问
        } catch (const exception& e) {
            cout << "捕获异常: " << e.what() << endl;
        }
        
        cout << "\n函数结束，RAII自动清理资源..." << endl;
    } catch (...) {
        cout << "发生异常，但RAII确保资源被正确释放" << endl;
    }
}
```

## 实践练习

### 练习1：智能数组类
```cpp
template<typename T>
class SmartArray {
private:
    T* data;
    size_t size;
    size_t capacity;
    
    // 扩容函数
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        
        // 移动现有元素
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    // 默认构造函数
    SmartArray() : data(nullptr), size(0), capacity(0) {
        cout << "SmartArray默认构造" << endl;
    }
    
    // 带容量的构造函数
    explicit SmartArray(size_t initialCapacity) 
        : data(new T[initialCapacity]), size(0), capacity(initialCapacity) {
        cout << "SmartArray构造，容量: " << capacity << endl;
    }
    
    // 带初始值的构造函数
    SmartArray(size_t count, const T& value) 
        : data(new T[count]), size(count), capacity(count) {
        cout << "SmartArray构造，大小: " << size << "，初始值: " << value << endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = value;
        }
    }
    
    // 拷贝构造函数
    SmartArray(const SmartArray& other) 
        : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        cout << "SmartArray拷贝构造，大小: " << size << endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // 移动构造函数（C++11）
    SmartArray(SmartArray&& other) noexcept 
        : data(other.data), size(other.size), capacity(other.capacity) {
        cout << "SmartArray移动构造，大小: " << size << endl;
        
        // 清空源对象
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    
    // 析构函数
    ~SmartArray() {
        cout << "SmartArray析构，大小: " << size << endl;
        delete[] data;
    }
    
    // 赋值操作符
    SmartArray& operator=(const SmartArray& other) {
        cout << "SmartArray拷贝赋值" << endl;
        if (this != &other) {
            delete[] data;
            
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 移动赋值操作符（C++11）
    SmartArray& operator=(SmartArray&& other) noexcept {
        cout << "SmartArray移动赋值" << endl;
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }
    
    // 添加元素
    void push_back(const T& value) {
        if (size >= capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = value;
    }
    
    // 访问元素
    T& operator[](size_t index) {
        if (index >= size) throw out_of_range("Index out of range");
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size) throw out_of_range("Index out of range");
        return data[index];
    }
    
    // 获取信息
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return size == 0; }
    
    // 显示内容
    void display() const {
        cout << "SmartArray [";
        for (size_t i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "] (size: " << size << ", capacity: " << capacity << ")" << endl;
    }
};

void exercise1() {
    cout << "\n=== 练习1：智能数组类 ===" << endl;
    
    // 不同的构造方式
    SmartArray<int> arr1;  // 默认构造
    SmartArray<int> arr2(5);  // 指定容量
    SmartArray<int> arr3(3, 100);  // 指定大小和初始值
    
    cout << "\n初始状态:" << endl;
    arr1.display();
    arr2.display();
    arr3.display();
    
    // 添加元素
    cout << "\n添加元素:" << endl;
    for (int i = 1; i <= 8; i++) {
        arr1.push_back(i * 10);
        if (i % 3 == 0) arr1.display();  // 显示扩容过程
    }
    
    for (int i = 1; i <= 3; i++) {
        arr2.push_back(i);
    }
    arr2.display();
    
    // 拷贝构造和赋值
    cout << "\n拷贝操作:" << endl;
    SmartArray<int> arr4 = arr1;  // 拷贝构造
    arr4.display();
    
    SmartArray<int> arr5;
    arr5 = arr3;  // 拷贝赋值
    arr5.display();
    
    // 修改元素
    cout << "\n修改元素:" << endl;
    arr4[0] = 999;
    arr4.display();
    arr1.display();  // 验证深拷贝
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 练习2：字符串类实现
```cpp
class MyString {
private:
    char* str;
    size_t length;
    
    // 辅助函数：复制字符串
    void copyString(const char* source) {
        if (source) {
            length = strlen(source);
            str = new char[length + 1];
            strcpy(str, source);
        } else {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        }
    }
    
public:
    // 默认构造函数
    MyString() : str(nullptr), length(0) {
        cout << "MyString默认构造" << endl;
        str = new char[1];
        str[0] = '\0';
    }
    
    // 从C字符串构造
    MyString(const char* cstr) {
        cout << "MyString从C字符串构造: " << (cstr ? cstr : "nullptr") << endl;
        copyString(cstr);
    }
    
    // 拷贝构造函数
    MyString(const MyString& other) {
        cout << "MyString拷贝构造: " << other.str << endl;
        copyString(other.str);
    }
    
    // 移动构造函数（C++11）
    MyString(MyString&& other) noexcept : str(other.str), length(other.length) {
        cout << "MyString移动构造: " << str << endl;
        other.str = nullptr;
        other.length = 0;
    }
    
    // 析构函数
    ~MyString() {
        cout << "MyString析构: " << (str ? str : "nullptr") << endl;
        delete[] str;
    }
    
    // 拷贝赋值操作符
    MyString& operator=(const MyString& other) {
        cout << "MyString拷贝赋值: " << other.str << endl;
        if (this != &other) {
            delete[] str;
            copyString(other.str);
        }
        return *this;
    }
    
    // 移动赋值操作符（C++11）
    MyString& operator=(MyString&& other) noexcept {
        cout << "MyString移动赋值: " << other.str << endl;
        if (this != &other) {
            delete[] str;
            str = other.str;
            length = other.length;
            
            other.str = nullptr;
            other.length = 0;
        }
        return *this;
    }
    
    // 从C字符串赋值
    MyString& operator=(const char* cstr) {
        cout << "MyString从C字符串赋值: " << (cstr ? cstr : "nullptr") << endl;
        delete[] str;
        copyString(cstr);
        return *this;
    }
    
    // 字符串拼接
    MyString operator+(const MyString& other) const {
        size_t newLength = length + other.length;
        char* newStr = new char[newLength + 1];
        
        strcpy(newStr, str);
        strcat(newStr, other.str);
        
        MyString result;
        delete[] result.str;
        result.str = newStr;
        result.length = newLength;
        
        return result;
    }
    
    // 字符访问
    char& operator[](size_t index) {
        if (index >= length) throw out_of_range("Index out of range");
        return str[index];
    }
    
    const char& operator[](size_t index) const {
        if (index >= length) throw out_of_range("Index out of range");
        return str[index];
    }
    
    // 比较操作
    bool operator==(const MyString& other) const {
        return strcmp(str, other.str) == 0;
    }
    
    bool operator<(const MyString& other) const {
        return strcmp(str, other.str) < 0;
    }
    
    // 获取信息
    size_t size() const { return length; }
    bool empty() const { return length == 0; }
    const char* c_str() const { return str; }
    
    // 输出流操作符
    friend ostream& operator<<(ostream& os, const MyString& myStr) {
        os << myStr.str;
        return os;
    }
    
    // 输入流操作符
    friend istream& operator>>(istream& is, MyString& myStr) {
        char buffer[1000];
        is >> buffer;
        myStr = buffer;
        return is;
    }
};

void exercise2() {
    cout << "\n=== 练习2：字符串类实现 ===" << endl;
    
    // 构造函数测试
    MyString str1;  // 默认构造
    MyString str2("Hello");  // 从C字符串构造
    MyString str3 = str2;  // 拷贝构造
    
    cout << "\n初始字符串:" << endl;
    cout << "str1: \"" << str1 << "\"" << endl;
    cout << "str2: \"" << str2 << "\"" << endl;
    cout << "str3: \"" << str3 << "\"" << endl;
    
    // 赋值操作
    cout << "\n赋值操作:" << endl;
    str1 = "World";
    str3 = str1;
    
    cout << "str1: \"" << str1 << "\"" << endl;
    cout << "str3: \"" << str3 << "\"" << endl;
    
    // 字符串拼接
    cout << "\n字符串拼接:" << endl;
    MyString str4 = str2 + MyString(" ") + str1;
    cout << "str4: \"" << str4 << "\"" << endl;
    
    // 字符访问和修改
    cout << "\n字符访问:" << endl;
    cout << "str4[0] = " << str4[0] << endl;
    str4[0] = 'h';
    cout << "修改后 str4: \"" << str4 << "\"" << endl;
    
    // 比较操作
    cout << "\n比较操作:" << endl;
    cout << "str2 == str3: " << (str2 == str3) << endl;
    cout << "str1 < str2: " << (str1 < str2) << endl;
    
    // 移动语义演示
    cout << "\n移动语义:" << endl;
    MyString str5 = MyString("Temporary");  // 移动构造
    str5 = MyString("Another Temp");  // 移动赋值
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 练习3：异常安全的资源管理
```cpp
class FileManager {
private:
    string filename;
    FILE* file;
    bool isOpen;
    
public:
    // 构造函数
    explicit FileManager(const string& name) : filename(name), file(nullptr), isOpen(false) {
        cout << "FileManager构造: " << filename << endl;
        
        // 尝试打开文件
        file = fopen(filename.c_str(), "w+");
        if (file) {
            isOpen = true;
            cout << "文件打开成功: " << filename << endl;
        } else {
            cout << "文件打开失败: " << filename << endl;
            throw runtime_error("无法打开文件: " + filename);
        }
    }
    
    // 禁止拷贝（文件句柄不应该被复制）
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    // 移动构造函数
    FileManager(FileManager&& other) noexcept 
        : filename(move(other.filename)), file(other.file), isOpen(other.isOpen) {
        cout << "FileManager移动构造: " << filename << endl;
        
        // 清空源对象
        other.file = nullptr;
        other.isOpen = false;
    }
    
    // 移动赋值操作符
    FileManager& operator=(FileManager&& other) noexcept {
        cout << "FileManager移动赋值: " << other.filename << endl;
        
        if (this != &other) {
            // 关闭当前文件
            close();
            
            // 移动资源
            filename = move(other.filename);
            file = other.file;
            isOpen = other.isOpen;
            
            // 清空源对象
            other.file = nullptr;
            other.isOpen = false;
        }
        return *this;
    }
    
    // 析构函数
    ~FileManager() {
        cout << "FileManager析构: " << filename << endl;
        close();
    }
    
    // 写入数据
    bool write(const string& data) {
        if (!isOpen || !file) {
            cout << "文件未打开，无法写入" << endl;
            return false;
        }
        
        size_t written = fwrite(data.c_str(), 1, data.length(), file);
        fflush(file);  // 立即刷新到磁盘
        
        cout << "写入 " << written << " 字节到 " << filename << endl;
        return written == data.length();
    }
    
    // 读取数据
    string read() {
        if (!isOpen || !file) {
            cout << "文件未打开，无法读取" << endl;
            return "";
        }
        
        // 移动到文件开头
        fseek(file, 0, SEEK_SET);
        
        // 获取文件大小
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        if (size <= 0) return "";
        
        // 读取数据
        string content(size, '\0');
        size_t bytesRead = fread(&content[0], 1, size, file);
        content.resize(bytesRead);
        
        cout << "从 " << filename << " 读取 " << bytesRead << " 字节" << endl;
        return content;
    }
    
    // 手动关闭文件
    void close() {
        if (file) {
            fclose(file);
            file = nullptr;
            isOpen = false;
            cout << "文件关闭: " << filename << endl;
        }
    }
    
    // 状态查询
    bool isFileOpen() const { return isOpen; }
    const string& getFilename() const { return filename; }
};

void exercise3() {
    cout << "\n=== 练习3：异常安全的资源管理 ===" << endl;
    
    try {
        // 正常文件操作
        FileManager fm1("test1.txt");
        fm1.write("Hello, World!\n");
        fm1.write("这是第二行\n");
        
        string content = fm1.read();
        cout << "读取的内容:\n" << content << endl;
        
        // 移动语义测试
        cout << "\n移动语义测试:" << endl;
        FileManager fm2("test2.txt");
        fm2.write("原始文件内容\n");
        
        // 移动构造
        FileManager fm3 = move(fm2);
        fm3.write("移动后添加的内容\n");
        
        cout << "fm3内容: " << fm3.read() << endl;
        
        // 尝试打开不存在的目录中的文件（会抛出异常）
        cout << "\n异常测试:" << endl;
        try {
            FileManager fm4("/nonexistent/path/file.txt");
        } catch (const exception& e) {
            cout << "捕获异常: " << e.what() << endl;
        }
        
        cout << "\n正常结束，RAII自动清理资源..." << endl;
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
        cout << "但RAII确保资源被正确释放" << endl;
    }
}
```

## 学习检查点

- [ ] 理解构造函数的各种类型和用途
- [ ] 掌握初始化列表的语法和优势
- [ ] 理解析构函数的作用和RAII原则
- [ ] 掌握拷贝构造函数和赋值操作符的区别
- [ ] 了解移动语义的基本概念（C++11）
- [ ] 能够设计异常安全的类
- [ ] 理解对象的生命周期管理
- [ ] 掌握资源管理的最佳实践

## 完整示例程序

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <cstdio>
using namespace std;

int main() {
    cout << "=== C++ 构造函数与析构函数学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        constructorDemo();
        initializationListDemo();
        raiiDemo();
        
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

[返回第二周](/plan/week2/) | [上一天：类与对象基础](/plan/week2/day8/) | [下一天：继承](/plan/week2/day10/)
