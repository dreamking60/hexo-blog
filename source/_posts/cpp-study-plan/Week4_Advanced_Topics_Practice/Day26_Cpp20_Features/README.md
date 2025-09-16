# 第26天：C++20新特性

## 学习目标
掌握C++20的核心新特性，学会使用概念、协程、模块、范围等现代C++特性来编写更安全、更高效的代码。

## 今日学习内容

### 1. 概念 (Concepts)
**概念：** 为模板参数提供编译时约束，提高模板代码的可读性和错误信息质量。

```cpp
#include <concepts>
#include <iostream>
#include <vector>
#include <type_traits>

// 基本概念定义
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept Arithmetic = Integral<T> || FloatingPoint<T>;

// 更复杂的概念
template<typename T>
concept Container = requires(T t) {
    t.begin();
    t.end();
    t.size();
    typename T::value_type;
};

template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

// 使用概念约束函数模板
template<Arithmetic T>
T multiply(T a, T b) {
    return a * b;
}

template<Container C>
void printContainer(const C& container) {
    std::cout << "Container with " << container.size() << " elements: ";
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 概念与类模板
template<Sortable T>
class SortedVector {
private:
    std::vector<T> data;
    
public:
    void insert(const T& value) {
        auto it = std::lower_bound(data.begin(), data.end(), value);
        data.insert(it, value);
    }
    
    bool contains(const T& value) const {
        return std::binary_search(data.begin(), data.end(), value);
    }
    
    const std::vector<T>& getData() const { return data; }
};

// 概念的组合和特化
template<typename T>
concept SignedIntegral = Integral<T> && std::is_signed_v<T>;

template<typename T>
concept UnsignedIntegral = Integral<T> && std::is_unsigned_v<T>;

template<SignedIntegral T>
T abs_value(T x) {
    return x < 0 ? -x : x;
}

template<UnsignedIntegral T>
T abs_value(T x) {
    return x;  // 无符号数总是非负的
}

void conceptExamples() {
    // 使用概念约束的函数
    std::cout << multiply(5, 3) << std::endl;        // int
    std::cout << multiply(2.5, 4.0) << std::endl;   // double
    
    // 容器概念
    std::vector<int> vec{1, 2, 3, 4, 5};
    printContainer(vec);
    
    // 排序容器
    SortedVector<int> sortedVec;
    sortedVec.insert(5);
    sortedVec.insert(2);
    sortedVec.insert(8);
    sortedVec.insert(1);
    
    printContainer(sortedVec.getData());
    
    // 概念特化
    std::cout << "abs(-5) = " << abs_value(-5) << std::endl;
    std::cout << "abs(5u) = " << abs_value(5u) << std::endl;
}
```

### 2. 范围 (Ranges)
**概念：** 提供更直观、更安全的容器操作方式，支持函数式编程风格。

```cpp
#include <ranges>
#include <vector>
#include <algorithm>
#include <iostream>

namespace ranges = std::ranges;
namespace views = std::views;

void rangesExamples() {
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 1. 基本范围操作
    std::cout << "Original: ";
    ranges::copy(numbers, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 2. 视图组合（惰性求值）
    auto evenSquares = numbers 
        | views::filter([](int n) { return n % 2 == 0; })  // 过滤偶数
        | views::transform([](int n) { return n * n; });   // 平方
    
    std::cout << "Even squares: ";
    ranges::copy(evenSquares, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 3. 更复杂的管道操作
    auto result = numbers
        | views::take(5)                                    // 取前5个
        | views::reverse                                    // 反转
        | views::transform([](int n) { return n * 2; });   // 乘以2
    
    std::cout << "Complex pipeline: ";
    ranges::copy(result, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // 4. 范围算法
    std::vector<std::string> words{"hello", "world", "cpp", "ranges"};
    
    // 排序
    ranges::sort(words);
    std::cout << "Sorted words: ";
    ranges::copy(words, std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    
    // 查找
    auto it = ranges::find(words, "cpp");
    if (it != words.end()) {
        std::cout << "Found: " << *it << std::endl;
    }
    
    // 计数
    auto count = ranges::count_if(words, [](const std::string& s) {
        return s.length() > 3;
    });
    std::cout << "Words longer than 3 chars: " << count << std::endl;
    
    // 5. 自定义范围
    auto fibonacci = views::iota(0)  // 无限序列
        | views::transform([](int n) {
            static std::vector<long long> fib{0, 1};
            while (fib.size() <= n) {
                fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
            }
            return fib[n];
        })
        | views::take(10);  // 只取前10个
    
    std::cout << "Fibonacci: ";
    ranges::copy(fibonacci, std::ostream_iterator<long long>(std::cout, " "));
    std::cout << std::endl;
}

// 自定义范围适配器
template<ranges::range R>
class ChunkView : public ranges::view_interface<ChunkView<R>> {
private:
    R base_;
    std::size_t chunk_size_;
    
public:
    ChunkView(R base, std::size_t chunk_size) 
        : base_(std::move(base)), chunk_size_(chunk_size) {}
    
    auto begin() { return iterator(ranges::begin(base_), chunk_size_); }
    auto end() { return ranges::end(base_); }
    
private:
    class iterator {
        ranges::iterator_t<R> current_;
        std::size_t chunk_size_;
        
    public:
        iterator(ranges::iterator_t<R> current, std::size_t chunk_size)
            : current_(current), chunk_size_(chunk_size) {}
        
        // 实现迭代器接口...
    };
};
```

