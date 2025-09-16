# 第25天：C++17新特性 - LeetCode算法题

## 今日算法练习 (4道Medium/Hard题目)

### 题目1：结构化绑定应用
**LeetCode 1396. Design Underground System (Medium)**
- **链接：** https://leetcode.com/problems/design-underground-system/
- **难度：** Medium
- **知识点：** 数据结构设计、结构化绑定、哈希表
- **描述：** 设计地铁系统，记录乘客进出站时间，计算站点间平均旅行时间
- **C++17特性应用：**
  - 使用结构化绑定处理map的键值对
  - 使用std::optional处理可能不存在的数据
  - 使用if constexpr优化模板代码

**实现要求：**
```cpp
class UndergroundSystem {
private:
    // 使用结构化绑定优化数据访问
    std::unordered_map<int, std::pair<std::string, int>> checkIns;
    std::unordered_map<std::string, std::pair<double, int>> routeStats;
    
public:
    void checkIn(int id, const std::string& stationName, int t) {
        // 使用C++17特性优化实现
    }
    
    void checkOut(int id, const std::string& stationName, int t) {
        // 使用结构化绑定和optional
    }
    
    double getAverageTime(const std::string& startStation, const std::string& endStation) {
        // 使用结构化绑定访问map
    }
};
```

### 题目2：std::optional和std::variant应用
**LeetCode 1825. Finding MK Average (Hard)**
- **链接：** https://leetcode.com/problems/finding-mk-average/
- **难度：** Hard
- **知识点：** 数据结构设计、滑动窗口、多集合
- **描述：** 设计数据结构维护最近m个数字，去除最大最小各k个后的平均值
- **C++17特性应用：**
  - 使用std::optional表示可能无效的平均值
  - 使用std::variant处理不同的数据状态
  - 使用if constexpr优化模板特化

**实现框架：**
```cpp
class MKAverage {
private:
    using DataState = std::variant<
        struct Initializing{},
        struct Ready{},
        struct Computing{}
    >;
    
    DataState state = Initializing{};
    
public:
    MKAverage(int m, int k) {
        // 使用C++17特性初始化
    }
    
    void addElement(int num) {
        // 使用std::visit处理不同状态
    }
    
    std::optional<int> calculateMKAverage() {
        // 返回optional，表示可能无效的结果
    }
};
```

### 题目3：文件系统库概念应用
**LeetCode 1166. Design File System (Medium)**
- **链接：** https://leetcode.com/problems/design-file-system/
- **难度：** Medium
- **知识点：** 树形结构、路径处理、哈希表
- **描述：** 设计文件系统，支持创建路径和获取路径值
- **C++17特性应用：**
  - 使用std::filesystem的路径概念（不实际使用文件系统库）
  - 使用结构化绑定处理路径分割
  - 使用std::optional处理路径查找结果

**实现思路：**
```cpp
class FileSystem {
private:
    struct PathInfo {
        std::string name;
        int value;
        std::unordered_map<std::string, std::unique_ptr<PathInfo>> children;
    };
    
    std::unique_ptr<PathInfo> root;
    
    // 使用类似filesystem::path的概念
    std::vector<std::string> parsePath(const std::string& path) {
        // 使用C++17字符串处理特性
    }
    
public:
    bool createPath(const std::string& path, int value) {
        // 使用结构化绑定和optional
    }
    
    std::optional<int> get(const std::string& path) {
        // 返回optional表示查找结果
    }
};
```

### 题目4：折叠表达式和模板推导 (Hard)
**LeetCode 1622. Fancy Sequence (Hard)**
- **链接：** https://leetcode.com/problems/fancy-sequence/
- **难度：** Hard
- **知识点：** 数学、模运算、延迟计算、模板编程
- **描述：** 设计支持append、addAll、multAll、getIndex操作的序列
- **C++17特性应用：**
  - 使用折叠表达式简化可变参数模板
  - 使用CTAD简化模板类使用
  - 使用if constexpr优化编译时计算

**高级实现：**
```cpp
template<typename T = long long, T MOD = 1000000007>
class FancySequence {
private:
    std::vector<T> data;
    T global_add = 0;
    T global_mult = 1;
    
    // 使用折叠表达式的工具函数
    template<typename... Args>
    constexpr T modSum(Args... args) {
        return ((args % MOD) + ...) % MOD;
    }
    
    template<typename... Args>
    constexpr T modMult(Args... args) {
        return ((args % MOD) * ...) % MOD;
    }
    
public:
    void append(T val) {
        // 使用C++17特性优化
    }
    
    void addAll(T inc) {
        // 使用if constexpr优化
    }
    
    void multAll(T m) {
        // 使用模板推导
    }
    
    std::optional<T> getIndex(int idx) {
        // 使用optional处理越界情况
    }
};

// 使用CTAD
FancySequence seq;  // 自动推导为FancySequence<long long, 1000000007>
```

## C++17特性应用要求

