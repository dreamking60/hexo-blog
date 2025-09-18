---
title: C++ 学习计划 - 第12天:运算符重载
date: 2025-09-16 10:22:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day12
layout: page
menu_id: plan
permalink: /plan/week2/day12/
---

# 第12天：运算符重载

## 学习目标
掌握运算符重载的方法和规则，学会为自定义类型实现自然的操作语法。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Operator Overloading](https://en.cppreference.com/w/cpp/language/operators) - C++官方运算符重载文档
- [LearnCpp - Operator Overloading](https://www.learncpp.com/cpp-tutorial/introduction-to-operator-overloading/) - 运算符重载教程
- [GeeksforGeeks - Operator Overloading](https://www.geeksforgeeks.org/operator-overloading-c/) - 运算符重载详解

### 🎥 视频教程
- [The Cherno C++ Operators](https://www.youtube.com/watch?v=mS9755gF66w) - 运算符重载深入讲解
- [C++ Operator Overloading Tutorial](https://www.youtube.com/watch?v=PgGhEovFhd0) - 运算符重载实例

### 📖 深入阅读
- [C++ Primer 第5版 - 第14章](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 重载运算与类型转换
- [Effective C++ - 条款23-25](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 运算符重载设计
- [More Effective C++ - 条款5,6,7](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X) - 运算符重载技巧

## 学习内容

### 1. 运算符重载基础
- 可重载的运算符
- 重载规则和限制
- 成员函数 vs 非成员函数
- 重载决议过程

### 2. 算术运算符重载
- 二元算术运算符
- 复合赋值运算符
- 一元运算符
- 递增递减运算符

### 3. 比较运算符重载
- 相等性运算符
- 关系运算符
- 三路比较运算符（C++20）
- 比较运算符的对称性

### 4. 特殊运算符重载
- 赋值运算符
- 下标运算符
- 函数调用运算符
- 类型转换运算符

### 5. 输入输出运算符
- 流插入运算符
- 流提取运算符
- 格式化输出
- 错误处理

## 重点概念和代码示例

### 复数类的运算符重载
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    double real, imag;
    
public:
    // 构造函数
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    // 访问器
    double getReal() const { return real; }
    double getImag() const { return imag; }
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }
    
    // 算术运算符重载（成员函数）
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw runtime_error("Division by zero");
        }
        return Complex(
            (real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator
        );
    }
    
    // 一元运算符
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    Complex operator+() const {
        return *this;
    }
    
    // 复合赋值运算符
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }
    
    Complex& operator*=(const Complex& other) {
        double newReal = real * other.real - imag * other.imag;
        double newImag = real * other.imag + imag * other.real;
        real = newReal;
        imag = newImag;
        return *this;
    }
    
    // 比较运算符
    bool operator==(const Complex& other) const {
        const double EPSILON = 1e-9;
        return abs(real - other.real) < EPSILON && abs(imag - other.imag) < EPSILON;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // 赋值运算符（编译器会自动生成，但这里展示如何自定义）
    Complex& operator=(const Complex& other) {
        if (this != &other) {  // 自赋值检查
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }
    
    // 类型转换运算符
    explicit operator double() const {
        return sqrt(real * real + imag * imag);  // 返回模长
    }
    
    explicit operator bool() const {
        return real != 0.0 || imag != 0.0;  // 非零复数为true
    }
    
    // 工具函数
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }
    
    double phase() const {
        return atan2(imag, real);
    }
    
    Complex conjugate() const {
        return Complex(real, -imag);
    }
    
    // 友元函数声明（用于非成员运算符）
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
    friend Complex operator+(double d, const Complex& c);
    friend Complex operator*(double d, const Complex& c);
};

// 输出流运算符（非成员函数）
ostream& operator<<(ostream& os, const Complex& c) {
    if (c.imag >= 0) {
        os << c.real << " + " << c.imag << "i";
    } else {
        os << c.real << " - " << (-c.imag) << "i";
    }
    return os;
}

// 输入流运算符
istream& operator>>(istream& is, Complex& c) {
    cout << "请输入实部: ";
    is >> c.real;
    cout << "请输入虚部: ";
    is >> c.imag;
    return is;
}

// 与标量的运算（非成员函数）
Complex operator+(double d, const Complex& c) {
    return Complex(d + c.real, c.imag);
}

Complex operator*(double d, const Complex& c) {
    return Complex(d * c.real, d * c.imag);
}

void complexDemo() {
    cout << "=== 复数类运算符重载演示 ===" << endl;
    
    Complex c1(3, 4);
    Complex c2(1, -2);
    Complex c3;
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    
    // 算术运算
    cout << "\n算术运算:" << endl;
    cout << "c1 + c2 = " << (c1 + c2) << endl;
    cout << "c1 - c2 = " << (c1 - c2) << endl;
    cout << "c1 * c2 = " << (c1 * c2) << endl;
    cout << "c1 / c2 = " << (c1 / c2) << endl;
    
    // 一元运算
    cout << "\n一元运算:" << endl;
    cout << "-c1 = " << (-c1) << endl;
    cout << "+c1 = " << (+c1) << endl;
    
    // 复合赋值
    cout << "\n复合赋值:" << endl;
    c3 = c1;
    cout << "c3 = " << c3 << endl;
    c3 += c2;
    cout << "c3 += c2: " << c3 << endl;
    c3 *= Complex(2, 0);
    cout << "c3 *= (2+0i): " << c3 << endl;
    
    // 比较运算
    cout << "\n比较运算:" << endl;
    cout << "c1 == c2: " << (c1 == c2) << endl;
    cout << "c1 != c2: " << (c1 != c2) << endl;
    
    // 与标量运算
    cout << "\n与标量运算:" << endl;
    cout << "2.5 + c1 = " << (2.5 + c1) << endl;
    cout << "3.0 * c2 = " << (3.0 * c2) << endl;
    
    // 类型转换
    cout << "\n类型转换:" << endl;
    cout << "c1的模长: " << static_cast<double>(c1) << endl;
    cout << "c1是否非零: " << static_cast<bool>(c1) << endl;
    
    // 工具函数
    cout << "\n复数属性:" << endl;
    cout << "c1的模长: " << c1.magnitude() << endl;
    cout << "c1的相位: " << c1.phase() << " 弧度" << endl;
    cout << "c1的共轭: " << c1.conjugate() << endl;
}
```

### 矩阵类的运算符重载
```cpp
class Matrix {
private:
    vector<vector<double>> data;
    size_t rows, cols;
    
public:
    // 构造函数
    Matrix(size_t r, size_t c, double initValue = 0.0) 
        : rows(r), cols(c), data(r, vector<double>(c, initValue)) {}
    
    // 拷贝构造函数
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}
    
    // 初始化列表构造函数
    Matrix(initializer_list<initializer_list<double>> init) {
        rows = init.size();
        cols = rows > 0 ? init.begin()->size() : 0;
        
        data.resize(rows);
        size_t i = 0;
        for (const auto& row : init) {
            data[i].resize(cols);
            size_t j = 0;
            for (double val : row) {
                if (j < cols) data[i][j] = val;
                j++;
            }
            i++;
        }
    }
    
    // 赋值运算符
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }
    
    // 下标运算符
    vector<double>& operator[](size_t row) {
        if (row >= rows) throw out_of_range("Row index out of range");
        return data[row];
    }
    
    const vector<double>& operator[](size_t row) const {
        if (row >= rows) throw out_of_range("Row index out of range");
        return data[row];
    }
    
    // 函数调用运算符
    double& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw out_of_range("Matrix index out of range");
        }
        return data[row][col];
    }
    
    const double& operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw out_of_range("Matrix index out of range");
        }
        return data[row][col];
    }
    
    // 算术运算符
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for addition");
        }
        
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for subtraction");
        }
        
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Invalid matrix dimensions for multiplication");
        }
        
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < other.cols; j++) {
                for (size_t k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
    
    // 标量运算
    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }
    
    // 复合赋值运算符
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }
    
    Matrix& operator*=(double scalar) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }
    
    // 比较运算符
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        
        const double EPSILON = 1e-9;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (abs(data[i][j] - other.data[i][j]) > EPSILON) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }
    
    // 获取信息
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    
    // 矩阵操作
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }
    
    // 友元函数
    friend ostream& operator<<(ostream& os, const Matrix& m);
    friend Matrix operator*(double scalar, const Matrix& m);
};

