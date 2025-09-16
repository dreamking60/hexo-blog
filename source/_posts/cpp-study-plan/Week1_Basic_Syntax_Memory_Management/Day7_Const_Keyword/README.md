# 第7天：const关键字

## 学习目标
深入理解const的各种用法，掌握常量变量、常量指针、常量引用等概念。

## 学习内容

### 1. 常量变量
- const变量的声明与初始化
- const变量的特点
- const与#define的区别
- constexpr常量表达式
- 编译时常量

### 2. 常量指针与指向常量的指针
- 常量指针（const pointer）
- 指向常量的指针（pointer to const）
- 指向常量的常量指针（const pointer to const）
- 指针的const修饰位置
- const指针的使用场景

### 3. 常量引用
- 常量引用的定义
- 常量引用的特点
- 常量引用作为函数参数
- 常量引用与临时对象
- 常量引用的性能优势

### 4. 常量成员函数
- const成员函数的定义
- const成员函数的特点
- const成员函数的重载
- mutable关键字
- const成员函数的调用

### 5. const_cast的使用
- const_cast的作用
- const_cast的使用场景
- const_cast的安全性
- 避免使用const_cast的情况
- 现代C++的替代方案

## 重点概念

### 常量变量
```cpp
// 基本常量变量
const int MAX_SIZE = 100;
const double PI = 3.14159;
const string NAME = "Hello";

// 常量变量必须初始化
// const int x;  // 错误：常量变量必须初始化

// const与#define的区别
#define MAX_SIZE_OLD 100  // 宏定义，不推荐
const int MAX_SIZE_NEW = 100;  // 常量变量，推荐

// constexpr常量表达式（C++11）
constexpr int BUFFER_SIZE = 1024;
constexpr double E = 2.71828;
```

### 常量指针与指向常量的指针
```cpp
int x = 10;
int y = 20;

// 指向常量的指针（pointer to const）
const int* ptr1 = &x;  // ptr1指向的int是常量
// *ptr1 = 30;  // 错误：不能通过ptr1修改x
ptr1 = &y;  // 正确：ptr1可以指向其他变量

// 常量指针（const pointer）
int* const ptr2 = &x;  // ptr2是常量指针
*ptr2 = 30;  // 正确：可以通过ptr2修改x
// ptr2 = &y;  // 错误：ptr2不能指向其他变量

// 指向常量的常量指针（const pointer to const）
const int* const ptr3 = &x;  // ptr3是常量指针，指向常量
// *ptr3 = 30;  // 错误：不能通过ptr3修改x
// ptr3 = &y;  // 错误：ptr3不能指向其他变量
```

### 常量引用
```cpp
int x = 10;

// 常量引用
const int& ref1 = x;  // ref1是常量引用
// ref1 = 20;  // 错误：不能通过ref1修改x

// 常量引用可以绑定到常量
const int y = 20;
const int& ref2 = y;  // 正确

// 常量引用可以绑定到临时对象
const int& ref3 = 42;  // 正确：常量引用可以绑定到临时对象
// int& ref4 = 42;  // 错误：非常量引用不能绑定到临时对象

// 常量引用作为函数参数
void printValue(const int& value) {
    cout << "值: " << value << endl;
    // value = 100;  // 错误：不能修改常量引用
}
```

### 常量成员函数
```cpp
class MyClass {
private:
    int value;
    mutable int counter;  // mutable成员变量可以在const成员函数中修改
    
public:
    MyClass(int v) : value(v), counter(0) {}
    
    // 普通成员函数
    int getValue() {
        return value;
    }
    
    // 常量成员函数
    int getValue() const {
        counter++;  // 正确：mutable成员变量可以在const成员函数中修改
        return value;
    }
    
    // 常量成员函数重载
    void print() const {
        cout << "常量成员函数: " << value << endl;
    }
    
    void print() {
        cout << "普通成员函数: " << value << endl;
    }
    
    // 修改成员变量的函数不能是const
    void setValue(int v) {
        value = v;
    }
};

// 使用示例
MyClass obj(42);
const MyClass constObj(100);

obj.print();        // 调用普通成员函数
constObj.print();   // 调用常量成员函数
```

### const_cast的使用
```cpp
// const_cast的基本用法
int x = 10;
const int* ptr = &x;

// 移除const修饰
int* mutablePtr = const_cast<int*>(ptr);
*mutablePtr = 20;  // 现在可以修改x

// 添加const修饰
const int* constPtr = const_cast<const int*>(&x);

// 注意：const_cast不能改变对象的常量性
const int y = 30;
int* ptr2 = const_cast<int*>(&y);
// *ptr2 = 40;  // 未定义行为：y是真正的常量
```

## 实践练习

### 练习1：常量变量
实现各种常量变量的声明和使用。

### 练习2：常量指针
实现常量指针和指向常量的指针的使用。

### 练习3：常量引用
实现常量引用作为函数参数的使用。

### 练习4：常量成员函数
实现常量成员函数和重载。

## 常见错误与注意事项

1. **常量变量未初始化**：常量变量必须在声明时初始化
2. **修改常量变量**：不能修改常量变量的值
3. **常量指针重新赋值**：常量指针不能重新赋值
4. **通过常量指针修改**：不能通过指向常量的指针修改值
5. **const_cast滥用**：滥用const_cast可能导致未定义行为

## 最佳实践

1. **优先使用const**：能用const的地方尽量使用const
2. **常量引用传参**：对于大对象使用常量引用避免拷贝
3. **const成员函数**：不修改对象状态的函数应该声明为const
4. **避免const_cast**：尽量避免使用const_cast
5. **明确const语义**：使用const时要明确其语义

## 学习检查点

- [ ] 理解const的基本概念和用法
- [ ] 掌握常量指针和指向常量的指针的区别
- [ ] 能够正确使用常量引用
- [ ] 理解常量成员函数的作用
- [ ] 了解const_cast的使用和注意事项
- [ ] 掌握const的最佳实践

## 扩展阅读

- C++ Primer 第2章：变量和基本类型
- Effective C++ 条款3：尽可能使用const
- 了解constexpr和constinit（C++20）
