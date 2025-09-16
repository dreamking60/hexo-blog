# 第26天：C++20新特性 - LeetCode算法题

## 今日算法练习 (4道Medium/Hard题目)

### 题目1：概念(Concepts)应用
**LeetCode 1670. Design Front Middle Back Queue (Medium)**
- **链接：** https://leetcode.com/problems/design-front-middle-back-queue/
- **难度：** Medium
- **知识点：** 数据结构设计、双端队列、概念约束
- **描述：** 设计支持前端、中间、后端插入和删除的队列
- **C++20特性应用：**
  - 使用概念约束模板参数
  - 使用三路比较运算符
  - 使用指定初始化器

**概念约束实现：**
```cpp
#include <concepts>
#include <deque>
#include <optional>

template<typename T>
concept QueueElement = std::copyable<T> && std::equality_comparable<T>;

template<QueueElement T>
class FrontMiddleBackQueue {
private:
    std::deque<T> left, right;
    
    void balance() {
        // 保持左右两边平衡
        if (left.size() > right.size() + 1) {
            right.push_front(left.back());
            left.pop_back();
        } else if (right.size() > left.size() + 1) {
            left.push_back(right.front());
            right.pop_front();
        }
    }
    
public:
    void pushFront(const T& val) requires std::copyable<T> {
        left.push_front(val);
        balance();
    }
    
    void pushMiddle(const T& val) {
        if (left.size() <= right.size()) {
            left.push_back(val);
        } else {
            right.push_front(val);
        }
        balance();
    }
    
    void pushBack(const T& val) {
        right.push_back(val);
        balance();
    }
    
    std::optional<T> popFront() {
        if (left.empty() && right.empty()) return std::nullopt;
        
        T result;
        if (!left.empty()) {
            result = left.front();
            left.pop_front();
        } else {
            result = right.front();
            right.pop_front();
        }
        balance();
        return result;
    }
    
    std::optional<T> popMiddle() {
        if (left.empty() && right.empty()) return std::nullopt;
        
        T result;
        if (left.size() >= right.size()) {
            result = left.back();
            left.pop_back();
        } else {
            result = right.front();
            right.pop_front();
        }
        balance();
        return result;
    }
    
    std::optional<T> popBack() {
        if (left.empty() && right.empty()) return std::nullopt;
        
        T result;
        if (!right.empty()) {
            result = right.back();
            right.pop_back();
        } else {
            result = left.back();
            left.pop_back();
        }
        balance();
        return result;
    }
};
```

### 题目2：范围(Ranges)和视图应用
**LeetCode 1878. Get Biggest Three Rhombus Sums in a Grid (Medium)**
- **链接：** https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/
- **难度：** Medium
- **知识点：** 二维数组、滑动窗口、范围算法
- **描述：** 在网格中找到最大的三个菱形和
- **C++20特性应用：**
  - 使用ranges::views进行数据处理
  - 使用ranges算法替代传统STL
  - 使用概念约束网格类型

**范围算法实现：**
```cpp
#include <ranges>
#include <vector>
#include <algorithm>
#include <set>

namespace ranges = std::ranges;
namespace views = std::views;

template<typename T>
concept GridType = requires(T t) {
    t[0][0];  // 支持二维索引
    t.size(); // 有size方法
    typename T::value_type::value_type; // 嵌套的value_type
};

class Solution {
public:
    template<GridType Grid>
    std::vector<int> getBiggestThree(const Grid& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        std::set<int> sums;
        
        // 使用ranges生成所有可能的菱形中心点
        auto centers = views::cartesian_product(
            views::iota(0, m),
            views::iota(0, n)
        );
        
        for (const auto& [i, j] : centers) {
            // 对每个中心点，尝试不同大小的菱形
            int maxSize = std::min({i, j, m-1-i, n-1-j});
            
            auto sizes = views::iota(0, maxSize + 1);
            
            for (int size : sizes) {
                int sum = calculateRhombusSum(grid, i, j, size);
                sums.insert(sum);
                
                // 只保留最大的三个
                if (sums.size() > 3) {
                    sums.erase(sums.begin());
                }
            }
        }
        
        // 使用ranges转换为vector并反转
        std::vector<int> result;
        ranges::copy(sums | views::reverse, std::back_inserter(result));
        
        return result;
    }
    
private:
    template<GridType Grid>
    int calculateRhombusSum(const Grid& grid, int centerI, int centerJ, int size) {
        if (size == 0) {
            return grid[centerI][centerJ];
        }
        
        int sum = 0;
        
        // 使用ranges生成菱形边界上的点
        auto topToRight = views::iota(0, size) 
            | views::transform([=](int k) {
                return std::pair{centerI - size + k, centerJ + k};
            });
            
        auto rightToBottom = views::iota(0, size)
            | views::transform([=](int k) {
                return std::pair{centerI + k, centerJ + size - k};
            });
            
        auto bottomToLeft = views::iota(0, size)
            | views::transform([=](int k) {
                return std::pair{centerI + size - k, centerJ - k};
            });
            
        auto leftToTop = views::iota(0, size)
            | views::transform([=](int k) {
                return std::pair{centerI - k, centerJ - size + k};
            });
        
        // 合并所有边界点
        auto allPoints = views::concat(topToRight, rightToBottom, bottomToLeft, leftToTop);
        
        for (const auto& [i, j] : allPoints) {
            sum += grid[i][j];
        }
        
        return sum;
    }
};
```

