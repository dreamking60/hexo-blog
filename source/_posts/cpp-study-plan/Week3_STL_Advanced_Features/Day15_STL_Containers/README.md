# 第15天：STL容器复习

## 学习目标
掌握C++标准模板库中各种容器的使用，理解不同容器的特点、性能和使用场景。

## 学习内容

### 1. 序列容器 (Sequence Containers)

#### vector
- **特点**：动态数组，支持随机访问
- **时间复杂度**：插入/删除末尾O(1)，中间O(n)，访问O(1)
- **使用场景**：需要随机访问，频繁在末尾操作
- **内存**：连续存储，缓存友好

```cpp
#include <vector>
#include <iostream>

void vectorExample() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // 添加元素
    vec.push_back(6);
    vec.insert(vec.begin() + 2, 10);
    
    // 访问元素
    std::cout << "第一个元素: " << vec[0] << std::endl;
    std::cout << "最后一个元素: " << vec.back() << std::endl;
    
    // 遍历
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // 容量管理
    std::cout << "大小: " << vec.size() << std::endl;
    std::cout << "容量: " << vec.capacity() << std::endl;
}
```

#### list
- **特点**：双向链表，不支持随机访问
- **时间复杂度**：插入/删除O(1)，访问O(n)
- **使用场景**：频繁在中间插入/删除，不需要随机访问
- **内存**：非连续存储

```cpp
#include <list>
#include <iostream>

void listExample() {
    std::list<int> lst = {1, 2, 3, 4, 5};
    
    // 插入元素
    auto it = lst.begin();
    std::advance(it, 2);  // 移动到第3个位置
    lst.insert(it, 10);
    
    // 删除元素
    lst.remove(3);  // 删除所有值为3的元素
    
    // 遍历
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
```

#### deque
- **特点**：双端队列，支持两端操作
- **时间复杂度**：两端插入/删除O(1)，中间O(n)，访问O(1)
- **使用场景**：需要两端操作，偶尔需要随机访问
- **内存**：分段连续存储

```cpp
#include <deque>
#include <iostream>

void dequeExample() {
    std::deque<int> dq = {1, 2, 3, 4, 5};
    
    // 两端操作
    dq.push_front(0);
    dq.push_back(6);
    
    // 访问
    std::cout << "前端: " << dq.front() << std::endl;
    std::cout << "后端: " << dq.back() << std::endl;
    
    // 随机访问
    std::cout << "中间元素: " << dq[2] << std::endl;
}
```

### 2. 关联容器 (Associative Containers)

#### set
- **特点**：有序集合，元素唯一
- **时间复杂度**：插入/删除/查找O(log n)
- **使用场景**：需要有序且唯一的元素集合
- **实现**：红黑树

```cpp
#include <set>
#include <iostream>

void setExample() {
    std::set<int> s = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // 插入
    s.insert(7);
    
    // 查找
    auto it = s.find(5);
    if (it != s.end()) {
        std::cout << "找到元素: " << *it << std::endl;
    }
    
    // 遍历（自动排序）
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // 范围查找
    auto lower = s.lower_bound(3);
    auto upper = s.upper_bound(6);
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

#### map
- **特点**：键值对映射，键唯一且有序
- **时间复杂度**：插入/删除/查找O(log n)
- **使用场景**：需要键值对映射，按键排序
- **实现**：红黑树

```cpp
#include <map>
#include <iostream>
#include <string>

void mapExample() {
    std::map<std::string, int> m = {
        {"apple", 5},
        {"banana", 3},
        {"cherry", 8}
    };
    
    // 插入/更新
    m["date"] = 2;
    m["apple"] = 6;  // 更新
    
    // 查找
    auto it = m.find("banana");
    if (it != m.end()) {
        std::cout << "banana: " << it->second << std::endl;
    }
    
    // 遍历
    for (const auto& pair : m) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // 使用[]操作符（注意：会创建不存在的键）
    std::cout << "grape: " << m["grape"] << std::endl;
}
```

### 3. 容器适配器 (Container Adapters)

#### stack
- **特点**：后进先出(LIFO)
- **默认容器**：deque
- **使用场景**：需要栈操作，如表达式求值、括号匹配

```cpp
#include <stack>
#include <iostream>

void stackExample() {
    std::stack<int> st;
    
    // 入栈
    st.push(1);
    st.push(2);
    st.push(3);
    
    // 查看栈顶
    std::cout << "栈顶: " << st.top() << std::endl;
    
    // 出栈
    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
}
```

#### queue
- **特点**：先进先出(FIFO)
- **默认容器**：deque
- **使用场景**：需要队列操作，如BFS、任务调度

```cpp
#include <queue>
#include <iostream>

void queueExample() {
    std::queue<int> q;
    
    // 入队
    q.push(1);
    q.push(2);
    q.push(3);
    
    // 查看队首
    std::cout << "队首: " << q.front() << std::endl;
    
    // 出队
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}
```

#### priority_queue
- **特点**：优先队列，默认最大堆
- **默认容器**：vector
- **使用场景**：需要优先处理，如Dijkstra算法、任务调度

```cpp
#include <queue>
#include <iostream>

