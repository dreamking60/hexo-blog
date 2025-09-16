# 第19天：移动语义复习

## 学习目标
掌握C++11引入的移动语义，理解左值与右值的概念，学会使用移动构造函数和移动赋值运算符优化性能。

## 学习内容

### 1. 移动语义概述

移动语义是C++11引入的重要特性，它允许"移动"资源而不是复制，从而显著提高性能，特别是在处理大型对象时。

#### 为什么需要移动语义？
- **性能优化**：避免不必要的深拷贝
- **资源管理**：高效转移资源所有权
- **异常安全**：减少异常时的资源浪费
- **现代C++**：支持现代C++编程模式

### 2. 左值与右值

#### 左值 (Lvalue)
左值是可以取地址的表达式，通常表示一个对象的内存位置。

```cpp
#include <iostream>

void lvalueExample() {
    int x = 42;        // x是左值
    int& ref = x;      // ref是左值引用
    int* ptr = &x;     // 可以取x的地址
    
    std::cout << "x = " << x << std::endl;
    std::cout << "ref = " << ref << std::endl;
    std::cout << "ptr = " << ptr << std::endl;
}
```

#### 右值 (Rvalue)
右值是不能取地址的表达式，通常是临时对象或字面量。

```cpp
#include <iostream>
#include <string>

void rvalueExample() {
    int x = 42;                    // 42是右值
    std::string s = "Hello";       // "Hello"是右值
    int result = x + 5;            // x + 5是右值
    
    // 函数返回的临时对象是右值
    std::string getString() {
        return "World";
    }
    
    std::string str = getString(); // getString()返回的是右值
    
    std::cout << "x = " << x << std::endl;
    std::cout << "s = " << s << std::endl;
    std::cout << "result = " << result << std::endl;
    std::cout << "str = " << str << std::endl;
}
```

#### 左值引用与右值引用
```cpp
#include <iostream>
#include <string>

void referenceExample() {
    int x = 42;
    
    // 左值引用
    int& lref = x;        // 正确：绑定到左值
    // int& lref2 = 42;   // 错误：不能绑定到右值
    
    // 右值引用
    int&& rref = 42;      // 正确：绑定到右值
    int&& rref2 = x + 5;  // 正确：绑定到右值
    // int&& rref3 = x;   // 错误：不能绑定到左值
    
    std::cout << "lref = " << lref << std::endl;
    std::cout << "rref = " << rref << std::endl;
    std::cout << "rref2 = " << rref2 << std::endl;
}
```

### 3. 移动构造函数

移动构造函数用于从右值转移资源，避免深拷贝。

#### 基本移动构造函数
```cpp
#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    size_t size;
    
public:
    // 构造函数
    MyString(const char* str = "") : size(strlen(str)) {
        data = new char[size + 1];
        strcpy(data, str);
        std::cout << "构造函数: " << data << std::endl;
    }
    
    // 拷贝构造函数
    MyString(const MyString& other) : size(other.size) {
        data = new char[size + 1];
        strcpy(data, other.data);
        std::cout << "拷贝构造函数: " << data << std::endl;
    }
    
    // 移动构造函数
    MyString(MyString&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "移动构造函数: " << data << std::endl;
    }
    
    // 析构函数
    ~MyString() {
        if (data) {
            std::cout << "析构函数: " << data << std::endl;
            delete[] data;
        }
    }
    
    // 拷贝赋值运算符
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            strcpy(data, other.data);
            std::cout << "拷贝赋值: " << data << std::endl;
        }
        return *this;
    }
    
    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "移动赋值: " << data << std::endl;
        }
        return *this;
    }
    
    const char* c_str() const { return data; }
    size_t length() const { return size; }
};

void moveConstructorExample() {
    std::cout << "=== 移动构造函数示例 ===" << std::endl;
    
    // 创建对象
    MyString str1("Hello");
    
    // 移动构造
    MyString str2 = std::move(str1);  // 调用移动构造函数
    
    std::cout << "str1: " << (str1.c_str() ? str1.c_str() : "null") << std::endl;
    std::cout << "str2: " << str2.c_str() << std::endl;
}
```

### 4. 移动赋值运算符

移动赋值运算符用于从右值转移资源到已存在的对象。

