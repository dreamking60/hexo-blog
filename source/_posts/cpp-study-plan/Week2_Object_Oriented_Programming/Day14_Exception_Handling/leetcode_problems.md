# 第14天算法题练习

## 1. 设计一个支持增量操作的栈 (Medium)

**题目链接**: https://leetcode.cn/problems/design-a-stack-with-increment-operation/

**题目描述**: 
请你设计一个支持下述操作的栈：
- CustomStack(int maxSize)：用 maxSize 初始化对象，maxSize 是栈中最多能容纳的元素数量。
- void push(int x)：如果栈还未增长到 maxSize，就将 x 添加到栈顶。
- int pop()：返回栈顶的值，或栈为空时返回 -1。
- void inc(int k, int val)：栈底的 k 个元素的值都增加 val。

**解题思路**:
- 使用数组实现栈
- 延迟更新：维护增量数组
- 异常安全：边界检查

## 2. 设计循环双端队列 (Medium)

**题目链接**: https://leetcode.cn/problems/design-circular-deque/

**题目描述**: 
设计实现双端队列。你的实现需要支持以下操作：
- MyCircularDeque(k)：构造函数,双端队列的大小为k。
- insertFront()：将一个元素添加到双端队列头部。
- insertLast()：将一个元素添加到双端队列尾部。
- deleteFront()：从双端队列头部删除一个元素。
- deleteLast()：从双端队列尾部删除一个元素。

**解题思路**:
- 循环数组实现
- 异常处理：边界检查
- RAII原则：资源管理

## 3. 设计推特 (Medium)

**题目链接**: https://leetcode.cn/problems/design-twitter/

**题目描述**: 
设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近十条推文。

**解题思路**:
- 面向对象设计
- 异常安全的数据结构
- 时间线算法

## 4. 设计前K个高频元素 (Medium)

**题目链接**: https://leetcode.cn/problems/top-k-frequent-elements/

**题目描述**: 
给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

**解题思路**:
- 哈希表统计频率
- 优先队列维护前K个
- 异常处理：空数组检查
