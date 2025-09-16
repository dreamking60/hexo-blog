# 第18天：Lambda表达式复习

## 学习目标
掌握C++11引入的Lambda表达式，理解函数式编程思想，学会使用Lambda表达式简化代码和提高可读性。

## 学习内容

### 1. Lambda表达式概述

Lambda表达式是C++11引入的匿名函数，它允许在需要函数的地方内联定义函数，使代码更加简洁和灵活。

#### 基本语法
```cpp
[捕获列表](参数列表) -> 返回类型 { 函数体 }
```

### 2. 基本Lambda表达式

#### 简单Lambda
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void basicLambda() {
    // 最简单的Lambda表达式
    auto lambda = []() { std::cout << "Hello Lambda!" << std::endl; };
    lambda();
    
    // 带参数的Lambda
    auto add = [](int a, int b) { return a + b; };
    std::cout << "3 + 4 = " << add(3, 4) << std::endl;
    
    // 多行Lambda
    auto complex = [](int x) {
        if (x > 0) {
            return x * 2;
        } else {
            return -x;
        }
    };
    std::cout << "complex(5) = " << complex(5) << std::endl;
    std::cout << "complex(-3) = " << complex(-3) << std::endl;
}
```

#### 与STL算法结合
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

void lambdaWithSTL() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 使用Lambda过滤偶数
    std::vector<int> evens;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens),
                 [](int n) { return n % 2 == 0; });
    
    std::cout << "偶数: ";
    for (int n : evens) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 使用Lambda转换
    std::vector<int> squares;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares),
                   [](int n) { return n * n; });
    
    std::cout << "平方: ";
    for (int n : squares) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 使用Lambda排序
    std::sort(numbers.begin(), numbers.end(),
              [](int a, int b) { return a > b; });  // 降序
    
    std::cout << "降序排序: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
```

### 3. 捕获列表 (Capture List)

捕获列表定义了Lambda表达式可以访问的外部变量。

#### 值捕获
```cpp
#include <iostream>

void valueCapture() {
    int x = 10;
    int y = 20;
    
    // 值捕获
    auto lambda1 = [x, y]() {
        std::cout << "x = " << x << ", y = " << y << std::endl;
    };
    
    lambda1();
    
    // 修改外部变量不会影响Lambda中的值
    x = 100;
    y = 200;
    lambda1();  // 仍然输出原来的值
}
```

#### 引用捕获
```cpp
#include <iostream>

void referenceCapture() {
    int x = 10;
    int y = 20;
    
    // 引用捕获
    auto lambda1 = [&x, &y]() {
        std::cout << "x = " << x << ", y = " << y << std::endl;
        x = 100;  // 修改外部变量
        y = 200;
    };
    
    lambda1();
    std::cout << "修改后: x = " << x << ", y = " << y << std::endl;
}
```

#### 混合捕获
```cpp
#include <iostream>

void mixedCapture() {
    int a = 1, b = 2, c = 3, d = 4;
    
    // 混合捕获：a值捕获，b引用捕获，c值捕获，d引用捕获
    auto lambda1 = [a, &b, c, &d]() {
        std::cout << "a = " << a << ", b = " << b 
                  << ", c = " << c << ", d = " << d << std::endl;
        b = 20;  // 可以修改
        d = 40;  // 可以修改
        // a = 10;  // 编译错误，不能修改值捕获的变量
        // c = 30;  // 编译错误，不能修改值捕获的变量
    };
    
    lambda1();
    std::cout << "修改后: b = " << b << ", d = " << d << std::endl;
}
```

#### 默认捕获
```cpp
#include <iostream>

void defaultCapture() {
    int x = 10;
    int y = 20;
    int z = 30;
    
    // 默认值捕获所有变量
    auto lambda1 = [=]() {
        std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
    };
    
    // 默认引用捕获所有变量
    auto lambda2 = [&]() {
        std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
        x = 100;  // 可以修改
    };
    
    // 混合默认捕获
    auto lambda3 = [=, &x]() {  // 默认值捕获，但x引用捕获
        std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
        x = 200;  // 可以修改x
    };
    
    lambda1();
    lambda2();
    lambda3();
}
```

