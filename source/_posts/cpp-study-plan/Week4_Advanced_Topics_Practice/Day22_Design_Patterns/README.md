# 第22天：设计模式

## 学习目标
掌握常用的设计模式，理解面向对象设计的最佳实践，学会在实际项目中应用设计模式来解决常见问题。

## 今日学习内容

### 1. 单例模式 (Singleton Pattern)
**概念：** 确保一个类只有一个实例，并提供一个全局访问点。

**应用场景：**
- 日志管理器
- 数据库连接池
- 配置管理器
- 缓存管理器

**实现要点：**
- 私有构造函数
- 静态实例变量
- 静态获取实例方法
- 线程安全考虑

**示例代码：**
```cpp
// 懒汉式单例（线程安全版本）
class Logger {
private:
    static std::mutex mtx;
    static std::unique_ptr<Logger> instance;
    std::ofstream logFile;
    
    Logger() { 
        logFile.open("app.log", std::ios::app); 
    }
    
public:
    static Logger& getInstance() {
        std::call_once(flag, []() {
            instance = std::make_unique<Logger>();
        });
        return *instance;
    }
    
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logFile << getCurrentTime() << ": " << message << std::endl;
    }
    
    // 禁止拷贝和赋值
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
private:
    static std::once_flag flag;
    std::string getCurrentTime() const;
};
```

### 2. 工厂模式 (Factory Pattern)
**概念：** 创建对象时不指定具体类，而是通过工厂方法来创建对象。

**应用场景：**
- 创建复杂对象
- 根据配置创建不同类型的对象
- 隐藏对象创建的复杂性

**示例代码：**
```cpp
// 抽象产品
class Shape {
public:
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

// 具体产品
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    void draw() const override {
        std::cout << "Drawing Circle with radius: " << radius << std::endl;
    }
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    void draw() const override {
        std::cout << "Drawing Rectangle: " << width << "x" << height << std::endl;
    }
    double area() const override {
        return width * height;
    }
};

// 工厂类
class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type, 
                                              const std::vector<double>& params) {
        if (type == "circle" && params.size() == 1) {
            return std::make_unique<Circle>(params[0]);
        } else if (type == "rectangle" && params.size() == 2) {
            return std::make_unique<Rectangle>(params[0], params[1]);
        }
        return nullptr;
    }
};
```

### 3. 观察者模式 (Observer Pattern)
**概念：** 定义对象间一对多的依赖关系，当一个对象状态改变时，所有依赖它的对象都会得到通知。

**应用场景：**
- 事件处理系统
- MVC架构
- 发布-订阅系统

**示例代码：**
```cpp
// 观察者接口
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// 被观察者（主题）
class Subject {
private:
    std::vector<Observer*> observers;
    std::string state;
    
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer),
                       observers.end());
    }
    
    void notify() {
        for (auto observer : observers) {
            observer->update(state);
        }
    }
    
    void setState(const std::string& newState) {
        state = newState;
        notify();
    }
    
    std::string getState() const { return state; }
};

// 具体观察者
class ConcreteObserver : public Observer {
private:
    std::string name;
    
public:
    ConcreteObserver(const std::string& n) : name(n) {}
    
    void update(const std::string& message) override {
        std::cout << "Observer " << name << " received: " << message << std::endl;
    }
};
```

### 4. 策略模式 (Strategy Pattern)
**概念：** 定义一系列算法，把它们封装起来，并且使它们可互换。

**应用场景：**
- 排序算法选择
- 支付方式选择
- 压缩算法选择

**示例代码：**
```cpp
// 策略接口
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

// 具体策略
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        size_t n = data.size();
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
        std::cout << "Used Bubble Sort" << std::endl;
    }
};

class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.begin(), data.end());
        std::cout << "Used Quick Sort" << std::endl;
    }
};

// 上下文类
class SortContext {
private:
    std::unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(std::unique_ptr<SortStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    
    void executeSort(std::vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        }
    }
};
```

### 5. RAII模式 (Resource Acquisition Is Initialization)
**概念：** 利用对象的构造和析构来管理资源的获取和释放。

**应用场景：**
- 内存管理
- 文件操作
- 锁管理
- 数据库连接

**示例代码：**
```cpp
// RAII文件管理
class FileManager {
private:
    std::FILE* file;
    std::string filename;
    
public:
    FileManager(const std::string& name, const std::string& mode) 
        : filename(name) {
        file = std::fopen(name.c_str(), mode.c_str());
        if (!file) {
            throw std::runtime_error("Failed to open file: " + name);
        }
    }
    
    ~FileManager() {
        if (file) {
            std::fclose(file);
            std::cout << "File " << filename << " closed automatically" << std::endl;
        }
    }
    
    // 禁止拷贝，允许移动
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    FileManager(FileManager&& other) noexcept 
        : file(other.file), filename(std::move(other.filename)) {
        other.file = nullptr;
    }
    
    FileManager& operator=(FileManager&& other) noexcept {
        if (this != &other) {
            if (file) {
                std::fclose(file);
            }
            file = other.file;
            filename = std::move(other.filename);
            other.file = nullptr;
        }
        return *this;
    }
    
    void write(const std::string& data) {
        if (file) {
            std::fwrite(data.c_str(), 1, data.length(), file);
        }
    }
    
    std::string read() {
        if (!file) return "";
        
        std::fseek(file, 0, SEEK_END);
        long size = std::ftell(file);
        std::fseek(file, 0, SEEK_SET);
        
        std::string content(size, '\0');
        std::fread(&content[0], 1, size, file);
        return content;
    }
};
```

## 实践练习

### 练习1：实现一个线程安全的单例配置管理器
```cpp
class ConfigManager {
    // 实现一个线程安全的单例模式
    // 支持读取和设置配置项
    // 支持从文件加载配置
};
```

### 练习2：使用工厂模式创建不同类型的数据库连接
```cpp
class DatabaseConnection {
    // 抽象数据库连接类
};

class MySQLConnection : public DatabaseConnection {
    // MySQL连接实现
};

class PostgreSQLConnection : public DatabaseConnection {
    // PostgreSQL连接实现
};

class DatabaseFactory {
    // 工厂类，根据配置创建不同类型的数据库连接
};
```

### 练习3：实现一个事件系统（观察者模式）
```cpp
class EventSystem {
    // 实现事件的注册、注销和触发
    // 支持不同类型的事件
    // 支持事件优先级
};
```

## 重点总结

1. **设计模式的本质**：解决软件设计中的常见问题
2. **单例模式**：全局唯一实例，注意线程安全
3. **工厂模式**：封装对象创建逻辑，降低耦合度
4. **观察者模式**：实现松耦合的事件通知机制
5. **策略模式**：算法的封装和互换
6. **RAII模式**：自动资源管理，异常安全

## 注意事项

1. **不要过度设计**：只在需要时使用设计模式
2. **理解问题本质**：选择合适的设计模式
3. **考虑性能影响**：有些模式可能引入额外开销
4. **保持代码简洁**：设计模式应该简化而不是复杂化代码
5. **线程安全**：在多线程环境中要特别注意

## 拓展阅读

- 《设计模式：可复用面向对象软件的基础》
- 《Head First 设计模式》
- 《Effective C++》中的相关条款
- C++核心准则中的设计模式部分
