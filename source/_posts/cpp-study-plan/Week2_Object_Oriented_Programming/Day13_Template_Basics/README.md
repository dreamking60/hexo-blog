# 第13天：模板基础

## 学习目标
掌握C++模板编程的基本概念，理解函数模板和类模板的使用，学会模板特化和实例化，了解泛型编程思想。

## 学习内容

### 1. 函数模板
函数模板允许编写与类型无关的代码。

```cpp
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

### 2. 类模板
类模板允许创建通用的类。

```cpp
template<typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    void push(const T& element);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;
};
```

## 实践练习

### 练习1：通用栈类模板
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    // 压入元素
    void push(const T& element) {
        elements.push_back(element);
    }
    
    // 弹出元素
    void pop() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        elements.pop_back();
    }
    
    // 获取栈顶元素
    T& top() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    const T& top() const {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    // 检查是否为空
    bool empty() const {
        return elements.empty();
    }
    
    // 获取大小
    size_t size() const {
        return elements.size();
    }
    
    // 显示所有元素
    void display() const {
        cout << "Stack contents: ";
        for (const auto& element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }
};
```

### 练习2：通用数组类模板
```cpp
template<typename T, size_t N>
class Array {
private:
    T data[N];
    
public:
    // 访问元素
    T& operator[](size_t index) {
        if (index >= N) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= N) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 获取大小
    constexpr size_t size() const {
        return N;
    }
    
    // 填充数组
    void fill(const T& value) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = value;
        }
    }
    
    // 显示数组
    void display() const {
        cout << "Array contents: ";
        for (size_t i = 0; i < N; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};
```

## 算法题练习

### 1. 合并K个升序链表 (Hard)
**题目链接**: https://leetcode.cn/problems/merge-k-sorted-lists/

### 2. 数组中的第K个最大元素 (Medium)
**题目链接**: https://leetcode.cn/problems/kth-largest-element-in-an-array/

### 3. 前K个高频元素 (Medium)
**题目链接**: https://leetcode.cn/problems/top-k-frequent-elements/

### 4. 最接近原点的K个点 (Medium)
**题目链接**: https://leetcode.cn/problems/k-closest-points-to-origin/

## 学习要点总结

### 1. 模板的基本概念
- 泛型编程思想
- 模板参数推导
- 模板实例化

### 2. 模板特化
- 全特化
- 偏特化
- 特化的使用场景

### 3. 模板元编程
- 编译期计算
- 类型推导
- SFINAE原则

记住：模板是C++强大的特性，但要注意编译时间和代码膨胀的问题！
