#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <memory>
using namespace std;

// 练习1：资源管理类
class ResourceManager {
private:
    int* resource;
    size_t size;
    string name;
    
public:
    // 构造函数
    ResourceManager(size_t s, string n);
    
    // 拷贝构造函数
    ResourceManager(const ResourceManager& other);
    
    // 移动构造函数
    ResourceManager(ResourceManager&& other) noexcept;
    
    // 拷贝赋值运算符
    ResourceManager& operator=(const ResourceManager& other);
    
    // 移动赋值运算符
    ResourceManager& operator=(ResourceManager&& other) noexcept;
    
    // 析构函数
    ~ResourceManager();
    
    // 其他成员函数
    void setValue(size_t index, int value);
    int getValue(size_t index) const;
    void display() const;
    size_t getSize() const { return size; }
    string getName() const { return name; }
};

// 构造函数实现
ResourceManager::ResourceManager(size_t s, string n) 
    : size(s), name(n) {
    cout << "构造函数: 为 " << name << " 分配 " << size << " 个int资源" << endl;
    
    if (size == 0) {
        resource = nullptr;
        return;
    }
    
    try {
        resource = new int[size];
        // 初始化资源
        for (size_t i = 0; i < size; ++i) {
            resource[i] = 0;
        }
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 拷贝构造函数实现
ResourceManager::ResourceManager(const ResourceManager& other) 
    : size(other.size), name(other.name + "_copy") {
    cout << "拷贝构造函数: 为 " << name << " 分配资源" << endl;
    
    if (size == 0) {
        resource = nullptr;
        return;
    }
    
    try {
        resource = new int[size];
        // 深拷贝
        for (size_t i = 0; i < size; ++i) {
            resource[i] = other.resource[i];
        }
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 移动构造函数实现
ResourceManager::ResourceManager(ResourceManager&& other) noexcept 
    : resource(other.resource), size(other.size), name(other.name + "_moved") {
    cout << "移动构造函数: 转移 " << other.name << " 的资源" << endl;
    
    // 转移资源所有权
    other.resource = nullptr;
    other.size = 0;
    other.name = "moved_away";
}

// 拷贝赋值运算符实现
ResourceManager& ResourceManager::operator=(const ResourceManager& other) {
    cout << "拷贝赋值运算符: " << name << " = " << other.name << endl;
    
    if (this != &other) {  // 自赋值检查
        // 释放当前资源
        delete[] resource;
        
        // 分配新资源
        size = other.size;
        name = other.name + "_assigned";
        
        if (size == 0) {
            resource = nullptr;
        } else {
            try {
                resource = new int[size];
                // 深拷贝
                for (size_t i = 0; i < size; ++i) {
                    resource[i] = other.resource[i];
                }
            } catch (const bad_alloc& e) {
                cout << "内存分配失败: " << e.what() << endl;
                resource = nullptr;
                size = 0;
                throw;
            }
        }
    }
    
    return *this;
}

// 移动赋值运算符实现
ResourceManager& ResourceManager::operator=(ResourceManager&& other) noexcept {
    cout << "移动赋值运算符: " << name << " = " << other.name << endl;
    
    if (this != &other) {  // 自赋值检查
        // 释放当前资源
        delete[] resource;
        
        // 转移资源所有权
        resource = other.resource;
        size = other.size;
        name = other.name + "_moved_assigned";
        
        // 清空源对象
        other.resource = nullptr;
        other.size = 0;
        other.name = "moved_away";
    }
    
    return *this;
}

// 析构函数实现
ResourceManager::~ResourceManager() {
    cout << "析构函数: 释放 " << name << " 的资源" << endl;
    delete[] resource;
}

// 设置值
void ResourceManager::setValue(size_t index, int value) {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    resource[index] = value;
}

// 获取值
int ResourceManager::getValue(size_t index) const {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    return resource[index];
}

// 显示内容
void ResourceManager::display() const {
    cout << name << " (" << size << " elements): ";
    if (resource == nullptr) {
        cout << "null";
    } else {
        for (size_t i = 0; i < size; ++i) {
            cout << resource[i] << " ";
        }
    }
    cout << endl;
}

// 练习2：智能指针模拟
template<typename T>
class SimpleUniquePtr {
private:
    T* ptr;
    
public:
    // 构造函数
    SimpleUniquePtr() : ptr(nullptr) {}
    
    explicit SimpleUniquePtr(T* p) : ptr(p) {
        cout << "SimpleUniquePtr: 接管资源" << endl;
    }
    
    // 禁用拷贝构造和拷贝赋值
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;
    
    // 移动构造函数
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept 
        : ptr(other.ptr) {
        cout << "SimpleUniquePtr: 移动构造" << endl;
        other.ptr = nullptr;
    }
    
    // 移动赋值运算符
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        cout << "SimpleUniquePtr: 移动赋值" << endl;
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // 析构函数
    ~SimpleUniquePtr() {
        cout << "SimpleUniquePtr: 释放资源" << endl;
        delete ptr;
    }
    
    // 解引用运算符
    T& operator*() const {
        if (ptr == nullptr) {
            throw runtime_error("空指针解引用");
        }
        return *ptr;
    }
    
    // 箭头运算符
    T* operator->() const {
        if (ptr == nullptr) {
            throw runtime_error("空指针访问");
        }
        return ptr;
    }
    
    // 获取原始指针
    T* get() const { return ptr; }
    
    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // 重置指针
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    // 检查是否为空
    bool empty() const { return ptr == nullptr; }
};

// 测试类
class TestClass {
private:
    int value;
    
public:
    TestClass(int v) : value(v) {
        cout << "TestClass构造: " << value << endl;
    }
    
    ~TestClass() {
        cout << "TestClass析构: " << value << endl;
    }
    
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
};

// 练习3：异常安全的数组类
class SafeArray {
private:
    int* data;
    size_t size;
    
public:
    // 构造函数
    explicit SafeArray(size_t s);
    
    // 拷贝构造函数
    SafeArray(const SafeArray& other);
    
    // 移动构造函数
    SafeArray(SafeArray&& other) noexcept;
    
    // 拷贝赋值运算符
    SafeArray& operator=(const SafeArray& other);
    
    // 移动赋值运算符
    SafeArray& operator=(SafeArray&& other) noexcept;
    
    // 析构函数
    ~SafeArray();
    
    // 访问元素
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    
    // 获取大小
    size_t getSize() const { return size; }
    
    // 显示内容
    void display() const;
    
private:
    // 辅助函数：安全的数组复制
    void safeCopy(const SafeArray& other);
    
    // 辅助函数：安全的数组移动
    void safeMove(SafeArray&& other) noexcept;
};

// 构造函数实现
SafeArray::SafeArray(size_t s) : size(s) {
    cout << "SafeArray构造: 分配 " << size << " 个元素" << endl;
    
    if (size == 0) {
        data = nullptr;
        return;
    }
    
    try {
        data = new int[size];
        // 初始化为0
        fill(data, data + size, 0);
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 拷贝构造函数实现
SafeArray::SafeArray(const SafeArray& other) : size(other.size) {
    cout << "SafeArray拷贝构造" << endl;
    safeCopy(other);
}

// 移动构造函数实现
SafeArray::SafeArray(SafeArray&& other) noexcept {
    cout << "SafeArray移动构造" << endl;
    safeMove(std::move(other));
}

// 拷贝赋值运算符实现
SafeArray& SafeArray::operator=(const SafeArray& other) {
    cout << "SafeArray拷贝赋值" << endl;
    
    if (this != &other) {
        SafeArray temp(other);  // 创建临时对象
        safeMove(std::move(temp));  // 移动临时对象
    }
    
    return *this;
}

// 移动赋值运算符实现
SafeArray& SafeArray::operator=(SafeArray&& other) noexcept {
    cout << "SafeArray移动赋值" << endl;
    
    if (this != &other) {
        safeMove(std::move(other));
    }
    
    return *this;
}

// 析构函数实现
SafeArray::~SafeArray() {
    cout << "SafeArray析构: 释放 " << size << " 个元素" << endl;
    delete[] data;
}

// 访问元素
int& SafeArray::operator[](size_t index) {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    return data[index];
}

const int& SafeArray::operator[](size_t index) const {
    if (index >= size) {
        throw out_of_range("索引超出范围");
    }
    return data[index];
}

// 显示内容
void SafeArray::display() const {
    cout << "SafeArray (" << size << " elements): ";
    if (data == nullptr) {
        cout << "null";
    } else {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
    }
    cout << endl;
}

// 辅助函数：安全的数组复制
void SafeArray::safeCopy(const SafeArray& other) {
    if (other.size == 0) {
        data = nullptr;
        return;
    }
    
    try {
        data = new int[other.size];
        copy(other.data, other.data + other.size, data);
    } catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
        throw;
    }
}

// 辅助函数：安全的数组移动
void SafeArray::safeMove(SafeArray&& other) noexcept {
    delete[] data;
    data = other.data;
    size = other.size;
    
    other.data = nullptr;
    other.size = 0;
}

// 主函数测试
int main() {
    cout << "=== 资源管理类测试 ===" << endl;
    {
        ResourceManager rm1(3, "Resource1");
        rm1.setValue(0, 10);
        rm1.setValue(1, 20);
        rm1.setValue(2, 30);
        rm1.display();
        
        // 拷贝构造测试
        ResourceManager rm2(rm1);
        rm2.display();
        
        // 移动构造测试
        ResourceManager rm3(std::move(rm1));
        rm3.display();
        rm1.display();  // 应该显示moved_away
        
        // 拷贝赋值测试
        ResourceManager rm4(2, "Resource4");
        rm4 = rm2;
        rm4.display();
        
        // 移动赋值测试
        ResourceManager rm5(1, "Resource5");
        rm5 = std::move(rm2);
        rm5.display();
        rm2.display();  // 应该显示moved_away
    }
    
    cout << "\n=== 智能指针测试 ===" << endl;
    {
        SimpleUniquePtr<TestClass> ptr1(new TestClass(100));
        cout << "值: " << ptr1->getValue() << endl;
        
        // 移动构造测试
        SimpleUniquePtr<TestClass> ptr2(std::move(ptr1));
        cout << "ptr1是否为空: " << ptr1.empty() << endl;
        cout << "ptr2值: " << ptr2->getValue() << endl;
        
        // 移动赋值测试
        SimpleUniquePtr<TestClass> ptr3;
        ptr3 = std::move(ptr2);
        cout << "ptr2是否为空: " << ptr2.empty() << endl;
        cout << "ptr3值: " << ptr3->getValue() << endl;
    }
    
    cout << "\n=== 异常安全数组测试 ===" << endl;
    {
        SafeArray arr1(5);
        for (size_t i = 0; i < 5; ++i) {
            arr1[i] = static_cast<int>(i * 10);
        }
        arr1.display();
        
        // 拷贝构造测试
        SafeArray arr2(arr1);
        arr2.display();
        
        // 移动构造测试
        SafeArray arr3(std::move(arr1));
        arr3.display();
        
        // 拷贝赋值测试
        SafeArray arr4(3);
        arr4 = arr2;
        arr4.display();
        
        // 移动赋值测试
        SafeArray arr5(2);
        arr5 = std::move(arr2);
        arr5.display();
    }
    
    cout << "\n=== 异常处理测试 ===" << endl;
    try {
        SafeArray arr(3);
        arr[5] = 100;  // 索引超出范围
    } catch (const exception& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    
    return 0;
}