### 4. 参数列表和返回类型

#### 参数列表
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void parameterList() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 无参数
    auto lambda1 = []() { std::cout << "无参数Lambda" << std::endl; };
    lambda1();
    
    // 单参数
    auto lambda2 = [](int x) { return x * 2; };
    std::cout << "lambda2(5) = " << lambda2(5) << std::endl;
    
    // 多参数
    auto lambda3 = [](int a, int b, int c) { return a + b + c; };
    std::cout << "lambda3(1, 2, 3) = " << lambda3(1, 2, 3) << std::endl;
    
    // 与STL算法结合
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0,
                              [](int acc, int n) { return acc + n * n; });
    std::cout << "平方和: " << sum << std::endl;
}
```

#### 返回类型
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void returnType() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 自动推导返回类型
    auto lambda1 = [](int x) { return x * 2; };
    std::cout << "lambda1(5) = " << lambda1(5) << std::endl;
    
    // 显式指定返回类型
    auto lambda2 = [](int x) -> int { return x * 2; };
    auto lambda3 = [](int x) -> double { return x * 2.5; };
    
    // 复杂返回类型
    auto lambda4 = [](int x) -> std::pair<int, int> {
        return {x, x * x};
    };
    
    auto result = lambda4(5);
    std::cout << "lambda4(5) = (" << result.first << ", " << result.second << ")" << std::endl;
    
    // 条件返回
    auto lambda5 = [](int x) -> int {
        if (x > 0) {
            return x * 2;
        } else {
            return -x;
        }
    };
    
    std::cout << "lambda5(5) = " << lambda5(5) << std::endl;
    std::cout << "lambda5(-3) = " << lambda5(-3) << std::endl;
}
```

### 5. 泛型Lambda (C++14)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void genericLambda() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<double> doubles = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    // 泛型Lambda
    auto print = [](const auto& value) {
        std::cout << value << " ";
    };
    
    std::cout << "整数: ";
    for (const auto& n : numbers) {
        print(n);
    }
    std::cout << std::endl;
    
    std::cout << "浮点数: ";
    for (const auto& d : doubles) {
        print(d);
    }
    std::cout << std::endl;
    
    // 泛型Lambda与STL算法
    auto multiply = [](const auto& a, const auto& b) {
        return a * b;
    };
    
    std::cout << "multiply(3, 4) = " << multiply(3, 4) << std::endl;
    std::cout << "multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << std::endl;
}
```

### 6. Lambda表达式与函数对象

#### 函数对象
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    int operator()(int x) const {
        return x * factor;
    }
};

void functionObject() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // 使用函数对象
    Multiplier multiplier(3);
    std::vector<int> result1;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(result1), multiplier);
    
    std::cout << "函数对象结果: ";
    for (int n : result1) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 使用Lambda表达式
    std::vector<int> result2;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(result2),
                   [](int x) { return x * 3; });
    
    std::cout << "Lambda结果: ";
    for (int n : result2) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
```

### 7. Lambda表达式与STL算法

#### 查找算法
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void lambdaWithSearch() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    // find_if
    auto it1 = std::find_if(numbers.begin(), numbers.end(),
                            [](int n) { return n > 5; });
    if (it1 != numbers.end()) {
        std::cout << "第一个大于5的数: " << *it1 << std::endl;
    }
    
    // find_if_not
    auto it2 = std::find_if_not(numbers.begin(), numbers.end(),
                                [](int n) { return n < 3; });
    if (it2 != numbers.end()) {
        std::cout << "第一个不小于3的数: " << *it2 << std::endl;
    }
    
    // 字符串查找
    auto it3 = std::find_if(words.begin(), words.end(),
                            [](const std::string& s) { return s.length() > 5; });
    if (it3 != words.end()) {
        std::cout << "第一个长度大于5的单词: " << *it3 << std::endl;
    }
}
```

#### 排序算法
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Person {
    std::string name;
    int age;
    double salary;
    
    Person(const std::string& n, int a, double s) : name(n), age(a), salary(s) {}
};

void lambdaWithSort() {
    std::vector<Person> people = {
        {"Alice", 25, 50000},
        {"Bob", 30, 60000},
        {"Charlie", 20, 45000},
        {"Diana", 35, 70000}
    };
    
    // 按年龄排序
    std::sort(people.begin(), people.end(),
              [](const Person& a, const Person& b) {
                  return a.age < b.age;
              });
    
    std::cout << "按年龄排序:" << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ")" << std::endl;
    }
    
    // 按工资降序排序
    std::sort(people.begin(), people.end(),
              [](const Person& a, const Person& b) {
                  return a.salary > b.salary;
              });
    
    std::cout << "\n按工资降序排序:" << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " ($" << person.salary << ")" << std::endl;
    }
}
```

