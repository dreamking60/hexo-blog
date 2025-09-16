# 第5天算法题 - 引用

## 今日算法题（4道 Medium/Hard 难度）

### 1. 反转链表 (Reverse Linked List)
**难度：** Easy (但用引用优化是重要练习)  
**链接：** https://leetcode.cn/problems/reverse-linked-list/  
**描述：** 给你单链表的头节点 head，请你反转链表，并返回反转后的链表。  
**关键点：** 引用优化、链表操作、迭代和递归、指针操作

### 2. 两两交换链表中的节点 (Swap Nodes in Pairs)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/swap-nodes-in-pairs/  
**描述：** 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。  
**关键点：** 引用操作、链表交换、边界处理、指针操作

### 3. 旋转链表 (Rotate List)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/rotate-list/  
**描述：** 给你一个链表的头节点 head，旋转链表，将链表每个节点向右移动 k 个位置。  
**关键点：** 引用优化、链表旋转、数学计算、边界处理

### 4. 删除排序链表中的重复元素 II (Remove Duplicates from Sorted List II)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/  
**描述：** 给定一个已排序的链表的头 head，删除原始链表中所有重复数字的节点，只留下不同的数字。返回已排序的链表。  
**关键点：** 引用操作、链表删除、重复处理、边界条件

## 解题思路提示

### 题目1：反转链表
**迭代思路：**
1. 使用三个指针：prev、current、next
2. 逐个反转节点之间的连接
3. 注意边界条件和指针更新顺序

**递归思路：**
1. 递归到链表末尾
2. 从后往前反转连接
3. 返回新的头节点

**关键代码：**
```cpp
// 迭代版本
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    
    while (current != nullptr) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

// 递归版本
ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return newHead;
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
    
    return dummy->next;
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
                delete temp;
            }
            prev->next = current;
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    return dummy->next;
}
```

## 今日学习重点

1. **引用优化**：使用引用减少不必要的拷贝
2. **链表操作**：熟练进行链表的增删改查
3. **指针操作**：掌握指针的移动和连接
4. **边界处理**：处理空链表、单节点等边界情况
5. **内存管理**：正确分配和释放内存

## 引用优化技巧

### 1. 函数参数使用引用
```cpp
// 避免拷贝大对象
void processList(const vector<int>& list) {
    // 使用常量引用避免拷贝
}

// 修改原对象
void modifyList(vector<int>& list) {
    // 使用引用修改原对象
}
```

### 2. 返回引用
```cpp
// 返回引用避免拷贝
const string& getName() const {
    return name;
}

// 链式操作
MyClass& setValue(int val) {
    this->val = val;
    return *this;
}
```

### 3. 引用成员变量
```cpp
class MyClass {
private:
    const string& name;  // 引用成员变量
public:
    MyClass(const string& n) : name(n) {}
};
```

## 链表操作模板

### 虚拟头节点模板
```cpp
ListNode* dummy = new ListNode(0);
dummy->next = head;
ListNode* current = dummy;
// 处理逻辑
return dummy->next;
```

### 链表遍历模板
```cpp
ListNode* current = head;
while (current) {
    // 处理当前节点
    current = current->next;
}
```

### 链表删除模板
```cpp
ListNode* prev = dummy;
ListNode* current = head;
while (current) {
    if (需要删除) {
        prev->next = current->next;
        delete current;
        current = prev->next;
    } else {
        prev = current;
        current = current->next;
    }
}
```

## 常见错误与注意事项

1. **空指针解引用**：访问空指针导致程序崩溃
2. **内存泄漏**：创建节点后忘记释放
3. **指针丢失**：修改指针前没有保存必要信息
4. **边界条件**：没有处理空链表或单节点链表
5. **引用绑定**：引用绑定到局部变量

## 调试技巧

1. **画图理解**：画出链表结构帮助理解
2. **逐步跟踪**：跟踪指针的移动过程
3. **边界测试**：测试各种边界情况
4. **内存检查**：使用工具检查内存泄漏
5. **打印调试**：在关键位置打印指针值

## 性能优化

1. **引用传参**：避免不必要的拷贝
2. **原地操作**：尽量使用原地算法
3. **减少分配**：减少动态内存分配
4. **缓存友好**：考虑内存局部性
5. **算法选择**：选择合适的时间复杂度

## 学习检查点

- [ ] 能够使用引用优化函数参数和返回值
- [ ] 掌握链表的基本操作和遍历
- [ ] 理解指针在链表中的重要作用
- [ ] 能够处理各种边界条件
- [ ] 掌握内存管理的基本技巧
- [ ] 了解引用和指针的区别和适用场景

## 扩展练习

1. 实现链表的归并排序
2. 实现链表的快速排序
3. 实现链表的去重操作
4. 实现链表的回文判断
5. 实现链表的相交检测
