# 第27天：数据结构实现

## 学习目标
从零实现常用数据结构，深入理解其内部原理和实现细节，掌握高效数据结构的设计思想。

## 今日学习内容

### 1. 动态数组实现 (Vector)
**概念：** 自动扩容的连续内存数组，是最常用的容器之一。

```cpp
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

template<typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    
    void reallocate(size_t new_capacity) {
        T* new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T)));
        if (!new_data && new_capacity > 0) {
            throw std::bad_alloc();
        }
        
        // 移动构造现有元素
        for (size_t i = 0; i < size_; ++i) {
            try {
                new (new_data + i) T(std::move(data_[i]));
                data_[i].~T();
            } catch (...) {
                // 清理已构造的元素
                for (size_t j = 0; j < i; ++j) {
                    new_data[j].~T();
                }
                std::free(new_data);
                throw;
            }
        }
        
        std::free(data_);
        data_ = new_data;
        capacity_ = new_capacity;
    }
    
    void grow() {
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    
public:
    // 构造函数
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit Vector(size_t count) : data_(nullptr), size_(0), capacity_(0) {
        reserve(count);
        for (size_t i = 0; i < count; ++i) {
            emplace_back();
        }
    }
    
    Vector(size_t count, const T& value) : data_(nullptr), size_(0), capacity_(0) {
        reserve(count);
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    
    Vector(std::initializer_list<T> init) : data_(nullptr), size_(0), capacity_(0) {
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // 拷贝构造函数
    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; ++i) {
            push_back(other.data_[i]);
        }
    }
    
    // 移动构造函数
    Vector(Vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // 析构函数
    ~Vector() {
        clear();
        std::free(data_);
    }
    
    // 赋值操作符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }
    
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            std::free(data_);
            
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    // 元素访问
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    
    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }
    
    T* data() { return data_; }
    const T* data() const { return data_; }
    
    // 容量相关
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            reallocate(new_capacity);
        }
    }
    
    void shrink_to_fit() {
        if (size_ < capacity_) {
            reallocate(size_);
        }
    }
    
    // 修改操作
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }
    
    void push_back(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        new (data_ + size_) T(value);
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ == capacity_) {
            grow();
        }
        new (data_ + size_) T(std::move(value));
        ++size_;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            grow();
        }
        new (data_ + size_) T(std::forward<Args>(args)...);
        ++size_;
    }
    
    void pop_back() {
        if (size_ > 0) {
            --size_;
            data_[size_].~T();
        }
    }
    
    void resize(size_t new_size) {
        if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i) {
                data_[i].~T();
            }
        } else if (new_size > size_) {
            reserve(new_size);
            for (size_t i = size_; i < new_size; ++i) {
                new (data_ + i) T();
            }
        }
        size_ = new_size;
    }
    
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    
    // 迭代器
    class iterator {
    private:
        T* ptr_;
    public:
        iterator(T* ptr) : ptr_(ptr) {}
        
        T& operator*() { return *ptr_; }
        T* operator->() { return ptr_; }
        
        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator temp = *this; ++ptr_; return temp; }
        
        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator temp = *this; --ptr_; return temp; }
        
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
    };
    
    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }
    
    class const_iterator {
    private:
        const T* ptr_;
    public:
        const_iterator(const T* ptr) : ptr_(ptr) {}
        
        const T& operator*() const { return *ptr_; }
        const T* operator->() const { return ptr_; }
        
        const_iterator& operator++() { ++ptr_; return *this; }
        const_iterator operator++(int) { const_iterator temp = *this; ++ptr_; return temp; }
        
        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
    };
    
    const_iterator begin() const { return const_iterator(data_); }
    const_iterator end() const { return const_iterator(data_ + size_); }
    const_iterator cbegin() const { return const_iterator(data_); }
    const_iterator cend() const { return const_iterator(data_ + size_); }
};
```

### 2. 链表实现 (Linked List)
**概念：** 动态数据结构，元素通过指针连接，支持高效插入删除。

