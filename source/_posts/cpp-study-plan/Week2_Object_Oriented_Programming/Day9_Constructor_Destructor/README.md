# 第9天：构造函数与析构函数

## 学习目标
掌握C++对象的构造和析构过程，理解RAII原则，学会设计异常安全的类，掌握拷贝构造函数和移动构造函数的使用。

## 学习内容

### 1. 构造函数
构造函数是类的特殊成员函数，用于初始化对象。当创建对象时，构造函数会自动调用。

#### 构造函数的特性
- 函数名与类名相同
- 没有返回类型
- 可以重载
- 自动调用

#### 构造函数的类型
```cpp
class MyClass {
private:
    int value;
    string name;
    
public:
    // 1. 默认构造函数
    MyClass();
    
    // 2. 带参数的构造函数
    MyClass(int val, string n);
    
    // 3. 拷贝构造函数
    MyClass(const MyClass& other);
    
    // 4. 移动构造函数 (C++11)
    MyClass(MyClass&& other) noexcept;
    
    // 5. 委托构造函数 (C++11)
    MyClass(int val) : MyClass(val, "default") {}
};
```

### 2. 析构函数
析构函数用于清理对象资源，当对象销毁时自动调用。

#### 析构函数的特性
- 函数名为 `~类名`
- 没有参数和返回类型
- 不能重载
- 自动调用

```cpp
class MyClass {
public:
    // 析构函数
    ~MyClass();
};
```

### 3. 初始化列表
初始化列表是构造函数的重要特性，用于初始化成员变量。

```cpp
class MyClass {
private:
    int value;
    string name;
    const int id;
    
public:
    // 使用初始化列表
    MyClass(int val, string n, int identifier) 
        : value(val), name(n), id(identifier) {
        // 构造函数体
    }
};
```

### 4. 拷贝构造函数
拷贝构造函数用于创建一个对象的副本。

```cpp
class MyClass {
public:
    // 拷贝构造函数
    MyClass(const MyClass& other) 
        : value(other.value), name(other.name) {
        cout << "拷贝构造函数被调用" << endl;
    }
};
```

### 5. 移动构造函数 (C++11)
移动构造函数用于转移资源所有权，提高性能。

```cpp
class MyClass {
public:
    // 移动构造函数
    MyClass(MyClass&& other) noexcept 
        : value(std::move(other.value)), name(std::move(other.name)) {
        cout << "移动构造函数被调用" << endl;
    }
};
```

### 6. RAII原则
RAII（Resource Acquisition Is Initialization）是C++的重要设计原则：
- 资源获取即初始化
- 资源在对象构造时获取
- 资源在对象析构时释放

## 实践练习

### 练习1：资源管理类
实现一个资源管理类，演示RAII原则和异常安全。

```cpp
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class ResourceManager {
private:
    int* resource;
    size_t size;
    string name;
    
public:
    // 构造函数
    ResourceManager(size_t s, string n);
    
    // 拷贝构造函数
    ResourceManager(const ResourceManager& other);
    
    // 移动构造函数
    ResourceManager(ResourceManager&& other) noexcept;
    
    // 拷贝赋值运算符
    ResourceManager& operator=(const ResourceManager& other);
    
    // 移动赋值运算符
    ResourceManager& operator=(ResourceManager&& other) noexcept;
    
    // 析构函数
    ~ResourceManager();
    
    // 其他成员函数
    void setValue(size_t index, int value);
    int getValue(size_t index) const;
    void display() const;
    size_t getSize() const { return size; }
    string getName() const { return name; }
};

// 构造函数实现
ResourceManager::ResourceManager(size_t s, string n) 
    : size(s), name(n) {
    cout << "构造函数: 为 " << name << " 分配 " << size << " 个int资源" << endl;
    
    if (size == 0) {
        resource = nullptr;
        return;
    }
    
    try {
        resource = new int[size];
        // 初始化资源
        for (size_t i = 0; i < size; ++i) {
            resource[i] = 0;
        }
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 拷贝构造函数实现
ResourceManager::ResourceManager(const ResourceManager& other) 
    : size(other.size), name(other.name + "_copy") {
    cout << "拷贝构造函数: 为 " << name << " 分配资源" << endl;
    
    if (size == 0) {
        resource = nullptr;
        return;
    }
    
    try {
        resource = new int[size];
        // 深拷贝
        for (size_t i = 0; i < size; ++i) {
            resource[i] = other.resource[i];
        }
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 移动构造函数实现
ResourceManager::ResourceManager(ResourceManager&& other) noexcept 
    : resource(other.resource), size(other.size), name(other.name + "_moved") {
    cout << "移动构造函数: 转移 " << other.name << " 的资源" << endl;
    
    // 转移资源所有权
    other.resource = nullptr;
    other.size = 0;
    other.name = "moved_away";
}

// 拷贝赋值运算符实现
ResourceManager& ResourceManager::operator=(const ResourceManager& other) {
    cout << "拷贝赋值运算符: " << name << " = " << other.name << endl;
    
    if (this != &other) {  // 自赋值检查
        // 释放当前资源
        delete[] resource;
        
        // 分配新资源
        size = other.size;
        name = other.name + "_assigned";
        
        if (size == 0) {
            resource = nullptr;
        } else {
            try {
                resource = new int[size];
                // 深拷贝
                for (size_t i = 0; i < size; ++i) {
                    resource[i] = other.resource[i];
                }
            } catch (const bad_alloc& e) {
                cout << "内存分配失败: " << e.what() << endl;
                resource = nullptr;
                size = 0;
                throw;
            }
        }
    }
    
    return *this;
}

// 移动赋值运算符实现
ResourceManager& ResourceManager::operator=(ResourceManager&& other) noexcept {
    cout << "移动赋值运算符: " << name << " = " << other.name << endl;
    
    if (this != &other) {  // 自赋值检查
        // 释放当前资源
        delete[] resource;
        
        // 转移资源所有权
        resource = other.resource;
        size = other.size;
        name = other.name + "_moved_assigned";
        
        // 清空源对象
        other.resource = nullptr;
        other.size = 0;
        other.name = "moved_away";
    }
    
    return *this;
}

// 析构函数实现
ResourceManager::~ResourceManager() {
    cout << "析构函数: 释放 " << name << " 的资源" << endl;
    delete[] resource;
}

// 设置值
void ResourceManager::setValue(size_t index, int value) {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    resource[index] = value;
}

// 获取值
int ResourceManager::getValue(size_t index) const {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    return resource[index];
}

// 显示内容
void ResourceManager::display() const {
    cout << name << " (" << size << " elements): ";
    if (resource == nullptr) {
        cout << "null";
    } else {
        for (size_t i = 0; i < size; ++i) {
            cout << resource[i] << " ";
        }
    }
    cout << endl;
}
```

