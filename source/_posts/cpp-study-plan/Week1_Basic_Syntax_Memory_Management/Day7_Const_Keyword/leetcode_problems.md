# 第7天算法题 - const关键字

## 今日算法题（4道 Medium/Hard 难度）

### 1. 删除链表的倒数第N个节点 (Remove Nth Node From End of List)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/remove-nth-node-from-end-of-list/  
**描述：** 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。  
**关键点：** const正确性、链表操作、双指针技术、边界处理、内存管理

### 2. 两两交换链表中的节点 (Swap Nodes in Pairs)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/swap-nodes-in-pairs/  
**描述：** 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。  
**关键点：** const正确性、链表操作、节点交换、指针操作、内存管理

### 3. 旋转链表 (Rotate List)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/rotate-list/  
**描述：** 给你一个链表的头节点 head，旋转链表，将链表每个节点向右移动 k 个位置。  
**关键点：** const正确性、链表操作、数学计算、边界处理、内存优化

### 4. 删除排序链表中的重复元素 II (Remove Duplicates from Sorted List II)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/  
**描述：** 给定一个已排序的链表的头 head，删除原始链表中所有重复数字的节点，只留下不同的数字。返回已排序的链表。  
**关键点：** const正确性、链表操作、重复处理、边界条件、内存管理

## 解题思路提示

### 题目1：删除链表的倒数第N个节点
**双指针思路：**
1. 使用两个指针，先让第一个指针走n+1步
2. 然后两个指针同时移动
3. 当第一个指针到达末尾时，第二个指针指向要删除节点的前一个
4. 删除节点并处理边界情况

**关键代码：**
```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* first = dummy;
    ListNode* second = dummy;
    
    // 先让first走n+1步
    for (int i = 0; i <= n; i++) {
        first = first->next;
    }
    
    // 然后两个指针同时移动
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    // 删除节点
    ListNode* toDelete = second->next;
    second->next = second->next->next;
    delete toDelete;  // 释放内存
    
    ListNode* result = dummy->next;
    delete dummy;  // 释放虚拟头节点
    return result;
}
```

### 题目2：两两交换链表中的节点
**迭代思路：**
1. 使用虚拟头节点简化边界处理
2. 维护三个指针：prev、first、second
3. 交换first和second节点
4. 更新指针继续下一对

**关键代码：**
```cpp
ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    
    while (prev->next && prev->next->next) {
        ListNode* first = prev->next;
        ListNode* second = prev->next->next;
        
        // 交换节点
        prev->next = second;
        first->next = second->next;
        second->next = first;
        
        // 更新prev指针
        prev = first;
    }
    
    ListNode* result = dummy->next;
    delete dummy;  // 释放虚拟头节点
    return result;
}
```

### 题目3：旋转链表
**思路：**
1. 先找到链表的长度和尾节点
2. 计算实际需要旋转的步数（k % length）
3. 将链表连接成环
4. 在合适位置断开环

**关键代码：**
```cpp
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) {
        return head;
    }
    
    // 计算链表长度并找到尾节点
    int length = 1;
    ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
        length++;
    }
    
    // 计算实际旋转步数
    k = k % length;
    if (k == 0) return head;
    
    // 将链表连接成环
    tail->next = head;
    
    // 找到新的尾节点
    for (int i = 0; i < length - k; i++) {
        tail = tail->next;
    }
    
    // 断开环
    ListNode* newHead = tail->next;
    tail->next = nullptr;
    
    return newHead;
}
```

### 题目4：删除排序链表中的重复元素 II
**思路：**
1. 使用虚拟头节点简化边界处理
2. 维护两个指针：prev和current
3. 当发现重复元素时，跳过所有重复元素
4. 更新连接关系

**关键代码：**
```cpp
ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    ListNode* current = head;
    
    while (current) {
        // 检查是否有重复
        if (current->next && current->val == current->next->val) {
            int duplicateVal = current->val;
            // 跳过所有重复元素
            while (current && current->val == duplicateVal) {
                ListNode* temp = current;
                current = current->next;
                delete temp;  // 释放内存
            }
            prev->next = current;
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    ListNode* result = dummy->next;
    delete dummy;  // 释放虚拟头节点
    return result;
}
```

## 今日学习重点

1. **const正确性**：确保代码的const正确性
2. **链表操作**：熟练进行链表的增删改查
3. **内存管理**：正确分配和释放内存
4. **边界处理**：处理空链表、单节点等边界情况
5. **指针操作**：掌握指针的移动和连接

## const正确性技巧

### 1. 函数参数使用const
```cpp
// 不修改参数的函数使用const
void printList(const ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
}

// 修改参数的函数不使用const
void modifyList(ListNode* head) {
    while (head) {
        head->val *= 2;
        head = head->next;
    }
}
```

### 2. 成员函数使用const
```cpp
class ListNode {
public:
    int val;
    ListNode* next;
    
    ListNode(int x) : val(x), next(nullptr) {}
    
    // const成员函数
    int getValue() const {
        return val;
    }
    
    // 非const成员函数
    void setValue(int newVal) {
        val = newVal;
    }
};
```

### 3. 返回值使用const
```cpp
// 返回const引用避免拷贝
const string& getName() const {
    return name;
}

// 返回const指针
const ListNode* getHead() const {
    return head;
}
```

## 内存管理技巧

### 1. RAII原则
```cpp
class ListManager {
private:
    ListNode* head;
    
public:
    ListManager() : head(nullptr) {}
    
    ~ListManager() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // 禁止拷贝
    ListManager(const ListManager&) = delete;
    ListManager& operator=(const ListManager&) = delete;
    
    // 允许移动
    ListManager(ListManager&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }
};
```

### 2. 智能指针使用
```cpp
// 使用unique_ptr管理单个节点
unique_ptr<ListNode> node = make_unique<ListNode>(42);

// 使用shared_ptr管理共享节点
shared_ptr<ListNode> sharedNode = make_shared<ListNode>(42);
```

### 3. 异常安全的内存管理
```cpp
ListNode* createList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    try {
        for (size_t i = 1; i < values.size(); i++) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
    } catch (...) {
        // 清理已分配的内存
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        throw;
    }
    
    return head;
}
```

## 常见错误与注意事项

1. **内存泄漏**：分配内存后忘记释放
2. **重复释放**：对同一块内存释放多次
3. **野指针**：释放内存后继续使用指针
4. **const正确性**：违反const约定
5. **边界条件**：没有处理空链表或单节点链表

## 性能优化技巧

1. **减少内存分配**：使用内存池或预分配
2. **避免不必要的拷贝**：使用引用和移动语义
3. **及时释放内存**：使用完后立即释放
4. **使用智能指针**：自动管理内存生命周期
5. **异常安全**：确保异常安全的内存管理

## 学习检查点

- [ ] 能够正确使用const关键字
- [ ] 掌握链表的基本操作
- [ ] 理解内存管理的基本技巧
- [ ] 了解const正确性的重要性
- [ ] 掌握异常安全的内存管理
- [ ] 了解现代C++的内存管理技术

## 扩展练习

1. 实现链表的归并排序
2. 实现链表的快速排序
3. 实现链表的去重操作
4. 实现链表的回文判断
5. 实现链表的相交检测
