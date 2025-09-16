# 第5天：引用

## 学习目标
掌握引用的概念和使用场景，理解引用与指针的区别，学会正确使用引用。

## 学习内容

### 1. 引用的基本概念
- 引用的定义与声明
- 引用的初始化
- 引用与变量的关系
- 引用的特点
- 引用的限制

### 2. 引用与指针的区别
- 语法差异
- 语义差异
- 使用场景差异
- 性能差异
- 安全性差异

### 3. 引用作为函数参数
- 引用传递的优势
- 避免拷贝开销
- 修改原变量
- 常量引用
- 引用参数的最佳实践

### 4. 引用作为返回值
- 返回引用的函数
- 返回引用的注意事项
- 链式操作
- 返回引用的生命周期
- 避免返回局部变量的引用

### 5. 引用的高级应用
- 引用成员变量
- 引用与const
- 引用与模板
- 引用与重载
- 引用与移动语义

## 重点概念

### 引用的基本操作
```cpp
int x = 10;
int& ref = x;        // 引用声明并初始化
cout << "x的值: " << x << endl;
cout << "ref的值: " << ref << endl;
cout << "x的地址: " << &x << endl;
cout << "ref的地址: " << &ref << endl;  // 与x的地址相同

// 通过引用修改值
ref = 20;
cout << "通过引用修改后，x的值: " << x << endl;
```

### 引用与指针的区别
```cpp
int x = 10;

// 指针方式
int* ptr = &x;
cout << "指针值: " << ptr << endl;
cout << "指针指向的值: " << *ptr << endl;
ptr = nullptr;  // 可以重新赋值

// 引用方式
int& ref = x;
cout << "引用值: " << ref << endl;
// ref = nullptr;  // 错误：引用不能重新赋值
// int& ref2;      // 错误：引用必须初始化
```

### 引用作为函数参数
```cpp
// 值传递（会拷贝）
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// 指针传递（需要解引用）
void swapByPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用传递（推荐方式）
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 常量引用（只读，避免拷贝）
void printValue(const int& value) {
    cout << "值: " << value << endl;
    // value = 100;  // 错误：不能修改常量引用
}
```

### 引用作为返回值
```cpp
class Counter {
private:
    int count;
public:
    Counter(int c = 0) : count(c) {}
    
    // 返回引用，可以链式操作
    Counter& increment() {
        count++;
        return *this;
    }
    
    // 返回引用，可以修改
    int& getCount() {
        return count;
    }
    
    // 返回常量引用，只读
    const int& getCount() const {
        return count;
    }
    
    void print() const {
        cout << "Count: " << count << endl;
    }
};

// 使用示例
Counter c(5);
c.increment().increment().increment();  // 链式操作
c.print();  // 输出: Count: 8

c.getCount() = 100;  // 通过引用修改
c.print();  // 输出: Count: 100
```

### 引用与const
```cpp
int x = 10;
const int& ref1 = x;        // 常量引用，不能通过ref1修改x
int& ref2 = x;              // 普通引用，可以通过ref2修改x

// ref1 = 20;               // 错误：不能修改常量引用
ref2 = 20;                  // 正确：可以修改普通引用

const int y = 20;
// int& ref3 = y;           // 错误：不能用普通引用绑定常量
const int& ref4 = y;        // 正确：可以用常量引用绑定常量
```

## 引用的高级应用

### 1. 引用成员变量
```cpp
class Person {
private:
    string& name;  // 引用成员变量
    int age;
public:
    Person(string& n, int a) : name(n), age(a) {}
    
    void print() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// 使用
string personName = "Alice";
Person p(personName, 25);
p.print();
```

### 2. 引用与模板
```cpp
template<typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 使用
int x = 10, y = 20;
swapValues(x, y);  // 自动推导类型
cout << "x: " << x << ", y: " << y << endl;
```

### 3. 引用与重载
```cpp
class MyClass {
public:
    void process(int& value) {
        cout << "处理左值引用: " << value << endl;
    }
    
    void process(const int& value) {
        cout << "处理常量引用: " << value << endl;
    }
    
    void process(int&& value) {
        cout << "处理右值引用: " << value << endl;
    }
};

// 使用
MyClass obj;
int x = 10;
obj.process(x);           // 调用左值引用版本
obj.process(20);          // 调用右值引用版本
obj.process(static_cast<const int&>(x));  // 调用常量引用版本
```

## 实践练习

### 练习1：引用基本操作
实现引用的各种基本操作。

### 练习2：引用作为函数参数
实现各种引用传递的函数。

### 练习3：引用作为返回值
实现返回引用的函数。

### 练习4：引用与const
实现常量引用的使用。

## 常见错误与注意事项

1. **引用未初始化**：引用必须在声明时初始化
2. **引用重新赋值**：引用不能重新绑定到其他变量
3. **返回局部变量引用**：返回局部变量的引用会导致未定义行为
4. **引用与指针混淆**：引用不是指针，不能进行指针运算
5. **常量引用绑定非常量**：常量引用可以绑定非常量，但反之不行

## 最佳实践

1. **优先使用引用**：在C++中优先使用引用而不是指针
2. **常量引用传参**：对于大对象使用常量引用避免拷贝
3. **避免返回局部引用**：不要返回局部变量的引用
4. **明确引用语义**：使用引用时要明确其语义
5. **合理使用const**：根据需要使用const修饰引用

## 学习检查点

- [ ] 理解引用的基本概念和特点
- [ ] 掌握引用与指针的区别
- [ ] 能够正确使用引用作为函数参数
- [ ] 理解引用作为返回值的用法和注意事项
- [ ] 掌握常量引用的使用
- [ ] 了解引用的高级应用场景

## 扩展阅读

- C++ Primer 第2章：变量和基本类型
- Effective C++ 条款20：宁以pass-by-reference-to-const替换pass-by-value
- 了解右值引用和移动语义
