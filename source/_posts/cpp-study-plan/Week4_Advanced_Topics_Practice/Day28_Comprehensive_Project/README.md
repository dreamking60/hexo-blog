# 第28天：综合项目 - 小型系统设计

## 学习目标
综合运用前面学到的所有知识，设计并实现一个完整的小型系统，展示系统架构设计、模块化编程、错误处理、性能优化等综合能力。

## 项目概述：分布式任务调度系统

我们将实现一个分布式任务调度系统，包含以下核心功能：
- 任务提交和管理
- 任务调度和执行
- 负载均衡
- 故障恢复
- 监控和日志
- 配置管理

## 系统架构设计

### 1. 整体架构
```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Client API    │    │   Web Dashboard │    │   Monitoring    │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         └───────────────────────┼───────────────────────┘
                                 │
                    ┌─────────────────┐
                    │  API Gateway    │
                    └─────────────────┘
                                 │
                    ┌─────────────────┐
                    │ Task Scheduler  │
                    └─────────────────┘
                                 │
         ┌───────────────────────┼───────────────────────┐
         │                       │                       │
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Worker Node   │    │   Worker Node   │    │   Worker Node   │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### 2. 核心组件设计

#### 任务定义系统
```cpp
#include <string>
#include <chrono>
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

// 任务优先级
enum class TaskPriority {
    LOW = 0,
    NORMAL = 1,
    HIGH = 2,
    CRITICAL = 3
};

// 任务状态
enum class TaskStatus {
    PENDING,
    RUNNING,
    COMPLETED,
    FAILED,
    CANCELLED
};

// 任务类型
enum class TaskType {
    CPU_INTENSIVE,
    IO_INTENSIVE,
    NETWORK_INTENSIVE,
    MEMORY_INTENSIVE
};

// 任务元数据
struct TaskMetadata {
    std::string task_id;
    std::string task_name;
    TaskType type;
    TaskPriority priority;
    std::chrono::system_clock::time_point submit_time;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::chrono::milliseconds timeout;
    int max_retries;
    int current_retries;
    std::string worker_id;
    std::unordered_map<std::string, std::string> parameters;
    
    TaskMetadata() : current_retries(0), max_retries(3) {}
};

// 任务结果
struct TaskResult {
    std::string task_id;
    TaskStatus status;
    std::string result_data;
    std::string error_message;
    std::chrono::milliseconds execution_time;
    std::unordered_map<std::string, std::string> metrics;
};

// 任务接口
class ITask {
public:
    virtual ~ITask() = default;
    virtual TaskResult execute(const TaskMetadata& metadata) = 0;
    virtual std::string getTaskType() const = 0;
    virtual bool canRetry() const = 0;
};

// 具体任务实现基类
class Task : public ITask {
protected:
    TaskMetadata metadata_;
    
public:
    Task(const TaskMetadata& metadata) : metadata_(metadata) {}
    
    const TaskMetadata& getMetadata() const { return metadata_; }
    void updateMetadata(const TaskMetadata& metadata) { metadata_ = metadata; }
    
    bool canRetry() const override {
        return metadata_.current_retries < metadata_.max_retries;
    }
};

// CPU密集型任务示例
class CPUIntensiveTask : public Task {
private:
    std::function<std::string(const std::unordered_map<std::string, std::string>&)> computation_;
    
public:
    CPUIntensiveTask(const TaskMetadata& metadata,
                    std::function<std::string(const std::unordered_map<std::string, std::string>&)> comp)
        : Task(metadata), computation_(comp) {}
    
