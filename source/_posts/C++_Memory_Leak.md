---
title: C++ Memory Leak
date: 2025-09-01 17:15:00
categories: Cpp
tags:
    - C++
    - Memory Leak
    - Debugging
---

# C++ Memory Leak
## C++内存泄漏的类型
C++内存泄漏主要指程序运行过程中分配的内存为能正确释放，导致系统资源浪费。常见的内存泄露类型如下：
### Heap Memroy Leak
- 原因：使用new分配的对象或malloc分配的内存未被delete或free释放。
- example:
```cpp
void func() {
    int* arr = new int[100]; // 分配内存
    // 忘记释放内存
}
```
### Array Memory Leak
- 原因：使用new[]分配的数组未被delete[]释放。
- example:
```cpp
void func() {
    int* arr = new int[100];
    delete arr; // Error: Should use delete[]
}
```

### Smart Pointer Reference Cycle
- 原因：shared_ptr之间相互引用，导致引用计数永远不为零，内存无法释放。
- example:
```cpp
struct A;
struct B;
struct A {
    std::shared_ptr<B> b_ptr;
};
struct B {
    std::shared_ptr<A> a_ptr;
};
void func() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a; // Reference cycle
}
```
- 解决方法：使用weak_ptr打破循环引用。
### 资源泄漏（文件、网络、线程）
- 原因：打开的文件、网络连接、线程等资源未被正确关闭或释放。
- example:
    ```cpp
        void func() {
            FILE* file = fopen("data.txt", "r");
            // 忘记关闭文件
        }
    ```
- Solution: 使用RAII封装资源管理，确保资源在对象销毁时自动释放。 (RAII: Resource Acquisition Is Initialization)
    ```cpp
        void func() {
            std::ifstream file("data.txt"); // automatically closed when going out of scope
        }
    ```
### 线程资源泄漏
- 原因：创建的线程未被正确join或detach，导致线程资源未释放。
- example:
```cpp
void threadFunc() {
    // Thread work
}
void func() {
    std::thread t(threadFunc);
    // 忘记join或detach
}
```

## 析构函数是否需要被声明为虚函数
> 如果一个类既不继承自其他类，也不是子类，内部也没有虚函数，那么它的析构函数不需要声明为虚函数。

### 虚析构函数
析构函数只有在类作为基类被继承并通过基类指针删除派生类对象时，才需要声明为virtual。
- example:
```cpp
class Base {
public:
    virtual ~Base() { // Virtual destructor
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor" << std::endl;
    }
};

void func() {
    Base* obj = new Derived();
    delete obj; // Correctly calls Derived's destructor followed by Base's destructor
}
```
- Why?
- 如果基类的析构函数不是虚函数，通过基类指针删除派生类对象时，只会调用基类的析构函数，导致派生类的资源未被释放，造成内存泄漏。
- 解决方法：将基类的析构函数声明为虚函数，确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数。