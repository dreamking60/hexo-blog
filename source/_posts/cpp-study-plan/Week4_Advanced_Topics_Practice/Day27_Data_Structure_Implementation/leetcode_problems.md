# 第27天：数据结构实现 - LeetCode算法题

## 今日算法练习 (4道Medium/Hard题目)

### 题目1：自定义数据结构设计
**LeetCode 146. LRU Cache (Medium)**
- **链接：** https://leetcode.com/problems/lru-cache/
- **难度：** Medium
- **知识点：** 哈希表、双向链表、缓存设计
- **描述：** 设计LRU(最近最少使用)缓存，支持get和put操作，都要求O(1)时间复杂度
- **数据结构要求：**
  - 自实现双向链表
  - 自实现哈希表
  - 组合使用实现LRU功能

**自实现版本：**
```cpp
class LRUCache {
private:
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        
        Node(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    // 自实现的简单哈希表
    class SimpleHashMap {
    private:
        static constexpr size_t BUCKET_SIZE = 1000;
        std::vector<std::list<std::pair<int, Node*>>> buckets;
        
        size_t hash(int key) const {
            return std::hash<int>{}(key) % BUCKET_SIZE;
        }
        
    public:
        SimpleHashMap() : buckets(BUCKET_SIZE) {}
        
        void put(int key, Node* node) {
            size_t index = hash(key);
            auto& bucket = buckets[index];
            
            for (auto& pair : bucket) {
                if (pair.first == key) {
                    pair.second = node;
                    return;
                }
            }
            
            bucket.emplace_back(key, node);
        }
        
        Node* get(int key) {
            size_t index = hash(key);
            auto& bucket = buckets[index];
            
            for (const auto& pair : bucket) {
                if (pair.first == key) {
                    return pair.second;
                }
            }
            
            return nullptr;
        }
        
        bool erase(int key) {
            size_t index = hash(key);
            auto& bucket = buckets[index];
            
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->first == key) {
                    bucket.erase(it);
                    return true;
                }
            }
            
            return false;
        }
    };
    
    int capacity_;
    Node* head_;  // 虚拟头节点
    Node* tail_;  // 虚拟尾节点
    SimpleHashMap hash_map_;
    
    void addToHead(Node* node) {
        node->prev = head_;
        node->next = head_->next;
        head_->next->prev = node;
        head_->next = node;
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }
    
    Node* removeTail() {
        Node* last = tail_->prev;
        removeNode(last);
        return last;
    }
    
public:
    LRUCache(int capacity) : capacity_(capacity) {
        head_ = new Node();
        tail_ = new Node();
        head_->next = tail_;
        tail_->prev = head_;
    }
    
    ~LRUCache() {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    int get(int key) {
        Node* node = hash_map_.get(key);
        if (!node) {
            return -1;
        }
        
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        Node* node = hash_map_.get(key);
        
        if (node) {
            // 更新现有节点
            node->value = value;
            moveToHead(node);
        } else {
            // 添加新节点
            Node* new_node = new Node(key, value);
            
            if (hash_map_.size() >= capacity_) {
                // 删除尾部节点
                Node* tail = removeTail();
                hash_map_.erase(tail->key);
                delete tail;
            }
            
            addToHead(new_node);
            hash_map_.put(key, new_node);
        }
    }
};
```

### 题目2：复杂树结构实现
**LeetCode 208. Implement Trie (Prefix Tree) (Medium)**
- **链接：** https://leetcode.com/problems/implement-trie-prefix-tree/
- **难度：** Medium
- **知识点：** 字典树、前缀匹配、字符串处理
- **描述：** 实现字典树(前缀树)，支持插入、搜索、前缀匹配操作
- **数据结构要求：**
  - 自实现树形结构
  - 高效的字符串存储和检索
  - 支持前缀查询

