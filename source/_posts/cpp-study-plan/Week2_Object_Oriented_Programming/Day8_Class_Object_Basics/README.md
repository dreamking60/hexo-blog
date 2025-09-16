# 第8天：类与对象基础

## 学习目标
掌握C++类的基本概念和对象的创建，理解面向对象编程的核心思想，学会设计和使用类。

## 学习内容

### 1. 类的定义与声明
类（Class）是C++面向对象编程的基础，它将数据（成员变量）和操作（成员函数）封装在一起。

#### 基本语法
```cpp
class ClassName {
private:
    // 私有成员（只能被类内部访问）
    dataType memberVariable;
    
protected:
    // 受保护成员（可以被派生类访问）
    dataType protectedMember;
    
public:
    // 公有成员（可以被外部访问）
    dataType publicMember;
    
    // 构造函数
    ClassName();
    
    // 成员函数
    returnType memberFunction();
};
```

#### 访问控制
- **private**：私有成员，只能在类内部访问
- **protected**：受保护成员，可以在类内部和派生类中访问
- **public**：公有成员，可以在任何地方访问

### 2. 对象的创建与销毁
对象是类的实例，通过构造函数创建，通过析构函数销毁。

#### 对象创建方式
```cpp
// 方式1：栈上创建
ClassName obj1;

// 方式2：堆上创建
ClassName* obj2 = new ClassName();

// 方式3：带参数的构造函数
ClassName obj3(param1, param2);
```

### 3. 成员变量与成员函数
- **成员变量**：类的数据成员，存储对象的状态
- **成员函数**：类的操作，定义对象的行为

### 4. this指针
this指针指向当前对象的地址，用于区分同名的成员变量和参数。

```cpp
class MyClass {
private:
    int value;
    
public:
    void setValue(int value) {
        this->value = value;  // 使用this指针区分
    }
    
    int getValue() const {
        return this->value;
    }
};
```

## 实践练习

### 练习1：银行账户类
实现一个银行账户类，包含账户号码、余额、存款和取款功能。

```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;
    
public:
    // 构造函数
    BankAccount(string accNum, double initialBalance = 0.0);
    
    // 存款
    void deposit(double amount);
    
    // 取款
    bool withdraw(double amount);
    
    // 获取余额
    double getBalance() const;
    
    // 获取账户号码
    string getAccountNumber() const;
    
    // 显示账户信息
    void displayAccount() const;
};

// 构造函数实现
BankAccount::BankAccount(string accNum, double initialBalance) 
    : accountNumber(accNum), balance(initialBalance) {
    cout << "账户 " << accountNumber << " 已创建，初始余额: " << balance << endl;
}

// 存款函数实现
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "存款成功，当前余额: " << balance << endl;
    } else {
        cout << "存款金额必须大于0" << endl;
    }
}

// 取款函数实现
bool BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "取款成功，当前余额: " << balance << endl;
        return true;
    } else if (amount <= 0) {
        cout << "取款金额必须大于0" << endl;
        return false;
    } else {
        cout << "余额不足" << endl;
        return false;
    }
}

// 获取余额
double BankAccount::getBalance() const {
    return balance;
}

// 获取账户号码
string BankAccount::getAccountNumber() const {
    return accountNumber;
}

// 显示账户信息
void BankAccount::displayAccount() const {
    cout << "账户号码: " << accountNumber << ", 余额: " << balance << endl;
}

// 主函数测试
int main() {
    // 创建银行账户对象
    BankAccount account1("123456789", 1000.0);
    BankAccount account2("987654321");
    
    // 测试存款功能
    account1.deposit(500.0);
    account2.deposit(200.0);
    
    // 测试取款功能
    account1.withdraw(300.0);
    account1.withdraw(2000.0);  // 余额不足
    
    // 显示账户信息
    account1.displayAccount();
    account2.displayAccount();
    
    return 0;
}
```

### 练习2：学生类
实现一个学生类，包含学号、姓名、成绩等信息。

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    string studentId;
    string name;
    vector<double> grades;
    
public:
    // 构造函数
    Student(string id, string studentName);
    
    // 添加成绩
    void addGrade(double grade);
    
    // 计算平均分
    double calculateAverage() const;
    
    // 获取最高分
    double getHighestGrade() const;
    
    // 获取最低分
    double getLowestGrade() const;
    
    // 显示学生信息
    void displayInfo() const;
    
    // Getter函数
    string getStudentId() const { return studentId; }
    string getName() const { return name; }
    int getGradeCount() const { return grades.size(); }
};

