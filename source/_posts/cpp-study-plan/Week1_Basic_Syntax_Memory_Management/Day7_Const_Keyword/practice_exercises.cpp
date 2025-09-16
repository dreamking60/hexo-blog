#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// 练习1：常量变量
class ConstVariables {
public:
    // 基本常量变量
    static void demonstrateBasicConst() {
        cout << "=== 基本常量变量 ===" << endl;
        
        const int MAX_SIZE = 100;
        const double PI = 3.14159;
        const string NAME = "Hello World";
        
        cout << "MAX_SIZE: " << MAX_SIZE << endl;
        cout << "PI: " << PI << endl;
        cout << "NAME: " << NAME << endl;
        
        // 常量变量不能修改
        // MAX_SIZE = 200;  // 错误：不能修改常量变量
        
        // 常量变量必须初始化
        // const int x;  // 错误：常量变量必须初始化
    }
    
    // const与#define的区别
    static void demonstrateConstVsDefine() {
        cout << "\n=== const与#define的区别 ===" << endl;
        
        #define MAX_SIZE_OLD 100
        const int MAX_SIZE_NEW = 100;
        
        cout << "宏定义 MAX_SIZE_OLD: " << MAX_SIZE_OLD << endl;
        cout << "常量变量 MAX_SIZE_NEW: " << MAX_SIZE_NEW << endl;
        
        // 宏定义没有类型检查
        #define PI_OLD 3.14159
        const double PI_NEW = 3.14159;
        
        cout << "宏定义 PI_OLD: " << PI_OLD << endl;
        cout << "常量变量 PI_NEW: " << PI_NEW << endl;
    }
    
    // constexpr常量表达式
    static void demonstrateConstexpr() {
        cout << "\n=== constexpr常量表达式 ===" << endl;
        
        constexpr int BUFFER_SIZE = 1024;
        constexpr double E = 2.71828;
        constexpr int ARRAY_SIZE = 10;
        
        cout << "BUFFER_SIZE: " << BUFFER_SIZE << endl;
        cout << "E: " << E << endl;
        cout << "ARRAY_SIZE: " << ARRAY_SIZE << endl;
        
        // constexpr可以在编译时计算
        constexpr int result = BUFFER_SIZE * 2;
        cout << "编译时计算结果: " << result << endl;
        
        // 使用constexpr定义数组大小
        int array[ARRAY_SIZE];
        cout << "数组大小: " << sizeof(array) / sizeof(array[0]) << endl;
    }
};

// 练习2：常量指针与指向常量的指针
class ConstPointers {
public:
    // 指向常量的指针
    static void demonstratePointerToConst() {
        cout << "\n=== 指向常量的指针 ===" << endl;
        
        int x = 10;
        int y = 20;
        
        const int* ptr1 = &x;  // ptr1指向的int是常量
        cout << "ptr1指向的值: " << *ptr1 << endl;
        
        // *ptr1 = 30;  // 错误：不能通过ptr1修改x
        ptr1 = &y;  // 正确：ptr1可以指向其他变量
        cout << "ptr1现在指向: " << *ptr1 << endl;
        
        // 常量引用
        const int& ref1 = x;
        cout << "ref1的值: " << ref1 << endl;
        // ref1 = 40;  // 错误：不能通过ref1修改x
    }
    
    // 常量指针
    static void demonstrateConstPointer() {
        cout << "\n=== 常量指针 ===" << endl;
        
        int x = 10;
        int y = 20;
        
        int* const ptr2 = &x;  // ptr2是常量指针
        cout << "ptr2指向的值: " << *ptr2 << endl;
        
        *ptr2 = 30;  // 正确：可以通过ptr2修改x
        cout << "修改后x的值: " << x << endl;
        
        // ptr2 = &y;  // 错误：ptr2不能指向其他变量
    }
    