#### 修改算法
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void lambdaWithModify() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // transform
    std::vector<int> squares;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares),
                   [](int n) { return n * n; });
    
    std::cout << "平方: ";
    for (int n : squares) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // replace_if
    std::vector<int> numbers2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::replace_if(numbers2.begin(), numbers2.end(),
                    [](int n) { return n % 2 == 0; }, 0);
    
    std::cout << "替换偶数: ";
    for (int n : numbers2) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // remove_if
    std::vector<int> numbers3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto newEnd = std::remove_if(numbers3.begin(), numbers3.end(),
                                 [](int n) { return n > 5; });
    numbers3.erase(newEnd, numbers3.end());
    
    std::cout << "移除大于5的数: ";
    for (int n : numbers3) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
```

## 实践练习

### 练习1：函数式编程工具
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

class FunctionalTools {
public:
    // 映射函数
    template<typename Container, typename Func>
    static auto map(const Container& container, Func func) {
        using ValueType = decltype(func(*container.begin()));
        std::vector<ValueType> result;
        std::transform(container.begin(), container.end(), std::back_inserter(result), func);
        return result;
    }
    
    // 过滤函数
    template<typename Container, typename Predicate>
    static auto filter(const Container& container, Predicate pred) {
        std::vector<typename Container::value_type> result;
        std::copy_if(container.begin(), container.end(), std::back_inserter(result), pred);
        return result;
    }
    
    // 归约函数
    template<typename Container, typename Func>
    static auto reduce(const Container& container, typename Container::value_type initial, Func func) {
        return std::accumulate(container.begin(), container.end(), initial, func);
    }
    
    // 查找函数
    template<typename Container, typename Predicate>
    static auto find(const Container& container, Predicate pred) {
        return std::find_if(container.begin(), container.end(), pred);
    }
    
    // 计数函数
    template<typename Container, typename Predicate>
    static size_t count(const Container& container, Predicate pred) {
        return std::count_if(container.begin(), container.end(), pred);
    }
};

void functionalToolsExample() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 映射：计算平方
    auto squares = FunctionalTools::map(numbers, [](int n) { return n * n; });
    std::cout << "平方: ";
    for (int n : squares) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 过滤：找出偶数
    auto evens = FunctionalTools::filter(numbers, [](int n) { return n % 2 == 0; });
    std::cout << "偶数: ";
    for (int n : evens) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 归约：求和
    int sum = FunctionalTools::reduce(numbers, 0, [](int acc, int n) { return acc + n; });
    std::cout << "和: " << sum << std::endl;
    
    // 查找：找到第一个大于5的数
    auto it = FunctionalTools::find(numbers, [](int n) { return n > 5; });
    if (it != numbers.end()) {
        std::cout << "第一个大于5的数: " << *it << std::endl;
    }
    
    // 计数：统计偶数的个数
    size_t evenCount = FunctionalTools::count(numbers, [](int n) { return n % 2 == 0; });
    std::cout << "偶数的个数: " << evenCount << std::endl;
}
```

### 练习2：事件处理器
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <string>

class EventHandler {
private:
    std::vector<std::function<void()>> handlers;
    
public:
    void addHandler(std::function<void()> handler) {
        handlers.push_back(handler);
    }
    