**高效实现版本：**
```cpp
class Trie {
private:
    struct TrieNode {
        static constexpr int ALPHABET_SIZE = 26;
        TrieNode* children[ALPHABET_SIZE];
        bool is_end_of_word;
        
        TrieNode() : is_end_of_word(false) {
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                children[i] = nullptr;
            }
        }
        
        ~TrieNode() {
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                delete children[i];
            }
        }
        
        // 禁止拷贝
        TrieNode(const TrieNode&) = delete;
        TrieNode& operator=(const TrieNode&) = delete;
    };
    
    TrieNode* root_;
    
    int charToIndex(char c) const {
        return c - 'a';
    }
    
    // 递归删除空节点优化内存
    bool deleteHelper(TrieNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            if (!node->is_end_of_word) {
                return false;  // 单词不存在
            }
            
            node->is_end_of_word = false;
            
            // 如果没有子节点，可以删除
            for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    return false;
                }
            }
            return true;  // 可以删除
        }
        
        int char_index = charToIndex(word[index]);
        TrieNode* child = node->children[char_index];
        
        if (!child) {
            return false;  // 单词不存在
        }
        
        bool should_delete_child = deleteHelper(child, word, index + 1);
        
        if (should_delete_child) {
            delete child;
            node->children[char_index] = nullptr;
            
            // 检查当前节点是否可以删除
            if (!node->is_end_of_word) {
                for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
                    if (node->children[i]) {
                        return false;
                    }
                }
                return true;  // 可以删除
            }
        }
        
        return false;
    }
    
public:
    Trie() {
        root_ = new TrieNode();
    }
    
    ~Trie() {
        delete root_;
    }
    
    // 禁止拷贝和移动（简化实现）
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    Trie(Trie&&) = delete;
    Trie& operator=(Trie&&) = delete;
    
    void insert(const std::string& word) {
        TrieNode* current = root_;
        
        for (char c : word) {
            int index = charToIndex(c);
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        
        current->is_end_of_word = true;
    }
    
    bool search(const std::string& word) const {
        TrieNode* current = root_;
        
        for (char c : word) {
            int index = charToIndex(c);
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        
        return current->is_end_of_word;
    }
    
    bool startsWith(const std::string& prefix) const {
        TrieNode* current = root_;
        
        for (char c : prefix) {
            int index = charToIndex(c);
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        
        return true;
    }
    
    // 扩展功能：删除单词
    void erase(const std::string& word) {
        deleteHelper(root_, word, 0);
    }
    
    // 扩展功能：获取所有以prefix开头的单词
    std::vector<std::string> getWordsWithPrefix(const std::string& prefix) const {
        std::vector<std::string> result;
        TrieNode* prefix_node = root_;
        
        // 找到前缀对应的节点
        for (char c : prefix) {
            int index = charToIndex(c);
            if (!prefix_node->children[index]) {
                return result;  // 前缀不存在
            }
            prefix_node = prefix_node->children[index];
        }
        
        // DFS收集所有单词
        std::string current_word = prefix;
        dfsCollectWords(prefix_node, current_word, result);
        
        return result;
    }
    
private:
    void dfsCollectWords(TrieNode* node, std::string& current_word, 
                        std::vector<std::string>& result) const {
        if (node->is_end_of_word) {
            result.push_back(current_word);
        }
        
        for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                current_word.push_back('a' + i);
                dfsCollectWords(node->children[i], current_word, result);
                current_word.pop_back();
            }
        }
    }
};
```

### 题目3：高级数据结构设计
**LeetCode 895. Maximum Frequency Stack (Hard)**
- **链接：** https://leetcode.com/problems/maximum-frequency-stack/
- **难度：** Hard
- **知识点：** 栈、哈希表、频率统计
- **描述：** 设计一个栈，pop操作返回频率最高的元素，相同频率返回最近的
- **数据结构要求：**
  - 自实现多级栈结构
  - 高效的频率统计
  - O(1)时间复杂度的push和pop

