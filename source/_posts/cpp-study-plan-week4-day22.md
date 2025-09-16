---
title: C++ 学习计划 - 第22天：设计模式
date: 2025-01-27 10:25:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week4
    - Day22
layout: page
menu_id: plan
permalink: /plan/week4/day22/
---

# 第22天：设计模式

## 学习目标
学习常用的设计模式，掌握面向对象设计的最佳实践，提高代码的可维护性和可扩展性。

## 学习资源链接

### 📚 官方文档和教程
- [Design Patterns Gang of Four](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612) - 设计模式经典教材
- [Refactoring Guru - Design Patterns](https://refactoring.guru/design-patterns) - 设计模式详细教程和示例
- [C++ Design Patterns](https://www.tutorialspoint.com/design_pattern/index.htm) - C++设计模式教程
- [Source Making - Design Patterns](https://sourcemaking.com/design_patterns) - 设计模式在线教程

### 🎥 视频教程
- [Design Patterns in C++](https://www.youtube.com/watch?v=v9ejT8FO-7I&list=PLrhzvIcii6GNjpARdnO4ueTUAVR9eMBpc) - C++设计模式系列视频
- [The Cherno - Singleton Pattern](https://www.youtube.com/watch?v=hUE_j6q0LTQ) - 单例模式详解
- [Design Patterns Explained](https://www.youtube.com/watch?v=NU_1StN5Tkk) - 设计模式概述

### 📖 深入阅读
- [Effective C++ - Item 4](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 确保对象被初始化
- [Modern C++ Design](https://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315) - 现代C++设计模式
- [Head First Design Patterns](https://www.amazon.com/Head-First-Design-Patterns-Brain-Friendly/dp/0596007124) - 设计模式入门书籍

## 学习内容

### 1. 单例模式 (Singleton Pattern)
- **概念**：确保一个类只有一个实例，并提供全局访问点
- **适用场景**：配置管理、日志系统、数据库连接池
- **实现方式**：
  - 懒汉式单例
  - 饿汉式单例
  - 线程安全的单例
- **现代C++实现**：使用std::call_once和std::once_flag

```cpp
// 线程安全的单例模式
class Singleton {
private:
    static std::once_flag flag;
    static std::unique_ptr<Singleton> instance;
    
    Singleton() = default;
    
public:
    static Singleton& getInstance() {
        std::call_once(flag, []() {
            instance = std::make_unique<Singleton>();
        });
        return *instance;
    }
    
    // 禁止拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```

### 2. 工厂模式 (Factory Pattern)
- **简单工厂模式**：通过工厂类创建对象
- **工厂方法模式**：定义创建对象的接口，子类决定实例化哪个类
- **抽象工厂模式**：提供创建相关对象家族的接口

```cpp
// 抽象产品
class Product {
public:
    virtual ~Product() = default;
    virtual void operation() = 0;
};

// 具体产品
class ConcreteProductA : public Product {
public:
    void operation() override {
        std::cout << "ConcreteProductA operation\n";
    }
};

// 工厂基类
class Factory {
public:
    virtual ~Factory() = default;
    virtual std::unique_ptr<Product> createProduct() = 0;
};

// 具体工厂
class ConcreteFactoryA : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ConcreteProductA>();
    }
};
```

### 3. 观察者模式 (Observer Pattern)
- **概念**：定义对象间的一种一对多依赖关系
- **组成**：主题(Subject)和观察者(Observer)
- **应用**：事件处理系统、MVC架构

```cpp
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;
    
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    void detach(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    void notify(const std::string& message) {
        for (auto* observer : observers) {
            observer->update(message);
        }
    }
};
```

### 4. 策略模式 (Strategy Pattern)
- **概念**：定义算法家族，分别封装起来，让它们之间可以互相替换
- **优点**：算法可以自由切换，避免使用多重条件判断
- **应用**：排序算法选择、支付方式选择

```cpp
// 策略接口
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

// 具体策略
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.begin(), data.end());
        std::cout << "Quick sort executed\n";
    }
};

// 上下文类
class SortContext {
private:
    std::unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(std::unique_ptr<SortStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    
    void executeSort(std::vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        }
    }
};
```

### 5. RAII模式 (Resource Acquisition Is Initialization)
- **概念**：资源获取即初始化
- **原理**：利用对象的构造和析构函数管理资源
- **应用**：智能指针、文件句柄、互斥锁

```cpp
// RAII文件管理类
class FileManager {
private:
    FILE* file;
    
public:
    explicit FileManager(const char* filename, const char* mode) {
        file = fopen(filename, mode);
        if (!file) {
            throw std::runtime_error("Failed to open file");
        }
    }
    
    ~FileManager() {
        if (file) {
            fclose(file);
        }
    }
    
    // 禁止拷贝，允许移动
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    FileManager(FileManager&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }
    
    FileManager& operator=(FileManager&& other) noexcept {
        if (this != &other) {
            if (file) fclose(file);
            file = other.file;
            other.file = nullptr;
        }
        return *this;
    }
    
    FILE* get() const { return file; }
};
```

## 实践练习

### 练习1：实现线程安全的日志系统
使用单例模式设计一个线程安全的日志系统：
- 支持不同日志级别（DEBUG, INFO, WARNING, ERROR）
- 支持输出到文件和控制台
- 线程安全

### 练习2：图形工厂系统
设计一个图形工厂系统：
- 抽象工厂创建不同类型的图形（圆形、矩形、三角形）
- 每种图形有不同的绘制方法
- 支持扩展新的图形类型

### 练习3：事件通知系统
实现一个基于观察者模式的事件通知系统：
- 支持多种事件类型
- 观察者可以订阅和取消订阅特定事件
- 事件发生时通知所有相关观察者

### 练习4：算法策略选择器
创建一个数据处理系统：
- 支持多种排序算法（快速排序、归并排序、堆排序）
- 可以根据数据特征动态选择最优算法
- 支持添加新的排序策略

## LeetCode相关题目

### 设计类题目
1. [LeetCode 146 - LRU Cache](https://leetcode.com/problems/lru-cache/) - 使用设计模式实现LRU缓存
2. [LeetCode 155 - Min Stack](https://leetcode.com/problems/min-stack/) - 栈的设计
3. [LeetCode 208 - Implement Trie](https://leetcode.com/problems/implement-trie-prefix-tree/) - 前缀树设计
4. [LeetCode 295 - Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) - 数据结构设计

### 系统设计题目
1. [LeetCode 348 - Design Tic-Tac-Toe](https://leetcode.com/problems/design-tic-tac-toe/) - 游戏设计
2. [LeetCode 362 - Design Hit Counter](https://leetcode.com/problems/design-hit-counter/) - 计数器设计
3. [LeetCode 380 - Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) - 数据结构设计

## 今日总结
通过学习设计模式，你应该掌握：
1. 常用设计模式的概念和实现
2. 如何选择合适的设计模式解决问题
3. RAII模式在C++中的重要性
4. 设计模式与现代C++特性的结合

## 明天预告
明天我们将学习C++性能优化技巧，包括编译器优化、内存优化和算法优化等内容。

[返回第四周](/plan/week4/) | [上一天：第21天](/plan/week3/day21/) | [下一天：第23天](/plan/week4/day23/)
