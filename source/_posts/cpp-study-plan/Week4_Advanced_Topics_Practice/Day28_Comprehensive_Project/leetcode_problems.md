# 第28天：综合项目 - LeetCode系统设计题

## 今日算法练习 (4道Hard系统设计题)

### 题目1：分布式系统设计
**LeetCode 1622. Fancy Sequence (Hard)**
- **链接：** https://leetcode.com/problems/fancy-sequence/
- **难度：** Hard
- **知识点：** 系统设计、数学、延迟计算、模运算
- **描述：** 设计一个支持append、addAll、multAll、getIndex操作的序列
- **系统设计要点：**
  - 高效的批量操作处理
  - 延迟计算优化
  - 数学运算的正确性
  - 大规模数据处理

**系统化实现：**
```cpp
#include <vector>
#include <stdexcept>
#include <iostream>

class FancySequence {
private:
    static constexpr long long MOD = 1000000007;
    
    // 数据存储
    std::vector<long long> data_;
    
    // 全局变换参数
    long long global_add_ = 0;
    long long global_mult_ = 1;
    
    // 日志系统（简化版）
    struct Operation {
        std::string type;
        long long value;
        size_t timestamp;
    };
    std::vector<Operation> operation_log_;
    size_t operation_counter_ = 0;
    
    // 性能统计
    mutable size_t total_operations_ = 0;
    mutable size_t cache_hits_ = 0;
    
    // 数学工具函数
    long long modPow(long long base, long long exp, long long mod) const {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
    
    long long modInverse(long long a, long long mod) const {
        return modPow(a, mod - 2, mod);  // 费马小定理
    }
    
    void logOperation(const std::string& type, long long value = 0) {
        operation_log_.push_back({type, value, operation_counter_++});
        
        // 限制日志大小
        if (operation_log_.size() > 10000) {
            operation_log_.erase(operation_log_.begin(), 
                               operation_log_.begin() + 5000);
        }
    }
    
public:
    FancySequence() {
        data_.reserve(1000);  // 预分配内存
        operation_log_.reserve(1000);
        logOperation("INIT");
    }
    
    void append(int val) {
        ++total_operations_;
        
        // 将新值转换为当前全局变换下的原始值
        long long original_val = val;
        
        // 撤销当前的全局变换
        if (global_mult_ != 1) {
            original_val = (original_val * modInverse(global_mult_, MOD)) % MOD;
        }
        if (global_add_ != 0) {
            original_val = (original_val - global_add_ + MOD) % MOD;
        }
        
        data_.push_back(original_val);
        logOperation("APPEND", val);
    }
    
    void addAll(int inc) {
        ++total_operations_;
        global_add_ = (global_add_ + inc) % MOD;
        logOperation("ADD_ALL", inc);
    }
    
    void multAll(int m) {
        ++total_operations_;
        global_mult_ = (global_mult_ * m) % MOD;
        global_add_ = (global_add_ * m) % MOD;
        logOperation("MULT_ALL", m);
    }
    
    int getIndex(int idx) const {
        ++total_operations_;
        
        if (idx < 0 || idx >= static_cast<int>(data_.size())) {
            return -1;
        }
        
        // 应用全局变换
        long long result = data_[idx];
        result = (result * global_mult_) % MOD;
        result = (result + global_add_) % MOD;
        
        return static_cast<int>(result);
    }
    
    // 系统监控和统计功能
    struct SystemStats {
        size_t total_operations;
        size_t data_size;
        size_t log_size;
        double cache_hit_rate;
        long long current_global_add;
        long long current_global_mult;
    };
    
    SystemStats getSystemStats() const {
        return {
            total_operations_,
            data_.size(),
            operation_log_.size(),
            total_operations_ > 0 ? static_cast<double>(cache_hits_) / total_operations_ : 0.0,
            global_add_,
            global_mult_
        };
    }
    
    // 批量操作优化
    std::vector<int> getRange(int start, int end) const {
        std::vector<int> result;
        if (start < 0 || end >= static_cast<int>(data_.size()) || start > end) {
            return result;
        }
        
        result.reserve(end - start + 1);
        for (int i = start; i <= end; ++i) {
            result.push_back(getIndex(i));
        }
        
        return result;
    }
    
    // 系统重置
    void reset() {
        data_.clear();
        global_add_ = 0;
        global_mult_ = 1;
        operation_log_.clear();
        operation_counter_ = 0;
        total_operations_ = 0;
        cache_hits_ = 0;
        logOperation("RESET");
    }
    
    // 系统状态序列化（简化版）
    std::string serialize() const {
        std::ostringstream oss;
        oss << "DATA_SIZE:" << data_.size() << ";";
        oss << "GLOBAL_ADD:" << global_add_ << ";";
        oss << "GLOBAL_MULT:" << global_mult_ << ";";
        oss << "OPERATIONS:" << total_operations_ << ";";
        return oss.str();
    }
};
```

