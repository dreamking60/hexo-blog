#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 练习1：银行账户类
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

// 练习2：学生类
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

// 练习3：图书类
class Book {
private:
    string title;
    string author;
    string isbn;
    int pages;
    double price;
    
public:
    // 构造函数
    Book(string bookTitle, string bookAuthor, string bookISBN, int bookPages, double bookPrice);
    
    // 显示图书信息
    void displayInfo() const;
    
    // 获取价格
    double getPrice() const { return price; }
    
    // 设置价格
    void setPrice(double newPrice);
    
    // 获取标题
    string getTitle() const { return title; }
    
    // 获取作者
    string getAuthor() const { return author; }
    
    // 获取ISBN
    string getISBN() const { return isbn; }
};

// 构造函数实现
Book::Book(string bookTitle, string bookAuthor, string bookISBN, int bookPages, double bookPrice)
    : title(bookTitle), author(bookAuthor), isbn(bookISBN), pages(bookPages), price(bookPrice) {
    cout << "图书《" << title << "》已创建" << endl;
}

// 显示图书信息
void Book::displayInfo() const {
    cout << "书名: " << title << endl;
    cout << "作者: " << author << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "页数: " << pages << endl;
    cout << "价格: " << price << "元" << endl;
}

// 设置价格
void Book::setPrice(double newPrice) {
    if (newPrice > 0) {
        price = newPrice;
        cout << "价格已更新为: " << price << "元" << endl;
    } else {
        cout << "价格必须大于0" << endl;
    }
}

// 主函数测试
int main() {
    cout << "=== 银行账户测试 ===" << endl;
    BankAccount account1("123456789", 1000.0);
    BankAccount account2("987654321");
    
    account1.deposit(500.0);
    account2.deposit(200.0);
    account1.withdraw(300.0);
    account1.withdraw(2000.0);
    
    account1.displayAccount();
    account2.displayAccount();
    
    cout << "\n=== 学生类测试 ===" << endl;
    Student student1("2023001", "张三");
    Student student2("2023002", "李四");
    
    student1.addGrade(85.5);
    student1.addGrade(92.0);
    student1.addGrade(78.5);
    
    student2.addGrade(90.0);
    student2.addGrade(88.5);
    
    student1.displayInfo();
    cout << "---" << endl;
    student2.displayInfo();
    
    cout << "\n=== 图书类测试 ===" << endl;
    Book book1("C++ Primer", "Stanley Lippman", "978-7-121-15535-2", 976, 128.0);
    Book book2("Effective C++", "Scott Meyers", "978-7-121-15536-9", 317, 89.0);
    
    book1.displayInfo();
    cout << "---" << endl;
    book2.displayInfo();
    
    book1.setPrice(118.0);
    book1.displayInfo();
    
    return 0;
}