### 题目3：协程(Coroutines)应用
**LeetCode 1586. Binary Search Tree Iterator II (Medium)**
- **链接：** https://leetcode.com/problems/binary-search-tree-iterator-ii/
- **难度：** Medium
- **知识点：** 二叉搜索树、迭代器、协程生成器
- **描述：** 设计支持前向和后向遍历的BST迭代器
- **C++20特性应用：**
  - 使用协程实现生成器模式
  - 使用概念约束树节点类型
  - 使用三路比较运算符

**协程迭代器实现：**
```cpp
#include <coroutine>
#include <vector>
#include <concepts>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    
    // C++20三路比较
    auto operator<=>(const TreeNode& other) const {
        return val <=> other.val;
    }
    
    bool operator==(const TreeNode& other) const {
        return val == other.val;
    }
};

template<typename T>
concept TreeNodeType = requires(T* t) {
    t->val;
    t->left;
    t->right;
    { t->val } -> std::convertible_to<int>;
};

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
    
private:
    std::coroutine_handle<promise_type> coro;
    
public:
    Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
    ~Generator() { if (coro) coro.destroy(); }
    
    // 移动语义
    Generator(Generator&& other) noexcept : coro(other.coro) {
        other.coro = {};
    }
    
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = {};
        }
        return *this;
    }
    
    // 禁止拷贝
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    
    bool next() {
        if (coro) {
            coro.resume();
            return !coro.done();
        }
        return false;
    }
    
    T current() const {
        return coro.promise().current_value;
    }
};

class BSTIterator {
private:
    Generator<int> forward_gen;
    Generator<int> backward_gen;
    std::vector<int> values;
    int current_index;
    
    Generator<int> inorderTraversal(TreeNode* root) {
        if (!root) co_return;
        
        // 递归生成中序遍历
        auto left_gen = inorderTraversal(root->left);
        while (left_gen.next()) {
            co_yield left_gen.current();
        }
        
        co_yield root->val;
        
        auto right_gen = inorderTraversal(root->right);
        while (right_gen.next()) {
            co_yield right_gen.current();
        }
    }
    
public:
    BSTIterator(TreeNode* root) : current_index(-1) {
        // 使用协程生成所有值
        auto gen = inorderTraversal(root);
        while (gen.next()) {
            values.push_back(gen.current());
        }
    }
    
    bool hasNext() {
        return current_index + 1 < values.size();
    }
    
    int next() {
        if (hasNext()) {
            return values[++current_index];
        }
        return -1;  // 或抛出异常
    }
    
    bool hasPrev() {
        return current_index > 0;
    }
    
    int prev() {
        if (hasPrev()) {
            return values[--current_index];
        }
        return -1;  // 或抛出异常
    }
};
```

### 题目4：综合特性应用 (Hard)
**LeetCode 1912. Design Movie Rental System (Hard)**
- **链接：** https://leetcode.com/problems/design-movie-rental-system/
- **难度：** Hard
- **知识点：** 复杂数据结构、多索引、排序
- **描述：** 设计电影租赁系统，支持搜索、租赁、归还操作
- **C++20特性应用：**
  - 使用概念约束所有模板
  - 使用ranges进行数据处理
  - 使用三路比较运算符
  - 使用指定初始化器