    TaskResult execute(const TaskMetadata& metadata) override {
        auto start = std::chrono::high_resolution_clock::now();
        
        TaskResult result;
        result.task_id = metadata.task_id;
        
        try {
            result.result_data = computation_(metadata.parameters);
            result.status = TaskStatus::COMPLETED;
        } catch (const std::exception& e) {
            result.status = TaskStatus::FAILED;
            result.error_message = e.what();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        return result;
    }
    
    std::string getTaskType() const override { return "CPU_INTENSIVE"; }
};
```

#### 任务调度器
```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <algorithm>

// 任务比较器（用于优先队列）
struct TaskComparator {
    bool operator()(const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) const {
        const auto& meta_a = a->getMetadata();
        const auto& meta_b = b->getMetadata();
        
        // 优先级高的先执行
        if (meta_a.priority != meta_b.priority) {
            return meta_a.priority < meta_b.priority;
        }
        
        // 相同优先级，提交时间早的先执行
        return meta_a.submit_time > meta_b.submit_time;
    }
};

// 负载均衡策略接口
class ILoadBalancer {
public:
    virtual ~ILoadBalancer() = default;
    virtual std::string selectWorker(const std::vector<std::string>& available_workers,
                                   const TaskMetadata& task) = 0;
};

// 轮询负载均衡
class RoundRobinBalancer : public ILoadBalancer {
private:
    std::atomic<size_t> current_index_{0};
    
public:
    std::string selectWorker(const std::vector<std::string>& available_workers,
                           const TaskMetadata& task) override {
        if (available_workers.empty()) {
            return "";
        }
        
        size_t index = current_index_.fetch_add(1) % available_workers.size();
        return available_workers[index];
    }
};

// 任务调度器
class TaskScheduler {
private:
    std::priority_queue<std::shared_ptr<Task>, 
                       std::vector<std::shared_ptr<Task>>, 
                       TaskComparator> task_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    
    std::unordered_map<std::string, TaskStatus> task_status_;
    std::unordered_map<std::string, TaskResult> task_results_;
    std::mutex status_mutex_;
    
    std::vector<std::string> worker_nodes_;
    std::unordered_map<std::string, int> worker_loads_;
    std::mutex worker_mutex_;
    
    std::unique_ptr<ILoadBalancer> load_balancer_;
    
    std::vector<std::thread> scheduler_threads_;
    std::atomic<bool> running_{false};
    
    // 监控和统计
    std::atomic<size_t> total_tasks_{0};
    std::atomic<size_t> completed_tasks_{0};
    std::atomic<size_t> failed_tasks_{0};
    
public:
    TaskScheduler(std::unique_ptr<ILoadBalancer> balancer) 
        : load_balancer_(std::move(balancer)) {}
    
    ~TaskScheduler() {
        stop();
    }
    
    void start(int num_threads = std::thread::hardware_concurrency()) {
        running_ = true;
        
        for (int i = 0; i < num_threads; ++i) {
            scheduler_threads_.emplace_back([this]() {
                schedulerLoop();
            });
        }
    }
    
