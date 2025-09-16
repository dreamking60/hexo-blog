# 第4天算法题 - 指针基础

## 今日算法题（4道 Medium/Hard 难度）

### 1. 两数相加 (Add Two Numbers)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/add-two-numbers/  
**描述：** 给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。请你将两个数相加，并以相同形式返回一个表示和的链表。  
**关键点：** 链表操作、指针遍历、进位处理、边界条件

### 2. 删除链表的倒数第N个节点 (Remove Nth Node From End of List)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/remove-nth-node-from-end-of-list/  
**描述：** 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。  
**关键点：** 双指针技术、链表遍历、边界处理、指针操作

### 3. 合并两个有序链表 (Merge Two Sorted Lists)
**难度：** Easy (但用指针操作是重要练习)  
**链接：** https://leetcode.cn/problems/merge-two-sorted-lists/  
**描述：** 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。  
**关键点：** 指针操作、链表合并、递归思想、边界条件

### 4. 环形链表 II (Linked List Cycle II)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/linked-list-cycle-ii/  
**描述：** 给定一个链表，返回链表开始入环的第一个节点。如果链表无环，则返回 null。  
**关键点：** 快慢指针、Floyd判环算法、数学推导、指针操作

## 解题思路提示

### 题目1：两数相加
**指针遍历思路：**
1. 使用虚拟头节点简化边界处理
2. 同时遍历两个链表，处理对应位置的数字
3. 维护进位变量
4. 注意链表长度不同的情况
5. 最后可能还有进位需要处理

**关键代码：**
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    int carry = 0;
    
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        carry = sum / 10;
        current->next = new ListNode(sum % 10);
        current = current->next;
    }
    
    return dummy->next;
}
```

### 题目2：删除链表的倒数第N个节点
**双指针思路：**
1. 使用两个指针，先让第一个指针走n步
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
    second->next = second->next->next;
    
    return dummy->next;
}
```

### 题目3：合并两个有序链表
**递归思路：**
1. 比较两个链表头节点的值
2. 选择较小的节点作为新链表的头
3. 递归处理剩余部分
4. 处理边界条件（空链表）

**迭代思路：**
1. 使用虚拟头节点简化边界处理
2. 维护当前指针，比较两个链表的值
3. 将较小的节点连接到结果链表
4. 处理剩余节点

**关键代码：**
```cpp
// 递归版本
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// 迭代版本
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

### 题目4：环形链表 II
**Floyd判环算法：**
1. 使用快慢指针检测环
2. 如果快指针追上慢指针，说明有环
3. 找到环的入口点：将其中一个指针重置到头部
4. 两个指针同时移动，相遇点就是环的入口

**关键代码：**
```cpp
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // 检测环
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (slow != fast) return nullptr;  // 无环
    
    // 找环的入口
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}
```

## 今日学习重点

1. **链表操作**：掌握链表的基本操作和遍历
2. **指针技巧**：熟练使用指针进行链表操作
3. **双指针技术**：在链表问题中的应用
4. **边界处理**：处理空链表和特殊情况
5. **递归思想**：用递归解决链表问题

## 链表操作模板

### 链表节点定义
```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

### 链表遍历模板
```cpp
ListNode* current = head;
while (current != nullptr) {
    // 处理当前节点
    current = current->next;
}
```

### 双指针模板
```cpp
ListNode* slow = head;
ListNode* fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    // 处理逻辑
}
```

### 虚拟头节点模板
```cpp
ListNode* dummy = new ListNode(0);
dummy->next = head;
ListNode* current = dummy;
// 处理逻辑
return dummy->next;
```

## 常见错误与注意事项

1. **空指针解引用**：访问空指针导致程序崩溃
2. **内存泄漏**：创建节点后忘记释放
3. **边界条件**：没有处理空链表或单节点链表
4. **指针移动**：指针移动时机错误
5. **循环引用**：创建循环链表后无法正确释放

## 调试技巧

1. **画图理解**：画出链表结构帮助理解
2. **逐步跟踪**：跟踪指针的移动过程
3. **边界测试**：测试空链表、单节点等边界情况
4. **内存检查**：使用工具检查内存泄漏
5. **打印调试**：在关键位置打印指针值

## 性能考虑

1. **时间复杂度**：大多数链表操作是O(n)
2. **空间复杂度**：递归可能使用O(n)栈空间
3. **原地操作**：尽量使用原地算法减少空间使用
4. **指针操作**：指针操作比数组操作更灵活但需要小心

## 学习检查点

- [ ] 能够熟练进行链表的基本操作
- [ ] 掌握指针在链表中的应用
- [ ] 理解双指针技术在链表问题中的作用
- [ ] 能够处理各种边界条件
- [ ] 掌握递归和迭代两种方法
- [ ] 了解链表算法的性能特点

## 扩展练习

1. 实现链表的反转（递归和迭代版本）
2. 实现链表的排序（归并排序）
3. 实现链表的去重操作
4. 实现链表的回文判断
5. 实现链表的相交检测