// 输出流运算符
ostream& operator<<(ostream& os, const Matrix& m) {
    for (size_t i = 0; i < m.rows; i++) {
        os << "[";
        for (size_t j = 0; j < m.cols; j++) {
            os << m.data[i][j];
            if (j < m.cols - 1) os << ", ";
        }
        os << "]" << endl;
    }
    return os;
}

// 标量与矩阵的乘法
Matrix operator*(double scalar, const Matrix& m) {
    return m * scalar;
}

void matrixDemo() {
    cout << "\n=== 矩阵类运算符重载演示 ===" << endl;
    
    // 创建矩阵
    Matrix m1{{1, 2}, {3, 4}};
    Matrix m2{{5, 6}, {7, 8}};
    Matrix m3(2, 2, 0);
    
    cout << "矩阵 m1:" << endl << m1 << endl;
    cout << "矩阵 m2:" << endl << m2 << endl;
    
    // 矩阵运算
    cout << "m1 + m2:" << endl << (m1 + m2) << endl;
    cout << "m1 - m2:" << endl << (m1 - m2) << endl;
    cout << "m1 * m2:" << endl << (m1 * m2) << endl;
    
    // 标量运算
    cout << "m1 * 2.5:" << endl << (m1 * 2.5) << endl;
    cout << "3.0 * m2:" << endl << (3.0 * m2) << endl;
    
    // 下标访问
    cout << "使用下标访问:" << endl;
    cout << "m1[0][1] = " << m1[0][1] << endl;
    
    // 函数调用运算符
    cout << "使用函数调用运算符:" << endl;
    cout << "m1(1,0) = " << m1(1, 0) << endl;
    
    // 修改元素
    m3(0, 0) = 10;
    m3(0, 1) = 20;
    m3(1, 0) = 30;
    m3(1, 1) = 40;
    cout << "修改后的 m3:" << endl << m3 << endl;
    
    // 矩阵转置
    cout << "m1 的转置:" << endl << m1.transpose() << endl;
    
    // 复合赋值
    m3 += m1;
    cout << "m3 += m1:" << endl << m3 << endl;
    
    // 比较运算
    cout << "m1 == m2: " << (m1 == m2) << endl;
    cout << "m1 != m2: " << (m1 != m2) << endl;
}
```

## 实践练习

### 练习1：字符串类运算符重载
```cpp
class MyString {
private:
    char* str;
    size_t length;
    
