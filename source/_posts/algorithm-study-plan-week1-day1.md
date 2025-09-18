---
title: 算法学习计划 - 第1天:动态规划基础
date: 2025-09-16 10:02:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day1
    - DP
    - Dynamic Programming
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day1/
---

# 第1天：动态规划基础

## 学习目标
- 理解动态规划的基本思想
- 掌握状态定义、状态转移、边界条件的设计
- 熟练解决一维DP问题
- 学会空间复杂度优化技巧

## 动态规划核心概念

### 什么是动态规划？
动态规划（Dynamic Programming，简称DP）是一种通过把原问题分解为相对简单的子问题的方式求解复杂问题的方法。动态规划常常适用于有重叠子问题和最优子结构性质的问题。

### DP三要素
1. **状态定义**：dp[i] 表示什么
2. **状态转移**：dp[i] 如何从 dp[i-1] 或其他状态推导
3. **边界条件**：初始状态和终止条件

### DP解题步骤
1. 确定状态定义
2. 找出状态转移方程
3. 确定边界条件
4. 编写代码实现
5. 优化空间复杂度（可选）

## 今日重点题目

### 1. 爬楼梯 (Easy)
**题目链接：** [70. 爬楼梯](https://leetcode.cn/problems/climbing-stairs/)

**题目描述：**
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

**解题思路：**
- 状态定义：dp[i] 表示爬到第 i 阶楼梯的方法数
- 状态转移：dp[i] = dp[i-1] + dp[i-2]
- 边界条件：dp[1] = 1, dp[2] = 2

**代码实现：**
```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1, prev1 = 2;
        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(1)

### 2. 打家劫舍 (Medium)
**题目链接：** [198. 打家劫舍](https://leetcode.cn/problems/house-robber/)

**题目描述：**
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你不触动警报装置的情况下，一夜之内能够偷窃到的最高金额。

**解题思路：**
- 状态定义：dp[i] 表示偷窃到第 i 个房屋时的最大金额
- 状态转移：dp[i] = max(dp[i-1], dp[i-2] + nums[i])
- 边界条件：dp[0] = nums[0], dp[1] = max(nums[0], nums[1])

**代码实现：**
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        
        int prev2 = nums[0];
        int prev1 = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            int curr = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(1)

### 3. 最长递增子序列 (Medium)
**题目链接：** [300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)

**题目描述：**
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

**解题思路：**
- 状态定义：dp[i] 表示以 nums[i] 结尾的最长递增子序列长度
- 状态转移：dp[i] = max(dp[j] + 1) for all j < i and nums[j] < nums[i]
- 边界条件：dp[i] = 1 for all i

**代码实现：**
```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int result = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            result = max(result, dp[i]);
        }
        
        return result;
    }
};
```

**时间复杂度：** O(n²)  
**空间复杂度：** O(n)

### 4. 使用最小花费爬楼梯 (Easy)
**题目链接：** [746. 使用最小花费爬楼梯](https://leetcode.cn/problems/min-cost-climbing-stairs/)

**题目描述：**
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。

你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。

请你计算并返回达到楼梯顶部的最低花费。

**解题思路：**
- 状态定义：dp[i] 表示到达第 i 个台阶的最小花费
- 状态转移：dp[i] = min(dp[i-1], dp[i-2]) + cost[i]
- 边界条件：dp[0] = cost[0], dp[1] = cost[1]

**代码实现：**
```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int prev2 = cost[0];
        int prev1 = cost[1];
        
        for (int i = 2; i < n; i++) {
            int curr = min(prev1, prev2) + cost[i];
            prev2 = prev1;
            prev1 = curr;
        }
        
        return min(prev1, prev2);
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(1)

## 扩展练习

### 5. 斐波那契数 (Easy)
**题目链接：** [509. 斐波那契数](https://leetcode.cn/problems/fibonacci-number/)

### 6. 最大子数组和 (Easy)
**题目链接：** [53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

### 7. 买卖股票的最佳时机 (Easy)
**题目链接：** [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)

## 学习总结

### DP解题模板
```cpp
// 1. 确定状态定义
vector<int> dp(n);

// 2. 设置边界条件
dp[0] = ...;
dp[1] = ...;

// 3. 状态转移
for (int i = 2; i < n; i++) {
    dp[i] = ...; // 根据状态转移方程
}

// 4. 返回结果
return dp[n-1];
```

### 空间优化技巧
- 当状态转移只依赖前几个状态时，可以用变量代替数组
- 滚动数组：用几个变量轮流存储状态
- 原地DP：直接在原数组上修改

### 常见错误
1. 边界条件处理不当
2. 状态转移方程错误
3. 数组越界
4. 初始化不完整

### 今日收获
- 理解了DP的基本思想
- 掌握了状态定义的方法
- 学会了空间复杂度优化
- 建立了DP解题的思维模式

## 明日预告
明天我们将学习动态规划进阶内容，包括二维DP和背包问题，难度会有所提升，但解题思路会更加丰富。

[返回周计划](/plan/algorithm/week1/) | [下一题：动态规划进阶](/plan/algorithm/week1/day2/)