### 题目2：缓存系统设计
**LeetCode 460. LFU Cache (Hard)**
- **链接：** https://leetcode.com/problems/lfu-cache/
- **难度：** Hard
- **知识点：** 缓存设计、频率统计、双向链表、哈希表
- **描述：** 设计LFU(最少使用频率)缓存，支持O(1)时间复杂度的get和put
- **系统设计要点：**
  - 多级数据结构协调
  - 高效的频率管理
  - 内存使用优化
  - 并发安全考虑

**企业级实现：**
```cpp
#include <unordered_map>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <atomic>

template<typename Key, typename Value>
class LFUCache {
private:
    struct CacheNode {
        Key key;
        Value value;
        int frequency;
        std::chrono::system_clock::time_point last_access;
        
        CacheNode(const Key& k, const Value& v) 
            : key(k), value(v), frequency(1), 
              last_access(std::chrono::system_clock::now()) {}
    };
    
    using NodeList = std::list<CacheNode>;
    using NodeIterator = typename NodeList::iterator;
    
    // 核心数据结构
    int capacity_;
    int min_frequency_;
    
    // key -> node iterator
    std::unordered_map<Key, NodeIterator> key_to_node_;
    
    // frequency -> list of nodes with that frequency
    std::unordered_map<int, NodeList> freq_to_nodes_;
    
    // 线程安全
    mutable std::shared_mutex cache_mutex_;
    
    // 性能统计
    mutable std::atomic<size_t> total_gets_{0};
    mutable std::atomic<size_t> cache_hits_{0};
    mutable std::atomic<size_t> total_puts_{0};
    mutable std::atomic<size_t> evictions_{0};
    
    // 内存管理
    std::atomic<size_t> memory_usage_{0};
    
    void updateFrequency(NodeIterator node_it) {
        int old_freq = node_it->frequency;
        int new_freq = old_freq + 1;
        
        // 更新访问时间
        node_it->last_access = std::chrono::system_clock::now();
        
        // 移动到新频率列表
        CacheNode node = *node_it;
        node.frequency = new_freq;
        
        // 从旧频率列表删除
        freq_to_nodes_[old_freq].erase(node_it);
        if (freq_to_nodes_[old_freq].empty() && old_freq == min_frequency_) {
            ++min_frequency_;
        }
        
        // 添加到新频率列表
        freq_to_nodes_[new_freq].push_front(node);
        key_to_node_[node.key] = freq_to_nodes_[new_freq].begin();
    }
    
    void evictLFU() {
        if (freq_to_nodes_[min_frequency_].empty()) {
            return;
        }
        
        // 移除最少使用频率列表的最后一个元素（最久未使用）
        auto& min_freq_list = freq_to_nodes_[min_frequency_];
        auto last_node = std::prev(min_freq_list.end());
        
        key_to_node_.erase(last_node->key);
        memory_usage_ -= sizeof(CacheNode) + sizeof(Key) + sizeof(Value);
        min_freq_list.erase(last_node);
        
        ++evictions_;
        
        // 更新最小频率
        if (min_freq_list.empty()) {
            while (freq_to_nodes_.find(min_frequency_) == freq_to_nodes_.end() ||
                   freq_to_nodes_[min_frequency_].empty()) {
                ++min_frequency_;
            }
        }
    }
    
public:
    explicit LFUCache(int capacity) : capacity_(capacity), min_frequency_(1) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
    }
    
    std::optional<Value> get(const Key& key) {
        ++total_gets_;
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        
        auto it = key_to_node_.find(key);
        if (it == key_to_node_.end()) {
            return std::nullopt;
        }
        
        ++cache_hits_;
        updateFrequency(it->second);
        return it->second->value;
    }
    
    void put(const Key& key, const Value& value) {
        ++total_puts_;
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        
        if (capacity_ == 0) return;
        
        auto it = key_to_node_.find(key);
        if (it != key_to_node_.end()) {
            // 更新现有键
            it->second->value = value;
            updateFrequency(it->second);
            return;
        }
        
        // 添加新键
        if (key_to_node_.size() >= capacity_) {
            evictLFU();
        }
        
        // 插入新节点
        freq_to_nodes_[1].emplace_front(key, value);
        key_to_node_[key] = freq_to_nodes_[1].begin();
        min_frequency_ = 1;
        
        memory_usage_ += sizeof(CacheNode) + sizeof(Key) + sizeof(Value);
    }
    
    // 系统监控功能
    struct CacheStats {
        size_t total_gets;
        size_t cache_hits;
        size_t total_puts;
        size_t evictions;
        double hit_rate;
        size_t current_size;
        size_t capacity;
        size_t memory_usage;
        int min_frequency;
    };
    
    CacheStats getStats() const {
        std::shared_lock<std::shared_mutex> lock(cache_mutex_);
        
        size_t gets = total_gets_.load();
        size_t hits = cache_hits_.load();
        
        return {
            gets,
            hits,
            total_puts_.load(),
            evictions_.load(),
            gets > 0 ? static_cast<double>(hits) / gets : 0.0,
            key_to_node_.size(),
            static_cast<size_t>(capacity_),
            memory_usage_.load(),
            min_frequency_
        };
    }
    
    // 批量操作
    std::unordered_map<Key, Value> getBatch(const std::vector<Key>& keys) {
        std::unordered_map<Key, Value> result;
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        
        for (const auto& key : keys) {
            auto it = key_to_node_.find(key);
            if (it != key_to_node_.end()) {
                result[key] = it->second->value;
                updateFrequency(it->second);
            }
        }
        
        total_gets_ += keys.size();
        cache_hits_ += result.size();
        
        return result;
    }
    
    void putBatch(const std::unordered_map<Key, Value>& items) {
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        
        for (const auto& [key, value] : items) {
            put(key, value);
        }
    }
    
    // 缓存预热
    void warmUp(const std::unordered_map<Key, Value>& initial_data) {
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        
        for (const auto& [key, value] : initial_data) {
            if (key_to_node_.size() >= capacity_) break;
            
            freq_to_nodes_[1].emplace_front(key, value);
            key_to_node_[key] = freq_to_nodes_[1].begin();
        }
        
        min_frequency_ = 1;
    }
    
    // 缓存清理
    void clear() {
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        
        key_to_node_.clear();
        freq_to_nodes_.clear();
        min_frequency_ = 1;
        memory_usage_ = 0;
    }
    
    // 获取频率分布
    std::unordered_map<int, size_t> getFrequencyDistribution() const {
        std::shared_lock<std::shared_mutex> lock(cache_mutex_);
        
        std::unordered_map<int, size_t> distribution;
        for (const auto& [freq, nodes] : freq_to_nodes_) {
            distribution[freq] = nodes.size();
        }
        
        return distribution;
    }
};
```

