/**
 * 第22天：设计模式 - 实践练习
 * 
 * 本文件包含设计模式的实际应用练习
 * 编译命令: g++ -std=c++17 -pthread -o practice_exercises practice_exercises.cpp
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <mutex>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>

// =============================================================================
// 练习1：线程安全的单例配置管理器
// =============================================================================

class ConfigManager {
private:
    static std::unique_ptr<ConfigManager> instance;
    static std::mutex mtx;
    static std::once_flag initialized;
    
    std::map<std::string, std::string> config;
    mutable std::shared_mutex configMutex;
    std::string configFile;
    
    // 私有构造函数
    ConfigManager(const std::string& filename = "config.txt") 
        : configFile(filename) {
        loadFromFile();
    }
    
    void loadFromFile() {
        std::ifstream file(configFile);
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                config[key] = value;
            }
        }
    }
    
    void saveToFile() {
        std::ofstream file(configFile);
        for (const auto& [key, value] : config) {
            file << key << "=" << value << std::endl;
        }
    }
    
public:
    // 获取单例实例
    static ConfigManager& getInstance() {
        std::call_once(initialized, []() {
            instance = std::unique_ptr<ConfigManager>(new ConfigManager());
        });
        return *instance;
    }
    
    // 获取配置项
    std::string get(const std::string& key, const std::string& defaultValue = "") const {
        std::shared_lock<std::shared_mutex> lock(configMutex);
        auto it = config.find(key);
        return (it != config.end()) ? it->second : defaultValue;
    }
    
    // 设置配置项
    void set(const std::string& key, const std::string& value) {
        std::unique_lock<std::shared_mutex> lock(configMutex);
        config[key] = value;
        saveToFile();
    }
    
    // 获取所有配置
    std::map<std::string, std::string> getAll() const {
        std::shared_lock<std::shared_mutex> lock(configMutex);
        return config;
    }
    
    // 禁止拷贝和赋值
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
};

// 静态成员定义
std::unique_ptr<ConfigManager> ConfigManager::instance = nullptr;
std::mutex ConfigManager::mtx;
std::once_flag ConfigManager::initialized;

// =============================================================================
// 练习2：工厂模式 - 数据库连接
// =============================================================================

// 抽象数据库连接
class DatabaseConnection {
public:
    virtual ~DatabaseConnection() = default;
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool execute(const std::string& query) = 0;
    virtual std::string getConnectionInfo() const = 0;
};

// MySQL连接实现
class MySQLConnection : public DatabaseConnection {
private:
    std::string host, username, password, database;
    bool connected = false;
    
public:
    MySQLConnection(const std::string& h, const std::string& u, 
                   const std::string& p, const std::string& db)
        : host(h), username(u), password(p), database(db) {}
    
    bool connect() override {
        std::cout << "Connecting to MySQL: " << host << "/" << database << std::endl;
        // 模拟连接过程
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        connected = true;
        return true;
    }
    
    void disconnect() override {
        if (connected) {
            std::cout << "Disconnecting from MySQL" << std::endl;
            connected = false;
        }
    }
    
    bool execute(const std::string& query) override {
        if (!connected) return false;
        std::cout << "MySQL executing: " << query << std::endl;
        return true;
    }
    
    std::string getConnectionInfo() const override {
        return "MySQL Connection to " + host + "/" + database;
    }
    
    ~MySQLConnection() {
        disconnect();
    }
};

// PostgreSQL连接实现
class PostgreSQLConnection : public DatabaseConnection {
private:
    std::string connectionString;
    bool connected = false;
    
public:
    PostgreSQLConnection(const std::string& connStr) 
        : connectionString(connStr) {}
    
    bool connect() override {
        std::cout << "Connecting to PostgreSQL: " << connectionString << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        connected = true;
        return true;
    }
    
    void disconnect() override {
        if (connected) {
            std::cout << "Disconnecting from PostgreSQL" << std::endl;
            connected = false;
        }
    }
    
    bool execute(const std::string& query) override {
        if (!connected) return false;
        std::cout << "PostgreSQL executing: " << query << std::endl;
        return true;
    }
    
    std::string getConnectionInfo() const override {
        return "PostgreSQL Connection: " + connectionString;
    }
    
    ~PostgreSQLConnection() {
        disconnect();
    }
};

// SQLite连接实现
class SQLiteConnection : public DatabaseConnection {
private:
    std::string dbFile;
    bool connected = false;
    
public:
    SQLiteConnection(const std::string& file) : dbFile(file) {}
    
    bool connect() override {
        std::cout << "Opening SQLite database: " << dbFile << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        connected = true;
        return true;
    }
    
    void disconnect() override {
        if (connected) {
            std::cout << "Closing SQLite database" << std::endl;
            connected = false;
        }
    }
    
    bool execute(const std::string& query) override {
        if (!connected) return false;
        std::cout << "SQLite executing: " << query << std::endl;
        return true;
    }
    
    std::string getConnectionInfo() const override {
        return "SQLite Database: " + dbFile;
    }
    
    ~SQLiteConnection() {
        disconnect();
    }
};

// 数据库工厂
class DatabaseFactory {
public:
    enum class DatabaseType {
        MYSQL,
        POSTGRESQL,
        SQLITE
    };
    
    static std::unique_ptr<DatabaseConnection> createConnection(
        DatabaseType type, const std::map<std::string, std::string>& config) {
        
        switch (type) {
            case DatabaseType::MYSQL:
                return std::make_unique<MySQLConnection>(
                    config.at("host"), config.at("username"), 
                    config.at("password"), config.at("database"));
                    
            case DatabaseType::POSTGRESQL:
                return std::make_unique<PostgreSQLConnection>(
                    config.at("connection_string"));
                    
            case DatabaseType::SQLITE:
                return std::make_unique<SQLiteConnection>(
                    config.at("database_file"));
                    
            default:
                throw std::invalid_argument("Unsupported database type");
        }
    }
    
    // 从配置创建连接
    static std::unique_ptr<DatabaseConnection> createFromConfig(
        const std::string& configKey) {
        
        auto& config = ConfigManager::getInstance();
        std::string dbType = config.get(configKey + ".type");
        
        std::map<std::string, std::string> dbConfig;
        if (dbType == "mysql") {
            dbConfig["host"] = config.get(configKey + ".host");
            dbConfig["username"] = config.get(configKey + ".username");
            dbConfig["password"] = config.get(configKey + ".password");
            dbConfig["database"] = config.get(configKey + ".database");
            return createConnection(DatabaseType::MYSQL, dbConfig);
        } else if (dbType == "postgresql") {
            dbConfig["connection_string"] = config.get(configKey + ".connection_string");
            return createConnection(DatabaseType::POSTGRESQL, dbConfig);
        } else if (dbType == "sqlite") {
            dbConfig["database_file"] = config.get(configKey + ".database_file");
            return createConnection(DatabaseType::SQLITE, dbConfig);
        }
        
        throw std::invalid_argument("Unknown database type: " + dbType);
    }
};

// =============================================================================
// 练习3：观察者模式 - 事件系统
// =============================================================================

// 事件数据基类
class EventData {
public:
    virtual ~EventData() = default;
    virtual std::string getType() const = 0;
};

// 具体事件类型
class UserLoginEvent : public EventData {
private:
    std::string username;
    std::chrono::system_clock::time_point timestamp;
    
public:
    UserLoginEvent(const std::string& user) 
        : username(user), timestamp(std::chrono::system_clock::now()) {}
    
    std::string getType() const override { return "UserLogin"; }
    std::string getUsername() const { return username; }
    auto getTimestamp() const { return timestamp; }
};

class FileUploadEvent : public EventData {
private:
    std::string filename;
    size_t fileSize;
    
public:
    FileUploadEvent(const std::string& name, size_t size) 
        : filename(name), fileSize(size) {}
    
    std::string getType() const override { return "FileUpload"; }
    std::string getFilename() const { return filename; }
    size_t getFileSize() const { return fileSize; }
};

// 事件监听器接口
class EventListener {
public:
    virtual ~EventListener() = default;
    virtual void onEvent(const std::shared_ptr<EventData>& event) = 0;
    virtual std::string getListenerName() const = 0;
};

// 具体监听器实现
class LoggingListener : public EventListener {
public:
    void onEvent(const std::shared_ptr<EventData>& event) override {
        std::cout << "[LOG] Event received: " << event->getType() << std::endl;
    }
    
    std::string getListenerName() const override { return "LoggingListener"; }
};

class SecurityListener : public EventListener {
public:
    void onEvent(const std::shared_ptr<EventData>& event) override {
        if (event->getType() == "UserLogin") {
            auto loginEvent = std::dynamic_pointer_cast<UserLoginEvent>(event);
            if (loginEvent) {
                std::cout << "[SECURITY] User login detected: " 
                         << loginEvent->getUsername() << std::endl;
            }
        }
    }
    
    std::string getListenerName() const override { return "SecurityListener"; }
};

class MetricsListener : public EventListener {
private:
    std::map<std::string, int> eventCounts;
    
public:
    void onEvent(const std::shared_ptr<EventData>& event) override {
        eventCounts[event->getType()]++;
        std::cout << "[METRICS] " << event->getType() 
                 << " count: " << eventCounts[event->getType()] << std::endl;
    }
    
    std::string getListenerName() const override { return "MetricsListener"; }
    
    std::map<std::string, int> getEventCounts() const { return eventCounts; }
};

// 事件系统
class EventSystem {
private:
    std::map<std::string, std::vector<std::weak_ptr<EventListener>>> listeners;
    std::mutex listenersMutex;
    
    // 清理失效的监听器
    void cleanupListeners(const std::string& eventType) {
        auto& eventListeners = listeners[eventType];
        eventListeners.erase(
            std::remove_if(eventListeners.begin(), eventListeners.end(),
                [](const std::weak_ptr<EventListener>& listener) {
                    return listener.expired();
                }),
            eventListeners.end());
    }
    
public:
    // 注册事件监听器
    void subscribe(const std::string& eventType, 
                  std::shared_ptr<EventListener> listener) {
        std::lock_guard<std::mutex> lock(listenersMutex);
        listeners[eventType].push_back(listener);
        std::cout << "Subscribed " << listener->getListenerName() 
                 << " to " << eventType << " events" << std::endl;
    }
    
    // 注销事件监听器
    void unsubscribe(const std::string& eventType, 
                    std::shared_ptr<EventListener> listener) {
        std::lock_guard<std::mutex> lock(listenersMutex);
        auto& eventListeners = listeners[eventType];
        eventListeners.erase(
            std::remove_if(eventListeners.begin(), eventListeners.end(),
                [&listener](const std::weak_ptr<EventListener>& weakListener) {
                    auto sharedListener = weakListener.lock();
                    return sharedListener && sharedListener == listener;
                }),
            eventListeners.end());
        std::cout << "Unsubscribed " << listener->getListenerName() 
                 << " from " << eventType << " events" << std::endl;
    }
    
    // 发布事件
    void publish(std::shared_ptr<EventData> event) {
        std::lock_guard<std::mutex> lock(listenersMutex);
        const std::string eventType = event->getType();
        
        cleanupListeners(eventType);
        
        for (auto& weakListener : listeners[eventType]) {
            if (auto listener = weakListener.lock()) {
                try {
                    listener->onEvent(event);
                } catch (const std::exception& e) {
                    std::cerr << "Error in event listener: " << e.what() << std::endl;
                }
            }
        }
    }
    
    // 获取监听器数量
    size_t getListenerCount(const std::string& eventType) {
        std::lock_guard<std::mutex> lock(listenersMutex);
        cleanupListeners(eventType);
        return listeners[eventType].size();
    }
};

// =============================================================================
// 测试函数
// =============================================================================

void testConfigManager() {
    std::cout << "\n=== Testing ConfigManager (Singleton Pattern) ===\n";
    
    auto& config1 = ConfigManager::getInstance();
    auto& config2 = ConfigManager::getInstance();
    
    // 验证是否为同一实例
    std::cout << "Same instance: " << (&config1 == &config2) << std::endl;
    
    // 设置和获取配置
    config1.set("database.host", "localhost");
    config1.set("database.port", "3306");
    config1.set("app.name", "TestApp");
    
    std::cout << "Database host: " << config2.get("database.host") << std::endl;
    std::cout << "Database port: " << config2.get("database.port") << std::endl;
    std::cout << "App name: " << config2.get("app.name") << std::endl;
}

void testDatabaseFactory() {
    std::cout << "\n=== Testing DatabaseFactory (Factory Pattern) ===\n";
    
    // 设置配置
    auto& config = ConfigManager::getInstance();
    config.set("primary_db.type", "mysql");
    config.set("primary_db.host", "localhost");
    config.set("primary_db.username", "root");
    config.set("primary_db.password", "password");
    config.set("primary_db.database", "testdb");
    
    config.set("cache_db.type", "sqlite");
    config.set("cache_db.database_file", "cache.db");
    
    // 使用工厂创建连接
    try {
        auto mysqlConn = DatabaseFactory::createFromConfig("primary_db");
        auto sqliteConn = DatabaseFactory::createFromConfig("cache_db");
        
        std::cout << mysqlConn->getConnectionInfo() << std::endl;
        std::cout << sqliteConn->getConnectionInfo() << std::endl;
        
        mysqlConn->connect();
        mysqlConn->execute("SELECT * FROM users");
        
        sqliteConn->connect();
        sqliteConn->execute("CREATE TABLE cache (key TEXT, value TEXT)");
        
    } catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << std::endl;
    }
}

void testEventSystem() {
    std::cout << "\n=== Testing EventSystem (Observer Pattern) ===\n";
    
    EventSystem eventSystem;
    
    // 创建监听器
    auto loggingListener = std::make_shared<LoggingListener>();
    auto securityListener = std::make_shared<SecurityListener>();
    auto metricsListener = std::make_shared<MetricsListener>();
    
    // 注册监听器
    eventSystem.subscribe("UserLogin", loggingListener);
    eventSystem.subscribe("UserLogin", securityListener);
    eventSystem.subscribe("UserLogin", metricsListener);
    eventSystem.subscribe("FileUpload", loggingListener);
    eventSystem.subscribe("FileUpload", metricsListener);
    
    // 发布事件
    eventSystem.publish(std::make_shared<UserLoginEvent>("alice"));
    eventSystem.publish(std::make_shared<UserLoginEvent>("bob"));
    eventSystem.publish(std::make_shared<FileUploadEvent>("document.pdf", 1024000));
    eventSystem.publish(std::make_shared<UserLoginEvent>("charlie"));
    
    std::cout << "UserLogin listeners: " 
              << eventSystem.getListenerCount("UserLogin") << std::endl;
    std::cout << "FileUpload listeners: " 
              << eventSystem.getListenerCount("FileUpload") << std::endl;
    
    // 注销监听器测试
    eventSystem.unsubscribe("UserLogin", securityListener);
    eventSystem.publish(std::make_shared<UserLoginEvent>("dave"));
}

// =============================================================================
// 主函数
// =============================================================================

int main() {
    std::cout << "=== C++ Design Patterns Practice ===\n";
    
    try {
        testConfigManager();
        testDatabaseFactory();
        testEventSystem();
        
        std::cout << "\n=== All tests completed successfully! ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
编译和运行说明：

1. 编译命令：
   g++ -std=c++17 -pthread -o practice_exercises practice_exercises.cpp

2. 运行：
   ./practice_exercises

3. 预期输出：
   - 单例模式验证
   - 工厂模式创建不同数据库连接
   - 观察者模式事件发布和监听

4. 学习重点：
   - 单例模式的线程安全实现
   - 工厂模式的灵活对象创建
   - 观察者模式的事件驱动架构
   - RAII模式的资源管理
   - 智能指针的正确使用

5. 扩展练习：
   - 添加更多数据库类型支持
   - 实现事件优先级机制
   - 添加异步事件处理
   - 实现配置热重载功能
*/
