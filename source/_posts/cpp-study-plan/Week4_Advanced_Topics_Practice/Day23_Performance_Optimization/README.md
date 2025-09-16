# 第23天：性能优化

## 学习目标
掌握C++性能优化的核心技巧和方法，学会分析性能瓶颈，运用各种优化策略提升程序执行效率。

## 今日学习内容

### 1. 编译器优化
**概念：** 利用编译器的优化能力提升程序性能。

**优化选项：**
- `-O0`: 无优化（调试用）
- `-O1`: 基本优化
- `-O2`: 标准优化（推荐）
- `-O3`: 激进优化
- `-Ofast`: 最快速度优化
- `-Os`: 优化代码大小

**编译器优化示例：**
```cpp
// 编译命令比较
// g++ -O0 -o program_debug program.cpp     // 调试版本
// g++ -O2 -o program_release program.cpp   // 发布版本
// g++ -O3 -march=native -o program_fast program.cpp  // 针对本机优化

// 性能测试代码
#include <chrono>
#include <vector>
#include <numeric>

class PerformanceTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string operation_name;
    
public:
    PerformanceTimer(const std::string& name) : operation_name(name) {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    ~PerformanceTimer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time).count();
        std::cout << operation_name << " took: " << duration << " microseconds" << std::endl;
    }
};

// 测试不同优化级别的性能差异
void testOptimizationLevels() {
    const size_t SIZE = 1000000;
    std::vector<int> data(SIZE);
    std::iota(data.begin(), data.end(), 1);
    
    {
        PerformanceTimer timer("Vector sum calculation");
        long long sum = std::accumulate(data.begin(), data.end(), 0LL);
        std::cout << "Sum: " << sum << std::endl;
    }
}
```

### 2. 内联函数优化
**概念：** 通过内联减少函数调用开销。

**使用原则：**
- 小函数适合内联
- 频繁调用的函数
- 避免内联递归函数
- 避免内联复杂函数

**内联优化示例：**
```cpp
// 传统函数调用（有开销）
double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// 内联函数（减少调用开销）
inline double calculateDistanceInline(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// 更好的做法：使用constexpr
constexpr double calculateDistanceConstexpr(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// 模板内联
template<typename T>
constexpr T square(T x) {
    return x * x;
}

template<typename T>
constexpr T distance(T x1, T y1, T x2, T y2) {
    return std::sqrt(square(x2-x1) + square(y2-y1));
}
```

### 3. 缓存友好的编程
**概念：** 优化内存访问模式，提高缓存命中率。

**关键原则：**
- 时间局部性：重复访问相同数据
- 空间局部性：访问相邻的数据
- 避免缓存抖动
- 数据结构对齐

**缓存优化示例：**
```cpp
#include <vector>
#include <array>
#include <memory>

// 缓存不友好的数据结构
struct BadDataLayout {
    char a;      // 1 byte
    double b;    // 8 bytes (可能有7字节填充)
    char c;      // 1 byte
    int d;       // 4 bytes (可能有3字节填充)
};

// 缓存友好的数据结构
struct GoodDataLayout {
    double b;    // 8 bytes
    int d;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    // 总共16字节，无浪费
};

// 结构体数组 vs 数组结构体
class DataOrganization {
public:
    // AoS (Array of Structures) - 缓存不友好
    struct Point3D {
        float x, y, z;
    };
    std::vector<Point3D> points_aos;
    
    // SoA (Structure of Arrays) - 缓存友好
    struct Points3D {
        std::vector<float> x;
        std::vector<float> y;
        std::vector<float> z;
    };
    Points3D points_soa;
    
    // 测试缓存性能
    void testCachePerformance(size_t n) {
        // 初始化数据
        points_aos.resize(n);
        points_soa.x.resize(n);
        points_soa.y.resize(n);
        points_soa.z.resize(n);
        
        for (size_t i = 0; i < n; ++i) {
            points_aos[i] = {float(i), float(i+1), float(i+2)};
            points_soa.x[i] = float(i);
            points_soa.y[i] = float(i+1);
            points_soa.z[i] = float(i+2);
        }
        
        // 测试AoS性能（只访问x坐标）
        {
            PerformanceTimer timer("AoS X-coordinate sum");
            float sum = 0.0f;
            for (const auto& point : points_aos) {
                sum += point.x;  // 每次访问都会加载整个Point3D
            }
            std::cout << "AoS sum: " << sum << std::endl;
        }
        
        // 测试SoA性能（只访问x坐标）
        {
            PerformanceTimer timer("SoA X-coordinate sum");
            float sum = 0.0f;
            for (float x : points_soa.x) {
                sum += x;  // 连续内存访问，缓存友好
            }
            std::cout << "SoA sum: " << sum << std::endl;
        }
    }
};
```

### 4. 避免不必要的拷贝
**概念：** 通过引用、移动语义等减少对象拷贝开销。

