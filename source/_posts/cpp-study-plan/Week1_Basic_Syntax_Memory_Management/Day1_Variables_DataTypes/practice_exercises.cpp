#include <iostream>
#include <limits>
#include <climits>
#include <cfloat>
#include <iomanip>
using namespace std;

// 练习1：数据类型范围测试
void testDataTypes() {
    cout << "=== 数据类型范围测试 ===" << endl;
    
    // 整数类型
    cout << "整数类型：" << endl;
    cout << "int: " << sizeof(int) << " bytes, 范围: " 
         << INT_MIN << " 到 " << INT_MAX << endl;
    cout << "short: " << sizeof(short) << " bytes, 范围: " 
         << SHRT_MIN << " 到 " << SHRT_MAX << endl;
    cout << "long: " << sizeof(long) << " bytes, 范围: " 
         << LONG_MIN << " 到 " << LONG_MAX << endl;
    cout << "long long: " << sizeof(long long) << " bytes, 范围: " 
         << LLONG_MIN << " 到 " << LLONG_MAX << endl;
    
    // 无符号整数类型
    cout << "\n无符号整数类型：" << endl;
    cout << "unsigned int: " << sizeof(unsigned int) << " bytes, 范围: 0 到 " 
         << UINT_MAX << endl;
    cout << "unsigned char: " << sizeof(unsigned char) << " bytes, 范围: 0 到 " 
         << UCHAR_MAX << endl;
    
    // 浮点类型
    cout << "\n浮点类型：" << endl;
    cout << "float: " << sizeof(float) << " bytes, 范围: " 
         << FLT_MIN << " 到 " << FLT_MAX << endl;
    cout << "double: " << sizeof(double) << " bytes, 范围: " 
         << DBL_MIN << " 到 " << DBL_MAX << endl;
    cout << "long double: " << sizeof(long double) << " bytes, 范围: " 
         << LDBL_MIN << " 到 " << LDBL_MAX << endl;
    
    // 字符类型
    cout << "\n字符类型：" << endl;
    cout << "char: " << sizeof(char) << " bytes, 范围: " 
         << CHAR_MIN << " 到 " << CHAR_MAX << endl;
    cout << "wchar_t: " << sizeof(wchar_t) << " bytes" << endl;
    
    // 布尔类型
    cout << "\n布尔类型：" << endl;
    cout << "bool: " << sizeof(bool) << " bytes" << endl;
}

// 练习2：运算符优先级测试
void testOperatorPrecedence() {
    cout << "\n=== 运算符优先级测试 ===" << endl;
    
    int a = 2, b = 3, c = 4;
    
    // 算术运算符优先级
    cout << "a + b * c = " << a + b * c << " (乘法优先)" << endl;
    cout << "(a + b) * c = " << (a + b) * c << endl;
    
    // 关系运算符优先级
    cout << "a < b < c = " << (a < b < c) << " (从左到右结合)" << endl;
    cout << "a < b && b < c = " << (a < b && b < c) << " (逻辑与)" << endl;
    
    // 赋值运算符优先级
    int x = 5;
    cout << "x = " << x << endl;
    x += 2 * 3;  // 等价于 x = x + (2 * 3)
    cout << "x += 2 * 3 = " << x << endl;
    
    // 位运算符优先级
    int y = 0b1010;  // 二进制10
    cout << "y = " << y << " (二进制: 1010)" << endl;
    cout << "y << 1 = " << (y << 1) << " (左移1位)" << endl;
    cout << "y & 0b1111 = " << (y & 0b1111) << " (按位与)" << endl;
}

// 练习3：控制结构综合应用 - 简单计算器
void simpleCalculator() {
    cout << "\n=== 简单计算器 ===" << endl;
    
    double num1, num2, result;
    char operation;
    
    cout << "请输入第一个数字: ";
    cin >> num1;
    
    cout << "请输入运算符 (+, -, *, /): ";
    cin >> operation;
    
    cout << "请输入第二个数字: ";
    cin >> num2;
    
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
                return;
            }
            break;
        default:
            cout << "错误：不支持的运算符！" << endl;
            return;
    }
    
    cout << num1 << " " << operation << " " << num2 << " = " << result << endl;
}

// 练习4：循环结构应用 - 打印乘法表
void printMultiplicationTable() {
    cout << "\n=== 乘法表 ===" << endl;
    
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << " × " << i << " = " << (i * j) << "\t";
        }
        cout << endl;
    }
}

// 练习5：条件语句应用 - 判断闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void checkLeapYear() {
    cout << "\n=== 闰年判断 ===" << endl;
    
    int year;
    cout << "请输入年份: ";
    cin >> year;
    
    if (isLeapYear(year)) {
        cout << year << " 是闰年" << endl;
    } else {
        cout << year << " 不是闰年" << endl;
    }
}

// 练习6：变量初始化方式演示
void demonstrateInitialization() {
    cout << "\n=== 变量初始化方式演示 ===" << endl;
    
    // 直接初始化
    int a(10);
    int b{20};  // 列表初始化（C++11）
    
    // 拷贝初始化
    int c = 30;
    
    // 自动类型推导
    auto d = 40;  // 推导为int
    auto e = 3.14;  // 推导为double
    auto f = 'A';  // 推导为char
    
    cout << "a = " << a << " (直接初始化)" << endl;
    cout << "b = " << b << " (列表初始化)" << endl;
    cout << "c = " << c << " (拷贝初始化)" << endl;
    cout << "d = " << d << " (auto推导为int)" << endl;
    cout << "e = " << e << " (auto推导为double)" << endl;
    cout << "f = " << f << " (auto推导为char)" << endl;
}

// 练习7：常量定义演示
void demonstrateConstants() {
    cout << "\n=== 常量定义演示 ===" << endl;
    
    // const常量
    const int MAX_SIZE = 100;
    const double PI = 3.14159;
    
    // constexpr常量（C++11）
    constexpr int BUFFER_SIZE = 1024;
    constexpr double E = 2.71828;
    
    // 宏定义（不推荐，但需要了解）
    #define GRAVITY 9.8
    
    cout << "MAX_SIZE = " << MAX_SIZE << endl;
    cout << "PI = " << PI << endl;
    cout << "BUFFER_SIZE = " << BUFFER_SIZE << endl;
    cout << "E = " << E << endl;
    cout << "GRAVITY = " << GRAVITY << endl;
}

int main() {
    cout << "C++ 基础语法与数据类型练习" << endl;
    cout << "=========================" << endl;
    
    // 运行所有练习
    testDataTypes();
    testOperatorPrecedence();
    demonstrateInitialization();
    demonstrateConstants();
    printMultiplicationTable();
    checkLeapYear();
    
    // 计算器需要用户输入，放在最后
    simpleCalculator();
    
    return 0;
}