```cpp
template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename... Args>
        Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr) {}
    };
    
    Node* head_;
    Node* tail_;
    size_t size_;
    
public:
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    ~LinkedList() {
        clear();
    }
    
    // 拷贝构造函数
    LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (const auto& item : other) {
            push_back(item);
        }
    }
    
    // 移动构造函数
    LinkedList(LinkedList&& other) noexcept 
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    
    // 赋值操作符
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            LinkedList temp(other);
            swap(temp);
        }
        return *this;
    }
    
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // 容量
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    
    // 元素访问
    T& front() { return head_->data; }
    const T& front() const { return head_->data; }
    
    T& back() { return tail_->data; }
    const T& back() const { return tail_->data; }
    
    // 修改操作
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head_;
        head_ = new_node;
        if (!tail_) {
            tail_ = head_;
        }
        ++size_;
    }
    
    void push_front(T&& value) {
        Node* new_node = new Node(std::move(value));
        new_node->next = head_;
        head_ = new_node;
        if (!tail_) {
            tail_ = head_;
        }
        ++size_;
    }
    
    template<typename... Args>
    void emplace_front(Args&&... args) {
        Node* new_node = new Node(std::forward<Args>(args)...);
        new_node->next = head_;
        head_ = new_node;
        if (!tail_) {
            tail_ = head_;
        }
        ++size_;
    }
    
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (tail_) {
            tail_->next = new_node;
            tail_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++size_;
    }
    
    void push_back(T&& value) {
        Node* new_node = new Node(std::move(value));
        if (tail_) {
            tail_->next = new_node;
            tail_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++size_;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args) {
        Node* new_node = new Node(std::forward<Args>(args)...);
        if (tail_) {
            tail_->next = new_node;
            tail_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++size_;
    }
    
    void pop_front() {
        if (head_) {
            Node* old_head = head_;
            head_ = head_->next;
            if (!head_) {
                tail_ = nullptr;
            }
            delete old_head;
            --size_;
        }
    }
    
    void clear() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
        tail_ = nullptr;
        size_ = 0;
    }
    
    void swap(LinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }
    
    // 迭代器
    class iterator {
    private:
        Node* node_;
    public:
        iterator(Node* node) : node_(node) {}
        
        T& operator*() { return node_->data; }
        T* operator->() { return &node_->data; }
        
        iterator& operator++() { 
            if (node_) node_ = node_->next; 
            return *this; 
        }
        
        iterator operator++(int) { 
            iterator temp = *this; 
            if (node_) node_ = node_->next; 
            return temp; 
        }
        
        bool operator==(const iterator& other) const { return node_ == other.node_; }
        bool operator!=(const iterator& other) const { return node_ != other.node_; }
    };
    
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
    
    class const_iterator {
    private:
        const Node* node_;
    public:
        const_iterator(const Node* node) : node_(node) {}
        
        const T& operator*() const { return node_->data; }
        const T* operator->() const { return &node_->data; }
        
        const_iterator& operator++() { 
            if (node_) node_ = node_->next; 
            return *this; 
        }
        
        const_iterator operator++(int) { 
            const_iterator temp = *this; 
            if (node_) node_ = node_->next; 
            return temp; 
        }
        
        bool operator==(const const_iterator& other) const { return node_ == other.node_; }
        bool operator!=(const const_iterator& other) const { return node_ != other.node_; }
    };
    
    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const { return const_iterator(nullptr); }
    const_iterator cbegin() const { return const_iterator(head_); }
    const_iterator cend() const { return const_iterator(nullptr); }
};
```

### 3. 栈实现 (Stack)
**概念：** 后进先出(LIFO)的数据结构。

```cpp
template<typename T, typename Container = Vector<T>>
class Stack {
private:
    Container container_;
    
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    
    // 构造函数
    Stack() = default;
    
    explicit Stack(const Container& container) : container_(container) {}
    explicit Stack(Container&& container) : container_(std::move(container)) {}
    
    // 元素访问
    reference top() { return container_.back(); }
    const_reference top() const { return container_.back(); }
    
    // 容量
    bool empty() const { return container_.empty(); }
    size_type size() const { return container_.size(); }
    
    // 修改操作
    void push(const value_type& value) {
        container_.push_back(value);
    }
    
    void push(value_type&& value) {
        container_.push_back(std::move(value));
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        container_.emplace_back(std::forward<Args>(args)...);
    }
    
    void pop() {
        container_.pop_back();
    }
    
    void swap(Stack& other) noexcept {
        container_.swap(other.container_);
    }
    
    // 比较操作符
    bool operator==(const Stack& other) const {
        return container_ == other.container_;
    }
    
    bool operator!=(const Stack& other) const {
        return container_ != other.container_;
    }
};
```

