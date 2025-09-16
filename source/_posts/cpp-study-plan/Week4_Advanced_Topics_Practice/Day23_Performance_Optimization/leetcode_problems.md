# 第23天：性能优化 - LeetCode算法题

## 今日算法练习 (4道Medium/Hard题目)

### 题目1：缓存优化 - 动态规划优化
**LeetCode 1449. Form Largest Integer With Digits That Add up to Target (Hard)**
- **链接：** https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/
- **难度：** Hard
- **知识点：** 动态规划、内存优化、缓存友好设计
- **描述：** 给定数字1-9的成本数组和目标值，找出能组成的最大整数
- **性能优化点：** 
  - 空间优化：滚动数组减少内存使用
  - 缓存优化：优化状态转移的内存访问模式
  - 分支预测：减少条件判断

**解题思路：**
- 使用动态规划，但要优化内存访问模式
- 考虑使用一维DP数组而不是二维
- 优化字符串构造过程，减少不必要的拷贝

### 题目2：SIMD优化思想 - 批量计算
**LeetCode 1648. Sell Diminishing-Valued Colored Balls (Medium)**
- **链接：** https://leetcode.com/problems/sell-diminishing-valued-colored-balls/
- **难度：** Medium
- **知识点：** 贪心算法、数学优化、批量计算
- **描述：** 有不同颜色的球，每种颜色有一定数量，价值递减，求最大收益
- **性能优化点：**
  - 批量计算：一次处理多个相同价值的球
  - 减少循环次数：使用数学公式代替逐个计算
  - 避免不必要的排序操作

**解题思路：**
- 使用优先队列管理球的价值
- 批量处理相同层级的球，避免逐个计算
- 使用数学公式计算等差数列和

### 题目3：内存访问优化 - 数据结构设计
**LeetCode 1172. Dinner Plate Stacks (Hard)**
- **链接：** https://leetcode.com/problems/dinner-plate-stacks/
- **难度：** Hard
- **知识点：** 数据结构设计、内存布局优化、缓存友好
- **描述：** 设计一个盘子栈系统，支持左侧推入、右侧弹出、指定位置弹出
- **性能优化点：**
  - 数据结构选择：选择缓存友好的数据结构
  - 内存布局：优化数据在内存中的排列
  - 减少间接访问：减少指针跳转

**解题思路：**
- 使用向量数组而不是链表减少缓存miss
- 维护可用栈的索引集合
- 优化数据结构以减少内存碎片

### 题目4：分支预测优化 - 条件逻辑优化 (Hard)
**LeetCode 1728. Cat and Mouse II (Hard)**
- **链接：** https://leetcode.com/problems/cat-and-mouse-ii/
- **难度：** Hard
- **知识点：** 博弈论、动态规划、分支预测优化
- **描述：** 在网格中，猫追老鼠的博弈问题，判断老鼠是否能获胜
- **性能优化点：**
  - 状态压缩：减少状态空间
  - 分支预测：优化条件判断顺序
  - 记忆化优化：使用高效的缓存策略

**解题思路：**
- 使用minimax算法with记忆化
- 优化状态表示，减少计算复杂度
- 优化条件判断的顺序，提高分支预测命中率

## 额外练习题（可选）

### 题目5：循环展开思想
**LeetCode 1659. Maximize Grid Happiness (Hard)**
- **链接：** https://leetcode.com/problems/maximize-grid-happiness/
- **难度：** Hard
- **性能优化点：** 状态压缩、循环展开、位运算优化

### 题目6：内存池思想应用
**LeetCode 1724. Checking Existence of Edge Length Limited Paths II (Hard)**
- **链接：** https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths-ii/
- **难度：** Hard
- **性能优化点：** 数据结构重用、内存预分配、批量操作

## 性能优化实现要求

### 1. 编译优化
```cpp
// 使用编译器优化选项
// g++ -O2 -march=native -DNDEBUG solution.cpp

// 使用constexpr进行编译时计算
constexpr int calculateConstant() {
    // 编译时计算，运行时无开销
    return 42 * 42;
}

// 使用inline优化小函数
inline int fastAdd(int a, int b) {
    return a + b;
}
```

### 2. 内存访问优化
```cpp
// 缓存友好的数据访问
class CacheFriendlyDP {
private:
    // 使用一维数组而不是二维，提高缓存命中率
    std::vector<int> dp;
    int rows, cols;
    
public:
    CacheFriendlyDP(int r, int c) : rows(r), cols(c), dp(r * c) {}
    
    // 按行访问，缓存友好
    int& operator()(int i, int j) {
        return dp[i * cols + j];
    }
};
```

