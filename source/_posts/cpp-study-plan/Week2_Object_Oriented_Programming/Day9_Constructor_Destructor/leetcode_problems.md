# 第9天算法题练习

## 1. 设计推特 (Medium)

**题目链接**: https://leetcode.cn/problems/design-twitter/

**题目描述**: 
设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近十条推文。

你的设计需要支持以下的几个功能：
1. postTweet(userId, tweetId): 创建一条新的推文
2. getNewsFeed(userId): 检索最近的十条推文。每个推文都必须是由此用户关注的人或者是用户自己发出的。推文必须按照时间顺序由最近的开始排序。
3. follow(followerId, followeeId): 关注一个用户
4. unfollow(followerId, followeeId): 取消关注一个用户

**示例**:
```
Twitter twitter = new Twitter();

// 用户1发送了一条新推文 (用户id = 1, 推文id = 5).
twitter.postTweet(1, 5);

// 用户1的获取推文应当返回一个列表，其中包含一个id为5的推文.
twitter.getNewsFeed(1);

// 用户1关注了用户2.
twitter.follow(1, 2);

// 用户2发送了一个新推文 (推文id = 6).
twitter.postTweet(2, 6);

// 用户1的获取推文应当返回一个列表，其中包含两个推文，id分别为 -> [6, 5].
// 推文id6应当在推文id5之前，因为它是在5之后发送的.
twitter.getNewsFeed(1);

// 用户1取消关注了用户2.
twitter.unfollow(1, 2);

// 用户1的获取推文应当返回一个列表，其中包含一个id为5的推文.
// 因为用户1已经不再关注用户2.
twitter.getNewsFeed(1);
```

**解题思路**:
- 使用面向对象设计，创建User和Tweet类
- 每个用户维护关注列表和推文列表
- 使用优先队列或归并排序获取最近的推文
- 考虑时间戳或推文ID的排序

**关键点**:
- 面向对象设计思维
- 合理的数据结构选择
- 时间线算法实现
- 关注/取消关注的逻辑处理

## 2. 设计前K个高频元素 (Medium)

**题目链接**: https://leetcode.cn/problems/top-k-frequent-elements/

**题目描述**:
给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

**示例 1**:
```
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
```

**示例 2**:
```
输入: nums = [1], k = 1
输出: [1]
```

**说明**:
- 你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
- 你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。

**解题思路**:
- 使用哈希表统计每个元素的频率
- 使用堆（优先队列）维护前k个高频元素
- 或者使用快速选择算法
- 时间复杂度优化到O(n)

**关键点**:
- 哈希表统计频率
- 堆排序或快速选择算法
- 时间复杂度优化
- 空间复杂度的权衡

## 3. 设计循环双端队列 (Medium)

**题目链接**: https://leetcode.cn/problems/design-circular-deque/

**题目描述**:
设计实现双端队列。你的实现需要支持以下操作：

- MyCircularDeque(k)：构造函数,双端队列的大小为k。
- insertFront()：将一个元素添加到双端队列头部。如果操作成功返回 true。
- insertLast()：将一个元素添加到双端队列尾部。如果操作成功返回 true。
- deleteFront()：从双端队列头部删除一个元素。如果成功删除则返回 true。
- deleteLast()：从双端队列尾部删除一个元素。如果成功删除则返回 true。
- getFront()：从双端队列头部获得一个元素。如果双端队列为空，返回 -1。
- getRear()：获得双端队列的最后一个元素。如果双端队列为空，返回 -1。
- isEmpty()：检查双端队列是否为空。
- isFull()：检查双端队列是否满了。

**示例**:
```
MyCircularDeque circularDeque = new MyCircularDeque(3); // 设置长度为 3
circularDeque.insertLast(1);			// 返回 true
circularDeque.insertLast(2);			// 返回 true
circularDeque.insertFront(3);			// 返回 true
circularDeque.insertFront(4);			// 返回 false,队列已满
circularDeque.getRear();  			// 返回 2
circularDeque.isFull();				// 返回 true
circularDeque.deleteLast();			// 返回 true
circularDeque.insertFront(4);			// 返回 true
circularDeque.getFront();			// 返回 4
```