    void stop() {
        running_ = false;
        queue_cv_.notify_all();
        
        for (auto& thread : scheduler_threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        scheduler_threads_.clear();
    }
    
    std::string submitTask(std::shared_ptr<Task> task) {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        
        const auto& metadata = task->getMetadata();
        task_queue_.push(task);
        
        {
            std::lock_guard<std::mutex> status_lock(status_mutex_);
            task_status_[metadata.task_id] = TaskStatus::PENDING;
        }
        
        total_tasks_++;
        queue_cv_.notify_one();
        
        return metadata.task_id;
    }
    
    TaskStatus getTaskStatus(const std::string& task_id) const {
        std::lock_guard<std::mutex> lock(status_mutex_);
        auto it = task_status_.find(task_id);
        return (it != task_status_.end()) ? it->second : TaskStatus::PENDING;
    }
    
    std::optional<TaskResult> getTaskResult(const std::string& task_id) const {
        std::lock_guard<std::mutex> lock(status_mutex_);
        auto it = task_results_.find(task_id);
        if (it != task_results_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    void registerWorker(const std::string& worker_id) {
        std::lock_guard<std::mutex> lock(worker_mutex_);
        worker_nodes_.push_back(worker_id);
        worker_loads_[worker_id] = 0;
    }
    
    void unregisterWorker(const std::string& worker_id) {
        std::lock_guard<std::mutex> lock(worker_mutex_);
        auto it = std::find(worker_nodes_.begin(), worker_nodes_.end(), worker_id);
        if (it != worker_nodes_.end()) {
            worker_nodes_.erase(it);
            worker_loads_.erase(worker_id);
        }
    }
    
    // 获取系统统计信息
    struct SystemStats {
        size_t total_tasks;
        size_t completed_tasks;
        size_t failed_tasks;
        size_t pending_tasks;
        size_t active_workers;
        double success_rate;
    };
    
    SystemStats getSystemStats() const {
        SystemStats stats;
        stats.total_tasks = total_tasks_.load();
        stats.completed_tasks = completed_tasks_.load();
        stats.failed_tasks = failed_tasks_.load();
        
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            stats.pending_tasks = task_queue_.size();
        }
        
        {
            std::lock_guard<std::mutex> lock(worker_mutex_);
            stats.active_workers = worker_nodes_.size();
        }
        
        stats.success_rate = stats.total_tasks > 0 ? 
            static_cast<double>(stats.completed_tasks) / stats.total_tasks : 0.0;
        
        return stats;
    }
    
private:
    void schedulerLoop() {
        while (running_) {
            std::shared_ptr<Task> task;
            
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                queue_cv_.wait(lock, [this]() {
                    return !task_queue_.empty() || !running_;
                });
                
                if (!running_) break;
                
                if (!task_queue_.empty()) {
                    task = task_queue_.top();
                    task_queue_.pop();
                }
            }
            
            if (task) {
                executeTask(task);
            }
        }
    }
    
    void executeTask(std::shared_ptr<Task> task) {
        const auto& metadata = task->getMetadata();
        
        // 选择工作节点
        std::string selected_worker;
        {
            std::lock_guard<std::mutex> lock(worker_mutex_);
            selected_worker = load_balancer_->selectWorker(worker_nodes_, metadata);
        }
        
        if (selected_worker.empty()) {
            // 没有可用的工作节点，重新放回队列
            std::lock_guard<std::mutex> lock(queue_mutex_);
            task_queue_.push(task);
            return;
        }
        
        // 更新任务状态
        {
            std::lock_guard<std::mutex> lock(status_mutex_);
            task_status_[metadata.task_id] = TaskStatus::RUNNING;
        }
        
        // 执行任务（这里简化为本地执行）
        TaskResult result = task->execute(metadata);
        
        // 更新结果和统计
        {
            std::lock_guard<std::mutex> lock(status_mutex_);
            task_status_[metadata.task_id] = result.status;
            task_results_[metadata.task_id] = result;
        }
        
        if (result.status == TaskStatus::COMPLETED) {
            completed_tasks_++;
        } else if (result.status == TaskStatus::FAILED) {
            failed_tasks_++;
            
            // 重试逻辑
            if (task->canRetry()) {
                auto retry_metadata = metadata;
                retry_metadata.current_retries++;
                task->updateMetadata(retry_metadata);
                
                std::lock_guard<std::mutex> lock(queue_mutex_);
                task_queue_.push(task);
                queue_cv_.notify_one();
            }
        }
    }
};
```

#### 配置管理系统
```cpp
#include <fstream>
#include <sstream>
#include <mutex>
#include <shared_mutex>

// 配置管理器（单例模式）
class ConfigurationManager {
private:
    static std::unique_ptr<ConfigurationManager> instance_;
    static std::once_flag init_flag_;
    
    std::unordered_map<std::string, std::string> config_map_;
    mutable std::shared_mutex config_mutex_;
    std::string config_file_;
    
    ConfigurationManager() = default;
    
public:
    static ConfigurationManager& getInstance() {
        std::call_once(init_flag_, []() {
            instance_ = std::unique_ptr<ConfigurationManager>(new ConfigurationManager());
        });
        return *instance_;
    }
    
    void loadFromFile(const std::string& filename) {
        std::unique_lock<std::shared_mutex> lock(config_mutex_);
        config_file_ = filename;
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open config file: " + filename);
        }
        
        config_map_.clear();
        std::string line;
        