### 3. 分支预测优化
```cpp
// 优化分支预测
class BranchOptimized {
public:
    // 将最可能的条件放在前面
    int processValue(int x) {
        if (x > 0) [[likely]] {  // C++20
            return x * 2;
        } else if (x == 0) {
            return 0;
        } else [[unlikely]] {
            return x * -1;
        }
    }
    
    // 使用查表替代条件判断
    static constexpr std::array<int, 10> lookup = {0,1,1,2,1,2,2,3,1,2};
    
    int popCount(int x) {
        return lookup[x];  // 无分支，更快
    }
};
```

### 4. 减少内存分配
```cpp
// 重用数据结构，减少分配
class OptimizedSolution {
private:
    // 重用的临时变量
    mutable std::vector<int> temp;
    mutable std::unordered_set<int> visited;
    
public:
    int solve(const std::vector<int>& input) {
        // 清空而不是重新分配
        temp.clear();
        visited.clear();
        
        // 预分配空间
        temp.reserve(input.size());
        visited.reserve(input.size());
        
        // 算法逻辑...
        return 0;
    }
};
```

### 5. SIMD思想应用
```cpp
// 批量处理数据
class BatchProcessor {
public:
    // 一次处理多个元素
    void processArray(std::vector<int>& arr) {
        const size_t BATCH_SIZE = 8;
        size_t i = 0;
        
        // 批量处理
        for (; i + BATCH_SIZE <= arr.size(); i += BATCH_SIZE) {
            // 同时处理8个元素
            for (size_t j = 0; j < BATCH_SIZE; ++j) {
                arr[i + j] = processElement(arr[i + j]);
            }
        }
        
        // 处理剩余元素
        for (; i < arr.size(); ++i) {
            arr[i] = processElement(arr[i]);
        }
    }
    
private:
    int processElement(int x) { return x * 2; }
};
```

## 性能测试框架

### 基准测试类
```cpp
#include <chrono>
#include <vector>
#include <iostream>
#include <functional>

class Benchmark {
private:
    std::string name;
    std::chrono::high_resolution_clock::time_point start;
    
public:
    Benchmark(const std::string& n) : name(n) {
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Benchmark() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end - start).count();
        std::cout << name << ": " << duration << " μs" << std::endl;
    }
};

// 使用宏简化基准测试
#define BENCHMARK(name) Benchmark _bench(name)

// 多次运行取平均值
template<typename Func>
double benchmarkAverage(const std::string& name, Func&& func, int iterations = 100) {
    std::vector<double> times;
    times.reserve(iterations);
    
    for (int i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
            end - start).count();
        times.push_back(duration);
    }
    
    double average = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    std::cout << name << " average: " << average << " ns" << std::endl;
    
    return average;
}
```

## 解题要求

### 性能指标
1. **时间复杂度**：达到最优时间复杂度
2. **空间复杂度**：尽可能优化空间使用
3. **实际运行时间**：通过优化技巧提升实际性能
4. **内存访问模式**：考虑缓存友好性

### 代码质量
1. **使用现代C++特性**：constexpr, inline, [[likely]]等
2. **避免不必要的拷贝**：使用引用、移动语义
3. **合理的数据结构选择**：考虑性能特征
4. **编译器优化友好**：编写编译器容易优化的代码

### 测试验证
1. **正确性测试**：确保优化后结果正确
2. **性能对比**：与未优化版本对比
3. **边界条件**：测试极端情况下的性能
4. **内存使用**：监控内存使用情况

## 学习目标检查

完成今天的算法题后，你应该能够：

1. ✅ **掌握编译器优化技巧**：合理使用优化选项和语言特性
2. ✅ **理解缓存友好编程**：优化数据访问模式
3. ✅ **减少不必要的开销**：避免拷贝、减少分配
4. ✅ **优化分支预测**：减少条件判断开销
5. ✅ **应用SIMD思想**：批量处理数据
6. ✅ **性能测试和分析**：使用工具测量和优化性能

## 提交要求

1. 每道题提供两个版本：基础版本和优化版本
2. 详细的性能对比分析和测试结果
3. 解释使用的优化技巧和原理
4. 包含基准测试代码
5. 总结性能优化在算法题中的应用心得

## 性能优化检查清单

- [ ] 编译器优化选项是否正确设置
- [ ] 是否避免了不必要的内存分配
- [ ] 数据访问是否缓存友好
- [ ] 是否减少了分支预测失败
- [ ] 是否使用了适当的数据结构
- [ ] 是否考虑了SIMD优化可能性
- [ ] 是否进行了性能测试和验证
