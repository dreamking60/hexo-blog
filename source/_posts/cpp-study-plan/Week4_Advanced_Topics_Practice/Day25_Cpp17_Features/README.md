# 第25天：C++17新特性

## 学习目标
掌握C++17引入的新特性，学会在实际项目中应用这些特性来提高代码质量和开发效率。

## 今日学习内容

### 1. 结构化绑定 (Structured Bindings)
**概念：** 允许从tuple、pair、array等容器中直接解包多个值。

```cpp
#include <iostream>
#include <tuple>
#include <map>
#include <string>

void structuredBindingExamples() {
    // 1. 从std::pair解包
    std::pair<int, std::string> person{25, "Alice"};
    auto [age, name] = person;
    std::cout << name << " is " << age << " years old" << std::endl;
    
    // 2. 从std::tuple解包
    std::tuple<int, double, std::string> data{42, 3.14, "Hello"};
    auto [i, d, s] = data;
    std::cout << "Values: " << i << ", " << d << ", " << s << std::endl;
    
    // 3. 从数组解包
    int arr[3] = {1, 2, 3};
    auto [x, y, z] = arr;
    std::cout << "Array: " << x << ", " << y << ", " << z << std::endl;
    
    // 4. 在range-based for循环中使用
    std::map<std::string, int> scores{
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}
    };
    
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }
    
    // 5. 从函数返回值解包
    auto getCoordinates = []() -> std::tuple<double, double> {
        return {3.14, 2.71};
    };
    
    auto [pi, e] = getCoordinates();
    std::cout << "π = " << pi << ", e = " << e << std::endl;
}
```

### 2. if constexpr
**概念：** 编译时条件判断，根据模板参数在编译时选择不同的代码路径。

```cpp
#include <type_traits>
#include <vector>
#include <list>

template<typename T>
void printContainer(const T& container) {
    if constexpr (std::is_same_v<T, std::vector<typename T::value_type>>) {
        std::cout << "Vector with " << container.size() << " elements:" << std::endl;
        for (size_t i = 0; i < container.size(); ++i) {
            std::cout << "  [" << i << "] = " << container[i] << std::endl;
        }
    } else if constexpr (std::is_same_v<T, std::list<typename T::value_type>>) {
        std::cout << "List with " << container.size() << " elements:" << std::endl;
        int index = 0;
        for (const auto& item : container) {
            std::cout << "  [" << index++ << "] = " << item << std::endl;
        }
    } else {
        std::cout << "Generic container:" << std::endl;
        for (const auto& item : container) {
            std::cout << "  " << item << std::endl;
        }
    }
}

// 编译时类型检查和优化
template<typename T>
constexpr auto getValue(T&& value) {
    if constexpr (std::is_integral_v<std::decay_t<T>>) {
        return value * 2;  // 整数类型：乘以2
    } else if constexpr (std::is_floating_point_v<std::decay_t<T>>) {
        return value / 2.0;  // 浮点类型：除以2
    } else {
        return value;  // 其他类型：原样返回
    }
}
```

### 3. std::optional
**概念：** 表示可能存在也可能不存在的值，替代使用指针或特殊值表示"无值"的情况。

```cpp
#include <optional>
#include <iostream>
#include <string>

class UserDatabase {
private:
    std::map<int, std::string> users{
        {1, "Alice"}, {2, "Bob"}, {3, "Charlie"}
    };
    
public:
    // 返回optional，避免异常或特殊值
    std::optional<std::string> findUser(int id) const {
        auto it = users.find(id);
        if (it != users.end()) {
            return it->second;  // 隐式转换为optional
        }
        return std::nullopt;  // 明确表示无值
    }
    
    // 安全的数值转换
    static std::optional<int> safeStringToInt(const std::string& str) {
        try {
            return std::stoi(str);
        } catch (const std::exception&) {
            return std::nullopt;
        }
    }
};

void optionalExamples() {
    UserDatabase db;
    
    // 1. 基本使用
    auto user = db.findUser(1);
    if (user) {  // 或者 user.has_value()
        std::cout << "Found user: " << *user << std::endl;  // 或者 user.value()
    } else {
        std::cout << "User not found" << std::endl;
    }
    
    // 2. 使用value_or提供默认值
    std::string userName = db.findUser(999).value_or("Unknown");
    std::cout << "User name: " << userName << std::endl;
    
    // 3. 链式操作
    auto processUser = [](int id) -> std::optional<std::string> {
        UserDatabase db;
        auto user = db.findUser(id);
        if (user) {
            return "Hello, " + *user + "!";
        }
        return std::nullopt;
    };
    
    auto greeting = processUser(2);
    if (greeting) {
        std::cout << *greeting << std::endl;
    }
    
    // 4. 与算法结合使用
    std::vector<std::string> inputs{"123", "abc", "456", "def"};
    std::vector<int> numbers;
    
    for (const auto& input : inputs) {
        auto num = UserDatabase::safeStringToInt(input);
        if (num) {
            numbers.push_back(*num);
        }
    }
    
    std::cout << "Converted numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
```

