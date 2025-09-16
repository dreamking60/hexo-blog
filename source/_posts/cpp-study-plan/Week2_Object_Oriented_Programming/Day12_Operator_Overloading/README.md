# 第12天：运算符重载

## 学习目标
掌握C++运算符重载的方法，理解运算符重载的规则，学会设计直观的类接口，掌握友元函数的使用。

## 学习内容

### 1. 运算符重载的基本概念
运算符重载允许为自定义类型定义运算符的行为。

```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // 成员函数重载
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    
    // 友元函数重载
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
    
    // 比较运算符
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
};
```

## 实践练习

### 练习1：复数类实现
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // 算术运算符重载
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                      (imag * other.real - real * other.imag) / denominator);
    }
    
    // 比较运算符
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // 赋值运算符
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }
    
    // 友元函数
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
    
    // 获取实部和虚部
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    // 计算模长
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }
};

// 输出运算符重载
ostream& operator<<(ostream& os, const Complex& c) {
    if (c.imag >= 0) {
        os << c.real << " + " << c.imag << "i";
    } else {
        os << c.real << " - " << -c.imag << "i";
    }
    return os;
}

// 输入运算符重载
istream& operator>>(istream& is, Complex& c) {
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}
```

## 算法题练习

### 1. 基本计算器II (Medium)
**题目链接**: https://leetcode.cn/problems/basic-calculator-ii/

### 2. 逆波兰表达式求值 (Medium)
**题目链接**: https://leetcode.cn/problems/evaluate-reverse-polish-notation/

### 3. 设计计算器 (Medium)
**题目链接**: https://leetcode.cn/problems/basic-calculator/

### 4. 字符串解码 (Medium)
**题目链接**: https://leetcode.cn/problems/decode-string/

## 学习要点总结

### 1. 运算符重载的规则
- 不能重载的运算符
- 成员函数vs友元函数
- 返回类型的选择

### 2. 特殊运算符的重载
- 赋值运算符
- 下标运算符
- 函数调用运算符

### 3. 友元函数的使用
- 何时使用友元函数
- 友元函数的声明
- 友元函数的实现

记住：运算符重载应该让类的使用更直观，但不要过度使用！
