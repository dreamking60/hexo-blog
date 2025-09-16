# 第21天：文件操作与IO复习

## 学习目标
掌握C++的文件操作和IO流，理解文本文件与二进制文件的处理，学会使用字符串流和错误处理。

## 学习内容

### 1. 文件流概述

C++提供了多种文件流类来处理文件操作：
- `ifstream`：输入文件流（读取文件）
- `ofstream`：输出文件流（写入文件）
- `fstream`：文件流（读写文件）

### 2. 基本文件操作

#### 文件写入
```cpp
#include <iostream>
#include <fstream>
#include <string>

void fileWritingExample() {
    // 创建输出文件流
    std::ofstream outFile("example.txt");
    
    if (outFile.is_open()) {
        // 写入文本
        outFile << "Hello, World!" << std::endl;
        outFile << "This is a test file." << std::endl;
        outFile << "Line 3" << std::endl;
        
        // 写入数字
        int number = 42;
        outFile << "Number: " << number << std::endl;
        
        outFile.close();
        std::cout << "文件写入成功" << std::endl;
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 文件读取
```cpp
#include <iostream>
#include <fstream>
#include <string>

void fileReadingExample() {
    // 创建输入文件流
    std::ifstream inFile("example.txt");
    
    if (inFile.is_open()) {
        std::string line;
        
        // 逐行读取
        while (std::getline(inFile, line)) {
            std::cout << "读取: " << line << std::endl;
        }
        
        inFile.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 文件读写
```cpp
#include <iostream>
#include <fstream>
#include <string>

void fileReadWriteExample() {
    // 创建文件流（读写模式）
    std::fstream file("data.txt", std::ios::in | std::ios::out | std::ios::trunc);
    
    if (file.is_open()) {
        // 写入数据
        file << "Line 1" << std::endl;
        file << "Line 2" << std::endl;
        file << "Line 3" << std::endl;
        
        // 移动到文件开头
        file.seekg(0, std::ios::beg);
        
        // 读取数据
        std::string line;
        while (std::getline(file, line)) {
            std::cout << "读取: " << line << std::endl;
        }
        
        file.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

### 3. 文件模式

```cpp
#include <iostream>
#include <fstream>

void fileModeExample() {
    // 不同的文件打开模式
    std::ofstream out1("file1.txt", std::ios::out);           // 输出模式
    std::ofstream out2("file2.txt", std::ios::out | std::ios::app);  // 追加模式
    std::ofstream out3("file3.txt", std::ios::out | std::ios::trunc); // 截断模式
    
    std::ifstream in1("file1.txt", std::ios::in);             // 输入模式
    std::ifstream in2("file1.txt", std::ios::in | std::ios::binary); // 二进制模式
    
    std::fstream file("file4.txt", std::ios::in | std::ios::out | std::ios::app); // 读写追加模式
    
    // 检查文件是否打开
    if (out1.is_open()) {
        out1 << "文件1内容" << std::endl;
        out1.close();
    }
    
    if (out2.is_open()) {
        out2 << "文件2内容" << std::endl;
        out2.close();
    }
}
```

### 4. 二进制文件操作

#### 二进制写入
```cpp
#include <iostream>
#include <fstream>
#include <vector>

struct Person {
    char name[50];
    int age;
    double salary;
};

void binaryWritingExample() {
    std::ofstream outFile("people.bin", std::ios::binary);
    
    if (outFile.is_open()) {
        Person people[] = {
            {"Alice", 25, 50000.0},
            {"Bob", 30, 60000.0},
            {"Charlie", 35, 70000.0}
        };
        
        // 写入二进制数据
        outFile.write(reinterpret_cast<const char*>(people), sizeof(people));
        
        outFile.close();
        std::cout << "二进制文件写入成功" << std::endl;
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

#### 二进制读取
```cpp
#include <iostream>
#include <fstream>
#include <vector>

void binaryReadingExample() {
    std::ifstream inFile("people.bin", std::ios::binary);
    
    if (inFile.is_open()) {
        // 获取文件大小
        inFile.seekg(0, std::ios::end);
        size_t fileSize = inFile.tellg();
        inFile.seekg(0, std::ios::beg);
        
        // 计算记录数量
        size_t numRecords = fileSize / sizeof(Person);
        
        // 读取数据
        std::vector<Person> people(numRecords);
        inFile.read(reinterpret_cast<char*>(people.data()), fileSize);
        
        // 显示数据
        for (const auto& person : people) {
            std::cout << "姓名: " << person.name 
                      << ", 年龄: " << person.age 
                      << ", 工资: " << person.salary << std::endl;
        }
        
        inFile.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
}
```

### 5. 文件定位

```cpp
#include <iostream>
#include <fstream>
#include <string>

void filePositioningExample() {
    std::fstream file("position.txt", std::ios::in | std::ios::out | std::ios::trunc);
    
    if (file.is_open()) {
        // 写入数据
        file << "Line 1: Hello" << std::endl;
        file << "Line 2: World" << std::endl;
        file << "Line 3: C++" << std::endl;
        file << "Line 4: Programming" << std::endl;
        
        // 获取当前位置
        std::cout << "当前位置: " << file.tellg() << std::endl;
        
        // 移动到文件开头
        file.seekg(0, std::ios::beg);
        std::cout << "移动到开头后位置: " << file.tellg() << std::endl;
        
        // 移动到文件末尾
        file.seekg(0, std::ios::end);
        std::cout << "移动到末尾后位置: " << file.tellg() << std::endl;
        
        // 移动到指定位置
        file.seekg(10, std::ios::beg);
        std::cout << "移动到位置10后位置: " << file.tellg() << std::endl;
        
        // 从当前位置向前移动
        file.seekg(-5, std::ios::cur);
        std::cout << "向前移动5个位置后位置: " << file.tellg() << std::endl;
        
        file.close();
    }
}
```

### 6. 字符串流

#### std::stringstream
```cpp
#include <iostream>
#include <sstream>
#include <string>

void stringStreamExample() {
    // 字符串到数字的转换
    std::string str = "123 456 789";
    std::stringstream ss(str);
    
    int num1, num2, num3;
    ss >> num1 >> num2 >> num3;
    
    std::cout << "数字1: " << num1 << std::endl;
    std::cout << "数字2: " << num2 << std::endl;
    std::cout << "数字3: " << num3 << std::endl;
    
    // 数字到字符串的转换
    std::stringstream ss2;
    int value = 42;
    double pi = 3.14159;
    
    ss2 << "Value: " << value << ", Pi: " << pi;
    std::string result = ss2.str();
    std::cout << "结果: " << result << std::endl;
}
```

#### std::istringstream 和 std::ostringstream
```cpp
#include <iostream>
#include <sstream>
#include <string>

void specializedStringStreamExample() {
    // 输入字符串流
    std::string input = "Hello World 123 45.67";
    std::istringstream iss(input);
    
    std::string word1, word2;
    int number;
    double decimal;
    
    iss >> word1 >> word2 >> number >> decimal;
    
    std::cout << "单词1: " << word1 << std::endl;
    std::cout << "单词2: " << word2 << std::endl;
    std::cout << "数字: " << number << std::endl;
    std::cout << "小数: " << decimal << std::endl;
    
    // 输出字符串流
    std::ostringstream oss;
    oss << "结果: " << word1 << " " << word2 << " " << number << " " << decimal;
    std::string output = oss.str();
    std::cout << "输出: " << output << std::endl;
}
```

### 7. 错误处理

```cpp
#include <iostream>
#include <fstream>
#include <string>

void errorHandlingExample() {
    std::ifstream file("nonexistent.txt");
    
    // 检查文件是否打开
    if (!file.is_open()) {
        std::cout << "错误: 无法打开文件" << std::endl;
        return;
    }
    
    // 检查文件状态
    if (file.fail()) {
        std::cout << "错误: 文件操作失败" << std::endl;
        return;
    }
    
    if (file.bad()) {
        std::cout << "错误: 文件流损坏" << std::endl;
        return;
    }
    
    if (file.eof()) {
        std::cout << "警告: 已到达文件末尾" << std::endl;
    }
    
    // 清除错误状态
    file.clear();
    
    file.close();
}
```

### 8. 文件管理器类

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

class FileManager {
public:
    static bool copyFile(const std::string& source, const std::string& destination) {
        std::ifstream src(source, std::ios::binary);
        std::ofstream dst(destination, std::ios::binary);
        
        if (!src.is_open() || !dst.is_open()) {
            return false;
        }
        
        dst << src.rdbuf();
        return true;
    }
    
    static bool moveFile(const std::string& source, const std::string& destination) {
        if (copyFile(source, destination)) {
            return std::remove(source.c_str()) == 0;
        }
        return false;
    }
    
    static std::vector<std::string> readLines(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }
        
        return lines;
    }
    
    static void writeLines(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream file(filename);
        
        if (file.is_open()) {
            for (const auto& line : lines) {
                file << line << std::endl;
            }
            file.close();
        }
    }
    
    static size_t getFileSize(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            return file.tellg();
        }
        return 0;
    }
    
    static bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
};

void fileManagerExample() {
    // 写入测试文件
    std::vector<std::string> lines = {"Line 1", "Line 2", "Line 3"};
    FileManager::writeLines("test.txt", lines);
    
    // 读取文件
    auto readLines = FileManager::readLines("test.txt");
    std::cout << "读取的行数: " << readLines.size() << std::endl;
    
    // 检查文件是否存在
    if (FileManager::fileExists("test.txt")) {
        std::cout << "文件存在" << std::endl;
        std::cout << "文件大小: " << FileManager::getFileSize("test.txt") << " 字节" << std::endl;
    }
    
    // 复制文件
    if (FileManager::copyFile("test.txt", "test_copy.txt")) {
        std::cout << "文件复制成功" << std::endl;
    }
}
```

## 实践练习

### 练习1：日志系统
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <mutex>

class Logger {
private:
    std::ofstream logFile;
    std::mutex mtx;
    
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }
    
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    void log(const std::string& level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        
        if (logFile.is_open()) {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            
            logFile << "[" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S") << "] "
                    << "[" << level << "] " << message << std::endl;
            logFile.flush();
        }
    }
    
    void info(const std::string& message) {
        log("INFO", message);
    }
    
    void warning(const std::string& message) {
        log("WARNING", message);
    }
    
    void error(const std::string& message) {
        log("ERROR", message);
    }
};

void loggerExample() {
    Logger logger("app.log");
    
    logger.info("应用程序启动");
    logger.warning("这是一个警告消息");
    logger.error("这是一个错误消息");
    logger.info("应用程序结束");
}
```

### 练习2：配置文件解析器
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

class ConfigParser {
private:
    std::map<std::string, std::string> config;
    
public:
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            // 跳过空行和注释
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            // 查找等号
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                // 去除空格
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                config[key] = value;
            }
        }
        
        file.close();
        return true;
    }
    
    std::string getString(const std::string& key, const std::string& defaultValue = "") const {
        auto it = config.find(key);
        return it != config.end() ? it->second : defaultValue;
    }
    
    int getInt(const std::string& key, int defaultValue = 0) const {
        auto it = config.find(key);
        if (it != config.end()) {
            std::istringstream iss(it->second);
            int value;
            if (iss >> value) {
                return value;
            }
        }
        return defaultValue;
    }
    
    double getDouble(const std::string& key, double defaultValue = 0.0) const {
        auto it = config.find(key);
        if (it != config.end()) {
            std::istringstream iss(it->second);
            double value;
            if (iss >> value) {
                return value;
            }
        }
        return defaultValue;
    }
    
    bool getBool(const std::string& key, bool defaultValue = false) const {
        auto it = config.find(key);
        if (it != config.end()) {
            std::string value = it->second;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            return value == "true" || value == "1" || value == "yes";
        }
        return defaultValue;
    }
    
    void printAll() const {
        for (const auto& pair : config) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
    }
};