### 题目3：实时数据流系统
**LeetCode 295. Find Median from Data Stream (Hard)**
- **链接：** https://leetcode.com/problems/find-median-from-data-stream/
- **难度：** Hard
- **知识点：** 数据流处理、堆、实时计算、统计
- **描述：** 设计数据结构从数据流中找到中位数
- **系统设计要点：**
  - 实时数据处理
  - 内存效率优化
  - 多线程安全
  - 统计信息维护

**生产级实现：**
```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>

class MedianFinder {
private:
    // 双堆结构：最大堆存储较小的一半，最小堆存储较大的一半
    std::priority_queue<int> max_heap_;  // 存储较小的一半
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap_;  // 存储较大的一半
    
    // 线程安全
    mutable std::mutex heap_mutex_;
    
    // 性能统计
    std::atomic<size_t> total_numbers_{0};
    std::atomic<size_t> median_queries_{0};
    
    // 数据流处理
    std::queue<int> buffer_;
    std::mutex buffer_mutex_;
    std::condition_variable buffer_cv_;
    std::thread processing_thread_;
    std::atomic<bool> running_{false};
    
    // 高级统计信息
    std::atomic<long long> sum_{0};
    std::atomic<int> min_value_{INT_MAX};
    std::atomic<int> max_value_{INT_MIN};
    
    void balanceHeaps() {
        // 确保两个堆的大小差不超过1
        if (max_heap_.size() > min_heap_.size() + 1) {
            min_heap_.push(max_heap_.top());
            max_heap_.pop();
        } else if (min_heap_.size() > max_heap_.size() + 1) {
            max_heap_.push(min_heap_.top());
            min_heap_.pop();
        }
    }
    
    void processBuffer() {
        while (running_) {
            std::unique_lock<std::mutex> buffer_lock(buffer_mutex_);
            buffer_cv_.wait(buffer_lock, [this]() {
                return !buffer_.empty() || !running_;
            });
            
            if (!running_) break;
            
            // 批量处理缓冲区中的数据
            std::vector<int> batch;
            while (!buffer_.empty() && batch.size() < 100) {  // 批量大小限制
                batch.push_back(buffer_.front());
                buffer_.pop();
            }
            buffer_lock.unlock();
            
            // 处理批量数据
            if (!batch.empty()) {
                std::lock_guard<std::mutex> heap_lock(heap_mutex_);
                for (int num : batch) {
                    addNumberInternal(num);
                }
            }
        }
    }
    
    void addNumberInternal(int num) {
        // 更新统计信息
        ++total_numbers_;
        sum_ += num;
        
        int current_min = min_value_.load();
        while (num < current_min && !min_value_.compare_exchange_weak(current_min, num));
        
        int current_max = max_value_.load();
        while (num > current_max && !max_value_.compare_exchange_weak(current_max, num));
        
        // 添加到堆
        if (max_heap_.empty() || num <= max_heap_.top()) {
            max_heap_.push(num);
        } else {
            min_heap_.push(num);
        }
        
        balanceHeaps();
    }
    
public:
    MedianFinder() {
        running_ = true;
        processing_thread_ = std::thread(&MedianFinder::processBuffer, this);
    }
    
    ~MedianFinder() {
        running_ = false;
        buffer_cv_.notify_all();
        if (processing_thread_.joinable()) {
            processing_thread_.join();
        }
    }
    
    // 异步添加数字（生产环境常用）
    void addNumberAsync(int num) {
        {
            std::lock_guard<std::mutex> lock(buffer_mutex_);
            buffer_.push(num);
        }
        buffer_cv_.notify_one();
    }
    
    // 同步添加数字
    void addNumber(int num) {
        std::lock_guard<std::mutex> lock(heap_mutex_);
        addNumberInternal(num);
    }
    
    double findMedian() const {
        ++median_queries_;
        std::lock_guard<std::mutex> lock(heap_mutex_);
        
        if (max_heap_.empty() && min_heap_.empty()) {
            throw std::runtime_error("No numbers available");
        }
        
        if (max_heap_.size() == min_heap_.size()) {
            return (max_heap_.top() + min_heap_.top()) / 2.0;
        } else if (max_heap_.size() > min_heap_.size()) {
            return max_heap_.top();
        } else {
            return min_heap_.top();
        }
    }
    
    // 扩展功能：获取百分位数
    double getPercentile(double percentile) const {
        if (percentile < 0 || percentile > 100) {
            throw std::invalid_argument("Percentile must be between 0 and 100");
        }
        
        std::lock_guard<std::mutex> lock(heap_mutex_);
        
        // 将两个堆合并为排序数组（简化实现）
        std::vector<int> all_numbers;
        
        // 从最大堆获取数据（需要反转）
        auto max_heap_copy = max_heap_;
        while (!max_heap_copy.empty()) {
            all_numbers.push_back(max_heap_copy.top());
            max_heap_copy.pop();
        }
        std::reverse(all_numbers.begin(), all_numbers.end());
        
        // 从最小堆获取数据
        auto min_heap_copy = min_heap_;
        while (!min_heap_copy.empty()) {
            all_numbers.push_back(min_heap_copy.top());
            min_heap_copy.pop();
        }
        
        if (all_numbers.empty()) return 0.0;
        
        size_t index = static_cast<size_t>(percentile / 100.0 * (all_numbers.size() - 1));
        return all_numbers[index];
    }
    
    // 系统统计信息
    struct StreamStats {
        size_t total_numbers;
        size_t median_queries;
        double mean;
        int min_value;
        int max_value;
        size_t buffer_size;
        double current_median;
    };
    
    StreamStats getStats() const {
        std::lock_guard<std::mutex> heap_lock(heap_mutex_);
        std::lock_guard<std::mutex> buffer_lock(buffer_mutex_);
        
        size_t total = total_numbers_.load();
        
        return {
            total,
            median_queries_.load(),
            total > 0 ? static_cast<double>(sum_.load()) / total : 0.0,
            min_value_.load(),
            max_value_.load(),
            buffer_.size(),
            total > 0 ? findMedian() : 0.0
        };
    }
    
    // 批量添加
    void addNumbers(const std::vector<int>& numbers) {
        std::lock_guard<std::mutex> lock(heap_mutex_);
        for (int num : numbers) {
            addNumberInternal(num);
        }
    }
    
    // 清空数据
    void clear() {
        std::lock_guard<std::mutex> heap_lock(heap_mutex_);
        std::lock_guard<std::mutex> buffer_lock(buffer_mutex_);
        
        while (!max_heap_.empty()) max_heap_.pop();
        while (!min_heap_.empty()) min_heap_.pop();
        while (!buffer_.empty()) buffer_.pop();
        
        total_numbers_ = 0;
        median_queries_ = 0;
        sum_ = 0;
        min_value_ = INT_MAX;
        max_value_ = INT_MIN;
    }
};
```