    // 指向常量的常量指针
    static void demonstrateConstPointerToConst() {
        cout << "\n=== 指向常量的常量指针 ===" << endl;
        
        int x = 10;
        int y = 20;
        
        const int* const ptr3 = &x;  // ptr3是常量指针，指向常量
        cout << "ptr3指向的值: " << *ptr3 << endl;
        
        // *ptr3 = 30;  // 错误：不能通过ptr3修改x
        // ptr3 = &y;  // 错误：ptr3不能指向其他变量
    }
    
    // 指针的const修饰位置
    static void demonstrateConstPosition() {
        cout << "\n=== 指针的const修饰位置 ===" << endl;
        
        int x = 10;
        int y = 20;
        
        // 指向常量的指针
        const int* ptr1 = &x;
        int const* ptr2 = &x;  // 等价于上面
        
        // 常量指针
        int* const ptr3 = &x;
        
        // 指向常量的常量指针
        const int* const ptr4 = &x;
        int const* const ptr5 = &x;  // 等价于上面
        
        cout << "ptr1: " << *ptr1 << endl;
        cout << "ptr2: " << *ptr2 << endl;
        cout << "ptr3: " << *ptr3 << endl;
        cout << "ptr4: " << *ptr4 << endl;
        cout << "ptr5: " << *ptr5 << endl;
    }
};

// 练习3：常量引用
class ConstReferences {
public:
    // 常量引用基本用法
    static void demonstrateBasicConstReference() {
        cout << "\n=== 常量引用基本用法 ===" << endl;
        
        int x = 10;
        const int& ref1 = x;  // 常量引用
        cout << "ref1的值: " << ref1 << endl;
        
        // ref1 = 20;  // 错误：不能通过ref1修改x
        
        // 常量引用可以绑定到常量
        const int y = 20;
        const int& ref2 = y;  // 正确
        cout << "ref2的值: " << ref2 << endl;
        
        // 常量引用可以绑定到临时对象
        const int& ref3 = 42;  // 正确
        cout << "ref3的值: " << ref3 << endl;
        
        // 非常量引用不能绑定到临时对象
        // int& ref4 = 42;  // 错误
    }
    
    // 常量引用作为函数参数
    static void processValue(const int& value) {
        cout << "处理值: " << value << endl;
        // value = 100;  // 错误：不能修改常量引用
    }
    
    static void processString(const string& str) {
        cout << "处理字符串: " << str << endl;
        cout << "字符串长度: " << str.length() << endl;
        // str[0] = 'X';  // 错误：不能修改常量引用
    }
    
    // 常量引用与临时对象
    static void demonstrateConstRefWithTemp() {
        cout << "\n=== 常量引用与临时对象 ===" << endl;
        
        // 常量引用可以绑定到临时对象
        const int& ref1 = 42;
        cout << "ref1: " << ref1 << endl;
        
        // 常量引用可以绑定到表达式结果
        const int& ref2 = 10 + 20;
        cout << "ref2: " << ref2 << endl;
        
        // 常量引用可以绑定到函数返回值
        const int& ref3 = getValue();
        cout << "ref3: " << ref3 << endl;
    }
    
private:
    static int getValue() {
        return 100;
    }
};

// 练习4：常量成员函数
class ConstMemberFunctions {
public:
    class MyClass {
    private:
        int value;
        mutable int counter;  // mutable成员变量可以在const成员函数中修改
        string name;
        
    public:
        MyClass(int v, const string& n) : value(v), counter(0), name(n) {}
        
        // 普通成员函数
        int getValue() {
            cout << "调用普通getValue()" << endl;
            return value;
        }
        
        // 常量成员函数
        int getValue() const {
            cout << "调用常量getValue()" << endl;
            counter++;  // 正确：mutable成员变量可以在const成员函数中修改
            return value;
        }
        
        // 常量成员函数重载
        void print() const {
            cout << "常量成员函数 - Name: " << name << ", Value: " << value << endl;
        }
        
        void print() {
            cout << "普通成员函数 - Name: " << name << ", Value: " << value << endl;
        }
        
