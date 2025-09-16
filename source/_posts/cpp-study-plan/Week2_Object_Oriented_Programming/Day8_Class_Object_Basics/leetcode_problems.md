# 第8天算法题练习

## 1. LRU缓存 (Medium)

**题目链接**: https://leetcode.cn/problems/lru-cache/

**题目描述**: 
设计并实现一个LRU（最近最少使用）缓存机制。它应该支持以下操作：获取数据 get 和写入数据 put。

- 获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
- 写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

**示例**:
```
LRUCache cache = new LRUCache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回 1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回 3
cache.get(4);       // 返回 4
```

**解题思路**:
- 使用双向链表维护访问顺序，最近访问的节点在头部
- 使用哈希表快速定位节点
- 当容量满时，删除链表尾部节点

**关键点**:
- 双向链表 + 哈希表实现
- 理解LRU算法的核心思想
- 掌握链表节点的插入和删除操作

## 2. 设计循环队列 (Medium)

**题目链接**: https://leetcode.cn/problems/design-circular-queue/

**题目描述**:
设计你的循环队列实现。循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为"环形缓冲器"。

循环队列的一个好处是我们可以利用这个队列之前用过的空间。在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。但是使用循环队列，我们能使用这些空间去存储新的值。

你的实现应该支持如下操作：
- MyCircularQueue(k): 构造器，设置队列长度为 k 。
- Front: 从队首获取元素。如果队列为空，返回 -1 。
- Rear: 获取队尾元素。如果队列为空，返回 -1 。
- enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
- deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
- isEmpty(): 检查循环队列是否为空。
- isFull(): 检查循环队列是否已满。

**示例**:
```
MyCircularQueue circularQueue = new MyCircularQueue(3); // 设置长度为 3
circularQueue.enQueue(1);  // 返回 true
circularQueue.enQueue(2);  // 返回 true
circularQueue.enQueue(3);  // 返回 true
circularQueue.enQueue(4);  // 返回 false，队列已满
circularQueue.Rear();  // 返回 3
circularQueue.isFull();  // 返回 true
circularQueue.deQueue();  // 返回 true
circularQueue.enQueue(4);  // 返回 true
circularQueue.Rear();  // 返回 4
```

**解题思路**:
- 使用数组实现循环队列
- 使用两个指针 front 和 rear 分别指向队首和队尾
- 通过模运算实现循环

**关键点**:
- 使用数组实现循环队列
- 理解循环队列的空和满状态判断
- 掌握模运算在循环数组中的应用

## 3. 设计哈希集合 (Easy-Medium)

**题目链接**: https://leetcode.cn/problems/design-hashset/

**题目描述**:
不使用任何内建的哈希表库设计一个哈希集合（HashSet）。

实现 MyHashSet 类：
- void add(key) 向哈希集合中插入值 key 。
- bool contains(key) 返回哈希集合中是否存在这个值 key 。
- void remove(key) 将给定值 key 从哈希集合中删除。如果哈希集合中没有这个值，什么也不做。

**示例**:
```
输入：
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
输出：
[null, null, null, true, false, null, true, null, false]

解释：
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // 返回 True
myHashSet.contains(3); // 返回 False ，（未找到）
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // 返回 True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // 返回 False ，（已移除）
```

**解题思路**:
- 使用数组 + 链表的链地址法解决哈希冲突
- 设计合适的哈希函数
- 实现基本的增删查操作

**关键点**:
- 设计哈希函数
- 处理哈希冲突（链地址法）
- 实现基本的增删查操作

## 4. 设计哈希映射 (Easy-Medium)

**题目链接**: https://leetcode.cn/problems/design-hashmap/

**题目描述**:
不使用任何内建的哈希表库设计一个哈希映射（HashMap）。

实现 MyHashMap 类：
- MyHashMap() 用空映射初始化对象
- void put(int key, int value) 向 HashMap 插入一个键值对 (key, value) 。如果 key 已经存在于映射中，则更新其对应的值 value 。
- int get(int key) 返回特定的 key 所映射的 value ；如果映射中不包含 key 的映射，返回 -1 。
- void remove(key) 如果映射中存在 key 的映射，则移除 key 和它所对应的 value 。

**示例**:
```
输入：
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
输出：
[null, null, null, 1, -1, null, 1, null, -1]

解释：
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // myHashMap 现在为 [[1,1]]
myHashMap.put(2, 2); // myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(1);    // 返回 1
myHashMap.get(3);    // 返回 -1（未找到）
myHashMap.put(2, 1); // myHashMap 现在为 [[1,1], [2,1]]
myHashMap.get(2);    // 返回 1
myHashMap.remove(2); // 删除键为 2 的数据，myHashMap 现在为 [[1,1]]
myHashMap.get(2);    // 返回 -1（未找到）
```

**解题思路**:
- 扩展哈希集合的实现
- 存储键值对而不是单个值
- 实现哈希映射的所有基本操作

**关键点**:
- 扩展哈希集合的实现
- 处理键值对的存储
- 实现哈希映射的所有基本操作

## 解题提示

### 数据结构设计
1. **LRU缓存**: 双向链表 + 哈希表
2. **循环队列**: 数组 + 两个指针
3. **哈希集合**: 数组 + 链表（链地址法）
4. **哈希映射**: 数组 + 链表（存储键值对）

### 编程技巧
1. **边界处理**: 注意各种边界条件
2. **内存管理**: 正确分配和释放内存
3. **时间复杂度**: 考虑各操作的时间复杂度
4. **空间复杂度**: 合理使用额外空间

### 常见错误
1. **循环队列**: 空和满状态的判断
2. **哈希表**: 哈希冲突的处理
3. **LRU**: 节点移动和删除的顺序
4. **内存泄漏**: 忘记释放动态分配的内存

## 学习目标

完成这4道题后，你应该掌握：
- [ ] 双向链表的基本操作
- [ ] 循环队列的实现原理
- [ ] 哈希表的设计和实现
- [ ] 面向对象设计在算法题中的应用
- [ ] 复杂数据结构的组合使用