```cpp
void moveAssignmentExample() {
    std::cout << "\n=== 移动赋值运算符示例 ===" << std::endl;
    
    MyString str1("World");
    MyString str2("Hello");
    
    // 移动赋值
    str2 = std::move(str1);  // 调用移动赋值运算符
    
    std::cout << "str1: " << (str1.c_str() ? str1.c_str() : "null") << std::endl;
    std::cout << "str2: " << str2.c_str() << std::endl;
}
```

### 5. std::move

`std::move`用于将左值转换为右值引用，启用移动语义。

```cpp
#include <iostream>
#include <vector>
#include <string>

void stdMoveExample() {
    std::cout << "\n=== std::move示例 ===" << std::endl;
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    
    std::cout << "移动前:" << std::endl;
    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    
    // 使用std::move
    str2 = std::move(str1);
    
    std::cout << "移动后:" << std::endl;
    std::cout << "str1: " << str1 << std::endl;  // 可能为空
    std::cout << "str2: " << str2 << std::endl;
    
    // 容器中的移动
    std::vector<std::string> vec;
    vec.push_back(std::move(str2));  // 移动str2到容器中
    
    std::cout << "移动后str2: " << str2 << std::endl;
    std::cout << "容器中的字符串: " << vec[0] << std::endl;
}
```

### 6. 完美转发 (Perfect Forwarding)

完美转发允许函数模板将其参数完美地转发给另一个函数。

```cpp
#include <iostream>
#include <utility>

// 完美转发示例
template<typename T>
void forwardFunction(T&& arg) {
    std::cout << "转发参数: " << arg << std::endl;
}

template<typename T>
void perfectForward(T&& arg) {
    // 使用std::forward保持参数的值类别
    forwardFunction(std::forward<T>(arg));
}

void perfectForwardingExample() {
    std::cout << "\n=== 完美转发示例 ===" << std::endl;
    
    int x = 42;
    const int y = 100;
    
    // 左值
    perfectForward(x);
    
    // 右值
    perfectForward(42);
    
    // 常量左值
    perfectForward(y);
    
    // 右值引用
    perfectForward(std::move(x));
}
```

### 7. 移动语义与容器

```cpp
#include <iostream>
#include <vector>
#include <string>

void moveWithContainers() {
    std::cout << "\n=== 移动语义与容器 ===" << std::endl;
    
    std::vector<std::string> vec;
    
    // 使用emplace_back避免不必要的拷贝
    vec.emplace_back("Hello");
    vec.emplace_back("World");
    vec.emplace_back("C++");
    
    std::cout << "容器内容:" << std::endl;
    for (const auto& str : vec) {
        std::cout << "  " << str << std::endl;
    }
    
    // 移动元素
    std::string temp = std::move(vec[0]);
    std::cout << "移动第一个元素: " << temp << std::endl;
    std::cout << "第一个元素现在: " << vec[0] << std::endl;
    
    // 移动整个容器
    std::vector<std::string> vec2 = std::move(vec);
    std::cout << "移动后vec大小: " << vec.size() << std::endl;
    std::cout << "移动后vec2大小: " << vec2.size() << std::endl;
}
```

### 8. 移动语义与智能指针

```cpp
#include <iostream>
#include <memory>
#include <vector>

void moveWithSmartPointers() {
    std::cout << "\n=== 移动语义与智能指针 ===" << std::endl;
    
    // unique_ptr支持移动语义
    auto ptr1 = std::make_unique<int>(42);
    std::cout << "ptr1: " << *ptr1 << std::endl;
    
    // 移动unique_ptr
    auto ptr2 = std::move(ptr1);
    std::cout << "ptr1是否为空: " << (ptr1 == nullptr) << std::endl;
    std::cout << "ptr2: " << *ptr2 << std::endl;
    
    // 容器存储unique_ptr
    std::vector<std::unique_ptr<int>> vec;
    vec.push_back(std::make_unique<int>(1));
    vec.push_back(std::make_unique<int>(2));
    vec.push_back(std::make_unique<int>(3));
    
    // 移动unique_ptr到容器
    auto ptr3 = std::make_unique<int>(4);
    vec.push_back(std::move(ptr3));
    
    std::cout << "容器中的值: ";
    for (const auto& ptr : vec) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;
}
```

## 实践练习

