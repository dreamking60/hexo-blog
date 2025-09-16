#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

// 练习1：图形类继承体系
class Shape {
protected:
    double x, y;
    
public:
    Shape(double x = 0, double y = 0) : x(x), y(y) {
        cout << "Shape constructor at (" << x << ", " << y << ")" << endl;
    }
    
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
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

// 练习2：动物类继承体系
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "Animal constructor: " << name << endl;
    }
    
    virtual void makeSound() = 0;
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
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "Dog constructor: " << breed << " breed" << endl;
    }
    
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
    Bird(string n, int a, bool fly) : Animal(n, a), canFly(fly) {
        cout << "Bird constructor: can fly = " << (canFly ? "Yes" : "No") << endl;
    }
    
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

// 主函数测试
int main() {
    cout << "=== 图形类继承体系测试 ===" << endl;
    {
        vector<unique_ptr<Shape>> shapes;
        
        shapes.push_back(make_unique<Circle>(0, 0, 5.0));
        shapes.push_back(make_unique<Rectangle>(10, 10, 8.0, 6.0));
        
        cout << "\n绘制所有图形:" << endl;
        for (const auto& shape : shapes) {
            shape->draw();
            cout << "Area: " << shape->area() << ", Perimeter: " << shape->perimeter() << endl;
        }
        
        cout << "\n移动所有图形:" << endl;
        for (const auto& shape : shapes) {
            shape->move(5, 5);
        }
    }
    
    cout << "\n=== 动物类继承体系测试 ===" << endl;
    {
        vector<unique_ptr<Animal>> animals;
        
        animals.push_back(make_unique<Dog>("Buddy", 3, "Golden Retriever"));
        animals.push_back(make_unique<Bird>("Tweety", 1, true));
        
        cout << "\n动物信息:" << endl;
        for (const auto& animal : animals) {
            animal->displayInfo();
            animal->makeSound();
            animal->move();
            cout << "---" << endl;
        }
        
        // 测试多态
        cout << "\n多态测试:" << endl;
        Animal* dog = new Dog("Rex", 5, "German Shepherd");
        Animal* bird = new Bird("Polly", 2, false);
        
        dog->makeSound();
        bird->makeSound();
        
        delete dog;
        delete bird;
    }
    
    return 0;
}