**创新实现：**
```cpp
class FreqStack {
private:
    // 自实现的动态数组栈
    template<typename T>
    class Stack {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;
        
        void grow() {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            T* new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T)));
            
            for (size_t i = 0; i < size_; ++i) {
                new (new_data + i) T(std::move(data_[i]));
                data_[i].~T();
            }
            
            std::free(data_);
            data_ = new_data;
            capacity_ = new_capacity;
        }
        
    public:
        Stack() : data_(nullptr), size_(0), capacity_(0) {}
        
        ~Stack() {
            clear();
            std::free(data_);
        }
        
        void push(const T& value) {
            if (size_ == capacity_) {
                grow();
            }
            new (data_ + size_) T(value);
            ++size_;
        }
        
        void push(T&& value) {
            if (size_ == capacity_) {
                grow();
            }
            new (data_ + size_) T(std::move(value));
            ++size_;
        }
        
        T pop() {
            if (size_ > 0) {
                --size_;
                T result = std::move(data_[size_]);
                data_[size_].~T();
                return result;
            }
            throw std::runtime_error("Stack is empty");
        }
        
        bool empty() const {
            return size_ == 0;
        }
        
        void clear() {
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~T();
            }
            size_ = 0;
        }
    };
    
    std::unordered_map<int, int> freq_;  // 元素 -> 频率
    std::unordered_map<int, Stack<int>> stacks_;  // 频率 -> 该频率的栈
    int max_freq_;
    
public:
    FreqStack() : max_freq_(0) {}
    
    void push(int x) {
        int f = ++freq_[x];  // 增加频率
        max_freq_ = std::max(max_freq_, f);
        stacks_[f].push(x);  // 添加到对应频率的栈
    }
    
    int pop() {
        if (max_freq_ == 0) {
            throw std::runtime_error("Stack is empty");
        }
        
        int x = stacks_[max_freq_].pop();  // 从最高频率栈弹出
        --freq_[x];  // 减少频率
        
        if (stacks_[max_freq_].empty()) {
            --max_freq_;  // 降低最大频率
        }
        
        return x;
    }
    
    // 扩展功能：获取当前最高频率
    int getMaxFreq() const {
        return max_freq_;
    }
    
    // 扩展功能：获取元素的当前频率
    int getFreq(int x) const {
        auto it = freq_.find(x);
        return it != freq_.end() ? it->second : 0;
    }
};
```

### 题目4：复合数据结构设计 (Hard)
**LeetCode 432. All O`one Data Structure (Hard)**
- **链接：** https://leetcode.com/problems/all-oone-data-structure/
- **难度：** Hard
- **知识点：** 双向链表、哈希表、计数器
- **描述：** 设计数据结构支持O(1)时间的inc、dec、getMaxKey、getMinKey操作
- **数据结构要求：**
  - 自实现双向链表
  - 复杂的哈希映射关系
  - 多个数据结构的协调工作

**完整实现：**
```cpp
class AllOne {
private:
    struct Node {
        int count;
        std::unordered_set<std::string> keys;
        Node* prev;
        Node* next;
        
        Node(int c) : count(c), prev(nullptr), next(nullptr) {}
    };
    
    Node* head_;  // 虚拟头节点，count最小
    Node* tail_;  // 虚拟尾节点，count最大
    std::unordered_map<std::string, Node*> key_to_node_;  // key -> node
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void insertAfter(Node* prev_node, Node* new_node) {
        new_node->next = prev_node->next;
        new_node->prev = prev_node;
        prev_node->next->prev = new_node;
        prev_node->next = new_node;
    }
    
    void insertBefore(Node* next_node, Node* new_node) {
        new_node->prev = next_node->prev;
        new_node->next = next_node;
        next_node->prev->next = new_node;
        next_node->prev = new_node;
    }
    
public:
    AllOne() {
        head_ = new Node(0);
        tail_ = new Node(INT_MAX);
        head_->next = tail_;
        tail_->prev = head_;
    }
    