**优化技巧：**
- 使用const引用传递参数
- 使用移动语义
- 返回值优化(RVO/NRVO)
- emplace vs insert

**拷贝优化示例：**
```cpp
#include <string>
#include <vector>
#include <utility>

class CopyOptimization {
private:
    std::vector<std::string> data;
    
public:
    // 不好的做法：按值传递
    void addItemBad(std::string item) {
        data.push_back(item);  // 可能产生两次拷贝
    }
    
    // 好的做法：const引用传递
    void addItemGood(const std::string& item) {
        data.push_back(item);  // 一次拷贝
    }
    
    // 更好的做法：完美转发
    template<typename T>
    void addItem(T&& item) {
        data.emplace_back(std::forward<T>(item));
    }
    
    // 移动语义优化
    void addItemMove(std::string item) {
        data.push_back(std::move(item));  // 移动，不拷贝
    }
    
    // 返回值优化
    std::vector<std::string> getDataCopy() const {
        return data;  // RVO优化，不会产生额外拷贝
    }
    
    // 引用返回避免拷贝
    const std::vector<std::string>& getData() const {
        return data;
    }
    
    // emplace vs push_back
    void testEmplaceVsPushBack() {
        std::vector<std::string> vec;
        
        // push_back: 构造临时对象，然后拷贝/移动
        vec.push_back(std::string("Hello"));
        
        // emplace_back: 直接在容器中构造对象
        vec.emplace_back("World");  // 更高效
        
        // 对于复杂对象，差异更明显
        std::vector<std::pair<int, std::string>> pairs;
        
        // push_back: 构造临时pair，然后移动
        pairs.push_back(std::make_pair(1, "one"));
        
        // emplace_back: 直接构造pair
        pairs.emplace_back(2, "two");  // 更高效
    }
};
```

### 5. 内存池技术
**概念：** 预分配内存块，减少动态内存分配的开销。

**应用场景：**
- 频繁的小对象分配
- 实时系统
- 游戏引擎
- 高性能服务器

**内存池实现：**
```cpp
#include <memory>
#include <vector>
#include <stack>

template<typename T, size_t BlockSize = 4096>
class MemoryPool {
private:
    struct Block {
        alignas(T) char data[BlockSize];
    };
    
    std::vector<std::unique_ptr<Block>> blocks;
    std::stack<T*> freeList;
    size_t objectsPerBlock;
    
    void allocateNewBlock() {
        auto block = std::make_unique<Block>();
        char* ptr = block->data;
        
        // 将块中的内存分割成对象大小的片段
        for (size_t i = 0; i < objectsPerBlock; ++i) {
            freeList.push(reinterpret_cast<T*>(ptr + i * sizeof(T)));
        }
        
        blocks.push_back(std::move(block));
    }
    
public:
    MemoryPool() : objectsPerBlock(BlockSize / sizeof(T)) {
        static_assert(sizeof(T) <= BlockSize, "Object size too large for block");
        allocateNewBlock();
    }
    
    ~MemoryPool() {
        // 析构函数会自动清理所有块
    }
    
    T* allocate() {
        if (freeList.empty()) {
            allocateNewBlock();
        }
        
        T* ptr = freeList.top();
        freeList.pop();
        return ptr;
    }
    
    void deallocate(T* ptr) {
        if (ptr) {
            freeList.push(ptr);
        }
    }
    
    // 获取统计信息
    size_t getBlockCount() const { return blocks.size(); }
    size_t getFreeObjectCount() const { return freeList.size(); }
    size_t getTotalObjectCount() const { return blocks.size() * objectsPerBlock; }
    size_t getUsedObjectCount() const { return getTotalObjectCount() - getFreeObjectCount(); }
};

// 使用内存池的对象
class PooledObject {
private:
    static MemoryPool<PooledObject> pool;
    int value;
    
public:
    PooledObject(int v = 0) : value(v) {}
    
    // 重载new和delete操作符
    void* operator new(size_t size) {
        return pool.allocate();
    }
    
    void operator delete(void* ptr) {
        pool.deallocate(static_cast<PooledObject*>(ptr));
    }
    
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
};

// 静态成员定义
MemoryPool<PooledObject> PooledObject::pool;
```

### 6. 分支预测优化
**概念：** 帮助CPU更好地预测分支，减少管道停顿。

**优化技巧：**
- 使用likely/unlikely属性
- 避免不可预测的分支
- 循环展开
- 查表替代条件判断