**解题思路**:
- 使用循环数组实现双端队列
- 维护front和rear两个指针
- 通过模运算实现循环
- 注意空和满状态的判断

**关键点**:
- 循环数组实现
- 双端队列操作
- 边界条件处理
- 模运算的正确使用

## 4. 设计一个支持增量操作的栈 (Medium)

**题目链接**: https://leetcode.cn/problems/design-a-stack-with-increment-operation/

**题目描述**:
请你设计一个支持下述操作的栈：

- CustomStack(int maxSize)：用 maxSize 初始化对象，maxSize 是栈中最多能容纳的元素数量。
- void push(int x)：如果栈还未增长到 maxSize ，就将 x 添加到栈顶。
- int pop()：返回栈顶的值，或栈为空时返回 -1 。
- void inc(int k, int val)：栈底的 k 个元素的值都增加 val 。如果栈中元素总数小于 k ，则栈中的所有元素都增加 val 。

**示例**:
```
输入：
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[]]
输出：
[null,null,null,2,null,null,null,null,null,103,202,201]
解释：
CustomStack customStack = new CustomStack(3); // 栈是空的 []
customStack.push(1);                          // 栈变为 [1]
customStack.push(2);                          // 栈变为 [1, 2]
customStack.pop();                            // 返回 2 --> 返回栈顶值 2，栈变为 [1]
customStack.push(2);                          // 栈变为 [1, 2]
customStack.push(3);                          // 栈变为 [1, 2, 3]
customStack.push(4);                          // 栈满了，所以拒绝添加新元素
customStack.increment(5, 100);                // 栈变为 [101, 102, 103]
customStack.increment(2, 100);                // 栈变为 [201, 202, 103]
customStack.pop();                            // 返回 103 --> 返回栈顶值 103，栈变为 [201, 202]
customStack.pop();                            // 返回 202 --> 返回栈顶值 202，栈变为 [201]
customStack.pop();                            // 返回 201 --> 返回栈顶值 201，栈变为 []
customStack.pop();                            // 返回 -1 --> 栈为空，返回 -1
```

**解题思路**:
- 使用数组实现栈的基本操作
- 对于增量操作，可以使用延迟更新的技巧
- 维护一个增量数组，记录每个位置的增量值
- 在pop时应用增量

**关键点**:
- 栈的基本操作实现
- 增量操作的优化
- 延迟更新技巧
- 时间复杂度优化

## 解题提示

### 面向对象设计
1. **推特设计**: 创建User和Tweet类，维护用户关系和推文时间线
2. **高频元素**: 使用哈希表+堆的组合数据结构
3. **循环双端队列**: 循环数组+双指针实现
4. **增量栈**: 栈+延迟更新数组

### 数据结构选择
1. **哈希表**: 快速查找和统计
2. **堆/优先队列**: 维护前K个元素
3. **循环数组**: 高效的空间利用
4. **延迟更新**: 优化批量操作

### 算法技巧
1. **时间线算法**: 多路归并或优先队列
2. **快速选择**: 线性时间找第K大元素
3. **模运算**: 实现循环数组
4. **延迟更新**: 批量操作优化

### 常见错误
1. **边界处理**: 空栈、满栈的判断
2. **索引计算**: 循环数组的索引计算
3. **内存管理**: 动态数组的分配和释放
4. **时间复杂度**: 避免不必要的重复计算

## 学习目标

完成这4道题后，你应该掌握：
- [ ] 面向对象设计在算法题中的应用
- [ ] 复杂数据结构的组合使用
- [ ] 延迟更新等优化技巧
- [ ] 循环数组的实现原理
- [ ] 哈希表+堆的组合应用
- [ ] 时间线算法的设计思路
