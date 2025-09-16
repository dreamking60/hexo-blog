---
title: C++ 学习计划 - 第25天：C++17新特性
date: 2025-09-16 10:28:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week4
    - Day25
layout: page
menu_id: plan
permalink: /plan/week4/day25/
---

# 第25天：C++17新特性

## 学习目标
了解和掌握C++17标准引入的新特性，学会使用现代C++特性提高代码的可读性、安全性和性能。

## 学习资源链接

### 📚 官方文档和教程
- [C++17 Reference](https://en.cppreference.com/w/cpp/17) - C++17官方参考文档
- [C++17 Features](https://www.modernescpp.com/index.php/c-17-core) - C++17核心特性介绍
- [C++17 in Detail](https://leanpub.com/cpp17indetail) - C++17详细指南
- [ISO C++17 Standard](https://www.iso.org/standard/68564.html) - C++17标准文档

### 🎥 视频教程
- [C++17 Features Overview](https://www.youtube.com/watch?v=QpFjOlzg1r4) - C++17特性概览
- [CppCon 2017 C++17 Talks](https://www.youtube.com/results?search_query=cppcon+2017+c%2B%2B17) - CppCon 2017 C++17演讲
- [The Cherno C++17](https://www.youtube.com/watch?v=QpFjOlzg1r4) - C++17新特性讲解

### 📖 深入阅读
- [Effective Modern C++](https://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996) - 现代C++最佳实践
- [C++17 STL Cookbook](https://www.amazon.com/STL-Cookbook-enhancements-programming-expressions/dp/178712049X) - C++17 STL指南
- [Professional C++](https://www.amazon.com/Professional-C-Marc-Gregoire/dp/1119695406) - 专业C++编程

### 🔧 编译器支持
- [GCC C++17 Support](https://gcc.gnu.org/projects/cxx-status.html#cxx17) - GCC对C++17的支持
- [Clang C++17 Support](https://clang.llvm.org/cxx_status.html#cxx17) - Clang对C++17的支持
- [MSVC C++17 Support](https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance) - MSVC对C++17的支持

## 学习内容

### 1. 结构化绑定 (Structured Bindings)

结构化绑定允许从数组、tuple、pair或自定义类型中解包多个值到单独的变量中。

```cpp
#include <iostream>
#include <tuple>
#include <map>
#include <array>

// 基本使用
void structured_binding_basics() {
    // 1. 数组解构
    int arr[3] = {1, 2, 3};
    auto [a, b, c] = arr;
    std::cout << "Array: " << a << ", " << b << ", " << c << std::endl;
    
    // 2. std::pair 解构
    std::pair<int, std::string> p = {42, "hello"};
    auto [id, message] = p;
    std::cout << "Pair: " << id << ", " << message << std::endl;
    
    // 3. std::tuple 解构
    std::tuple<int, double, std::string> t = {1, 3.14, "world"};
    auto [num, pi, str] = t;
    std::cout << "Tuple: " << num << ", " << pi << ", " << str << std::endl;
}

// 在循环中使用
void structured_binding_in_loops() {
    std::map<std::string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };
    
    // 遍历map时自动解构key-value对
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }
}

// 自定义类型支持结构化绑定
struct Point {
    double x, y, z;
};

// 方法1：使用tuple-like接口
template<size_t N>
auto get(const Point& p) {
    if constexpr (N == 0) return p.x;
    else if constexpr (N == 1) return p.y;
    else if constexpr (N == 2) return p.z;
}

// 特化std::tuple_size和std::tuple_element
template<>
struct std::tuple_size<Point> : std::integral_constant<size_t, 3> {};

template<size_t N>
struct std::tuple_element<N, Point> {
    using type = double;
};

void custom_structured_binding() {
    Point p{1.0, 2.0, 3.0};
    auto [x, y, z] = p;
    std::cout << "Point: (" << x << ", " << y << ", " << z << ")" << std::endl;
}
```

### 2. if constexpr

`if constexpr` 允许在编译时进行条件编译，特别适用于模板编程。

```cpp
#include <type_traits>
#include <iostream>
#include <vector>
#include <string>

// 基本使用
template<typename T>
void process_type() {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Processing integer type" << std::endl;
        T value = 42;
        std::cout << "Value: " << value << std::endl;
    }
    else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Processing floating point type" << std::endl;
        T value = 3.14;
        std::cout << "Value: " << value << std::endl;
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "Processing string type" << std::endl;
        T value = "Hello, World!";
        std::cout << "Value: " << value << std::endl;
    }
    else {
        std::cout << "Processing other type" << std::endl;
    }
}

// 递归模板中的应用
template<typename T>
constexpr auto factorial(T n) {
    if constexpr (std::is_integral_v<T>) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    } else {
        static_assert(std::is_integral_v<T>, "Factorial requires integral type");
    }
}

// 容器特化处理
template<typename Container>
void print_container(const Container& container) {
    std::cout << "Container contents: ";
    
    if constexpr (std::is_same_v<Container, std::string>) {
        std::cout << "\"" << container << "\"";
    }
    else {
        std::cout << "[";
        bool first = true;
        for (const auto& item : container) {
            if (!first) std::cout << ", ";
            std::cout << item;
            first = false;
        }
        std::cout << "]";
    }
    std::cout << std::endl;
}

void if_constexpr_examples() {
    process_type<int>();
    process_type<double>();
    process_type<std::string>();
    
    constexpr auto fact5 = factorial(5);
    std::cout << "5! = " << fact5 << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string str = "Hello";
    print_container(vec);
    print_container(str);
}
```

### 3. std::optional

`std::optional` 表示一个可能存在也可能不存在的值，替代了传统的指针或特殊值来表示"无值"状态。

```cpp
#include <optional>
#include <iostream>
#include <string>
#include <vector>

class Database {
private:
    std::vector<std::pair<int, std::string>> users = {
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}
    };
    
public:
    // 返回optional而不是指针或异常
    std::optional<std::string> findUserName(int id) {
        for (const auto& [userId, userName] : users) {
            if (userId == id) {
                return userName; // 隐式构造optional
            }
        }
        return std::nullopt; // 明确表示无值
    }
    
    // 解析字符串为整数
    std::optional<int> parseInteger(const std::string& str) {
        try {
            return std::stoi(str);
        } catch (const std::exception&) {
            return std::nullopt;
        }
    }
};

void optional_examples() {
    Database db;
    
    // 1. 基本使用
    auto userName = db.findUserName(2);
    if (userName.has_value()) {
        std::cout << "Found user: " << userName.value() << std::endl;
    } else {
        std::cout << "User not found" << std::endl;
    }
    
    // 2. 使用value_or提供默认值
    auto unknownUser = db.findUserName(99);
    std::cout << "User name: " << unknownUser.value_or("Unknown") << std::endl;
    
    // 3. 解构optional
    if (auto name = db.findUserName(1); name) {
        std::cout << "User 1: " << *name << std::endl;
    }
    
    // 4. 链式操作
    auto result = db.parseInteger("42");
    if (result) {
        std::cout << "Parsed integer: " << *result << std::endl;
    }
    
    // 5. 使用and_then进行链式操作 (C++23特性，这里展示概念)
    auto processUser = [&](int id) -> std::optional<std::string> {
        if (auto name = db.findUserName(id); name) {
            return "Hello, " + *name + "!";
        }
        return std::nullopt;
    };
    
    if (auto greeting = processUser(1); greeting) {
        std::cout << *greeting << std::endl;
    }
}

// optional作为成员变量
class Configuration {
private:
    std::optional<std::string> database_url;
    std::optional<int> port;
    std::optional<bool> debug_mode;
    
public:
    void setDatabaseUrl(const std::string& url) {
        database_url = url;
    }
    
    void setPort(int p) {
        port = p;
    }
    
    void setDebugMode(bool debug) {
        debug_mode = debug;
    }
    
    std::string getDatabaseUrl() const {
        return database_url.value_or("localhost:5432");
    }
    
    int getPort() const {
        return port.value_or(8080);
    }
    
    bool isDebugMode() const {
        return debug_mode.value_or(false);
    }
    
    void printConfig() const {
        std::cout << "Database URL: " << getDatabaseUrl() << std::endl;
        std::cout << "Port: " << getPort() << std::endl;
        std::cout << "Debug mode: " << (isDebugMode() ? "on" : "off") << std::endl;
    }
};
```

### 4. std::variant

`std::variant` 是一个类型安全的union，可以在运行时持有多种类型中的一种。

```cpp
#include <variant>
#include <iostream>
#include <string>
#include <vector>

// 基本使用
using Value = std::variant<int, double, std::string>;

void variant_basics() {
    Value v1 = 42;
    Value v2 = 3.14;
    Value v3 = "hello";
    
    // 1. 使用std::get检查和获取值
    try {
        std::cout << "v1 as int: " << std::get<int>(v1) << std::endl;
        std::cout << "v2 as double: " << std::get<double>(v2) << std::endl;
        std::cout << "v3 as string: " << std::get<std::string>(v3) << std::endl;
        
        // 这会抛出异常
        // std::cout << std::get<int>(v2) << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cout << "Bad variant access: " << e.what() << std::endl;
    }
    
    // 2. 使用std::get_if安全获取值
    if (auto* pval = std::get_if<int>(&v1)) {
        std::cout << "v1 contains int: " << *pval << std::endl;
    }
    
    // 3. 检查当前持有的类型索引
    std::cout << "v1 index: " << v1.index() << std::endl; // 0 (int)
    std::cout << "v2 index: " << v2.index() << std::endl; // 1 (double)
    std::cout << "v3 index: " << v3.index() << std::endl; // 2 (string)
    
    // 4. 使用std::holds_alternative检查类型
    if (std::holds_alternative<std::string>(v3)) {
        std::cout << "v3 holds a string" << std::endl;
    }
}

// 使用std::visit处理variant
struct VariantPrinter {
    void operator()(int i) const {
        std::cout << "Integer: " << i << std::endl;
    }
    
    void operator()(double d) const {
        std::cout << "Double: " << d << std::endl;
    }
    
    void operator()(const std::string& s) const {
        std::cout << "String: " << s << std::endl;
    }
};

void variant_visitor() {
    std::vector<Value> values = {42, 3.14, "world", 100, 2.71};
    
    for (const auto& value : values) {
        // 使用函数对象访问
        std::visit(VariantPrinter{}, value);
        
        // 使用lambda访问
        std::visit([](const auto& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, int>) {
                std::cout << "  -> This is an integer\n";
            } else if constexpr (std::is_same_v<T, double>) {
                std::cout << "  -> This is a double\n";
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "  -> This is a string\n";
            }
        }, value);
    }
}

// 实际应用：JSON值表示
using JsonValue = std::variant<
    std::nullptr_t,
    bool,
    int,
    double,
    std::string,
    std::vector<JsonValue>,
    std::map<std::string, JsonValue>
>;

class JsonPrinter {
public:
    void operator()(std::nullptr_t) const {
        std::cout << "null";
    }
    
    void operator()(bool b) const {
        std::cout << (b ? "true" : "false");
    }
    
    void operator()(int i) const {
        std::cout << i;
    }
    
    void operator()(double d) const {
        std::cout << d;
    }
    
    void operator()(const std::string& s) const {
        std::cout << "\"" << s << "\"";
    }
    
    void operator()(const std::vector<JsonValue>& arr) const {
        std::cout << "[";
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::visit(*this, arr[i]);
        }
        std::cout << "]";
    }
    
    void operator()(const std::map<std::string, JsonValue>& obj) const {
        std::cout << "{";
        bool first = true;
        for (const auto& [key, value] : obj) {
            if (!first) std::cout << ", ";
            std::cout << "\"" << key << "\": ";
            std::visit(*this, value);
            first = false;
        }
        std::cout << "}";
    }
};
```

### 5. 文件系统库 (std::filesystem)

C++17引入了标准文件系统库，提供了跨平台的文件和目录操作。

```cpp
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

void filesystem_examples() {
    // 1. 路径操作
    fs::path p1 = "/home/user/documents/file.txt";
    fs::path p2 = "C:\\Users\\User\\Documents\\file.txt";
    
    std::cout << "Filename: " << p1.filename() << std::endl;
    std::cout << "Extension: " << p1.extension() << std::endl;
    std::cout << "Parent path: " << p1.parent_path() << std::endl;
    std::cout << "Stem: " << p1.stem() << std::endl;
    
    // 2. 路径构建
    fs::path base = "/tmp";
    fs::path filename = "test.txt";
    fs::path full_path = base / filename;
    std::cout << "Full path: " << full_path << std::endl;
    
    // 3. 文件和目录检查
    fs::path current_dir = fs::current_path();
    std::cout << "Current directory: " << current_dir << std::endl;
    
    if (fs::exists(current_dir)) {
        std::cout << "Current directory exists" << std::endl;
    }
    
    if (fs::is_directory(current_dir)) {
        std::cout << "It's a directory" << std::endl;
    }
    
    // 4. 创建目录
    fs::path test_dir = current_dir / "test_directory";
    try {
        if (fs::create_directory(test_dir)) {
            std::cout << "Directory created: " << test_dir << std::endl;
        }
        
        // 创建多级目录
        fs::path nested_dir = test_dir / "sub1" / "sub2";
        fs::create_directories(nested_dir);
        std::cout << "Nested directories created: " << nested_dir << std::endl;
        
    } catch (const fs::filesystem_error& e) {
        std::cout << "Filesystem error: " << e.what() << std::endl;
    }
    
    // 5. 遍历目录
    std::cout << "\nDirectory contents:" << std::endl;
    for (const auto& entry : fs::directory_iterator(current_dir)) {
        std::cout << entry.path().filename();
        if (entry.is_directory()) {
            std::cout << " [DIR]";
        } else if (entry.is_regular_file()) {
            std::cout << " [FILE] (" << entry.file_size() << " bytes)";
        }
        std::cout << std::endl;
    }
    
    // 6. 递归遍历
    std::cout << "\nRecursive directory contents:" << std::endl;
    for (const auto& entry : fs::recursive_directory_iterator(current_dir)) {
        // 计算深度
        auto relative_path = fs::relative(entry.path(), current_dir);
        auto depth = std::distance(relative_path.begin(), relative_path.end()) - 1;
        
        std::cout << std::string(depth * 2, ' ') << entry.path().filename();
        if (entry.is_directory()) {
            std::cout << "/";
        }
        std::cout << std::endl;
    }
    
    // 7. 文件操作
    fs::path test_file = test_dir / "example.txt";
    
    // 创建文件
    {
        std::ofstream ofs(test_file);
        ofs << "Hello, filesystem!" << std::endl;
    }
    
    if (fs::exists(test_file)) {
        // 获取文件信息
        auto file_size = fs::file_size(test_file);
        auto last_write_time = fs::last_write_time(test_file);
        
        std::cout << "\nFile info:" << std::endl;
        std::cout << "Size: " << file_size << " bytes" << std::endl;
        
        // 文件权限
        auto perms = fs::status(test_file).permissions();
        std::cout << "Permissions: ";
        std::cout << ((perms & fs::perms::owner_read) != fs::perms::none ? "r" : "-");
        std::cout << ((perms & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
        std::cout << ((perms & fs::perms::owner_exec) != fs::perms::none ? "x" : "-");
        std::cout << std::endl;
        
        // 复制文件
        fs::path copy_file = test_dir / "copy_example.txt";
        fs::copy_file(test_file, copy_file);
        std::cout << "File copied to: " << copy_file << std::endl;
        
        // 移动/重命名文件
        fs::path renamed_file = test_dir / "renamed_example.txt";
        fs::rename(copy_file, renamed_file);
        std::cout << "File renamed to: " << renamed_file << std::endl;
    }
    
    // 8. 清理
    try {
        fs::remove_all(test_dir);
        std::cout << "Test directory removed" << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error removing directory: " << e.what() << std::endl;
    }
}
```

## 其他C++17特性

### 内联变量 (Inline Variables)
```cpp
// 头文件中定义内联变量
class Config {
public:
    static inline std::string app_name = "MyApp";
    static inline int version = 1;
};

// 全局内联变量
inline constexpr double PI = 3.14159265359;
```

### 折叠表达式 (Fold Expressions)
```cpp
// 可变参数模板的折叠表达式
template<typename... Args>
auto sum(Args... args) {
    return (args + ...); // 右折叠
}

template<typename... Args>
void print(Args... args) {
    ((std::cout << args << " "), ...); // 左折叠
    std::cout << std::endl;
}

void fold_expressions_example() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl; // 15
    print("Hello", "World", 42, 3.14); // Hello World 42 3.14
}
```

## 实践练习

### 练习1：配置管理器
使用std::optional和std::variant实现一个配置管理器：
- 支持多种配置值类型
- 支持默认值
- 支持配置验证

### 练习2：文件处理工具
使用std::filesystem实现一个文件处理工具：
- 递归搜索文件
- 文件过滤和分类
- 批量文件操作

### 练习3：JSON解析器
使用std::variant实现一个简单的JSON解析器：
- 支持基本JSON类型
- 支持嵌套结构
- 支持序列化和反序列化

### 练习4：模板元编程
使用if constexpr实现类型特性检查：
- 容器类型检查
- 成员函数存在性检查
- 编译时算法选择

## 今日总结
通过学习C++17新特性，你应该掌握：
1. 结构化绑定的使用方法和应用场景
2. if constexpr在模板编程中的应用
3. std::optional处理可选值的最佳实践
4. std::variant实现类型安全的联合体
5. std::filesystem进行文件系统操作

## 明天预告
明天我们将学习C++20的新特性，包括概念(Concepts)、协程(Coroutines)、模块(Modules)等更加现代的C++特性。

[返回第四周](/plan/week4/) | [上一天：第24天](/plan/week4/day24/) | [下一天：第26天](/plan/week4/day26/)