        while (std::getline(file, line)) {
            // 跳过注释和空行
            if (line.empty() || line[0] == '#') continue;
            
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                // 去除前后空格
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                config_map_[key] = value;
            }
        }
    }
    
    void saveToFile() const {
        std::shared_lock<std::shared_mutex> lock(config_mutex_);
        
        std::ofstream file(config_file_);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot write to config file: " + config_file_);
        }
        
        for (const auto& [key, value] : config_map_) {
            file << key << " = " << value << std::endl;
        }
    }
    
    template<typename T>
    T get(const std::string& key, const T& default_value = T{}) const {
        std::shared_lock<std::shared_mutex> lock(config_mutex_);
        
        auto it = config_map_.find(key);
        if (it == config_map_.end()) {
            return default_value;
        }
        
        return convertFromString<T>(it->second);
    }
    
    template<typename T>
    void set(const std::string& key, const T& value) {
        std::unique_lock<std::shared_mutex> lock(config_mutex_);
        config_map_[key] = convertToString(value);
    }
    
    bool contains(const std::string& key) const {
        std::shared_lock<std::shared_mutex> lock(config_mutex_);
        return config_map_.find(key) != config_map_.end();
    }
    
    std::vector<std::string> getKeys() const {
        std::shared_lock<std::shared_mutex> lock(config_mutex_);
        std::vector<std::string> keys;
        keys.reserve(config_map_.size());
        
        for (const auto& [key, value] : config_map_) {
            keys.push_back(key);
        }
        
        return keys;
    }
    
private:
    template<typename T>
    T convertFromString(const std::string& str) const {
        if constexpr (std::is_same_v<T, std::string>) {
            return str;
        } else if constexpr (std::is_same_v<T, int>) {
            return std::stoi(str);
        } else if constexpr (std::is_same_v<T, double>) {
            return std::stod(str);
        } else if constexpr (std::is_same_v<T, bool>) {
            return str == "true" || str == "1";
        } else {
            static_assert(std::is_same_v<T, void>, "Unsupported type");
        }
    }
    
    template<typename T>
    std::string convertToString(const T& value) const {
        if constexpr (std::is_same_v<T, std::string>) {
            return value;
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(value);
        } else if constexpr (std::is_same_v<T, bool>) {
            return value ? "true" : "false";
        } else {
            static_assert(std::is_same_v<T, void>, "Unsupported type");
        }
    }
};

// 静态成员定义
std::unique_ptr<ConfigurationManager> ConfigurationManager::instance_ = nullptr;
std::once_flag ConfigurationManager::init_flag_;
```

#### 日志系统
```cpp
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

// 日志格式化器接口
class ILogFormatter {
public:
    virtual ~ILogFormatter() = default;
    virtual std::string format(LogLevel level, const std::string& message, 
                              const std::chrono::system_clock::time_point& timestamp) = 0;
};

// 默认日志格式化器
class DefaultLogFormatter : public ILogFormatter {
public:
    std::string format(LogLevel level, const std::string& message,
                      const std::chrono::system_clock::time_point& timestamp) override {
        std::stringstream ss;
        
        // 时间戳
        auto time_t = std::chrono::system_clock::to_time_t(timestamp);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            timestamp.time_since_epoch()) % 1000;
        
        ss << "[" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";
        
        // 日志级别
        ss << "[" << levelToString(level) << "] ";
        
        // 线程ID
        ss << "[Thread-" << std::this_thread::get_id() << "] ";
        
        // 消息
        ss << message;
        
        return ss.str();
    }
    
private:
    std::string levelToString(LogLevel level) const {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::CRITICAL: return "CRIT";
            default: return "UNKNOWN";
        }
    }
};

// 日志输出器接口
class ILogAppender {
public:
    virtual ~ILogAppender() = default;
    virtual void append(const std::string& formatted_message) = 0;
};

// 文件日志输出器
class FileLogAppender : public ILogAppender {
private:
    std::ofstream file_;
    std::mutex file_mutex_;
    
public:
    FileLogAppender(const std::string& filename) {
        file_.open(filename, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Cannot open log file: " + filename);
        }
    }
    