### 练习2：智能指针模拟
实现一个简单的智能指针类，演示RAII原则。

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class SimpleUniquePtr {
private:
    T* ptr;
    
public:
    // 构造函数
    SimpleUniquePtr() : ptr(nullptr) {}
    
    explicit SimpleUniquePtr(T* p) : ptr(p) {
        cout << "SimpleUniquePtr: 接管资源" << endl;
    }
    
    // 禁用拷贝构造和拷贝赋值
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;
    
    // 移动构造函数
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept 
        : ptr(other.ptr) {
        cout << "SimpleUniquePtr: 移动构造" << endl;
        other.ptr = nullptr;
    }
    
    // 移动赋值运算符
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        cout << "SimpleUniquePtr: 移动赋值" << endl;
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // 析构函数
    ~SimpleUniquePtr() {
        cout << "SimpleUniquePtr: 释放资源" << endl;
        delete ptr;
    }
    
    // 解引用运算符
    T& operator*() const {
        if (ptr == nullptr) {
            throw runtime_error("空指针解引用");
        }
        return *ptr;
    }
    
    // 箭头运算符
    T* operator->() const {
        if (ptr == nullptr) {
            throw runtime_error("空指针访问");
        }
        return ptr;
    }
    
    // 获取原始指针
    T* get() const { return ptr; }
    
    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // 重置指针
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    // 检查是否为空
    bool empty() const { return ptr == nullptr; }
};

// 测试类
class TestClass {
private:
    int value;
    
public:
    TestClass(int v) : value(v) {
        cout << "TestClass构造: " << value << endl;
    }
    
    ~TestClass() {
        cout << "TestClass析构: " << value << endl;
    }
    
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
};
```

### 练习3：异常安全的类
实现一个异常安全的数组类。

```cpp
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

class SafeArray {
private:
    int* data;
    size_t size;
    
public:
    // 构造函数
    explicit SafeArray(size_t s);
    
    // 拷贝构造函数
    SafeArray(const SafeArray& other);
    
    // 移动构造函数
    SafeArray(SafeArray&& other) noexcept;
    
    // 拷贝赋值运算符
    SafeArray& operator=(const SafeArray& other);
    
    // 移动赋值运算符
    SafeArray& operator=(SafeArray&& other) noexcept;
    
    // 析构函数
    ~SafeArray();
    
    // 访问元素
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    
    // 获取大小
    size_t getSize() const { return size; }
    
    // 显示内容
    void display() const;
    
private:
    // 辅助函数：安全的数组复制
    void safeCopy(const SafeArray& other);
    
    // 辅助函数：安全的数组移动
    void safeMove(SafeArray&& other) noexcept;
};

