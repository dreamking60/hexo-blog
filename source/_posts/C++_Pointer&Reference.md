---
title: C++ Pointer & Reference
date: 2025-09-02 00:30:00
categories: Cpp
tags:
    - C++
    - Pointer
    - Reference
---
# C++ Pointer & Reference
C++中指针和引用的区别是一个经典且重要的面试问题。让我详细解释它们的区别：

## 1. 定义和初始化

### 指针
```cpp
int x = 10;
int* ptr;        // 可以声明时不初始化
ptr = &x;        // 后续赋值
int* ptr2 = &x;  // 声明时初始化
```

### 引用
```cpp
int x = 10;
int& ref = x;    // 必须在声明时初始化
// int& ref;     // 错误！引用必须初始化
```

## 2. 重新赋值

### 指针
```cpp
int x = 10, y = 20;
int* ptr = &x;
cout << *ptr << endl;  // 输出：10

ptr = &y;              // 可以指向另一个变量
cout << *ptr << endl;  // 输出：20
```

### 引用
```cpp
int x = 10, y = 20;
int& ref = x;
cout << ref << endl;   // 输出：10

ref = y;               // 这不是重新绑定！这是赋值操作
cout << ref << endl;   // 输出：20
cout << x << endl;     // 输出：20（x的值被改变了）
```

## 3. 空值和有效性

### 指针
```cpp
int* ptr = nullptr;    // 指针可以为空
if (ptr != nullptr) {  // 需要检查空指针
    cout << *ptr << endl;
}

int* ptr2;             // 野指针，未初始化
// cout << *ptr2;      // 危险！未定义行为
```

### 引用
```cpp
// int& ref = nullptr; // 错误！引用不能为空
// int& ref;           // 错误！引用必须绑定到对象
int x = 10;
int& ref = x;          // 引用总是有效的
cout << ref << endl;   // 安全，不需要检查
```

## 4. 内存占用

### 指针
```cpp
int x = 10;
int* ptr = &x;

cout << sizeof(ptr) << endl;    // 通常是8字节（64位系统）
cout << sizeof(x) << endl;      // 4字节
```

### 引用
```cpp
int x = 10;
int& ref = x;

cout << sizeof(ref) << endl;    // 4字节（与原变量相同）
cout << sizeof(x) << endl;      // 4字节
// 引用本身通常不占用额外内存（编译器优化）
```

## 5. 算术运算

### 指针
```cpp
int arr[] = {1, 2, 3, 4, 5};
int* ptr = arr;

cout << *ptr << endl;      // 输出：1
cout << *(ptr + 1) << endl; // 输出：2
cout << *(ptr + 2) << endl; // 输出：3

ptr++;                     // 指针算术
cout << *ptr << endl;      // 输出：2
```

### 引用
```cpp
int arr[] = {1, 2, 3, 4, 5};
int& ref = arr[0];

cout << ref << endl;       // 输出：1
// ref++;                  // 这是对值的递增，不是引用算术
// cout << ref << endl;    // 会输出：2（arr[0]变成了2）

// 引用不支持算术运算来"移动"到其他对象
```

## 6. 作为函数参数

### 指针参数
```cpp
void func1(int* ptr) {
    if (ptr != nullptr) {  // 需要检查
        *ptr = 100;
    }
}

void func2(int* ptr) {
    ptr = new int(200);    // 只改变局部指针，不影响外部
}

int main() {
    int x = 10;
    int* p = &x;
    
    func1(p);              // x变成100
    func2(p);              // p仍然指向x，没有内存泄漏（这次）
    
    func1(nullptr);        // 安全，函数内部检查了空指针
}
```

### 引用参数
```cpp
void func1(int& ref) {
    ref = 100;             // 直接修改，无需解引用
}

// void func2(int& ref) {
//     ref = ???;          // 无法让引用绑定到其他对象
// }

int main() {
    int x = 10;
    
    func1(x);              // x变成100，语法简洁
    // func1(nullptr);     // 错误！不能传递空值
}
```

## 7. 返回值使用

### 返回指针
```cpp
int* createInt() {
    return new int(42);    // 返回动态分配的内存
}

int* dangerousFunc() {
    int x = 10;
    return &x;             // 危险！返回局部变量地址
}
```

### 返回引用
```cpp
int& getElement(vector<int>& vec, int index) {
    return vec[index];     // 返回容器元素的引用
}

int& dangerousFunc() {
    int x = 10;
    return x;              // 危险！返回局部变量引用
}

int main() {
    vector<int> vec = {1, 2, 3};
    getElement(vec, 1) = 100;  // 可以直接赋值
    cout << vec[1] << endl;    // 输出：100
}
```

## 8. 总结对比表

| 特性 | 指针 | 引用 |
|------|------|------|
| 初始化 | 可选 | 必须 |
| 重新赋值 | 可以 | 不可以 |
| 空值 | 可以 | 不可以 |
| 算术运算 | 支持 | 不支持 |
| 内存占用 | 占用额外空间 | 通常不占用 |
| 语法复杂度 | 需要 * 和 & | 简洁 |
| 安全性 | 需要检查 | 相对安全 |
| 多级间接 | 支持（指针的指针） | 不支持 |

## 使用建议

- **优先使用引用**：当你需要别名时，引用更安全、语法更简洁
- **使用指针**：当需要可选性（可为空）、重新赋值、或指针算术时
- **函数参数**：引用用于必须传递有效对象的情况，指针用于可选参数
- **动态内存**：必须使用指针（配合智能指针更好）