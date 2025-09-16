#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <chrono>
using namespace std;

// 练习1：基本动态内存操作
class DynamicMemoryBasics {
public:
    // 基本动态内存分配
    static void demonstrateBasicAllocation() {
        cout << "=== 基本动态内存分配 ===" << endl;
        
        // 分配单个变量
        int* ptr = new int(42);
        cout << "动态分配的值: " << *ptr << endl;
        cout << "动态分配的地址: " << ptr << endl;
        
        // 修改值
        *ptr = 100;
        cout << "修改后的值: " << *ptr << endl;
        
        // 释放内存
        delete ptr;
        ptr = nullptr;  // 避免野指针
        cout << "内存已释放" << endl;
    }
    
    // 动态数组分配
    static void demonstrateArrayAllocation() {
        cout << "\n=== 动态数组分配 ===" << endl;
        
        int size = 5;
        int* arr = new int[size];
        
        // 初始化数组
        for (int i = 0; i < size; i++) {
            arr[i] = i * i;
        }
        
        cout << "动态数组内容: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        // 释放数组内存
        delete[] arr;
        arr = nullptr;
        cout << "数组内存已释放" << endl;
    }
    
    // 内存分配失败处理
    static void demonstrateAllocationFailure() {
        cout << "\n=== 内存分配失败处理 ===" << endl;
        
        // 使用nothrow版本
        int* ptr = new(nothrow) int(42);
        if (ptr == nullptr) {
            cout << "内存分配失败" << endl;
            return;
        }
        cout << "内存分配成功: " << *ptr << endl;
        delete ptr;
        
        // 使用异常处理
        try {
            // 尝试分配大量内存
            size_t hugeSize = SIZE_MAX;
            int* hugePtr = new int[hugeSize];
            delete[] hugePtr;
        } catch (const bad_alloc& e) {
            cout << "内存分配异常: " << e.what() << endl;
        }
    }
};

// 练习2：动态多维数组
class DynamicMultiArray {
public:
    // 动态二维数组
    static int** create2DArray(int rows, int cols) {
        int** matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
        return matrix;
    }
    
    // 初始化二维数组
    static void initialize2DArray(int** matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = i * cols + j + 1;
            }
        }
    }
    
    // 打印二维数组
    static void print2DArray(int** matrix, int rows, int cols) {
        cout << "二维数组内容:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }
    
    // 释放二维数组
    static void delete2DArray(int** matrix, int rows) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    
    // 动态三维数组
    static int*** create3DArray(int x, int y, int z) {
        int*** array = new int**[x];
        for (int i = 0; i < x; i++) {
            array[i] = new int*[y];
            for (int j = 0; j < y; j++) {
                array[i][j] = new int[z];
            }
        }
        return array;
    }
    
    // 释放三维数组
    static void delete3DArray(int*** array, int x, int y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                delete[] array[i][j];
            }
            delete[] array[i];
        }
        delete[] array;
    }
};