### 4. 队列实现 (Queue)
**概念：** 先进先出(FIFO)的数据结构。

```cpp
template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename... Args>
        Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr) {}
    };
    
    Node* front_;
    Node* rear_;
    size_t size_;
    
public:
    Queue() : front_(nullptr), rear_(nullptr), size_(0) {}
    
    ~Queue() {
        clear();
    }
    
    // 拷贝构造函数
    Queue(const Queue& other) : front_(nullptr), rear_(nullptr), size_(0) {
        Node* current = other.front_;
        while (current) {
            push(current->data);
            current = current->next;
        }
    }
    
    // 移动构造函数
    Queue(Queue&& other) noexcept 
        : front_(other.front_), rear_(other.rear_), size_(other.size_) {
        other.front_ = nullptr;
        other.rear_ = nullptr;
        other.size_ = 0;
    }
    
    // 赋值操作符
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            Queue temp(other);
            swap(temp);
        }
        return *this;
    }
    
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            clear();
            front_ = other.front_;
            rear_ = other.rear_;
            size_ = other.size_;
            
            other.front_ = nullptr;
            other.rear_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // 元素访问
    T& front() { return front_->data; }
    const T& front() const { return front_->data; }
    
    T& back() { return rear_->data; }
    const T& back() const { return rear_->data; }
    
    // 容量
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    
    // 修改操作
    void push(const T& value) {
        Node* new_node = new Node(value);
        if (rear_) {
            rear_->next = new_node;
            rear_ = new_node;
        } else {
            front_ = rear_ = new_node;
        }
        ++size_;
    }
    
    void push(T&& value) {
        Node* new_node = new Node(std::move(value));
        if (rear_) {
            rear_->next = new_node;
            rear_ = new_node;
        } else {
            front_ = rear_ = new_node;
        }
        ++size_;
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        Node* new_node = new Node(std::forward<Args>(args)...);
        if (rear_) {
            rear_->next = new_node;
            rear_ = new_node;
        } else {
            front_ = rear_ = new_node;
        }
        ++size_;
    }
    
    void pop() {
        if (front_) {
            Node* old_front = front_;
            front_ = front_->next;
            if (!front_) {
                rear_ = nullptr;
            }
            delete old_front;
            --size_;
        }
    }
    
    void clear() {
        while (front_) {
            Node* temp = front_;
            front_ = front_->next;
            delete temp;
        }
        rear_ = nullptr;
        size_ = 0;
    }
    
    void swap(Queue& other) noexcept {
        std::swap(front_, other.front_);
        std::swap(rear_, other.rear_);
        std::swap(size_, other.size_);
    }
};
```

### 5. 二叉搜索树实现 (Binary Search Tree)
**概念：** 有序二叉树，支持高效的搜索、插入、删除操作。

