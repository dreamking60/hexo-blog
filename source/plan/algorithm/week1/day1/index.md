---
title: 算法第1天：动态规划基础
date: 2025-01-27 10:00:00
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day1/
---

# 🧮 算法第1天：动态规划基础

## 学习目标
- 理解动态规划的基本思想和核心概念
- 掌握状态定义、状态转移、边界条件的分析方法
- 熟练解决经典的动态规划问题
- 学会优化DP空间复杂度

## 📚 动态规划核心概念

### 什么是动态规划？
动态规划（Dynamic Programming，简称DP）是一种通过把原问题分解为相对简单的子问题的方式求解复杂问题的方法。动态规划常常适用于有重叠子问题和最优子结构性质的问题。

### 动态规划三要素
1. **状态定义**：定义dp[i]表示什么
2. **状态转移**：dp[i]如何从dp[i-1]或其他状态推导
3. **边界条件**：初始状态和终止条件

### 动态规划解题步骤
1. 确定状态
2. 找到状态转移方程
3. 确定初始状态
4. 确定计算顺序
5. 优化空间复杂度（可选）

## 💻 经典题目解析

### 题目1：爬楼梯 (LeetCode 70)

**题目描述：**
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

**解题思路：**
- 状态定义：dp[i] 表示爬到第i阶楼梯的方法数
- 状态转移：dp[i] = dp[i-1] + dp[i-2]
- 边界条件：dp[1] = 1, dp[2] = 2

**代码实现：**
```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        // 方法1：使用数组
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
};

// 方法2：空间优化
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1;  // dp[i-2]
        int prev1 = 2;  // dp[i-1]
        
        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};
```

### 题目2：打家劫舍 (LeetCode 198)

**题目描述：**
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

**解题思路：**
- 状态定义：dp[i] 表示偷到第i间房屋时能偷到的最大金额
- 状态转移：dp[i] = max(dp[i-1], dp[i-2] + nums[i])
- 边界条件：dp[0] = nums[0], dp[1] = max(nums[0], nums[1])

**代码实现：**
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        
        return dp[n-1];
    }
};

// 空间优化版本
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
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

### 题目3：使用最小花费爬楼梯 (LeetCode 746)

**题目描述：**
数组的每个索引作为一个阶梯，第 i个阶梯对应着一个非负数的体力花费值 cost[i](索引从0开始)。每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。请找出达到楼层顶部的最低花费。

**解题思路：**
- 状态定义：dp[i] 表示到达第i阶楼梯的最小花费
- 状态转移：dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2])
- 边界条件：dp[0] = 0, dp[1] = 0

**代码实现：**
```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 0;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
        }
        
        return dp[n];
    }
};
```

## 🏋️ 练习题目

### 必做题
1. **[LeetCode 70. 爬楼梯](https://leetcode.cn/problems/climbing-stairs/)**
2. **[LeetCode 198. 打家劫舍](https://leetcode.cn/problems/house-robber/)**
3. **[LeetCode 746. 使用最小花费爬楼梯](https://leetcode.cn/problems/min-cost-climbing-stairs/)**

### 进阶题
4. **[LeetCode 213. 打家劫舍 II](https://leetcode.cn/problems/house-robber-ii/)** - 环形数组
5. **[LeetCode 337. 打家劫舍 III](https://leetcode.cn/problems/house-robber-iii/)** - 树形DP

### 挑战题
6. **[LeetCode 91. 解码方法](https://leetcode.cn/problems/decode-ways/)**
7. **[LeetCode 139. 单词拆分](https://leetcode.cn/problems/word-break/)**

## 📝 解题模板

### 一维DP模板
```cpp
// 1. 确定状态
// dp[i] 表示...

// 2. 状态转移方程
// dp[i] = ...

// 3. 边界条件
// dp[0] = ...
// dp[1] = ...

// 4. 计算顺序
for (int i = 2; i <= n; i++) {
    dp[i] = ...;
}

// 5. 返回结果
return dp[n];
```

### 空间优化模板
```cpp
// 当dp[i]只依赖于dp[i-1]和dp[i-2]时
int prev2 = ...;  // dp[i-2]
int prev1 = ...;  // dp[i-1]

for (int i = 2; i <= n; i++) {
    int curr = ...;  // dp[i]
    prev2 = prev1;
    prev1 = curr;
}

return prev1;
```

## 💡 学习技巧

### 1. 如何识别DP问题
- 问题可以分解为子问题
- 子问题之间有重叠
- 具有最优子结构性质
- 通常涉及"最值"、"方案数"、"可行性"等问题

### 2. 状态定义技巧
- 明确dp[i]表示什么
- 状态要包含所有必要信息
- 状态要能够推导出答案

### 3. 状态转移技巧
- 考虑所有可能的状态转移
- 注意边界条件
- 确保状态转移的正确性

### 4. 空间优化技巧
- 观察状态转移方程
- 只保留必要的状态
- 使用滚动数组或变量

## 🎯 今日总结

### 掌握内容
- ✅ 动态规划的基本概念和解题步骤
- ✅ 一维DP问题的解决方法
- ✅ 空间优化的技巧
- ✅ 经典DP问题的解题思路

### 明日预告
明天我们将学习动态规划进阶，包括：
- 背包问题（01背包、完全背包）
- 股票买卖问题
- 编辑距离问题
- 区间DP

[**继续学习：第2天 动态规划进阶** →](/plan/algorithm/week1/day2/)

---

**记住：动态规划的核心是状态定义和状态转移，多练习才能熟练掌握！** 💪