### 4. std::variant
**概念：** 类型安全的union，可以存储多种类型中的一种。

```cpp
#include <variant>
#include <iostream>
#include <vector>

using Value = std::variant<int, double, std::string>;

class Calculator {
public:
    static Value add(const Value& a, const Value& b) {
        return std::visit([](const auto& x, const auto& y) -> Value {
            using T = std::decay_t<decltype(x)>;
            using U = std::decay_t<decltype(y)>;
            
            if constexpr (std::is_same_v<T, std::string> || std::is_same_v<U, std::string>) {
                // 字符串连接
                return toString(x) + toString(y);
            } else if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
                // 数值相加
                return x + y;
            } else {
                throw std::runtime_error("Unsupported operation");
            }
        }, a, b);
    }
    
    static void printValue(const Value& value) {
        std::visit([](const auto& v) {
            std::cout << "Value: " << v << " (type: " << typeid(v).name() << ")" << std::endl;
        }, value);
    }
    
private:
    template<typename T>
    static std::string toString(const T& value) {
        if constexpr (std::is_same_v<T, std::string>) {
            return value;
        } else {
            return std::to_string(value);
        }
    }
};

// 状态机示例
enum class State { Idle, Running, Paused, Stopped };

using Event = std::variant<
    struct StartEvent {},
    struct PauseEvent {},
    struct ResumeEvent {},
    struct StopEvent {}
>;

class StateMachine {
private:
    State current_state = State::Idle;
    
public:
    void handleEvent(const Event& event) {
        std::visit([this](const auto& e) {
            using EventType = std::decay_t<decltype(e)>;
            
            if constexpr (std::is_same_v<EventType, StartEvent>) {
                if (current_state == State::Idle) {
                    current_state = State::Running;
                    std::cout << "Started" << std::endl;
                }
            } else if constexpr (std::is_same_v<EventType, PauseEvent>) {
                if (current_state == State::Running) {
                    current_state = State::Paused;
                    std::cout << "Paused" << std::endl;
                }
            } else if constexpr (std::is_same_v<EventType, ResumeEvent>) {
                if (current_state == State::Paused) {
                    current_state = State::Running;
                    std::cout << "Resumed" << std::endl;
                }
            } else if constexpr (std::is_same_v<EventType, StopEvent>) {
                current_state = State::Stopped;
                std::cout << "Stopped" << std::endl;
            }
        }, event);
    }
    
    State getState() const { return current_state; }
};

void variantExamples() {
    // 1. 基本使用
    std::vector<Value> values{42, 3.14, std::string("Hello")};
    
    for (const auto& value : values) {
        Calculator::printValue(value);
    }
    
    // 2. 类型检查和访问
    Value v = 42;
    if (std::holds_alternative<int>(v)) {
        std::cout << "Integer value: " << std::get<int>(v) << std::endl;
    }
    
    // 3. 安全访问
    try {
        auto str = std::get<std::string>(v);  // 会抛异常
    } catch (const std::bad_variant_access& e) {
        std::cout << "Bad variant access: " << e.what() << std::endl;
    }
    
    // 4. 使用get_if进行安全访问
    if (auto* ptr = std::get_if<int>(&v)) {
        std::cout << "Integer value (safe): " << *ptr << std::endl;
    }
    
    // 5. 状态机示例
    StateMachine sm;
    sm.handleEvent(StartEvent{});
    sm.handleEvent(PauseEvent{});
    sm.handleEvent(ResumeEvent{});
    sm.handleEvent(StopEvent{});
}
```

### 5. 文件系统库 (std::filesystem)
**概念：** 提供跨平台的文件系统操作接口。