        // 修改成员变量的函数不能是const
        void setValue(int v) {
            value = v;
        }
        
        void setName(const string& n) {
            name = n;
        }
        
        // 获取计数器值
        int getCounter() const {
            return counter;
        }
    };
    
    static void demonstrateConstMemberFunctions() {
        cout << "\n=== 常量成员函数 ===" << endl;
        
        MyClass obj(42, "Object1");
        const MyClass constObj(100, "ConstObject");
        
        // 调用普通成员函数
        obj.print();
        cout << "obj.getValue(): " << obj.getValue() << endl;
        
        // 调用常量成员函数
        constObj.print();
        cout << "constObj.getValue(): " << constObj.getValue() << endl;
        
        // 修改对象
        obj.setValue(200);
        obj.setName("ModifiedObject");
        obj.print();
        
        // 常量对象不能调用非const成员函数
        // constObj.setValue(300);  // 错误：常量对象不能调用非const成员函数
        
        // 显示计数器
        cout << "obj.getCounter(): " << obj.getCounter() << endl;
        cout << "constObj.getCounter(): " << constObj.getCounter() << endl;
    }
};

// 练习5：const_cast的使用
class ConstCastDemo {
public:
    // const_cast的基本用法
    static void demonstrateBasicConstCast() {
        cout << "\n=== const_cast基本用法 ===" << endl;
        
        int x = 10;
        const int* ptr = &x;
        
        cout << "原始值: " << x << endl;
        cout << "通过const指针: " << *ptr << endl;
        
        // 移除const修饰
        int* mutablePtr = const_cast<int*>(ptr);
        *mutablePtr = 20;
        
        cout << "修改后值: " << x << endl;
        cout << "通过const指针: " << *ptr << endl;
    }
    
    // const_cast添加const修饰
    static void demonstrateAddingConst() {
        cout << "\n=== const_cast添加const修饰 ===" << endl;
        
        int x = 10;
        int* ptr = &x;
        
        cout << "原始值: " << x << endl;
        cout << "通过普通指针: " << *ptr << endl;
        
        // 添加const修饰
        const int* constPtr = const_cast<const int*>(ptr);
        cout << "通过const指针: " << *constPtr << endl;
        
        // 仍然可以通过原指针修改
        *ptr = 20;
        cout << "修改后值: " << x << endl;
        cout << "通过const指针: " << *constPtr << endl;
    }
    
    // const_cast的危险用法
    static void demonstrateDangerousConstCast() {
        cout << "\n=== const_cast危险用法 ===" << endl;
        
        const int y = 30;  // 真正的常量
        cout << "原始常量值: " << y << endl;
        
        // 移除const修饰（危险）
        int* ptr = const_cast<int*>(&y);
        cout << "通过const_cast后的指针: " << *ptr << endl;
        
        // 尝试修改（未定义行为）
        *ptr = 40;
        cout << "修改后值: " << y << endl;  // 可能仍然是30
        cout << "通过指针的值: " << *ptr << endl;  // 可能是40
        
        cout << "警告：修改真正的常量是未定义行为！" << endl;
    }
    
    // 安全的const_cast使用
    static void demonstrateSafeConstCast() {
        cout << "\n=== 安全的const_cast使用 ===" << endl;
        
        int x = 10;
        const int* ptr = &x;  // 指向非常量的const指针
        
        cout << "原始值: " << x << endl;
        
        // 安全地移除const修饰
        int* mutablePtr = const_cast<int*>(ptr);
        *mutablePtr = 20;
        
        cout << "修改后值: " << x << endl;
        cout << "这是安全的，因为x不是真正的常量" << endl;
    }
};

// 练习6：const与模板
class ConstTemplates {
public:
    // 模板函数使用const
    template<typename T>
    static void printValue(const T& value) {
        cout << "值: " << value << endl;
    }
    
