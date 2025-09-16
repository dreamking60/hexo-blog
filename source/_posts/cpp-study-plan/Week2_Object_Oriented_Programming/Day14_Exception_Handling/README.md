# 第14天：异常处理

## 学习目标
掌握C++异常处理机制，理解try-catch-throw的使用，学会设计异常安全的代码，掌握RAII与异常安全的结合。

## 学习内容

### 1. 异常处理的基本概念
异常处理是处理程序运行时错误的重要机制。

```cpp
try {
    // 可能抛出异常的代码
    riskyFunction();
} catch (const std::exception& e) {
    // 处理异常
    std::cout << "Exception caught: " << e.what() << std::endl;
} catch (...) {
    // 处理所有其他异常
    std::cout << "Unknown exception caught" << std::endl;
}
```

### 2. 抛出异常
```cpp
void divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}
```

### 3. 标准异常类
```cpp
#include <stdexcept>

// 标准异常类
std::runtime_error
std::logic_error
std::invalid_argument
std::out_of_range
std::bad_alloc
```

## 实践练习

### 练习1：异常安全的资源管理
```cpp
#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;

class SafeResource {
private:
    int* resource;
    size_t size;
    
public:
    SafeResource(size_t s) : size(s) {
        cout << "SafeResource constructor: allocating " << size << " elements" << endl;
        
        if (size == 0) {
            resource = nullptr;
            return;
        }
        
        try {
            resource = new int[size];
            // 初始化为0
            for (size_t i = 0; i < size; ++i) {
                resource[i] = 0;
            }
        } catch (const bad_alloc& e) {
            cout << "Memory allocation failed: " << e.what() << endl;
            throw;
        }
    }
    
    ~SafeResource() {
        cout << "SafeResource destructor: freeing " << size << " elements" << endl;
        delete[] resource;
    }
    
    // 禁止拷贝，只允许移动
    SafeResource(const SafeResource&) = delete;
    SafeResource& operator=(const SafeResource&) = delete;
    
    // 移动构造函数
    SafeResource(SafeResource&& other) noexcept 
        : resource(other.resource), size(other.size) {
        cout << "SafeResource move constructor" << endl;
        other.resource = nullptr;
        other.size = 0;
    }
    
    // 移动赋值运算符
    SafeResource& operator=(SafeResource&& other) noexcept {
        cout << "SafeResource move assignment" << endl;
        if (this != &other) {
            delete[] resource;
            resource = other.resource;
            size = other.size;
            other.resource = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    void setValue(size_t index, int value) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        resource[index] = value;
    }
    
    int getValue(size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return resource[index];
    }
    
    void display() const {
        cout << "SafeResource (" << size << " elements): ";
        if (resource == nullptr) {
            cout << "null";
        } else {
            for (size_t i = 0; i < size; ++i) {
                cout << resource[i] << " ";
            }
        }
        cout << endl;
    }
};

// 异常安全的函数
void processResource(size_t size) {
    try {
        SafeResource resource(size);
        
        // 设置一些值
        for (size_t i = 0; i < size; ++i) {
            resource.setValue(i, static_cast<int>(i * 10));
        }
        
        resource.display();
        
        // 故意访问越界
        if (size > 0) {
            resource.setValue(size, 100);  // 这会抛出异常
        }
        
    } catch (const out_of_range& e) {
        cout << "Out of range error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Standard exception: " << e.what() << endl;
    } catch (...) {
        cout << "Unknown exception caught" << endl;
    }
}
```

### 练习2：自定义异常类
```cpp
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// 自定义异常类
class MathException : public std::exception {
private:
    string message;
    
public:
    MathException(const string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DivisionByZeroException : public MathException {
public:
    DivisionByZeroException() : MathException("Division by zero is not allowed") {}
};

class NegativeNumberException : public MathException {
public:
    NegativeNumberException() : MathException("Negative numbers are not allowed") {}
};

// 数学运算类
class MathOperations {
public:
    static double divide(double a, double b) {
        if (b == 0.0) {
            throw DivisionByZeroException();
        }
        return a / b;
    }
    
    static double squareRoot(double x) {
        if (x < 0) {
            throw NegativeNumberException();
        }
        return sqrt(x);
    }
    
    static double power(double base, double exponent) {
        if (base < 0 && exponent != floor(exponent)) {
            throw MathException("Negative base with non-integer exponent");
        }
        return pow(base, exponent);
    }
};

// 异常处理示例
void testMathOperations() {
    try {
        cout << "Testing division: " << MathOperations::divide(10, 2) << endl;
        cout << "Testing square root: " << MathOperations::squareRoot(16) << endl;
        cout << "Testing power: " << MathOperations::power(2, 3) << endl;
        
        // 这些会抛出异常
        MathOperations::divide(10, 0);
        
    } catch (const DivisionByZeroException& e) {
        cout << "Division error: " << e.what() << endl;
    } catch (const NegativeNumberException& e) {
        cout << "Negative number error: " << e.what() << endl;
    } catch (const MathException& e) {
        cout << "Math error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Standard error: " << e.what() << endl;
    }
}
```

## 算法题练习

### 1. 设计一个支持增量操作的栈 (Medium)
**题目链接**: https://leetcode.cn/problems/design-a-stack-with-increment-operation/

### 2. 设计循环双端队列 (Medium)
**题目链接**: https://leetcode.cn/problems/design-circular-deque/

### 3. 设计推特 (Medium)
**题目链接**: https://leetcode.cn/problems/design-twitter/

### 4. 设计前K个高频元素 (Medium)
**题目链接**: https://leetcode.cn/problems/top-k-frequent-elements/

## 学习要点总结

### 1. 异常处理的重要性
- 错误处理机制
- 程序健壮性
- 资源管理

### 2. 异常安全保证
- 基本保证
- 强保证
- 不抛出保证

### 3. RAII与异常安全
- 资源获取即初始化
- 自动资源管理
- 异常安全的设计

### 4. 异常处理的最佳实践
- 使用标准异常类
- 避免在析构函数中抛出异常
- 异常安全的代码设计

记住：异常处理是C++重要的错误处理机制，正确使用异常处理可以提高程序的健壮性！