**综合实现：**
```cpp
#include <concepts>
#include <ranges>
#include <set>
#include <unordered_map>
#include <vector>

namespace ranges = std::ranges;

template<typename T>
concept MovieId = std::integral<T> && requires(T t) {
    { t >= 0 } -> std::convertible_to<bool>;
};

template<typename T>
concept ShopId = std::integral<T> && requires(T t) {
    { t >= 0 } -> std::convertible_to<bool>;
};

template<typename T>
concept Price = std::integral<T> && requires(T t) {
    { t >= 0 } -> std::convertible_to<bool>;
};

struct MovieEntry {
    int price;
    int shop;
    int movie;
    
    // C++20三路比较
    auto operator<=>(const MovieEntry& other) const {
        if (auto cmp = price <=> other.price; cmp != 0) return cmp;
        if (auto cmp = shop <=> other.shop; cmp != 0) return cmp;
        return movie <=> other.movie;
    }
    
    bool operator==(const MovieEntry& other) const = default;
};

class MovieRentalSystem {
private:
    std::unordered_map<int, std::set<MovieEntry>> unrented; // movie -> entries
    std::set<MovieEntry> rented;
    std::unordered_map<int, std::unordered_map<int, int>> shop_movie_price;
    
public:
    template<ranges::range R>
    MovieRentalSystem(R&& entries) requires requires(R r) {
        ranges::begin(r);
        ranges::end(r);
    } {
        for (const auto& entry : entries) {
            int shop = entry[0];
            int movie = entry[1]; 
            int price = entry[2];
            
            // 使用指定初始化器
            MovieEntry me{.price = price, .shop = shop, .movie = movie};
            
            unrented[movie].insert(me);
            shop_movie_price[shop][movie] = price;
        }
    }
    
    template<MovieId M>
    std::vector<int> search(M movie) {
        std::vector<int> result;
        
        if (unrented.contains(movie)) {
            auto& entries = unrented[movie];
            
            // 使用ranges取前5个
            auto top5 = entries | std::views::take(5);
            
            ranges::transform(top5, std::back_inserter(result),
                [](const MovieEntry& entry) { return entry.shop; });
        }
        
        return result;
    }
    
    template<ShopId S, MovieId M>
    void rent(S shop, M movie) {
        int price = shop_movie_price[shop][movie];
        MovieEntry entry{.price = price, .shop = shop, .movie = movie};
        
        unrented[movie].erase(entry);
        rented.insert(entry);
    }
    
    template<ShopId S, MovieId M> 
    void drop(S shop, M movie) {
        int price = shop_movie_price[shop][movie];
        MovieEntry entry{.price = price, .shop = shop, .movie = movie};
        
        rented.erase(entry);
        unrented[movie].insert(entry);
    }
    
    std::vector<std::vector<int>> report() {
        std::vector<std::vector<int>> result;
        
        // 使用ranges取前5个已租赁的电影
        auto top5_rented = rented | std::views::take(5);
        
        ranges::transform(top5_rented, std::back_inserter(result),
            [](const MovieEntry& entry) {
                return std::vector<int>{entry.shop, entry.movie};
            });
        
        return result;
    }
};
```

## C++20特性应用要求

### 1. 概念约束
```cpp
// 定义清晰的概念
template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

// 使用概念约束函数
template<Comparable T>
void sortData(std::vector<T>& data) {
    std::ranges::sort(data);
}
```

### 2. 范围算法优化
```cpp
// 传统STL写法
std::vector<int> processData(const std::vector<int>& input) {
    std::vector<int> filtered;
    std::copy_if(input.begin(), input.end(), std::back_inserter(filtered),
        [](int x) { return x > 0; });
    
    std::vector<int> result;
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(result),
        [](int x) { return x * x; });
    
    return result;
}

// C++20 ranges写法
std::vector<int> processDataRanges(const std::vector<int>& input) {
    auto result = input 
        | std::views::filter([](int x) { return x > 0; })
        | std::views::transform([](int x) { return x * x; });
    
    return std::vector<int>(result.begin(), result.end());
}
```

### 3. 协程生成器
```cpp
// 使用协程简化复杂的迭代逻辑
template<typename T>
Generator<T> treeTraversal(TreeNode<T>* root) {
    if (!root) co_return;
    
    co_yield root->val;
    
    auto left = treeTraversal(root->left);
    while (left.next()) {
        co_yield left.current();
    }
    
    auto right = treeTraversal(root->right);
    while (right.next()) {
        co_yield right.current();
    }
}
```

## 学习目标检查

完成今天的算法题后，你应该能够：

1. ✅ **熟练使用概念**：为模板提供清晰的约束
2. ✅ **掌握ranges库**：简化数据处理逻辑
3. ✅ **应用协程**：实现生成器和异步模式
4. ✅ **使用三路比较**：简化比较操作
5. ✅ **理解指定初始化**：提高代码可读性
6. ✅ **综合运用新特性**：在复杂问题中应用多种特性

## 提交要求

1. 每道题充分利用C++20新特性
2. 对比传统C++实现，展示新特性优势
3. 包含概念定义和约束说明
4. 提供性能测试和分析
5. 总结C++20特性在算法题中的应用心得

## C++20特性检查清单

- [ ] 是否定义了清晰的概念约束
- [ ] 是否使用了ranges简化数据处理
- [ ] 是否考虑了协程的应用场景
- [ ] 是否使用了三路比较运算符
- [ ] 是否利用了指定初始化器
- [ ] 是否保持了代码的现代化风格
- [ ] 是否考虑了编译器兼容性问题