```cpp
template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
        Node(T&& value) : data(std::move(value)), left(nullptr), right(nullptr) {}
    };
    
    Node* root_;
    size_t size_;
    
    Node* insert_recursive(Node* node, const T& value) {
        if (!node) {
            ++size_;
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insert_recursive(node->left, value);
        } else if (value > node->data) {
            node->right = insert_recursive(node->right, value);
        }
        // 相等的值不插入
        
        return node;
    }
    
    Node* find_min(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    Node* remove_recursive(Node* node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = remove_recursive(node->left, value);
        } else if (value > node->data) {
            node->right = remove_recursive(node->right, value);
        } else {
            // 找到要删除的节点
            --size_;
            
            if (!node->left && !node->right) {
                // 叶子节点
                delete node;
                return nullptr;
            } else if (!node->left) {
                // 只有右子树
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                // 只有左子树
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                // 有两个子树
                Node* successor = find_min(node->right);
                node->data = successor->data;
                node->right = remove_recursive(node->right, successor->data);
                ++size_; // 因为上面的递归调用会减少size_
            }
        }
        
        return node;
    }
    
    Node* find_recursive(Node* node, const T& value) const {
        if (!node || node->data == value) {
            return node;
        }
        
        if (value < node->data) {
            return find_recursive(node->left, value);
        } else {
            return find_recursive(node->right, value);
        }
    }
    
    void inorder_recursive(Node* node, Vector<T>& result) const {
        if (node) {
            inorder_recursive(node->left, result);
            result.push_back(node->data);
            inorder_recursive(node->right, result);
        }
    }
    
    void clear_recursive(Node* node) {
        if (node) {
            clear_recursive(node->left);
            clear_recursive(node->right);
            delete node;
        }
    }
    
    Node* copy_recursive(Node* node) {
        if (!node) return nullptr;
        
        Node* new_node = new Node(node->data);
        new_node->left = copy_recursive(node->left);
        new_node->right = copy_recursive(node->right);
        
        return new_node;
    }
    
public:
    BinarySearchTree() : root_(nullptr), size_(0) {}
    
    ~BinarySearchTree() {
        clear();
    }
    
    // 拷贝构造函数
    BinarySearchTree(const BinarySearchTree& other) : root_(nullptr), size_(other.size_) {
        root_ = copy_recursive(other.root_);
    }
    
    // 移动构造函数
    BinarySearchTree(BinarySearchTree&& other) noexcept 
        : root_(other.root_), size_(other.size_) {
        other.root_ = nullptr;
        other.size_ = 0;
    }
    
    // 赋值操作符
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            BinarySearchTree temp(other);
            swap(temp);
        }
        return *this;
    }
    
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            clear();
            root_ = other.root_;
            size_ = other.size_;
            
            other.root_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // 基本操作
    void insert(const T& value) {
        root_ = insert_recursive(root_, value);
    }
    
    void insert(T&& value) {
        // 为简化，这里直接调用const版本
        insert(value);
    }
    
    void remove(const T& value) {
        root_ = remove_recursive(root_, value);
    }
    
    bool contains(const T& value) const {
        return find_recursive(root_, value) != nullptr;
    }
    
    // 容量
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    
    // 遍历
    Vector<T> inorder() const {
        Vector<T> result;
        inorder_recursive(root_, result);
        return result;
    }
    
    void clear() {
        clear_recursive(root_);
        root_ = nullptr;
        size_ = 0;
    }
    
    void swap(BinarySearchTree& other) noexcept {
        std::swap(root_, other.root_);
        std::swap(size_, other.size_);
    }
};
```

### 6. 哈希表实现 (Hash Table)
**概念：** 基于哈希函数的键值对存储，平均O(1)时间复杂度。

