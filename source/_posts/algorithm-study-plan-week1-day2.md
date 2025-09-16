---
title: 算法学习计划 - 第2天：动态规划进阶
date: 2025-09-16 10:03:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day2
    - DP
    - Dynamic Programming
    - 2D DP
    - Knapsack
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day2/
---

# 第2天：动态规划进阶

## 学习目标
- 掌握二维DP问题的解题思路
- 理解背包问题的经典模型
- 学会状态压缩DP技巧
- 掌握区间DP基础概念

## 二维DP基础

### 二维DP特点
- 状态定义：dp[i][j] 表示某种状态
- 状态转移：通常涉及两个维度的状态转移
- 边界条件：需要处理第一行和第一列
- 空间复杂度：O(m×n)

### 二维DP解题模板
```cpp
// 1. 确定状态定义
vector<vector<int>> dp(m, vector<int>(n));

// 2. 设置边界条件
dp[0][0] = ...;
for (int i = 1; i < m; i++) dp[i][0] = ...;
for (int j = 1; j < n; j++) dp[0][j] = ...;

// 3. 状态转移
for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
        dp[i][j] = ...; // 根据状态转移方程
    }
}

// 4. 返回结果
return dp[m-1][n-1];
```

## 今日重点题目

### 1. 不同路径 (Medium)
**题目链接：** [62. 不同路径](https://leetcode.cn/problems/unique-paths/)

**题目描述：**
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 "Start" ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 "Finish" ）。

问总共有多少条不同的路径？

**解题思路：**
- 状态定义：dp[i][j] 表示从 (0,0) 到 (i,j) 的路径数
- 状态转移：dp[i][j] = dp[i-1][j] + dp[i][j-1]
- 边界条件：dp[0][j] = 1, dp[i][0] = 1

**代码实现：**
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
};
```

**空间优化版本：**
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j-1];
            }
        }
        
        return dp[n-1];
    }
};
```

**时间复杂度：** O(m×n)  
**空间复杂度：** O(n)

### 2. 最小路径和 (Medium)
**题目链接：** [64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)

**题目描述：**
给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

**解题思路：**
- 状态定义：dp[i][j] 表示从 (0,0) 到 (i,j) 的最小路径和
- 状态转移：dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
- 边界条件：dp[0][0] = grid[0][0]

**代码实现：**
```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        
        dp[0][0] = grid[0][0];
        
        // 初始化第一行
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        
        // 初始化第一列
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        
        // 状态转移
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        
        return dp[m-1][n-1];
    }
};
```

**时间复杂度：** O(m×n)  
**空间复杂度：** O(m×n)

### 3. 最长公共子序列 (Medium)
**题目链接：** [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)

**题目描述：**
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

**解题思路：**
- 状态定义：dp[i][j] 表示 text1[0:i] 和 text2[0:j] 的最长公共子序列长度
- 状态转移：
  - 如果 text1[i-1] == text2[j-1]：dp[i][j] = dp[i-1][j-1] + 1
  - 否则：dp[i][j] = max(dp[i-1][j], dp[i][j-1])
- 边界条件：dp[0][j] = 0, dp[i][0] = 0

**代码实现：**
```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[m][n];
    }
};
```

**时间复杂度：** O(m×n)  
**空间复杂度：** O(m×n)

### 4. 分割等和子集 (Medium)
**题目链接：** [416. 分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)

**题目描述：**
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

**解题思路：**
这是一个01背包问题的变种。
- 状态定义：dp[i][j] 表示前 i 个数字能否组成和为 j 的子集
- 状态转移：
  - 不选 nums[i-1]：dp[i][j] = dp[i-1][j]
  - 选 nums[i-1]：dp[i][j] = dp[i-1][j-nums[i-1]]
- 边界条件：dp[0][0] = true

**代码实现：**
```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        
        int target = sum / 2;
        int n = nums.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        
        dp[0][0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i-1][j];
                if (j >= nums[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j-nums[i-1]];
                }
            }
        }
        
        return dp[n][target];
    }
};
```

**空间优化版本：**
```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        
        return dp[target];
    }
};
```

**时间复杂度：** O(n×target)  
**空间复杂度：** O(target)

## 背包问题基础

### 01背包问题
- **问题描述**：有 n 个物品，每个物品有重量 w[i] 和价值 v[i]，背包容量为 W，求最大价值
- **状态定义**：dp[i][j] 表示前 i 个物品在容量为 j 的背包中的最大价值
- **状态转移**：dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i])

### 完全背包问题
- **问题描述**：每个物品可以无限次使用
- **状态转移**：dp[i][j] = max(dp[i-1][j], dp[i][j-w[i]] + v[i])

## 扩展练习

### 5. 编辑距离 (Hard)
**题目链接：** [72. 编辑距离](https://leetcode.cn/problems/edit-distance/)

### 6. 零钱兑换 (Medium)
**题目链接：** [322. 零钱兑换](https://leetcode.cn/problems/coin-change/)

### 7. 最长回文子序列 (Medium)
**题目链接：** [516. 最长回文子序列](https://leetcode.cn/problems/longest-palindromic-subsequence/)

## 学习总结

### 二维DP解题要点
1. **状态定义要清晰**：明确 dp[i][j] 表示什么
2. **边界条件要完整**：处理第一行和第一列
3. **状态转移要正确**：考虑所有可能的状态转移
4. **空间优化要合理**：根据状态转移特点进行优化

### 背包问题解题模板
```cpp
// 01背包
for (int i = 1; i <= n; i++) {
    for (int j = W; j >= w[i]; j--) {
        dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
    }
}

// 完全背包
for (int i = 1; i <= n; i++) {
    for (int j = w[i]; j <= W; j++) {
        dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
    }
}
```

### 常见错误
1. 边界条件处理不当
2. 状态转移方程错误
3. 空间优化时遍历顺序错误
4. 数组越界

### 今日收获
- 掌握了二维DP的解题思路
- 理解了背包问题的经典模型
- 学会了空间复杂度优化技巧
- 建立了更复杂的DP思维模式

## 明日预告
明天我们将学习树结构基础，包括二叉树遍历和各种树操作，这将是一个全新的算法领域。

[返回周计划](/plan/algorithm/week1/) | [上一题：动态规划基础](/plan/algorithm/week1/day1/) | [下一题：树结构基础](/plan/algorithm/week1/day3/)