// 练习3：动态对象管理
class DynamicObject {
private:
    int* data;
    size_t size;
    string name;
    
public:
    // 构造函数
    DynamicObject(size_t s, const string& n) : size(s), name(n) {
        cout << "构造 " << name << " (大小: " << size << ")" << endl;
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    // 拷贝构造函数
    DynamicObject(const DynamicObject& other) : size(other.size), name(other.name + "_copy") {
        cout << "拷贝构造 " << name << endl;
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // 赋值操作符
    DynamicObject& operator=(const DynamicObject& other) {
        if (this != &other) {
            cout << "赋值操作 " << name << " = " << other.name << endl;
            delete[] data;
            size = other.size;
            name = other.name + "_assigned";
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 移动构造函数
    DynamicObject(DynamicObject&& other) noexcept 
        : data(other.data), size(other.size), name(other.name + "_moved") {
        cout << "移动构造 " << name << endl;
        other.data = nullptr;
        other.size = 0;
    }
    
    // 移动赋值操作符
    DynamicObject& operator=(DynamicObject&& other) noexcept {
        if (this != &other) {
            cout << "移动赋值 " << name << " = " << other.name << endl;
            delete[] data;
            data = other.data;
            size = other.size;
            name = other.name + "_moved";
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    // 析构函数
    ~DynamicObject() {
        cout << "析构 " << name << endl;
        delete[] data;
    }
    
    // 访问数据
    int& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("索引超出范围");
        }
        return data[index];
    }
    
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("索引超出范围");
        }
        return data[index];
    }
    
    // 获取大小
    size_t getSize() const { return size; }
    
    // 获取名称
    const string& getName() const { return name; }
    
    // 打印数据
    void print() const {
        cout << name << " 数据: ";
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// 练习4：RAII资源管理
class ResourceManager {
private:
    int* resource;
    size_t size;
    string name;
    
public:
    // 构造函数
    ResourceManager(size_t s, const string& n) : size(s), name(n) {
        cout << "获取资源: " << name << " (大小: " << size << ")" << endl;
        resource = new int[size];
        for (size_t i = 0; i < size; i++) {
            resource[i] = i;
        }
    }
    
    // 禁止拷贝
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // 移动构造函数
    ResourceManager(ResourceManager&& other) noexcept 
        : resource(other.resource), size(other.size), name(other.name + "_moved") {
        cout << "移动资源: " << name << endl;
        other.resource = nullptr;
        other.size = 0;
    }
    
    // 移动赋值操作符
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            cout << "移动赋值资源: " << name << endl;
            delete[] resource;
            resource = other.resource;
            size = other.size;
            name = other.name + "_moved";
            other.resource = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    // 析构函数
    ~ResourceManager() {
        cout << "释放资源: " << name << endl;
        delete[] resource;
    }
    
    // 访问资源
    int& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("索引超出范围");
        }
        return resource[index];
    }
    
    // 获取大小
    size_t getSize() const { return size; }
    
    // 打印资源
    void print() const {
        cout << name << " 资源: ";
        for (size_t i = 0; i < size; i++) {
            cout << resource[i] << " ";
        }
        cout << endl;
    }
};

// 练习5：异常安全的内存管理
class SafeArray {
private:
    int* data;
    size_t size;
    
public:
    // 构造函数
    SafeArray(size_t s) : size(s) {
        data = new int[size];
        // 如果这里抛出异常，析构函数不会被调用
        // 但构造函数会抛出异常，所以不会造成内存泄漏
        for (size_t i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    // 析构函数
    ~SafeArray() {
        delete[] data;
    }
    
    // 异常安全的赋值
    SafeArray& operator=(const SafeArray& other) {
        if (this != &other) {
            // 先创建新数据
            int* newData = new int[other.size];
            for (size_t i = 0; i < other.size; i++) {
                newData[i] = other.data[i];
            }
            
            // 如果上面没有异常，再替换
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }
    
    // 访问数据
    int& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("索引超出范围");
        }
        return data[index];
    }
    
    // 获取大小
    size_t getSize() const { return size; }
    
    // 打印数据
    void print() const {
        cout << "SafeArray 数据: ";
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// 练习6：智能指针使用
class SmartPointerDemo {
public:
    // unique_ptr使用
    static void demonstrateUniquePtr() {
        cout << "\n=== unique_ptr 使用 ===" << endl;
        
        // 创建unique_ptr
        unique_ptr<int> ptr1 = make_unique<int>(42);
        cout << "unique_ptr 值: " << *ptr1 << endl;
        
        // 移动语义
        unique_ptr<int> ptr2 = move(ptr1);
        cout << "移动后 ptr2 值: " << *ptr2 << endl;
        cout << "移动后 ptr1 是否为空: " << (ptr1 == nullptr) << endl;
        
        // 自动释放内存
        cout << "unique_ptr 将自动释放内存" << endl;
    }
    
    // shared_ptr使用
    static void demonstrateSharedPtr() {
        cout << "\n=== shared_ptr 使用 ===" << endl;
        
        // 创建shared_ptr
        shared_ptr<int> ptr1 = make_shared<int>(42);
        cout << "shared_ptr 引用计数: " << ptr1.use_count() << endl;
        
        // 共享所有权
        shared_ptr<int> ptr2 = ptr1;
        cout << "共享后引用计数: " << ptr1.use_count() << endl;
        
        // 弱引用
        weak_ptr<int> weakPtr = ptr1;
        cout << "weak_ptr 是否过期: " << weakPtr.expired() << endl;
        
        // 自动释放内存
        cout << "shared_ptr 将自动释放内存" << endl;
    }
    
    // 智能指针数组
    static void demonstrateSmartPtrArray() {
        cout << "\n=== 智能指针数组 ===" << endl;
        
        // 创建智能指针数组
        unique_ptr<int[]> arr = make_unique<int[]>(5);
        for (int i = 0; i < 5; i++) {
            arr[i] = i * i;
        }
        
        cout << "智能指针数组: ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        // 自动释放数组内存
        cout << "智能指针数组将自动释放内存" << endl;
    }
};

// 练习7：内存泄漏检测
class MemoryLeakDetector {
private:
    static int allocationCount;
    static int deallocationCount;
    
public:
    // 重载new和delete来跟踪内存分配
    static void* operator new(size_t size) {
        allocationCount++;
        cout << "分配内存: " << size << " 字节" << endl;
        return malloc(size);
    }
    
    static void operator delete(void* ptr) {
        deallocationCount++;
        cout << "释放内存" << endl;
        free(ptr);
    }
    
    // 获取统计信息
    static void printStats() {
        cout << "内存分配次数: " << allocationCount << endl;
        cout << "内存释放次数: " << deallocationCount << endl;
        cout << "内存泄漏: " << (allocationCount - deallocationCount) << endl;
    }
    
    // 重置统计
    static void resetStats() {
        allocationCount = 0;
        deallocationCount = 0;
    }
};

// 静态成员定义
int MemoryLeakDetector::allocationCount = 0;
int MemoryLeakDetector::deallocationCount = 0;

int main() {
    cout << "C++ 动态内存管理练习" << endl;
    cout << "===================" << endl;
    
    // 练习1：基本动态内存操作
    DynamicMemoryBasics::demonstrateBasicAllocation();
    DynamicMemoryBasics::demonstrateArrayAllocation();
    DynamicMemoryBasics::demonstrateAllocationFailure();
    
    // 练习2：动态多维数组
    cout << "\n=== 动态多维数组 ===" << endl;
    int rows = 3, cols = 4;
    int** matrix = DynamicMultiArray::create2DArray(rows, cols);
    DynamicMultiArray::initialize2DArray(matrix, rows, cols);
    DynamicMultiArray::print2DArray(matrix, rows, cols);
    DynamicMultiArray::delete2DArray(matrix, rows);
    
    // 练习3：动态对象管理
    cout << "\n=== 动态对象管理 ===" << endl;
    {
        DynamicObject obj1(5, "Object1");
        obj1.print();
        
        // 拷贝构造
        DynamicObject obj2 = obj1;
        obj2.print();
        
        // 赋值操作
        DynamicObject obj3(3, "Object3");
        obj3 = obj1;
        obj3.print();
        
        // 移动构造
        DynamicObject obj4 = move(obj1);
        obj4.print();
        
        // 移动赋值
        DynamicObject obj5(2, "Object5");
        obj5 = move(obj2);
        obj5.print();
    }  // 对象自动析构
    
    // 练习4：RAII资源管理
    cout << "\n=== RAII资源管理 ===" << endl;
    {
        ResourceManager rm1(5, "Resource1");
        rm1.print();
        
        // 移动资源
        ResourceManager rm2 = move(rm1);
        rm2.print();
        
        // 移动赋值
        ResourceManager rm3(3, "Resource3");
        rm3 = move(rm2);
        rm3.print();
    }  // 资源自动释放
    
    // 练习5：异常安全的内存管理
    cout << "\n=== 异常安全的内存管理 ===" << endl;
    {
        SafeArray sa1(5);
        SafeArray sa2(3);
        
        sa1.print();
        sa2.print();
        
        // 异常安全的赋值
        sa2 = sa1;
        sa2.print();
    }  // 自动释放内存
    
    // 练习6：智能指针使用
    SmartPointerDemo::demonstrateUniquePtr();
    SmartPointerDemo::demonstrateSharedPtr();
    SmartPointerDemo::demonstrateSmartPtrArray();
    
    // 练习7：内存泄漏检测
    cout << "\n=== 内存泄漏检测 ===" << endl;
    MemoryLeakDetector::resetStats();
    
    {
        MemoryLeakDetector* obj1 = new MemoryLeakDetector();
        MemoryLeakDetector* obj2 = new MemoryLeakDetector();
        
        delete obj1;
        // 故意不删除obj2来演示内存泄漏
    }
    
    MemoryLeakDetector::printStats();
    
    return 0;
}
