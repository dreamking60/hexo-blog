# 第10天：继承

## 学习目标
掌握C++继承机制，理解基类与派生类的关系，学会设计合理的继承层次，掌握函数重写和虚析构函数的使用。

## 学习内容

### 1. 继承的基本概念
继承是面向对象编程的核心特性之一，允许一个类（派生类）继承另一个类（基类）的成员。

#### 继承的语法
```cpp
class BaseClass {
    // 基类成员
};

class DerivedClass : access-specifier BaseClass {
    // 派生类成员
};
```

#### 访问控制符
- **public继承**：基类的public成员在派生类中仍为public，protected成员仍为protected
- **protected继承**：基类的public和protected成员在派生类中都变为protected
- **private继承**：基类的public和protected成员在派生类中都变为private

### 2. 基类与派生类
```cpp
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {}
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    void sleep() {
        cout << name << " is sleeping" << endl;
    }
    
    virtual void makeSound() {
        cout << name << " makes a sound" << endl;
    }
    
    virtual ~Animal() {}  // 虚析构函数
};

class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}
    
    void makeSound() override {  // 函数重写
        cout << name << " barks: Woof!" << endl;
    }
    
    void wagTail() {
        cout << name << " is wagging tail" << endl;
    }
    
    void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << ", Breed: " << breed << endl;
    }
};
```

### 3. 派生类的构造与析构
派生类的构造函数必须调用基类的构造函数，析构函数会自动调用基类的析构函数。

```cpp
class Base {
protected:
    int value;
    
public:
    Base(int v) : value(v) {
        cout << "Base constructor: " << value << endl;
    }
    
    ~Base() {
        cout << "Base destructor: " << value << endl;
    }
};

class Derived : public Base {
private:
    string name;
    
public:
    Derived(int v, string n) : Base(v), name(n) {
        cout << "Derived constructor: " << name << endl;
    }
    
    ~Derived() {
        cout << "Derived destructor: " << name << endl;
    }
};
```

### 4. 函数重写
派生类可以重写基类的虚函数，实现多态。

```cpp
class Shape {
protected:
    double x, y;
    
public:
    Shape(double x, double y) : x(x), y(y) {}
    
    virtual double area() const = 0;  // 纯虚函数
    virtual double perimeter() const = 0;  // 纯虚函数
    virtual void draw() const {
        cout << "Drawing a shape at (" << x << ", " << y << ")" << endl;
    }
    
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double x, double y, double r) : Shape(x, y), radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        cout << "Drawing a circle at (" << x << ", " << y << ") with radius " << radius << endl;
    }
};
```

### 5. 多重继承
C++支持多重继承，一个类可以继承多个基类。

```cpp
class Flyable {
public:
    virtual void fly() = 0;
    virtual ~Flyable() = default;
};

class Swimmable {
public:
    virtual void swim() = 0;
    virtual ~Swimmable() = default;
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(string n, int a) : Animal(n, a) {}
    
    void makeSound() override {
        cout << name << " quacks: Quack!" << endl;
    }
    
    void fly() override {
        cout << name << " is flying" << endl;
    }
    
    void swim() override {
        cout << name << " is swimming" << endl;
    }
};
```

## 实践练习

### 练习1：图形类继承体系
实现一个完整的图形类继承体系，包括基类和多个派生类。

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
using namespace std;

// 基类：图形
class Shape {
protected:
    double x, y;  // 位置坐标
    
public:
    Shape(double x = 0, double y = 0) : x(x), y(y) {
        cout << "Shape constructor at (" << x << ", " << y << ")" << endl;
    }
    
    virtual double area() const = 0;  // 纯虚函数
    virtual double perimeter() const = 0;  // 纯虚函数
    virtual void draw() const {
        cout << "Drawing a shape at (" << x << ", " << y << ")" << endl;
    }
    
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        cout << "Shape moved to (" << x << ", " << y << ")" << endl;
    }
    
    virtual ~Shape() {
        cout << "Shape destructor" << endl;
    }
};

// 派生类：圆形
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double x, double y, double r) : Shape(x, y), radius(r) {
        cout << "Circle constructor with radius " << radius << endl;
    }
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void draw() const override {
        cout << "Drawing a circle at (" << x << ", " << y << ") with radius " << radius << endl;
    }
    
    double getRadius() const { return radius; }
    void setRadius(double r) { radius = r; }
    
    ~Circle() {
        cout << "Circle destructor" << endl;
    }
};