### 3. 协程 (Coroutines)
**概念：** 支持协作式多任务，简化异步编程。

```cpp
#include <coroutine>
#include <iostream>
#include <vector>
#include <optional>

// 简单的生成器协程
template<typename T>
class Generator {
public:
    struct promise_type {
        T current_value;
        
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
    
    ~Generator() {
        if (coro) {
            coro.destroy();
        }
    }
    
    // 移动构造和赋值
    Generator(Generator&& other) noexcept : coro(other.coro) {
        other.coro = {};
    }
    
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coro) {
                coro.destroy();
            }
            coro = other.coro;
            other.coro = {};
        }
        return *this;
    }
    
    // 禁止拷贝
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    
    // 迭代器接口
    class iterator {
        std::coroutine_handle<promise_type> coro_;
        
    public:
        iterator(std::coroutine_handle<promise_type> coro) : coro_(coro) {}
        
        iterator& operator++() {
            coro_.resume();
            if (coro_.done()) {
                coro_ = {};
            }
            return *this;
        }
        
        T operator*() const {
            return coro_.promise().current_value;
        }
        
        bool operator==(const iterator& other) const {
            return coro_ == other.coro_;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };
    
    iterator begin() {
        if (coro) {
            coro.resume();
            if (coro.done()) {
                return iterator{};
            }
        }
        return iterator{coro};
    }
    
    iterator end() {
        return iterator{};
    }
};

// 使用协程生成斐波那契数列
Generator<long long> fibonacci() {
    long long a = 0, b = 1;
    while (true) {
        co_yield a;
        auto temp = a;
        a = b;
        b = temp + b;
    }
}

// 使用协程生成素数
Generator<int> primes() {
    std::vector<int> known_primes;
    int candidate = 2;
    
    while (true) {
        bool is_prime = true;
        for (int prime : known_primes) {
            if (prime * prime > candidate) break;
            if (candidate % prime == 0) {
                is_prime = false;
                break;
            }
        }
        
        if (is_prime) {
            known_primes.push_back(candidate);
            co_yield candidate;
        }
        
        candidate++;
    }
}

void coroutineExamples() {
    // 斐波那契数列
    std::cout << "First 10 Fibonacci numbers: ";
    auto fib = fibonacci();
    auto it = fib.begin();
    for (int i = 0; i < 10; ++i, ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 素数生成
    std::cout << "First 10 primes: ";
    auto prime_gen = primes();
    auto prime_it = prime_gen.begin();
    for (int i = 0; i < 10; ++i, ++prime_it) {
        std::cout << *prime_it << " ";
    }
    std::cout << std::endl;
}
```

### 4. 三路比较运算符 (Spaceship Operator)
**概念：** `<=>`运算符，简化比较操作的实现。

```cpp
#include <compare>
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    double salary;
    
public:
    Person(std::string n, int a, double s) : name(n), age(a), salary(s) {}
    
    // 三路比较运算符 - 自动生成所有比较运算符
    auto operator<=>(const Person& other) const {
        // 按优先级比较：先姓名，再年龄，最后薪水
        if (auto cmp = name <=> other.name; cmp != 0) {
            return cmp;
        }
        if (auto cmp = age <=> other.age; cmp != 0) {
            return cmp;
        }
        return salary <=> other.salary;
    }
    
    // 相等比较（可选，如果需要特殊的相等逻辑）
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age && salary == other.salary;
    }
    
    // 用于输出
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.name << "(" << p.age << ", $" << p.salary << ")";
    }
};

// 自定义比较类型
enum class Grade { F, D, C, B, A };

struct Student {
    std::string name;
    Grade grade;
    
    // 只定义三路比较，其他比较运算符自动生成
    std::strong_ordering operator<=>(const Student& other) const {
        if (auto cmp = name <=> other.name; cmp != 0) {
            return cmp;
        }
        return grade <=> other.grade;
    }
    
    bool operator==(const Student& other) const = default;  // 默认相等比较
};

void spaceshipOperatorExamples() {
    Person alice("Alice", 30, 50000);
    Person bob("Bob", 25, 45000);
    Person charlie("Alice", 35, 60000);
    
    std::cout << "Comparing persons:" << std::endl;
    std::cout << alice << " vs " << bob << ": ";
    
    if (alice < bob) {
        std::cout << "Alice < Bob" << std::endl;
    } else if (alice > bob) {
        std::cout << "Alice > Bob" << std::endl;
    } else {
        std::cout << "Alice == Bob" << std::endl;
    }
    
    std::cout << alice << " vs " << charlie << ": ";
    if (alice < charlie) {
        std::cout << "Alice < Charlie" << std::endl;
    } else if (alice > charlie) {
        std::cout << "Alice > Charlie" << std::endl;
    } else {
        std::cout << "Alice == Charlie" << std::endl;
    }
    
    // 使用三路比较的结果
    auto cmp = alice <=> bob;
    if (cmp < 0) {
        std::cout << "Alice comes before Bob" << std::endl;
    } else if (cmp > 0) {
        std::cout << "Alice comes after Bob" << std::endl;
    } else {
        std::cout << "Alice and Bob are equivalent" << std::endl;
    }
}
```

