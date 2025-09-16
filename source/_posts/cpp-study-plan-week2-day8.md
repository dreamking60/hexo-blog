---
title: C++ 学习计划 - 第8天：类与对象基础
date: 2025-09-16 10:18:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day8
layout: page
menu_id: plan
permalink: /plan/week2/day8/
---

# 第8天：类与对象基础

## 学习目标
掌握类的基本概念和对象的创建，理解面向对象编程的基础知识，学会设计简单的类。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Classes](https://en.cppreference.com/w/cpp/language/class) - C++官方类文档
- [LearnCpp - Classes](https://www.learncpp.com/cpp-tutorial/introduction-to-classes/) - 类和对象教程
- [GeeksforGeeks - Classes and Objects](https://www.geeksforgeeks.org/c-classes-and-objects/) - 类与对象详解

### 🎥 视频教程
- [The Cherno C++ Classes](https://www.youtube.com/watch?v=2BP8NhxjrO0) - 类概念深入讲解
- [C++ OOP Basics](https://www.youtube.com/watch?v=wN0x9eZLix4) - 面向对象基础

### 📖 深入阅读
- [C++ Primer 第5版 - 第7章](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 类
- [Effective C++ - 条款5-12](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 类的设计和实现
- [Design Patterns](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612) - 面向对象设计模式

## 学习内容

### 1. 类的基本概念
- 类的定义和声明
- 成员变量和成员函数
- 类的作用域
- 类与结构体的区别

### 2. 访问控制
- public访问级别
- private访问级别
- protected访问级别
- 封装的概念

### 3. 对象的创建和使用
- 对象的声明和初始化
- 成员访问操作符
- 对象数组
- 对象指针和引用

### 4. this指针
- this指针的概念
- this指针的使用
- 返回对象引用
- 链式调用

### 5. 类的设计原则
- 单一职责原则
- 接口设计
- 数据隐藏
- 类的内聚性

## 重点概念和代码示例

### 基本类定义
```cpp
#include <iostream>
#include <string>
using namespace std;

// 基本类定义
class Student {
private:  // 私有成员
    string name;
    int age;
    double gpa;
    
public:   // 公有成员
    // 构造函数
    Student() : name("Unknown"), age(0), gpa(0.0) {
        cout << "默认构造函数被调用" << endl;
    }
    
    Student(const string& n, int a, double g) : name(n), age(a), gpa(g) {
        cout << "参数构造函数被调用: " << name << endl;
    }
    
    // 成员函数
    void setName(const string& n) {
        name = n;
    }
    
    string getName() const {
        return name;
    }
    
    void setAge(int a) {
        if (a >= 0 && a <= 150) {  // 数据验证
            age = a;
        }
    }
    
    int getAge() const {
        return age;
    }
    
    void setGPA(double g) {
        if (g >= 0.0 && g <= 4.0) {
            gpa = g;
        }
    }
    
    double getGPA() const {
        return gpa;
    }
    
    // 行为方法
    void study(const string& subject) {
        cout << name << " 正在学习 " << subject << endl;
    }
    
    void displayInfo() const {
        cout << "学生信息: " << name << ", " << age << "岁, GPA: " << gpa << endl;
    }
    
    // 比较方法
    bool isOlderThan(const Student& other) const {
        return age > other.age;
    }
};

void classBasics() {
    cout << "=== 类与对象基础 ===" << endl;
    
    // 创建对象
    Student student1;  // 调用默认构造函数
    Student student2("Alice", 20, 3.8);  // 调用参数构造函数
    
    // 使用对象
    student1.setName("Bob");
    student1.setAge(19);
    student1.setGPA(3.5);
    
    // 显示信息
    student1.displayInfo();
    student2.displayInfo();
    
    // 调用行为方法
    student1.study("C++编程");
    student2.study("数据结构");
    
    // 对象比较
    if (student2.isOlderThan(student1)) {
        cout << student2.getName() << " 比 " << student1.getName() << " 年龄大" << endl;
    }
}
```

### 访问控制详解
```cpp
class AccessControlDemo {
private:
    int privateData;
    
    void privateMethod() {
        cout << "私有方法被调用" << endl;
    }
    
protected:
    int protectedData;
    
    void protectedMethod() {
        cout << "保护方法被调用" << endl;
    }
    
public:
    int publicData;
    
    AccessControlDemo() : privateData(1), protectedData(2), publicData(3) {}
    
    void publicMethod() {
        cout << "公有方法被调用" << endl;
        
        // 类内部可以访问所有成员
        privateMethod();
        protectedMethod();
        
        cout << "私有数据: " << privateData << endl;
        cout << "保护数据: " << protectedData << endl;
        cout << "公有数据: " << publicData << endl;
    }
    
    // 提供访问私有成员的接口
    int getPrivateData() const { return privateData; }
    void setPrivateData(int value) { privateData = value; }
};

void accessControlDemo() {
    cout << "\n=== 访问控制演示 ===" << endl;
    
    AccessControlDemo obj;
    
    // 只能访问公有成员
    obj.publicData = 100;
    obj.publicMethod();
    
    // obj.privateData = 200;    // 错误！不能访问私有成员
    // obj.protectedData = 300;  // 错误！不能访问保护成员
    
    // 通过公有接口访问私有数据
    cout << "通过接口获取私有数据: " << obj.getPrivateData() << endl;
    obj.setPrivateData(500);
    cout << "修改后的私有数据: " << obj.getPrivateData() << endl;
}
```

### this指针的使用
```cpp
class Calculator {
private:
    double value;
    
public:
    Calculator(double initial = 0.0) : value(initial) {}
    
    // 使用this指针返回对象引用，支持链式调用
    Calculator& add(double x) {
        this->value += x;  // 显式使用this指针
        return *this;      // 返回当前对象的引用
    }
    
    Calculator& subtract(double x) {
        value -= x;        // 隐式使用this指针
        return *this;
    }
    
    Calculator& multiply(double x) {
        this->value *= x;
        return *this;
    }
    
    Calculator& divide(double x) {
        if (x != 0.0) {
            this->value /= x;
        } else {
            cout << "错误：除数不能为零！" << endl;
        }
        return *this;
    }
    
    // 比较函数，演示this指针的另一种用法
    bool equals(const Calculator& other) const {
        return this->value == other.value;
    }
    
    // 赋值函数，演示自赋值检查
    Calculator& assign(const Calculator& other) {
        if (this != &other) {  // 检查自赋值
            this->value = other.value;
        }
        return *this;
    }
    
    double getValue() const { return value; }
    
    void reset() { value = 0.0; }
    
    void display() const {
        cout << "当前值: " << value << endl;
    }
};

void thisPointerDemo() {
    cout << "\n=== this指针演示 ===" << endl;
    
    Calculator calc1(10.0);
    Calculator calc2(5.0);
    
    cout << "calc1初始值: ";
    calc1.display();
    
    // 链式调用
    calc1.add(5).multiply(2).subtract(10).divide(2);
    cout << "链式计算后: ";
    calc1.display();
    
    // 对象比较
    cout << "calc1 == calc2: " << calc1.equals(calc2) << endl;
    
    // 对象赋值
    calc2.assign(calc1);
    cout << "赋值后calc2: ";
    calc2.display();
    cout << "现在 calc1 == calc2: " << calc1.equals(calc2) << endl;
}
```

## 实践练习

### 练习1：银行账户类
```cpp
class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;
    static int nextAccountId;  // 静态成员，用于生成账户号
    
public:
    // 构造函数
    BankAccount(const string& owner, double initialBalance = 0.0) 
        : ownerName(owner), balance(initialBalance) {
        accountNumber = "ACC" + to_string(++nextAccountId);
        cout << "账户创建成功: " << accountNumber << endl;
    }
    
    // 存款
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "存款成功: $" << amount << ", 当前余额: $" << balance << endl;
            return true;
        } else {
            cout << "存款金额必须大于0" << endl;
            return false;
        }
    }
    
    // 取款
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "取款成功: $" << amount << ", 当前余额: $" << balance << endl;
            return true;
        } else if (amount <= 0) {
            cout << "取款金额必须大于0" << endl;
            return false;
        } else {
            cout << "余额不足，当前余额: $" << balance << endl;
            return false;
        }
    }
    
    // 转账
    bool transfer(BankAccount& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "转账成功: " << ownerName << " -> " << toAccount.ownerName 
                 << ", 金额: $" << amount << endl;
            return true;
        } else {
            cout << "转账失败" << endl;
            return false;
        }
    }
    
    // 获取余额
    double getBalance() const {
        return balance;
    }
    
    // 获取账户信息
    string getAccountNumber() const {
        return accountNumber;
    }
    
    string getOwnerName() const {
        return ownerName;
    }
    
    // 显示账户信息
    void displayAccountInfo() const {
        cout << "账户号: " << accountNumber 
             << ", 户主: " << ownerName 
             << ", 余额: $" << balance << endl;
    }
    
    // 比较账户余额
    bool hasMoreMoneyThan(const BankAccount& other) const {
        return balance > other.balance;
    }
};

// 静态成员定义
int BankAccount::nextAccountId = 0;

void exercise1() {
    cout << "\n=== 练习1：银行账户类 ===" << endl;
    
    // 创建账户
    BankAccount account1("Alice", 1000.0);
    BankAccount account2("Bob", 500.0);
    BankAccount account3("Charlie");
    
    // 显示初始状态
    cout << "\n初始账户状态:" << endl;
    account1.displayAccountInfo();
    account2.displayAccountInfo();
    account3.displayAccountInfo();
    
    // 进行交易
    cout << "\n进行交易:" << endl;
    account1.deposit(200.0);
    account2.withdraw(100.0);
    account3.deposit(50.0);
    
    // 转账操作
    cout << "\n转账操作:" << endl;
    account1.transfer(account3, 300.0);
    
    // 显示最终状态
    cout << "\n最终账户状态:" << endl;
    account1.displayAccountInfo();
    account2.displayAccountInfo();
    account3.displayAccountInfo();
    
    // 比较账户
    if (account1.hasMoreMoneyThan(account2)) {
        cout << account1.getOwnerName() << " 比 " << account2.getOwnerName() << " 有更多钱" << endl;
    }
}
```

### 练习2：图书类和图书馆类
```cpp
class Book {
private:
    string title;
    string author;
    string isbn;
    int pages;
    bool available;
    
public:
    Book(const string& t, const string& a, const string& i, int p) 
        : title(t), author(a), isbn(i), pages(p), available(true) {}
    
    // Getter方法
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    int getPages() const { return pages; }
    bool isAvailable() const { return available; }
    
    // 借书和还书
    bool borrow() {
        if (available) {
            available = false;
            return true;
        }
        return false;
    }
    
    void returnBook() {
        available = true;
    }
    
    // 显示图书信息
    void displayInfo() const {
        cout << "《" << title << "》 - " << author 
             << " (ISBN: " << isbn << ", " << pages << "页) "
             << (available ? "[可借]" : "[已借出]") << endl;
    }
    
    // 比较函数
    bool hasSameAuthor(const Book& other) const {
        return author == other.author;
    }
};

class Library {
private:
    string name;
    Book* books;     // 动态数组存储图书
    int capacity;    // 容量
    int bookCount;   // 当前图书数量
    
public:
    Library(const string& libName, int cap) 
        : name(libName), capacity(cap), bookCount(0) {
        books = new Book*[capacity];
        for (int i = 0; i < capacity; i++) {
            books[i] = nullptr;
        }
        cout << "图书馆 \"" << name << "\" 创建成功，容量: " << capacity << endl;
    }
    
    ~Library() {
        // 释放所有图书对象
        for (int i = 0; i < bookCount; i++) {
            delete books[i];
        }
        delete[] books;
        cout << "图书馆 \"" << name << "\" 已关闭" << endl;
    }
    
    // 添加图书
    bool addBook(const string& title, const string& author, const string& isbn, int pages) {
        if (bookCount < capacity) {
            books[bookCount] = new Book(title, author, isbn, pages);
            bookCount++;
            cout << "图书添加成功: " << title << endl;
            return true;
        } else {
            cout << "图书馆已满，无法添加更多图书" << endl;
            return false;
        }
    }
    
    // 查找图书
    Book* findBookByTitle(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getTitle() == title) {
                return books[i];
            }
        }
        return nullptr;
    }
    
    Book* findBookByISBN(const string& isbn) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getISBN() == isbn) {
                return books[i];
            }
        }
        return nullptr;
    }
    
    // 借书
    bool borrowBook(const string& title) {
        Book* book = findBookByTitle(title);
        if (book != nullptr) {
            if (book->borrow()) {
                cout << "借书成功: " << title << endl;
                return true;
            } else {
                cout << "图书已被借出: " << title << endl;
                return false;
            }
        } else {
            cout << "未找到图书: " << title << endl;
            return false;
        }
    }
    
    // 还书
    bool returnBook(const string& title) {
        Book* book = findBookByTitle(title);
        if (book != nullptr) {
            book->returnBook();
            cout << "还书成功: " << title << endl;
            return true;
        } else {
            cout << "未找到图书: " << title << endl;
            return false;
        }
    }
    
    // 显示所有图书
    void displayAllBooks() const {
        cout << "\n=== " << name << " 图书清单 ===" << endl;
        if (bookCount == 0) {
            cout << "图书馆暂无图书" << endl;
        } else {
            for (int i = 0; i < bookCount; i++) {
                cout << (i + 1) << ". ";
                books[i]->displayInfo();
            }
        }
    }
    
    // 显示可借图书
    void displayAvailableBooks() const {
        cout << "\n=== 可借图书 ===" << endl;
        bool hasAvailable = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->isAvailable()) {
                books[i]->displayInfo();
                hasAvailable = true;
            }
        }
        if (!hasAvailable) {
            cout << "暂无可借图书" << endl;
        }
    }
    
    // 统计信息
    int getTotalBooks() const { return bookCount; }
    
    int getAvailableBooks() const {
        int count = 0;
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->isAvailable()) {
                count++;
            }
        }
        return count;
    }
};

void exercise2() {
    cout << "\n=== 练习2：图书类和图书馆类 ===" << endl;
    
    // 创建图书馆
    Library library("市立图书馆", 10);
    
    // 添加图书
    library.addBook("C++ Primer", "Stanley Lippman", "978-0321714114", 976);
    library.addBook("Effective C++", "Scott Meyers", "978-0321334879", 297);
    library.addBook("Design Patterns", "Gang of Four", "978-0201633610", 395);
    library.addBook("Clean Code", "Robert Martin", "978-0132350884", 464);
    
    // 显示所有图书
    library.displayAllBooks();
    
    // 借书操作
    cout << "\n=== 借书操作 ===" << endl;
    library.borrowBook("C++ Primer");
    library.borrowBook("Effective C++");
    library.borrowBook("不存在的书");
    
    // 显示可借图书
    library.displayAvailableBooks();
    
    // 还书操作
    cout << "\n=== 还书操作 ===" << endl;
    library.returnBook("C++ Primer");
    
    // 显示统计信息
    cout << "\n=== 统计信息 ===" << endl;
    cout << "总图书数: " << library.getTotalBooks() << endl;
    cout << "可借图书数: " << library.getAvailableBooks() << endl;
    
    library.displayAvailableBooks();
}
```

### 练习3：点和圆类
```cpp
class Point {
private:
    double x, y;
    
public:
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    // Getter和Setter
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setPoint(double newX, double newY) { x = newX; y = newY; }
    
    // 计算到另一点的距离
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
    
    // 计算到原点的距离
    double distanceToOrigin() const {
        return sqrt(x * x + y * y);
    }
    
    // 移动点
    Point& move(double deltaX, double deltaY) {
        x += deltaX;
        y += deltaY;
        return *this;  // 支持链式调用
    }
    
    // 显示点的坐标
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
    
    // 比较两点是否相等
    bool equals(const Point& other) const {
        const double EPSILON = 1e-9;
        return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON;
    }
};

class Circle {
private:
    Point center;
    double radius;
    
public:
    Circle(const Point& c, double r) : center(c), radius(r) {
        if (radius < 0) {
            radius = 0;
            cout << "警告：半径不能为负数，已设置为0" << endl;
        }
    }
    
    Circle(double x, double y, double r) : center(x, y), radius(r) {
        if (radius < 0) {
            radius = 0;
            cout << "警告：半径不能为负数，已设置为0" << endl;
        }
    }
    
    // Getter方法
    Point getCenter() const { return center; }
    double getRadius() const { return radius; }
    
    // Setter方法
    void setCenter(const Point& newCenter) { center = newCenter; }
    void setRadius(double newRadius) {
        if (newRadius >= 0) {
            radius = newRadius;
        } else {
            cout << "错误：半径不能为负数" << endl;
        }
    }
    
    // 计算面积
    double getArea() const {
        const double PI = 3.14159265359;
        return PI * radius * radius;
    }
    
    // 计算周长
    double getPerimeter() const {
        const double PI = 3.14159265359;
        return 2 * PI * radius;
    }
    
    // 判断点是否在圆内
    bool containsPoint(const Point& point) const {
        return center.distanceTo(point) <= radius;
    }
    
    // 判断点是否在圆上
    bool pointOnCircle(const Point& point) const {
        const double EPSILON = 1e-9;
        return abs(center.distanceTo(point) - radius) < EPSILON;
    }
    
    // 判断两圆是否相交
    bool intersects(const Circle& other) const {
        double distance = center.distanceTo(other.center);
        return distance <= (radius + other.radius) && distance >= abs(radius - other.radius);
    }
    
    // 移动圆心
    Circle& moveCenter(double deltaX, double deltaY) {
        center.move(deltaX, deltaY);
        return *this;
    }
    
    // 显示圆的信息
    void display() const {
        cout << "圆心: ";
        center.display();
        cout << ", 半径: " << radius 
             << ", 面积: " << getArea() 
             << ", 周长: " << getPerimeter() << endl;
    }
};

void exercise3() {
    cout << "\n=== 练习3：点和圆类 ===" << endl;
    
    // 创建点
    Point p1(3, 4);
    Point p2(0, 0);
    Point p3(1, 1);
    
    cout << "点的信息:" << endl;
    cout << "p1: "; p1.display(); cout << endl;
    cout << "p2: "; p2.display(); cout << endl;
    cout << "p3: "; p3.display(); cout << endl;
    
    // 计算距离
    cout << "\n距离计算:" << endl;
    cout << "p1到p2的距离: " << p1.distanceTo(p2) << endl;
    cout << "p1到原点的距离: " << p1.distanceToOrigin() << endl;
    
    // 移动点
    cout << "\n移动p1 (2, -1):" << endl;
    p1.move(2, -1);
    cout << "移动后p1: "; p1.display(); cout << endl;
    
    // 创建圆
    Circle circle1(Point(0, 0), 5);
    Circle circle2(3, 4, 2);
    
    cout << "\n圆的信息:" << endl;
    circle1.display();
    circle2.display();
    
    // 点与圆的关系
    cout << "\n点与圆的关系:" << endl;
    cout << "p2是否在circle1内: " << (circle1.containsPoint(p2) ? "是" : "否") << endl;
    cout << "p3是否在circle1内: " << (circle1.containsPoint(p3) ? "是" : "否") << endl;
    
    // 圆与圆的关系
    cout << "\n圆与圆的关系:" << endl;
    cout << "circle1和circle2是否相交: " << (circle1.intersects(circle2) ? "是" : "否") << endl;
    
    // 移动圆心
    cout << "\n移动circle2的圆心 (-1, -1):" << endl;
    circle2.moveCenter(-1, -1);
    circle2.display();
    cout << "移动后circle1和circle2是否相交: " << (circle1.intersects(circle2) ? "是" : "否") << endl;
}
```

## 算法练习题

### LeetCode相关题目
1. **[设计链表](https://leetcode.cn/problems/design-linked-list/)** - 链表类设计
2. **[设计哈希映射](https://leetcode.cn/problems/design-hashmap/)** - 哈希表类设计
3. **[LRU缓存机制](https://leetcode.cn/problems/lru-cache/)** - 缓存类设计

### 练习4：简单的向量类
```cpp
class Vector2D {
private:
    double x, y;
    
public:
    // 构造函数
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    // 拷贝构造函数
    Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}
    
    // 访问器
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    
    // 向量运算
    Vector2D add(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D subtract(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D multiply(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    // 点积
    double dotProduct(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    
    // 向量长度
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    // 单位向量
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag > 0) {
            return Vector2D(x / mag, y / mag);
        }
        return Vector2D(0, 0);
    }
    
    // 角度（弧度）
    double angle() const {
        return atan2(y, x);
    }
    
    // 两向量夹角
    double angleBetween(const Vector2D& other) const {
        double dot = dotProduct(other);
        double mag1 = magnitude();
        double mag2 = other.magnitude();
        if (mag1 > 0 && mag2 > 0) {
            return acos(dot / (mag1 * mag2));
        }
        return 0;
    }
    
    // 向量是否相等
    bool equals(const Vector2D& other, double epsilon = 1e-9) const {
        return abs(x - other.x) < epsilon && abs(y - other.y) < epsilon;
    }
    
    // 显示向量
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
    
    // 链式操作支持
    Vector2D& addInPlace(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector2D& multiplyInPlace(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
};

void exercise4() {
    cout << "\n=== 练习4：向量类 ===" << endl;
    
    // 创建向量
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    Vector2D v3;  // 零向量
    
    cout << "向量信息:" << endl;
    cout << "v1: "; v1.display(); cout << " (长度: " << v1.magnitude() << ")" << endl;
    cout << "v2: "; v2.display(); cout << " (长度: " << v2.magnitude() << ")" << endl;
    cout << "v3: "; v3.display(); cout << " (长度: " << v3.magnitude() << ")" << endl;
    
    // 向量运算
    Vector2D sum = v1.add(v2);
    Vector2D diff = v1.subtract(v2);
    Vector2D scaled = v1.multiply(2.0);
    
    cout << "\n向量运算:" << endl;
    cout << "v1 + v2 = "; sum.display(); cout << endl;
    cout << "v1 - v2 = "; diff.display(); cout << endl;
    cout << "v1 * 2 = "; scaled.display(); cout << endl;
    
    // 点积和夹角
    double dot = v1.dotProduct(v2);
    double angle = v1.angleBetween(v2);
    
    cout << "\n高级运算:" << endl;
    cout << "v1 · v2 = " << dot << endl;
    cout << "v1和v2的夹角: " << angle << " 弧度 (" << (angle * 180 / 3.14159) << " 度)" << endl;
    
    // 单位向量
    Vector2D unit1 = v1.normalize();
    cout << "v1的单位向量: "; unit1.display(); 
    cout << " (长度: " << unit1.magnitude() << ")" << endl;
    
    // 链式操作
    Vector2D v4(1, 1);
    v4.addInPlace(v2).multiplyInPlace(3);
    cout << "链式操作结果: "; v4.display(); cout << endl;
}
```

## 学习检查点

- [ ] 理解类和对象的基本概念
- [ ] 掌握类的定义和成员声明
- [ ] 理解访问控制的三个级别
- [ ] 熟练使用构造函数初始化对象
- [ ] 掌握this指针的概念和使用
- [ ] 能够设计简单的类和对象
- [ ] 理解封装的重要性
- [ ] 能够实现类的基本方法

## 完整示例程序

```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    cout << "=== C++ 类与对象基础学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        classBasics();
        accessControlDemo();
        thisPointerDemo();
        
        exercise1();
        exercise2();
        exercise3();
        exercise4();
        
    } catch (const exception& e) {
        cout << "异常: " << e.what() << endl;
    }
    
    return 0;
}
```

[返回第二周](/plan/week2/) | [上一天：const关键字](/plan/week1/day7/) | [下一天：构造函数与析构函数](/plan/week2/day9/)
