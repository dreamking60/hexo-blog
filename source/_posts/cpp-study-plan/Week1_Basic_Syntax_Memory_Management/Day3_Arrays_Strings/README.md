---
title: C++ 学习计划 - 第3天:数组与字符串
date: 2025-09-16 10:13:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week1
    - Day3
layout: page
menu_id: plan
permalink: /plan/week1/day3/
---

# 第3天：数组与字符串

## 学习目标
掌握数组和字符串的使用，理解内存布局和访问方式。

## 学习内容

### 1. 数组基础
- 一维数组和多维数组
- 数组的初始化与访问
- 数组的内存布局
- 数组越界问题

### 2. 字符串处理
- 字符数组与字符串
- C风格字符串函数
- string类的使用
- 字符串操作方法

### 3. 数组作为函数参数
- 数组参数的传递方式
- 数组大小的传递
- 多维数组参数

## 重点概念

### 数组初始化
```cpp
// 静态初始化
int arr1[5] = {1, 2, 3, 4, 5};
int arr2[] = {1, 2, 3, 4, 5};  // 自动推导大小
int arr3[5] = {1, 2};          // 部分初始化，其余为0

// 二维数组
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
```

### 字符串操作
```cpp
// C风格字符串
char str1[] = "Hello";
char str2[10] = "World";

// 字符串函数
int len = strlen(str1);
strcpy(str2, str1);
strcat(str1, str2);
int cmp = strcmp(str1, str2);

// C++字符串
string s1 = "Hello";
string s2 = "World";
string s3 = s1 + " " + s2;
cout << s3.length() << endl;
```

### 数组作为参数
```cpp
// 方式1：数组参数（退化为指针）
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

// 方式2：指针参数
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

// 方式3：引用参数（固定大小）
void printArray(int (&arr)[5]) {
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
}
```

## 实践练习

### 练习1：数组操作
实现数组的基本操作，包括查找、排序、反转等。

### 练习2：字符串处理
实现字符串的基本操作，如反转、查找子串、替换等。

### 练习3：矩阵运算
实现二维数组的矩阵加法、乘法等运算。

## 常见错误与注意事项

1. **数组越界**：访问超出数组范围的元素
2. **未初始化数组**：使用未初始化的数组元素
3. **字符串缓冲区溢出**：写入超过数组大小的字符
4. **数组参数退化**：数组作为参数时退化为指针

## 学习检查点

- [ ] 理解数组的内存布局和访问方式
- [ ] 掌握多维数组的使用方法
- [ ] 熟练使用C风格字符串函数
- [ ] 理解数组作为函数参数的机制
- [ ] 能够避免常见的数组相关错误

[返回第一周](/plan/week1/) | [上一天：函数与作用域](/plan/week1/day2/) | [下一天：指针基础](/plan/week1/day4/)