### 5. 其他重要特性

#### 5.1 指定初始化器 (Designated Initializers)
```cpp
struct Point3D {
    double x, y, z;
};

struct Config {
    std::string host;
    int port;
    bool ssl_enabled;
    int timeout;
};

void designatedInitializerExamples() {
    // 指定初始化器 - 提高可读性
    Point3D p1{.x = 1.0, .y = 2.0, .z = 3.0};
    Point3D p2{.z = 5.0, .x = 1.0};  // 可以跳过某些字段，顺序可以不同
    
    Config cfg{
        .host = "localhost",
        .port = 8080,
        .ssl_enabled = true,
        .timeout = 30
    };
    
    std::cout << "Point: (" << p1.x << ", " << p1.y << ", " << p1.z << ")" << std::endl;
    std::cout << "Config: " << cfg.host << ":" << cfg.port << std::endl;
}
```

#### 5.2 模板语法改进
```cpp
// 缩写函数模板
void print(auto value) {  // 等价于 template<typename T> void print(T value)
    std::cout << value << std::endl;
}

// 约束的缩写语法
void processNumber(std::integral auto number) {  // 使用概念约束
    std::cout << "Processing integer: " << number << std::endl;
}

void processFloating(std::floating_point auto number) {
    std::cout << "Processing float: " << number << std::endl;
}

// 泛型lambda改进
auto lambda = []<typename T>(T value) {  // 模板lambda
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else {
        return value;
    }
};
```

#### 5.3 consteval和constinit
```cpp
// consteval - 强制编译时计算
consteval int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// constinit - 保证编译时初始化
constinit int global_value = factorial(5);  // 必须在编译时计算

void constEvalExamples() {
    constexpr int result = factorial(6);  // 编译时计算
    std::cout << "6! = " << result << std::endl;
    std::cout << "Global value: " << global_value << std::endl;
}
```

## 实践练习

### 练习1：使用概念设计安全的容器
```cpp
// 设计一个使用概念约束的安全容器类
// 只接受可比较的类型，提供类型安全的操作
```

### 练习2：用协程实现异步任务
```cpp
// 实现一个简单的任务调度器
// 使用协程处理异步操作
```

### 练习3：范围算法应用
```cpp
// 使用ranges重构复杂的数据处理逻辑
// 比较传统STL算法和ranges的差异
```

## 重点总结

1. **概念**：为模板提供编译时约束，提高代码安全性
2. **范围**：函数式编程风格，简化容器操作
3. **协程**：简化异步编程，支持生成器模式
4. **三路比较**：简化比较操作的实现
5. **指定初始化**：提高结构体初始化的可读性
6. **模板改进**：缩写语法，约束语法
7. **consteval/constinit**：更强的编译时保证

## 迁移和采用建议

1. **渐进式迁移**：优先在新代码中使用新特性
2. **编译器支持**：确保目标编译器完全支持C++20
3. **团队培训**：新特性需要团队学习和适应
4. **性能测试**：验证新特性对性能的影响
5. **代码审查**：建立C++20最佳实践

## 注意事项

1. **编译器兼容性**：C++20支持程度因编译器而异
2. **编译时间**：某些特性可能增加编译时间
3. **调试支持**：调试器对新特性的支持可能有限
4. **学习曲线**：概念和协程有一定学习难度
5. **向后兼容**：考虑与旧版本代码的兼容性

## 拓展阅读

- C++20标准文档
- 《C++20 The Complete Guide》
- cppreference.com的C++20特性介绍
- CppCon关于C++20的演讲
- 各编译器的C++20支持状态
