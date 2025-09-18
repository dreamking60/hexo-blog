---
title: C++ 学习计划 - 第三周第16天:STL算法
date: 2025-09-16 16:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
    - STL
    - Algorithms
layout: page
menu_id: plan
permalink: /plan/week3/day16/
---

# 第16天：STL算法

## 学习目标
掌握C++标准模板库中各种算法的使用，理解算法与容器的结合使用，学会自定义比较器和谓词。

## 核心知识点

### 1. 查找算法 (Search Algorithms)

#### find 系列
- **find**：查找第一个匹配的元素
- **find_if**：查找第一个满足条件的元素
- **find_if_not**：查找第一个不满足条件的元素
- **参考资料**：
  - [std::find - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/find)
  - [C++ find算法详解](https://blog.csdn.net/weixin_43914604/article/details/105270000)

#### binary_search 系列
- **binary_search**：二分查找（需要有序）
- **lower_bound**：查找第一个不小于目标值的位置
- **upper_bound**：查找第一个大于目标值的位置
- **equal_range**：查找等于目标值的范围
- **参考资料**：
  - [std::binary_search - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/binary_search)
  - [C++ 二分查找算法详解](https://www.cnblogs.com/grandyang/p/6854825.html)

### 2. 排序算法 (Sorting Algorithms)

#### sort 系列
- **sort**：快速排序（不稳定）
- **stable_sort**：稳定排序
- **partial_sort**：部分排序（前k个元素）
- **nth_element**：找到第n个元素
- **参考资料**：
  - [std::sort - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/sort)
  - [C++ 排序算法完全指南](https://blog.csdn.net/weixin_43914604/article/details/105271000)

#### 自定义比较器
- **Lambda表达式**：现代C++推荐方式
- **函数对象**：传统方式
- **函数指针**：C风格方式
- **参考资料**：
  - [C++ 自定义比较器详解](https://blog.csdn.net/weixin_43914604/article/details/105272000)
  - [Lambda表达式在STL中的应用](https://www.cnblogs.com/skyfsm/p/7050946.html)

### 3. 修改算法 (Modifying Algorithms)

#### transform
- **单容器转换**：将一个容器的元素转换后存储到另一个容器
- **双容器转换**：将两个容器的对应元素进行运算
- **参考资料**：
  - [std::transform - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/transform)
  - [C++ transform算法详解](https://blog.csdn.net/weixin_43914604/article/details/105273000)

#### replace 系列
- **replace**：替换所有匹配的元素
- **replace_if**：替换满足条件的元素
- **replace_copy**：复制并替换
- **参考资料**：
  - [std::replace - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/replace)

#### remove 系列
- **remove**：移除元素（不改变容器大小）
- **remove_if**：移除满足条件的元素
- **remove_copy**：复制并移除
- **参考资料**：
  - [std::remove - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/remove)
  - [remove-erase惯用法详解](https://www.cnblogs.com/skyfsm/p/7050947.html)

### 4. 数值算法 (Numeric Algorithms)

#### accumulate
- **基本求和**：计算容器元素的和
- **自定义操作**：使用自定义函数进行累积
- **参考资料**：
  - [std::accumulate - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/accumulate)
  - [C++ 数值算法详解](https://blog.csdn.net/weixin_43914604/article/details/105274000)

#### inner_product
- **内积计算**：计算两个容器的内积
- **自定义内积**：使用自定义运算符
- **参考资料**：
  - [std::inner_product - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/inner_product)

### 5. 集合算法 (Set Algorithms)

#### 集合运算
- **set_union**：并集
- **set_intersection**：交集
- **set_difference**：差集
- **set_symmetric_difference**：对称差集
- **参考资料**：
  - [C++ 集合算法详解](https://en.cppreference.com/w/cpp/algorithm/set_union)
  - [STL集合算法应用](https://blog.csdn.net/weixin_43914604/article/details/105275000)

### 6. 堆算法 (Heap Algorithms)

#### 堆操作
- **make_heap**：创建堆
- **push_heap**：添加元素到堆
- **pop_heap**：移除堆顶元素
- **sort_heap**：堆排序
- **参考资料**：
  - [std::make_heap - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/make_heap)
  - [C++ 堆算法详解](https://blog.csdn.net/weixin_43914604/article/details/105276000)

## 算法与容器的结合

### 迭代器适配器
- **back_inserter**：后插迭代器
- **front_inserter**：前插迭代器
- **inserter**：插入迭代器
- **参考资料**：
  - [C++ 迭代器适配器](https://en.cppreference.com/w/cpp/iterator/back_inserter)

### 算法复杂度分析
- **时间复杂度**：了解各算法的时间复杂度
- **空间复杂度**：理解算法的空间需求
- **参考资料**：
  - [STL算法复杂度分析](https://www.cnblogs.com/skyfsm/p/6934247.html)

## 实用教程和文档

### 官方文档
- [C++ 算法库 - cppreference.com](https://en.cppreference.com/w/cpp/algorithm)
- [STL算法详解 - Microsoft Docs](https://docs.microsoft.com/en-us/cpp/standard-library/algorithm-functions)

### 优质教程
- [C++ STL算法全面解析](https://blog.csdn.net/weixin_43914604/article/details/104830000)
- [STL算法使用指南](https://changkun.de/modern-cpp/zh-cn/05-pointers/)
- [现代C++中的STL算法](https://www.fluentcpp.com/STL/)

### 实战案例
- [STL算法在竞赛编程中的应用](https://oi-wiki.org/lang/csl/algorithm/)
- [实际项目中的STL算法使用](https://github.com/huihut/interview#算法)

## 今日练习

### 基础练习
1. 实现一个数据分析器，使用各种STL算法进行数据处理
2. 编写一个文本处理器，使用算法进行字符串操作
3. 实现一个排序和查找系统，比较不同算法的性能

### 算法题推荐
1. [LeetCode 56. Merge Intervals](https://leetcode.com/problems/merge-intervals/) - 使用排序和合并算法
2. [LeetCode 347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) - 使用排序和计数算法
3. [LeetCode 215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) - 使用部分排序算法
4. [LeetCode 49. Group Anagrams](https://leetcode.com/problems/group-anagrams/) - 使用排序和分组算法

## 学习要点总结

1. **算法分类**：查找、排序、修改、数值、集合、堆算法
2. **迭代器使用**：理解各种迭代器的适用范围
3. **自定义比较器**：掌握Lambda表达式和函数对象
4. **性能考虑**：了解各算法的时间复杂度
5. **组合使用**：多个算法的组合使用

## 下一天预告
明天我们将学习智能指针，包括unique_ptr、shared_ptr、weak_ptr等现代C++的内存管理技术。

[上一天：STL容器](/plan/week3/day15/) | [返回第三周总览](/plan/week3/) | [下一天：智能指针](/plan/week3/day17/)
