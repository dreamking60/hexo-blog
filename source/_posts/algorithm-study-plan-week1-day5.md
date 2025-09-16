---
title: 算法学习计划 - 第5天：哈希表基础
date: 2025-01-27 10:06:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day5
    - Hash Table
    - Map
    - Two Sum
    - Sliding Window
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day5/
---

# 第5天：哈希表基础

## 学习目标
- 掌握哈希表的基本操作和特性
- 熟练解决两数之和、三数之和问题
- 理解字符串哈希和字符计数
- 学会滑动窗口+哈希表的组合技巧

## 哈希表基础概念

### 哈希表特点
- **查找效率**：O(1) 平均时间复杂度
- **空间换时间**：用额外空间换取查找速度
- **键值对存储**：通过键快速查找值
- **去重功能**：自动处理重复元素

### 哈希表常用操作
- `insert(key, value)`：插入键值对
- `find(key)`：查找键对应的值
- `erase(key)`：删除键值对
- `count(key)`：统计键的出现次数

### C++中的哈希表
- `unordered_map`：无序映射，基于哈希表
- `unordered_set`：无序集合，基于哈希表
- `map`：有序映射，基于红黑树
- `set`：有序集合，基于红黑树

## 今日重点题目

### 1. 两数之和 (Easy)
**题目链接：** [1. 两数之和](https://leetcode.cn/problems/two-sum/)

**题目描述：**
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target 的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

**解题思路：**
使用哈希表存储已遍历的元素和其索引，对于当前元素，查找target-nums[i]是否在哈希表中。

**代码实现：**
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numToIndex;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (numToIndex.find(complement) != numToIndex.end()) {
                return {numToIndex[complement], i};
            }
            numToIndex[nums[i]] = i;
        }
        
        return {};
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 2. 无重复字符的最长子串 (Medium)
**题目链接：** [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)

**题目描述：**
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

**解题思路：**
滑动窗口+哈希表，维护一个不包含重复字符的窗口，用哈希表记录字符在窗口中的位置。

**代码实现：**
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charToIndex;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (charToIndex.find(s[right]) != charToIndex.end() && 
                charToIndex[s[right]] >= left) {
                left = charToIndex[s[right]] + 1;
            }
            charToIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(min(m, n))，m是字符集大小

### 3. 字母异位词分组 (Medium)
**题目链接：** [49. 字母异位词分组](https://leetcode.cn/problems/group-anagrams/)

**题目描述：**
给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

字母异位词 是由重新排列字母得到的单词，所有源单词中的字母通常恰好只用一次。

**解题思路：**
将每个字符串排序后作为键，相同键的字符串归为一组。

**代码实现：**
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (const string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for (auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
};
```

**时间复杂度：** O(nk log k)，k是字符串平均长度  
**空间复杂度：** O(nk)

### 4. 最长连续序列 (Medium)
**题目链接：** [128. 最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/)

**题目描述：**
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

**解题思路：**
使用哈希表存储所有数字，对于每个数字，检查其连续序列的长度。

**代码实现：**
```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;
        
        for (int num : numSet) {
            // 只从序列的起始位置开始计算
            if (numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentLen = 1;
                
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum++;
                    currentLen++;
                }
                
                maxLen = max(maxLen, currentLen);
            }
        }
        
        return maxLen;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

## 滑动窗口+哈希表

### 滑动窗口模板
```cpp
int slidingWindow(string s) {
    unordered_map<char, int> window;
    int left = 0, right = 0;
    int result = 0;
    
    while (right < s.length()) {
        // 扩大窗口
        char c = s[right];
        window[c]++;
        right++;
        
        // 检查是否需要收缩窗口
        while (window needs shrink) {
            char d = s[left];
            window[d]--;
            left++;
        }
        
        // 更新结果
        result = max(result, right - left);
    }
    
    return result;
}
```

## 字符串哈希技巧

### 字符计数
```cpp
// 统计字符串中每个字符的出现次数
unordered_map<char, int> charCount;
for (char c : s) {
    charCount[c]++;
}
```

### 字符频率比较
```cpp
// 比较两个字符串的字符频率是否相同
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (char c : t) {
        count[c]--;
        if (count[c] < 0) return false;
    }
    return true;
}
```

## 扩展练习

### 5. 三数之和 (Medium)
**题目链接：** [15. 三数之和](https://leetcode.cn/problems/3sum/)

### 6. 四数之和 (Medium)
**题目链接：** [18. 四数之和](https://leetcode.cn/problems/4sum/)

### 7. 有效的字母异位词 (Easy)
**题目链接：** [242. 有效的字母异位词](https://leetcode.cn/problems/valid-anagram/)

### 8. 赎金信 (Easy)
**题目链接：** [383. 赎金信](https://leetcode.cn/problems/ransom-note/)

## 学习总结

### 哈希表解题要点
1. **键的选择**：选择合适的键类型和值
2. **查找优化**：利用哈希表O(1)查找特性
3. **去重处理**：利用哈希表自动去重
4. **空间权衡**：考虑空间复杂度的合理性

### 滑动窗口+哈希表
1. **窗口维护**：保持窗口内元素满足条件
2. **边界处理**：正确处理窗口的扩大和收缩
3. **状态更新**：及时更新哈希表中的状态
4. **结果计算**：在合适的时机计算最终结果

### 字符串哈希技巧
1. **字符计数**：统计字符频率
2. **模式匹配**：利用哈希表快速匹配
3. **去重处理**：处理重复字符问题
4. **排序优化**：利用排序简化比较

### 常见错误
1. 哈希表键类型选择错误
2. 滑动窗口边界处理不当
3. 字符串比较时忽略大小写
4. 内存泄漏（C++中）

### 今日收获
- 掌握了哈希表的基本应用
- 学会了滑动窗口+哈希表的组合
- 理解了字符串哈希的技巧
- 建立了哈希表解题的思维模式

## 明日预告
明天我们将学习哈希表进阶内容，包括双指针+哈希表、前缀和+哈希表等更复杂的应用。

[返回周计划](/plan/algorithm/week1/) | [上一题：树结构进阶](/plan/algorithm/week1/day4/) | [下一题：哈希表进阶](/plan/algorithm/week1/day6/)
