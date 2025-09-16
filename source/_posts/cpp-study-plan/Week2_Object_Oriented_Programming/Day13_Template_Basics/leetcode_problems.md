# 第13天算法题练习

## 1. 合并K个升序链表 (Hard)

**题目链接**: https://leetcode.cn/problems/merge-k-sorted-lists/

**题目描述**: 
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

**解题思路**:
- 使用优先队列（最小堆）
- 分治法：两两合并
- 模板编程：泛型实现

## 2. 数组中的第K个最大元素 (Medium)

**题目链接**: https://leetcode.cn/problems/kth-largest-element-in-an-array/

**题目描述**: 
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

**解题思路**:
- 快速选择算法
- 堆排序
- 模板实现：支持不同数据类型

## 3. 前K个高频元素 (Medium)

**题目链接**: https://leetcode.cn/problems/top-k-frequent-elements/

**题目描述**: 
给你一个整数数组 nums 和一个整数 k，请你返回其中出现频率前 k 高的元素。

**解题思路**:
- 哈希表统计频率
- 优先队列维护前K个
- 模板实现：泛型容器

## 4. 最接近原点的K个点 (Medium)

**题目链接**: https://leetcode.cn/problems/k-closest-points-to-origin/

**题目描述**: 
给定平面上 n 个点的坐标，找到距离原点最近的 k 个点。

**解题思路**:
- 计算每个点到原点的距离
- 使用优先队列维护最近的K个点
- 模板实现：支持不同维度的点
