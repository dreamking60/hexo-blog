#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

// 练习1：引用基本操作
class ReferenceBasics {
public:
    // 引用声明和初始化
    static void demonstrateBasicOperations() {
        cout << "=== 引用基本操作 ===" << endl;
        
        int x = 10;
        int& ref = x;  // 引用声明并初始化
        
        cout << "变量x的值: " << x << endl;
        cout << "变量x的地址: " << &x << endl;
        cout << "引用ref的值: " << ref << endl;
        cout << "引用ref的地址: " << &ref << endl;
        cout << "x和ref是同一个变量: " << (&x == &ref) << endl;
        
        // 通过引用修改值
        ref = 20;
        cout << "通过引用修改后，x的值: " << x << endl;
        cout << "通过引用修改后，ref的值: " << ref << endl;
    }
    
    // 引用与指针的区别
    static void demonstrateReferenceVsPointer() {
        cout << "\n=== 引用与指针的区别 ===" << endl;
        
        int x = 10;
        
        // 指针方式
        int* ptr = &x;
        cout << "指针ptr的值: " << ptr << endl;
        cout << "指针ptr指向的值: " << *ptr << endl;
        cout << "指针ptr的地址: " << &ptr << endl;
        
        // 引用方式
        int& ref = x;
        cout << "引用ref的值: " << ref << endl;
        cout << "引用ref的地址: " << &ref << endl;
        
        // 指针可以重新赋值
        int y = 20;
        ptr = &y;
        cout << "指针重新赋值后指向: " << *ptr << endl;
        
        // 引用不能重新赋值
        // ref = y;  // 这是赋值操作，不是重新绑定
        cout << "引用不能重新绑定到其他变量" << endl;
    }
    
    // 引用数组元素
    static void demonstrateArrayReferences() {
        cout << "\n=== 引用数组元素 ===" << endl;
        
        int arr[5] = {1, 2, 3, 4, 5};
        
        // 创建数组元素的引用
        int& first = arr[0];
        int& last = arr[4];
        
        cout << "原数组: ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        // 通过引用修改数组元素
        first = 100;
        last = 500;
        
        cout << "通过引用修改后: ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        cout << "第一个元素: " << first << endl;
        cout << "最后一个元素: " << last << endl;
    }
};

// 练习2：引用作为函数参数
class ReferenceParameters {
public:
    // 值传递
    static void swapByValue(int a, int b) {
        cout << "值传递 - 交换前: a=" << a << ", b=" << b << endl;
        int temp = a;
        a = b;
        b = temp;
        cout << "值传递 - 交换后: a=" << a << ", b=" << b << endl;
    }
    
    // 指针传递
    static void swapByPointer(int* a, int* b) {
        cout << "指针传递 - 交换前: *a=" << *a << ", *b=" << *b << endl;
        int temp = *a;
        *a = *b;
        *b = temp;
        cout << "指针传递 - 交换后: *a=" << *a << ", *b=" << *b << endl;
    }
    
    // 引用传递
    static void swapByReference(int& a, int& b) {
        cout << "引用传递 - 交换前: a=" << a << ", b=" << b << endl;
        int temp = a;
        a = b;
        b = temp;
        cout << "引用传递 - 交换后: a=" << a << ", b=" << b << endl;
    }
    
    // 常量引用传递
    static void printValue(const int& value) {
        cout << "常量引用传递 - 值: " << value << endl;
        // value = 100;  // 错误：不能修改常量引用
    }
    
    // 大对象传递性能测试
    static void performanceTest() {
        cout << "\n=== 性能测试 ===" << endl;
        
        vector<int> largeVector(1000000, 42);
        
        // 值传递性能测试
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            processByValue(largeVector);
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // 引用传递性能测试
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            processByReference(largeVector);
        }
        end = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "值传递耗时: " << duration1.count() << " 微秒" << endl;
        cout << "引用传递耗时: " << duration2.count() << " 微秒" << endl;
        cout << "性能提升: " << (double)duration1.count() / duration2.count() << " 倍" << endl;
    }
    
