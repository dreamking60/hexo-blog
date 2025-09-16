# 第1天：变量、数据类型与基本语法

## 学习目标
复习C++基础语法和数据类型，掌握基本数据类型的特性和使用。

## 学习内容

### 1. 基本数据类型
- **整数类型**：`int`, `short`, `long`, `long long`
- **浮点类型**：`float`, `double`, `long double`
- **字符类型**：`char`, `wchar_t`, `char16_t`, `char32_t`
- **布尔类型**：`bool`
- **无符号类型**：`unsigned int`, `unsigned char` 等

### 2. 变量声明与初始化
- 变量声明语法
- 初始化方式（直接初始化、拷贝初始化、列表初始化）
- 变量命名规则
- 作用域规则

### 3. 常量与字面量
- `const` 关键字
- 字面量类型
- 宏定义 `#define`
- `constexpr` 常量表达式

### 4. 运算符优先级
- 算术运算符
- 关系运算符
- 逻辑运算符
- 位运算符
- 赋值运算符

### 5. 控制结构
- 条件语句：`if-else`, `switch-case`
- 循环语句：`for`, `while`, `do-while`
- 跳转语句：`break`, `continue`, `goto`

## 重点概念

### 数据类型大小
```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "int: " << sizeof(int) << " bytes" << endl;
    cout << "int range: " << INT_MIN << " to " << INT_MAX << endl;
    cout << "float: " << sizeof(float) << " bytes" << endl;
    cout << "double: " << sizeof(double) << " bytes" << endl;
    cout << "char: " << sizeof(char) << " bytes" << endl;
    cout << "bool: " << sizeof(bool) << " bytes" << endl;
    return 0;
}
```

### 变量初始化
```cpp
// 直接初始化
int a(10);
int b{20};  // 列表初始化（C++11）

// 拷贝初始化
int c = 30;

// 自动类型推导
auto d = 40;  // C++11
auto e = 3.14;  // 推导为double
```

### 常量定义
```cpp
const int MAX_SIZE = 100;
constexpr int BUFFER_SIZE = 1024;  // 编译时常量

#define PI 3.14159  // 宏定义（不推荐）
```

## 实践练习

### 练习1：数据类型范围测试
编写程序测试各种数据类型的范围，包括有符号和无符号类型。

### 练习2：运算符优先级
编写程序验证不同运算符的优先级和结合性。

### 练习3：控制结构综合应用
实现一个简单的计算器程序，支持基本的四则运算。

## 常见错误与注意事项

1. **整数溢出**：注意数据类型的范围限制
2. **浮点精度**：浮点数比较时注意精度问题
3. **未初始化变量**：使用未初始化的变量会导致未定义行为
4. **类型转换**：注意隐式类型转换可能导致的精度损失

## 学习检查点

- [ ] 能够正确声明和初始化各种类型的变量
- [ ] 理解各种数据类型的存储大小和取值范围
- [ ] 掌握运算符的优先级和结合性
- [ ] 能够熟练使用各种控制结构
- [ ] 了解常量与字面量的区别和使用场景

## 扩展阅读

- C++ Primer 第2章：变量和基本类型
- cppreference.com 数据类型页面
- 了解不同编译器和平台上的数据类型大小差异