    void copyFrom(const char* source) {
        if (source) {
            length = strlen(source);
            str = new char[length + 1];
            strcpy(str, source);
        } else {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        }
    }
    
public:
    // 构造函数
    MyString() : str(nullptr), length(0) {
        str = new char[1];
        str[0] = '\0';
    }
    
    MyString(const char* s) {
        copyFrom(s);
    }
    
    MyString(const MyString& other) {
        copyFrom(other.str);
    }
    
    // 析构函数
    ~MyString() {
        delete[] str;
    }
    
    // 赋值运算符
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            copyFrom(other.str);
        }
        return *this;
    }
    
    MyString& operator=(const char* s) {
        delete[] str;
        copyFrom(s);
        return *this;
    }
    
    // 字符串连接
    MyString operator+(const MyString& other) const {
        char* newStr = new char[length + other.length + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        
        MyString result;
        delete[] result.str;
        result.str = newStr;
        result.length = length + other.length;
        
        return result;
    }
    
    MyString operator+(const char* s) const {
        if (!s) return *this;
        
        size_t sLen = strlen(s);
        char* newStr = new char[length + sLen + 1];
        strcpy(newStr, str);
        strcat(newStr, s);
        
        MyString result;
        delete[] result.str;
        result.str = newStr;
        result.length = length + sLen;
        
        return result;
    }
    
    // 复合赋值
    MyString& operator+=(const MyString& other) {
        *this = *this + other;
        return *this;
    }
    
    MyString& operator+=(const char* s) {
        *this = *this + s;
        return *this;
    }
    
    // 下标运算符
    char& operator[](size_t index) {
        if (index >= length) throw out_of_range("String index out of range");
        return str[index];
    }
    
    const char& operator[](size_t index) const {
        if (index >= length) throw out_of_range("String index out of range");
        return str[index];
    }
    
    // 比较运算符
    bool operator==(const MyString& other) const {
        return strcmp(str, other.str) == 0;
    }
    
    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }
    
    bool operator<(const MyString& other) const {
        return strcmp(str, other.str) < 0;
    }
    
    bool operator<=(const MyString& other) const {
        return strcmp(str, other.str) <= 0;
    }
    
    bool operator>(const MyString& other) const {
        return strcmp(str, other.str) > 0;
    }
    
    bool operator>=(const MyString& other) const {
        return strcmp(str, other.str) >= 0;
    }
    
    // 类型转换运算符
    operator const char*() const {
        return str;
    }
    
    operator bool() const {
        return length > 0;
    }
    
    // 工具函数
    size_t size() const { return length; }
    bool empty() const { return length == 0; }
    const char* c_str() const { return str; }
    
    // 友元函数
    friend ostream& operator<<(ostream& os, const MyString& s);
    friend istream& operator>>(istream& is, MyString& s);
    friend MyString operator+(const char* s, const MyString& str);
};

