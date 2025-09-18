---
title: 算法学习计划 - 第3天:树结构基础
date: 2025-09-16 10:04:00
categories: Algorithm
tags:
    - Algorithm 
    - LeetCode
    - Study Plan
    - Day3
    - Tree
    - Binary Tree
    - Traversal
layout: page
menu_id: plan
permalink: /plan/algorithm/week1/day3/
---

# 第3天：树结构基础

## 学习目标
- 掌握二叉树的基本概念和性质
- 熟练实现四种遍历方式：前序、中序、后序、层序
- 理解递归和迭代两种实现方式
- 掌握树的基本操作：深度、高度、路径等

## 二叉树基础概念

### 二叉树定义
二叉树是每个节点最多有两个子树的树结构，通常子树被称作"左子树"和"右子树"。

### 二叉树性质
1. 第 i 层最多有 2^(i-1) 个节点
2. 深度为 k 的二叉树最多有 2^k - 1 个节点
3. 叶子节点数 = 度为2的节点数 + 1

### 二叉树遍历
- **前序遍历**：根 → 左 → 右
- **中序遍历**：左 → 根 → 右
- **后序遍历**：左 → 右 → 根
- **层序遍历**：按层从左到右

## 今日重点题目

### 1. 二叉树的中序遍历 (Easy)
**题目链接：** [94. 二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/)

**题目描述：**
给定一个二叉树的根节点 root ，返回它的 中序遍历 。

**解题思路：**
中序遍历：左 → 根 → 右

**递归实现：**
```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
    
private:
    void inorder(TreeNode* root, vector<int>& result) {
        if (!root) return;
        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right, result);
    }
};
```

**迭代实现（使用栈）：**
```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* curr = root;
        
        while (curr || !stk.empty()) {
            while (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            curr = stk.top();
            stk.pop();
            result.push_back(curr->val);
            curr = curr->right;
        }
        
        return result;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 2. 二叉树的层序遍历 (Medium)
**题目链接：** [102. 二叉树的层序遍历](https://leetcode.cn/problems/binary-tree-level-order-traversal/)

**题目描述：**
给你二叉树的根节点 root ，返回其节点值的层序遍历。 （即逐层地，从左到右访问所有节点）。

**解题思路：**
使用队列实现层序遍历，每次处理一层。

**代码实现：**
```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(level);
        }
        
        return result;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 3. 二叉树的最大深度 (Easy)
**题目链接：** [104. 二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

**题目描述：**
给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

**解题思路：**
递归计算左右子树的最大深度，取较大值加1。

**递归实现：**
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

**迭代实现（层序遍历）：**
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while (!q.empty()) {
            int size = q.size();
            depth++;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return depth;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

### 4. 翻转二叉树 (Easy)
**题目链接：** [226. 翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/)

**题目描述：**
给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。

**解题思路：**
递归交换左右子树。

**代码实现：**
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        
        // 交换左右子树
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        
        // 递归处理左右子树
        invertTree(root->left);
        invertTree(root->right);
        
        return root;
    }
};
```

**时间复杂度：** O(n)  
**空间复杂度：** O(n)

## 树遍历总结

### 前序遍历模板
```cpp
void preorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);  // 访问根节点
    preorder(root->left, result); // 遍历左子树
    preorder(root->right, result); // 遍历右子树
}
```

### 中序遍历模板
```cpp
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);  // 遍历左子树
    result.push_back(root->val);  // 访问根节点
    inorder(root->right, result); // 遍历右子树
}
```

### 后序遍历模板
```cpp
void postorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorder(root->left, result);  // 遍历左子树
    postorder(root->right, result); // 遍历右子树
    result.push_back(root->val);    // 访问根节点
}
```

### 层序遍历模板
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(level);
    }
    
    return result;
}
```

## 扩展练习

### 5. 二叉树的前序遍历 (Easy)
**题目链接：** [144. 二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)

### 6. 二叉树的后序遍历 (Easy)
**题目链接：** [145. 二叉树的后序遍历](https://leetcode.cn/problems/binary-tree-postorder-traversal/)

### 7. 对称二叉树 (Easy)
**题目链接：** [101. 对称二叉树](https://leetcode.cn/problems/symmetric-tree/)

### 8. 平衡二叉树 (Easy)
**题目链接：** [110. 平衡二叉树](https://leetcode.cn/problems/balanced-binary-tree/)

## 学习总结

### 树问题解题要点
1. **递归思维**：树问题通常用递归解决
2. **边界条件**：处理空节点的情况
3. **遍历顺序**：根据问题选择合适的遍历方式
4. **状态传递**：在递归中传递必要的信息

### 递归三要素
1. **递归终止条件**：什么时候停止递归
2. **递归函数功能**：函数要做什么
3. **递归调用**：如何调用自身

### 常见错误
1. 忘记处理空节点
2. 递归终止条件错误
3. 遍历顺序错误
4. 栈溢出（递归过深）

### 今日收获
- 掌握了二叉树的四种遍历方式
- 理解了递归和迭代两种实现方法
- 学会了基本的树操作
- 建立了树问题的解题思维

## 明日预告
明天我们将学习树结构进阶内容，包括路径问题、二叉搜索树等更复杂的树问题。

[返回周计划](/plan/algorithm/week1/) | [上一题：动态规划进阶](/plan/algorithm/week1/day2/) | [下一题：树结构进阶](/plan/algorithm/week1/day4/)
