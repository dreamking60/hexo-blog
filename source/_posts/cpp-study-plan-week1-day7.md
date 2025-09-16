---
title: C++ 学习计划 - 第7天：const关键字
date: 2025-09-16 10:17:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week1
    - Day7
layout: page
menu_id: plan
permalink: /plan/week1/day7/
---

# 第7天：const关键字

## 学习目标
深入理解const关键字的各种用法，掌握常量安全编程，学会在不同场景下正确使用const。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - const](https://en.cppreference.com/w/cpp/language/const) - C++官方const文档
- [LearnCpp - const](https://www.learncpp.com/cpp-tutorial/const-variables-and-symbolic-constants/) - const详解教程
- [GeeksforGeeks - const in C++](https://www.geeksforgeeks.org/const-keyword-in-cpp/) - const关键字用法

### 🎥 视频教程
- [The Cherno C++ const](https://www.youtube.com/watch?v=4fJBrditnJU) - const概念深入讲解
- [C++ const Correctness](https://www.youtube.com/watch?v=RC7uE_wl1Uc) - const正确性

### 📖 深入阅读
- [C++ Primer 第5版 - 第2.4节](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - const限定符
- [Effective C++ - 条款3](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 尽可能使用const
- [More Effective C++ - 条款21](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X) - 利用const的威力

## 学习内容

### 1. const变量
- const变量的声明和初始化
- 编译时常量 vs 运行时常量
- const与字面量类型
- const变量的作用域

### 2. const指针
- 指向常量的指针
- 常量指针
- 指向常量的常量指针
- const指针的转换规则

### 3. const引用
- 常量引用的声明
- 临时对象绑定
- 参数传递中的const引用
- const引用的生命周期

### 4. const成员函数
- const成员函数的声明
- const对象的方法调用
- mutable关键字
- const重载

### 5. const_cast转换
- const_cast的用法
- 去除const限定
- 使用场景和注意事项
- const安全性

## 重点概念和代码示例

### const变量基础
```cpp
#include <iostream>
using namespace std;

void constVariables() {
    cout << "=== const变量基础 ===" << endl;
    
    // 编译时常量
    const int MAX_SIZE = 100;
    const double PI = 3.14159;
    
    // 运行时常量
    int input = 42;
    const int runtime_const = input * 2;
    
    cout << "MAX_SIZE = " << MAX_SIZE << endl;
    cout << "PI = " << PI << endl;
    cout << "runtime_const = " << runtime_const << endl;
    
    // const变量必须初始化
    // const int uninitialized;  // 错误！
    
    // 数组大小可以使用const变量
    const int ARRAY_SIZE = 5;
    int array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    
    cout << "数组内容: ";
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    
    // const与auto
    auto x = 42;        // x是int类型
    const auto y = 42;  // y是const int类型
    auto z = MAX_SIZE;  // z是int类型（const被忽略）
    
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}
```

### const指针详解
```cpp
void constPointers() {
    cout << "\n=== const指针详解 ===" << endl;
    
    int value1 = 10, value2 = 20;
    
    // 1. 指向常量的指针（pointer to const）
    const int* ptr1 = &value1;
    cout << "指向常量的指针: *ptr1 = " << *ptr1 << endl;
    // *ptr1 = 30;  // 错误！不能通过ptr1修改值
    ptr1 = &value2;  // 可以改变指向
    cout << "改变指向后: *ptr1 = " << *ptr1 << endl;
    
    // 2. 常量指针（const pointer）
    int* const ptr2 = &value1;
    cout << "常量指针: *ptr2 = " << *ptr2 << endl;
    *ptr2 = 30;  // 可以修改指向的值
    // ptr2 = &value2;  // 错误！不能改变指向
    cout << "修改值后: *ptr2 = " << *ptr2 << endl;
    
    // 3. 指向常量的常量指针（const pointer to const）
    const int* const ptr3 = &value2;
    cout << "指向常量的常量指针: *ptr3 = " << *ptr3 << endl;
    // *ptr3 = 40;     // 错误！不能修改值
    // ptr3 = &value1; // 错误！不能改变指向
    
    // 4. 指针和const的位置关系
    cout << "\n指针声明分析:" << endl;
    cout << "const int* p1;        // 指向常量的指针" << endl;
    cout << "int const* p2;        // 指向常量的指针（同上）" << endl;
    cout << "int* const p3;        // 常量指针" << endl;
    cout << "const int* const p4;  // 指向常量的常量指针" << endl;
}
```

### const引用
```cpp
void constReferences() {
    cout << "\n=== const引用 ===" << endl;
    
    int value = 42;
    
    // 常量引用
    const int& constRef = value;
    cout << "常量引用: constRef = " << constRef << endl;
    
    // 可以通过原变量修改值
    value = 100;
    cout << "修改原变量后: constRef = " << constRef << endl;
    
    // 但不能通过常量引用修改
    // constRef = 200;  // 错误！
    
    // 常量引用可以绑定到临时对象
    const int& tempRef = 42;
    const int& exprRef = 3 + 4;
    const string& stringRef = string("Hello") + " World";
    
    cout << "临时对象引用: " << tempRef << endl;
    cout << "表达式引用: " << exprRef << endl;
    cout << "字符串引用: " << stringRef << endl;
    
    // 类型转换和const引用
    double pi = 3.14159;
    const int& intRef = pi;  // 会创建临时int对象
    cout << "类型转换引用: " << intRef << endl;
    
    // 延长临时对象生命周期
    const string& temp = string("Temporary");
    cout << "延长生命周期: " << temp << endl;
}
```

### const成员函数
```cpp
class Rectangle {
private:
    double width, height;
    mutable int accessCount;  // mutable成员可以在const函数中修改
    
public:
    Rectangle(double w, double h) : width(w), height(h), accessCount(0) {}
    
    // const成员函数
    double getWidth() const {
        accessCount++;  // mutable成员可以修改
        return width;
    }
    
    double getHeight() const {
        accessCount++;
        return height;
    }
    
    double getArea() const {
        return width * height;
    }
    
    int getAccessCount() const {
        return accessCount;
    }
    
    // 非const成员函数
    void setWidth(double w) {
        width = w;
    }
    
    void setHeight(double h) {
        height = h;
    }
    
    // const重载
    char& at(int index) {
        cout << "调用非const版本" << endl;
        static char buffer[100] = "Non-const version";
        return buffer[index];
    }
    
    const char& at(int index) const {
        cout << "调用const版本" << endl;
        static const char buffer[100] = "Const version";
        return buffer[index];
    }
    
    // 错误示例：const函数试图修改成员
    /*
    void badConstFunction() const {
        width = 10;  // 错误！const函数不能修改非mutable成员
    }
    */
};

void constMemberFunctions() {
    cout << "\n=== const成员函数 ===" << endl;
    
    Rectangle rect(10.0, 5.0);
    const Rectangle constRect(20.0, 15.0);
    
    // 非const对象可以调用const和非const函数
    cout << "非const对象:" << endl;
    cout << "宽度: " << rect.getWidth() << endl;
    cout << "高度: " << rect.getHeight() << endl;
    cout << "面积: " << rect.getArea() << endl;
    rect.setWidth(12.0);  // 可以调用非const函数
    
    // const对象只能调用const函数
    cout << "\nconst对象:" << endl;
    cout << "宽度: " << constRect.getWidth() << endl;
    cout << "高度: " << constRect.getHeight() << endl;
    cout << "面积: " << constRect.getArea() << endl;
    // constRect.setWidth(25.0);  // 错误！不能调用非const函数
    
    // mutable成员的使用
    cout << "\n访问计数:" << endl;
    cout << "rect访问次数: " << rect.getAccessCount() << endl;
    cout << "constRect访问次数: " << constRect.getAccessCount() << endl;
    
    // const重载演示
    cout << "\nconst重载:" << endl;
    rect.at(0);      // 调用非const版本
    constRect.at(0); // 调用const版本
}
```

## 实践练习

### 练习1：const正确性检查器
```cpp
class ConstCorrectnessChecker {
private:
    int* data;
    size_t size;
    mutable bool cached;
    mutable double cachedSum;
    
public:
    ConstCorrectnessChecker(size_t s) : size(s), cached(false), cachedSum(0.0) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i + 1);
        }
    }
    
    ~ConstCorrectnessChecker() {
        delete[] data;
    }
    
    // const访问器
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 非const访问器
    int& operator[](size_t index) {
        cached = false;  // 数据可能被修改，清除缓存
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // const成员函数，使用mutable实现缓存
    double getSum() const {
        if (!cached) {
            cachedSum = 0.0;
            for (size_t i = 0; i < size; i++) {
                cachedSum += data[i];
            }
            cached = true;
        }
        return cachedSum;
    }
    
    size_t getSize() const { return size; }
    
    // 修改数据的函数
    void set(size_t index, int value) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        data[index] = value;
        cached = false;  // 清除缓存
    }
    
    void print() const {
        cout << "数据: ";
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void exercise1() {
    cout << "\n=== 练习1：const正确性检查器 ===" << endl;
    
    ConstCorrectnessChecker checker(5);
    const ConstCorrectnessChecker constChecker(3);
    
    // 非const对象操作
    cout << "非const对象操作:" << endl;
    checker.print();
    cout << "和: " << checker.getSum() << endl;
    
    checker[2] = 100;  // 修改数据
    cout << "修改后:" << endl;
    checker.print();
    cout << "新的和: " << checker.getSum() << endl;
    
    // const对象操作
    cout << "\nconst对象操作:" << endl;
    constChecker.print();
    cout << "和: " << constChecker.getSum() << endl;
    cout << "元素[1]: " << constChecker[1] << endl;
    // constChecker[1] = 50;  // 错误！不能修改const对象
}
```

### 练习2：const安全的字符串类
```cpp
class SafeString {
private:
    char* str;
    size_t len;
    
    void copyFrom(const char* source) {
        len = strlen(source);
        str = new char[len + 1];
        strcpy(str, source);
    }
    
public:
    // 构造函数
    SafeString(const char* s = "") {
        copyFrom(s);
    }
    
    // 拷贝构造函数
    SafeString(const SafeString& other) {
        copyFrom(other.str);
    }
    
    // 赋值操作符
    SafeString& operator=(const SafeString& other) {
        if (this != &other) {
            delete[] str;
            copyFrom(other.str);
        }
        return *this;
    }
    
    // 析构函数
    ~SafeString() {
        delete[] str;
    }
    
    // const成员函数
    size_t length() const { return len; }
    bool empty() const { return len == 0; }
    const char* c_str() const { return str; }
    
    // const版本的字符访问
    const char& operator[](size_t index) const {
        if (index >= len) {
            throw out_of_range("Index out of range");
        }
        return str[index];
    }
    
    // 非const版本的字符访问
    char& operator[](size_t index) {
        if (index >= len) {
            throw out_of_range("Index out of range");
        }
        return str[index];
    }
    
    // const成员函数：查找子串
    int find(const char* substr) const {
        if (!substr) return -1;
        
        const char* pos = strstr(str, substr);
        return pos ? static_cast<int>(pos - str) : -1;
    }
    
    // const成员函数：比较
    int compare(const SafeString& other) const {
        return strcmp(str, other.str);
    }
    
    bool operator==(const SafeString& other) const {
        return compare(other) == 0;
    }
    
    bool operator<(const SafeString& other) const {
        return compare(other) < 0;
    }
    
    // 修改操作（非const）
    void append(const char* suffix) {
        if (!suffix) return;
        
        size_t suffixLen = strlen(suffix);
        char* newStr = new char[len + suffixLen + 1];
        strcpy(newStr, str);
        strcat(newStr, suffix);
        
        delete[] str;
        str = newStr;
        len += suffixLen;
    }
    
    void toUpper() {
        for (size_t i = 0; i < len; i++) {
            str[i] = toupper(str[i]);
        }
    }
    
    // 友元函数用于输出
    friend ostream& operator<<(ostream& os, const SafeString& s) {
        os << s.str;
        return os;
    }
};

void exercise2() {
    cout << "\n=== 练习2：const安全的字符串类 ===" << endl;
    
    SafeString str1("Hello");
    const SafeString str2("World");
    
    cout << "str1: " << str1 << " (长度: " << str1.length() << ")" << endl;
    cout << "str2: " << str2 << " (长度: " << str2.length() << ")" << endl;
    
    // const对象只能调用const函数
    cout << "str2是否为空: " << str2.empty() << endl;
    cout << "str2的C字符串: " << str2.c_str() << endl;
    cout << "str2[1] = " << str2[1] << endl;
    
    // 非const对象可以调用所有函数
    str1.append(" ");
    str1.append(str2.c_str());
    cout << "拼接后的str1: " << str1 << endl;
    
    // 修改字符
    str1[0] = 'h';
    cout << "修改首字符后: " << str1 << endl;
    
    // 比较操作
    SafeString str3("hello world");
    cout << "str1 == str3: " << (str1 == str3) << endl;
    cout << "str1 < str2: " << (str1 < str2) << endl;
}
```

### 练习3：const与模板
```cpp
template<typename T>
class ConstContainer {
private:
    T* data;
    size_t size;
    size_t capacity;
    
public:
    ConstContainer(size_t cap = 10) : size(0), capacity(cap) {
        data = new T[capacity];
    }
    
    ~ConstContainer() {
        delete[] data;
    }
    
    // const成员函数
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return size == 0; }
    bool full() const { return size >= capacity; }
    
    // const版本的访问器
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // 非const版本的访问器
    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // const成员函数：查找
    bool contains(const T& value) const {
        for (size_t i = 0; i < size; i++) {
            if (data[i] == value) {
                return true;
            }
        }
        return false;
    }
    
    // const成员函数：获取最大值
    const T& getMax() const {
        if (size == 0) {
            throw runtime_error("Container is empty");
        }
        
        const T* maxPtr = &data[0];
        for (size_t i = 1; i < size; i++) {
            if (data[i] > *maxPtr) {
                maxPtr = &data[i];
            }
        }
        return *maxPtr;
    }
    
    // 修改操作（非const）
    void push_back(const T& value) {
        if (full()) {
            throw runtime_error("Container is full");
        }
        data[size++] = value;
    }
    
    void clear() {
        size = 0;
    }
    
    void print() const {
        cout << "容器内容: ";
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void exercise3() {
    cout << "\n=== 练习3：const与模板 ===" << endl;
    
    ConstContainer<int> container;
    
    // 添加元素
    for (int i = 1; i <= 5; i++) {
        container.push_back(i * 10);
    }
    
    container.print();
    cout << "大小: " << container.getSize() << endl;
    cout << "容量: " << container.getCapacity() << endl;
    
    // 创建const容器
    const ConstContainer<int>& constRef = container;
    cout << "const容器访问:" << endl;
    cout << "元素[2]: " << constRef[2] << endl;
    cout << "包含30: " << constRef.contains(30) << endl;
    cout << "最大值: " << constRef.getMax() << endl;
    
    // 修改非const容器
    container[1] = 999;
    cout << "修改后:" << endl;
    container.print();
    
    // 字符串版本
    ConstContainer<string> strContainer;
    strContainer.push_back("Hello");
    strContainer.push_back("World");
    strContainer.push_back("C++");
    
    cout << "\n字符串容器:" << endl;
    strContainer.print();
    cout << "最大字符串: " << strContainer.getMax() << endl;
}
```

## 算法练习题

### LeetCode相关题目
1. **[只出现一次的数字](https://leetcode.cn/problems/single-number/)** - const参数优化
2. **[有效的字母异位词](https://leetcode.cn/problems/valid-anagram/)** - const字符串处理
3. **[最长公共前缀](https://leetcode.cn/problems/longest-common-prefix/)** - const引用优化

### 练习4：const优化的算法实现
```cpp
class AlgorithmUtils {
public:
    // 二分查找 - const版本
    static int binarySearch(const vector<int>& arr, int target) {
        int left = 0, right = static_cast<int>(arr.size()) - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;  // 未找到
    }
    
    // 快速排序 - 非const版本（需要修改数组）
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivot = partition(arr, low, high);
            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }
    
    // 字符串匹配 - const版本
    static int findSubstring(const string& text, const string& pattern) {
        if (pattern.empty()) return 0;
        if (text.length() < pattern.length()) return -1;
        
        for (size_t i = 0; i <= text.length() - pattern.length(); i++) {
            size_t j = 0;
            while (j < pattern.length() && text[i + j] == pattern[j]) {
                j++;
            }
            if (j == pattern.length()) {
                return static_cast<int>(i);
            }
        }
        
        return -1;
    }
    
    // 计算数组和 - const版本
    static long long calculateSum(const vector<int>& arr) {
        long long sum = 0;
        for (const int& element : arr) {  // const引用避免拷贝
            sum += element;
        }
        return sum;
    }
    
    // 查找最大最小值 - const版本
    static pair<int, int> findMinMax(const vector<int>& arr) {
        if (arr.empty()) {
            throw invalid_argument("Array is empty");
        }
        
        int minVal = arr[0], maxVal = arr[0];
        for (const int& element : arr) {
            if (element < minVal) minVal = element;
            if (element > maxVal) maxVal = element;
        }
        
        return make_pair(minVal, maxVal);
    }

private:
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

void exercise4() {
    cout << "\n=== 练习4：const优化的算法实现 ===" << endl;
    
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90, 5};
    
    cout << "原始数组: ";
    for (const int& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // const算法测试
    cout << "数组和: " << AlgorithmUtils::calculateSum(numbers) << endl;
    
    auto minMax = AlgorithmUtils::findMinMax(numbers);
    cout << "最小值: " << minMax.first << ", 最大值: " << minMax.second << endl;
    
    // 排序（非const操作）
    AlgorithmUtils::quickSort(numbers, 0, static_cast<int>(numbers.size()) - 1);
    cout << "排序后: ";
    for (const int& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 二分查找（const操作）
    int target = 25;
    int index = AlgorithmUtils::binarySearch(numbers, target);
    cout << "查找 " << target << ": " << (index != -1 ? "找到，索引 " + to_string(index) : "未找到") << endl;
    
    // 字符串匹配
    string text = "Hello World, this is a test string";
    string pattern = "World";
    int pos = AlgorithmUtils::findSubstring(text, pattern);
    cout << "在 \"" << text << "\" 中查找 \"" << pattern << "\": ";
    cout << (pos != -1 ? "找到，位置 " + to_string(pos) : "未找到") << endl;
}
```

## const_cast使用示例

```cpp
void constCastExample() {
    cout << "\n=== const_cast使用示例 ===" << endl;
    
    // 场景1：调用不支持const的遗留API
    auto legacyFunction = [](char* str) -> int {
        return static_cast<int>(strlen(str));
    };
    
    const char* constStr = "Hello, World!";
    // int len = legacyFunction(constStr);  // 错误！类型不匹配
    int len = legacyFunction(const_cast<char*>(constStr));  // 使用const_cast
    cout << "字符串长度: " << len << endl;
    
    // 场景2：实现const和非const版本的重载
    class DataContainer {
    private:
        vector<int> data{1, 2, 3, 4, 5};
        
    public:
        // 非const版本
        int& at(size_t index) {
            cout << "调用非const at()" << endl;
            return const_cast<int&>(static_cast<const DataContainer*>(this)->at(index));
        }
        
        // const版本（实际实现）
        const int& at(size_t index) const {
            cout << "调用const at()" << endl;
            if (index >= data.size()) {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }
    };
    
    DataContainer container;
    const DataContainer& constContainer = container;
    
    cout << "非const对象访问: " << container.at(2) << endl;
    cout << "const对象访问: " << constContainer.at(2) << endl;
    
    // 场景3：注意const_cast的危险性
    const int originalConst = 42;
    int& dangerousRef = const_cast<int&>(originalConst);
    // dangerousRef = 100;  // 未定义行为！不要这样做
    
    cout << "原始const值: " << originalConst << endl;
    cout << "危险引用: " << dangerousRef << endl;
}
```

## 学习检查点

- [ ] 理解const变量的声明和初始化规则
- [ ] 掌握const指针的三种形式和用法
- [ ] 熟练使用const引用优化函数参数
- [ ] 理解const成员函数的作用和限制
- [ ] 掌握mutable关键字的使用场景
- [ ] 了解const重载的实现方法
- [ ] 理解const_cast的使用场景和注意事项
- [ ] 能够编写const正确的代码

## 完整示例程序

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;

int main() {
    cout << "=== C++ const关键字学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        constVariables();
        constPointers();
        constReferences();
        constMemberFunctions();
        
        exercise1();
        exercise2();
        exercise3();
        exercise4();
        
        constCastExample();
        
    } catch (const exception& e) {
        cout << "异常: " << e.what() << endl;
    }
    
    return 0;
}
```

## 总结

第一周的学习到此结束！通过这7天的学习，你应该已经掌握了：

1. **基础语法和数据类型** - C++的基础知识
2. **函数和作用域** - 函数设计和参数传递
3. **数组和字符串** - 基本数据结构操作
4. **指针基础** - 内存地址和间接访问
5. **引用** - 别名机制和参数优化
6. **动态内存分配** - 堆内存管理
7. **const关键字** - 常量安全编程

这些知识为后续的面向对象编程奠定了坚实的基础。

[返回第一周](/plan/week1/) | [上一天：动态内存分配](/plan/week1/day6/) | [下一周：面向对象编程](/plan/week2/)