### 题目4：分布式一致性系统 (Hard)
**LeetCode 1396. Design Underground System (Medium升级为分布式版本)**
- **难度：** Hard (分布式版本)
- **知识点：** 分布式系统、一致性、分片、负载均衡
- **描述：** 设计分布式地铁系统，支持多节点、数据一致性、故障恢复
- **系统设计要点：**
  - 数据分片策略
  - 一致性协议
  - 故障检测和恢复
  - 负载均衡

**分布式系统实现：**
```cpp
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <random>

// 分布式地铁系统
class DistributedUndergroundSystem {
private:
    // 数据结构
    struct CheckInRecord {
        std::string station_name;
        int check_in_time;
        std::chrono::system_clock::time_point timestamp;
    };
    
    struct TravelRecord {
        std::string start_station;
        std::string end_station;
        int travel_time;
        std::chrono::system_clock::time_point timestamp;
    };
    
    struct RouteStats {
        double total_time = 0.0;
        int count = 0;
        std::chrono::system_clock::time_point last_update;
        
        void addTravel(int time) {
            total_time += time;
            ++count;
            last_update = std::chrono::system_clock::now();
        }
        
        double getAverageTime() const {
            return count > 0 ? total_time / count : 0.0;
        }
    };
    
    // 节点信息
    struct NodeInfo {
        std::string node_id;
        std::string address;
        bool is_active;
        std::chrono::system_clock::time_point last_heartbeat;
        int load_factor;
    };
    
    // 核心数据
    std::unordered_map<int, CheckInRecord> check_ins_;
    std::unordered_map<std::string, RouteStats> route_stats_;
    
    // 分布式相关
    std::string node_id_;
    std::vector<NodeInfo> cluster_nodes_;
    std::unordered_map<std::string, int> data_shards_;  // route -> node_index
    
    // 线程安全
    mutable std::shared_mutex data_mutex_;
    mutable std::mutex cluster_mutex_;
    
    // 一致性和同步
    std::atomic<int> version_vector_{0};
    std::thread heartbeat_thread_;
    std::thread sync_thread_;
    std::atomic<bool> running_{true};
    
    // 性能统计
    std::atomic<size_t> total_checkins_{0};
    std::atomic<size_t> total_checkouts_{0};
    std::atomic<size_t> total_queries_{0};
    std::atomic<size_t> replication_ops_{0};
    
    // 分片函数
    int getShardForRoute(const std::string& route) const {
        std::hash<std::string> hasher;
        return hasher(route) % cluster_nodes_.size();
    }
    
    std::string getRouteKey(const std::string& start, const std::string& end) const {
        return start + "->" + end;
    }
    
    // 心跳机制
    void heartbeatLoop() {
        while (running_) {
            {
                std::lock_guard<std::mutex> lock(cluster_mutex_);
                for (auto& node : cluster_nodes_) {
                    if (node.node_id == node_id_) {
                        node.last_heartbeat = std::chrono::system_clock::now();
                        node.is_active = true;
                    } else {
                        // 检查其他节点的心跳
                        auto now = std::chrono::system_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                            now - node.last_heartbeat);
                        
                        if (duration.count() > 30) {  // 30秒超时
                            node.is_active = false;
                        }
                    }
                }
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
    
    // 数据同步
    void syncLoop() {
        while (running_) {
            // 简化的数据同步逻辑
            {
                std::shared_lock<std::shared_mutex> lock(data_mutex_);
                // 在实际实现中，这里会将数据同步到其他节点
                ++replication_ops_;
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
    
    // 故障检测和恢复
    void handleNodeFailure(const std::string& failed_node_id) {
        std::lock_guard<std::mutex> lock(cluster_mutex_);
        
        // 重新分配失败节点的数据分片
        for (auto& [route, node_index] : data_shards_) {
            if (cluster_nodes_[node_index].node_id == failed_node_id) {
                // 找到活跃节点重新分配
                for (size_t i = 0; i < cluster_nodes_.size(); ++i) {
                    if (cluster_nodes_[i].is_active && 
                        cluster_nodes_[i].node_id != failed_node_id) {
                        data_shards_[route] = i;
                        break;
                    }
                }
            }
        }
    }
    
public:
    DistributedUndergroundSystem(const std::string& node_id, 
                               const std::vector<std::string>& cluster_addresses) 
        : node_id_(node_id) {
        
        // 初始化集群节点
        for (size_t i = 0; i < cluster_addresses.size(); ++i) {
            NodeInfo node;
            node.node_id = "node-" + std::to_string(i);
            node.address = cluster_addresses[i];
            node.is_active = true;
            node.last_heartbeat = std::chrono::system_clock::now();
            node.load_factor = 0;
            cluster_nodes_.push_back(node);
        }
        
        // 启动后台线程
        heartbeat_thread_ = std::thread(&DistributedUndergroundSystem::heartbeatLoop, this);
        sync_thread_ = std::thread(&DistributedUndergroundSystem::syncLoop, this);
    }
    
    ~DistributedUndergroundSystem() {
        running_ = false;
        if (heartbeat_thread_.joinable()) heartbeat_thread_.join();
        if (sync_thread_.joinable()) sync_thread_.join();
    }
    
    void checkIn(int id, const std::string& stationName, int t) {
        ++total_checkins_;
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        
        check_ins_[id] = {stationName, t, std::chrono::system_clock::now()};
        ++version_vector_;
    }
    
    void checkOut(int id, const std::string& stationName, int t) {
        ++total_checkouts_;
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        
        auto it = check_ins_.find(id);
        if (it != check_ins_.end()) {
            const auto& checkin = it->second;
            int travel_time = t - checkin.check_in_time;
            
            std::string route = getRouteKey(checkin.station_name, stationName);
            route_stats_[route].addTravel(travel_time);
            
            check_ins_.erase(it);
            ++version_vector_;
        }
    }
    
    double getAverageTime(const std::string& startStation, const std::string& endStation) {
        ++total_queries_;
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        
        std::string route = getRouteKey(startStation, endStation);
        auto it = route_stats_.find(route);
        
        if (it != route_stats_.end()) {
            return it->second.getAverageTime();
        }
        
        return 0.0;
    }
    
    // 分布式系统管理功能
    struct ClusterStats {
        size_t total_nodes;
        size_t active_nodes;
        size_t total_checkins;
        size_t total_checkouts;
        size_t total_queries;
        size_t replication_ops;
        int current_version;
        std::vector<std::pair<std::string, bool>> node_status;
    };
    
    ClusterStats getClusterStats() const {
        std::lock_guard<std::mutex> cluster_lock(cluster_mutex_);
        
        ClusterStats stats;
        stats.total_nodes = cluster_nodes_.size();
        stats.active_nodes = 0;
        stats.total_checkins = total_checkins_.load();
        stats.total_checkouts = total_checkouts_.load();
        stats.total_queries = total_queries_.load();
        stats.replication_ops = replication_ops_.load();
        stats.current_version = version_vector_.load();
        
        for (const auto& node : cluster_nodes_) {
            if (node.is_active) ++stats.active_nodes;
            stats.node_status.emplace_back(node.node_id, node.is_active);
        }
        
        return stats;
    }
    
    // 数据迁移（用于节点扩容/缩容）
    void migrateData(const std::string& target_node_id, 
                    const std::vector<std::string>& routes) {
        std::unique_lock<std::shared_mutex> data_lock(data_mutex_);
        std::lock_guard<std::mutex> cluster_lock(cluster_mutex_);
        
        // 在实际实现中，这里会将指定路由的数据迁移到目标节点
        for (const auto& route : routes) {
            // 找到目标节点索引
            for (size_t i = 0; i < cluster_nodes_.size(); ++i) {
                if (cluster_nodes_[i].node_id == target_node_id) {
                    data_shards_[route] = i;
                    break;
                }
            }
        }
        
        ++version_vector_;
    }
    
    // 负载均衡
    void rebalanceLoad() {
        std::lock_guard<std::mutex> lock(cluster_mutex_);
        
        // 计算每个节点的负载
        std::vector<int> node_loads(cluster_nodes_.size(), 0);
        for (const auto& [route, node_index] : data_shards_) {
            if (node_index < node_loads.size()) {
                ++node_loads[node_index];
            }
        }
        
        // 简单的负载均衡：将负载最高节点的部分数据迁移到负载最低节点
        auto max_it = std::max_element(node_loads.begin(), node_loads.end());
        auto min_it = std::min_element(node_loads.begin(), node_loads.end());
        
        if (max_it != node_loads.end() && min_it != node_loads.end() && 
            *max_it > *min_it + 1) {
            
            int max_node = std::distance(node_loads.begin(), max_it);
            int min_node = std::distance(node_loads.begin(), min_it);
            
            // 迁移一个分片
            for (auto& [route, node_index] : data_shards_) {
                if (node_index == max_node) {
                    node_index = min_node;
                    break;
                }
            }
        }
    }
    
    // 一致性检查
    bool checkConsistency() const {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        
        // 简化的一致性检查：验证数据完整性
        for (const auto& [route, stats] : route_stats_) {
            if (stats.count < 0 || stats.total_time < 0) {
                return false;
            }
        }
        
        return true;
    }
};
```