**分支优化示例：**
```cpp
#include <random>
#include <algorithm>

class BranchOptimization {
public:
    // 使用C++20的likely/unlikely属性
    int processValue(int x) {
        if (x > 0) [[likely]] {  // 告诉编译器这个分支更可能执行
            return x * 2;
        } else [[unlikely]] {
            return x * -1;
        }
    }
    
    // 避免不可预测的分支
    int findMaxTraditional(const std::vector<int>& data) {
        int max_val = data[0];
        for (size_t i = 1; i < data.size(); ++i) {
            if (data[i] > max_val) {  // 分支不可预测
                max_val = data[i];
            }
        }
        return max_val;
    }
    
    // 使用STL算法避免显式分支
    int findMaxOptimized(const std::vector<int>& data) {
        return *std::max_element(data.begin(), data.end());
    }
    
    // 查表替代条件判断
    static constexpr int LOOKUP_TABLE[256] = {
        // 预计算的值，避免运行时计算
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        // ... 更多值
    };
    
    int popCountLookup(uint8_t x) {
        return LOOKUP_TABLE[x];  // O(1)查表，无分支
    }
    
    int popCountBranches(uint8_t x) {
        int count = 0;
        while (x) {  // 包含不可预测的分支
            if (x & 1) count++;
            x >>= 1;
        }
        return count;
    }
};
```

### 7. SIMD优化
**概念：** 使用Single Instruction, Multiple Data指令集提升并行计算性能。

**SIMD示例：**
```cpp
#include <immintrin.h>  // Intel intrinsics
#include <vector>
#include <numeric>

class SIMDOptimization {
public:
    // 传统标量加法
    void addArraysScalar(const float* a, const float* b, float* result, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            result[i] = a[i] + b[i];
        }
    }
    
    // SIMD向量加法（AVX）
    void addArraysSIMD(const float* a, const float* b, float* result, size_t size) {
        size_t simd_size = size - (size % 8);  // 8个float为一组
        
        // SIMD处理
        for (size_t i = 0; i < simd_size; i += 8) {
            __m256 va = _mm256_load_ps(&a[i]);
            __m256 vb = _mm256_load_ps(&b[i]);
            __m256 vresult = _mm256_add_ps(va, vb);
            _mm256_store_ps(&result[i], vresult);
        }
        
        // 处理剩余元素
        for (size_t i = simd_size; i < size; ++i) {
            result[i] = a[i] + b[i];
        }
    }
    
    // 向量点积SIMD优化
    float dotProductSIMD(const float* a, const float* b, size_t size) {
        __m256 sum = _mm256_setzero_ps();
        size_t simd_size = size - (size % 8);
        
        for (size_t i = 0; i < simd_size; i += 8) {
            __m256 va = _mm256_load_ps(&a[i]);
            __m256 vb = _mm256_load_ps(&b[i]);
            sum = _mm256_fmadd_ps(va, vb, sum);  // fused multiply-add
        }
        
        // 水平加法
        __m128 sum_high = _mm256_extractf128_ps(sum, 1);
        __m128 sum_low = _mm256_castps256_ps128(sum);
        __m128 sum_final = _mm_add_ps(sum_high, sum_low);
        
        sum_final = _mm_hadd_ps(sum_final, sum_final);
        sum_final = _mm_hadd_ps(sum_final, sum_final);
        
        float result = _mm_cvtss_f32(sum_final);
        
        // 处理剩余元素
        for (size_t i = simd_size; i < size; ++i) {
            result += a[i] * b[i];
        }
        
        return result;
    }
};
```

## 实践练习

### 练习1：性能分析工具使用
```cpp
// 使用chrono进行性能测量
// 使用valgrind进行内存分析
// 使用gprof进行性能分析
```

### 练习2：缓存优化实战
```cpp
// 实现矩阵乘法的缓存优化版本
// 比较不同数据布局的性能差异
```

### 练习3：内存池实现
```cpp
// 实现一个通用的内存池
// 测试内存池与标准allocator的性能差异
```

## 重点总结

1. **编译器优化**：合理使用优化选项，理解编译器能力
2. **内存访问优化**：提高缓存命中率，优化数据布局
3. **减少拷贝**：使用移动语义、引用、emplace等技术
4. **内存管理**：使用内存池减少分配开销
5. **分支优化**：减少不可预测分支，使用查表等技术
6. **并行化**：使用SIMD指令提升计算密集型任务性能

## 性能测试方法

1. **基准测试**：使用统一的测试环境和数据
2. **多次测量**：避免偶然因素影响
3. **统计分析**：计算平均值、标准差等
4. **热身运行**：排除冷启动影响
5. **内存对齐**：确保数据正确对齐

## 注意事项

1. **过早优化是万恶之源**：先保证正确性，再考虑性能
2. **测量驱动优化**：使用性能分析工具定位瓶颈
3. **平台相关性**：不同硬件平台优化效果可能不同
4. **可维护性**：不要为了性能牺牲代码可读性
5. **编译器已经很智能**：很多优化编译器会自动完成

## 拓展阅读

- 《Optimized C++》
- 《Computer Systems: A Programmer's Perspective》
- Intel优化手册
- Agner Fog的优化指南
- Chandler Carruth的CppCon演讲
