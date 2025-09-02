---
title: "C++中的const详解"
date: 2025-09-02 01:00:00
tags:
    - C++
    - const
    - Pointer
    - Reference
---

# C++中的const详解
## 1. 常量 (const)

### 基本常量
```cpp
const int x = 10;        // x是常量，不能修改
// x = 20;               // 错误！不能修改常量
cout << x << endl;       // 正确，可以读取
```

### 常量引用
```cpp
int y = 20;
const int& ref = y;      // 常量引用，不能通过ref修改y
// ref = 30;             // 错误！不能通过常量引用修改值
cout << ref << endl;     // 正确，可以读取

y = 30;                  // 正确，可以直接修改y
cout << ref << endl;     // 输出30，ref看到的是修改后的值
```

## 2. 指向常量的指针 (pointer to const)

```cpp
const int x = 10;
const int y = 20;

const int* ptr = &x;     // 指向常量的指针
cout << *ptr << endl;    // 正确，可以读取

// *ptr = 30;            // 错误！不能通过指针修改常量
ptr = &y;                // 正确！指针本身可以重新赋值指向其他常量
cout << *ptr << endl;    // 输出20

// 也可以指向非常量，但仍不能修改
int z = 40;
ptr = &z;                // 正确
// *ptr = 50;            // 错误！即使z不是常量，也不能通过const指针修改
z = 50;                  // 正确，可以直接修改z
cout << *ptr << endl;    // 输出50
```

## 3. 常量指针 (const pointer)

```cpp
int x = 10;
int y = 20;

int* const ptr = &x;     // 常量指针，指针本身是常量
cout << *ptr << endl;    // 正确，可以读取

*ptr = 30;               // 正确！可以修改指向的值
cout << x << endl;       // 输出30，x被修改了

// ptr = &y;             // 错误！常量指针不能重新赋值
```

## 4. 指向常量的常量指针 (const pointer to const)

```cpp
const int x = 10;
const int y = 20;

const int* const ptr = &x;  // 指向常量的常量指针
cout << *ptr << endl;       // 正确，可以读取

// *ptr = 30;               // 错误！不能修改指向的常量
// ptr = &y;                // 错误！指针本身也是常量
```

## 5. 记忆方法和语法规则

### 从右往左读法
```cpp
const int* ptr;          // ptr is a pointer to const int
int* const ptr;          // ptr is a const pointer to int  
const int* const ptr;    // ptr is a const pointer to const int
```

### 另一种写法（等价）
```cpp
int const* ptr;          // 等价于 const int* ptr
int* const ptr;          // 常量指针
int const* const ptr;    // 等价于 const int* const ptr
```

## 6. 实际应用示例

### 函数参数中的使用
```cpp
// 1. 传递指向常量的指针 - 保护数据不被修改
void printArray(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";  // 可以读取
        // arr[i] = 0;          // 错误！不能修改
    }
    // arr = nullptr;          // 正确，可以修改指针本身（但没意义）
}

// 2. 传递常量指针 - 保证指针不会改变指向
void processBuffer(int* const buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] *= 2;         // 正确，可以修改数据
    }
    // buffer = new int[100];   // 错误！不能改变指针指向
}

// 3. 最严格的保护
void readOnlyAccess(const int* const data, int size) {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " "; // 只能读取
        // data[i] = 0;         // 错误！不能修改数据
    }
    // data = nullptr;         // 错误！不能修改指针
}
```

### 类中的常量成员
```cpp
class MyClass {
private:
    const int constantMember;           // 常量成员
    int* const constantPointer;         // 常量指针成员
    
public:
    // 必须在初始化列表中初始化常量成员
    MyClass(int value, int* ptr) 
        : constantMember(value), constantPointer(ptr) {
        // constantMember = value;      // 错误！不能在构造函数体中赋值
    }
    
    void show() const {                 // 常量成员函数
        cout << constantMember << endl; // 可以访问
        cout << *constantPointer << endl;
        // constantMember = 10;         // 错误！常量成员函数不能修改成员
    }
    
    void modify() {
        // constantMember = 20;         // 错误！常量成员永远不能修改
        *constantPointer = 30;          // 正确！可以修改指向的值
        // constantPointer = nullptr;   // 错误！常量指针不能重新赋值
    }
};
```

## 7. 常见错误和注意事项

### 错误示例
```cpp
// 1. 试图修改常量
const int x = 10;
// x = 20;                  // 编译错误

// 2. 常量指针的初始化问题
// int* const ptr;          // 错误！常量指针必须初始化

// 3. 类型不匹配
int x = 10;
// const int* ptr = &x;     // 正确
// int* ptr2 = ptr;         // 错误！不能将const int*赋值给int*

// 正确的做法需要const_cast（不推荐）
int* ptr3 = const_cast<int*>(ptr);  // 危险操作，移除const属性
```

### 最佳实践
```cpp
// 1. 尽可能使用const保护数据
void processData(const vector<int>& data) {  // 避免不必要的拷贝和修改
    // 处理数据...
}

// 2. 返回const引用避免修改
class Container {
    vector<int> data;
public:
    const int& at(size_t index) const {      // 常量版本
        return data[index];
    }
    
    int& at(size_t index) {                  // 非常量版本
        return data[index];
    }
};

// 3. 智能指针中的const
unique_ptr<const int> ptr1(new int(10));    // 指向常量的智能指针
const unique_ptr<int> ptr2(new int(20));    // 常量智能指针
const unique_ptr<const int> ptr3(new int(30)); // 最严格
```

## 8. 总结表格

| 声明 | 指针本身 | 指向的值 | 说明 |
|------|----------|----------|------|
| `int* ptr` | 可修改 | 可修改 | 普通指针 |
| `const int* ptr` | 可修改 | 不可修改 | 指向常量的指针 |
| `int* const ptr` | 不可修改 | 可修改 | 常量指针 |
| `const int* const ptr` | 不可修改 | 不可修改 | 指向常量的常量指针 |

理解这些概念对于编写安全、可维护的C++代码非常重要，它们帮助我们在编译时就发现潜在的错误。