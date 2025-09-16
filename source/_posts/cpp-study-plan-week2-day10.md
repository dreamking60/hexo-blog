---
title: C++ 学习计划 - 第10天：继承
date: 2025-09-16 10:20:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day10
layout: page
menu_id: plan
permalink: /plan/week2/day10/
---

# 第10天：继承

## 学习目标
掌握面向对象的继承机制，理解基类和派生类的关系，学会设计类继承体系。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Inheritance](https://en.cppreference.com/w/cpp/language/derived_class) - C++官方继承文档
- [LearnCpp - Inheritance](https://www.learncpp.com/cpp-tutorial/introduction-to-inheritance/) - 继承详解教程
- [GeeksforGeeks - Inheritance](https://www.geeksforgeeks.org/inheritance-in-c/) - 继承基础知识

### 🎥 视频教程
- [The Cherno C++ Inheritance](https://www.youtube.com/watch?v=X8nYM8GdnmE) - 继承概念深入讲解
- [C++ Inheritance Tutorial](https://www.youtube.com/watch?v=9RJTQmK0YPI) - 继承实例演示

### 📖 深入阅读
- [C++ Primer 第5版 - 第15章](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 面向对象程序设计
- [Effective C++ - 条款32-40](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 继承与面向对象设计
- [Design Patterns](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612) - 继承在设计模式中的应用

## 学习内容

### 1. 继承基础概念
- 基类和派生类
- is-a关系
- 代码重用
- 继承的语法

### 2. 继承方式
- public继承
- private继承
- protected继承
- 继承方式的影响

### 3. 派生类的构造和析构
- 构造函数调用顺序
- 析构函数调用顺序
- 基类构造函数的调用
- 初始化列表

### 4. 成员访问和隐藏
- 成员函数的重写
- 名称隐藏
- 作用域解析
- using声明

### 5. 多重继承
- 多重继承的语法
- 菱形继承问题
- 虚继承
- 多重继承的复杂性

## 重点概念和代码示例

### 基本继承
```cpp
#include <iostream>
#include <string>
using namespace std;

// 基类：动物
class Animal {
protected:  // protected成员可以被派生类访问
    string name;
    int age;
    
public:
    Animal(const string& n, int a) : name(n), age(a) {
        cout << "Animal构造函数：" << name << endl;
    }
    
    virtual ~Animal() {  // 虚析构函数很重要
        cout << "Animal析构函数：" << name << endl;
    }
    
    // 基类的公共接口
    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    
    void setAge(int a) { age = a; }
    int getAge() const { return age; }
    
    // 虚函数，可以被派生类重写
    virtual void makeSound() const {
        cout << name << " 发出了声音" << endl;
    }
    
    virtual void move() const {
        cout << name << " 在移动" << endl;
    }
    
    // 普通成员函数
    void sleep() const {
        cout << name << " 正在睡觉" << endl;
    }
    
    void displayInfo() const {
        cout << "动物信息 - 姓名: " << name << ", 年龄: " << age << endl;
    }
};

// 派生类：狗
class Dog : public Animal {  // public继承
private:
    string breed;  // 品种
    
public:
    // 派生类构造函数必须调用基类构造函数
    Dog(const string& n, int a, const string& b) 
        : Animal(n, a), breed(b) {  // 调用基类构造函数
        cout << "Dog构造函数：" << name << " (" << breed << ")" << endl;
    }
    
    ~Dog() {
        cout << "Dog析构函数：" << name << endl;
    }
    
    // 重写基类的虚函数
    void makeSound() const override {
        cout << name << " 汪汪叫" << endl;
    }
    
    void move() const override {
        cout << name << " 在跑步" << endl;
    }
    
    // 派生类特有的方法
    void wagTail() const {
        cout << name << " 摇尾巴" << endl;
    }
    
    void fetch() const {
        cout << name << " 去捡球" << endl;
    }
    
    string getBreed() const { return breed; }
    void setBreed(const string& b) { breed = b; }
    
    // 重写基类方法，提供更详细的信息
    void displayInfo() const {
        Animal::displayInfo();  // 调用基类方法
        cout << "品种: " << breed << endl;
    }
};

// 派生类：猫
class Cat : public Animal {
private:
    bool isIndoor;
    
public:
    Cat(const string& n, int a, bool indoor = true) 
        : Animal(n, a), isIndoor(indoor) {
        cout << "Cat构造函数：" << name << endl;
    }
    
    ~Cat() {
        cout << "Cat析构函数：" << name << endl;
    }
    
    void makeSound() const override {
        cout << name << " 喵喵叫" << endl;
    }
    
    void move() const override {
        cout << name << " 悄悄地走" << endl;
    }
    
    // 猫特有的行为
    void purr() const {
        cout << name << " 发出呼噜声" << endl;
    }
    
    void climb() const {
        cout << name << " 爬树" << endl;
    }
    
    bool getIsIndoor() const { return isIndoor; }
    void setIsIndoor(bool indoor) { isIndoor = indoor; }
    
    void displayInfo() const {
        Animal::displayInfo();
        cout << "类型: " << (isIndoor ? "室内猫" : "室外猫") << endl;
    }
};

void inheritanceBasics() {
    cout << "=== 基本继承演示 ===" << endl;
    
    // 创建对象
    Animal animal("通用动物", 5);
    Dog dog("旺财", 3, "金毛");
    Cat cat("咪咪", 2, true);
    
    cout << "\n=== 对象信息 ===" << endl;
    animal.displayInfo();
    dog.displayInfo();
    cat.displayInfo();
    
    cout << "\n=== 多态行为 ===" << endl;
    animal.makeSound();
    dog.makeSound();
    cat.makeSound();
    
    cout << "\n=== 移动行为 ===" << endl;
    animal.move();
    dog.move();
    cat.move();
    
    cout << "\n=== 特有行为 ===" << endl;
    dog.wagTail();
    dog.fetch();
    cat.purr();
    cat.climb();
    
    cout << "\n=== 共同行为 ===" << endl;
    animal.sleep();
    dog.sleep();  // 继承自基类
    cat.sleep();  // 继承自基类
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 继承方式详解
```cpp
class Base {
private:
    int privateData;
protected:
    int protectedData;
public:
    int publicData;
    
    Base() : privateData(1), protectedData(2), publicData(3) {}
    
    void showData() const {
        cout << "Base - private: " << privateData 
             << ", protected: " << protectedData 
             << ", public: " << publicData << endl;
    }
};

// public继承 - 最常用
class PublicDerived : public Base {
public:
    void accessMembers() {
        // privateData;     // 错误！不能访问基类private成员
        protectedData = 20; // 可以访问基类protected成员
        publicData = 30;    // 可以访问基类public成员
        
        cout << "PublicDerived访问成员" << endl;
    }
};

// protected继承 - 较少使用
class ProtectedDerived : protected Base {
public:
    void accessMembers() {
        // privateData;     // 错误！不能访问基类private成员
        protectedData = 200; // 可以访问
        publicData = 300;    // 可以访问，但外部访问级别变为protected
        
        cout << "ProtectedDerived访问成员" << endl;
    }
};

// private继承 - 表示"用...实现"关系
class PrivateDerived : private Base {
public:
    void accessMembers() {
        // privateData;     // 错误！不能访问基类private成员
        protectedData = 2000; // 可以访问
        publicData = 3000;    // 可以访问，但外部访问级别变为private
        
        cout << "PrivateDerived访问成员" << endl;
    }
    
    // 如果想要外部访问基类的某些public成员，可以使用using声明
    using Base::showData;  // 将基类的showData提升为public
};

void inheritanceModes() {
    cout << "\n=== 继承方式演示 ===" << endl;
    
    PublicDerived pd;
    ProtectedDerived protd;
    PrivateDerived privd;
    
    cout << "\n访问测试:" << endl;
    
    // public继承
    pd.publicData = 100;     // 可以访问
    pd.showData();           // 可以访问基类public方法
    pd.accessMembers();
    
    // protected继承
    // protd.publicData = 200;  // 错误！publicData在派生类中变为protected
    // protd.showData();        // 错误！showData在派生类中变为protected
    protd.accessMembers();
    
    // private继承
    // privd.publicData = 300;  // 错误！publicData在派生类中变为private
    privd.showData();           // 可以访问，因为使用了using声明
    privd.accessMembers();
}
```

### 构造和析构顺序
```cpp
class GrandParent {
public:
    GrandParent() { cout << "1. GrandParent构造函数" << endl; }
    virtual ~GrandParent() { cout << "6. GrandParent析构函数" << endl; }
};

class Parent : public GrandParent {
public:
    Parent() { cout << "2. Parent构造函数" << endl; }
    ~Parent() { cout << "5. Parent析构函数" << endl; }
};

class Child : public Parent {
public:
    Child() { cout << "3. Child构造函数" << endl; }
    ~Child() { cout << "4. Child析构函数" << endl; }
};

void constructionOrder() {
    cout << "\n=== 构造析构顺序演示 ===" << endl;
    
    cout << "创建Child对象:" << endl;
    {
        Child child;  // 构造顺序：GrandParent -> Parent -> Child
        cout << "Child对象创建完成" << endl;
    }  // 析构顺序：Child -> Parent -> GrandParent
    cout << "Child对象已销毁" << endl;
}
```

## 实践练习

### 练习1：图形继承体系
```cpp
#include <cmath>

// 抽象基类：形状
class Shape {
protected:
    double x, y;  // 位置坐标
    string color;
    
public:
    Shape(double x, double y, const string& c) 
        : x(x), y(y), color(c) {
        cout << "Shape构造: (" << x << "," << y << ") " << color << endl;
    }
    
    virtual ~Shape() {
        cout << "Shape析构: " << color << endl;
    }
    
    // 纯虚函数，派生类必须实现
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void draw() const = 0;
    
    // 虚函数，派生类可以重写
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        cout << color << "形状移动到 (" << x << "," << y << ")" << endl;
    }
    
    // 普通成员函数
    void setColor(const string& c) { color = c; }
    string getColor() const { return color; }
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    virtual void displayInfo() const {
        cout << color << "形状位于 (" << x << "," << y << ")" << endl;
    }
};

// 圆形类
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double x, double y, double r, const string& c = "红色") 
        : Shape(x, y, c), radius(r) {
        cout << "Circle构造: 半径=" << radius << endl;
    }
    
    ~Circle() {
        cout << "Circle析构: 半径=" << radius << endl;
    }
    
    // 实现纯虚函数
    double getArea() const override {
        return M_PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void draw() const override {
        cout << "绘制" << color << "圆形: 中心(" << x << "," << y 
             << "), 半径=" << radius << endl;
    }
    
    // 圆形特有的方法
    double getRadius() const { return radius; }
    void setRadius(double r) { 
        if (r > 0) radius = r; 
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        cout << "半径: " << radius << ", 面积: " << getArea() 
             << ", 周长: " << getPerimeter() << endl;
    }
};

// 矩形类
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double x, double y, double w, double h, const string& c = "蓝色") 
        : Shape(x, y, c), width(w), height(h) {
        cout << "Rectangle构造: " << width << "x" << height << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle析构: " << width << "x" << height << endl;
    }
    
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "绘制" << color << "矩形: 左上角(" << x << "," << y 
             << "), 大小=" << width << "x" << height << endl;
    }
    
    // 矩形特有的方法
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    void setWidth(double w) { if (w > 0) width = w; }
    void setHeight(double h) { if (h > 0) height = h; }
    
    void displayInfo() const override {
        Shape::displayInfo();
        cout << "尺寸: " << width << "x" << height 
             << ", 面积: " << getArea() 
             << ", 周长: " << getPerimeter() << endl;
    }
};

// 正方形类（继承自矩形）
class Square : public Rectangle {
public:
    Square(double x, double y, double side, const string& c = "绿色") 
        : Rectangle(x, y, side, side, c) {
        cout << "Square构造: 边长=" << side << endl;
    }
    
    ~Square() {
        cout << "Square析构" << endl;
    }
    
    void draw() const override {
        cout << "绘制" << color << "正方形: 左上角(" << x << "," << y 
             << "), 边长=" << getWidth() << endl;
    }
    
    // 正方形特有的方法
    double getSide() const { return getWidth(); }
    
    void setSide(double side) {
        setWidth(side);
        setHeight(side);
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        cout << "边长: " << getSide() 
             << ", 面积: " << getArea() 
             << ", 周长: " << getPerimeter() << endl;
    }
};

void exercise1() {
    cout << "\n=== 练习1：图形继承体系 ===" << endl;
    
    // 创建不同的图形对象
    Circle circle(0, 0, 5);
    Rectangle rect(10, 10, 8, 6);
    Square square(20, 20, 4);
    
    cout << "\n=== 图形信息 ===" << endl;
    circle.displayInfo();
    rect.displayInfo();
    square.displayInfo();
    
    cout << "\n=== 绘制图形 ===" << endl;
    circle.draw();
    rect.draw();
    square.draw();
    
    cout << "\n=== 移动图形 ===" << endl;
    circle.move(5, 5);
    rect.move(-2, 3);
    square.move(1, -1);
    
    cout << "\n=== 多态演示 ===" << endl;
    // 使用基类指针数组
    Shape* shapes[] = {&circle, &rect, &square};
    
    for (int i = 0; i < 3; i++) {
        cout << "形状 " << (i+1) << ": ";
        shapes[i]->draw();
        cout << "面积: " << shapes[i]->getArea() << endl;
    }
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 练习2：员工管理系统
```cpp
#include <vector>
#include <memory>

// 基类：员工
class Employee {
protected:
    int id;
    string name;
    string department;
    double baseSalary;
    
    static int nextId;  // 静态成员用于生成ID
    
public:
    Employee(const string& n, const string& dept, double salary) 
        : id(++nextId), name(n), department(dept), baseSalary(salary) {
        cout << "Employee构造: " << name << " (ID: " << id << ")" << endl;
    }
    
    virtual ~Employee() {
        cout << "Employee析构: " << name << endl;
    }
    
    // 纯虚函数：计算工资
    virtual double calculateSalary() const = 0;
    
    // 虚函数：显示信息
    virtual void displayInfo() const {
        cout << "ID: " << id << ", 姓名: " << name 
             << ", 部门: " << department << ", 基本工资: $" << baseSalary << endl;
    }
    
    // 虚函数：工作描述
    virtual string getJobDescription() const {
        return "通用员工工作";
    }
    
    // Getter方法
    int getId() const { return id; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    double getBaseSalary() const { return baseSalary; }
    
    // Setter方法
    void setName(const string& n) { name = n; }
    void setDepartment(const string& dept) { department = dept; }
    void setBaseSalary(double salary) { 
        if (salary > 0) baseSalary = salary; 
    }
};

int Employee::nextId = 0;

// 全职员工
class FullTimeEmployee : public Employee {
private:
    double bonus;
    int vacationDays;
    
public:
    FullTimeEmployee(const string& n, const string& dept, double salary, double b = 0) 
        : Employee(n, dept, salary), bonus(b), vacationDays(20) {
        cout << "FullTimeEmployee构造: " << name << endl;
    }
    
    ~FullTimeEmployee() {
        cout << "FullTimeEmployee析构: " << name << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary + bonus;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "类型: 全职员工, 奖金: $" << bonus 
             << ", 年假: " << vacationDays << "天" << endl;
        cout << "总工资: $" << calculateSalary() << endl;
    }
    
    string getJobDescription() const override {
        return "全职员工 - 负责日常运营工作";
    }
    
    // 全职员工特有方法
    double getBonus() const { return bonus; }
    void setBonus(double b) { if (b >= 0) bonus = b; }
    
    int getVacationDays() const { return vacationDays; }
    void setVacationDays(int days) { if (days >= 0) vacationDays = days; }
    
    void takeVacation(int days) {
        if (days <= vacationDays) {
            vacationDays -= days;
            cout << name << " 请假 " << days << " 天，剩余年假: " << vacationDays << " 天" << endl;
        } else {
            cout << name << " 年假不足，无法请假 " << days << " 天" << endl;
        }
    }
};

// 兼职员工
class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;
    
public:
    PartTimeEmployee(const string& n, const string& dept, double rate) 
        : Employee(n, dept, 0), hourlyRate(rate), hoursWorked(0) {
        cout << "PartTimeEmployee构造: " << name << endl;
    }
    
    ~PartTimeEmployee() {
        cout << "PartTimeEmployee析构: " << name << endl;
    }
    
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "类型: 兼职员工, 时薪: $" << hourlyRate 
             << ", 工作时长: " << hoursWorked << "小时" << endl;
        cout << "总工资: $" << calculateSalary() << endl;
    }
    
    string getJobDescription() const override {
        return "兼职员工 - 按小时计费的灵活工作";
    }
    
    // 兼职员工特有方法
    double getHourlyRate() const { return hourlyRate; }
    void setHourlyRate(double rate) { if (rate > 0) hourlyRate = rate; }
    
    int getHoursWorked() const { return hoursWorked; }
    void addWorkHours(int hours) { 
        if (hours > 0) hoursWorked += hours; 
    }
    void resetWorkHours() { hoursWorked = 0; }
};

// 经理（继承自全职员工）
class Manager : public FullTimeEmployee {
private:
    vector<Employee*> subordinates;
    double managementBonus;
    
public:
    Manager(const string& n, const string& dept, double salary, double mgmtBonus) 
        : FullTimeEmployee(n, dept, salary), managementBonus(mgmtBonus) {
        cout << "Manager构造: " << name << endl;
    }
    
    ~Manager() {
        cout << "Manager析构: " << name << endl;
    }
    
    double calculateSalary() const override {
        double teamBonus = subordinates.size() * 500;  // 每个下属500奖金
        return FullTimeEmployee::calculateSalary() + managementBonus + teamBonus;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "类型: 经理, 管理奖金: $" << managementBonus 
             << ", 团队人数: " << subordinates.size() << endl;
        cout << "总工资: $" << calculateSalary() << endl;
    }
    
    string getJobDescription() const override {
        return "经理 - 负责团队管理和项目协调";
    }
    
    // 经理特有方法
    void addSubordinate(Employee* emp) {
        subordinates.push_back(emp);
        cout << name << " 现在管理 " << emp->getName() << endl;
    }
    
    void removeSubordinate(Employee* emp) {
        auto it = find(subordinates.begin(), subordinates.end(), emp);
        if (it != subordinates.end()) {
            subordinates.erase(it);
            cout << name << " 不再管理 " << emp->getName() << endl;
        }
    }
    
    vector<Employee*> getSubordinates() const {
        return subordinates;
    }
    
    void holdTeamMeeting() {
        cout << name << " 召开团队会议，参与人员:" << endl;
        for (const auto& emp : subordinates) {
            cout << "  - " << emp->getName() << endl;
        }
    }
};

void exercise2() {
    cout << "\n=== 练习2：员工管理系统 ===" << endl;
    
    // 创建不同类型的员工
    FullTimeEmployee ft1("张三", "开发部", 8000, 1000);
    FullTimeEmployee ft2("李四", "测试部", 7000, 800);
    PartTimeEmployee pt1("王五", "设计部", 50);  // 时薪50
    PartTimeEmployee pt2("赵六", "市场部", 45);  // 时薪45
    Manager mgr("陈经理", "技术部", 12000, 2000);
    
    cout << "\n=== 员工信息 ===" << endl;
    ft1.displayInfo();
    cout << endl;
    
    ft2.displayInfo();
    cout << endl;
    
    // 兼职员工工作记录
    pt1.addWorkHours(80);
    pt1.displayInfo();
    cout << endl;
    
    pt2.addWorkHours(60);
    pt2.displayInfo();
    cout << endl;
    
    // 经理管理团队
    mgr.addSubordinate(&ft1);
    mgr.addSubordinate(&ft2);
    mgr.addSubordinate(&pt1);
    mgr.displayInfo();
    cout << endl;
    
    cout << "\n=== 工作场景 ===" << endl;
    // 请假
    ft1.takeVacation(5);
    
    // 团队会议
    mgr.holdTeamMeeting();
    
    // 多态演示
    cout << "\n=== 多态演示 ===" << endl;
    vector<Employee*> employees = {&ft1, &ft2, &pt1, &pt2, &mgr};
    
    double totalPayroll = 0;
    for (const auto& emp : employees) {
        cout << emp->getName() << ": " << emp->getJobDescription() << endl;
        totalPayroll += emp->calculateSalary();
    }
    
    cout << "\n总工资支出: $" << totalPayroll << endl;
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 练习3：多重继承示例
```cpp
// 多重继承示例：飞行器
class Flyable {
public:
    virtual ~Flyable() = default;
    virtual void fly() const = 0;
    virtual double getMaxAltitude() const = 0;
};

class Swimmable {
public:
    virtual ~Swimmable() = default;
    virtual void swim() const = 0;
    virtual double getMaxDepth() const = 0;
};

// 基础载具类
class Vehicle {
protected:
    string name;
    double speed;
    
public:
    Vehicle(const string& n, double s) : name(n), speed(s) {
        cout << "Vehicle构造: " << name << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle析构: " << name << endl;
    }
    
    virtual void move() const {
        cout << name << " 以 " << speed << " km/h 的速度移动" << endl;
    }
    
    string getName() const { return name; }
    double getSpeed() const { return speed; }
};

// 鸭子 - 多重继承示例
class Duck : public Vehicle, public Flyable, public Swimmable {
private:
    bool isWild;
    
public:
    Duck(const string& n, bool wild = true) 
        : Vehicle(n, 50), isWild(wild) {
        cout << "Duck构造: " << name << (isWild ? " (野鸭)" : " (家鸭)") << endl;
    }
    
    ~Duck() {
        cout << "Duck析构: " << name << endl;
    }
    
    // 实现Flyable接口
    void fly() const override {
        cout << name << " 振翅飞翔" << endl;
    }
    
    double getMaxAltitude() const override {
        return isWild ? 3000.0 : 100.0;  // 野鸭飞得更高
    }
    
    // 实现Swimmable接口
    void swim() const override {
        cout << name << " 在水中游泳" << endl;
    }
    
    double getMaxDepth() const override {
        return 5.0;  // 鸭子潜水深度有限
    }
    
    // 重写Vehicle的move方法
    void move() const override {
        cout << name << " 可以走路、游泳和飞行" << endl;
    }
    
    // 鸭子特有行为
    void quack() const {
        cout << name << " 嘎嘎叫" << endl;
    }
    
    bool getIsWild() const { return isWild; }
};

// 潜水艇 - 只能游泳
class Submarine : public Vehicle, public Swimmable {
private:
    int crewSize;
    
public:
    Submarine(const string& n, int crew) 
        : Vehicle(n, 30), crewSize(crew) {
        cout << "Submarine构造: " << name << " (船员: " << crewSize << ")" << endl;
    }
    
    ~Submarine() {
        cout << "Submarine析构: " << name << endl;
    }
    
    void swim() const override {
        cout << name << " 在水下潜行" << endl;
    }
    
    double getMaxDepth() const override {
        return 200.0;  // 潜水艇可以潜得很深
    }
    
    void move() const override {
        cout << name << " 在水中以 " << speed << " km/h 的速度航行" << endl;
    }
    
    void dive() const {
        cout << name << " 开始下潜" << endl;
    }
    
    void surface() const {
        cout << name << " 上浮到水面" << endl;
    }
    
    int getCrewSize() const { return crewSize; }
};

void exercise3() {
    cout << "\n=== 练习3：多重继承示例 ===" << endl;
    
    Duck duck("唐老鸭", false);
    Submarine sub("海狼号", 50);
    
    cout << "\n=== 基本信息 ===" << endl;
    cout << duck.getName() << " - 速度: " << duck.getSpeed() << " km/h" << endl;
    cout << sub.getName() << " - 速度: " << sub.getSpeed() << " km/h, 船员: " << sub.getCrewSize() << endl;
    
    cout << "\n=== 移动能力 ===" << endl;
    duck.move();
    sub.move();
    
    cout << "\n=== 飞行能力 ===" << endl;
    duck.fly();
    cout << duck.getName() << " 最大飞行高度: " << duck.getMaxAltitude() << " 米" << endl;
    
    cout << "\n=== 游泳能力 ===" << endl;
    duck.swim();
    cout << duck.getName() << " 最大潜水深度: " << duck.getMaxDepth() << " 米" << endl;
    
    sub.swim();
    cout << sub.getName() << " 最大潜水深度: " << sub.getMaxDepth() << " 米" << endl;
    
    cout << "\n=== 特有行为 ===" << endl;
    duck.quack();
    sub.dive();
    sub.surface();
    
    cout << "\n=== 多态演示 ===" << endl;
    // 使用接口指针
    Flyable* flyer = &duck;
    flyer->fly();
    
    Swimmable* swimmers[] = {&duck, &sub};
    for (int i = 0; i < 2; i++) {
        swimmers[i]->swim();
        cout << "最大深度: " << swimmers[i]->getMaxDepth() << " 米" << endl;
    }
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

## 学习检查点

- [ ] 理解继承的基本概念和is-a关系
- [ ] 掌握三种继承方式的区别和使用场景
- [ ] 了解派生类的构造和析构顺序
- [ ] 能够正确重写基类的虚函数
- [ ] 理解成员访问权限在继承中的变化
- [ ] 掌握多重继承的语法和注意事项
- [ ] 能够设计合理的类继承体系
- [ ] 理解继承在多态中的作用

## 完整示例程序

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    cout << "=== C++ 继承学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        inheritanceBasics();
        inheritanceModes();
        constructionOrder();
        
        exercise1();
        exercise2();
        exercise3();
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
    
    cout << "\n程序结束" << endl;
    return 0;
}
```

[返回第二周](/plan/week2/) | [上一天：构造函数与析构函数](/plan/week2/day9/) | [下一天：虚函数与多态](/plan/week2/day11/)
