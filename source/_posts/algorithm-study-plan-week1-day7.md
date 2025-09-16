---
title: 算法学习计划 - 第7天：综合练习
date: 2025-09-16 10:08:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day7
    - Comprehensive
    - DP
    - Tree
    - Map
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day7/
---

# 第7天：综合练习

## 学习目标
- 综合运用DP、Tree、Map三种算法
- 解决复杂的综合问题
- 提升算法思维和解题能力
- 巩固本周所学知识

## 综合练习策略

### 解题思路
1. **问题分析**：仔细分析题目要求
2. **算法选择**：确定使用哪种或哪几种算法
3. **组合应用**：将不同算法有机结合
4. **优化改进**：考虑时间和空间复杂度优化

### 常见组合模式
- **DP + Tree**：树形DP问题
- **Tree + Map**：树遍历+哈希表记录
- **DP + Map**：状态压缩+哈希表优化
- **多种算法**：分步骤使用不同算法

## 今日重点题目

### 1. 打家劫舍 III (Medium)
**题目链接：** [337. 打家劫舍 III](https://leetcode.cn/problems/house-robber-iii/)

**题目描述：**
小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。

除了 root 之外，每栋房子有且只有一个"父"房子与之相连。一番侦察之后，聪明的小偷意识到"这个地方的所有房屋的排列类似于一棵二叉树"。 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。

给定二叉树的 root 。返回 在不触动警报的情况下，小偷能够盗取的最高金额。

**解题思路：**
树形DP，每个节点有两种状态：偷或不偷。使用后序遍历，从叶子节点开始计算。

**代码实现：**
```cpp
class Solution {
public:
    int rob(TreeNode* root) {
        auto result = robHelper(root);
        return max(result.first, result.second);
    }
    
private:
    // 返回 {不偷当前节点的最大金额, 偷当前节点的最大金额}
    pair<int, int> robHelper(TreeNode* root) {
        if (!root) return {0, 0};
        
        auto left = robHelper(root->left);
        auto right = robHelper(root->right);
        
        // 不偷当前节点：左右子树可以偷或不偷
        int notRob = max(left.first, left.second) + max(right.first, right.second);
        
        // 偷当前节点：左右子树都不能偷
        int rob = root->val + left.first + right.first;
        
        return {notRob, rob};
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 2. 从前序与中序遍历序列构造二叉树 (Medium)
**题目链接：** [105. 从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

**题目描述：**
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

**解题思路：**
递归构建，使用哈希表记录中序遍历中每个值的位置，提高查找效率。

**代码实现：**
```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return buildTreeHelper(preorder, 0, preorder.size() - 1,
                              inorder, 0, inorder.size() - 1, inorderMap);
    }
    
private:
    TreeNode* buildTreeHelper(vector<int>& preorder, int preStart, int preEnd,
                             vector<int>& inorder, int inStart, int inEnd,
                             unordered_map<int, int>& inorderMap) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;
        
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);
        
        int rootIndex = inorderMap[rootVal];
        int leftSize = rootIndex - inStart;
        
        root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSize,
                                   inorder, inStart, rootIndex - 1, inorderMap);
        root->right = buildTreeHelper(preorder, preStart + leftSize + 1, preEnd,
                                    inorder, rootIndex + 1, inEnd, inorderMap);
        
        return root;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 3. 单词拆分 (Medium)
**题目链接：** [139. 单词拆分](https://leetcode.cn/problems/word-break/)

**题目描述：**
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

**解题思路：**
DP + 哈希表，dp[i]表示前i个字符能否被拆分，使用哈希表快速查找单词。

**代码实现：**
```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
```

**时间复杂度：** O(n²)  
**空间复杂度：** O(n)

### 4. 课程表 (Medium)
**题目链接：** [207. 课程表](https://leetcode.cn/problems/course-schedule/)

**题目描述：**
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程 bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

**解题思路：**
拓扑排序，使用BFS+哈希表记录入度，检测是否存在环。

**代码实现：**
```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        // 构建图和入度
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            inDegree[edge[0]]++;
        }
        
        // BFS拓扑排序
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            count++;
            
            for (int next : graph[course]) {
                inDegree[next]--;
                if (inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return count == numCourses;
    }
};
```

**时间复杂度：** O(V + E)  
**空间复杂度：** O(V + E)

## 综合练习题目

### 5. 最长递增子序列 (Medium)
**题目链接：** [300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)

### 6. 二叉树的最近公共祖先 (Medium)
**题目链接：** [236. 二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/)

### 7. 无重复字符的最长子串 (Medium)
**题目链接：** [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)

### 8. 三数之和 (Medium)
**题目链接：** [15. 三数之和](https://leetcode.cn/problems/3sum/)

## 算法组合技巧

### DP + Tree
- **特点**：树形DP，状态在树上传递
- **应用**：路径问题、选择问题
- **技巧**：后序遍历，从叶子节点开始计算

### Tree + Map
- **特点**：树遍历+哈希表记录
- **应用**：查找问题、统计问题
- **技巧**：遍历时记录状态，查找时快速定位

### DP + Map
- **特点**：状态压缩+哈希表优化
- **应用**：状态空间过大时的优化
- **技巧**：用哈希表存储状态，避免重复计算

## 学习总结

### 本周学习成果
1. **动态规划**：掌握了基本DP思想和经典模型
2. **树结构**：熟练处理各种树问题
3. **哈希表**：灵活运用哈希表解决复杂问题
4. **综合应用**：能够组合多种算法解决问题

### 解题能力提升
1. **问题分析**：能够快速识别问题类型
2. **算法选择**：知道何时使用哪种算法
3. **代码实现**：能够正确实现算法
4. **优化改进**：考虑时间和空间复杂度

### 常见解题模式
1. **简单问题**：直接应用单一算法
2. **中等问题**：组合两种算法
3. **复杂问题**：分步骤使用多种算法
4. **综合问题**：需要创新思维和灵活应用

### 继续学习建议
1. **多练习**：继续刷题巩固知识
2. **总结模板**：整理常用解题模板
3. **扩展学习**：学习更多算法和数据结构
4. **实战应用**：参与算法竞赛或项目

## 本周总结

恭喜你完成了算法题一周学习计划！通过这一周的学习，你已经掌握了：

### 核心算法
- **动态规划**：从基础到进阶，掌握了状态定义、状态转移、边界条件
- **树结构**：从遍历到操作，掌握了递归和迭代两种实现方式
- **哈希表**：从基础到进阶，掌握了各种应用场景和优化技巧

### 解题能力
- **问题分析**：能够快速理解题目要求
- **算法选择**：知道何时使用哪种算法
- **代码实现**：能够正确实现算法逻辑
- **优化改进**：考虑时间和空间复杂度

### 学习成果
- 完成了20+道精选算法题
- 掌握了3大核心算法领域
- 建立了系统的解题思维
- 提升了编程和算法能力

记住：算法学习是一个持续的过程，需要不断的练习和总结。继续保持学习的热情，你一定会成为优秀的算法工程师！

[返回周计划](/plan/algorithm/week1/) | [返回主页](/plan/algorithm/)
