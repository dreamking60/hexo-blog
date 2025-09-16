# 第1天算法题 - 基础语法与数据类型

## 今日算法题（4道 Medium/Hard 难度）

### 1. 两数相加 (Add Two Numbers)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/add-two-numbers/  
**描述：** 给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。请你将两个数相加，并以相同形式返回一个表示和的链表。  
**关键点：** 链表操作、进位处理、边界条件

### 2. 无重复字符的最长子串 (Longest Substring Without Repeating Characters)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/longest-substring-without-repeating-characters/  
**描述：** 给定一个字符串 s ，请你找出其中不含有重复字符的最长子串的长度。  
**关键点：** 滑动窗口、哈希表、字符串处理

### 3. 寻找两个正序数组的中位数 (Median of Two Sorted Arrays)
**难度：** Hard  
**链接：** https://leetcode.cn/problems/median-of-two-sorted-arrays/  
**描述：** 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。  
**关键点：** 二分查找、数组合并、中位数计算

### 4. 盛最多水的容器 (Container With Most Water)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/container-with-most-water/  
**描述：** 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i])。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。  
**关键点：** 双指针、贪心算法、面积计算

## 解题思路提示

### 题目1：两数相加
- 使用虚拟头节点简化边界处理
- 注意进位和链表长度不同的情况
- 最后可能还有进位需要处理

### 题目2：无重复字符的最长子串
- 使用滑动窗口技术
- 用哈希表记录字符最后出现的位置
- 当遇到重复字符时，移动左指针

### 题目3：寻找两个正序数组的中位数
- 将问题转化为寻找第k小的元素
- 使用二分查找在较短的数组上搜索
- 注意边界条件的处理

### 题目4：盛最多水的容器
- 使用双指针从两端向中间移动
- 每次移动高度较小的指针
- 记录过程中的最大面积

## 今日学习重点

1. **链表操作**：掌握链表的创建、遍历、插入、删除
2. **字符串处理**：熟悉字符串的各种操作和字符处理
3. **数组操作**：掌握数组的遍历、查找、排序
4. **双指针技术**：理解双指针在数组和字符串问题中的应用
5. **哈希表使用**：学会用哈希表优化查找和去重

## 代码模板

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

### 双指针模板
```cpp
int left = 0, right = n - 1;
while (left < right) {
    // 处理逻辑
    if (condition) {
        left++;
    } else {
        right--;
    }
}
```

### 滑动窗口模板
```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    // 扩展窗口
    while (window_needs_shrink) {
        // 收缩窗口
        left++;
    }
    // 更新结果
}
```

## 注意事项

1. 注意边界条件的处理
2. 考虑空输入和特殊情况
3. 注意整数溢出问题
4. 合理使用辅助数据结构
5. 代码要简洁易读，注释清晰
