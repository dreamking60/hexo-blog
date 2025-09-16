# 第2天算法题 - 函数与作用域

## 今日算法题（4道 Medium/Hard 难度）

### 1. 合并两个有序链表 (Merge Two Sorted Lists)
**难度：** Easy (但用递归实现是Medium思维)  
**链接：** https://leetcode.cn/problems/merge-two-sorted-lists/  
**描述：** 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。  
**关键点：** 递归思想、链表操作、边界条件处理

### 2. 括号生成 (Generate Parentheses)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/generate-parentheses/  
**描述：** 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且有效的括号组合。  
**关键点：** 递归回溯、括号匹配、剪枝优化

### 3. 全排列 (Permutations)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/permutations/  
**描述：** 给定一个不含重复数字的数组 nums，返回其所有可能的全排列。你可以按任意顺序返回答案。  
**关键点：** 递归回溯、排列生成、状态标记

### 4. 子集 (Subsets)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/subsets/  
**描述：** 给你一个整数数组 nums，数组中的元素互不相同。返回该数组所有可能的子集（幂集）。解集不能包含重复的子集。你可以按任意顺序返回解集。  
**关键点：** 递归回溯、子集生成、位运算优化

## 解题思路提示

### 题目1：合并两个有序链表
**递归思路：**
- 比较两个链表头节点的值
- 选择较小的节点作为新链表的头
- 递归处理剩余部分
- 处理边界条件（空链表）

**迭代思路：**
- 使用虚拟头节点简化边界处理
- 维护当前指针，比较两个链表的值
- 将较小的节点连接到结果链表

### 题目2：括号生成
**递归回溯思路：**
- 使用两个计数器：left（左括号数）、right（右括号数）
- 递归条件：
  - 如果left < n，可以添加左括号
  - 如果right < left，可以添加右括号
- 当left == n && right == n时，找到一个解

### 题目3：全排列
**递归回溯思路：**
- 使用visited数组标记已使用的元素
- 递归函数参数：当前路径、剩余元素
- 终止条件：路径长度等于数组长度
- 回溯：恢复状态，尝试下一个选择

### 题目4：子集
**递归回溯思路：**
- 每个元素都有两种选择：选或不选
- 递归函数参数：当前位置、当前路径
- 终止条件：遍历完所有元素
- 位运算优化：用二进制数表示选择状态

## 今日学习重点

1. **递归思维**：理解递归的基本原理和适用场景
2. **回溯算法**：掌握回溯算法的模板和剪枝技巧
3. **链表操作**：熟练进行链表的遍历、插入、删除
4. **状态管理**：学会在递归中管理状态和回溯
5. **边界条件**：注意处理各种边界情况和特殊情况

## 代码模板

### 递归模板
```cpp
void recursiveFunction(参数) {
    // 终止条件
    if (终止条件) {
        处理结果;
        return;
    }
    
    // 递归处理
    for (所有可能的选择) {
        做选择;
        recursiveFunction(更新参数);
        撤销选择;  // 回溯
    }
}
```

### 链表递归模板
```cpp
ListNode* recursiveList(ListNode* head) {
    // 终止条件
    if (!head || !head->next) {
        return head;
    }
    
    // 递归处理
    ListNode* newHead = recursiveList(head->next);
    
    // 处理当前节点
    // ...
    
    return newHead;
}
```

### 回溯模板
```cpp
void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        
        path.push_back(nums[i]);
        used[i] = true;
        backtrack(nums, path, used);
        used[i] = false;
        path.pop_back();
    }
}
```

## 递归优化技巧

### 1. 记忆化递归
```cpp
unordered_map<int, int> memo;
int fibonacci(int n) {
    if (n <= 1) return n;
    if (memo.count(n)) return memo[n];
    memo[n] = fibonacci(n-1) + fibonacci(n-2);
    return memo[n];
}
```

### 2. 尾递归优化
```cpp
int factorialTail(int n, int acc = 1) {
    if (n <= 1) return acc;
    return factorialTail(n-1, n * acc);
}
```

### 3. 剪枝优化
```cpp
void backtrack(参数) {
    if (不满足条件) return;  // 剪枝
    
    // 继续递归...
}
```

## 常见错误与注意事项

1. **递归终止条件错误**：可能导致无限递归
2. **状态回溯不完整**：可能导致结果错误
3. **边界条件处理不当**：可能导致数组越界
4. **重复计算**：没有使用记忆化导致超时
5. **递归深度过大**：可能导致栈溢出

## 性能考虑

1. **时间复杂度**：分析递归的时间复杂度
2. **空间复杂度**：考虑递归栈的空间开销
3. **剪枝优化**：减少不必要的递归调用
4. **记忆化**：避免重复计算
5. **迭代转换**：将递归转换为迭代以提高性能

## 学习检查点

- [ ] 能够正确实现递归函数
- [ ] 理解递归的调用过程和栈的使用
- [ ] 掌握回溯算法的基本模板
- [ ] 能够处理递归中的状态管理
- [ ] 了解递归的性能特点和优化方法
- [ ] 能够将递归问题转换为迭代实现

## 扩展练习

1. 实现非递归版本的合并链表
2. 使用位运算优化子集生成
3. 实现全排列的去重版本
4. 解决N皇后问题（经典回溯问题）
5. 实现快速排序的递归版本
