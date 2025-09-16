/**
 * 第23天：性能优化 - 实践练习
 * 
 * 本文件包含各种C++性能优化技巧的实际应用
 * 编译命令: g++ -std=c++17 -O2 -march=native -pthread -o practice_exercises practice_exercises.cpp
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include <memory>
#include <thread>
#include <immintrin.h>  // For SIMD intrinsics
#include <array>
#include <unordered_map>
#include <stack>

// =============================================================================
// 性能测试工具类
// =============================================================================

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
        std::cout << operation_name << " took: " << duration << " μs" << std::endl;
    }
};

#define BENCHMARK(name) PerformanceTimer _timer(name)

// 多次运行基准测试
template<typename Func>
double benchmarkFunction(const std::string& name, Func&& func, int iterations = 100) {
    std::vector<double> times;
    times.reserve(iterations);
    
    // 热身运行
    for (int i = 0; i < 5; ++i) {
        func();
    }
    
    // 正式测试
    for (int i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
            end - start).count();
        times.push_back(duration);
    }
    
    double average = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    double min_time = *std::min_element(times.begin(), times.end());
    double max_time = *std::max_element(times.begin(), times.end());
    
    std::cout << name << " - Avg: " << average << " ns, Min: " << min_time 
              << " ns, Max: " << max_time << " ns" << std::endl;
    
    return average;
}

// =============================================================================
// 1. 缓存优化示例
// =============================================================================

class CacheOptimization {
public:
    // 矩阵乘法 - 缓存不友好版本
    static void matrixMultiplyNaive(const std::vector<std::vector<double>>& A,
                                   const std::vector<std::vector<double>>& B,
                                   std::vector<std::vector<double>>& C) {
        size_t n = A.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    C[i][j] += A[i][k] * B[k][j];  // B[k][j]访问不连续
                }
            }
        }
    }
    
    // 矩阵乘法 - 缓存友好版本（分块算法）
    static void matrixMultiplyBlocked(const std::vector<std::vector<double>>& A,
                                     const std::vector<std::vector<double>>& B,
                                     std::vector<std::vector<double>>& C,
                                     size_t block_size = 64) {
        size_t n = A.size();
        
        for (size_t ii = 0; ii < n; ii += block_size) {
            for (size_t jj = 0; jj < n; jj += block_size) {
                for (size_t kk = 0; kk < n; kk += block_size) {
                    // 分块内的计算
                    size_t i_max = std::min(ii + block_size, n);
                    size_t j_max = std::min(jj + block_size, n);
                    size_t k_max = std::min(kk + block_size, n);
                    
                    for (size_t i = ii; i < i_max; ++i) {
                        for (size_t j = jj; j < j_max; ++j) {
                            double sum = 0.0;
                            for (size_t k = kk; k < k_max; ++k) {
                                sum += A[i][k] * B[k][j];
                            }
                            C[i][j] += sum;
                        }
                    }
                }
            }
        }
    }
    
    // 一维数组版本（更缓存友好）
    static void matrixMultiplyFlat(const std::vector<double>& A,
                                  const std::vector<double>& B,
                                  std::vector<double>& C,
                                  size_t n) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t k = 0; k < n; ++k) {
                double a_ik = A[i * n + k];
                for (size_t j = 0; j < n; ++j) {
                    C[i * n + j] += a_ik * B[k * n + j];
                }
            }
        }
    }
    
    // 测试缓存优化效果
    static void testCacheOptimization() {
        std::cout << "\n=== Cache Optimization Test ===\n";
        
        const size_t n = 256;
        
        // 初始化矩阵
        std::vector<std::vector<double>> A(n, std::vector<double>(n, 1.0));
        std::vector<std::vector<double>> B(n, std::vector<double>(n, 2.0));
        std::vector<std::vector<double>> C1(n, std::vector<double>(n, 0.0));
        std::vector<std::vector<double>> C2(n, std::vector<double>(n, 0.0));
        
        // 一维数组版本
        std::vector<double> A_flat(n * n, 1.0);
        std::vector<double> B_flat(n * n, 2.0);
        std::vector<double> C_flat(n * n, 0.0);
        
        // 测试朴素算法
        benchmarkFunction("Matrix Multiply Naive", [&]() {
            std::fill(C1.begin(), C1.end(), std::vector<double>(n, 0.0));
            matrixMultiplyNaive(A, B, C1);
        }, 3);
        
        // 测试分块算法
        benchmarkFunction("Matrix Multiply Blocked", [&]() {
            std::fill(C2.begin(), C2.end(), std::vector<double>(n, 0.0));
            matrixMultiplyBlocked(A, B, C2);
        }, 3);
        
        // 测试一维数组版本
        benchmarkFunction("Matrix Multiply Flat", [&]() {
            std::fill(C_flat.begin(), C_flat.end(), 0.0);
            matrixMultiplyFlat(A_flat, B_flat, C_flat, n);
        }, 3);
    }
};

// =============================================================================
// 2. 内存池优化
// =============================================================================

template<typename T, size_t BlockSize = 4096>
class HighPerformanceMemoryPool {
private:
    struct Block {
        alignas(T) char data[BlockSize];
        Block* next = nullptr;
    };
    
    Block* current_block = nullptr;
    char* current_pos = nullptr;
    char* block_end = nullptr;
    std::vector<std::unique_ptr<Block>> blocks;
    
    void allocateNewBlock() {
        auto block = std::make_unique<Block>();
        current_pos = block->data;
        block_end = block->data + BlockSize;
        current_block = block.get();
        blocks.push_back(std::move(block));
    }
    
public:
    HighPerformanceMemoryPool() {
        allocateNewBlock();
    }
    
    T* allocate() {
        if (current_pos + sizeof(T) > block_end) {
            allocateNewBlock();
        }
        
        T* result = reinterpret_cast<T*>(current_pos);
        current_pos += sizeof(T);
        return result;
    }
    
    void reset() {
        if (!blocks.empty()) {
            current_block = blocks[0].get();
            current_pos = current_block->data;
            block_end = current_block->data + BlockSize;
        }
    }
    
    size_t getBlockCount() const { return blocks.size(); }
    size_t getUsedMemory() const {
        return blocks.size() * BlockSize - (block_end - current_pos);
    }
};

// 使用内存池的高性能容器
template<typename T>
class PooledVector {
private:
    HighPerformanceMemoryPool<T>& pool;
    T* data = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    
public:
    PooledVector(HighPerformanceMemoryPool<T>& p) : pool(p) {}
    
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new(data + size_) T(value);
        ++size_;
    }
    
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = pool.allocate();  // 简化版本
            if (data) {
                for (size_t i = 0; i < size_; ++i) {
                    new(new_data + i) T(std::move(data[i]));
                    data[i].~T();
                }
            }
            data = new_data;
            capacity_ = new_capacity;
        }
    }
    
    size_t size() const { return size_; }
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
};

// 测试内存池性能
void testMemoryPool() {
    std::cout << "\n=== Memory Pool Performance Test ===\n";
    
    const size_t num_allocations = 100000;
    
    // 测试标准分配器
    benchmarkFunction("Standard Allocator", [&]() {
        std::vector<int*> ptrs;
        ptrs.reserve(num_allocations);
        
        for (size_t i = 0; i < num_allocations; ++i) {
            ptrs.push_back(new int(i));
        }
        
        for (auto ptr : ptrs) {
            delete ptr;
        }
    }, 10);
    
    // 测试内存池
    benchmarkFunction("Memory Pool", [&]() {
        HighPerformanceMemoryPool<int> pool;
        std::vector<int*> ptrs;
        ptrs.reserve(num_allocations);
        
        for (size_t i = 0; i < num_allocations; ++i) {
            int* ptr = pool.allocate();
            *ptr = i;
            ptrs.push_back(ptr);
        }
        
        pool.reset();  // 快速释放所有内存
    }, 10);
}

// =============================================================================
// 3. SIMD优化示例
// =============================================================================

class SIMDOptimization {
public:
    // 标量版本：数组求和
    static double sumArrayScalar(const float* arr, size_t size) {
        double sum = 0.0;
        for (size_t i = 0; i < size; ++i) {
            sum += arr[i];
        }
        return sum;
    }
    
    // SIMD版本：数组求和（AVX）
    static double sumArraySIMD(const float* arr, size_t size) {
        __m256 sum_vec = _mm256_setzero_ps();
        size_t simd_size = size - (size % 8);
        
        // SIMD处理
        for (size_t i = 0; i < simd_size; i += 8) {
            __m256 data = _mm256_loadu_ps(&arr[i]);
            sum_vec = _mm256_add_ps(sum_vec, data);
        }
        
        // 水平求和
        __m128 sum_high = _mm256_extractf128_ps(sum_vec, 1);
        __m128 sum_low = _mm256_castps256_ps128(sum_vec);
        __m128 sum_final = _mm_add_ps(sum_high, sum_low);
        
        sum_final = _mm_hadd_ps(sum_final, sum_final);
        sum_final = _mm_hadd_ps(sum_final, sum_final);
        
        double result = _mm_cvtss_f32(sum_final);
        
        // 处理剩余元素
        for (size_t i = simd_size; i < size; ++i) {
            result += arr[i];
        }
        
        return result;
    }
    
    // 向量加法 - 标量版本
    static void addArraysScalar(const float* a, const float* b, float* result, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            result[i] = a[i] + b[i];
        }
    }
    
    // 向量加法 - SIMD版本
    static void addArraysSIMD(const float* a, const float* b, float* result, size_t size) {
        size_t simd_size = size - (size % 8);
        
        for (size_t i = 0; i < simd_size; i += 8) {
            __m256 va = _mm256_loadu_ps(&a[i]);
            __m256 vb = _mm256_loadu_ps(&b[i]);
            __m256 vresult = _mm256_add_ps(va, vb);
            _mm256_storeu_ps(&result[i], vresult);
        }
        
        // 处理剩余元素
        for (size_t i = simd_size; i < size; ++i) {
            result[i] = a[i] + b[i];
        }
    }
    
    // 测试SIMD优化效果
    static void testSIMDOptimization() {
        std::cout << "\n=== SIMD Optimization Test ===\n";
        
        const size_t size = 1000000;
        
        // 初始化数据
        std::vector<float> a(size), b(size), result1(size), result2(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-100.0f, 100.0f);
        
        for (size_t i = 0; i < size; ++i) {
            a[i] = dis(gen);
            b[i] = dis(gen);
        }
        
        // 测试数组求和
        benchmarkFunction("Array Sum Scalar", [&]() {
            volatile double sum = sumArrayScalar(a.data(), size);
        }, 100);
        
        benchmarkFunction("Array Sum SIMD", [&]() {
            volatile double sum = sumArraySIMD(a.data(), size);
        }, 100);
        
        // 测试向量加法
        benchmarkFunction("Array Add Scalar", [&]() {
            addArraysScalar(a.data(), b.data(), result1.data(), size);
        }, 100);
        
        benchmarkFunction("Array Add SIMD", [&]() {
            addArraysSIMD(a.data(), b.data(), result2.data(), size);
        }, 100);
        
        // 验证结果正确性
        bool results_match = std::equal(result1.begin(), result1.end(), result2.begin(),
            [](float a, float b) { return std::abs(a - b) < 1e-6f; });
        std::cout << "Results match: " << (results_match ? "Yes" : "No") << std::endl;
    }
};

// =============================================================================
// 4. 分支预测优化
// =============================================================================

class BranchOptimization {
public:
    // 分支预测不友好的版本
    static int countPositivesBad(const std::vector<int>& data) {
        int count = 0;
        for (int value : data) {
            if (value > 0) {  // 随机分支，预测困难
                count++;
            }
        }
        return count;
    }
    
    // 分支预测友好的版本
    static int countPositivesGood(const std::vector<int>& data) {
        int count = 0;
        for (int value : data) {
            // 使用算术运算代替分支
            count += (value > 0) ? 1 : 0;  // 编译器可能优化为无分支代码
        }
        return count;
    }
    
    // 使用位运算完全避免分支
    static int countPositivesBest(const std::vector<int>& data) {
        int count = 0;
        for (int value : data) {
            // 利用符号位，完全无分支
            count += (value >> 31) ^ 1;  // 如果value >= 0，则+1
        }
        return count;
    }
    
    // 查表法优化
    static constexpr std::array<int, 256> popcount_table = []() {
        std::array<int, 256> table{};
        for (int i = 0; i < 256; ++i) {
            table[i] = __builtin_popcount(i);
        }
        return table;
    }();
    
    static int popcountLookup(uint8_t x) {
        return popcount_table[x];
    }
    
    static int popcountBranches(uint8_t x) {
        int count = 0;
        while (x) {
            if (x & 1) count++;  // 分支预测困难
            x >>= 1;
        }
        return count;
    }
    
    // 测试分支优化效果
    static void testBranchOptimization() {
        std::cout << "\n=== Branch Optimization Test ===\n";
        
        const size_t size = 1000000;
        std::vector<int> random_data(size);
        std::vector<int> sorted_data(size);
        
        // 生成随机数据（分支预测困难）
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(-1000, 1000);
        
        for (size_t i = 0; i < size; ++i) {
            random_data[i] = dis(gen);
        }
        
        // 生成排序数据（分支预测容易）
        std::iota(sorted_data.begin(), sorted_data.end(), -500000);
        
        std::cout << "Testing with random data (branch prediction hard):\n";
        benchmarkFunction("Count Positives Bad", [&]() {
            volatile int count = countPositivesBad(random_data);
        }, 50);
        
        benchmarkFunction("Count Positives Good", [&]() {
            volatile int count = countPositivesGood(random_data);
        }, 50);
        
        benchmarkFunction("Count Positives Best", [&]() {
            volatile int count = countPositivesBest(random_data);
        }, 50);
        
        std::cout << "\nTesting with sorted data (branch prediction easy):\n";
        benchmarkFunction("Count Positives Bad (sorted)", [&]() {
            volatile int count = countPositivesBad(sorted_data);
        }, 50);
        
        benchmarkFunction("Count Positives Good (sorted)", [&]() {
            volatile int count = countPositivesGood(sorted_data);
        }, 50);
        
        // 测试查表法
        std::vector<uint8_t> bytes(size);
        std::generate(bytes.begin(), bytes.end(), [&]() { return dis(gen) & 0xFF; });
        
        benchmarkFunction("Popcount Branches", [&]() {
            int total = 0;
            for (uint8_t b : bytes) {
                total += popcountBranches(b);
            }
            volatile int result = total;
        }, 50);
        
        benchmarkFunction("Popcount Lookup", [&]() {
            int total = 0;
            for (uint8_t b : bytes) {
                total += popcountLookup(b);
            }
            volatile int result = total;
        }, 50);
    }
};

// =============================================================================
// 5. 数据结构优化
// =============================================================================

// 传统的链表节点（缓存不友好）
struct ListNode {
    int data;
    ListNode* next;
    
    ListNode(int val) : data(val), next(nullptr) {}
};

// 缓存友好的数组链表
class ArrayBasedList {
private:
    struct Node {
        int data;
        int next;  // 索引而不是指针
    };
    
    std::vector<Node> nodes;
    int head;
    int free_list;
    
public:
    ArrayBasedList() : head(-1), free_list(-1) {
        nodes.reserve(1000);  // 预分配
    }
    
    void push_front(int value) {
        int new_index;
        
        if (free_list != -1) {
            new_index = free_list;
            free_list = nodes[free_list].next;
        } else {
            new_index = nodes.size();
            nodes.emplace_back();
        }
        
        nodes[new_index].data = value;
        nodes[new_index].next = head;
        head = new_index;
    }
    
    void pop_front() {
        if (head != -1) {
            int old_head = head;
            head = nodes[head].next;
            nodes[old_head].next = free_list;
            free_list = old_head;
        }
    }
    
    int sum() const {
        int total = 0;
        int current = head;
        while (current != -1) {
            total += nodes[current].data;
            current = nodes[current].next;
        }
        return total;
    }
};

// 测试数据结构优化
void testDataStructureOptimization() {
    std::cout << "\n=== Data Structure Optimization Test ===\n";
    
    const int num_operations = 100000;
    
    // 测试传统链表
    benchmarkFunction("Traditional Linked List", [&]() {
        ListNode* head = nullptr;
        
        // 插入操作
        for (int i = 0; i < num_operations; ++i) {
            ListNode* new_node = new ListNode(i);
            new_node->next = head;
            head = new_node;
        }
        
        // 求和操作
        int sum = 0;
        ListNode* current = head;
        while (current) {
            sum += current->data;
            current = current->next;
        }
        
        // 清理内存
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        
        volatile int result = sum;
    }, 10);
    
    // 测试数组链表
    benchmarkFunction("Array-based List", [&]() {
        ArrayBasedList list;
        
        // 插入操作
        for (int i = 0; i < num_operations; ++i) {
            list.push_front(i);
        }
        
        // 求和操作
        volatile int sum = list.sum();
    }, 10);
}

// =============================================================================
// 主测试函数
// =============================================================================

int main() {
    std::cout << "=== C++ Performance Optimization Benchmarks ===\n";
    std::cout << "Compiled with optimization flags for best performance\n";
    
    try {
        // 测试各种优化技术
        CacheOptimization::testCacheOptimization();
        testMemoryPool();
        SIMDOptimization::testSIMDOptimization();
        BranchOptimization::testBranchOptimization();
        testDataStructureOptimization();
        
        std::cout << "\n=== All performance tests completed! ===\n";
        std::cout << "Note: Results may vary depending on hardware and compiler optimizations.\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
编译和运行说明：

1. 编译命令（重要！）：
   g++ -std=c++17 -O2 -march=native -pthread -mavx2 -o practice_exercises practice_exercises.cpp
   
   参数说明：
   -O2: 开启优化
   -march=native: 针对本机CPU优化
   -mavx2: 启用AVX2指令集
   -pthread: 线程支持

2. 运行：
   ./practice_exercises

3. 预期输出：
   - 各种优化技术的性能对比
   - 缓存友好 vs 缓存不友好的性能差异
   - SIMD vs 标量计算的性能提升
   - 分支预测优化的效果

4. 学习重点：
   - 缓存友好的数据访问模式
   - SIMD指令的使用
   - 分支预测优化技巧
   - 内存池的实现和使用
   - 数据结构选择对性能的影响

5. 性能分析工具：
   - 使用perf工具分析缓存命中率
   - 使用valgrind分析内存使用
   - 使用gprof分析函数调用开销

6. 扩展练习：
   - 尝试不同的编译器优化选项
   - 测试在不同硬件上的性能表现
   - 实现更复杂的SIMD算法
   - 添加多线程优化
*/