    ~AllOne() {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void inc(const std::string& key) {
        if (key_to_node_.find(key) == key_to_node_.end()) {
            // 新key，count = 1
            if (head_->next->count != 1) {
                // 创建count=1的节点
                Node* new_node = new Node(1);
                insertAfter(head_, new_node);
            }
            head_->next->keys.insert(key);
            key_to_node_[key] = head_->next;
        } else {
            // 现有key，增加count
            Node* current_node = key_to_node_[key];
            int new_count = current_node->count + 1;
            
            // 找到或创建count+1的节点
            Node* next_node = current_node->next;
            if (next_node->count != new_count) {
                Node* new_node = new Node(new_count);
                insertAfter(current_node, new_node);
                next_node = new_node;
            }
            
            // 移动key
            next_node->keys.insert(key);
            key_to_node_[key] = next_node;
            
            // 从当前节点删除key
            current_node->keys.erase(key);
            if (current_node->keys.empty()) {
                removeNode(current_node);
                delete current_node;
            }
        }
    }
    
    void dec(const std::string& key) {
        if (key_to_node_.find(key) == key_to_node_.end()) {
            return;  // key不存在
        }
        
        Node* current_node = key_to_node_[key];
        int new_count = current_node->count - 1;
        
        if (new_count == 0) {
            // 删除key
            key_to_node_.erase(key);
        } else {
            // 找到或创建count-1的节点
            Node* prev_node = current_node->prev;
            if (prev_node->count != new_count) {
                Node* new_node = new Node(new_count);
                insertBefore(current_node, new_node);
                prev_node = new_node;
            }
            
            // 移动key
            prev_node->keys.insert(key);
            key_to_node_[key] = prev_node;
        }
        
        // 从当前节点删除key
        current_node->keys.erase(key);
        if (current_node->keys.empty()) {
            removeNode(current_node);
            delete current_node;
        }
    }
    
    std::string getMaxKey() const {
        if (tail_->prev == head_) {
            return "";  // 没有key
        }
        return *(tail_->prev->keys.begin());
    }
    
    std::string getMinKey() const {
        if (head_->next == tail_) {
            return "";  // 没有key
        }
        return *(head_->next->keys.begin());
    }
    
    // 扩展功能：获取所有count的key
    std::vector<std::string> getKeysWithCount(int count) const {
        std::vector<std::string> result;
        Node* current = head_->next;
        
        while (current != tail_) {
            if (current->count == count) {
                for (const auto& key : current->keys) {
                    result.push_back(key);
                }
                break;
            }
            current = current->next;
        }
        
        return result;
    }
};
```

## 数据结构实现要求

### 1. 内存管理
```cpp
// 正确的RAII实现
class MyContainer {
private:
    int* data_;
    size_t size_;
    
public:
    MyContainer() : data_(nullptr), size_(0) {}
    
    ~MyContainer() {
        delete[] data_;  // 确保释放内存
    }
    
    // 实现拷贝构造、移动构造等
    MyContainer(const MyContainer& other);
    MyContainer(MyContainer&& other) noexcept;
    MyContainer& operator=(const MyContainer& other);
    MyContainer& operator=(MyContainer&& other) noexcept;
};
```

### 2. 异常安全
```cpp
// 强异常安全保证
void MyVector::push_back(const T& value) {
    if (size_ == capacity_) {
        // 先分配新内存，再移动数据
        T* new_data = allocateNewMemory();
        try {
            moveElements(new_data);
        } catch (...) {
            delete[] new_data;  // 清理新分配的内存
            throw;  // 重新抛出异常
        }
        delete[] data_;
        data_ = new_data;
    }
    
    new (data_ + size_) T(value);
    ++size_;
}
```

### 3. 性能优化
```cpp
// 内存预分配策略
void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        size_t optimal_capacity = std::max(new_capacity, capacity_ * 2);
        reallocate(optimal_capacity);
    }
}

// 移动语义优化
void push_back(T&& value) {
    emplace_back(std::move(value));
}

template<typename... Args>
void emplace_back(Args&&... args) {
    if (size_ == capacity_) grow();
    new (data_ + size_) T(std::forward<Args>(args)...);
    ++size_;
}
```

## 学习目标检查

完成今天的算法题后，你应该能够：

1. ✅ **掌握基础数据结构**：动态数组、链表、栈、队列
2. ✅ **理解高级数据结构**：树、哈希表、复合结构
3. ✅ **实现内存管理**：RAII、异常安全、移动语义
4. ✅ **优化性能**：时间复杂度、空间复杂度、缓存友好
5. ✅ **设计接口**：STL风格接口、迭代器支持
6. ✅ **处理边界情况**：空容器、满容器、异常情况

## 提交要求

1. 每道题提供完整的数据结构实现
2. 包含详细的时间和空间复杂度分析
3. 提供充分的测试用例和边界情况测试
4. 对比STL实现，分析优缺点
5. 总结数据结构设计的最佳实践

## 数据结构实现检查清单

- [ ] 是否正确实现了内存管理(RAII)
- [ ] 是否提供了完整的拷贝/移动语义
- [ ] 是否考虑了异常安全性
- [ ] 是否实现了STL风格的接口
- [ ] 是否提供了迭代器支持
- [ ] 是否优化了性能关键路径
- [ ] 是否处理了所有边界情况
- [ ] 是否进行了充分的测试验证