```cpp
#include <functional>
#include <vector>
#include <list>

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
private:
    using KeyValue = std::pair<Key, Value>;
    using Bucket = std::list<KeyValue>;
    using BucketArray = Vector<Bucket>;
    
    BucketArray buckets_;
    size_t size_;
    Hash hasher_;
    
    static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
    static constexpr double MAX_LOAD_FACTOR = 0.75;
    
    size_t get_bucket_index(const Key& key) const {
        return hasher_(key) % buckets_.size();
    }
    
    void rehash() {
        if (buckets_.empty()) return;
        
        BucketArray old_buckets = std::move(buckets_);
        buckets_ = BucketArray(old_buckets.size() * 2);
        size_ = 0;
        
        for (auto& bucket : old_buckets) {
            for (auto& kv : bucket) {
                insert(std::move(kv.first), std::move(kv.second));
            }
        }
    }
    
    double load_factor() const {
        return buckets_.empty() ? 0.0 : static_cast<double>(size_) / buckets_.size();
    }
    
public:
    HashTable() : buckets_(DEFAULT_BUCKET_COUNT), size_(0) {}
    
    explicit HashTable(size_t bucket_count) 
        : buckets_(bucket_count > 0 ? bucket_count : DEFAULT_BUCKET_COUNT), size_(0) {}
    
    // 插入操作
    void insert(const Key& key, const Value& value) {
        if (load_factor() >= MAX_LOAD_FACTOR) {
            rehash();
        }
        
        size_t index = get_bucket_index(key);
        auto& bucket = buckets_[index];
        
        // 检查是否已存在
        for (auto& kv : bucket) {
            if (kv.first == key) {
                kv.second = value;  // 更新值
                return;
            }
        }
        
        // 插入新键值对
        bucket.emplace_back(key, value);
        ++size_;
    }
    
    void insert(Key&& key, Value&& value) {
        if (load_factor() >= MAX_LOAD_FACTOR) {
            rehash();
        }
        
        size_t index = get_bucket_index(key);
        auto& bucket = buckets_[index];
        
        // 检查是否已存在
        for (auto& kv : bucket) {
            if (kv.first == key) {
                kv.second = std::move(value);  // 更新值
                return;
            }
        }
        
        // 插入新键值对
        bucket.emplace_back(std::move(key), std::move(value));
        ++size_;
    }
    
    // 查找操作
    Value* find(const Key& key) {
        if (buckets_.empty()) return nullptr;
        
        size_t index = get_bucket_index(key);
        auto& bucket = buckets_[index];
        
        for (auto& kv : bucket) {
            if (kv.first == key) {
                return &kv.second;
            }
        }
        
        return nullptr;
    }
    
    const Value* find(const Key& key) const {
        if (buckets_.empty()) return nullptr;
        
        size_t index = get_bucket_index(key);
        const auto& bucket = buckets_[index];
        
        for (const auto& kv : bucket) {
            if (kv.first == key) {
                return &kv.second;
            }
        }
        
        return nullptr;
    }
    
    bool contains(const Key& key) const {
        return find(key) != nullptr;
    }
    
    // 删除操作
    bool remove(const Key& key) {
        if (buckets_.empty()) return false;
        
        size_t index = get_bucket_index(key);
        auto& bucket = buckets_[index];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        
        return false;
    }
    
    // 访问操作符
    Value& operator[](const Key& key) {
        Value* value = find(key);
        if (value) {
            return *value;
        }
        
        // 插入默认值
        insert(key, Value{});
        return *find(key);
    }
    
    // 容量
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_ ; }
    size_t bucket_count() const { return buckets_.size(); }
    
    void clear() {
        for (auto& bucket : buckets_) {
            bucket.clear();
        }
        size_ = 0;
    }
};
```

## 实践练习

### 练习1：性能对比测试
```cpp
// 比较自实现的数据结构与STL的性能差异
// 测试不同操作的时间复杂度
```

### 练习2：扩展功能实现
```cpp
// 为BST添加平衡功能（AVL或红黑树）
// 为哈希表添加更多哈希策略
```

### 练习3：内存优化
```cpp
// 实现内存池版本的数据结构
// 减少内存碎片和分配次数
```

## 重点总结

1. **动态数组**：连续内存、自动扩容、随机访问
2. **链表**：动态内存、高效插入删除、顺序访问
3. **栈**：LIFO、函数调用、表达式求值
4. **队列**：FIFO、任务调度、BFS
5. **二叉搜索树**：有序存储、对数时间复杂度
6. **哈希表**：常数时间复杂度、键值存储

## 设计原则

1. **异常安全**：保证强异常安全性
2. **RAII**：资源获取即初始化
3. **移动语义**：支持高效的对象移动
4. **迭代器**：提供统一的遍历接口
5. **模板设计**：支持泛型编程
6. **内存管理**：正确的内存分配和释放

## 注意事项

1. **内存泄漏**：确保所有分配的内存都被释放
2. **异常安全**：在异常情况下保持对象状态一致
3. **迭代器失效**：修改容器时注意迭代器失效
4. **线程安全**：考虑多线程环境下的安全性
5. **性能优化**：平衡时间复杂度和空间复杂度

## 拓展阅读

- 《数据结构与算法分析》
- 《STL源码剖析》
- 《Effective C++》
- 《C++标准库》
- 各种数据结构的学术论文