// 构造函数实现
SafeArray::SafeArray(size_t s) : size(s) {
    cout << "SafeArray构造: 分配 " << size << " 个元素" << endl;
    
    if (size == 0) {
        data = nullptr;
        return;
    }
    
    try {
        data = new int[size];
        // 初始化为0
        fill(data, data + size, 0);
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 拷贝构造函数实现
SafeArray::SafeArray(const SafeArray& other) : size(other.size) {
    cout << "SafeArray拷贝构造" << endl;
    safeCopy(other);
}

// 移动构造函数实现
SafeArray::SafeArray(SafeArray&& other) noexcept {
    cout << "SafeArray移动构造" << endl;
    safeMove(std::move(other));
}

// 拷贝赋值运算符实现
SafeArray& SafeArray::operator=(const SafeArray& other) {
    cout << "SafeArray拷贝赋值" << endl;
    
    if (this != &other) {
        SafeArray temp(other);  // 创建临时对象
        safeMove(std::move(temp));  // 移动临时对象
    }
    
    return *this;
}

// 移动赋值运算符实现
SafeArray& SafeArray::operator=(SafeArray&& other) noexcept {
    cout << "SafeArray移动赋值" << endl;
    
    if (this != &other) {
        safeMove(std::move(other));
    }
    
    return *this;
}

// 析构函数实现
SafeArray::~SafeArray() {
    cout << "SafeArray析构: 释放 " << size << " 个元素" << endl;
    delete[] data;
}

// 访问元素
int& SafeArray::operator[](size_t index) {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    return data[index];
}

const int& SafeArray::operator[](size_t index) const {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    return data[index];
}

// 显示内容
void SafeArray::display() const {
    cout << "SafeArray (" << size << " elements): ";
    if (data == nullptr) {
        cout << "null";
    } else {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
    }
    cout << endl;
}

// 辅助函数：安全的数组复制
void SafeArray::safeCopy(const SafeArray& other) {
    if (other.size == 0) {
        data = nullptr;
        return;
    }
    
    try {
        data = new int[other.size];
        copy(other.data, other.data + other.size, data);
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 辅助函数：安全的数组移动
void SafeArray::safeMove(SafeArray&& other) noexcept {
    delete[] data;
    data = other.data;
    size = other.size;
    
    other.data = nullptr;
    other.size = 0;
}
```

## 算法题练习

### 1. 设计推特 (Medium)
**题目链接**: https://leetcode.cn/problems/design-twitter/

设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近十条推文。

**关键点**：
- 使用面向对象设计
- 合理的数据结构选择
- 时间线算法实现

### 2. 设计前K个高频元素 (Medium)
**题目链接**: https://leetcode.cn/problems/top-k-frequent-elements/

给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

**关键点**：
- 哈希表统计频率
- 堆排序或快速选择算法
- 时间复杂度优化

### 3. 设计循环双端队列 (Medium)
**题目链接**: https://leetcode.cn/problems/design-circular-deque/

设计实现双端队列。你的实现需要支持以下操作：
- MyCircularDeque(k)：构造函数,双端队列的大小为k。
- insertFront()：将一个元素添加到双端队列头部。如果操作成功返回 true。
- insertLast()：将一个元素添加到双端队列尾部。如果操作成功返回 true。
- deleteFront()：从双端队列头部删除一个元素。如果操作成功返回 true。
- deleteLast()：从双端队列尾部删除一个元素。如果操作成功返回 true。
- getFront()：从双端队列头部获得一个元素。如果双端队列为空，返回 -1。
- getRear()：获得双端队列的最后一个元素。如果双端队列为空，返回 -1。
- isEmpty()：检查双端队列是否为空。
- isFull()：检查双端队列是否满了。

**关键点**：
- 循环数组实现
- 双端队列操作
- 边界条件处理

### 4. 设计一个支持增量操作的栈 (Medium)
**题目链接**: https://leetcode.cn/problems/design-a-stack-with-increment-operation/

请你设计一个支持下述操作的栈：
- CustomStack(int maxSize)：用 maxSize 初始化对象，maxSize 是栈中最多能容纳的元素数量。
- void push(int x)：如果栈还未增长到 maxSize ，就将 x 添加到栈顶。
- int pop()：返回栈顶的值，或栈为空时返回 -1 。
- void inc(int k, int val)：栈底的 k 个元素的值都增加 val 。如果栈中元素总数小于 k ，则栈中的所有元素都增加 val 。

**关键点**：
- 栈的基本操作
- 增量操作的优化
- 延迟更新技巧

## 学习要点总结

### 1. 构造和析构的重要性
- **RAII原则**：资源获取即初始化
- **异常安全**：确保异常情况下的资源正确释放
- **生命周期管理**：理解对象的创建和销毁时机

### 2. 拷贝语义 vs 移动语义
- **拷贝语义**：深拷贝，资源独立
- **移动语义**：资源转移，性能优化
- **何时使用**：根据需求选择合适的语义

### 3. 异常安全保证
- **基本保证**：不泄漏资源
- **强保证**：操作要么成功，要么恢复到原状态
- **不抛出保证**：操作不会抛出异常

### 4. 设计原则
- **单一职责**：每个类有明确的职责
- **异常安全**：设计异常安全的接口
- **性能考虑**：避免不必要的拷贝

## 扩展练习

1. 实现一个异常安全的字符串类
2. 设计一个线程安全的单例类
3. 实现一个支持RAII的文件管理类
4. 设计一个异常安全的容器类

## 学习检查

完成今天的学习后，你应该能够：
- [ ] 理解构造函数和析构函数的作用
- [ ] 掌握RAII原则的应用
- [ ] 会设计异常安全的类
- [ ] 理解拷贝构造和移动构造的区别
- [ ] 掌握初始化列表的使用
- [ ] 完成4道算法题

记住：良好的资源管理是C++编程的基础，RAII原则是C++的核心设计理念！