### 1. 结构化绑定优化
```cpp
// 传统写法
for (auto it = map.begin(); it != map.end(); ++it) {
    std::string key = it->first;
    int value = it->second;
    // 处理key和value
}

// C++17结构化绑定
for (const auto& [key, value] : map) {
    // 直接使用key和value，代码更清晰
}

// 函数返回多值
std::tuple<bool, int, std::string> processData() {
    return {true, 42, "success"};
}

// 使用结构化绑定接收
auto [success, result, message] = processData();
```

### 2. std::optional错误处理
```cpp
class SafeLeetCodeSolution {
public:
    // 替代抛异常或返回特殊值
    std::optional<int> findElement(const std::vector<int>& arr, int target) {
        auto it = std::find(arr.begin(), arr.end(), target);
        if (it != arr.end()) {
            return std::distance(arr.begin(), it);
        }
        return std::nullopt;  // 明确表示未找到
    }
    
    // 链式操作
    std::optional<int> safeCalculation(int a, int b) {
        if (b == 0) return std::nullopt;
        
        auto result = divide(a, b);
        if (result < 0) return std::nullopt;
        
        return result;
    }
    
    // 与算法结合
    template<typename Container, typename Predicate>
    std::optional<typename Container::value_type> 
    findFirst(const Container& container, Predicate pred) {
        auto it = std::find_if(container.begin(), container.end(), pred);
        if (it != container.end()) {
            return *it;
        }
        return std::nullopt;
    }
};
```

### 3. std::variant类型安全
```cpp
// 替代union或void*的类型安全方案
using LeetCodeValue = std::variant<int, double, std::string, std::vector<int>>;

class VariantProcessor {
public:
    static void processValue(const LeetCodeValue& value) {
        std::visit([](const auto& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, int>) {
                std::cout << "Processing integer: " << v << std::endl;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "Processing string: " << v << std::endl;
            } else if constexpr (std::is_same_v<T, std::vector<int>>) {
                std::cout << "Processing vector of size: " << v.size() << std::endl;
            }
        }, value);
    }
    
    // 类型安全的计算
    static LeetCodeValue calculate(const LeetCodeValue& a, const LeetCodeValue& b) {
        return std::visit([](const auto& x, const auto& y) -> LeetCodeValue {
            using T = std::decay_t<decltype(x)>;
            using U = std::decay_t<decltype(y)>;
            
            if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
                return x + y;
            } else {
                throw std::runtime_error("Unsupported operation");
            }
        }, a, b);
    }
};
```

### 4. if constexpr模板优化
```cpp
template<typename Container>
class ContainerProcessor {
public:
    static void process(const Container& container) {
        if constexpr (std::is_same_v<Container, std::vector<typename Container::value_type>>) {
            // 针对vector的优化处理
            processVector(container);
        } else if constexpr (std::is_same_v<Container, std::list<typename Container::value_type>>) {
            // 针对list的特殊处理
            processList(container);
        } else {
            // 通用处理
            processGeneric(container);
        }
    }
    
    // 编译时类型检查
    template<typename T>
    static constexpr auto getValue(T&& value) {
        if constexpr (std::is_integral_v<std::decay_t<T>>) {
            return value * 2;
        } else if constexpr (std::is_floating_point_v<std::decay_t<T>>) {
            return value / 2.0;
        } else {
            static_assert(std::is_arithmetic_v<std::decay_t<T>>, "Type must be arithmetic");
            return value;
        }
    }
};
```

## 性能和代码质量要求

### 编译时优化
1. **使用constexpr**：尽可能在编译时计算
2. **if constexpr**：避免运行时分支
3. **CTAD**：简化模板使用，提高可读性
4. **折叠表达式**：简化可变参数模板

### 类型安全
1. **std::optional**：替代异常或特殊值
2. **std::variant**：类型安全的union
3. **结构化绑定**：避免临时变量和类型错误

### 代码现代化
1. **使用auto推导**：结合CTAD使用
2. **范围for循环**：结合结构化绑定
3. **lambda表达式**：结合std::visit使用

## 学习目标检查

完成今天的算法题后，你应该能够：

1. ✅ **熟练使用结构化绑定**：简化多值处理
2. ✅ **掌握std::optional**：安全的错误处理
3. ✅ **应用std::variant**：类型安全的多态
4. ✅ **使用if constexpr**：编译时条件判断
5. ✅ **理解CTAD**：简化模板类使用
6. ✅ **应用折叠表达式**：简化可变参数模板

## 提交要求

1. 每道题提供C++17特性丰富的解决方案
2. 对比传统C++写法，展示C++17的优势
3. 包含编译时优化和类型安全的考虑
4. 提供完整的测试用例和性能分析
5. 总结C++17特性在算法题中的应用心得

## C++17特性检查清单

- [ ] 是否使用了结构化绑定简化代码
- [ ] 是否用std::optional替代了异常处理
- [ ] 是否考虑了std::variant的类型安全优势
- [ ] 是否使用了if constexpr进行编译时优化
- [ ] 是否利用了CTAD简化模板使用
- [ ] 是否在适当场合使用了折叠表达式
- [ ] 是否保持了代码的可读性和维护性