private:
    static int processByValue(vector<int> vec) {
        return vec.size();  // 会拷贝整个vector
    }
    
    static int processByReference(const vector<int>& vec) {
        return vec.size();  // 不会拷贝，只是引用
    }
};

// 练习3：引用作为返回值
class ReferenceReturn {
public:
    // 返回引用的类
    class Counter {
    private:
        int count;
    public:
        Counter(int c = 0) : count(c) {}
        
        // 返回引用，可以链式操作
        Counter& increment() {
            count++;
            return *this;
        }
        
        Counter& decrement() {
            count--;
            return *this;
        }
        
        // 返回引用，可以修改
        int& getCount() {
            return count;
        }
        
        // 返回常量引用，只读
        const int& getCount() const {
            return count;
        }
        
        void print() const {
            cout << "Count: " << count << endl;
        }
    };
    
    // 返回引用的函数
    static int& getMax(int& a, int& b) {
        return (a > b) ? a : b;
    }
    
    // 返回引用的数组访问
    static int& getArrayElement(int arr[], int index) {
        return arr[index];
    }
    
    // 危险的返回局部引用（演示错误用法）
    static int& dangerousFunction() {
        int local = 42;
        return local;  // 危险：返回局部变量的引用
    }
    
    // 安全的返回引用
    static int& safeFunction(int& value) {
        return value;  // 安全：返回传入参数的引用
    }
};

// 练习4：引用与const
class ConstReferences {
public:
    // 常量引用
    static void demonstrateConstReference() {
        cout << "\n=== 常量引用 ===" << endl;
        
        int x = 10;
        const int& ref1 = x;        // 常量引用，不能通过ref1修改x
        int& ref2 = x;              // 普通引用，可以通过ref2修改x
        
        cout << "x: " << x << endl;
        cout << "ref1: " << ref1 << endl;
        cout << "ref2: " << ref2 << endl;
        
        // ref1 = 20;               // 错误：不能修改常量引用
        ref2 = 20;                  // 正确：可以修改普通引用
        
        cout << "通过ref2修改后，x: " << x << endl;
        cout << "ref1: " << ref1 << endl;
    }
    
    // 常量引用绑定常量
    static void demonstrateConstBinding() {
        cout << "\n=== 常量引用绑定 ===" << endl;
        
        const int y = 20;
        // int& ref3 = y;           // 错误：不能用普通引用绑定常量
        const int& ref4 = y;        // 正确：可以用常量引用绑定常量
        
        cout << "y: " << y << endl;
        cout << "ref4: " << ref4 << endl;
        
        // 常量引用也可以绑定非常量
        int z = 30;
        const int& ref5 = z;        // 正确：常量引用可以绑定非常量
        cout << "z: " << z << endl;
        cout << "ref5: " << ref5 << endl;
    }
    
    // 常量引用作为函数参数
    static void processConstReference(const string& str) {
        cout << "处理字符串: " << str << endl;
        cout << "字符串长度: " << str.length() << endl;
        // str[0] = 'X';  // 错误：不能修改常量引用
    }
};

// 练习5：引用与模板
class ReferenceTemplates {
public:
    // 模板函数使用引用
    template<typename T>
    static void swapValues(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
    
    // 模板函数使用常量引用
    template<typename T>
    static void printValue(const T& value) {
        cout << "值: " << value << endl;
    }
    
    // 模板类使用引用
    template<typename T>
    class ReferenceWrapper {
    private:
        T& value;
    public:
        ReferenceWrapper(T& v) : value(v) {}
        
        T& get() { return value; }
        const T& get() const { return value; }
        
        void set(const T& v) { value = v; }
    };
};

// 练习6：引用与重载
class ReferenceOverloading {
public:
    // 重载函数：左值引用
    static void process(int& value) {
        cout << "处理左值引用: " << value << endl;
    }
    
    // 重载函数：常量引用
    static void process(const int& value) {
        cout << "处理常量引用: " << value << endl;
    }
    
    // 重载函数：右值引用
    static void process(int&& value) {
        cout << "处理右值引用: " << value << endl;
    }
    
