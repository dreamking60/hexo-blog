---
title: C++ 学习计划 - 第三周第15天:STL容器
date: 2025-09-16 15:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
    - STL
    - Containers
layout: page
menu_id: plan
permalink: /plan/week3/day15/
---

# 第15天：STL容器

## 学习目标
掌握C++标准模板库中各种容器的使用，理解不同容器的特点、性能和使用场景。

## 核心知识点

### 1. 序列容器 (Sequence Containers)

#### vector - 动态数组
- **特点**：动态数组，支持随机访问
- **时间复杂度**：插入/删除末尾O(1)，中间O(n)，访问O(1)
- **使用场景**：需要随机访问，频繁在末尾操作
- **参考资料**：
  - [std::vector - cppreference.com](https://en.cppreference.com/w/cpp/container/vector)
  - [C++ vector容器详解 - 菜鸟教程](https://www.runoob.com/cplusplus/cpp-vector-container.html)

#### list - 双向链表
- **特点**：双向链表，不支持随机访问
- **时间复杂度**：插入/删除O(1)，访问O(n)
- **使用场景**：频繁在中间插入/删除，不需要随机访问
- **参考资料**：
  - [std::list - cppreference.com](https://en.cppreference.com/w/cpp/container/list)
  - [C++ list容器详解 - C语言中文网](http://c.biancheng.net/view/6892.html)

#### deque - 双端队列
- **特点**：双端队列，支持两端操作
- **时间复杂度**：两端插入/删除O(1)，中间O(n)，访问O(1)
- **使用场景**：需要两端操作，偶尔需要随机访问
- **参考资料**：
  - [std::deque - cppreference.com](https://en.cppreference.com/w/cpp/container/deque)
  - [C++ deque容器详解](https://blog.csdn.net/weixin_43914604/article/details/104827688)

### 2. 关联容器 (Associative Containers)

#### set - 有序集合
- **特点**：有序集合，元素唯一
- **时间复杂度**：插入/删除/查找O(log n)
- **实现**：红黑树
- **参考资料**：
  - [std::set - cppreference.com](https://en.cppreference.com/w/cpp/container/set)
  - [C++ set容器详解](https://blog.csdn.net/weixin_43914604/article/details/105263965)

#### map - 键值对映射
- **特点**：键值对映射，键唯一且有序
- **时间复杂度**：插入/删除/查找O(log n)
- **实现**：红黑树
- **参考资料**：
  - [std::map - cppreference.com](https://en.cppreference.com/w/cpp/container/map)
  - [C++ map容器详解](https://blog.csdn.net/weixin_43914604/article/details/105264618)

### 3. 容器适配器 (Container Adapters)

#### stack - 栈
- **特点**：后进先出(LIFO)
- **默认容器**：deque
- **使用场景**：需要栈操作，如表达式求值、括号匹配
- **参考资料**：
  - [std::stack - cppreference.com](https://en.cppreference.com/w/cpp/container/stack)
  - [C++ stack详解](https://blog.csdn.net/weixin_43914604/article/details/105265280)

#### queue - 队列
- **特点**：先进先出(FIFO)
- **默认容器**：deque
- **使用场景**：需要队列操作，如BFS、任务调度
- **参考资料**：
  - [std::queue - cppreference.com](https://en.cppreference.com/w/cpp/container/queue)
  - [C++ queue详解](https://blog.csdn.net/weixin_43914604/article/details/105265652)

#### priority_queue - 优先队列
- **特点**：优先队列，默认最大堆
- **默认容器**：vector
- **使用场景**：需要优先处理，如Dijkstra算法、任务调度
- **参考资料**：
  - [std::priority_queue - cppreference.com](https://en.cppreference.com/w/cpp/container/priority_queue)
  - [C++ priority_queue详解](https://blog.csdn.net/weixin_43914604/article/details/105266000)

### 4. 迭代器 (Iterators)

#### 迭代器类型
- **正向迭代器**：begin(), end()
- **反向迭代器**：rbegin(), rend()
- **常量迭代器**：cbegin(), cend()
- **参考资料**：
  - [C++ 迭代器详解 - cppreference.com](https://en.cppreference.com/w/cpp/iterator)
  - [C++ 迭代器使用指南](https://blog.csdn.net/weixin_43914604/article/details/104828000)

## 容器选择原则

### 1. 访问模式
- **随机访问**：vector, deque
- **顺序访问**：list, forward_list
- **键值访问**：map, unordered_map

### 2. 插入/删除位置
- **末尾**：vector, deque
- **中间**：list
- **任意位置**：set, map

### 3. 内存考虑
- **连续存储**：vector, array
- **非连续存储**：list, set, map

### 4. 性能要求
- **查找频繁**：set, map, unordered_set, unordered_map
- **插入频繁**：list, unordered_set, unordered_map

## 实用教程和文档

### 官方文档
- [C++ 容器库 - cppreference.com](https://en.cppreference.com/w/cpp/container)
- [STL容器详解 - Microsoft Docs](https://docs.microsoft.com/en-us/cpp/standard-library/stl-containers)

### 优质教程
- [C++ STL容器全面解析](https://blog.csdn.net/weixin_43914604/article/details/104826000)
- [STL容器使用指南 - 现代C++教程](https://changkun.de/modern-cpp/zh-cn/05-pointers/)
- [C++ STL容器性能对比分析](https://www.cnblogs.com/skyfsm/p/6934246.html)

### 实战案例
- [LeetCode中的STL容器应用](https://leetcode-cn.com/problemset/all/)
- [STL容器在实际项目中的应用](https://github.com/huihut/interview#stl)

## 今日练习

### 基础练习
1. 实现一个学生成绩管理系统，使用不同的容器存储学生信息
2. 编写一个表达式求值器，使用stack容器
3. 实现一个任务调度系统，使用priority_queue

### 算法题推荐
1. [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/) - 使用双向链表和哈希表
2. [LeetCode 295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) - 使用两个优先队列
3. [LeetCode 239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) - 使用双端队列
4. [LeetCode 380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) - 使用哈希表和动态数组

## 学习要点总结

1. **容器选择**：根据使用场景选择合适的容器
2. **性能考虑**：了解各容器的时间复杂度
3. **内存管理**：理解容器的内存分配策略
4. **迭代器**：掌握各种迭代器的使用
5. **实践应用**：通过实际项目加深理解

## 下一天预告
明天我们将学习STL算法，包括查找算法、排序算法、修改算法等，学会如何将算法与容器结合使用。

[返回第三周总览](/plan/week3/) | [下一天：STL算法](/plan/week3/day16/)