// 派生类：矩形
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double x, double y, double w, double h) : Shape(x, y), width(w), height(h) {
        cout << "Rectangle constructor with width " << width << " and height " << height << endl;
    }
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "Drawing a rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }
    
    ~Rectangle() {
        cout << "Rectangle destructor" << endl;
    }
};

// 派生类：三角形
class Triangle : public Shape {
private:
    double side1, side2, side3;
    
public:
    Triangle(double x, double y, double s1, double s2, double s3) 
        : Shape(x, y), side1(s1), side2(s2), side3(s3) {
        cout << "Triangle constructor with sides " << side1 << ", " << side2 << ", " << side3 << endl;
    }
    
    double area() const override {
        // 使用海伦公式
        double s = perimeter() / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    
    double perimeter() const override {
        return side1 + side2 + side3;
    }
    
    void draw() const override {
        cout << "Drawing a triangle at (" << x << ", " << y << ") with sides " << side1 << ", " << side2 << ", " << side3 << endl;
    }
    
    double getSide1() const { return side1; }
    double getSide2() const { return side2; }
    double getSide3() const { return side3; }
    
    ~Triangle() {
        cout << "Triangle destructor" << endl;
    }
};

// 图形管理器类
class ShapeManager {
private:
    vector<unique_ptr<Shape>> shapes;
    
public:
    void addShape(unique_ptr<Shape> shape) {
        shapes.push_back(std::move(shape));
    }
    
    void drawAll() const {
        cout << "\n=== 绘制所有图形 ===" << endl;
        for (const auto& shape : shapes) {
            shape->draw();
        }
    }
    
    void moveAll(double dx, double dy) {
        cout << "\n=== 移动所有图形 ===" << endl;
        for (const auto& shape : shapes) {
            shape->move(dx, dy);
        }
    }
    
    double getTotalArea() const {
        double total = 0;
        for (const auto& shape : shapes) {
            total += shape->area();
        }
        return total;
    }
    
    double getTotalPerimeter() const {
        double total = 0;
        for (const auto& shape : shapes) {
            total += shape->perimeter();
        }
        return total;
    }
    
