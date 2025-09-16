# 第11天：虚函数与多态

## 学习目标
深入理解C++多态机制，掌握虚函数表和动态绑定，学会设计多态类体系，理解抽象类和接口设计。

## 学习内容

### 1. 虚函数的概念
虚函数是实现多态的关键机制，允许在运行时确定调用哪个函数。

```cpp
class Animal {
public:
    virtual void makeSound() {
        cout << "Animal makes a sound" << endl;
    }
    
    virtual ~Animal() {}  // 虚析构函数
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Dog barks: Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Cat meows: Meow!" << endl;
    }
};
```

### 2. 虚函数表（vtable）
每个包含虚函数的类都有一个虚函数表，存储虚函数的地址。

### 3. 纯虚函数与抽象类
```cpp
class Shape {
protected:
    double x, y;
    
public:
    Shape(double x, double y) : x(x), y(y) {}
    
    virtual double area() const = 0;  // 纯虚函数
    virtual double perimeter() const = 0;  // 纯虚函数
    virtual void draw() const = 0;  // 纯虚函数
    
    virtual ~Shape() = default;
};
```

## 实践练习

### 练习1：多态动物类体系
```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {}
    
    virtual void makeSound() = 0;  // 纯虚函数
    virtual void move() {
        cout << name << " is moving" << endl;
    }
    
    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
};

class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}
    
    void makeSound() override {
        cout << name << " barks: Woof! Woof!" << endl;
    }
    
    void move() override {
        cout << name << " runs on four legs" << endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Breed: " << breed << endl;
    }
    
    void wagTail() {
        cout << name << " is wagging tail" << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor" << endl;
    }
};

class Bird : public Animal {
private:
    bool canFly;
    
public:
    Bird(string n, int a, bool fly) : Animal(n, a), canFly(fly) {}
    
    void makeSound() override {
        cout << name << " chirps: Tweet! Tweet!" << endl;
    }
    
    void move() override {
        if (canFly) {
            cout << name << " flies in the sky" << endl;
        } else {
            cout << name << " walks on the ground" << endl;
        }
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Can fly: " << (canFly ? "Yes" : "No") << endl;
    }
    
    ~Bird() {
        cout << "Bird destructor" << endl;
    }
};
```

## 算法题练习

### 1. 二叉树的最近公共祖先 (Medium)
**题目链接**: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/

### 2. 路径总和III (Medium)
**题目链接**: https://leetcode.cn/problems/path-sum-iii/

### 3. 验证完全二叉树 (Medium)
**题目链接**: https://leetcode.cn/problems/check-completeness-of-a-binary-tree/

### 4. 二叉树中的最大路径和 (Hard)
**题目链接**: https://leetcode.cn/problems/binary-tree-maximum-path-sum/

## 学习要点总结

### 1. 多态的实现原理
- 虚函数表机制
- 动态绑定vs静态绑定
- 运行时类型识别

### 2. 抽象类的设计
- 纯虚函数的使用
- 接口的定义
- 不能实例化的类

### 3. 虚析构函数的重要性
- 确保正确的析构顺序
- 避免内存泄漏
- 多态销毁的正确性

记住：多态是面向对象编程的核心特性，正确使用虚函数是实现多态的关键！
