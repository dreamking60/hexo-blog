---
title: 算法学习计划 - 第4天:树结构进阶
date: 2025-09-16 10:05:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day4
    - Tree
    - Binary Tree
    - BST
    - Path Sum
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day4/
---

# 第4天：树结构进阶

## 学习目标
- 掌握树的路径问题解法
- 理解二叉搜索树的性质和操作
- 学会树的序列化和反序列化
- 掌握最近公共祖先问题

## 树路径问题

### 路径问题特点
- 通常需要从根节点到叶子节点的路径
- 可能涉及路径和、路径数量等计算
- 需要回溯或记录路径信息
- 递归时传递路径状态

### 路径问题解题模板
```cpp
void dfs(TreeNode* root, int target, vector<int>& path, vector<vector<int>>& result) {
    if (!root) return;
    
    path.push_back(root->val);
    
    // 检查是否满足条件
    if (满足条件) {
        result.push_back(path);
    }
    
    // 递归处理左右子树
    dfs(root->left, target, path, result);
    dfs(root->right, target, path, result);
    
    // 回溯
    path.pop_back();
}
```

## 今日重点题目

### 1. 路径总和 (Easy)
**题目链接：** [112. 路径总和](https://leetcode.cn/problems/path-sum/)

**题目描述：**
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

**解题思路：**
递归检查是否存在从根到叶子的路径和等于目标值。

**代码实现：**
```cpp
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        
        // 叶子节点
        if (!root->left && !root->right) {
            return root->val == targetSum;
        }
        
        // 递归检查左右子树
        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 2. 路径总和 III (Medium)
**题目链接：** [437. 路径总和 III](https://leetcode.cn/problems/path-sum-iii/)

**题目描述：**
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

**解题思路：**
双重递归：外层递归遍历每个节点，内层递归计算以该节点为起点的路径数。

**代码实现：**
```cpp
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        
        // 以当前节点为起点的路径数 + 左右子树的路径数
        return countPath(root, targetSum) +
               pathSum(root->left, targetSum) +
               pathSum(root->right, targetSum);
    }
    
private:
    int countPath(TreeNode* root, int targetSum) {
        if (!root) return 0;
        
        int count = 0;
        if (root->val == targetSum) count++;
        
        count += countPath(root->left, targetSum - root->val);
        count += countPath(root->right, targetSum - root->val);
        
        return count;
    }
};
```

**时间复杂度：** O(n²)  
**空间复杂度：** O(n)

### 3. 验证二叉搜索树 (Medium)
**题目链接：** [98. 验证二叉搜索树](https://leetcode.cn/problems/validate-binary-search-tree/)

**题目描述：**
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：
- 节点的左子树只包含 小于 当前节点的数。
- 节点的右子树只包含 大于 当前节点的数。
- 所有左子树和右子树自身必须也是二叉搜索树。

**解题思路：**
中序遍历BST得到有序序列，或者递归检查每个节点是否在合理范围内。

**方法1：中序遍历**
```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> inorder;
        inorderTraversal(root, inorder);
        
        for (int i = 1; i < inorder.size(); i++) {
            if (inorder[i] <= inorder[i-1]) {
                return false;
            }
        }
        return true;
    }
    
private:
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        if (!root) return;
        inorderTraversal(root->left, inorder);
        inorder.push_back(root->val);
        inorderTraversal(root->right, inorder);
    }
};
```

**方法2：递归检查范围**
```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }
    
private:
    bool isValidBST(TreeNode* root, long min, long max) {
        if (!root) return true;
        
        if (root->val <= min || root->val >= max) {
            return false;
        }
        
        return isValidBST(root->left, min, root->val) &&
               isValidBST(root->right, root->val, max);
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 4. 二叉树的最近公共祖先 (Medium)
**题目链接：** [236. 二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/)

**题目描述：**
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

最近公共祖先的定义为："对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。"

**解题思路：**
递归查找，如果当前节点是p或q，返回当前节点；否则递归查找左右子树，如果左右子树都找到，则当前节点是LCA。

**代码实现：**
```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) {
            return root;
        }
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if (left && right) {
            return root;
        }
        
        return left ? left : right;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

## 二叉搜索树(BST)基础

### BST性质
1. 左子树所有节点值 < 根节点值
2. 右子树所有节点值 > 根节点值
3. 左右子树都是BST

### BST操作
- **查找**：O(log n) 平均，O(n) 最坏
- **插入**：O(log n) 平均，O(n) 最坏
- **删除**：O(log n) 平均，O(n) 最坏

### BST中序遍历
BST的中序遍历结果是升序序列，这是BST的重要性质。

## 扩展练习

### 5. 路径总和 II (Medium)
**题目链接：** [113. 路径总和 II](https://leetcode.cn/problems/path-sum-ii/)

### 6. 二叉搜索树中的搜索 (Easy)
**题目链接：** [700. 二叉搜索树中的搜索](https://leetcode.cn/problems/search-in-a-binary-search-tree/)

### 7. 二叉搜索树中的插入操作 (Medium)
**题目链接：** [701. 二叉搜索树中的插入操作](https://leetcode.cn/problems/insert-into-a-binary-search-tree/)

### 8. 删除二叉搜索树中的节点 (Medium)
**题目链接：** [450. 删除二叉搜索树中的节点](https://leetcode.cn/problems/delete-node-in-a-bst/)

## 学习总结

### 树路径问题解题要点
1. **路径定义**：明确路径的起点和终点
2. **状态传递**：在递归中传递路径信息
3. **回溯处理**：及时清理路径状态
4. **边界条件**：处理空节点和叶子节点

### BST问题解题要点
1. **利用性质**：BST的中序遍历是有序的
2. **范围检查**：递归时传递值的范围
3. **查找优化**：利用BST性质进行二分查找
4. **操作维护**：插入删除后保持BST性质

### 最近公共祖先问题
1. **递归查找**：在左右子树中查找目标节点
2. **状态判断**：根据查找结果判断LCA位置
3. **边界处理**：处理节点不存在的情况

### 常见错误
1. 路径问题中忘记回溯
2. BST验证时范围检查错误
3. LCA问题中状态判断错误
4. 递归终止条件不完整

### 今日收获
- 掌握了树路径问题的解法
- 理解了BST的性质和操作
- 学会了LCA问题的解法
- 建立了更复杂的树问题思维

## 明日预告
明天我们将学习哈希表基础，包括两数之和、滑动窗口等经典问题，这将是一个全新的算法领域。

[返回周计划](/plan/algorithm/week1/) | [上一题：树结构基础](/plan/algorithm/week1/day3/) | [下一题：哈希表基础](/plan/algorithm/week1/day5/)