    void append(const std::string& formatted_message) override {
        std::lock_guard<std::mutex> lock(file_mutex_);
        file_ << formatted_message << std::endl;
        file_.flush();
    }
};

// 控制台日志输出器
class ConsoleLogAppender : public ILogAppender {
private:
    std::mutex console_mutex_;
    
public:
    void append(const std::string& formatted_message) override {
        std::lock_guard<std::mutex> lock(console_mutex_);
        std::cout << formatted_message << std::endl;
    }
};

// 主日志器
class Logger {
private:
    LogLevel min_level_;
    std::unique_ptr<ILogFormatter> formatter_;
    std::vector<std::unique_ptr<ILogAppender>> appenders_;
    
public:
    Logger(LogLevel min_level = LogLevel::INFO) 
        : min_level_(min_level), formatter_(std::make_unique<DefaultLogFormatter>()) {}
    
    void setFormatter(std::unique_ptr<ILogFormatter> formatter) {
        formatter_ = std::move(formatter);
    }
    
    void addAppender(std::unique_ptr<ILogAppender> appender) {
        appenders_.push_back(std::move(appender));
    }
    
    void setMinLevel(LogLevel level) {
        min_level_ = level;
    }
    
    template<typename... Args>
    void log(LogLevel level, const std::string& format, Args&&... args) {
        if (level < min_level_) return;
        
        std::string message = formatMessage(format, std::forward<Args>(args)...);
        auto timestamp = std::chrono::system_clock::now();
        
        std::string formatted = formatter_->format(level, message, timestamp);
        
        for (auto& appender : appenders_) {
            appender->append(formatted);
        }
    }
    
