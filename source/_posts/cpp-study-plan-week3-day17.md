---
title: C++ 学习计划 - 第三周第17天：智能指针
date: 2025-09-16 17:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
    - Smart Pointers
    - RAII
layout: page
menu_id: plan
permalink: /plan/week3/day17/
---

# 第17天：智能指针

## 学习目标
掌握C++11引入的智能指针，理解现代C++的内存管理方式，学会使用RAII原则避免内存泄漏。

## 核心知识点

### 1. 智能指针概述

#### 为什么需要智能指针？
- **避免内存泄漏**：自动释放内存
- **异常安全**：即使发生异常也能正确释放资源
- **简化代码**：减少手动内存管理
- **避免悬空指针**：防止访问已释放的内存

#### RAII原则
- **Resource Acquisition Is Initialization**：资源获取即初始化
- **自动管理资源生命周期**
- **参考资料**：
  - [RAII - cppreference.com](https://en.cppreference.com/w/cpp/language/raii)
  - [RAII详解 - 现代C++教程](https://changkun.de/modern-cpp/zh-cn/05-pointers/#5-1-raii-%E4%B8%8E%E5%BC%95%E7%94%A8%E8%AE%A1%E6%95%B0)

### 2. unique_ptr

#### 特点
- **独占所有权**：同一时间只能有一个unique_ptr拥有对象
- **移动语义**：支持移动，不支持复制
- **零开销**：与原始指针性能相同

#### 基本使用
```cpp
// 创建unique_ptr
std::unique_ptr<int> ptr = std::make_unique<int>(42);

// 移动所有权
std::unique_ptr<int> ptr2 = std::move(ptr);

// 自定义删除器
auto deleter = [](int* p) { delete p; };
std::unique_ptr<int, decltype(deleter)> ptr3(new int(42), deleter);
```

#### 参考资料
- [std::unique_ptr - cppreference.com](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [unique_ptr详解 - 现代C++教程](https://changkun.de/modern-cpp/zh-cn/05-pointers/#5-2-std-shared-ptr)
- [C++ unique_ptr使用指南](https://blog.csdn.net/weixin_43914604/article/details/105280000)

### 3. shared_ptr

#### 特点
- **共享所有权**：多个shared_ptr可以共享同一个对象
- **引用计数**：自动管理引用计数
- **线程安全**：引用计数操作是线程安全的

#### 基本使用
```cpp
// 创建shared_ptr
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);

// 复制shared_ptr（增加引用计数）
std::shared_ptr<int> ptr2 = ptr1;

// 检查引用计数
std::cout << ptr1.use_count() << std::endl;
```

#### 循环引用问题
- **问题描述**：两个对象相互持有shared_ptr会导致内存泄漏
- **解决方案**：使用weak_ptr打破循环引用

#### 参考资料
- [std::shared_ptr - cppreference.com](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [shared_ptr详解 - 现代C++教程](https://changkun.de/modern-cpp/zh-cn/05-pointers/#5-2-std-shared-ptr)
- [C++ shared_ptr使用指南](https://blog.csdn.net/weixin_43914604/article/details/105281000)

### 4. weak_ptr

#### 特点
- **弱引用**：不影响对象的生命周期
- **解决循环引用**：打破shared_ptr的循环引用
- **安全访问**：通过lock()方法安全访问对象

#### 基本使用
```cpp
std::shared_ptr<int> shared = std::make_shared<int>(42);
std::weak_ptr<int> weak = shared;

// 检查是否过期
if (!weak.expired()) {
    // 安全访问
    if (auto locked = weak.lock()) {
        std::cout << *locked << std::endl;
    }
}
```

#### 参考资料
- [std::weak_ptr - cppreference.com](https://en.cppreference.com/w/cpp/memory/weak_ptr)
- [weak_ptr详解 - 现代C++教程](https://changkun.de/modern-cpp/zh-cn/05-pointers/#5-3-std-weak-ptr)
- [C++ weak_ptr使用指南](https://blog.csdn.net/weixin_43914604/article/details/105282000)

### 5. make_unique 和 make_shared

#### make_unique (C++14)
- **推荐使用**：比new + unique_ptr更安全
- **异常安全**：避免内存泄漏
- **简洁语法**：减少代码重复

#### make_shared
- **性能优势**：一次分配内存（对象+控制块）
- **异常安全**：避免内存泄漏
- **推荐使用**：优于new + shared_ptr

#### 参考资料
- [std::make_unique - cppreference.com](https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)
- [std::make_shared - cppreference.com](https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared)
- [make_unique vs make_shared详解](https://www.fluentcpp.com/2017/01/16/make_unique-vs-the-new-operator/)

### 6. 智能指针与容器

#### 存储智能指针
```cpp
// 存储unique_ptr
std::vector<std::unique_ptr<Base>> vec;
vec.push_back(std::make_unique<Derived>());

// 存储shared_ptr
std::vector<std::shared_ptr<Base>> sharedVec;
sharedVec.push_back(std::make_shared<Derived>());
```

#### 多态支持
- **基类指针**：智能指针支持多态
- **虚析构函数**：确保正确析构派生类对象

### 7. 智能指针最佳实践

#### 选择原则
1. **默认使用unique_ptr**：大多数情况下的最佳选择
2. **需要共享时使用shared_ptr**：多个所有者的情况
3. **打破循环引用使用weak_ptr**：观察者模式等场景

#### 性能考虑
- **unique_ptr**：零开销，与原始指针性能相同
- **shared_ptr**：有引用计数开销，但通常可接受
- **make_shared**：比new + shared_ptr更高效

#### 参考资料
- [C++ 智能指针最佳实践](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/)
- [现代C++内存管理指南](https://www.fluentcpp.com/2017/08/22/smart-developers-use-smart-pointers-smart-pointers-basics/)

## 实用教程和文档

### 官方文档
- [C++ 内存管理库 - cppreference.com](https://en.cppreference.com/w/cpp/memory)
- [智能指针详解 - Microsoft Docs](https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp)

### 优质教程
- [现代C++智能指针完全指南](https://changkun.de/modern-cpp/zh-cn/05-pointers/)
- [C++ 智能指针详解](https://blog.csdn.net/weixin_43914604/article/details/104835000)
- [智能指针在实际项目中的应用](https://www.fluentcpp.com/2017/08/22/smart-developers-use-smart-pointers-smart-pointers-basics/)

### 设计模式与智能指针
- [RAII与智能指针](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization)
- [观察者模式与weak_ptr](https://www.codeproject.com/Articles/328552/Understanding-Weak-References)

## 今日练习

### 基础练习
1. 实现一个资源管理类，使用智能指针管理资源
2. 编写一个观察者模式的实现，使用weak_ptr避免循环引用
3. 实现一个树结构，使用智能指针管理节点

### 算法题推荐
1. [LeetCode 138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) - 使用智能指针管理链表节点
2. [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/) - 使用智能指针实现LRU缓存
3. [LeetCode 208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) - 使用智能指针实现字典树
4. [LeetCode 341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/) - 使用智能指针实现迭代器

## 学习要点总结

1. **RAII原则**：资源获取即初始化，自动管理资源生命周期
2. **所有权语义**：unique_ptr独占，shared_ptr共享，weak_ptr弱引用
3. **循环引用**：使用weak_ptr避免循环引用导致的内存泄漏
4. **异常安全**：智能指针确保异常情况下也能正确释放资源
5. **性能考虑**：make_shared比new + shared_ptr更高效

## 下一天预告
明天我们将学习Lambda表达式，包括捕获列表、参数列表、返回类型等现代C++的函数式编程特性。

[上一天：STL算法](/plan/week3/day16/) | [返回第三周总览](/plan/week3/) | [下一天：Lambda表达式](/plan/week3/day18/)
