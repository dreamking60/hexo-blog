---
title: C++ 学习计划 - 第三周：STL与高级特性
date: 2025-01-27 10:03:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
layout: page
menu_id: plan
permalink: /plan/week3/
---

# 第三周：STL与高级特性

本周将学习C++标准模板库（STL）和现代C++的高级特性，提升编程效率和代码质量。

## 本周学习目标
- 熟练使用STL容器和算法
- 掌握现代C++内存管理技术
- 学会使用Lambda表达式
- 理解移动语义和并发编程基础

## 每日计划

### [第15天：STL容器](/plan/week3/day15/) ✅
**学习目标：** 掌握STL容器的使用
- vector, list, deque - 序列容器的特点和使用
- set, multiset, map, multimap - 关联容器的应用
- stack, queue, priority_queue - 容器适配器
- 容器的选择原则和性能对比
- 迭代器的使用和类型
- **参考资料：** [STL容器 - cppreference.com](https://en.cppreference.com/w/cpp/container)

### [第16天：STL算法](/plan/week3/day16/) ✅
**学习目标：** 掌握STL算法的使用
- 查找算法（find, find_if, binary_search）
- 排序算法（sort, stable_sort, partial_sort）
- 修改算法（transform, replace, remove）
- 数值算法（accumulate, inner_product）
- 自定义比较器和Lambda表达式
- **参考资料：** [STL算法 - cppreference.com](https://en.cppreference.com/w/cpp/algorithm)

### [第17天：智能指针](/plan/week3/day17/) ✅
**学习目标：** 掌握现代C++的内存管理
- unique_ptr的使用 - 独占所有权智能指针
- shared_ptr的使用 - 共享所有权智能指针
- weak_ptr的使用 - 弱引用智能指针
- make_unique和make_shared - 推荐的创建方式
- 循环引用问题和解决方案
- **参考资料：** [智能指针 - cppreference.com](https://en.cppreference.com/w/cpp/memory)

### [第18天：Lambda表达式](/plan/week3/day18/) ✅
**学习目标：** 掌握现代C++的Lambda表达式
- Lambda表达式的语法和基本使用
- 捕获列表 - 值捕获、引用捕获、混合捕获
- 参数列表与返回类型
- 泛型Lambda（C++14）
- Lambda与STL的结合使用
- **参考资料：** [Lambda表达式 - cppreference.com](https://en.cppreference.com/w/cpp/language/lambda)

### [第19天：移动语义](/plan/week3/day19/) ✅
**学习目标：** 掌握C++11的移动语义
- 左值与右值的概念和区别
- 移动构造函数与移动赋值运算符
- std::move的使用和原理
- 完美转发（Perfect Forwarding）
- 移动语义的性能优势
- **参考资料：** [移动语义 - cppreference.com](https://en.cppreference.com/w/cpp/language/move_constructor)

### [第20天：并发编程基础](/plan/week3/day20/) ✅
**学习目标：** 掌握C++11的并发编程
- std::thread的使用 - 线程创建和管理
- 线程同步（mutex, condition_variable）
- 原子操作 - std::atomic的使用
- 线程安全编程技巧
- 异步编程（async, future, promise）
- **参考资料：** [C++并发编程 - cppreference.com](https://en.cppreference.com/w/cpp/thread)

### [第21天：文件操作与IO](/plan/week3/day21/) ✅
**学习目标：** 掌握C++的文件操作
- 文件流（ifstream, ofstream, fstream）
- 文本文件与二进制文件的处理
- 文件定位和随机访问
- 错误处理和异常安全
- 字符串流（stringstream）的使用
- **参考资料：** [C++ IO库 - cppreference.com](https://en.cppreference.com/w/cpp/io)

## 本周总结
完成第三周的学习后，你应该能够：
1. 熟练使用STL提高开发效率
2. 编写内存安全的现代C++代码
3. 使用Lambda表达式简化代码
4. 理解并发编程的基本概念

## 下周预告
第四周我们将学习高级主题和进行项目实战，包括设计模式、性能优化等。

[返回主页](/plan/) | [上一周：面向对象编程](/plan/week2/) | [下一周：高级主题与实战](/plan/week4/)