```cpp
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

class FileManager {
public:
    static void demonstrateFilesystem() {
        try {
            // 1. 路径操作
            fs::path currentPath = fs::current_path();
            std::cout << "Current path: " << currentPath << std::endl;
            
            fs::path filePath = currentPath / "example.txt";
            std::cout << "File path: " << filePath << std::endl;
            std::cout << "Filename: " << filePath.filename() << std::endl;
            std::cout << "Extension: " << filePath.extension() << std::endl;
            
            // 2. 创建文件
            {
                std::ofstream file(filePath);
                file << "Hello, C++17 filesystem!" << std::endl;
            }
            
            // 3. 检查文件状态
            if (fs::exists(filePath)) {
                std::cout << "File exists" << std::endl;
                std::cout << "File size: " << fs::file_size(filePath) << " bytes" << std::endl;
                
                auto lastWrite = fs::last_write_time(filePath);
                std::cout << "Last modified: " << 
                    std::chrono::duration_cast<std::chrono::seconds>(
                        lastWrite.time_since_epoch()).count() << std::endl;
            }
            
            // 4. 创建目录
            fs::path dirPath = currentPath / "test_directory";
            fs::create_directory(dirPath);
            
            // 5. 遍历目录
            std::cout << "Directory contents:" << std::endl;
            for (const auto& entry : fs::directory_iterator(currentPath)) {
                std::cout << "  " << entry.path().filename();
                if (entry.is_directory()) {
                    std::cout << " (directory)";
                } else if (entry.is_regular_file()) {
                    std::cout << " (file, " << entry.file_size() << " bytes)";
                }
                std::cout << std::endl;
            }
            
            // 6. 递归遍历
            std::cout << "Recursive directory contents:" << std::endl;
            for (const auto& entry : fs::recursive_directory_iterator(currentPath)) {
                std::cout << "  " << entry.path() << std::endl;
            }
            
            // 7. 复制和移动文件
            fs::path copyPath = currentPath / "example_copy.txt";
            fs::copy_file(filePath, copyPath);
            
            fs::path movePath = currentPath / "example_moved.txt";
            fs::rename(copyPath, movePath);
            
            // 8. 清理
            fs::remove(filePath);
            fs::remove(movePath);
            fs::remove(dirPath);
            
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
    }
    
    // 实用工具函数
    static std::vector<fs::path> findFiles(const fs::path& directory, 
                                          const std::string& extension) {
        std::vector<fs::path> result;
        
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            return result;
        }
        
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && 
                entry.path().extension() == extension) {
                result.push_back(entry.path());
            }
        }
        
        return result;
    }
    
    static uintmax_t calculateDirectorySize(const fs::path& directory) {
        uintmax_t size = 0;
        
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            return size;
        }
        
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                size += entry.file_size();
            }
        }
        
        return size;
    }
};
```

### 6. 其他重要特性

#### 6.1 类模板参数推导 (Class Template Argument Deduction)
```cpp
#include <vector>
#include <utility>

void ctadExamples() {
    // C++17之前需要显式指定模板参数
    // std::vector<int> vec{1, 2, 3, 4, 5};
    
    // C++17可以自动推导
    std::vector vec{1, 2, 3, 4, 5};  // 推导为std::vector<int>
    std::pair p{42, 3.14};           // 推导为std::pair<int, double>
    
    // 自定义类也可以支持
    template<typename T>
    class MyContainer {
        std::vector<T> data;
    public:
        MyContainer(std::initializer_list<T> init) : data(init) {}
        MyContainer(const std::vector<T>& vec) : data(vec) {}
    };
    
    MyContainer container{1, 2, 3, 4};  // 推导为MyContainer<int>
}
```

#### 6.2 内联变量 (Inline Variables)
```cpp
// header.h
class Config {
public:
    inline static const int MAX_SIZE = 1000;  // C++17内联变量
    inline static const std::string DEFAULT_NAME = "Unknown";
};

// 不需要在.cpp文件中定义，避免链接错误
```

#### 6.3 折叠表达式 (Fold Expressions)
```cpp
#include <iostream>

// 可变参数模板的简化
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // 折叠表达式
}

template<typename... Args>
void print(Args... args) {
    ((std::cout << args << " "), ...);  // 折叠表达式
    std::cout << std::endl;
}

template<typename... Args>
bool allTrue(Args... args) {
    return (args && ...);  // 逻辑与折叠
}

void foldExpressionExamples() {
    std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl;
    print("Hello", "World", 42, 3.14);
    std::cout << "All true: " << allTrue(true, true, false) << std::endl;
}
```

## 实践练习

### 练习1：使用结构化绑定优化代码
```cpp
// 重写现有代码，使用结构化绑定提高可读性
// 例如：处理map的迭代、函数返回多个值等
```

### 练习2：用std::optional重构错误处理
```cpp
// 将使用异常或特殊值的错误处理改为使用optional
// 提高代码的安全性和可读性
```

### 练习3：std::variant实现多态
```cpp
// 使用variant替代虚函数实现多态
// 比较性能和代码复杂度
```

## 重点总结

1. **结构化绑定**：简化多值返回和容器遍历
2. **if constexpr**：编译时条件判断，提高模板代码质量
3. **std::optional**：安全的可选值表示
4. **std::variant**：类型安全的union替代方案
5. **文件系统库**：跨平台文件操作
6. **CTAD**：简化模板类的使用
7. **折叠表达式**：简化可变参数模板

## 迁移建议

1. **渐进式采用**：在新代码中使用新特性
2. **兼容性考虑**：确保编译器支持C++17
3. **性能测试**：验证新特性的性能影响
4. **团队培训**：确保团队理解新特性
5. **代码审查**：在代码审查中推广最佳实践

## 注意事项

1. **编译器支持**：确保目标编译器完全支持C++17
2. **标准库实现**：某些特性可能在不同标准库实现中有差异
3. **性能考虑**：新特性可能引入额外开销
4. **可读性平衡**：不要为了使用新特性而牺牲代码可读性
5. **向后兼容**：考虑与旧版本C++的兼容性

## 拓展阅读

- C++17标准文档
- 《C++17 The Complete Guide》
- cppreference.com的C++17特性介绍
- Herb Sutter和Bjarne Stroustrup的相关演讲
