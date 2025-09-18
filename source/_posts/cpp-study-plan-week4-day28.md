---
title: C++ 学习计划 - 第28天:综合项目 - 小型系统设计
date: 2025-09-16 10:31:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week4
    - Day28
layout: page
menu_id: plan
permalink: /plan/week4/day28/
---

# 第28天：综合项目 - 小型系统设计

## 学习目标
通过设计和实现一个完整的小型系统，综合运用四周来学到的所有C++知识，包括面向对象设计、现代C++特性、设计模式和性能优化等。

## 学习资源链接

### 📚 系统设计资源
- [System Design Primer](https://github.com/donnemartin/system-design-primer) - 系统设计入门
- [Clean Architecture](https://www.amazon.com/Clean-Architecture-Craftsmans-Software-Structure/dp/0134494164) - 整洁架构
- [Design Patterns](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612) - 设计模式经典
- [C++ Software Design](https://www.amazon.com/Software-Design-Principles-Patterns-High-Quality/dp/1098113160) - C++软件设计

### 🎥 视频教程
- [System Design Interview](https://www.youtube.com/results?search_query=system+design+interview) - 系统设计面试
- [Clean Code](https://www.youtube.com/watch?v=7EmboKQH8lM) - 整洁代码
- [SOLID Principles](https://www.youtube.com/watch?v=_jDNAf3CzeY) - SOLID设计原则

### 📖 深入阅读
- [Effective C++](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 高效C++编程
- [Modern C++ Design](https://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315) - 现代C++设计
- [Large-Scale C++ Software Design](https://www.amazon.com/Large-Scale-Software-Design-John-Lakos/dp/0201633620) - 大规模C++软件设计

### 🔧 开发工具
- [CMake](https://cmake.org/) - 构建系统
- [Git](https://git-scm.com/) - 版本控制
- [Doxygen](https://www.doxygen.nl/) - 文档生成
- [Clang-Format](https://clang.llvm.org/docs/ClangFormat.html) - 代码格式化

## 项目：图书管理系统

我们将实现一个完整的图书管理系统，包含以下功能：
- 用户管理（读者、管理员）
- 图书管理（添加、删除、查询、借阅）
- 借阅记录管理
- 数据持久化
- 日志系统
- 配置管理

### 项目结构

```
LibrarySystem/
├── src/
│   ├── core/
│   │   ├── User.hpp
│   │   ├── Book.hpp
│   │   ├── BorrowRecord.hpp
│   │   └── Library.hpp
│   ├── storage/
│   │   ├── Database.hpp
│   │   └── FileStorage.hpp
│   ├── utils/
│   │   ├── Logger.hpp
│   │   ├── Config.hpp
│   │   └── DateTime.hpp
│   ├── ui/
│   │   └── ConsoleUI.hpp
│   └── main.cpp
├── tests/
├── docs/
├── config/
│   └── library.conf
├── data/
└── CMakeLists.txt
```

### 1. 核心数据模型

首先定义系统的核心数据结构：

```cpp
// src/utils/DateTime.hpp
#pragma once
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

class DateTime {
private:
    std::chrono::system_clock::time_point time_point_;
    
public:
    DateTime() : time_point_(std::chrono::system_clock::now()) {}
    
    explicit DateTime(std::chrono::system_clock::time_point tp) : time_point_(tp) {}
    
    static DateTime now() {
        return DateTime{};
    }
    
    static DateTime from_string(const std::string& date_str) {
        std::tm tm = {};
        std::istringstream ss(date_str);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        
        auto time_t = std::mktime(&tm);
        return DateTime{std::chrono::system_clock::from_time_t(time_t)};
    }
    
    std::string to_string() const {
        auto time_t = std::chrono::system_clock::to_time_t(time_point_);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    DateTime add_days(int days) const {
        auto duration = std::chrono::hours(24 * days);
        return DateTime{time_point_ + duration};
    }
    
    std::chrono::system_clock::duration operator-(const DateTime& other) const {
        return time_point_ - other.time_point_;
    }
    
    bool operator<(const DateTime& other) const {
        return time_point_ < other.time_point_;
    }
    
    bool operator>(const DateTime& other) const {
        return time_point_ > other.time_point_;
    }
    
    bool operator==(const DateTime& other) const {
        return time_point_ == other.time_point_;
    }
    
    auto get_time_point() const { return time_point_; }
};
```

```cpp
// src/core/User.hpp
#pragma once
#include <string>
#include <memory>
#include <vector>

enum class UserType {
    READER,
    LIBRARIAN,
    ADMIN
};

class User {
private:
    std::string user_id_;
    std::string name_;
    std::string email_;
    std::string phone_;
    UserType type_;
    bool active_;
    
public:
    User(std::string user_id, std::string name, std::string email, 
         std::string phone, UserType type = UserType::READER)
        : user_id_(std::move(user_id))
        , name_(std::move(name))
        , email_(std::move(email))
        , phone_(std::move(phone))
        , type_(type)
        , active_(true) {}
    
    // Getters
    const std::string& user_id() const { return user_id_; }
    const std::string& name() const { return name_; }
    const std::string& email() const { return email_; }
    const std::string& phone() const { return phone_; }
    UserType type() const { return type_; }
    bool is_active() const { return active_; }
    
    // Setters
    void set_name(std::string name) { name_ = std::move(name); }
    void set_email(std::string email) { email_ = std::move(email); }
    void set_phone(std::string phone) { phone_ = std::move(phone); }
    void set_type(UserType type) { type_ = type; }
    void set_active(bool active) { active_ = active; }
    
    // 权限检查
    bool can_borrow_books() const {
        return active_ && (type_ == UserType::READER || type_ == UserType::LIBRARIAN);
    }
    
    bool can_manage_books() const {
        return active_ && (type_ == UserType::LIBRARIAN || type_ == UserType::ADMIN);
    }
    
    bool can_manage_users() const {
        return active_ && type_ == UserType::ADMIN;
    }
    
    // 序列化支持
    std::string to_string() const {
        return user_id_ + "|" + name_ + "|" + email_ + "|" + phone_ + "|" + 
               std::to_string(static_cast<int>(type_)) + "|" + 
               (active_ ? "1" : "0");
    }
    
    static std::unique_ptr<User> from_string(const std::string& str) {
        std::vector<std::string> parts;
        std::string current;
        
        for (char c : str) {
            if (c == '|') {
                parts.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        parts.push_back(current);
        
        if (parts.size() != 6) return nullptr;
        
        auto user = std::make_unique<User>(
            parts[0], parts[1], parts[2], parts[3],
            static_cast<UserType>(std::stoi(parts[4]))
        );
        user->set_active(parts[5] == "1");
        
        return user;
    }
};
```

```cpp
// src/core/Book.hpp
#pragma once
#include <string>
#include <memory>
#include <vector>

enum class BookStatus {
    AVAILABLE,
    BORROWED,
    RESERVED,
    DAMAGED,
    LOST
};

class Book {
private:
    std::string isbn_;
    std::string title_;
    std::string author_;
    std::string publisher_;
    int year_;
    std::string category_;
    BookStatus status_;
    std::string current_borrower_id_;
    
public:
    Book(std::string isbn, std::string title, std::string author,
         std::string publisher, int year, std::string category)
        : isbn_(std::move(isbn))
        , title_(std::move(title))
        , author_(std::move(author))
        , publisher_(std::move(publisher))
        , year_(year)
        , category_(std::move(category))
        , status_(BookStatus::AVAILABLE) {}
    
    // Getters
    const std::string& isbn() const { return isbn_; }
    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }
    const std::string& publisher() const { return publisher_; }
    int year() const { return year_; }
    const std::string& category() const { return category_; }
    BookStatus status() const { return status_; }
    const std::string& current_borrower_id() const { return current_borrower_id_; }
    
    // Setters
    void set_title(std::string title) { title_ = std::move(title); }
    void set_author(std::string author) { author_ = std::move(author); }
    void set_publisher(std::string publisher) { publisher_ = std::move(publisher); }
    void set_year(int year) { year_ = year; }
    void set_category(std::string category) { category_ = std::move(category); }
    void set_status(BookStatus status) { status_ = status; }
    void set_current_borrower_id(std::string borrower_id) { 
        current_borrower_id_ = std::move(borrower_id); 
    }
    
    // 状态检查
    bool is_available() const {
        return status_ == BookStatus::AVAILABLE;
    }
    
    bool is_borrowed() const {
        return status_ == BookStatus::BORROWED;
    }
    
    // 借阅操作
    bool borrow(const std::string& user_id) {
        if (is_available()) {
            status_ = BookStatus::BORROWED;
            current_borrower_id_ = user_id;
            return true;
        }
        return false;
    }
    
    bool return_book() {
        if (is_borrowed()) {
            status_ = BookStatus::AVAILABLE;
            current_borrower_id_.clear();
            return true;
        }
        return false;
    }
    
    // 序列化支持
    std::string to_string() const {
        return isbn_ + "|" + title_ + "|" + author_ + "|" + publisher_ + "|" +
               std::to_string(year_) + "|" + category_ + "|" +
               std::to_string(static_cast<int>(status_)) + "|" + current_borrower_id_;
    }
    
    static std::unique_ptr<Book> from_string(const std::string& str) {
        std::vector<std::string> parts;
        std::string current;
        
        for (char c : str) {
            if (c == '|') {
                parts.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        parts.push_back(current);
        
        if (parts.size() != 8) return nullptr;
        
        auto book = std::make_unique<Book>(
            parts[0], parts[1], parts[2], parts[3],
            std::stoi(parts[4]), parts[5]
        );
        
        book->set_status(static_cast<BookStatus>(std::stoi(parts[6])));
        if (!parts[7].empty()) {
            book->set_current_borrower_id(parts[7]);
        }
        
        return book;
    }
};
```

```cpp
// src/core/BorrowRecord.hpp
#pragma once
#include "../utils/DateTime.hpp"
#include <string>
#include <memory>
#include <optional>

class BorrowRecord {
private:
    std::string record_id_;
    std::string user_id_;
    std::string isbn_;
    DateTime borrow_date_;
    DateTime due_date_;
    std::optional<DateTime> return_date_;
    double fine_amount_;
    
public:
    BorrowRecord(std::string record_id, std::string user_id, std::string isbn,
                 DateTime borrow_date, DateTime due_date)
        : record_id_(std::move(record_id))
        , user_id_(std::move(user_id))
        , isbn_(std::move(isbn))
        , borrow_date_(borrow_date)
        , due_date_(due_date)
        , fine_amount_(0.0) {}
    
    // Getters
    const std::string& record_id() const { return record_id_; }
    const std::string& user_id() const { return user_id_; }
    const std::string& isbn() const { return isbn_; }
    const DateTime& borrow_date() const { return borrow_date_; }
    const DateTime& due_date() const { return due_date_; }
    const std::optional<DateTime>& return_date() const { return return_date_; }
    double fine_amount() const { return fine_amount_; }
    
    // 状态检查
    bool is_returned() const {
        return return_date_.has_value();
    }
    
    bool is_overdue() const {
        if (is_returned()) {
            return *return_date_ > due_date_;
        }
        return DateTime::now() > due_date_;
    }
    
    int days_overdue() const {
        if (!is_overdue()) return 0;
        
        DateTime check_date = is_returned() ? *return_date_ : DateTime::now();
        auto duration = check_date - due_date_;
        return static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24);
    }
    
    // 归还操作
    void return_book(DateTime return_time = DateTime::now()) {
        return_date_ = return_time;
        
        // 计算罚金（每天1元）
        if (is_overdue()) {
            fine_amount_ = days_overdue() * 1.0;
        }
    }
    
    // 序列化支持
    std::string to_string() const {
        std::string result = record_id_ + "|" + user_id_ + "|" + isbn_ + "|" +
                           borrow_date_.to_string() + "|" + due_date_.to_string() + "|";
        
        if (return_date_) {
            result += return_date_->to_string();
        }
        result += "|" + std::to_string(fine_amount_);
        
        return result;
    }
    
    static std::unique_ptr<BorrowRecord> from_string(const std::string& str) {
        std::vector<std::string> parts;
        std::string current;
        
        for (char c : str) {
            if (c == '|') {
                parts.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        parts.push_back(current);
        
        if (parts.size() != 7) return nullptr;
        
        auto record = std::make_unique<BorrowRecord>(
            parts[0], parts[1], parts[2],
            DateTime::from_string(parts[3]),
            DateTime::from_string(parts[4])
        );
        
        if (!parts[5].empty()) {
            record->return_date_ = DateTime::from_string(parts[5]);
        }
        
        record->fine_amount_ = std::stod(parts[6]);
        
        return record;
    }
};
```

### 2. 存储层设计

实现数据持久化功能：

```cpp
// src/storage/Database.hpp
#pragma once
#include "../core/User.hpp"
#include "../core/Book.hpp"
#include "../core/BorrowRecord.hpp"
#include <vector>
#include <memory>
#include <functional>

class Database {
public:
    virtual ~Database() = default;
    
    // 用户管理
    virtual bool save_user(const User& user) = 0;
    virtual std::unique_ptr<User> load_user(const std::string& user_id) = 0;
    virtual std::vector<std::unique_ptr<User>> load_all_users() = 0;
    virtual bool delete_user(const std::string& user_id) = 0;
    
    // 图书管理
    virtual bool save_book(const Book& book) = 0;
    virtual std::unique_ptr<Book> load_book(const std::string& isbn) = 0;
    virtual std::vector<std::unique_ptr<Book>> load_all_books() = 0;
    virtual bool delete_book(const std::string& isbn) = 0;
    
    // 借阅记录管理
    virtual bool save_borrow_record(const BorrowRecord& record) = 0;
    virtual std::unique_ptr<BorrowRecord> load_borrow_record(const std::string& record_id) = 0;
    virtual std::vector<std::unique_ptr<BorrowRecord>> load_all_borrow_records() = 0;
    virtual std::vector<std::unique_ptr<BorrowRecord>> load_user_borrow_records(const std::string& user_id) = 0;
    virtual bool delete_borrow_record(const std::string& record_id) = 0;
    
    // 搜索功能
    virtual std::vector<std::unique_ptr<Book>> search_books(
        std::function<bool(const Book&)> predicate) = 0;
    virtual std::vector<std::unique_ptr<User>> search_users(
        std::function<bool(const User&)> predicate) = 0;
};
```

```cpp
// src/storage/FileStorage.hpp
#pragma once
#include "Database.hpp"
#include <fstream>
#include <filesystem>
#include <unordered_map>

class FileStorage : public Database {
private:
    std::filesystem::path data_dir_;
    std::filesystem::path users_file_;
    std::filesystem::path books_file_;
    std::filesystem::path records_file_;
    
    // 缓存
    mutable std::unordered_map<std::string, std::unique_ptr<User>> user_cache_;
    mutable std::unordered_map<std::string, std::unique_ptr<Book>> book_cache_;
    mutable std::unordered_map<std::string, std::unique_ptr<BorrowRecord>> record_cache_;
    mutable bool cache_loaded_ = false;
    
    void ensure_data_directory() {
        if (!std::filesystem::exists(data_dir_)) {
            std::filesystem::create_directories(data_dir_);
        }
    }
    
    void load_cache() const {
        if (cache_loaded_) return;
        
        // 加载用户
        if (std::filesystem::exists(users_file_)) {
            std::ifstream file(users_file_);
            std::string line;
            while (std::getline(file, line)) {
                if (auto user = User::from_string(line)) {
                    user_cache_[user->user_id()] = std::move(user);
                }
            }
        }
        
        // 加载图书
        if (std::filesystem::exists(books_file_)) {
            std::ifstream file(books_file_);
            std::string line;
            while (std::getline(file, line)) {
                if (auto book = Book::from_string(line)) {
                    book_cache_[book->isbn()] = std::move(book);
                }
            }
        }
        
        // 加载借阅记录
        if (std::filesystem::exists(records_file_)) {
            std::ifstream file(records_file_);
            std::string line;
            while (std::getline(file, line)) {
                if (auto record = BorrowRecord::from_string(line)) {
                    record_cache_[record->record_id()] = std::move(record);
                }
            }
        }
        
        cache_loaded_ = true;
    }
    
    void save_users_to_file() const {
        std::ofstream file(users_file_);
        for (const auto& [id, user] : user_cache_) {
            file << user->to_string() << '\n';
        }
    }
    
    void save_books_to_file() const {
        std::ofstream file(books_file_);
        for (const auto& [isbn, book] : book_cache_) {
            file << book->to_string() << '\n';
        }
    }
    
    void save_records_to_file() const {
        std::ofstream file(records_file_);
        for (const auto& [id, record] : record_cache_) {
            file << record->to_string() << '\n';
        }
    }
    
public:
    explicit FileStorage(const std::filesystem::path& data_dir = "data")
        : data_dir_(data_dir)
        , users_file_(data_dir / "users.txt")
        , books_file_(data_dir / "books.txt")
        , records_file_(data_dir / "records.txt") {
        ensure_data_directory();
    }
    
    // 用户管理实现
    bool save_user(const User& user) override {
        load_cache();
        user_cache_[user.user_id()] = std::make_unique<User>(user);
        save_users_to_file();
        return true;
    }
    
    std::unique_ptr<User> load_user(const std::string& user_id) override {
        load_cache();
        auto it = user_cache_.find(user_id);
        if (it != user_cache_.end()) {
            return std::make_unique<User>(*it->second);
        }
        return nullptr;
    }
    
    std::vector<std::unique_ptr<User>> load_all_users() override {
        load_cache();
        std::vector<std::unique_ptr<User>> result;
        for (const auto& [id, user] : user_cache_) {
            result.push_back(std::make_unique<User>(*user));
        }
        return result;
    }
    
    bool delete_user(const std::string& user_id) override {
        load_cache();
        if (user_cache_.erase(user_id) > 0) {
            save_users_to_file();
            return true;
        }
        return false;
    }
    
    // 图书管理实现
    bool save_book(const Book& book) override {
        load_cache();
        book_cache_[book.isbn()] = std::make_unique<Book>(book);
        save_books_to_file();
        return true;
    }
    
    std::unique_ptr<Book> load_book(const std::string& isbn) override {
        load_cache();
        auto it = book_cache_.find(isbn);
        if (it != book_cache_.end()) {
            return std::make_unique<Book>(*it->second);
        }
        return nullptr;
    }
    
    std::vector<std::unique_ptr<Book>> load_all_books() override {
        load_cache();
        std::vector<std::unique_ptr<Book>> result;
        for (const auto& [isbn, book] : book_cache_) {
            result.push_back(std::make_unique<Book>(*book));
        }
        return result;
    }
    
    bool delete_book(const std::string& isbn) override {
        load_cache();
        if (book_cache_.erase(isbn) > 0) {
            save_books_to_file();
            return true;
        }
        return false;
    }
    
    // 借阅记录管理实现
    bool save_borrow_record(const BorrowRecord& record) override {
        load_cache();
        record_cache_[record.record_id()] = std::make_unique<BorrowRecord>(record);
        save_records_to_file();
        return true;
    }
    
    std::unique_ptr<BorrowRecord> load_borrow_record(const std::string& record_id) override {
        load_cache();
        auto it = record_cache_.find(record_id);
        if (it != record_cache_.end()) {
            return std::make_unique<BorrowRecord>(*it->second);
        }
        return nullptr;
    }
    
    std::vector<std::unique_ptr<BorrowRecord>> load_all_borrow_records() override {
        load_cache();
        std::vector<std::unique_ptr<BorrowRecord>> result;
        for (const auto& [id, record] : record_cache_) {
            result.push_back(std::make_unique<BorrowRecord>(*record));
        }
        return result;
    }
    
    std::vector<std::unique_ptr<BorrowRecord>> load_user_borrow_records(const std::string& user_id) override {
        load_cache();
        std::vector<std::unique_ptr<BorrowRecord>> result;
        for (const auto& [id, record] : record_cache_) {
            if (record->user_id() == user_id) {
                result.push_back(std::make_unique<BorrowRecord>(*record));
            }
        }
        return result;
    }
    
    bool delete_borrow_record(const std::string& record_id) override {
        load_cache();
        if (record_cache_.erase(record_id) > 0) {
            save_records_to_file();
            return true;
        }
        return false;
    }
    
    // 搜索功能实现
    std::vector<std::unique_ptr<Book>> search_books(
        std::function<bool(const Book&)> predicate) override {
        load_cache();
        std::vector<std::unique_ptr<Book>> result;
        for (const auto& [isbn, book] : book_cache_) {
            if (predicate(*book)) {
                result.push_back(std::make_unique<Book>(*book));
            }
        }
        return result;
    }
    
    std::vector<std::unique_ptr<User>> search_users(
        std::function<bool(const User&)> predicate) override {
        load_cache();
        std::vector<std::unique_ptr<User>> result;
        for (const auto& [id, user] : user_cache_) {
            if (predicate(*user)) {
                result.push_back(std::make_unique<User>(*user));
            }
        }
        return result;
    }
};
```

### 3. 业务逻辑层

实现核心业务逻辑：

```cpp
// src/core/Library.hpp
#pragma once
#include "../storage/Database.hpp"
#include "../utils/Logger.hpp"
#include "../utils/Config.hpp"
#include <memory>
#include <string>
#include <random>
#include <sstream>

class Library {
private:
    std::unique_ptr<Database> database_;
    std::unique_ptr<Logger> logger_;
    std::unique_ptr<Config> config_;
    
    std::string generate_record_id() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(100000, 999999);
        
        std::stringstream ss;
        ss << "REC" << dis(gen);
        return ss.str();
    }
    
public:
    Library(std::unique_ptr<Database> database, 
            std::unique_ptr<Logger> logger,
            std::unique_ptr<Config> config)
        : database_(std::move(database))
        , logger_(std::move(logger))
        , config_(std::move(config)) {
        logger_->info("Library system initialized");
    }
    
    // 用户管理
    bool register_user(const std::string& user_id, const std::string& name,
                      const std::string& email, const std::string& phone,
                      UserType type = UserType::READER) {
        if (database_->load_user(user_id)) {
            logger_->warning("User already exists:", user_id);
            return false;
        }
        
        User user(user_id, name, email, phone, type);
        bool success = database_->save_user(user);
        
        if (success) {
            logger_->info("User registered:", user_id, name);
        } else {
            logger_->error("Failed to register user:", user_id);
        }
        
        return success;
    }
    
    std::unique_ptr<User> get_user(const std::string& user_id) {
        return database_->load_user(user_id);
    }
    
    std::vector<std::unique_ptr<User>> get_all_users() {
        return database_->load_all_users();
    }
    
    bool update_user(const User& user) {
        logger_->info("Updating user:", user.user_id());
        return database_->save_user(user);
    }
    
    bool delete_user(const std::string& user_id) {
        // 检查是否有未归还的书籍
        auto records = database_->load_user_borrow_records(user_id);
        for (const auto& record : records) {
            if (!record->is_returned()) {
                logger_->warning("Cannot delete user with unreturned books:", user_id);
                return false;
            }
        }
        
        bool success = database_->delete_user(user_id);
        if (success) {
            logger_->info("User deleted:", user_id);
        }
        return success;
    }
    
    // 图书管理
    bool add_book(const std::string& isbn, const std::string& title,
                  const std::string& author, const std::string& publisher,
                  int year, const std::string& category) {
        if (database_->load_book(isbn)) {
            logger_->warning("Book already exists:", isbn);
            return false;
        }
        
        Book book(isbn, title, author, publisher, year, category);
        bool success = database_->save_book(book);
        
        if (success) {
            logger_->info("Book added:", isbn, title);
        } else {
            logger_->error("Failed to add book:", isbn);
        }
        
        return success;
    }
    
    std::unique_ptr<Book> get_book(const std::string& isbn) {
        return database_->load_book(isbn);
    }
    
    std::vector<std::unique_ptr<Book>> get_all_books() {
        return database_->load_all_books();
    }
    
    std::vector<std::unique_ptr<Book>> search_books_by_title(const std::string& title) {
        return database_->search_books([&title](const Book& book) {
            return book.title().find(title) != std::string::npos;
        });
    }
    
    std::vector<std::unique_ptr<Book>> search_books_by_author(const std::string& author) {
        return database_->search_books([&author](const Book& book) {
            return book.author().find(author) != std::string::npos;
        });
    }
    
    std::vector<std::unique_ptr<Book>> search_books_by_category(const std::string& category) {
        return database_->search_books([&category](const Book& book) {
            return book.category() == category;
        });
    }
    
    bool update_book(const Book& book) {
        logger_->info("Updating book:", book.isbn());
        return database_->save_book(book);
    }
    
    bool delete_book(const std::string& isbn) {
        auto book = database_->load_book(isbn);
        if (!book) {
            return false;
        }
        
        if (book->is_borrowed()) {
            logger_->warning("Cannot delete borrowed book:", isbn);
            return false;
        }
        
        bool success = database_->delete_book(isbn);
        if (success) {
            logger_->info("Book deleted:", isbn);
        }
        return success;
    }
    
    // 借阅管理
    bool borrow_book(const std::string& user_id, const std::string& isbn) {
        auto user = database_->load_user(user_id);
        if (!user || !user->can_borrow_books()) {
            logger_->warning("User cannot borrow books:", user_id);
            return false;
        }
        
        auto book = database_->load_book(isbn);
        if (!book || !book->is_available()) {
            logger_->warning("Book not available for borrowing:", isbn);
            return false;
        }
        
        // 检查用户是否已达到借阅限制
        auto user_records = database_->load_user_borrow_records(user_id);
        int active_borrows = 0;
        for (const auto& record : user_records) {
            if (!record->is_returned()) {
                active_borrows++;
            }
        }
        
        int max_borrows = config_->get_int("max_books_per_user", 5);
        if (active_borrows >= max_borrows) {
            logger_->warning("User has reached borrowing limit:", user_id);
            return false;
        }
        
        // 创建借阅记录
        std::string record_id = generate_record_id();
        DateTime borrow_date = DateTime::now();
        int borrow_days = config_->get_int("default_borrow_days", 14);
        DateTime due_date = borrow_date.add_days(borrow_days);
        
        BorrowRecord record(record_id, user_id, isbn, borrow_date, due_date);
        
        // 更新图书状态
        book->borrow(user_id);
        
        // 保存更改
        bool record_saved = database_->save_borrow_record(record);
        bool book_updated = database_->save_book(*book);
        
        if (record_saved && book_updated) {
            logger_->info("Book borrowed:", user_id, isbn, "due:", due_date.to_string());
            return true;
        } else {
            logger_->error("Failed to complete borrowing:", user_id, isbn);
            return false;
        }
    }
    
    bool return_book(const std::string& user_id, const std::string& isbn) {
        // 查找活跃的借阅记录
        auto user_records = database_->load_user_borrow_records(user_id);
        BorrowRecord* active_record = nullptr;
        
        for (const auto& record : user_records) {
            if (record->isbn() == isbn && !record->is_returned()) {
                active_record = record.get();
                break;
            }
        }
        
        if (!active_record) {
            logger_->warning("No active borrow record found:", user_id, isbn);
            return false;
        }
        
        auto book = database_->load_book(isbn);
        if (!book || !book->is_borrowed()) {
            logger_->warning("Book is not currently borrowed:", isbn);
            return false;
        }
        
        // 处理归还
        active_record->return_book();
        book->return_book();
        
        // 保存更改
        bool record_updated = database_->save_borrow_record(*active_record);
        bool book_updated = database_->save_book(*book);
        
        if (record_updated && book_updated) {
            if (active_record->is_overdue()) {
                logger_->info("Book returned (overdue):", user_id, isbn, 
                             "fine:", active_record->fine_amount());
            } else {
                logger_->info("Book returned:", user_id, isbn);
            }
            return true;
        } else {
            logger_->error("Failed to complete return:", user_id, isbn);
            return false;
        }
    }
    
    std::vector<std::unique_ptr<BorrowRecord>> get_user_borrow_history(const std::string& user_id) {
        return database_->load_user_borrow_records(user_id);
    }
    
    std::vector<std::unique_ptr<BorrowRecord>> get_overdue_books() {
        auto all_records = database_->load_all_borrow_records();
        std::vector<std::unique_ptr<BorrowRecord>> overdue;
        
        for (auto& record : all_records) {
            if (!record->is_returned() && record->is_overdue()) {
                overdue.push_back(std::move(record));
            }
        }
        
        return overdue;
    }
    
    // 统计信息
    struct LibraryStats {
        int total_books = 0;
        int available_books = 0;
        int borrowed_books = 0;
        int total_users = 0;
        int active_users = 0;
        int overdue_books = 0;
        double total_fines = 0.0;
    };
    
    LibraryStats get_statistics() {
        LibraryStats stats;
        
        auto books = database_->load_all_books();
        stats.total_books = static_cast<int>(books.size());
        for (const auto& book : books) {
            if (book->is_available()) {
                stats.available_books++;
            } else if (book->is_borrowed()) {
                stats.borrowed_books++;
            }
        }
        
        auto users = database_->load_all_users();
        stats.total_users = static_cast<int>(users.size());
        for (const auto& user : users) {
            if (user->is_active()) {
                stats.active_users++;
            }
        }
        
        auto records = database_->load_all_borrow_records();
        for (const auto& record : records) {
            if (!record->is_returned() && record->is_overdue()) {
                stats.overdue_books++;
            }
            stats.total_fines += record->fine_amount();
        }
        
        return stats;
    }
};
```

### 4. 工具类实现

```cpp
// src/utils/Logger.hpp
#pragma once
#include "DateTime.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger {
private:
    std::ofstream file_;
    LogLevel min_level_;
    std::mutex mutex_;
    
    std::string level_to_string(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
    
public:
    Logger(const std::string& filename, LogLevel min_level = LogLevel::INFO)
        : file_(filename, std::ios::app), min_level_(min_level) {}
    
    template<typename... Args>
    void log(LogLevel level, Args&&... args) {
        if (level < min_level_) return;
        
        std::lock_guard<std::mutex> lock(mutex_);
        
        std::stringstream ss;
        ss << "[" << DateTime::now().to_string() << "] "
           << "[" << level_to_string(level) << "] ";
        
        ((ss << args << " "), ...);
        
        std::string message = ss.str();
        file_ << message << std::endl;
        std::cout << message << std::endl;
    }
    
    template<typename... Args>
    void debug(Args&&... args) {
        log(LogLevel::DEBUG, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void info(Args&&... args) {
        log(LogLevel::INFO, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void warning(Args&&... args) {
        log(LogLevel::WARNING, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void error(Args&&... args) {
        log(LogLevel::ERROR, std::forward<Args>(args)...);
    }
};
```

```cpp
// src/utils/Config.hpp
#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

class Config {
private:
    std::unordered_map<std::string, std::string> config_map_;
    
public:
    explicit Config(const std::string& config_file = "config/library.conf") {
        load_from_file(config_file);
    }
    
    void load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        
        while (std::getline(file, line)) {
            // 跳过注释和空行
            if (line.empty() || line[0] == '#') continue;
            
            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                // 去除空格
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                config_map_[key] = value;
            }
        }
    }
    
    std::string get_string(const std::string& key, const std::string& default_value = "") {
        auto it = config_map_.find(key);
        return it != config_map_.end() ? it->second : default_value;
    }
    
    int get_int(const std::string& key, int default_value = 0) {
        auto it = config_map_.find(key);
        if (it != config_map_.end()) {
            try {
                return std::stoi(it->second);
            } catch (...) {
                return default_value;
            }
        }
        return default_value;
    }
    
    double get_double(const std::string& key, double default_value = 0.0) {
        auto it = config_map_.find(key);
        if (it != config_map_.end()) {
            try {
                return std::stod(it->second);
            } catch (...) {
                return default_value;
            }
        }
        return default_value;
    }
    
    bool get_bool(const std::string& key, bool default_value = false) {
        auto it = config_map_.find(key);
        if (it != config_map_.end()) {
            std::string value = it->second;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            return value == "true" || value == "1" || value == "yes";
        }
        return default_value;
    }
    
    void set(const std::string& key, const std::string& value) {
        config_map_[key] = value;
    }
};
```

## 实践练习

### 练习1：扩展功能
为系统添加更多功能：
- 图书预约系统
- 用户积分系统
- 图书推荐算法
- 多语言支持

### 练习2：性能优化
优化系统性能：
- 实现数据库索引
- 添加缓存机制
- 并发访问支持
- 内存使用优化

### 练习3：用户界面
实现更好的用户界面：
- Web界面
- GUI应用
- REST API
- 移动应用支持

### 练习4：系统扩展
扩展系统架构：
- 微服务架构
- 分布式部署
- 数据备份和恢复
- 监控和日志分析

## 今日总结
通过完成这个综合项目，你应该掌握：
1. 系统架构设计和模块化编程
2. 面向对象设计原则的实际应用
3. 现代C++特性在实际项目中的使用
4. 错误处理和日志系统的设计
5. 数据持久化和文件操作
6. 项目组织和代码管理

## 课程总结
经过28天的系统学习，你已经：
1. 掌握了C++语言的核心特性和现代语法
2. 理解了面向对象编程的设计思想
3. 学会了STL和现代C++库的使用
4. 掌握了设计模式和软件架构
5. 具备了独立设计和实现C++项目的能力

继续保持学习的热情，在实际项目中不断提升你的C++技能！

[返回第四周](/plan/week4/) | [上一天：第27天](/plan/week4/day27/) | [返回主页](/plan/)