// 输出流运算符
ostream& operator<<(ostream& os, const MyString& s) {
    os << s.str;
    return os;
}

// 输入流运算符
istream& operator>>(istream& is, MyString& s) {
    char buffer[1000];
    is >> buffer;
    s = buffer;
    return is;
}

// C字符串与MyString的连接
MyString operator+(const char* s, const MyString& str) {
    MyString temp(s);
    return temp + str;
}

void exercise1() {
    cout << "\n=== 练习1：字符串类运算符重载 ===" << endl;
    
    MyString s1("Hello");
    MyString s2("World");
    MyString s3;
    
    cout << "s1 = \"" << s1 << "\"" << endl;
    cout << "s2 = \"" << s2 << "\"" << endl;
    
    // 字符串连接
    s3 = s1 + " " + s2;
    cout << "s3 = s1 + \" \" + s2 = \"" << s3 << "\"" << endl;
    
    // 复合赋值
    s1 += ", ";
    s1 += s2;
    cout << "s1 += \", \" + s2 = \"" << s1 << "\"" << endl;
    
    // 下标访问
    cout << "s1[0] = '" << s1[0] << "'" << endl;
    s1[0] = 'h';
    cout << "修改后 s1 = \"" << s1 << "\"" << endl;
    
    // 比较运算
    MyString s4("hello");
    cout << "s1 == s4: " << (s1 == s4) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;
    
    // 类型转换
    cout << "s1 转换为 const char*: " << static_cast<const char*>(s1) << endl;
    cout << "s3 是否非空: " << static_cast<bool>(s3) << endl;
    
    // 与C字符串混合运算
    MyString s5 = "C++ " + s2;
    cout << "\"C++ \" + s2 = \"" << s5 << "\"" << endl;
}
```

### 练习2：有理数类
```cpp
class Rational {
private:
    int numerator;    // 分子
    int denominator;  // 分母
    
    // 求最大公约数
    int gcd(int a, int b) const {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // 化简分数
    void reduce() {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        
        int g = gcd(numerator, denominator);
        if (g > 1) {
            numerator /= g;
            denominator /= g;
        }
    }
    
public:
    // 构造函数
    Rational(int num = 0, int den = 1) : numerator(num), denominator(den) {
        reduce();
    }
    
    // 拷贝构造函数
    Rational(const Rational& other) : numerator(other.numerator), denominator(other.denominator) {}
    
    // 赋值运算符
    Rational& operator=(const Rational& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }
    
    // 算术运算符
    Rational operator+(const Rational& other) const {
        return Rational(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        );
    }
    
    Rational operator-(const Rational& other) const {
        return Rational(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        );
    }
    
    Rational operator*(const Rational& other) const {
        return Rational(
            numerator * other.numerator,
            denominator * other.denominator
        );
    }
    
    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Division by zero");
        }
        return Rational(
            numerator * other.denominator,
            denominator * other.numerator
        );
    }
    
    // 一元运算符
    Rational operator-() const {
        return Rational(-numerator, denominator);
    }
    
    Rational operator+() const {
        return *this;
    }
    
    // 复合赋值运算符
    Rational& operator+=(const Rational& other) {
        *this = *this + other;
        return *this;
    }
    
    Rational& operator-=(const Rational& other) {
        *this = *this - other;
        return *this;
    }
    
    Rational& operator*=(const Rational& other) {
        *this = *this * other;
        return *this;
    }
    
    Rational& operator/=(const Rational& other) {
        *this = *this / other;
        return *this;
    }
    
    // 比较运算符
    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
    
    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    
    bool operator<=(const Rational& other) const {
        return *this < other || *this == other;
    }
    
    bool operator>(const Rational& other) const {
        return !(*this <= other);
    }
    
    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }
    
    // 类型转换运算符
    explicit operator double() const {
        return static_cast<double>(numerator) / denominator;
    }
    
    explicit operator bool() const {
        return numerator != 0;
    }
    
    // 访问器
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    
    // 工具函数
    Rational reciprocal() const {
        if (numerator == 0) {
            throw invalid_argument("Cannot find reciprocal of zero");
        }
        return Rational(denominator, numerator);
    }
    
    Rational abs() const {
        return Rational(::abs(numerator), denominator);
    }
    
    // 友元函数
    friend ostream& operator<<(ostream& os, const Rational& r);
    friend istream& operator>>(istream& is, Rational& r);
    friend Rational operator+(int i, const Rational& r);
    friend Rational operator*(int i, const Rational& r);
};

