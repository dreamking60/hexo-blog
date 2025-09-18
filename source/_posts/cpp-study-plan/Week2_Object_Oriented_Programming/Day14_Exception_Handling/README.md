---
title: C++ 学习计划 - 第14天:异常处理
date: 2025-09-16 10:24:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day14
layout: page
menu_id: plan
permalink: /plan/week2/day14/
---

# 第14天：异常处理

## 学习目标
掌握C++异常处理机制，理解RAII与异常安全，学会编写健壮的异常安全代码。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Exceptions](https://en.cppreference.com/w/cpp/error/exception) - C++官方异常文档
- [LearnCpp - Exception Handling](https://www.learncpp.com/cpp-tutorial/the-need-for-exceptions/) - 异常处理详解教程
- [GeeksforGeeks - Exception Handling](https://www.geeksforgeeks.org/exception-handling-c/) - 异常处理基础知识

### 🎥 视频教程
- [The Cherno C++ Exceptions](https://www.youtube.com/watch?v=0ojB8c0xUd8) - 异常处理深入讲解
- [C++ Exception Safety](https://www.youtube.com/watch?v=W6jZKibuJpU) - 异常安全详解

### 📖 深入阅读
- [C++ Primer 第5版 - 第5.6节](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - try语句块和异常处理
- [Effective C++ - 条款13-15](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 资源管理和异常安全
- [More Effective C++ - 条款9-15](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X) - 异常处理技巧

## 学习内容

### 1. 异常处理基础
- try-catch-throw机制
- 异常的传播过程
- 异常处理的开销
- 异常 vs 错误码

### 2. 异常类型
- 标准异常类层次
- 自定义异常类
- 异常规范（C++11前）
- noexcept规范（C++11）

### 3. RAII与异常安全
- 异常安全的三个级别
- RAII原则在异常处理中的应用
- 智能指针与异常安全
- 异常安全的设计模式

### 4. 异常处理最佳实践
- 何时使用异常
- 异常处理的性能考虑
- 异常安全的代码编写
- 调试异常相关问题

### 5. 高级异常处理
- 异常重新抛出
- 嵌套异常
- 异常转换
- 异常处理与多线程

## 重点概念和代码示例

### 异常处理基础
```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// 自定义异常类
class MathError : public runtime_error {
public:
    MathError(const string& message) : runtime_error("数学错误: " + message) {}
};

class DivisionByZeroError : public MathError {
public:
    DivisionByZeroError() : MathError("除数不能为零") {}
};

class NegativeSquareRootError : public MathError {
private:
    double value;
public:
    NegativeSquareRootError(double val) : MathError("负数不能开平方根"), value(val) {}
    double getValue() const { return value; }
};

// 可能抛出异常的函数
double divide(double a, double b) {
    if (b == 0.0) {
        throw DivisionByZeroError();
    }
    return a / b;
}

double squareRoot(double x) {
    if (x < 0) {
        throw NegativeSquareRootError(x);
    }
    return sqrt(x);
}

int factorial(int n) {
    if (n < 0) {
        throw invalid_argument("阶乘的参数不能为负数");
    }
    if (n > 20) {
        throw overflow_error("阶乘结果太大，会溢出");
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

void basicExceptionDemo() {
    cout << "=== 异常处理基础演示 ===" << endl;
    
    // 除法异常
    try {
        double result1 = divide(10, 2);
        cout << "10 / 2 = " << result1 << endl;
        
        double result2 = divide(10, 0);  // 抛出异常
        cout << "这行不会执行" << endl;
    }
    catch (const DivisionByZeroError& e) {
        cout << "捕获除零异常: " << e.what() << endl;
    }
    catch (const MathError& e) {
        cout << "捕获数学异常: " << e.what() << endl;
    }
    
    // 平方根异常
    try {
        double result1 = squareRoot(16);
        cout << "sqrt(16) = " << result1 << endl;
        
        double result2 = squareRoot(-4);  // 抛出异常
        cout << "这行不会执行" << endl;
    }
    catch (const NegativeSquareRootError& e) {
        cout << "捕获负数开方异常: " << e.what() << endl;
        cout << "问题值: " << e.getValue() << endl;
    }
    
    // 阶乘异常
    try {
        cout << "5! = " << factorial(5) << endl;
        cout << "(-3)! = " << factorial(-3) << endl;  // 抛出异常
    }
    catch (const invalid_argument& e) {
        cout << "捕获参数异常: " << e.what() << endl;
    }
    catch (const overflow_error& e) {
        cout << "捕获溢出异常: " << e.what() << endl;
    }
    catch (const exception& e) {  // 捕获所有标准异常
        cout << "捕获标准异常: " << e.what() << endl;
    }
    catch (...) {  // 捕获所有异常
        cout << "捕获未知异常" << endl;
    }
}
```

### 异常安全的资源管理
```cpp
// 异常不安全的类
class UnsafeResource {
private:
    int* data;
    size_t size;
    
public:
    UnsafeResource(size_t s) : size(s) {
        cout << "分配资源，大小: " << size << endl;
        data = new int[size];
        
        // 模拟可能失败的操作
        if (size > 1000) {
            throw runtime_error("资源太大，分配失败");
        }
        
        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i);
        }
    }
    
    ~UnsafeResource() {
        cout << "释放资源，大小: " << size << endl;
        delete[] data;
    }
    
    // 危险的操作 - 可能导致异常
    void dangerousOperation() {
        cout << "执行危险操作..." << endl;
        if (size > 10) {
            throw runtime_error("危险操作失败");
        }
    }
    
    void display() const {
        cout << "资源内容: ";
        for (size_t i = 0; i < min(size, size_t(5)); i++) {
            cout << data[i] << " ";
        }
        if (size > 5) cout << "...";
        cout << endl;
    }
};

// 异常安全的类 - 使用RAII
class SafeResource {
private:
    unique_ptr<int[]> data;
    size_t size;
    
public:
    SafeResource(size_t s) : size(s) {
        cout << "安全分配资源，大小: " << size << endl;
        
        // 使用智能指针，异常安全
        data = make_unique<int[]>(size);
        
        // 模拟可能失败的操作
        if (size > 1000) {
            throw runtime_error("资源太大，分配失败");
        }
        
        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i);
        }
    }
    
    ~SafeResource() {
        cout << "安全释放资源，大小: " << size << endl;
        // 智能指针自动清理，无需手动delete
    }
    
    // 异常安全的操作
    void safeOperation() {
        cout << "执行安全操作..." << endl;
        
        // 使用RAII保护临时资源
        auto tempResource = make_unique<int[]>(10);
        
        if (size > 10) {
            // 即使抛出异常，tempResource也会自动清理
            throw runtime_error("安全操作失败");
        }
        
        cout << "安全操作完成" << endl;
    }
    
    void display() const {
        cout << "安全资源内容: ";
        for (size_t i = 0; i < min(size, size_t(5)); i++) {
            cout << data[i] << " ";
        }
        if (size > 5) cout << "...";
        cout << endl;
    }
};

// 演示异常安全的函数
void processResources() {
    cout << "\n=== 处理多个资源 ===" << endl;
    
    try {
        SafeResource res1(5);
        res1.display();
        
        SafeResource res2(8);
        res2.display();
        
        // 这个操作可能失败
        res2.safeOperation();
        
        SafeResource res3(15);  // 可能抛出异常
        res3.display();
        
    } catch (const exception& e) {
        cout << "处理资源时发生异常: " << e.what() << endl;
        cout << "所有资源都已自动清理" << endl;
    }
}

void raiiExceptionDemo() {
    cout << "\n=== RAII与异常安全演示 ===" << endl;
    
    cout << "1. 不安全的资源管理:" << endl;
    try {
        UnsafeResource unsafe(5);
        unsafe.display();
        unsafe.dangerousOperation();  // 抛出异常
    } catch (const exception& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    
    cout << "\n2. 安全的资源管理:" << endl;
    try {
        SafeResource safe(5);
        safe.display();
        safe.safeOperation();  // 抛出异常
    } catch (const exception& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    
    processResources();
}
```

## 实践练习

### 练习1：异常安全的栈类
```cpp
template<typename T>
class ExceptionSafeStack {
private:
    vector<T> elements;
    size_t maxSize;
    
public:
    class StackException : public runtime_error {
    public:
        StackException(const string& message) 
            : runtime_error("栈异常: " + message) {}
    };
    
    class StackOverflowException : public StackException {
    public:
        StackOverflowException() : StackException("栈溢出") {}
    };
    
    class StackUnderflowException : public StackException {
    public:
        StackUnderflowException() : StackException("栈为空") {}
    };
    
    // 构造函数
    explicit ExceptionSafeStack(size_t maxSz = 100) : maxSize(maxSz) {
        elements.reserve(maxSize);  // 预分配内存，减少异常风险
        cout << "创建异常安全栈，最大容量: " << maxSize << endl;
    }
    
    // 拷贝构造函数 - 异常安全
    ExceptionSafeStack(const ExceptionSafeStack& other) 
        : maxSize(other.maxSize) {
        try {
            elements = other.elements;  // 可能抛出bad_alloc
            cout << "拷贝构造栈，元素数量: " << elements.size() << endl;
        } catch (...) {
            // 确保对象处于有效状态
            elements.clear();
            throw;  // 重新抛出异常
        }
    }
    
    // 赋值操作符 - 异常安全（强异常安全保证）
    ExceptionSafeStack& operator=(const ExceptionSafeStack& other) {
        if (this != &other) {
            // 使用拷贝-交换惯用法确保异常安全
            ExceptionSafeStack temp(other);  // 可能抛出异常
            swap(temp);  // 不抛出异常的交换
        }
        return *this;
    }
    
    // 析构函数 - 不应抛出异常
    ~ExceptionSafeStack() noexcept {
        cout << "销毁栈，元素数量: " << elements.size() << endl;
    }
    
    // 压栈 - 强异常安全保证
    void push(const T& item) {
        if (elements.size() >= maxSize) {
            throw StackOverflowException();
        }
        
        // vector::push_back提供强异常安全保证
        elements.push_back(item);
    }
    
    // 弹栈 - 基本异常安全保证
    void pop() {
        if (empty()) {
            throw StackUnderflowException();
        }
        
        elements.pop_back();  // 不抛出异常
    }
    
    // 获取栈顶元素 - 无异常抛出保证
    const T& top() const {
        if (empty()) {
            throw StackUnderflowException();
        }
        
        return elements.back();
    }
    
    // 获取栈顶元素（非const版本）
    T& top() {
        if (empty()) {
            throw StackUnderflowException();
        }
        
        return elements.back();
    }
    
    // 弹出并返回栈顶元素 - 异常安全版本
    T popAndReturn() {
        if (empty()) {
            throw StackUnderflowException();
        }
        
        T result = elements.back();  // 可能抛出异常（拷贝构造）
        elements.pop_back();         // 不抛出异常
        return result;
    }
    
    // 状态查询 - 不抛出异常
    bool empty() const noexcept {
        return elements.empty();
    }
    
    size_t size() const noexcept {
        return elements.size();
    }
    
    size_t capacity() const noexcept {
        return maxSize;
    }
    
    // 清空栈 - 不抛出异常
    void clear() noexcept {
        elements.clear();
    }
    
    // 显示栈内容
    void display() const {
        cout << "栈内容 (从底到顶): ";
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << "(size: " << size() << "/" << capacity() << ")" << endl;
    }
    
private:
    // 异常安全的交换函数
    void swap(ExceptionSafeStack& other) noexcept {
        elements.swap(other.elements);
        std::swap(maxSize, other.maxSize);
    }
};

void exercise1() {
    cout << "\n=== 练习1：异常安全的栈类 ===" << endl;
    
    try {
        ExceptionSafeStack<int> stack(5);
        
        // 正常操作
        for (int i = 1; i <= 3; i++) {
            stack.push(i * 10);
        }
        stack.display();
        
        cout << "栈顶元素: " << stack.top() << endl;
        
        // 弹出元素
        cout << "弹出元素: " << stack.popAndReturn() << endl;
        stack.display();
        
        // 测试栈溢出
        cout << "\n测试栈溢出:" << endl;
        try {
            for (int i = 0; i < 10; i++) {
                stack.push(i);
                cout << "推入: " << i << endl;
            }
        } catch (const ExceptionSafeStack<int>::StackOverflowException& e) {
            cout << "捕获溢出异常: " << e.what() << endl;
            stack.display();
        }
        
        // 测试栈下溢
        cout << "\n测试栈下溢:" << endl;
        stack.clear();
        try {
            stack.pop();
        } catch (const ExceptionSafeStack<int>::StackUnderflowException& e) {
            cout << "捕获下溢异常: " << e.what() << endl;
        }
        
        // 测试拷贝构造
        cout << "\n测试拷贝构造:" << endl;
        stack.push(100);
        stack.push(200);
        ExceptionSafeStack<int> stack2 = stack;
        stack2.display();
        
        // 修改原栈
        stack.push(300);
        cout << "原栈: ";
        stack.display();
        cout << "拷贝栈: ";
        stack2.display();
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
}
```

### 练习2：异常安全的文件处理类
```cpp
class FileProcessor {
private:
    string filename;
    unique_ptr<FILE, function<void(FILE*)>> file;
    bool isOpen;
    
public:
    class FileException : public runtime_error {
    public:
        FileException(const string& message) 
            : runtime_error("文件异常: " + message) {}
    };
    
    class FileOpenException : public FileException {
    public:
        FileOpenException(const string& filename) 
            : FileException("无法打开文件: " + filename) {}
    };
    
    class FileReadException : public FileException {
    public:
        FileReadException() : FileException("文件读取失败") {}
    };
    
    class FileWriteException : public FileException {
    public:
        FileWriteException() : FileException("文件写入失败") {}
    };
    
    // 构造函数 - 异常安全
    explicit FileProcessor(const string& fname) 
        : filename(fname), isOpen(false) {
        cout << "创建文件处理器: " << filename << endl;
    }
    
    // 禁止拷贝（文件句柄不应该被复制）
    FileProcessor(const FileProcessor&) = delete;
    FileProcessor& operator=(const FileProcessor&) = delete;
    
    // 移动构造函数
    FileProcessor(FileProcessor&& other) noexcept 
        : filename(move(other.filename)), 
          file(move(other.file)), 
          isOpen(other.isOpen) {
        other.isOpen = false;
        cout << "移动构造文件处理器: " << filename << endl;
    }
    
    // 析构函数 - 不抛出异常
    ~FileProcessor() noexcept {
        try {
            close();
        } catch (...) {
            // 析构函数中不应该让异常逃逸
            cout << "警告: 析构时关闭文件失败" << endl;
        }
        cout << "销毁文件处理器: " << filename << endl;
    }
    
    // 打开文件 - 异常安全
    void open(const string& mode) {
        if (isOpen) {
            throw FileException("文件已经打开");
        }
        
        FILE* rawFile = fopen(filename.c_str(), mode.c_str());
        if (!rawFile) {
            throw FileOpenException(filename);
        }
        
        // 使用RAII管理文件句柄
        file = unique_ptr<FILE, function<void(FILE*)>>(
            rawFile, 
            [this](FILE* f) {
                if (f) {
                    fclose(f);
                    cout << "自动关闭文件: " << filename << endl;
                }
            }
        );
        
        isOpen = true;
        cout << "成功打开文件: " << filename << " (模式: " << mode << ")" << endl;
    }
    
    // 写入数据 - 异常安全
    void write(const string& data) {
        if (!isOpen || !file) {
            throw FileException("文件未打开");
        }
        
        size_t written = fwrite(data.c_str(), 1, data.length(), file.get());
        if (written != data.length()) {
            throw FileWriteException();
        }
        
        // 立即刷新到磁盘
        if (fflush(file.get()) != 0) {
            throw FileWriteException();
        }
        
        cout << "成功写入 " << written << " 字节" << endl;
    }
    
    // 读取数据 - 异常安全
    string read() {
        if (!isOpen || !file) {
            throw FileException("文件未打开");
        }
        
        // 获取文件大小
        long currentPos = ftell(file.get());
        if (fseek(file.get(), 0, SEEK_END) != 0) {
            throw FileReadException();
        }
        
        long fileSize = ftell(file.get());
        if (fseek(file.get(), currentPos, SEEK_SET) != 0) {
            throw FileReadException();
        }
        
        if (fileSize <= currentPos) {
            return "";  // 已到文件末尾
        }
        
        size_t remainingSize = fileSize - currentPos;
        string buffer(remainingSize, '\0');
        
        size_t bytesRead = fread(&buffer[0], 1, remainingSize, file.get());
        buffer.resize(bytesRead);
        
        cout << "成功读取 " << bytesRead << " 字节" << endl;
        return buffer;
    }
    
    // 读取一行 - 异常安全
    string readLine() {
        if (!isOpen || !file) {
            throw FileException("文件未打开");
        }
        
        string line;
        char ch;
        
        while (fread(&ch, 1, 1, file.get()) == 1) {
            if (ch == '\n') {
                break;
            }
            line += ch;
        }
        
        if (line.empty() && feof(file.get())) {
            throw FileReadException();
        }
        
        return line;
    }
    
    // 关闭文件 - 异常安全
    void close() {
        if (isOpen) {
            file.reset();  // 自动调用删除器关闭文件
            isOpen = false;
        }
    }
    
    // 状态查询
    bool isFileOpen() const noexcept {
        return isOpen;
    }
    
    const string& getFilename() const noexcept {
        return filename;
    }
    
    // 批量处理文件 - 事务性操作
    static void batchProcess(const vector<string>& filenames, 
                           const function<void(FileProcessor&)>& processor) {
        vector<unique_ptr<FileProcessor>> processors;
        
        try {
            // 准备阶段：创建所有处理器
            for (const auto& fname : filenames) {
                processors.push_back(make_unique<FileProcessor>(fname));
            }
            
            // 处理阶段：对每个文件执行操作
            for (auto& proc : processors) {
                processor(*proc);
            }
            
            cout << "批量处理完成，共处理 " << processors.size() << " 个文件" << endl;
            
        } catch (const exception& e) {
            cout << "批量处理失败: " << e.what() << endl;
            cout << "已处理的文件将自动清理" << endl;
            throw;  // 重新抛出异常
        }
    }
};

void exercise2() {
    cout << "\n=== 练习2：异常安全的文件处理类 ===" << endl;
    
    try {
        // 基本文件操作
        FileProcessor processor("test_file.txt");
        
        processor.open("w+");
        processor.write("Hello, Exception Safe World!\n");
        processor.write("这是第二行内容\n");
        processor.write("异常安全的文件处理\n");
        
        // 重新定位到文件开头读取
        processor.close();
        processor.open("r");
        
        string content = processor.read();
        cout << "读取的文件内容:\n" << content << endl;
        
        processor.close();
        
        // 测试异常情况
        cout << "\n测试异常情况:" << endl;
        try {
            FileProcessor badProcessor("/nonexistent/path/file.txt");
            badProcessor.open("r");  // 应该抛出异常
        } catch (const FileProcessor::FileOpenException& e) {
            cout << "捕获文件打开异常: " << e.what() << endl;
        }
        
        // 测试移动语义
        cout << "\n测试移动语义:" << endl;
        auto createProcessor = []() {
            FileProcessor proc("temp_file.txt");
            proc.open("w");
            proc.write("临时文件内容");
            return proc;  // 移动返回
        };
        
        FileProcessor movedProc = createProcessor();
        cout << "移动后的处理器文件名: " << movedProc.getFilename() << endl;
        
        // 批量处理
        cout << "\n测试批量处理:" << endl;
        vector<string> files = {"batch1.txt", "batch2.txt", "batch3.txt"};
        
        try {
            FileProcessor::batchProcess(files, [](FileProcessor& proc) {
                proc.open("w");
                proc.write("批量处理的文件: " + proc.getFilename() + "\n");
                proc.close();
            });
        } catch (const exception& e) {
            cout << "批量处理异常: " << e.what() << endl;
        }
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
}
```

### 练习3：异常安全的数据库连接类
```cpp
// 模拟数据库连接类
class DatabaseConnection {
private:
    string connectionString;
    bool connected;
    int connectionId;
    static int nextConnectionId;
    
public:
    class DatabaseException : public runtime_error {
    public:
        DatabaseException(const string& message) 
            : runtime_error("数据库异常: " + message) {}
    };
    
    class ConnectionException : public DatabaseException {
    public:
        ConnectionException(const string& connStr) 
            : DatabaseException("连接失败: " + connStr) {}
    };
    
    class QueryException : public DatabaseException {
    public:
        QueryException(const string& query) 
            : DatabaseException("查询失败: " + query) {}
    };
    
    class TransactionException : public DatabaseException {
    public:
        TransactionException(const string& message) 
            : DatabaseException("事务异常: " + message) {}
    };
    
    // 构造函数
    explicit DatabaseConnection(const string& connStr) 
        : connectionString(connStr), connected(false), connectionId(++nextConnectionId) {
        cout << "创建数据库连接 [" << connectionId << "]: " << connectionString << endl;
        
        // 模拟连接可能失败
        if (connStr.find("invalid") != string::npos) {
            throw ConnectionException(connStr);
        }
    }
    
    // 禁止拷贝
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
    // 移动构造
    DatabaseConnection(DatabaseConnection&& other) noexcept 
        : connectionString(move(other.connectionString)),
          connected(other.connected),
          connectionId(other.connectionId) {
        other.connected = false;
        cout << "移动数据库连接 [" << connectionId << "]" << endl;
    }
    
    // 析构函数 - 异常安全
    ~DatabaseConnection() noexcept {
        try {
            disconnect();
        } catch (...) {
            cout << "警告: 析构时断开连接失败 [" << connectionId << "]" << endl;
        }
        cout << "销毁数据库连接 [" << connectionId << "]" << endl;
    }
    
    // 连接数据库
    void connect() {
        if (connected) {
            throw DatabaseException("连接已存在");
        }
        
        cout << "正在连接数据库 [" << connectionId << "]..." << endl;
        
        // 模拟连接过程可能失败
        if (connectionString.find("timeout") != string::npos) {
            throw ConnectionException("连接超时");
        }
        
        connected = true;
        cout << "成功连接数据库 [" << connectionId << "]" << endl;
    }
    
    // 断开连接
    void disconnect() noexcept {
        if (connected) {
            connected = false;
            cout << "断开数据库连接 [" << connectionId << "]" << endl;
        }
    }
    
    // 执行查询 - 异常安全
    vector<string> executeQuery(const string& query) {
        if (!connected) {
            throw DatabaseException("数据库未连接");
        }
        
        cout << "执行查询 [" << connectionId << "]: " << query << endl;
        
        // 模拟查询可能失败
        if (query.find("DROP") != string::npos) {
            throw QueryException("危险的DROP操作被拒绝");
        }
        
        if (query.find("invalid") != string::npos) {
            throw QueryException("SQL语法错误");
        }
        
        // 模拟查询结果
        vector<string> results;
        if (query.find("SELECT") != string::npos) {
            results = {"结果1", "结果2", "结果3"};
        }
        
        cout << "查询完成，返回 " << results.size() << " 条记录" << endl;
        return results;
    }
    
    // 状态查询
    bool isConnected() const noexcept {
        return connected;
    }
    
    int getId() const noexcept {
        return connectionId;
    }
};

int DatabaseConnection::nextConnectionId = 0;

// 数据库事务管理器 - RAII
class DatabaseTransaction {
private:
    DatabaseConnection& conn;
    bool committed;
    bool rolledBack;
    
public:
    explicit DatabaseTransaction(DatabaseConnection& connection) 
        : conn(connection), committed(false), rolledBack(false) {
        if (!conn.isConnected()) {
            throw DatabaseConnection::TransactionException("数据库未连接");
        }
        
        cout << "开始事务 [连接 " << conn.getId() << "]" << endl;
    }
    
    // 禁止拷贝和移动
    DatabaseTransaction(const DatabaseTransaction&) = delete;
    DatabaseTransaction& operator=(const DatabaseTransaction&) = delete;
    DatabaseTransaction(DatabaseTransaction&&) = delete;
    DatabaseTransaction& operator=(DatabaseTransaction&&) = delete;
    
    // 析构函数 - 自动回滚未提交的事务
    ~DatabaseTransaction() noexcept {
        try {
            if (!committed && !rolledBack) {
                rollback();
            }
        } catch (...) {
            cout << "警告: 析构时回滚事务失败" << endl;
        }
    }
    
    // 提交事务
    void commit() {
        if (committed) {
            throw DatabaseConnection::TransactionException("事务已提交");
        }
        if (rolledBack) {
            throw DatabaseConnection::TransactionException("事务已回滚");
        }
        
        cout << "提交事务 [连接 " << conn.getId() << "]" << endl;
        committed = true;
    }
    
    // 回滚事务
    void rollback() {
        if (committed) {
            throw DatabaseConnection::TransactionException("无法回滚已提交的事务");
        }
        if (rolledBack) {
            return;  // 已经回滚过了
        }
        
        cout << "回滚事务 [连接 " << conn.getId() << "]" << endl;
        rolledBack = true;
    }
    
    // 执行查询（在事务中）
    vector<string> execute(const string& query) {
        if (committed || rolledBack) {
            throw DatabaseConnection::TransactionException("事务已结束");
        }
        
        return conn.executeQuery(query);
    }
};

void exercise3() {
    cout << "\n=== 练习3：异常安全的数据库连接类 ===" << endl;
    
    try {
        // 正常的数据库操作
        DatabaseConnection db("server=localhost;database=test");
        db.connect();
        
        auto results = db.executeQuery("SELECT * FROM users");
        cout << "查询结果数量: " << results.size() << endl;
        
        // 使用事务
        cout << "\n使用事务:" << endl;
        {
            DatabaseTransaction trans(db);
            trans.execute("INSERT INTO users VALUES ('Alice', 25)");
            trans.execute("INSERT INTO users VALUES ('Bob', 30)");
            trans.commit();
            cout << "事务提交成功" << endl;
        }
        
        // 事务回滚示例
        cout << "\n事务回滚示例:" << endl;
        try {
            DatabaseTransaction trans(db);
            trans.execute("INSERT INTO users VALUES ('Charlie', 35)");
            trans.execute("DROP TABLE users");  // 这会抛出异常
            trans.commit();  // 不会执行到这里
        } catch (const DatabaseConnection::QueryException& e) {
            cout << "捕获查询异常: " << e.what() << endl;
            cout << "事务将自动回滚" << endl;
        }
        
        // 测试连接失败
        cout << "\n测试连接失败:" << endl;
        try {
            DatabaseConnection badDb("server=invalid;timeout=true");
            badDb.connect();
        } catch (const DatabaseConnection::ConnectionException& e) {
            cout << "捕获连接异常: " << e.what() << endl;
        }
        
        // 测试移动语义
        cout << "\n测试移动语义:" << endl;
        auto createConnection = []() {
            DatabaseConnection conn("server=temp;database=temp");
            conn.connect();
            conn.executeQuery("SELECT 1");
            return conn;
        };
        
        DatabaseConnection movedConn = createConnection();
        cout << "移动后的连接ID: " << movedConn.getId() << endl;
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
}
```

## 学习检查点

- [ ] 理解异常处理的基本机制和语法
- [ ] 掌握标准异常类的层次结构
- [ ] 能够设计和实现自定义异常类
- [ ] 理解RAII在异常安全中的重要作用
- [ ] 掌握异常安全的三个级别
- [ ] 能够编写异常安全的代码
- [ ] 理解noexcept规范的使用
- [ ] 掌握异常处理的最佳实践

## 完整示例程序

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cstdio>
using namespace std;

int main() {
    cout << "=== C++ 异常处理学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        basicExceptionDemo();
        raiiExceptionDemo();
        
        exercise1();
        exercise2();
        exercise3();
        
    } catch (const exception& e) {
        cout << "程序顶层异常: " << e.what() << endl;
    } catch (...) {
        cout << "捕获未知异常" << endl;
    }
    
    cout << "\n程序结束" << endl;
    return 0;
}
```

## 第二周总结

🎉 **恭喜完成第二周的学习！**

通过这一周的学习，你已经掌握了C++面向对象编程的核心概念：

1. **类与对象基础** - 封装和基本的类设计
2. **构造函数与析构函数** - 对象生命周期管理和RAII
3. **继承** - 代码重用和is-a关系
4. **虚函数与多态** - 动态绑定和接口设计
5. **运算符重载** - 为自定义类型提供自然语法
6. **模板基础** - 泛型编程和代码重用
7. **异常处理** - 错误处理和异常安全编程

下一周我们将学习STL和C++的高级特性，进一步提升编程技能！

[返回第二周](/plan/week2/) | [上一天：模板基础](/plan/week2/day13/) | [下一周：STL与高级特性](/plan/week3/)
