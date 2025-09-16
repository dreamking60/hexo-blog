# 第6天算法题 - 动态内存分配

## 今日算法题（4道 Medium/Hard 难度）

### 1. 合并K个升序链表 (Merge k Sorted Lists)
**难度：** Hard  
**链接：** https://leetcode.cn/problems/merge-k-sorted-lists/  
**描述：** 给你一个链表数组，每个链表都已经按升序排列。请你将所有链表合并到一个升序链表中，返回合并后的链表。  
**关键点：** 动态内存管理、链表操作、分治算法、优先队列、内存优化

### 2. 复制带随机指针的链表 (Copy List with Random Pointer)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/copy-list-with-random-pointer/  
**描述：** 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random，该指针可以指向链表中的任何节点或空节点。构造这个链表的深拷贝。  
**关键点：** 动态内存分配、深拷贝、链表操作、哈希表、内存管理

### 3. 重排链表 (Reorder List)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/reorder-list/  
**描述：** 给定一个单链表 L 的头节点 head，单链表 L 表示为：L0 → L1 → … → Ln-1 → Ln。请将其重新排列为：L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …  
**关键点：** 动态内存管理、链表操作、快慢指针、链表反转、内存优化

### 4. 删除链表中的节点 (Delete Node in a Linked List)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/delete-node-in-a-linked-list/  
**描述：** 有一个单链表的头节点 head，想删除它其中的某个节点 node。给你一个需要删除的节点 node，你将无法访问第一个节点 head。  
**关键点：** 动态内存管理、链表操作、节点删除、内存释放、指针操作

## 解题思路提示

### 题目1：合并K个升序链表
**分治算法思路：**
1. 将k个链表分成两组
2. 递归合并每组
3. 合并两个已排序的链表
4. 使用动态内存管理优化

**优先队列思路：**
1. 使用优先队列存储所有链表的头节点
2. 每次取出最小的节点
3. 将下一个节点加入队列
4. 构建结果链表

**关键代码：**
```cpp
// 分治算法
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    return mergeKListsHelper(lists, 0, lists.size() - 1);
}

ListNode* mergeKListsHelper(vector<ListNode*>& lists, int left, int right) {
    if (left == right) return lists[left];
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    ListNode* leftList = mergeKListsHelper(lists, left, mid);
    ListNode* rightList = mergeKListsHelper(lists, mid + 1, right);
    
    return mergeTwoLists(leftList, rightList);
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    
    current->next = l1 ? l1 : l2;
    return dummy->next;
}
```

### 题目2：复制带随机指针的链表
**哈希表思路：**
1. 第一次遍历：创建所有新节点并建立映射
2. 第二次遍历：设置next和random指针
3. 使用动态内存管理

**关键代码：**
```cpp
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;
    
    unordered_map<Node*, Node*> nodeMap;
    Node* current = head;
    
    // 第一次遍历：创建所有新节点
    while (current) {
        nodeMap[current] = new Node(current->val);
        current = current->next;
    }
    
    // 第二次遍历：设置指针
    current = head;
    while (current) {
        Node* newNode = nodeMap[current];
        if (current->next) {
            newNode->next = nodeMap[current->next];
        }
        if (current->random) {
            newNode->random = nodeMap[current->random];
        }
        current = current->next;
    }
    
    return nodeMap[head];
}
```

### 题目3：重排链表
**思路：**
1. 找到链表中点
2. 反转后半部分
3. 交替合并两部分
4. 使用动态内存管理

**关键代码：**
```cpp
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    
    // 找到中点
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // 反转后半部分
    ListNode* second = reverseList(slow->next);
    slow->next = nullptr;
    
    // 交替合并
    ListNode* first = head;
    while (second) {
        ListNode* temp1 = first->next;
        ListNode* temp2 = second->next;
        
        first->next = second;
        second->next = temp1;
        
        first = temp1;
        second = temp2;
    }
}

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    
    while (current) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}
```

### 题目4：删除链表中的节点
**思路：**
1. 将下一个节点的值复制到当前节点
2. 删除下一个节点
3. 注意内存管理

**关键代码：**
```cpp
void deleteNode(ListNode* node) {
    if (!node || !node->next) return;
    
    // 将下一个节点的值复制到当前节点
    node->val = node->next->val;
    
    // 删除下一个节点
    ListNode* next = node->next;
    node->next = next->next;
    delete next;  // 释放内存
}
```

## 今日学习重点

1. **动态内存管理**：正确分配和释放内存
2. **链表操作**：熟练进行链表的增删改查
3. **内存优化**：减少不必要的内存分配
4. **异常安全**：确保异常安全的内存管理
5. **RAII原则**：资源获取即初始化

## 动态内存管理技巧

### 1. 智能指针使用
```cpp
// 使用unique_ptr管理单个对象
unique_ptr<ListNode> node = make_unique<ListNode>(val);

// 使用shared_ptr管理共享对象
shared_ptr<ListNode> sharedNode = make_shared<ListNode>(val);
```

### 2. 内存池技术
```cpp
class ListNodePool {
private:
    vector<ListNode> pool;
    size_t nextIndex;
    
public:
    ListNodePool(size_t size) : pool(size), nextIndex(0) {}
    
    ListNode* allocate(int val) {
        if (nextIndex >= pool.size()) {
            pool.resize(pool.size() * 2);
        }
        pool[nextIndex].val = val;
        pool[nextIndex].next = nullptr;
        return &pool[nextIndex++];
    }
};
```

### 3. 异常安全的内存管理
```cpp
class SafeList {
private:
    ListNode* head;
    
public:
    SafeList() : head(nullptr) {}
    
    ~SafeList() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // 异常安全的插入
    void insert(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }
};
```

## 常见错误与注意事项

1. **内存泄漏**：分配内存后忘记释放
2. **重复释放**：对同一块内存释放多次
3. **野指针**：释放内存后继续使用指针
4. **异常安全**：异常发生时内存没有正确释放
5. **内存越界**：访问超出分配范围的内存

## 性能优化技巧

1. **减少内存分配**：使用内存池或预分配
2. **避免不必要的拷贝**：使用引用和移动语义
3. **及时释放内存**：使用完后立即释放
4. **使用智能指针**：自动管理内存生命周期
5. **异常安全**：确保异常安全的内存管理

## 学习检查点

- [ ] 能够正确管理动态内存
- [ ] 掌握链表的基本操作
- [ ] 理解内存泄漏的原因和预防
- [ ] 了解RAII原则
- [ ] 掌握异常安全的内存管理
- [ ] 了解现代C++的内存管理技术

## 扩展练习

1. 实现链表的归并排序
2. 实现链表的快速排序
3. 实现链表的去重操作
4. 实现链表的回文判断
5. 实现链表的相交检测