// 输出流运算符
ostream& operator<<(ostream& os, const Rational& r) {
    if (r.denominator == 1) {
        os << r.numerator;
    } else {
        os << r.numerator << "/" << r.denominator;
    }
    return os;
}

// 输入流运算符
istream& operator>>(istream& is, Rational& r) {
    cout << "请输入分子: ";
    is >> r.numerator;
    cout << "请输入分母: ";
    is >> r.denominator;
    r.reduce();
    return is;
}

// 整数与有理数的运算
Rational operator+(int i, const Rational& r) {
    return Rational(i) + r;
}

Rational operator*(int i, const Rational& r) {
    return Rational(i) * r;
}

void exercise2() {
    cout << "\n=== 练习2：有理数类 ===" << endl;
    
    Rational r1(3, 4);
    Rational r2(2, 5);
    Rational r3(6, 8);  // 应该化简为3/4
    
    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << " (自动化简)" << endl;
    
    // 算术运算
    cout << "\n算术运算:" << endl;
    cout << "r1 + r2 = " << (r1 + r2) << endl;
    cout << "r1 - r2 = " << (r1 - r2) << endl;
    cout << "r1 * r2 = " << (r1 * r2) << endl;
    cout << "r1 / r2 = " << (r1 / r2) << endl;
    
    // 一元运算
    cout << "\n一元运算:" << endl;
    cout << "-r1 = " << (-r1) << endl;
    cout << "+r2 = " << (+r2) << endl;
    
    // 比较运算
    cout << "\n比较运算:" << endl;
    cout << "r1 == r3: " << (r1 == r3) << endl;
    cout << "r1 < r2: " << (r1 < r2) << endl;
    cout << "r1 > r2: " << (r1 > r2) << endl;
    
    // 复合赋值
    cout << "\n复合赋值:" << endl;
    Rational r4 = r1;
    cout << "r4 = " << r4 << endl;
    r4 += r2;
    cout << "r4 += r2: " << r4 << endl;
    r4 *= Rational(2, 3);
    cout << "r4 *= 2/3: " << r4 << endl;
    
    // 与整数运算
    cout << "\n与整数运算:" << endl;
    cout << "2 + r1 = " << (2 + r1) << endl;
    cout << "3 * r2 = " << (3 * r2) << endl;
    
    // 类型转换
    cout << "\n类型转换:" << endl;
    cout << "r1 转换为 double: " << static_cast<double>(r1) << endl;
    cout << "r1 是否非零: " << static_cast<bool>(r1) << endl;
    
    // 工具函数
    cout << "\n工具函数:" << endl;
    cout << "r1 的倒数: " << r1.reciprocal() << endl;
    cout << "(-r1) 的绝对值: " << (-r1).abs() << endl;
}
```

## 学习检查点

- [ ] 理解运算符重载的基本规则和限制
- [ ] 掌握成员函数和非成员函数重载的选择
- [ ] 熟练实现算术运算符和比较运算符
- [ ] 掌握特殊运算符的重载技巧
- [ ] 理解运算符重载的对称性问题
- [ ] 能够实现输入输出流运算符
- [ ] 掌握类型转换运算符的使用
- [ ] 了解运算符重载的最佳实践

## 完整示例程序

```cpp
#include <iostream>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <cstring>
#include <stdexcept>
using namespace std;

int main() {
    cout << "=== C++ 运算符重载学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        complexDemo();
        matrixDemo();
        
        exercise1();
        exercise2();
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
    
    cout << "\n程序结束" << endl;
    return 0;
}
```

[返回第二周](/plan/week2/) | [上一天：虚函数与多态](/plan/week2/day11/) | [下一天：模板基础](/plan/week2/day13/)
