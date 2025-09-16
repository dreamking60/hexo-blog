# 第6天：动态内存分配

## 学习目标
掌握动态内存的分配与释放，理解内存泄漏的预防，学会使用现代C++的内存管理技术。

## 学习内容

### 1. 动态内存分配基础
- new和delete操作符
- new[]和delete[]操作符
- 动态内存的生命周期
- 内存分配失败处理
- 内存对齐

### 2. 内存泄漏与野指针
- 内存泄漏的原因和危害
- 野指针的产生和避免
- 内存泄漏检测工具
- 内存泄漏的预防措施
- 异常安全的内存管理

### 3. 动态数组
- 动态一维数组
- 动态多维数组
- 动态数组的初始化
- 动态数组的释放
- 动态数组的性能考虑

### 4. 动态对象
- 动态创建对象
- 动态对象的构造和析构
- 动态对象的数组
- 动态对象的生命周期管理
- 动态对象的异常安全

### 5. 现代C++内存管理
- 智能指针简介
- RAII原则
- 移动语义与内存管理
- 内存池技术
- 自定义内存分配器

## 重点概念

### 基本动态内存操作
```cpp
// 分配单个变量
int* ptr = new int(42);
cout << "动态分配的值: " << *ptr << endl;
delete ptr;  // 释放内存
ptr = nullptr;  // 避免野指针

// 分配数组
int size = 5;
int* arr = new int[size];
for (int i = 0; i < size; i++) {
    arr[i] = i * i;
}
delete[] arr;  // 释放数组内存
arr = nullptr;
```

### 动态内存分配失败处理
```cpp
// 检查分配是否成功
int* ptr = new(std::nothrow) int(42);
if (ptr == nullptr) {
    cout << "内存分配失败" << endl;
    return;
}

// 使用try-catch处理异常
try {
    int* ptr = new int(42);
    // 使用ptr
    delete ptr;
} catch (const std::bad_alloc& e) {
    cout << "内存分配失败: " << e.what() << endl;
}
```

### 动态多维数组
```cpp
// 动态二维数组
int rows = 3, cols = 4;
int** matrix = new int*[rows];
for (int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
}

// 初始化
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = i * cols + j;
    }
}

// 释放内存
for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
}
delete[] matrix;
```

### 动态对象管理
```cpp
class MyClass {
private:
    int* data;
    size_t size;
public:
    MyClass(size_t s) : size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    ~MyClass() {
        delete[] data;
    }
    
    // 拷贝构造函数
    MyClass(const MyClass& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // 赋值操作符
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
};
```

## 内存泄漏预防

### 1. RAII原则
```cpp
class ResourceManager {
private:
    int* resource;
public:
    ResourceManager(size_t size) : resource(new int[size]) {}
    
    ~ResourceManager() {
        delete[] resource;
    }
    
    // 禁止拷贝
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // 允许移动
    ResourceManager(ResourceManager&& other) noexcept 
        : resource(other.resource) {
        other.resource = nullptr;
    }
    
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete[] resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
};
```

### 2. 异常安全的内存管理
```cpp
class SafeArray {
private:
    int* data;
    size_t size;
public:
    SafeArray(size_t s) : size(s) {
        data = new int[size];
        // 如果这里抛出异常，析构函数不会被调用
        // 但构造函数会抛出异常，所以不会造成内存泄漏
    }
    
    ~SafeArray() {
        delete[] data;
    }
    
    // 异常安全的赋值
    SafeArray& operator=(const SafeArray& other) {
        if (this != &other) {
            int* newData = new int[other.size];
            for (size_t i = 0; i < other.size; i++) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }
};
```

### 3. 智能指针简介
```cpp
#include <memory>

// 使用unique_ptr
std::unique_ptr<int> ptr = std::make_unique<int>(42);
// 自动释放内存，无需手动delete

// 使用shared_ptr
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = ptr1;  // 共享所有权
// 当最后一个shared_ptr销毁时，内存自动释放

// 使用weak_ptr
std::weak_ptr<int> weakPtr = ptr1;
// 不增加引用计数，避免循环引用
```

## 实践练习

### 练习1：基本动态内存操作
实现动态内存的分配、使用和释放。

### 练习2：动态数组管理
实现动态数组的创建、操作和释放。

### 练习3：动态对象管理
实现动态对象的创建、使用和释放。

### 练习4：内存泄漏检测
实现内存泄漏的检测和预防。

## 常见错误与注意事项

1. **内存泄漏**：分配内存后忘记释放
2. **重复释放**：对同一块内存释放多次
3. **野指针**：释放内存后继续使用指针
4. **内存越界**：访问超出分配范围的内存
5. **异常安全**：异常发生时内存没有正确释放

## 最佳实践

1. **使用RAII**：资源获取即初始化
2. **使用智能指针**：优先使用智能指针而不是裸指针
3. **异常安全**：确保异常安全的内存管理
4. **及时释放**：使用完后立即释放内存
5. **避免裸指针**：尽量避免使用裸指针管理内存

## 学习检查点

- [ ] 掌握new和delete的基本用法
- [ ] 理解内存泄漏的原因和危害
- [ ] 能够正确管理动态内存
- [ ] 了解RAII原则
- [ ] 掌握异常安全的内存管理
- [ ] 了解现代C++的内存管理技术

## 扩展阅读

- C++ Primer 第12章：动态内存
- Effective C++ 条款13-17：资源管理
- 了解智能指针的详细用法
- 学习内存池和自定义分配器
