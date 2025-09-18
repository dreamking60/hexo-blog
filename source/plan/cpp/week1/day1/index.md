---
title: C++ 第1天：变量、数据类型与基本语法
date: 2025-01-27 10:00:00
layout: page
menu_id: plan
permalink: /plan/cpp/week1/day1/
---

# 📅 C++ 第1天：变量、数据类型与基本语法

## 学习目标
- 掌握C++基本数据类型和变量声明
- 理解常量与字面量的概念
- 熟悉运算符优先级和控制结构
- 能够编写基本的C++程序

## 📚 学习内容

### 1. 基本数据类型

C++提供了丰富的数据类型，主要包括：

#### 整数类型
```cpp
int age = 25;           // 32位整数
long long bigNumber = 1234567890LL;  // 64位整数
short smallNumber = 100;              // 16位整数
```

#### 浮点类型
```cpp
float price = 19.99f;   // 单精度浮点数
double pi = 3.14159265359;  // 双精度浮点数
long double precise = 3.141592653589793238L;  // 扩展精度
```

#### 字符类型
```cpp
char grade = 'A';       // 单个字符
wchar_t wideChar = L'中';  // 宽字符
char16_t utf16Char = u'中';  // UTF-16字符
char32_t utf32Char = U'中';  // UTF-32字符
```

#### 布尔类型
```cpp
bool isStudent = true;  // 布尔值
bool isGraduated = false;
```

### 2. 变量声明与初始化

#### 声明方式
```cpp
// 传统C风格声明
int x;
x = 10;

// C++11统一初始化
int y{20};
int z = {30};

// 自动类型推导
auto name = "Hello";  // 自动推导为const char*
auto count = 42;      // 自动推导为int
```

#### 常量声明
```cpp
const int MAX_SIZE = 100;        // 编译时常量
constexpr int BUFFER_SIZE = 256; // C++11常量表达式

// 只读变量
const double PI = 3.14159;
```

### 3. 运算符优先级

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3, c = 2;
    
    // 算术运算符优先级
    int result1 = a + b * c;      // 10 + (3 * 2) = 16
    int result2 = (a + b) * c;    // (10 + 3) * 2 = 26
    
    // 关系运算符
    bool isGreater = a > b;       // true
    bool isEqual = a == b;        // false
    
    // 逻辑运算符
    bool logicalAnd = (a > 5) && (b < 10);  // true && true = true
    bool logicalOr = (a < 5) || (b > 10);   // false || false = false
    
    cout << "result1: " << result1 << endl;
    cout << "result2: " << result2 << endl;
    cout << "isGreater: " << isGreater << endl;
    
    return 0;
}
```

### 4. 控制结构

#### 条件语句
```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "请输入分数: ";
    cin >> score;
    
    // if-else语句
    if (score >= 90) {
        cout << "优秀" << endl;
    } else if (score >= 80) {
        cout << "良好" << endl;
    } else if (score >= 70) {
        cout << "中等" << endl;
    } else if (score >= 60) {
        cout << "及格" << endl;
    } else {
        cout << "不及格" << endl;
    }
    
    // switch语句
    char grade;
    cout << "请输入等级: ";
    cin >> grade;
    
    switch (grade) {
        case 'A':
        case 'a':
            cout << "优秀" << endl;
            break;
        case 'B':
        case 'b':
            cout << "良好" << endl;
            break;
        case 'C':
        case 'c':
            cout << "中等" << endl;
            break;
        default:
            cout << "其他等级" << endl;
            break;
    }
    
    return 0;
}
```

#### 循环语句
```cpp
#include <iostream>
using namespace std;

int main() {
    // for循环
    cout << "for循环示例:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "i = " << i << endl;
    }
    
    // while循环
    cout << "\nwhile循环示例:" << endl;
    int j = 1;
    while (j <= 3) {
        cout << "j = " << j << endl;
        j++;
    }
    
    // do-while循环
    cout << "\ndo-while循环示例:" << endl;
    int k = 1;
    do {
        cout << "k = " << k << endl;
        k++;
    } while (k <= 3);
    
    return 0;
}
```

## 💻 实践练习

### 练习1：数据类型范围
编写一个程序，显示不同数据类型的范围：

```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "=== C++数据类型范围 ===" << endl;
    cout << "int范围: " << INT_MIN << " 到 " << INT_MAX << endl;
    cout << "long范围: " << LONG_MIN << " 到 " << LONG_MAX << endl;
    cout << "float范围: " << FLT_MIN << " 到 " << FLT_MAX << endl;
    cout << "double范围: " << DBL_MIN << " 到 " << DBL_MAX << endl;
    cout << "char范围: " << CHAR_MIN << " 到 " << CHAR_MAX << endl;
    
    return 0;
}
```

### 练习2：计算器程序
编写一个简单的计算器程序：

```cpp
#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char operation;
    
    cout << "请输入第一个数字: ";
    cin >> num1;
    
    cout << "请输入运算符 (+, -, *, /): ";
    cin >> operation;
    
    cout << "请输入第二个数字: ";
    cin >> num2;
    
    double result;
    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "错误：除数不能为零！" << endl;
                return 1;
            }
            break;
        default:
            cout << "错误：不支持的运算符！" << endl;
            return 1;
    }
    
    cout << num1 << " " << operation << " " << num2 << " = " << result << endl;
    
    return 0;
}
```

### 练习3：数字游戏
编写一个猜数字游戏：

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // 设置随机数种子
    srand(time(0));
    
    // 生成1-100的随机数
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    
    cout << "=== 猜数字游戏 ===" << endl;
    cout << "我想了一个1到100之间的数字，你能猜出来吗？" << endl;
    
    do {
        cout << "请输入你的猜测: ";
        cin >> guess;
        attempts++;
        
        if (guess < secretNumber) {
            cout << "太小了！再试试。" << endl;
        } else if (guess > secretNumber) {
            cout << "太大了！再试试。" << endl;
        } else {
            cout << "恭喜你！猜对了！" << endl;
            cout << "你用了 " << attempts << " 次就猜对了！" << endl;
        }
    } while (guess != secretNumber);
    
    return 0;
}
```

## 📝 学习总结

### 重点概念
1. **数据类型**：C++提供了丰富的数据类型，选择合适的类型很重要
2. **变量声明**：理解声明和初始化的区别
3. **常量**：使用const和constexpr声明常量
4. **运算符**：掌握运算符优先级和结合性
5. **控制结构**：if-else、switch、for、while、do-while的使用

### 常见错误
1. **未初始化变量**：使用未初始化的变量会导致未定义行为
2. **类型不匹配**：注意隐式类型转换
3. **运算符优先级**：使用括号明确运算顺序
4. **循环条件**：避免无限循环

### 最佳实践
1. **使用有意义的变量名**：提高代码可读性
2. **初始化变量**：总是初始化变量
3. **使用const**：尽可能使用const声明常量
4. **代码格式化**：保持代码整洁和一致

## 🚀 下一步

明天我们将学习函数与作用域，包括：
- 函数声明与定义
- 参数传递方式
- 函数重载
- 作用域规则

[**继续学习：第2天 函数与作用域** →](/plan/cpp/week1/day2/)

---

**记住：基础语法是C++学习的基石，一定要多练习！** 💪