    template<typename... Args>
    void debug(const std::string& format, Args&&... args) {
        log(LogLevel::DEBUG, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void info(const std::string& format, Args&&... args) {
        log(LogLevel::INFO, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void warning(const std::string& format, Args&&... args) {
        log(LogLevel::WARNING, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void error(const std::string& format, Args&&... args) {
        log(LogLevel::ERROR, format, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    void critical(const std::string& format, Args&&... args) {
        log(LogLevel::CRITICAL, format, std::forward<Args>(args)...);
    }
    
private:
    template<typename... Args>
    std::string formatMessage(const std::string& format, Args&&... args) {
        if constexpr (sizeof...(args) == 0) {
            return format;
        } else {
            std::ostringstream oss;
            formatImpl(oss, format, std::forward<Args>(args)...);
            return oss.str();
        }
    }
    
    void formatImpl(std::ostringstream& oss, const std::string& format) {
        oss << format;
    }
    
    template<typename T, typename... Args>
    void formatImpl(std::ostringstream& oss, const std::string& format, T&& value, Args&&... args) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << value;
            formatImpl(oss, format.substr(pos + 2), std::forward<Args>(args)...);
        } else {
            oss << format;
        }
    }
};

// 全局日志器
class LoggerManager {
private:
    static std::unique_ptr<Logger> instance_;
    static std::once_flag init_flag_;
    
public:
    static Logger& getInstance() {
        std::call_once(init_flag_, []() {
            instance_ = std::make_unique<Logger>();
            
            // 默认添加控制台输出
            instance_->addAppender(std::make_unique<ConsoleLogAppender>());
            
            // 从配置读取日志设置
            auto& config = ConfigurationManager::getInstance();
            if (config.contains("log.file")) {
                instance_->addAppender(
                    std::make_unique<FileLogAppender>(config.get<std::string>("log.file"))
                );
            }
            
            if (config.contains("log.level")) {
                std::string level_str = config.get<std::string>("log.level");
                LogLevel level = LogLevel::INFO;
                if (level_str == "DEBUG") level = LogLevel::DEBUG;
                else if (level_str == "INFO") level = LogLevel::INFO;
                else if (level_str == "WARNING") level = LogLevel::WARNING;
                else if (level_str == "ERROR") level = LogLevel::ERROR;
                else if (level_str == "CRITICAL") level = LogLevel::CRITICAL;
                
                instance_->setMinLevel(level);
            }
        });
        return *instance_;
    }
};

std::unique_ptr<Logger> LoggerManager::instance_ = nullptr;
std::once_flag LoggerManager::init_flag_;

// 便利宏
#define LOG_DEBUG(...) LoggerManager::getInstance().debug(__VA_ARGS__)
#define LOG_INFO(...) LoggerManager::getInstance().info(__VA_ARGS__)
#define LOG_WARNING(...) LoggerManager::getInstance().warning(__VA_ARGS__)
#define LOG_ERROR(...) LoggerManager::getInstance().error(__VA_ARGS__)
#define LOG_CRITICAL(...) LoggerManager::getInstance().critical(__VA_ARGS__)
```

#### 主应用程序
```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

// 示例任务工厂
class TaskFactory {
public:
    static std::shared_ptr<Task> createCPUTask(const std::string& task_id, 
                                              const std::string& operation,
                                              const std::unordered_map<std::string, std::string>& params) {
        TaskMetadata metadata;
        metadata.task_id = task_id;
        metadata.task_name = "CPU Task: " + operation;
        metadata.type = TaskType::CPU_INTENSIVE;
        metadata.priority = TaskPriority::NORMAL;
        metadata.submit_time = std::chrono::system_clock::now();
        metadata.timeout = std::chrono::seconds(30);
        metadata.parameters = params;
        
        auto computation = [operation](const std::unordered_map<std::string, std::string>& params) -> std::string {
            if (operation == "fibonacci") {
                int n = std::stoi(params.at("n"));
                long long result = 1, prev = 0;
                for (int i = 2; i <= n; ++i) {
                    long long temp = result;
                    result = result + prev;
                    prev = temp;
                }
                return std::to_string(result);
            } else if (operation == "prime_check") {
                long long num = std::stoll(params.at("number"));
                if (num < 2) return "false";
                for (long long i = 2; i * i <= num; ++i) {
                    if (num % i == 0) return "false";
                }
                return "true";
            }
            return "unknown_operation";
        };
        
        return std::make_shared<CPUIntensiveTask>(metadata, computation);
    }
};

// 主应用程序类
class TaskSchedulingSystem {
private:
    std::unique_ptr<TaskScheduler> scheduler_;
    Logger& logger_;
    
public:
    TaskSchedulingSystem() : logger_(LoggerManager::getInstance()) {
        // 初始化配置
        auto& config = ConfigurationManager::getInstance();
        try {
            config.loadFromFile("config.txt");
        } catch (const std::exception& e) {
            // 使用默认配置
            config.set("scheduler.threads", 4);
            config.set("scheduler.max_queue_size", 1000);
            config.set("log.level", "INFO");
            config.set("log.file", "system.log");
        }
        
        // 创建调度器
        auto balancer = std::make_unique<RoundRobinBalancer>();
        scheduler_ = std::make_unique<TaskScheduler>(std::move(balancer));
        
        logger_.info("Task Scheduling System initialized");
    }
    
    void start() {
        logger_.info("Starting Task Scheduling System");
        
        // 启动调度器
        int num_threads = ConfigurationManager::getInstance().get("scheduler.threads", 4);
        scheduler_->start(num_threads);
        
        // 注册一些工作节点
        scheduler_->registerWorker("worker-1");
        scheduler_->registerWorker("worker-2");
        scheduler_->registerWorker("worker-3");
        
        logger_.info("System started with {} worker threads", num_threads);
    }
    
    void stop() {
        logger_.info("Stopping Task Scheduling System");
        scheduler_->stop();
        logger_.info("System stopped");
    }
    
    std::string submitTask(const std::string& operation, 
                          const std::unordered_map<std::string, std::string>& params) {
        static std::atomic<int> task_counter{0};
        std::string task_id = "task-" + std::to_string(task_counter.fetch_add(1));
        
        auto task = TaskFactory::createCPUTask(task_id, operation, params);
        std::string submitted_id = scheduler_->submitTask(task);
        
        logger_.info("Task submitted: {} ({})", task_id, operation);
        return submitted_id;
    }
    
    TaskStatus getTaskStatus(const std::string& task_id) {
        return scheduler_->getTaskStatus(task_id);
    }
    
    std::optional<TaskResult> getTaskResult(const std::string& task_id) {
        return scheduler_->getTaskResult(task_id);
    }
    
    void printSystemStats() {
        auto stats = scheduler_->getSystemStats();
        
        logger_.info("=== System Statistics ===");
        logger_.info("Total tasks: {}", stats.total_tasks);
        logger_.info("Completed tasks: {}", stats.completed_tasks);
        logger_.info("Failed tasks: {}", stats.failed_tasks);
        logger_.info("Pending tasks: {}", stats.pending_tasks);
        logger_.info("Active workers: {}", stats.active_workers);
        logger_.info("Success rate: {:.2f}%", stats.success_rate * 100);
    }
    
    void runDemo() {
        logger_.info("Running system demo");
        
        // 提交一些测试任务
        std::vector<std::string> task_ids;
        
        // Fibonacci任务
        for (int i = 10; i <= 50; i += 10) {
            std::unordered_map<std::string, std::string> params{{"n", std::to_string(i)}};
            std::string task_id = submitTask("fibonacci", params);
            task_ids.push_back(task_id);
        }
        
        // 素数检查任务
        std::vector<long long> numbers{97, 1009, 10007, 100003, 1000003};
        for (long long num : numbers) {
            std::unordered_map<std::string, std::string> params{{"number", std::to_string(num)}};
            std::string task_id = submitTask("prime_check", params);
            task_ids.push_back(task_id);
        }
        
        // 等待任务完成
        logger_.info("Waiting for tasks to complete...");
        
        while (true) {
            bool all_completed = true;
            
            for (const auto& task_id : task_ids) {
                TaskStatus status = getTaskStatus(task_id);
                if (status == TaskStatus::PENDING || status == TaskStatus::RUNNING) {
                    all_completed = false;
                    break;
                }
            }
            
            if (all_completed) break;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        // 打印结果
        logger_.info("All tasks completed. Results:");
        for (const auto& task_id : task_ids) {
            auto result = getTaskResult(task_id);
            if (result) {
                logger_.info("Task {}: {} ({}ms)", 
                           task_id, 
                           result->result_data, 
                           result->execution_time.count());
            }
        }
        
        printSystemStats();
    }
};

// 主函数
int main() {
    try {
        TaskSchedulingSystem system;
        system.start();
        
        // 运行演示
        system.runDemo();
        
        // 保持系统运行一段时间
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        system.stop();
        
    } catch (const std::exception& e) {
        std::cerr << "System error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

## 项目特点总结

### 1. 设计模式应用
- **单例模式**：配置管理器、日志管理器
- **工厂模式**：任务工厂
- **策略模式**：负载均衡策略
- **观察者模式**：任务状态通知
- **RAII模式**：资源管理

### 2. 现代C++特性
- **智能指针**：自动内存管理
- **移动语义**：高效对象传递
- **模板编程**：泛型设计
- **并发编程**：多线程任务处理
- **异常安全**：强异常安全保证

### 3. 系统架构
- **模块化设计**：松耦合的组件
- **可扩展性**：易于添加新功能
- **可配置性**：灵活的配置管理
- **监控能力**：完善的日志和统计
- **容错性**：任务重试和错误处理

### 4. 性能考虑
- **线程池**：复用线程资源
- **内存管理**：减少内存分配
- **缓存友好**：优化数据结构
- **负载均衡**：合理分配任务

## 扩展方向

1. **网络通信**：添加分布式节点通信
2. **持久化**：任务和结果的数据库存储
3. **Web界面**：任务管理的Web控制台
4. **监控告警**：系统监控和告警机制
5. **安全性**：身份验证和权限控制

这个综合项目展示了如何将前面学到的所有知识点整合到一个实际的系统中，体现了软件工程的最佳实践。
