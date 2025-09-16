# 第22天：设计模式 - LeetCode算法题

## 今日算法练习 (4道Medium/Hard题目)

### 题目1：设计模式 - 单例模式应用
**LeetCode 1472. Design Browser History (Medium)**
- **链接：** https://leetcode.com/problems/design-browser-history/
- **难度：** Medium
- **知识点：** 设计模式、栈、链表
- **描述：** 设计一个浏览器历史记录系统，支持访问页面、后退、前进操作
- **设计模式应用：** 可以使用单例模式管理全局浏览器历史，使用策略模式处理不同的导航策略

**解题思路：**
- 使用双向链表或栈来维护历史记录
- 实现visit、back、forward三个核心方法
- 考虑使用设计模式优化代码结构

### 题目2：工厂模式 - 对象创建
**LeetCode 1845. Seat Reservation Manager (Medium)**
- **链接：** https://leetcode.com/problems/seat-reservation-manager/
- **难度：** Medium
- **知识点：** 工厂模式、优先队列、堆
- **描述：** 设计一个座位预约管理系统，支持预约最小编号的可用座位和释放座位
- **设计模式应用：** 使用工厂模式创建不同类型的座位管理器，使用单例模式管理全局座位状态

**解题思路：**
- 使用最小堆维护可用座位
- 实现reserve和unreserve方法
- 考虑使用工厂模式创建管理器实例

### 题目3：观察者模式 - 事件通知
**LeetCode 1656. Design an Ordered Stream (Medium)**
- **链接：** https://leetcode.com/problems/design-an-ordered-stream/
- **难度：** Medium
- **知识点：** 观察者模式、数据流、状态管理
- **描述：** 设计一个有序数据流，当插入数据时返回从指针位置开始的连续数据块
- **设计模式应用：** 使用观察者模式通知数据变化，使用状态模式管理指针状态

**解题思路：**
- 维护一个数组和指针位置
- 每次插入后检查连续性
- 实现观察者模式通知机制

### 题目4：策略模式 - 算法选择 (Hard)
**LeetCode 1622. Fancy Sequence (Hard)**
- **链接：** https://leetcode.com/problems/fancy-sequence/
- **难度：** Hard
- **知识点：** 策略模式、数学、模运算、延迟更新
- **描述：** 设计一个支持append、addAll、multAll、getIndex操作的序列，要求高效处理大量操作
- **设计模式应用：** 使用策略模式选择不同的更新策略，使用命令模式封装操作

**解题思路：**
- 使用延迟更新技术避免每次操作都更新所有元素
- 维护全局的加法和乘法因子
- 使用模运算处理大数
- 实现不同的更新策略

## 额外练习题（可选）

### 题目5：建造者模式应用
**LeetCode 1603. Design Parking System (Easy)**
- **链接：** https://leetcode.com/problems/design-parking-system/
- **难度：** Easy (作为设计模式练习提升为Medium)
- **设计模式应用：** 使用建造者模式构建停车系统配置

### 题目6：装饰器模式应用
**LeetCode 1352. Product of the Last K Numbers (Medium)**
- **链接：** https://leetcode.com/problems/product-of-the-last-k-numbers/
- **难度：** Medium
- **设计模式应用：** 使用装饰器模式扩展基本数组功能

## 解题要求

### 编码规范
1. **使用现代C++特性**：智能指针、auto、范围for循环等
2. **应用设计模式**：在解题中体现今天学习的设计模式
3. **异常安全**：使用RAII管理资源
4. **线程安全**：考虑多线程环境下的安全性

### 性能要求
- 时间复杂度应该达到题目要求
- 空间复杂度尽可能优化
- 考虑大数据量下的性能表现

### 代码质量
- 代码结构清晰，职责分离
- 适当的注释和文档
- 错误处理完善
- 单元测试覆盖

## 设计模式应用示例

### 示例：在LeetCode 1472中应用设计模式
```cpp
// 使用单例模式管理浏览器历史
class BrowserHistoryManager {
private:
    static std::unique_ptr<BrowserHistoryManager> instance;
    static std::mutex mtx;
    
    BrowserHistoryManager() = default;
    
public:
    static BrowserHistoryManager& getInstance() {
        std::call_once(flag, []() {
            instance = std::make_unique<BrowserHistoryManager>();
        });
        return *instance;
    }
    
    // 工厂方法创建不同类型的历史记录
    std::unique_ptr<BrowserHistory> createHistory(const std::string& homepage) {
        return std::make_unique<BrowserHistory>(homepage);
    }
    
private:
    static std::once_flag flag;
};

// 策略模式：不同的导航策略
class NavigationStrategy {
public:
    virtual std::string navigate(BrowserHistory* history, int steps) = 0;
    virtual ~NavigationStrategy() = default;
};

class BackwardStrategy : public NavigationStrategy {
public:
    std::string navigate(BrowserHistory* history, int steps) override {
        // 后退逻辑
    }
};

class ForwardStrategy : public NavigationStrategy {
public:
    std::string navigate(BrowserHistory* history, int steps) override {
        // 前进逻辑
    }
};
```

## 学习目标检查

完成今天的算法题后，你应该能够：

1. ✅ **理解设计模式的实际应用**：在解题中体现设计模式的价值
2. ✅ **掌握单例模式**：在需要全局唯一实例的场景中应用
3. ✅ **掌握工厂模式**：在需要创建不同类型对象时应用
4. ✅ **掌握观察者模式**：在需要事件通知的场景中应用
5. ✅ **掌握策略模式**：在需要算法选择的场景中应用
6. ✅ **掌握RAII模式**：在资源管理中应用

## 提交要求

1. 每道题提供完整的C++解决方案
2. 代码中体现相应的设计模式
3. 包含时间和空间复杂度分析
4. 提供测试用例和验证结果
5. 总结设计模式在算法题中的应用心得