    template<typename T>
    static void processArray(const T* array, size_t size) {
        cout << "数组内容: ";
        for (size_t i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    
    // 模板类使用const
    template<typename T>
    class ConstWrapper {
    private:
        T value;
        
    public:
        ConstWrapper(const T& v) : value(v) {}
        
        const T& getValue() const {
            return value;
        }
        
        void print() const {
            cout << "ConstWrapper值: " << value << endl;
        }
    };
    
    static void demonstrateConstTemplates() {
        cout << "\n=== const与模板 ===" << endl;
        
        // 模板函数
        printValue(42);
        printValue(3.14);
        printValue(string("Hello"));
        
        // 模板数组
        int intArray[] = {1, 2, 3, 4, 5};
        processArray(intArray, 5);
        
        double doubleArray[] = {1.1, 2.2, 3.3};
        processArray(doubleArray, 3);
        
        // 模板类
        ConstWrapper<int> intWrapper(100);
        intWrapper.print();
        
        ConstWrapper<string> stringWrapper("Hello World");
        stringWrapper.print();
    }
};

// 练习7：const与智能指针
class ConstSmartPointers {
public:
    static void demonstrateConstSmartPointers() {
        cout << "\n=== const与智能指针 ===" << endl;
        
        // const unique_ptr
        const unique_ptr<int> constPtr = make_unique<int>(42);
        cout << "const unique_ptr值: " << *constPtr << endl;
        // *constPtr = 100;  // 错误：不能修改const unique_ptr指向的值
        // constPtr.reset();  // 错误：不能修改const unique_ptr本身
        
        // unique_ptr指向const对象
        unique_ptr<const int> ptrToConst = make_unique<const int>(100);
        cout << "unique_ptr指向const值: " << *ptrToConst << endl;
        // *ptrToConst = 200;  // 错误：不能修改const对象
        ptrToConst.reset();  // 正确：可以修改unique_ptr本身
        
        // const shared_ptr
        const shared_ptr<int> constSharedPtr = make_shared<int>(200);
        cout << "const shared_ptr值: " << *constSharedPtr << endl;
        cout << "引用计数: " << constSharedPtr.use_count() << endl;
        
        // shared_ptr指向const对象
        shared_ptr<const int> sharedPtrToConst = make_shared<const int>(300);
        cout << "shared_ptr指向const值: " << *sharedPtrToConst << endl;
        cout << "引用计数: " << sharedPtrToConst.use_count() << endl;
    }
};

int main() {
    cout << "C++ const关键字练习" << endl;
    cout << "=================" << endl;
    
    // 练习1：常量变量
    ConstVariables::demonstrateBasicConst();
    ConstVariables::demonstrateConstVsDefine();
    ConstVariables::demonstrateConstexpr();
    
    // 练习2：常量指针与指向常量的指针
    ConstPointers::demonstratePointerToConst();
    ConstPointers::demonstrateConstPointer();
    ConstPointers::demonstrateConstPointerToConst();
    ConstPointers::demonstrateConstPosition();
    
    // 练习3：常量引用
    ConstReferences::demonstrateBasicConstReference();
    ConstReferences::demonstrateConstRefWithTemp();
    
    // 常量引用作为函数参数
    cout << "\n=== 常量引用作为函数参数 ===" << endl;
    ConstReferences::processValue(42);
    ConstReferences::processString("Hello, World!");
    
    // 练习4：常量成员函数
    ConstMemberFunctions::demonstrateConstMemberFunctions();
    
    // 练习5：const_cast的使用
    ConstCastDemo::demonstrateBasicConstCast();
    ConstCastDemo::demonstrateAddingConst();
    ConstCastDemo::demonstrateDangerousConstCast();
    ConstCastDemo::demonstrateSafeConstCast();
    
    // 练习6：const与模板
    ConstTemplates::demonstrateConstTemplates();
    
    // 练习7：const与智能指针
    ConstSmartPointers::demonstrateConstSmartPointers();
    
    return 0;
}