    // 重载函数：指针
    static void process(int* value) {
        cout << "处理指针: " << *value << endl;
    }
};

// 练习7：引用成员变量
class ReferenceMembers {
public:
    class Person {
    private:
        string& name;  // 引用成员变量
        int age;
    public:
        Person(string& n, int a) : name(n), age(a) {}
        
        void print() const {
            cout << "Name: " << name << ", Age: " << age << endl;
        }
        
        void changeName(string& newName) {
            name = newName;  // 修改引用绑定的对象
        }
    };
    
    static void demonstrateReferenceMembers() {
        cout << "\n=== 引用成员变量 ===" << endl;
        
        string personName = "Alice";
        Person p(personName, 25);
        p.print();
        
        string newName = "Bob";
        p.changeName(newName);
        p.print();
        
        cout << "原name变量: " << personName << endl;
    }
};

int main() {
    cout << "C++ 引用练习" << endl;
    cout << "===========" << endl;
    
    // 练习1：引用基本操作
    ReferenceBasics::demonstrateBasicOperations();
    ReferenceBasics::demonstrateReferenceVsPointer();
    ReferenceBasics::demonstrateArrayReferences();
    
    // 练习2：引用作为函数参数
    cout << "\n=== 引用作为函数参数 ===" << endl;
    int a = 10, b = 20;
    cout << "原始值: a=" << a << ", b=" << b << endl;
    
    ReferenceParameters::swapByValue(a, b);
    cout << "值传递后: a=" << a << ", b=" << b << endl;
    
    ReferenceParameters::swapByPointer(&a, &b);
    cout << "指针传递后: a=" << a << ", b=" << b << endl;
    
    ReferenceParameters::swapByReference(a, b);
    cout << "引用传递后: a=" << a << ", b=" << b << endl;
    
    ReferenceParameters::printValue(a);
    ReferenceParameters::performanceTest();
    
    // 练习3：引用作为返回值
    cout << "\n=== 引用作为返回值 ===" << endl;
    ReferenceReturn::Counter counter(5);
    counter.print();
    
    // 链式操作
    counter.increment().increment().decrement();
    counter.print();
    
    // 通过引用修改
    counter.getCount() = 100;
    counter.print();
    
    // 返回引用的函数
    int x = 10, y = 20;
    int& maxRef = ReferenceReturn::getMax(x, y);
    cout << "最大值: " << maxRef << endl;
    maxRef = 50;
    cout << "修改最大值后，y: " << y << endl;
    
    // 数组引用
    int arr[5] = {1, 2, 3, 4, 5};
    int& element = ReferenceReturn::getArrayElement(arr, 2);
    cout << "数组元素[2]: " << element << endl;
    element = 100;
    cout << "修改后数组: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 练习4：引用与const
    ConstReferences::demonstrateConstReference();
    ConstReferences::demonstrateConstBinding();
    
    string str = "Hello, World!";
    ConstReferences::processConstReference(str);
    
    // 练习5：引用与模板
    cout << "\n=== 引用与模板 ===" << endl;
    int m = 10, n = 20;
    cout << "交换前: m=" << m << ", n=" << n << endl;
    ReferenceTemplates::swapValues(m, n);
    cout << "交换后: m=" << m << ", n=" << n << endl;
    
    ReferenceTemplates::printValue(42);
    ReferenceTemplates::printValue("Hello");
    
    // 模板类使用引用
    int value = 100;
    ReferenceTemplates::ReferenceWrapper<int> wrapper(value);
    cout << "包装器中的值: " << wrapper.get() << endl;
    wrapper.set(200);
    cout << "修改后，原值: " << value << endl;
    
    // 练习6：引用与重载
    cout << "\n=== 引用与重载 ===" << endl;
    int val = 42;
    ReferenceOverloading::process(val);                    // 左值引用
    ReferenceOverloading::process(static_cast<const int&>(val));  // 常量引用
    ReferenceOverloading::process(42);                     // 右值引用
    ReferenceOverloading::process(&val);                   // 指针
    
    // 练习7：引用成员变量
    ReferenceMembers::demonstrateReferenceMembers();
    
    return 0;
}