    void trigger() {
        for (const auto& handler : handlers) {
            handler();
        }
    }
    
    void clear() {
        handlers.clear();
    }
    
    size_t size() const {
        return handlers.size();
    }
};

void eventHandlerExample() {
    EventHandler eventHandler;
    
    // 添加事件处理器
    eventHandler.addHandler([]() {
        std::cout << "处理器1: 事件触发!" << std::endl;
    });
    
    eventHandler.addHandler([]() {
        std::cout << "处理器2: 处理事件..." << std::endl;
    });
    
    // 使用捕获列表
    std::string message = "Hello World!";
    eventHandler.addHandler([&message]() {
        std::cout << "处理器3: " << message << std::endl;
    });
    
    // 触发事件
    std::cout << "触发事件 (处理器数量: " << eventHandler.size() << "):" << std::endl;
    eventHandler.trigger();
}
```

### 练习3：配置管理器
```cpp
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>

class ConfigManager {
private:
    std::map<std::string, std::string> config;
    std::vector<std::function<void(const std::string&, const std::string&)>> changeListeners;
    
public:
    void set(const std::string& key, const std::string& value) {
        config[key] = value;
        notifyChange(key, value);
    }
    
    std::string get(const std::string& key) const {
        auto it = config.find(key);
        return it != config.end() ? it->second : "";
    }
    
    void addChangeListener(std::function<void(const std::string&, const std::string&)> listener) {
        changeListeners.push_back(listener);
    }
    
    void forEach(std::function<void(const std::string&, const std::string&)> func) const {
        for (const auto& pair : config) {
            func(pair.first, pair.second);
        }
    }
    
    std::vector<std::string> getKeys(std::function<bool(const std::string&)> predicate) const {
        std::vector<std::string> result;
        for (const auto& pair : config) {
            if (predicate(pair.first)) {
                result.push_back(pair.first);
            }
        }
        return result;
    }
    
private:
    void notifyChange(const std::string& key, const std::string& value) {
        for (const auto& listener : changeListeners) {
            listener(key, value);
        }
    }
};

void configManagerExample() {
    ConfigManager config;
    
    // 添加变化监听器
    config.addChangeListener([](const std::string& key, const std::string& value) {
        std::cout << "配置变化: " << key << " = " << value << std::endl;
    });
    
    // 设置配置
    config.set("database.host", "localhost");
    config.set("database.port", "3306");
    config.set("app.name", "MyApp");
    config.set("app.version", "1.0.0");
    
    // 遍历所有配置
    std::cout << "\n所有配置:" << std::endl;
    config.forEach([](const std::string& key, const std::string& value) {
        std::cout << "  " << key << " = " << value << std::endl;
    });
    
    // 查找特定模式的键
    auto dbKeys = config.getKeys([](const std::string& key) {
        return key.find("database.") == 0;
    });
    
    std::cout << "\n数据库相关配置:" << std::endl;
    for (const auto& key : dbKeys) {
        std::cout << "  " << key << " = " << config.get(key) << std::endl;
    }
}
```

## 学习要点总结

1. **语法结构**：掌握Lambda表达式的完整语法
2. **捕获列表**：理解值捕获、引用捕获和混合捕获
3. **与STL结合**：熟练使用Lambda表达式与STL算法
4. **泛型Lambda**：掌握C++14的泛型Lambda特性
5. **函数式编程**：理解函数式编程思想

## 今日算法题

完成以下4道LeetCode题目，巩固Lambda表达式的使用：

1. [LeetCode 49. Group Anagrams](https://leetcode.com/problems/group-anagrams/) - 使用Lambda表达式进行字符串处理
2. [LeetCode 347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) - 使用Lambda表达式进行排序和比较
3. [LeetCode 451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) - 使用Lambda表达式进行字符频率排序
4. [LeetCode 692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/) - 使用Lambda表达式进行单词频率排序

每道题目都涉及Lambda表达式的使用，是很好的实践机会！