### 练习1：资源管理类
```cpp
#include <iostream>
#include <memory>
#include <vector>

class Resource {
private:
    int* data;
    size_t size;
    
public:
    Resource(size_t s) : size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
        std::cout << "创建资源，大小: " << size << std::endl;
    }
    
    // 拷贝构造函数
    Resource(const Resource& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "拷贝构造资源" << std::endl;
    }
    
    // 移动构造函数
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "移动构造资源" << std::endl;
    }
    
    // 拷贝赋值运算符
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            std::cout << "拷贝赋值资源" << std::endl;
        }
        return *this;
    }
    
    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "移动赋值资源" << std::endl;
        }
        return *this;
    }
    
    ~Resource() {
        if (data) {
            std::cout << "销毁资源，大小: " << size << std::endl;
            delete[] data;
        }
    }
    
    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
    size_t getSize() const { return size; }
};

void resourceManagementExample() {
    std::cout << "=== 资源管理示例 ===" << std::endl;
    
    // 创建资源
    Resource res1(5);
    std::cout << "res1[0] = " << res1[0] << std::endl;
    
    // 移动构造
    Resource res2 = std::move(res1);
    std::cout << "res2[0] = " << res2[0] << std::endl;
    std::cout << "res1大小: " << res1.getSize() << std::endl;
    
    // 移动赋值
    Resource res3(3);
    res3 = std::move(res2);
    std::cout << "res3[0] = " << res3[0] << std::endl;
    std::cout << "res2大小: " << res2.getSize() << std::endl;
}
```

### 练习2：移动语义优化
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class OptimizedString {
private:
    char* data;
    size_t size;
    size_t capacity;
    
public:
    OptimizedString(const char* str = "") : size(strlen(str)), capacity(size + 1) {
        data = new char[capacity];
        strcpy(data, str);
    }
    
    // 移动构造函数
    OptimizedString(OptimizedString&& other) noexcept 
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    
    // 移动赋值运算符
    OptimizedString& operator=(OptimizedString&& other) noexcept {
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
    
    ~OptimizedString() {
        delete[] data;
    }
    
    const char* c_str() const { return data; }
    size_t length() const { return size; }
};

void performanceComparison() {
    std::cout << "\n=== 性能比较 ===" << std::endl;
    
    const int count = 100000;
    
    // 测试移动语义
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<OptimizedString> vec;
    vec.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        vec.emplace_back("Hello World");
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "移动语义优化后，创建 " << count << " 个字符串耗时: " 
              << duration.count() << " 微秒" << std::endl;
}
```

### 练习3：工厂模式与移动语义
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

class ConcreteProductA : public Product {
private:
    std::string data;
    
public:
    ConcreteProductA(std::string d) : data(std::move(d)) {}
    
    void use() const override {
        std::cout << "使用产品A: " << data << std::endl;
    }
};

class ConcreteProductB : public Product {
private:
    std::string data;
    
public:
    ConcreteProductB(std::string d) : data(std::move(d)) {}
    
    void use() const override {
        std::cout << "使用产品B: " << data << std::endl;
    }
};

class ProductFactory {
public:
    static std::unique_ptr<Product> createProductA(std::string data) {
        return std::make_unique<ConcreteProductA>(std::move(data));
    }
    
    static std::unique_ptr<Product> createProductB(std::string data) {
        return std::make_unique<ConcreteProductB>(std::move(data));
    }
};

void factoryPatternExample() {
    std::cout << "\n=== 工厂模式与移动语义 ===" << std::endl;
    
    std::vector<std::unique_ptr<Product>> products;
    
    // 创建产品
    products.push_back(ProductFactory::createProductA("数据A"));
    products.push_back(ProductFactory::createProductB("数据B"));
    products.push_back(ProductFactory::createProductA("数据C"));
    
    // 使用产品
    for (const auto& product : products) {
        product->use();
    }
}
```

## 学习要点总结

1. **左值右值**：理解左值和右值的区别
2. **移动语义**：掌握移动构造函数和移动赋值运算符
3. **std::move**：学会使用std::move启用移动语义
4. **完美转发**：理解std::forward的作用
5. **性能优化**：通过移动语义提高程序性能

## 今日算法题

完成以下4道LeetCode题目，巩固移动语义的使用：

1. [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/) - 使用移动语义优化缓存操作
2. [LeetCode 208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) - 使用移动语义优化字典树
3. [LeetCode 341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/) - 使用移动语义优化迭代器
4. [LeetCode 460. LFU Cache](https://leetcode.com/problems/lfu-cache/) - 使用移动语义优化LFU缓存

每道题目都涉及移动语义的使用，是很好的实践机会！
