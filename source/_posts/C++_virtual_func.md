---
title: C++ virtual function
date: 2025-09-01 18:00:00
categories: Cpp
tags:
    - C++
    - Virtual Function
    - Polymorphism
---
# C++ virtual function
## 虚函数表 （vtable）
1. 每个包含虚函数的类都有一个虚函数表，表中存储着该类的所有虚函数地址。
2. 每个对象实例包含一个指向其类的虚函数表的指针（vptr）。
3. 当通过基类指针调用虚函数时，程序会通过vptr找到vtable，然后调用正确的函数实现，实现动态绑定。

```cpp
class Base {
public:
    virtual void func1() { cout << "Base func1" << endl; }
    virtual void func2() { cout << "Base func2" << endl; }
};
class Derived : public Base {
public:
    void func1() override { cout << "Derived func1" << endl; }
};

int main() {
    Base* b = new Derived();
    b->func1(); // Calls Derived::func1
    b->func2(); // Calls Base::func2
    delete b;
    return 0;
}
```

## 多重继承对vtable的影响
1. 每个基类都有自己的vtable，因此多重继承的类会有多个vtable。
2. 对象实例会包含多个vptr，分别指向各个基类的vtable。
3. 调用虚函数时，程序会根据调用的基类类型选择对应的vtable。

```cpp
class Base1 {
public:
    virtual void func1() { cout << "Base1 func1" << endl; }
};
class Base2 {
public:
    virtual void func2() { cout << "Base2 func2" << endl; }
};
class Derived : public Base1, public Base2 {
public:
    void func1() override { cout << "Derived func1" << endl; }
    void func2() override { cout << "Derived func2" << endl; }
};  
int main() {
    Derived d;
    Base1* b1 = &d;
    Base2* b2 = &d;
    b1->func1(); // Calls Derived::func1
    b2->func2(); // Calls Derived::func2
    return 0;
}
```

## 虚继承对vtable的影响
1. 虚继承用于解决菱形继承问题，确保共享的基类只有一份实例。
2. 虚继承的类会有一个额外的指针，用于指向共享的基类实例。
3. vtable结构会更复杂，以支持虚继承的动态绑定。
4. 调用虚函数时，程序会正确处理共享基类的函数调用。

共享基类对象：所有虚继承的派生类共享同一个基类对象实例
构造顺序：虚基类总是在非虚基类之前构造
初始化责任：最终派生类负责直接初始化虚基类
```cpp
class Base {
public:
    virtual void func() { cout << "Base func" << endl; }
};
class Derived1 : virtual public Base {
public:
    void func() override { cout << "Derived1 func" << endl; }
    void func1() { cout << "Derived1 func1" << endl; }
};
class Derived2 : virtual public Base {
public:
    void func() override { cout << "Derived2 func" << endl; }
    void func2() { cout << "Derived2 func2" << endl; }
};
class MostDerived : public Derived1, public Derived2 {
public:
    
};
int main() {
    MostDerived md;
    Base* b = &md;
    b->func(); // Error because both Derived1 and Derived2 override func
    return 0;
}
```