    void displaySummary() const {
        cout << "\n=== 图形统计 ===" << endl;
        cout << "总图形数量: " << shapes.size() << endl;
        cout << "总面积: " << getTotalArea() << endl;
        cout << "总周长: " << getTotalPerimeter() << endl;
    }
};
```

### 练习2：车辆继承体系
实现一个车辆类的继承体系，演示不同类型的车辆。

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 基类：车辆
class Vehicle {
protected:
    string brand;
    string model;
    int year;
    double price;
    
public:
    Vehicle(string b, string m, int y, double p) 
        : brand(b), model(m), year(y), price(p) {
        cout << "Vehicle constructor: " << brand << " " << model << endl;
    }
    
    virtual void start() {
        cout << brand << " " << model << " is starting..." << endl;
    }
    
    virtual void stop() {
        cout << brand << " " << model << " is stopping..." << endl;
    }
    
    virtual void displayInfo() const {
        cout << "Brand: " << brand << ", Model: " << model 
             << ", Year: " << year << ", Price: $" << price << endl;
    }
    
    virtual double calculateTax() const {
        return price * 0.1;  // 10% 税率
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle destructor: " << brand << " " << model << endl;
    }
};

// 派生类：汽车
class Car : public Vehicle {
private:
    int doors;
    string fuelType;
    
public:
    Car(string b, string m, int y, double p, int d, string f) 
        : Vehicle(b, m, y, p), doors(d), fuelType(f) {
        cout << "Car constructor: " << doors << " doors, " << fuelType << " fuel" << endl;
    }
    
    void start() override {
        cout << brand << " " << model << " car is starting with key..." << endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Doors: " << doors << ", Fuel Type: " << fuelType << endl;
    }
    
    double calculateTax() const override {
        return price * 0.12;  // 汽车税率12%
    }
    
    void openTrunk() {
        cout << brand << " " << model << " trunk is opened" << endl;
    }
    
    ~Car() {
        cout << "Car destructor" << endl;
    }
};

// 派生类：摩托车
class Motorcycle : public Vehicle {
private:
    string engineType;
    bool hasWindshield;
    
public:
    Motorcycle(string b, string m, int y, double p, string e, bool w) 
        : Vehicle(b, m, y, p), engineType(e), hasWindshield(w) {
        cout << "Motorcycle constructor: " << engineType << " engine" << endl;
    }
    
    void start() override {
        cout << brand << " " << model << " motorcycle is starting with kick..." << endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Engine Type: " << engineType << ", Windshield: " 
             << (hasWindshield ? "Yes" : "No") << endl;
    }
    
    double calculateTax() const override {
        return price * 0.08;  // 摩托车税率8%
    }
    
    void wheelie() {
        cout << brand << " " << model << " is doing a wheelie!" << endl;
    }
    
    ~Motorcycle() {
        cout << "Motorcycle destructor" << endl;
    }
};

// 派生类：卡车
class Truck : public Vehicle {
private:
    double cargoCapacity;
    int axles;
    
public:
    Truck(string b, string m, int y, double p, double c, int a) 
        : Vehicle(b, m, y, p), cargoCapacity(c), axles(a) {
        cout << "Truck constructor: " << cargoCapacity << " tons capacity, " << axles << " axles" << endl;
    }
    
    void start() override {
        cout << brand << " " << model << " truck is starting with air brakes..." << endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Cargo Capacity: " << cargoCapacity << " tons, Axles: " << axles << endl;
    }
    
    double calculateTax() const override {
        return price * 0.15;  // 卡车税率15%
    }
    
    void loadCargo(double weight) {
        if (weight <= cargoCapacity) {
            cout << brand << " " << model << " loaded " << weight << " tons of cargo" << endl;
        } else {
            cout << "Cargo weight exceeds capacity!" << endl;
        }
    }
    
    ~Truck() {
        cout << "Truck destructor" << endl;
    }
};

// 车辆展示类
class VehicleShowroom {
private:
    vector<unique_ptr<Vehicle>> vehicles;
    
public:
    void addVehicle(unique_ptr<Vehicle> vehicle) {
        vehicles.push_back(std::move(vehicle));
    }
    
    void displayAllVehicles() const {
        cout << "\n=== 车辆展示 ===" << endl;
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
            cout << "Tax: $" << vehicle->calculateTax() << endl;
            cout << "---" << endl;
        }
    }
    
    void testAllVehicles() {
        cout << "\n=== 车辆测试 ===" << endl;
        for (const auto& vehicle : vehicles) {
            vehicle->start();
            vehicle->stop();
            cout << "---" << endl;
        }
    }
    
    double getTotalValue() const {
        double total = 0;
        for (const auto& vehicle : vehicles) {
            total += vehicle->calculateTax();
        }
        return total;
    }
};
```

## 算法题练习

### 1. 二叉搜索树的最近公共祖先 (Medium)
**题目链接**: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

**关键点**：
- 理解二叉搜索树的性质
- 最近公共祖先的概念
- 递归和迭代两种解法

### 2. 删除二叉搜索树中的节点 (Medium)
**题目链接**: https://leetcode.cn/problems/delete-node-in-a-bst/

给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。

**关键点**：
- 二叉搜索树的删除操作
- 三种情况的处理
- 递归实现

### 3. 验证二叉搜索树 (Medium)
**题目链接**: https://leetcode.cn/problems/validate-binary-search-tree/

给定一个二叉树，判断其是否是一个有效的二叉搜索树。

**关键点**：
- 二叉搜索树的性质
- 中序遍历验证
- 递归边界处理

### 4. 二叉搜索树中的插入操作 (Medium)
**题目链接**: https://leetcode.cn/problems/insert-into-a-binary-search-tree/

给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。

**关键点**：
- 二叉搜索树的插入规则
- 递归和迭代实现
- 保持BST性质

## 学习要点总结

### 1. 继承的设计原则
- **is-a关系**：派生类应该是基类的特化
- **里氏替换原则**：派生类对象应该能够替换基类对象
- **单一职责**：每个类应该有明确的职责

### 2. 访问控制的重要性
- **public继承**：表示is-a关系
- **protected继承**：表示implemented-in-terms-of关系
- **private继承**：表示implemented-in-terms-of关系

### 3. 虚函数和纯虚函数
- **虚函数**：可以被重写，提供默认实现
- **纯虚函数**：必须被重写，定义抽象接口
- **抽象类**：包含纯虚函数的类，不能实例化

### 4. 虚析构函数的重要性
- **基类析构函数应该是虚函数**
- **确保正确的析构顺序**
- **避免内存泄漏**

## 扩展练习

1. 实现一个动物类的继承体系
2. 设计一个员工管理系统的继承层次
3. 实现一个游戏角色的继承体系
4. 设计一个文件系统的继承结构

## 学习检查

完成今天的学习后，你应该能够：
- [ ] 理解继承的基本概念
- [ ] 掌握派生类的构造和析构
- [ ] 会设计合理的继承层次
- [ ] 理解函数重写的机制
- [ ] 掌握虚析构函数的使用
- [ ] 完成4道算法题

记住：继承是代码复用的重要手段，但不要过度使用。优先考虑组合而不是继承！
