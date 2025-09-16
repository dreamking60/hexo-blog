---
title: C++ 学习计划 - 第三周第21天：文件操作与IO
date: 2025-01-27 21:00:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week3
    - File IO
    - Streams
layout: page
menu_id: plan
permalink: /plan/week3/day21/
---

# 第21天：文件操作与IO

## 学习目标
掌握C++的文件操作和IO流，理解文本文件与二进制文件的处理，学会使用字符串流和错误处理。

## 核心知识点

### 1. 文件流概述

C++提供了多种文件流类来处理文件操作：
- `ifstream`：输入文件流（读取文件）
- `ofstream`：输出文件流（写入文件）
- `fstream`：文件流（读写文件）

#### 头文件包含
```cpp
#include <fstream>   // 文件流
#include <iostream>  // 标准输入输出流
#include <sstream>   // 字符串流
```

#### 参考资料
- [C++ 输入输出库 - cppreference.com](https://en.cppreference.com/w/cpp/io)
- [文件流详解 - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_fstream)

### 2. 基本文件操作

#### 文件写入
```cpp
#include <fstream>
#include <iostream>
#include <string>

void fileWritingExample() {
    // 创建输出文件流
    std::ofstream outFile("example.txt");
    
    if (outFile.is_open()) {
        // 写入文本
        outFile << "Hello, World!" << std::endl;
        outFile << "This is a test file." << std::endl;
        outFile << "Line 3" << std::endl;
        
        // 写入数字
        int number = 42;
        outFile << "Number: " << number << std::endl;
        
        outFile.close();
        std::cout << "文件写入成功" << std::endl;
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 文件读取
```cpp
void fileReadingExample() {
    // 创建输入文件流
    std::ifstream inFile("example.txt");
    
    if (inFile.is_open()) {
        std::string line;
        
        // 逐行读取
        while (std::getline(inFile, line)) {
            std::cout << "读取: " << line << std::endl;
        }
        
        inFile.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 文件读写
```cpp
void fileReadWriteExample() {
    // 创建文件流（读写模式）
    std::fstream file("data.txt", std::ios::in | std::ios::out | std::ios::trunc);
    
    if (file.is_open()) {
        // 写入数据
        file << "Line 1" << std::endl;
        file << "Line 2" << std::endl;
        file << "Line 3" << std::endl;
        
        // 移动到文件开头
        file.seekg(0, std::ios::beg);
        
        // 读取数据
        std::string line;
        while (std::getline(file, line)) {
            std::cout << "读取: " << line << std::endl;
        }
        
        file.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 参考资料
- [std::ofstream - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_ofstream)
- [std::ifstream - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_ifstream)
- [C++ 文件操作详解](https://blog.csdn.net/weixin_43914604/article/details/105300000)

### 3. 文件模式

#### 常用文件模式
```cpp
// 不同的文件打开模式
std::ofstream out1("file1.txt", std::ios::out);           // 输出模式
std::ofstream out2("file2.txt", std::ios::out | std::ios::app);  // 追加模式
std::ofstream out3("file3.txt", std::ios::out | std::ios::trunc); // 截断模式

std::ifstream in1("file1.txt", std::ios::in);             // 输入模式
std::ifstream in2("file1.txt", std::ios::in | std::ios::binary); // 二进制模式

std::fstream file("file4.txt", std::ios::in | std::ios::out | std::ios::app); // 读写追加模式
```

#### 文件模式说明
- `std::ios::in`：读取模式
- `std::ios::out`：写入模式
- `std::ios::app`：追加模式
- `std::ios::trunc`：截断模式（清空文件）
- `std::ios::binary`：二进制模式
- `std::ios::ate`：打开时定位到文件末尾

#### 参考资料
- [文件打开模式 - cppreference.com](https://en.cppreference.com/w/cpp/io/ios_base/openmode)

### 4. 二进制文件操作

#### 二进制写入
```cpp
#include <vector>

struct Person {
    char name[50];
    int age;
    double salary;
};

void binaryWritingExample() {
    std::ofstream outFile("people.bin", std::ios::binary);
    
    if (outFile.is_open()) {
        Person people[] = {
            {"Alice", 25, 50000.0},
            {"Bob", 30, 60000.0},
            {"Charlie", 35, 70000.0}
        };
        
        // 写入二进制数据
        outFile.write(reinterpret_cast<const char*>(people), sizeof(people));
        
        outFile.close();
        std::cout << "二进制文件写入成功" << std::endl;
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 二进制读取
```cpp
void binaryReadingExample() {
    std::ifstream inFile("people.bin", std::ios::binary);
    
    if (inFile.is_open()) {
        // 获取文件大小
        inFile.seekg(0, std::ios::end);
        size_t fileSize = inFile.tellg();
        inFile.seekg(0, std::ios::beg);
        
        // 计算记录数量
        size_t numRecords = fileSize / sizeof(Person);
        
        // 读取数据
        std::vector<Person> people(numRecords);
        inFile.read(reinterpret_cast<char*>(people.data()), fileSize);
        
        // 显示数据
        for (const auto& person : people) {
            std::cout << "姓名: " << person.name 
                      << ", 年龄: " << person.age 
                      << ", 工资: " << person.salary << std::endl;
        }
        
        inFile.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 参考资料
- [二进制文件操作详解](https://www.learncpp.com/cpp-tutorial/file-handling-and-fstream/)

### 5. 文件定位

#### 文件指针操作
```cpp
void filePositioningExample() {
    std::fstream file("position.txt", std::ios::in | std::ios::out | std::ios::trunc);
    
    if (file.is_open()) {
        // 写入数据
        file << "Line 1: Hello" << std::endl;
        file << "Line 2: World" << std::endl;
        file << "Line 3: C++" << std::endl;
        file << "Line 4: Programming" << std::endl;
        
        // 获取当前位置
        std::cout << "当前位置: " << file.tellg() << std::endl;
        
        // 移动到文件开头
        file.seekg(0, std::ios::beg);
        std::cout << "移动到开头后位置: " << file.tellg() << std::endl;
        
        // 移动到文件末尾
        file.seekg(0, std::ios::end);
        std::cout << "移动到末尾后位置: " << file.tellg() << std::endl;
        
        // 移动到指定位置
        file.seekg(10, std::ios::beg);
        std::cout << "移动到位置10后位置: " << file.tellg() << std::endl;
        
        // 从当前位置向前移动
        file.seekg(-5, std::ios::cur);
        std::cout << "向前移动5个位置后位置: " << file.tellg() << std::endl;
        
        file.close();
    }
}
```

#### 定位函数说明
- `tellg()`：获取读指针位置
- `tellp()`：获取写指针位置
- `seekg(pos)`：设置读指针位置
- `seekp(pos)`：设置写指针位置
- `seekg(offset, dir)`：相对定位

#### 参考资料
- [文件定位操作 - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_istream/seekg)

### 6. 字符串流

#### std::stringstream
```cpp
#include <sstream>

void stringStreamExample() {
    // 字符串到数字的转换
    std::string str = "123 456 789";
    std::stringstream ss(str);
    
    int num1, num2, num3;
    ss >> num1 >> num2 >> num3;
    
    std::cout << "数字1: " << num1 << std::endl;
    std::cout << "数字2: " << num2 << std::endl;
    std::cout << "数字3: " << num3 << std::endl;
    
    // 数字到字符串的转换
    std::stringstream ss2;
    int value = 42;
    double pi = 3.14159;
    
    ss2 << "Value: " << value << ", Pi: " << pi;
    std::string result = ss2.str();
    std::cout << "结果: " << result << std::endl;
}
```

#### std::istringstream 和 std::ostringstream
```cpp
void specializedStringStreamExample() {
    // 输入字符串流
    std::string input = "Hello World 123 45.67";
    std::istringstream iss(input);
    
    std::string word1, word2;
    int number;
    double decimal;
    
    iss >> word1 >> word2 >> number >> decimal;
    
    std::cout << "单词1: " << word1 << std::endl;
    std::cout << "单词2: " << word2 << std::endl;
    std::cout << "数字: " << number << std::endl;
    std::cout << "小数: " << decimal << std::endl;
    
    // 输出字符串流
    std::ostringstream oss;
    oss << "结果: " << word1 << " " << word2 << " " << number << " " << decimal;
    std::string output = oss.str();
    std::cout << "输出: " << output << std::endl;
}
```

#### 参考资料
- [std::stringstream - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_stringstream)
- [字符串流详解](https://blog.csdn.net/weixin_43914604/article/details/105301000)

### 7. 错误处理

#### 文件状态检查
```cpp
void errorHandlingExample() {
    std::ifstream file("nonexistent.txt");
    
    // 检查文件是否打开
    if (!file.is_open()) {
        std::cout << "错误: 无法打开文件" << std::endl;
        return;
    }
    
    // 检查文件状态
    if (file.fail()) {
        std::cout << "错误: 文件操作失败" << std::endl;
        return;
    }
    
    if (file.bad()) {
        std::cout << "错误: 文件流损坏" << std::endl;
        return;
    }
    
    if (file.eof()) {
        std::cout << "警告: 已到达文件末尾" << std::endl;
    }
    
    // 清除错误状态
    file.clear();
    
    file.close();
}
```

#### 异常处理
```cpp
void exceptionHandlingExample() {
    try {
        std::ifstream file("data.txt");
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    } catch (const std::ifstream::failure& e) {
        std::cout << "文件操作异常: " << e.what() << std::endl;
    }
}
```

#### 参考资料
- [IO错误处理 - cppreference.com](https://en.cppreference.com/w/cpp/io/ios_base/iostate)

### 8. 文件管理器类

#### 实用文件操作工具
```cpp
#include <filesystem>  // C++17

class FileManager {
public:
    // 复制文件
    static bool copyFile(const std::string& source, const std::string& destination) {
        std::ifstream src(source, std::ios::binary);
        std::ofstream dst(destination, std::ios::binary);
        
        if (!src.is_open() || !dst.is_open()) {
            return false;
        }
        
        dst << src.rdbuf();
        return true;
    }
    
    // 移动文件
    static bool moveFile(const std::string& source, const std::string& destination) {
        if (copyFile(source, destination)) {
            return std::remove(source.c_str()) == 0;
        }
        return false;
    }
    
    // 读取所有行
    static std::vector<std::string> readLines(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }
        
        return lines;
    }
    
    // 写入所有行
    static void writeLines(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream file(filename);
        
        if (file.is_open()) {
            for (const auto& line : lines) {
                file << line << std::endl;
            }
            file.close();
        }
    }
    
    // 获取文件大小
    static size_t getFileSize(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            return file.tellg();
        }
        return 0;
    }
    
    // 检查文件是否存在
    static bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
    
    // C++17 filesystem版本
    static bool fileExistsModern(const std::string& filename) {
        return std::filesystem::exists(filename);
    }
    
    static size_t getFileSizeModern(const std::string& filename) {
        return std::filesystem::file_size(filename);
    }
};
```

#### 参考资料
- [C++17 filesystem - cppreference.com](https://en.cppreference.com/w/cpp/filesystem)
- [文件系统库详解](https://blog.csdn.net/weixin_43914604/article/details/105302000)

### 9. 高级IO操作

#### 格式化输出
```cpp
#include <iomanip>

void formattedOutputExample() {
    std::ofstream file("formatted.txt");
    
    if (file.is_open()) {
        double pi = 3.14159265359;
        int number = 42;
        
        // 设置精度
        file << std::fixed << std::setprecision(2) << pi << std::endl;
        
        // 设置宽度和对齐
        file << std::setw(10) << std::left << "Name" 
             << std::setw(5) << std::right << "Age" << std::endl;
        
        file << std::setw(10) << std::left << "Alice" 
             << std::setw(5) << std::right << 25 << std::endl;
        
        // 十六进制输出
        file << "Hex: " << std::hex << number << std::endl;
        
        file.close();
    }
}
```

#### 自定义分隔符
```cpp
void customDelimiterExample() {
    std::string data = "apple,banana,cherry,date";
    std::stringstream ss(data);
    std::string item;
    
    // 使用自定义分隔符读取
    while (std::getline(ss, item, ',')) {
        std::cout << "Item: " << item << std::endl;
    }
}
```

#### 参考资料
- [IO操纵符 - cppreference.com](https://en.cppreference.com/w/cpp/io/manip)

## 实用教程和文档

### 官方文档
- [C++ 输入输出库 - cppreference.com](https://en.cppreference.com/w/cpp/io)
- [文件流操作 - cppreference.com](https://en.cppreference.com/w/cpp/io/basic_fstream)

### 优质教程
- [C++ 文件操作完全指南](https://blog.csdn.net/weixin_43914604/article/details/105300000)
- [文件IO最佳实践](https://www.learncpp.com/cpp-tutorial/file-handling-and-fstream/)
- [现代C++文件操作](https://changkun.de/modern-cpp/zh-cn/06-regex/)

### 实战案例
- [日志系统实现](https://github.com/gabime/spdlog)
- [配置文件解析](https://github.com/nlohmann/json)

## 今日练习

### 基础练习
1. 实现一个日志系统，支持不同级别的日志记录
2. 编写一个配置文件解析器，支持键值对格式
3. 实现一个数据序列化系统，支持二进制和文本格式

### 算法题推荐
1. [LeetCode 68. Text Justification](https://leetcode.com/problems/text-justification/) - 文本对齐，涉及字符串处理
2. [LeetCode 151. Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/) - 字符串处理
3. [LeetCode 165. Compare Version Numbers](https://leetcode.com/problems/compare-version-numbers/) - 版本号比较
4. [LeetCode 273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/) - 数字转英文单词

## 学习要点总结

1. **文件流类型**：掌握ifstream、ofstream、fstream的使用
2. **文件模式**：理解不同的文件打开模式
3. **二进制操作**：学会处理二进制文件
4. **字符串流**：掌握stringstream的使用
5. **错误处理**：学会处理文件操作错误

## 第三周总结

经过第三周的学习，你已经掌握了：
- **STL容器**：vector、list、map等容器的使用
- **STL算法**：查找、排序、修改等算法的应用
- **智能指针**：现代C++的内存管理技术
- **Lambda表达式**：函数式编程的基础
- **移动语义**：性能优化的重要技术
- **并发编程**：多线程和异步编程基础
- **文件IO**：文件操作和流处理技术

这些都是现代C++开发中的核心技术，为你进入第四周的高级主题和项目实战打下了坚实基础。

[上一天：并发编程基础](/plan/week3/day20/) | [返回第三周总览](/plan/week3/) | [下一周：高级主题与实战](/plan/week4/)
