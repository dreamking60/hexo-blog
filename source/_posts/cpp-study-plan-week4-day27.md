---
title: C++ 学习计划 - 第27天：项目实战 - 数据结构实现
date: 2025-09-16 10:30:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week4
    - Day27
layout: page
menu_id: plan
permalink: /plan/week4/day27/
---

# 第27天：项目实战 - 数据结构实现

## 学习目标
通过实现常用的数据结构，综合运用前面学到的C++知识，掌握数据结构的设计原理和实现技巧。

## 学习资源链接

### 📚 数据结构教程
- [Data Structures and Algorithms in C++](https://www.amazon.com/Data-Structures-Algorithms-Michael-Goodrich/dp/1118771338) - C++数据结构教材
- [Introduction to Algorithms](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844) - 算法导论
- [GeeksforGeeks Data Structures](https://www.geeksforgeeks.org/data-structures/) - 数据结构在线教程
- [Visualgo](https://visualgo.net/) - 数据结构可视化工具

### 🎥 视频教程
- [Data Structures in C++](https://www.youtube.com/playlist?list=PLfqMhTWNBTe0b2nM6JHVCnAkhQRGiZMSJ) - C++数据结构视频教程
- [MIT 6.006 Introduction to Algorithms](https://www.youtube.com/playlist?list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb) - MIT算法课程
- [The Cherno Data Structures](https://www.youtube.com/results?search_query=the+cherno+data+structures) - 数据结构实现

### 📖 深入阅读
- [STL Source Code Analysis](https://www.amazon.com/STL-Source-Code-Analysis-Chinese/dp/B00CFKZH2E) - STL源码剖析
- [Effective STL](https://www.amazon.com/Effective-STL-Specific-Standard-Template/dp/0201749629) - 高效使用STL
- [Algorithm Design Manual](https://www.amazon.com/Algorithm-Design-Manual-Steven-Skiena/dp/1849967202) - 算法设计手册

### 🔧 开发工具
- [Valgrind](https://valgrind.org/) - 内存检查工具
- [Google Benchmark](https://github.com/google/benchmark) - 性能基准测试
- [Catch2](https://github.com/catchorg/Catch2) - 单元测试框架
- [Doxygen](https://www.doxygen.nl/) - 文档生成工具

## 项目实现

### 1. 动态数组 (Dynamic Array)

首先实现一个类似std::vector的动态数组，理解内存管理和容量扩展机制。

```cpp
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

template<typename T>
class DynamicArray {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    
    void reallocate(size_t new_capacity) {
        T* new_data = static_cast<T*>(std::aligned_alloc(alignof(T), sizeof(T) * new_capacity));
        
        if (!new_data) {
            throw std::bad_alloc();
        }
        
        // 移动或拷贝现有元素
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (std::is_nothrow_move_constructible_v<T>) {
                new (new_data + i) T(std::move(data_[i]));
            } else {
                new (new_data + i) T(data_[i]);
            }
            data_[i].~T();
        }
        
        std::free(data_);
        data_ = new_data;
        capacity_ = new_capacity;
    }
    
public:
    // 构造函数
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit DynamicArray(size_t initial_capacity) 
        : data_(static_cast<T*>(std::aligned_alloc(alignof(T), sizeof(T) * initial_capacity)))
        , size_(0)
        , capacity_(initial_capacity) {
        if (!data_) {
            throw std::bad_alloc();
        }
    }
    
    DynamicArray(std::initializer_list<T> init) 
        : DynamicArray(init.size()) {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // 拷贝构造函数
    DynamicArray(const DynamicArray& other) : DynamicArray(other.capacity_) {
        for (size_t i = 0; i < other.size_; ++i) {
            push_back(other.data_[i]);
        }
    }
    
    // 移动构造函数
    DynamicArray(DynamicArray&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // 析构函数
    ~DynamicArray() {
        clear();
        std::free(data_);
    }
    
    // 赋值运算符
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            clear();
            if (capacity_ < other.size_) {
                std::free(data_);
                capacity_ = other.capacity_;
                data_ = static_cast<T*>(std::aligned_alloc(alignof(T), sizeof(T) * capacity_));
            }
            for (size_t i = 0; i < other.size_; ++i) {
                push_back(other.data_[i]);
            }
        }
        return *this;
    }
    
    DynamicArray& operator=(DynamicArray&& other) noexcept {
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
    T& operator[](size_t index) {
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        return data_[index];
    }
    
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }
    
    // 容量相关
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    
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
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        new (data_ + size_) T(value);
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        new (data_ + size_) T(std::move(value));
        ++size_;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_capacity);
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
    
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }
    
    // 迭代器支持
    T* begin() { return data_; }
    const T* begin() const { return data_; }
    T* end() { return data_ + size_; }
    const T* end() const { return data_ + size_; }
};
```

### 2. 链表 (Linked List)

实现双向链表，支持高效的插入和删除操作。

```cpp
#include <memory>
#include <iterator>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;
        
        template<typename... Args>
        Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr), prev(nullptr) {}
    };
    
    std::unique_ptr<Node> head_;
    Node* tail_;
    size_t size_;
    
public:
    // 迭代器类
    class iterator {
    private:
        Node* current_;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        explicit iterator(Node* node) : current_(node) {}
        
        reference operator*() { return current_->data; }
        pointer operator->() { return &current_->data; }
        
        iterator& operator++() {
            current_ = current_->next.get();
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }
        
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        
        friend class LinkedList;
    };
    
    class const_iterator {
    private:
        const Node* current_;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        explicit const_iterator(const Node* node) : current_(node) {}
        const_iterator(const iterator& it) : current_(it.current_) {}
        
        reference operator*() const { return current_->data; }
        pointer operator->() const { return &current_->data; }
        
        const_iterator& operator++() {
            current_ = current_->next.get();
            return *this;
        }
        
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        const_iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }
        
        const_iterator operator--(int) {
            const_iterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const const_iterator& other) const {
            return current_ == other.current_;
        }
        
        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };
    
    // 构造函数
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    LinkedList(std::initializer_list<T> init) : LinkedList() {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // 拷贝构造函数
    LinkedList(const LinkedList& other) : LinkedList() {
        for (const auto& item : other) {
            push_back(item);
        }
    }
    
    // 移动构造函数
    LinkedList(LinkedList&& other) noexcept 
        : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_) {
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    
    // 赋值运算符
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            for (const auto& item : other) {
                push_back(item);
            }
        }
        return *this;
    }
    
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = std::move(other.head_);
            tail_ = other.tail_;
            size_ = other.size_;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // 元素访问
    T& front() { return head_->data; }
    const T& front() const { return head_->data; }
    T& back() { return tail_->data; }
    const T& back() const { return tail_->data; }
    
    // 容量
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    // 修改操作
    void push_front(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        Node* new_node_ptr = new_node.get();
        
        if (head_) {
            head_->prev = new_node_ptr;
            new_node->next = std::move(head_);
        } else {
            tail_ = new_node_ptr;
        }
        
        head_ = std::move(new_node);
        ++size_;
    }
    
    void push_front(T&& value) {
        auto new_node = std::make_unique<Node>(std::move(value));
        Node* new_node_ptr = new_node.get();
        
        if (head_) {
            head_->prev = new_node_ptr;
            new_node->next = std::move(head_);
        } else {
            tail_ = new_node_ptr;
        }
        
        head_ = std::move(new_node);
        ++size_;
    }
    
    void push_back(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        Node* new_node_ptr = new_node.get();
        
        if (tail_) {
            tail_->next = std::move(new_node);
            new_node_ptr->prev = tail_;
            tail_ = new_node_ptr;
        } else {
            head_ = std::move(new_node);
            tail_ = new_node_ptr;
        }
        
        ++size_;
    }
    
    void push_back(T&& value) {
        auto new_node = std::make_unique<Node>(std::move(value));
        Node* new_node_ptr = new_node.get();
        
        if (tail_) {
            tail_->next = std::move(new_node);
            new_node_ptr->prev = tail_;
            tail_ = new_node_ptr;
        } else {
            head_ = std::move(new_node);
            tail_ = new_node_ptr;
        }
        
        ++size_;
    }
    
    void pop_front() {
        if (head_) {
            if (head_->next) {
                head_->next->prev = nullptr;
                head_ = std::move(head_->next);
            } else {
                head_.reset();
                tail_ = nullptr;
            }
            --size_;
        }
    }
    
    void pop_back() {
        if (tail_) {
            if (tail_->prev) {
                tail_ = tail_->prev;
                tail_->next.reset();
            } else {
                head_.reset();
                tail_ = nullptr;
            }
            --size_;
        }
    }
    
    iterator insert(const_iterator pos, const T& value) {
        if (pos.current_ == nullptr) {
            push_back(value);
            return iterator(tail_);
        }
        
        if (pos.current_ == head_.get()) {
            push_front(value);
            return iterator(head_.get());
        }
        
        auto new_node = std::make_unique<Node>(value);
        Node* new_node_ptr = new_node.get();
        Node* prev_node = pos.current_->prev;
        
        new_node->prev = prev_node;
        new_node->next = std::move(prev_node->next);
        new_node->next->prev = new_node_ptr;
        prev_node->next = std::move(new_node);
        
        ++size_;
        return iterator(new_node_ptr);
    }
    
    iterator erase(const_iterator pos) {
        if (pos.current_ == nullptr) {
            return end();
        }
        
        Node* node_to_erase = const_cast<Node*>(pos.current_);
        Node* next_node = node_to_erase->next.get();
        
        if (node_to_erase->prev) {
            node_to_erase->prev->next = std::move(node_to_erase->next);
        } else {
            head_ = std::move(node_to_erase->next);
        }
        
        if (next_node) {
            next_node->prev = node_to_erase->prev;
        } else {
            tail_ = node_to_erase->prev;
        }
        
        --size_;
        return iterator(next_node);
    }
    
    void clear() {
        while (head_) {
            head_ = std::move(head_->next);
        }
        tail_ = nullptr;
        size_ = 0;
    }
    
    // 迭代器
    iterator begin() { return iterator(head_.get()); }
    const_iterator begin() const { return const_iterator(head_.get()); }
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }
};
```

### 3. 栈 (Stack)

基于动态数组实现栈结构。

```cpp
#include <stdexcept>

template<typename T>
class Stack {
private:
    DynamicArray<T> container_;
    
public:
    // 构造函数
    Stack() = default;
    Stack(std::initializer_list<T> init) : container_(init) {}
    
    // 元素访问
    T& top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return container_.back();
    }
    
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return container_.back();
    }
    
    // 容量
    bool empty() const {
        return container_.empty();
    }
    
    size_t size() const {
        return container_.size();
    }
    
    // 修改操作
    void push(const T& value) {
        container_.push_back(value);
    }
    
    void push(T&& value) {
        container_.push_back(std::move(value));
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        container_.emplace_back(std::forward<Args>(args)...);
    }
    
    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        container_.pop_back();
    }
    
    void clear() {
        container_.clear();
    }
    
    // 交换
    void swap(Stack& other) {
        std::swap(container_, other.container_);
    }
};
```

### 4. 队列 (Queue)

基于链表实现队列结构。

```cpp
template<typename T>
class Queue {
private:
    LinkedList<T> container_;
    
public:
    // 构造函数
    Queue() = default;
    Queue(std::initializer_list<T> init) : container_(init) {}
    
    // 元素访问
    T& front() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return container_.front();
    }
    
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return container_.front();
    }
    
    T& back() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return container_.back();
    }
    
    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return container_.back();
    }
    
    // 容量
    bool empty() const {
        return container_.empty();
    }
    
    size_t size() const {
        return container_.size();
    }
    
    // 修改操作
    void push(const T& value) {
        container_.push_back(value);
    }
    
    void push(T&& value) {
        container_.push_back(std::move(value));
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        container_.emplace_back(std::forward<Args>(args)...);
    }
    
    void pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        container_.pop_front();
    }
    
    void clear() {
        container_.clear();
    }
    
    // 交换
    void swap(Queue& other) {
        std::swap(container_, other.container_);
    }
};
```

### 5. 二叉搜索树 (Binary Search Tree)

实现支持基本操作的二叉搜索树。

```cpp
#include <memory>
#include <functional>
#include <queue>

template<typename T, typename Compare = std::less<T>>
class BinarySearchTree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;
        
        template<typename... Args>
        Node(Args&&... args) 
            : data(std::forward<Args>(args)...), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    std::unique_ptr<Node> root_;
    size_t size_;
    Compare comp_;
    
    Node* find_node(const T& value) const {
        Node* current = root_.get();
        while (current) {
            if (comp_(value, current->data)) {
                current = current->left.get();
            } else if (comp_(current->data, value)) {
                current = current->right.get();
            } else {
                return current;
            }
        }
        return nullptr;
    }
    
    Node* find_min(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }
    
    Node* find_max(Node* node) const {
        while (node && node->right) {
            node = node->right.get();
        }
        return node;
    }
    
    std::unique_ptr<Node> remove_node(std::unique_ptr<Node> node, const T& value) {
        if (!node) {
            return nullptr;
        }
        
        if (comp_(value, node->data)) {
            node->left = remove_node(std::move(node->left), value);
        } else if (comp_(node->data, value)) {
            node->right = remove_node(std::move(node->right), value);
        } else {
            // 找到要删除的节点
            if (!node->left) {
                auto right_child = std::move(node->right);
                if (right_child) {
                    right_child->parent = node->parent;
                }
                --size_;
                return right_child;
            } else if (!node->right) {
                auto left_child = std::move(node->left);
                if (left_child) {
                    left_child->parent = node->parent;
                }
                --size_;
                return left_child;
            } else {
                // 两个子节点都存在
                Node* successor = find_min(node->right.get());
                node->data = successor->data;
                node->right = remove_node(std::move(node->right), successor->data);
                ++size_; // 补偿remove_node中的减法
            }
        }
        
        return node;
    }
    
    void inorder_traversal(Node* node, std::function<void(const T&)> visit) const {
        if (node) {
            inorder_traversal(node->left.get(), visit);
            visit(node->data);
            inorder_traversal(node->right.get(), visit);
        }
    }
    
    void preorder_traversal(Node* node, std::function<void(const T&)> visit) const {
        if (node) {
            visit(node->data);
            preorder_traversal(node->left.get(), visit);
            preorder_traversal(node->right.get(), visit);
        }
    }
    
    void postorder_traversal(Node* node, std::function<void(const T&)> visit) const {
        if (node) {
            postorder_traversal(node->left.get(), visit);
            postorder_traversal(node->right.get(), visit);
            visit(node->data);
        }
    }
    
public:
    // 构造函数
    BinarySearchTree(const Compare& comp = Compare{}) : root_(nullptr), size_(0), comp_(comp) {}
    
    BinarySearchTree(std::initializer_list<T> init, const Compare& comp = Compare{}) 
        : BinarySearchTree(comp) {
        for (const auto& item : init) {
            insert(item);
        }
    }
    
    // 拷贝构造函数
    BinarySearchTree(const BinarySearchTree& other) : BinarySearchTree(other.comp_) {
        other.inorder([this](const T& value) {
            insert(value);
        });
    }
    
    // 移动构造函数
    BinarySearchTree(BinarySearchTree&& other) noexcept 
        : root_(std::move(other.root_)), size_(other.size_), comp_(std::move(other.comp_)) {
        other.size_ = 0;
    }
    
    // 赋值运算符
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            clear();
            comp_ = other.comp_;
            other.inorder([this](const T& value) {
                insert(value);
            });
        }
        return *this;
    }
    
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            clear();
            root_ = std::move(other.root_);
            size_ = other.size_;
            comp_ = std::move(other.comp_);
            other.size_ = 0;
        }
        return *this;
    }
    
    // 容量
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    // 修改操作
    bool insert(const T& value) {
        if (!root_) {
            root_ = std::make_unique<Node>(value);
            ++size_;
            return true;
        }
        
        Node* current = root_.get();
        Node* parent = nullptr;
        
        while (current) {
            parent = current;
            if (comp_(value, current->data)) {
                current = current->left.get();
            } else if (comp_(current->data, value)) {
                current = current->right.get();
            } else {
                return false; // 值已存在
            }
        }
        
        auto new_node = std::make_unique<Node>(value);
        new_node->parent = parent;
        
        if (comp_(value, parent->data)) {
            parent->left = std::move(new_node);
        } else {
            parent->right = std::move(new_node);
        }
        
        ++size_;
        return true;
    }
    
    bool insert(T&& value) {
        if (!root_) {
            root_ = std::make_unique<Node>(std::move(value));
            ++size_;
            return true;
        }
        
        Node* current = root_.get();
        Node* parent = nullptr;
        
        while (current) {
            parent = current;
            if (comp_(value, current->data)) {
                current = current->left.get();
            } else if (comp_(current->data, value)) {
                current = current->right.get();
            } else {
                return false; // 值已存在
            }
        }
        
        auto new_node = std::make_unique<Node>(std::move(value));
        new_node->parent = parent;
        
        if (comp_(value, parent->data)) {
            parent->left = std::move(new_node);
        } else {
            parent->right = std::move(new_node);
        }
        
        ++size_;
        return true;
    }
    
    bool remove(const T& value) {
        if (find_node(value)) {
            root_ = remove_node(std::move(root_), value);
            return true;
        }
        return false;
    }
    
    void clear() {
        root_.reset();
        size_ = 0;
    }
    
    // 查找操作
    bool contains(const T& value) const {
        return find_node(value) != nullptr;
    }
    
    bool find(const T& value) const {
        return contains(value);
    }
    
    // 遍历操作
    void inorder(std::function<void(const T&)> visit) const {
        inorder_traversal(root_.get(), visit);
    }
    
    void preorder(std::function<void(const T&)> visit) const {
        preorder_traversal(root_.get(), visit);
    }
    
    void postorder(std::function<void(const T&)> visit) const {
        postorder_traversal(root_.get(), visit);
    }
    
    void level_order(std::function<void(const T&)> visit) const {
        if (!root_) return;
        
        std::queue<Node*> queue;
        queue.push(root_.get());
        
        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();
            
            visit(current->data);
            
            if (current->left) {
                queue.push(current->left.get());
            }
            if (current->right) {
                queue.push(current->right.get());
            }
        }
    }
    
    // 获取最小/最大值
    const T* min() const {
        Node* min_node = find_min(root_.get());
        return min_node ? &min_node->data : nullptr;
    }
    
    const T* max() const {
        Node* max_node = find_max(root_.get());
        return max_node ? &max_node->data : nullptr;
    }
};
```

## 测试和使用示例

```cpp
#include <iostream>
#include <string>

void test_data_structures() {
    // 测试动态数组
    std::cout << "=== Testing DynamicArray ===" << std::endl;
    DynamicArray<int> arr{1, 2, 3, 4, 5};
    arr.push_back(6);
    
    std::cout << "Array contents: ";
    for (const auto& item : arr) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 测试链表
    std::cout << "\n=== Testing LinkedList ===" << std::endl;
    LinkedList<std::string> list{"hello", "world", "cpp"};
    list.push_front("modern");
    list.push_back("programming");
    
    std::cout << "List contents: ";
    for (const auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 测试栈
    std::cout << "\n=== Testing Stack ===" << std::endl;
    Stack<int> stack{1, 2, 3};
    stack.push(4);
    stack.push(5);
    
    std::cout << "Stack contents (top to bottom): ";
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
    
    // 测试队列
    std::cout << "\n=== Testing Queue ===" << std::endl;
    Queue<char> queue{'a', 'b', 'c'};
    queue.push('d');
    queue.push('e');
    
    std::cout << "Queue contents (front to back): ";
    while (!queue.empty()) {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;
    
    // 测试二叉搜索树
    std::cout << "\n=== Testing BinarySearchTree ===" << std::endl;
    BinarySearchTree<int> bst{5, 3, 7, 1, 9, 2, 8};
    
    std::cout << "BST inorder traversal: ";
    bst.inorder([](const int& value) {
        std::cout << value << " ";
    });
    std::cout << std::endl;
    
    std::cout << "BST level order traversal: ";
    bst.level_order([](const int& value) {
        std::cout << value << " ";
    });
    std::cout << std::endl;
    
    std::cout << "Contains 7: " << bst.contains(7) << std::endl;
    std::cout << "Contains 10: " << bst.contains(10) << std::endl;
    
    if (auto min_val = bst.min()) {
        std::cout << "Minimum value: " << *min_val << std::endl;
    }
    if (auto max_val = bst.max()) {
        std::cout << "Maximum value: " << *max_val << std::endl;
    }
}

int main() {
    test_data_structures();
    return 0;
}
```

## 实践练习

### 练习1：性能测试
为每个数据结构编写性能测试：
- 插入操作的时间复杂度测试
- 查找操作的效率比较
- 内存使用情况分析

### 练习2：扩展功能
为数据结构添加更多功能：
- 动态数组的shrink_to_fit优化
- 链表的reverse操作
- BST的平衡检查和自平衡

### 练习3：异常安全
确保所有数据结构都是异常安全的：
- 强异常安全保证
- 资源管理的RAII
- 异常情况下的状态一致性

### 练习4：泛型优化
使用现代C++特性优化实现：
- 完美转发
- 移动语义优化
- constexpr支持

## 今日总结
通过实现基本数据结构，你应该掌握：
1. 内存管理和资源所有权的最佳实践
2. 迭代器设计模式和STL兼容性
3. 模板编程和泛型设计技巧
4. 异常安全和错误处理策略
5. 现代C++特性在数据结构中的应用

## 明天预告
明天是本课程的最后一天，我们将进行综合项目实战，设计和实现一个小型系统，综合运用四周来学到的所有知识。

[返回第四周](/plan/week4/) | [上一天：第26天](/plan/week4/day26/) | [下一天：第28天](/plan/week4/day28/)