// 构造函数实现
Student::Student(string id, string studentName) 
    : studentId(id), name(studentName) {
    cout << "学生 " << name << " (学号: " << studentId << ") 已创建" << endl;
}

// 添加成绩
void Student::addGrade(double grade) {
    if (grade >= 0 && grade <= 100) {
        grades.push_back(grade);
        cout << "成绩 " << grade << " 已添加" << endl;
    } else {
        cout << "成绩必须在0-100之间" << endl;
    }
}

// 计算平均分
double Student::calculateAverage() const {
    if (grades.empty()) return 0.0;
    
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    return sum / grades.size();
}

// 获取最高分
double Student::getHighestGrade() const {
    if (grades.empty()) return 0.0;
    
    double highest = grades[0];
    for (double grade : grades) {
        if (grade > highest) {
            highest = grade;
        }
    }
    return highest;
}

// 获取最低分
double Student::getLowestGrade() const {
    if (grades.empty()) return 0.0;
    
    double lowest = grades[0];
    for (double grade : grades) {
        if (grade < lowest) {
            lowest = grade;
        }
    }
    return lowest;
}

// 显示学生信息
void Student::displayInfo() const {
    cout << "学号: " << studentId << ", 姓名: " << name << endl;
    cout << "成绩数量: " << grades.size() << endl;
    if (!grades.empty()) {
        cout << "平均分: " << calculateAverage() << endl;
        cout << "最高分: " << getHighestGrade() << endl;
        cout << "最低分: " << getLowestGrade() << endl;
    }
}

// 主函数测试
int main() {
    Student student1("2023001", "张三");
    Student student2("2023002", "李四");
    
    // 添加成绩
    student1.addGrade(85.5);
    student1.addGrade(92.0);
    student1.addGrade(78.5);
    
    student2.addGrade(90.0);
    student2.addGrade(88.5);
    
    // 显示学生信息
    student1.displayInfo();
    cout << "---" << endl;
    student2.displayInfo();
    
    return 0;
}
```

## 算法题练习

### 1. LRU缓存 (Medium)
**题目链接**: https://leetcode.cn/problems/lru-cache/

设计并实现一个LRU（最近最少使用）缓存机制。它应该支持以下操作：获取数据 get 和写入数据 put。

**关键点**：
- 使用双向链表 + 哈希表实现
- 理解LRU算法的核心思想
- 掌握链表节点的插入和删除操作

### 2. 设计循环队列 (Medium)
**题目链接**: https://leetcode.cn/problems/design-circular-queue/

设计你的循环队列实现。循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为"环形缓冲器"。

**关键点**：
- 使用数组实现循环队列
- 理解循环队列的空和满状态判断
- 掌握模运算在循环数组中的应用

### 3. 设计哈希集合 (Easy-Medium)
**题目链接**: https://leetcode.cn/problems/design-hashset/

不使用任何内建的哈希表库设计一个哈希集合（HashSet）。

**关键点**：
- 设计哈希函数
- 处理哈希冲突（链地址法）
- 实现基本的增删查操作

### 4. 设计哈希映射 (Easy-Medium)
**题目链接**: https://leetcode.cn/problems/design-hashmap/

不使用任何内建的哈希表库设计一个哈希映射（HashMap）。

**关键点**：
- 扩展哈希集合的实现
- 处理键值对的存储
- 实现哈希映射的所有基本操作

## 学习要点总结

### 1. 类的设计原则
- **封装性**：将数据和行为封装在类中
- **单一职责**：每个类应该有明确的职责
- **接口设计**：提供清晰的公有接口

### 2. 访问控制的重要性
- **private**：保护内部实现细节
- **public**：提供外部访问接口
- **protected**：为继承做准备

### 3. this指针的使用
- 区分成员变量和参数
- 返回当前对象的引用
- 链式调用

### 4. 良好的编程习惯
- 使用const成员函数
- 合理的成员变量初始化
- 清晰的函数命名

## 扩展练习

1. 实现一个图书类，包含书名、作者、ISBN等信息
2. 设计一个日期类，支持日期的比较和计算
3. 实现一个简单的计算器类
4. 设计一个员工管理系统的基础类

## 学习检查

完成今天的学习后，你应该能够：
- [ ] 理解类的基本概念和语法
- [ ] 掌握对象的创建和销毁
- [ ] 理解访问控制的作用
- [ ] 会使用this指针
- [ ] 能够设计简单的类
- [ ] 完成4道算法题

记住：面向对象编程的核心是抽象和封装，通过类来模拟现实世界中的概念！