void priorityQueueExample() {
    // 最大堆（默认）
    std::priority_queue<int> maxHeap;
    
    // 最小堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
    // 添加元素
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    maxHeap.push(1);
    maxHeap.push(5);
    
    // 查看堆顶
    std::cout << "最大堆顶: " << maxHeap.top() << std::endl;
    
    // 弹出元素
    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    std::cout << std::endl;
}
```

### 4. 迭代器 (Iterators)

```cpp
#include <vector>
#include <iostream>

void iteratorExample() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // 正向迭代器
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 反向迭代器
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 常量迭代器
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

## 容器选择原则

### 1. 访问模式
- **随机访问**：vector, deque
- **顺序访问**：list, forward_list
- **键值访问**：map, unordered_map

### 2. 插入/删除位置
- **末尾**：vector, deque
- **中间**：list
- **任意位置**：set, map

### 3. 内存考虑
- **连续存储**：vector, array
- **非连续存储**：list, set, map

### 4. 性能要求
- **查找频繁**：set, map, unordered_set, unordered_map
- **插入频繁**：list, unordered_set, unordered_map

## 实践练习

### 练习1：学生成绩管理系统
```cpp
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class StudentManager {
private:
    std::map<int, std::string> students;  // 学号->姓名
    std::vector<std::pair<int, double>> grades;  // 学号->成绩
    
public:
    void addStudent(int id, const std::string& name) {
        students[id] = name;
    }
    
    void addGrade(int id, double grade) {
        grades.emplace_back(id, grade);
    }
    
    double getAverageGrade(int id) const {
        double sum = 0;
        int count = 0;
        for (const auto& grade : grades) {
            if (grade.first == id) {
                sum += grade.second;
                count++;
            }
        }
        return count > 0 ? sum / count : 0.0;
    }
    
    void printAllStudents() const {
        for (const auto& student : students) {
            std::cout << "学号: " << student.first 
                      << ", 姓名: " << student.second
                      << ", 平均成绩: " << getAverageGrade(student.first) 
                      << std::endl;
        }
    }
    
    std::vector<int> getTopStudents(int n) const {
        std::vector<std::pair<int, double>> studentAverages;
        for (const auto& student : students) {
            double avg = getAverageGrade(student.first);
            studentAverages.emplace_back(student.first, avg);
        }
        
        // 按平均成绩降序排序
        std::sort(studentAverages.begin(), studentAverages.end(),
                  [](const auto& a, const auto& b) {
                      return a.second > b.second;
                  });
        
        std::vector<int> result;
        for (int i = 0; i < std::min(n, static_cast<int>(studentAverages.size())); ++i) {
            result.push_back(studentAverages[i].first);
        }
        return result;
    }
};
```

### 练习2：表达式求值器
```cpp
#include <stack>
#include <string>
#include <iostream>
#include <cctype>

class ExpressionEvaluator {
public:
    static double evaluate(const std::string& expression) {
        std::stack<double> operands;
        std::stack<char> operators;
        
        for (size_t i = 0; i < expression.length(); ++i) {
            char c = expression[i];
            
            if (std::isspace(c)) {
                continue;
            } else if (std::isdigit(c)) {
                double num = 0;
                while (i < expression.length() && std::isdigit(expression[i])) {
                    num = num * 10 + (expression[i] - '0');
                    ++i;
                }
                --i;  // 回退一个字符
                operands.push(num);
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    applyOperator(operands, operators);
                }
                operators.pop();  // 移除 '('
            } else if (isOperator(c)) {
                while (!operators.empty() && 
                       precedence(operators.top()) >= precedence(c)) {
                    applyOperator(operands, operators);
                }
                operators.push(c);
            }
        }
        
        while (!operators.empty()) {
            applyOperator(operands, operators);
        }
        
        return operands.top();
    }
    
private:
    static bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
    
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    
    static void applyOperator(std::stack<double>& operands, 
                             std::stack<char>& operators) {
        if (operands.size() < 2) return;
        
        double b = operands.top(); operands.pop();
        double a = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        
        switch (op) {
            case '+': operands.push(a + b); break;
            case '-': operands.push(a - b); break;
            case '*': operands.push(a * b); break;
            case '/': operands.push(a / b); break;
        }
    }
};
```

## 学习要点总结

1. **容器选择**：根据使用场景选择合适的容器
2. **性能考虑**：了解各容器的时间复杂度
3. **内存管理**：理解容器的内存分配策略
4. **迭代器**：掌握各种迭代器的使用
5. **实践应用**：通过实际项目加深理解

## 今日算法题

完成以下4道LeetCode题目，巩固STL容器的使用：

1. [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/) - 使用双向链表和哈希表
2. [LeetCode 295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) - 使用两个优先队列
3. [LeetCode 239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) - 使用双端队列
4. [LeetCode 380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) - 使用哈希表和动态数组

每道题目都涉及多个STL容器的组合使用，是很好的实践机会！