void configParserExample() {
    // 创建配置文件
    std::ofstream configFile("config.txt");
    configFile << "# 应用程序配置\n";
    configFile << "app_name = MyApp\n";
    configFile << "version = 1.0.0\n";
    configFile << "debug = true\n";
    configFile << "max_connections = 100\n";
    configFile << "timeout = 30.5\n";
    configFile.close();
    
    // 解析配置文件
    ConfigParser parser;
    if (parser.loadFromFile("config.txt")) {
        std::cout << "配置加载成功:" << std::endl;
        parser.printAll();
        
        std::cout << "\n特定配置:" << std::endl;
        std::cout << "应用名称: " << parser.getString("app_name") << std::endl;
        std::cout << "版本: " << parser.getString("version") << std::endl;
        std::cout << "调试模式: " << (parser.getBool("debug") ? "开启" : "关闭") << std::endl;
        std::cout << "最大连接数: " << parser.getInt("max_connections") << std::endl;
        std::cout << "超时时间: " << parser.getDouble("timeout") << std::endl;
    } else {
        std::cout << "配置加载失败" << std::endl;
    }
}
```

### 练习3：数据序列化
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class DataSerializer {
public:
    // 序列化到文件
    static bool serializeToFile(const std::string& filename, const std::vector<std::string>& data) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        // 写入数据数量
        size_t count = data.size();
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
        
        // 写入每个字符串
        for (const auto& str : data) {
            size_t length = str.length();
            file.write(reinterpret_cast<const char*>(&length), sizeof(length));
            file.write(str.c_str(), length);
        }
        
        file.close();
        return true;
    }
    
    // 从文件反序列化
    static bool deserializeFromFile(const std::string& filename, std::vector<std::string>& data) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        // 读取数据数量
        size_t count;
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        
        data.clear();
        data.reserve(count);
        
        // 读取每个字符串
        for (size_t i = 0; i < count; ++i) {
            size_t length;
            file.read(reinterpret_cast<char*>(&length), sizeof(length));
            
            std::string str(length, '\0');
            file.read(&str[0], length);
            
            data.push_back(str);
        }
        
        file.close();
        return true;
    }
    
    // 序列化到字符串
    static std::string serializeToString(const std::vector<std::string>& data) {
        std::ostringstream oss;
        
        oss << data.size() << "\n";
        for (const auto& str : data) {
            oss << str.length() << " " << str << "\n";
        }
        
        return oss.str();
    }
    
    // 从字符串反序列化
    static bool deserializeFromString(const std::string& str, std::vector<std::string>& data) {
        std::istringstream iss(str);
        
        size_t count;
        if (!(iss >> count)) {
            return false;
        }
        
        data.clear();
        data.reserve(count);
        
        for (size_t i = 0; i < count; ++i) {
            size_t length;
            if (!(iss >> length)) {
                return false;
            }
            
            std::string item(length, '\0');
            iss.read(&item[0], length);
            data.push_back(item);
        }
        
        return true;
    }
};

void dataSerializerExample() {
    // 测试数据
    std::vector<std::string> originalData = {
        "Hello, World!",
        "C++ Programming",
        "File I/O Operations",
        "Data Serialization"
    };
    
    // 序列化到文件
    if (DataSerializer::serializeToFile("data.bin", originalData)) {
        std::cout << "数据序列化到文件成功" << std::endl;
    }
    
    // 从文件反序列化
    std::vector<std::string> loadedData;
    if (DataSerializer::deserializeFromFile("data.bin", loadedData)) {
        std::cout << "从文件反序列化成功:" << std::endl;
        for (const auto& str : loadedData) {
            std::cout << "  " << str << std::endl;
        }
    }
    
    // 序列化到字符串
    std::string serialized = DataSerializer::serializeToString(originalData);
    std::cout << "\n序列化字符串: " << serialized << std::endl;
    
    // 从字符串反序列化
    std::vector<std::string> deserializedData;
    if (DataSerializer::deserializeFromString(serialized, deserializedData)) {
        std::cout << "从字符串反序列化成功:" << std::endl;
        for (const auto& str : deserializedData) {
            std::cout << "  " << str << std::endl;
        }
    }
}
```

## 学习要点总结

1. **文件流类型**：掌握ifstream、ofstream、fstream的使用
2. **文件模式**：理解不同的文件打开模式
3. **二进制操作**：学会处理二进制文件
4. **字符串流**：掌握stringstream的使用
5. **错误处理**：学会处理文件操作错误

## 今日算法题

完成以下4道LeetCode题目，巩固文件操作的使用：

1. [LeetCode 68. Text Justification](https://leetcode.com/problems/text-justification/) - 文本对齐，涉及字符串处理
2. [LeetCode 151. Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/) - 字符串处理
3. [LeetCode 165. Compare Version Numbers](https://leetcode.com/problems/compare-version-numbers/) - 版本号比较
4. [LeetCode 273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/) - 数字转英文单词

每道题目都涉及字符串处理和文本操作，是很好的实践机会！