## 系统设计总结

### 1. 核心设计原则
- **可扩展性**：支持水平和垂直扩展
- **可靠性**：故障检测和自动恢复
- **一致性**：数据一致性保证
- **性能**：高并发和低延迟
- **可观测性**：完善的监控和日志

### 2. 技术栈选择
- **并发控制**：mutex、shared_mutex、atomic
- **内存管理**：智能指针、RAII
- **数据结构**：高效的容器选择
- **算法优化**：时间和空间复杂度优化

### 3. 系统架构模式
- **微服务架构**：模块化设计
- **事件驱动**：异步消息处理
- **CQRS**：命令查询职责分离
- **分片策略**：数据分布和负载均衡

## 学习目标检查

完成今天的系统设计题后，你应该能够：

1. ✅ **掌握系统架构设计**：模块化、可扩展的架构
2. ✅ **理解分布式系统**：一致性、分片、故障恢复
3. ✅ **应用设计模式**：在大型系统中合理使用设计模式
4. ✅ **优化系统性能**：并发控制、内存管理、算法优化
5. ✅ **实现监控和日志**：系统可观测性
6. ✅ **处理复杂业务逻辑**：实际场景的系统设计

## 提交要求

1. 每道题提供完整的系统设计和实现
2. 包含详细的架构文档和设计说明
3. 提供性能测试和压力测试结果
4. 分析系统的可扩展性和可靠性
5. 总结系统设计的最佳实践和经验教训

## 系统设计检查清单

- [ ] 是否考虑了系统的可扩展性
- [ ] 是否实现了适当的并发控制
- [ ] 是否提供了完善的错误处理
- [ ] 是否包含了监控和日志功能
- [ ] 是否考虑了性能优化
- [ ] 是否设计了合理的数据结构
- [ ] 是否应用了适当的设计模式
- [ ] 是否考虑了系统的维护性
