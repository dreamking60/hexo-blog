---
title: 算法学习计划 - 第6天：哈希表进阶
date: 2025-01-27 10:07:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day6
    - Hash Table
    - Map
    - Two Pointers
    - Prefix Sum
    - LRU Cache
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day6/
---

# 第6天：哈希表进阶

## 学习目标
- 掌握双指针+哈希表的组合技巧
- 理解前缀和+哈希表的应用
- 学会设计类问题：LRU、LFU缓存
- 掌握字符串匹配和模式识别

## 双指针+哈希表

### 组合特点
- **双指针**：维护窗口或搜索范围
- **哈希表**：记录状态或计数
- **优势**：结合两种算法的优点
- **应用**：子数组、子字符串问题

### 解题模板
```cpp
int twoPointersWithHash(vector<int>& nums) {
    unordered_map<int, int> count;
    int left = 0, right = 0;
    int result = 0;
    
    while (right < nums.size()) {
        // 扩展右指针
        count[nums[right]]++;
        
        // 收缩左指针（如果需要）
        while (condition) {
            count[nums[left]]--;
            left++;
        }
        
        // 更新结果
        result = max(result, right - left + 1);
        right++;
    }
    
    return result;
}
```

## 今日重点题目

### 1. 三数之和 (Medium)
**题目链接：** [15. 三数之和](https://leetcode.cn/problems/3sum/)

**题目描述：**
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

**解题思路：**
排序+双指针，固定一个数，用双指针在剩余数组中找两数之和。

**代码实现：**
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 3) return result;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; i++) {
            // 跳过重复元素
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // 跳过重复元素
                    while (left < right && nums[left] == nums[left+1]) left++;
                    while (left < right && nums[right] == nums[right-1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return result;
    }
};
```

**时间复杂度：** O(n²)  
**空间复杂度：** O(1)

### 2. 和为K的子数组 (Medium)
**题目链接：** [560. 和为K的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)

**题目描述：**
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的连续子数组的个数。

**解题思路：**
前缀和+哈希表，记录前缀和的出现次数，对于当前前缀和，查找是否存在前缀和等于当前前缀和-k。

**代码实现：**
```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1; // 前缀和为0出现1次
        
        int prefixSum = 0, count = 0;
        
        for (int num : nums) {
            prefixSum += num;
            if (prefixSumCount.find(prefixSum - k) != prefixSumCount.end()) {
                count += prefixSumCount[prefixSum - k];
            }
            prefixSumCount[prefixSum]++;
        }
        
        return count;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 3. LRU缓存 (Medium)
**题目链接：** [146. LRU缓存](https://leetcode.cn/problems/lru-cache/)

**题目描述：**
请你设计并实现一个满足 LRU (最近最少使用) 缓存 约束的数据结构。

实现 LRUCache 类：
- LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
- int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
- void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最近最少使用的关键字。

**解题思路：**
双向链表+哈希表，双向链表维护访问顺序，哈希表快速查找节点。

**代码实现：**
```cpp
class LRUCache {
private:
    struct Node {
        int key, value;
        Node* prev, *next;
        Node(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    int capacity;
    Node* head, *tail;
    unordered_map<int, Node*> cache;
    
    void addNode(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }
    
    Node* popTail() {
        Node* last = tail->prev;
        removeNode(last);
        return last;
    }
    
public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            moveToHead(node);
            return node->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            Node* newNode = new Node(key, value);
            if (cache.size() >= capacity) {
                Node* tail = popTail();
                cache.erase(tail->key);
                delete tail;
            }
            cache[key] = newNode;
            addNode(newNode);
        }
    }
};
```

**时间复杂度：** O(1)  
**空间复杂度：** O(capacity)

### 4. 最小覆盖子串 (Hard)
**题目链接：** [76. 最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring/)

**题目描述：**
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

**解题思路：**
滑动窗口+哈希表，维护一个包含t中所有字符的窗口，记录最小窗口。

**代码实现：**
```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        
        // 统计t中每个字符的需要次数
        for (char c : t) need[c]++;
        
        int left = 0, right = 0;
        int valid = 0; // 窗口中满足need条件的字符个数
        int start = 0, len = INT_MAX;
        
        while (right < s.length()) {
            char c = s[right];
            right++;
            
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }
            
            // 收缩窗口
            while (valid == need.size()) {
                if (right - left < len) {
                    start = left;
                    len = right - left;
                }
                
                char d = s[left];
                left++;
                
                if (need.count(d)) {
                    if (window[d] == need[d]) {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};
```

**时间复杂度：** O(|s| + |t|)  
**空间复杂度：** O(|s| + |t|)

## 前缀和+哈希表

### 前缀和概念
前缀和是指数组中从开始位置到当前位置的所有元素的和。

### 前缀和公式
- `prefixSum[i] = prefixSum[i-1] + nums[i]`
- 子数组和：`sum(i, j) = prefixSum[j] - prefixSum[i-1]`

### 前缀和+哈希表模板
```cpp
int prefixSumWithHash(vector<int>& nums, int target) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1; // 前缀和为0出现1次
    
    int prefixSum = 0, count = 0;
    
    for (int num : nums) {
        prefixSum += num;
        if (prefixSumCount.find(prefixSum - target) != prefixSumCount.end()) {
            count += prefixSumCount[prefixSum - target];
        }
        prefixSumCount[prefixSum]++;
    }
    
    return count;
}
```

## 扩展练习

### 5. 四数之和 (Medium)
**题目链接：** [18. 四数之和](https://leetcode.cn/problems/4sum/)

### 6. 连续的子数组和 (Medium)
**题目链接：** [523. 连续的子数组和](https://leetcode.cn/problems/continuous-subarray-sum/)

### 7. 和为S的两个数字 (Easy)
**题目链接：** [剑指 Offer 57. 和为s的两个数字](https://leetcode.cn/problems/he-wei-sde-liang-ge-shu-zi-lcof/)

### 8. 无重复字符的最长子串 (Medium)
**题目链接：** [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)

## 学习总结

### 双指针+哈希表要点
1. **窗口维护**：保持窗口内元素满足条件
2. **状态记录**：用哈希表记录窗口状态
3. **边界处理**：正确处理指针移动
4. **去重处理**：避免重复结果

### 前缀和+哈希表要点
1. **前缀和计算**：正确计算前缀和
2. **哈希表记录**：记录前缀和出现次数
3. **目标查找**：查找目标前缀和
4. **边界初始化**：正确初始化哈希表

### 设计类问题要点
1. **数据结构选择**：选择合适的底层数据结构
2. **操作实现**：正确实现各种操作
3. **状态维护**：维护数据结构的正确状态
4. **边界处理**：处理各种边界情况

### 常见错误
1. 双指针移动条件错误
2. 前缀和计算错误
3. 哈希表键值类型错误
4. 设计类问题状态维护错误

### 今日收获
- 掌握了双指针+哈希表的组合技巧
- 理解了前缀和+哈希表的应用
- 学会了设计类问题的解法
- 建立了更复杂的哈希表思维

## 明日预告
明天我们将进行综合练习，结合DP、Tree、Map三种算法解决复杂问题，这是本周的总结和提升。

[返回周计划](/plan/algorithm/week1/) | [上一题：哈希表基础](/plan/algorithm/week1/day5/) | [下一题：综合练习](/plan/algorithm/week1/day7/)
