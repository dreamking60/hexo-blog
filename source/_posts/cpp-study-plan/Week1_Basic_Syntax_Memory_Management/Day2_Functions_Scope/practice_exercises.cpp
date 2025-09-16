#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

// 练习1：基本函数操作
class MathUtils {
public:
    // 基本运算
    static int add(int a, int b) {
        return a + b;
    }
    
    static double add(double a, double b) {
        return a + b;
    }
    
    static int subtract(int a, int b) {
        return a - b;
    }
    
    static int multiply(int a, int b) {
        return a * b;
    }
    
    static double divide(double a, double b) {
        if (b == 0) {
            throw invalid_argument("Division by zero!");
        }
        return a / b;
    }
    
    // 幂运算
    static long long power(int base, int exponent) {
        if (exponent < 0) {
            throw invalid_argument("Negative exponent not supported!");
        }
        if (exponent == 0) return 1;
        if (exponent == 1) return base;
        
        long long result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
    
    // 快速幂运算（递归）
    static long long fastPower(int base, int exponent) {
        if (exponent == 0) return 1;
        if (exponent == 1) return base;
        
        long long half = fastPower(base, exponent / 2);
        if (exponent % 2 == 0) {
            return half * half;
        } else {
            return half * half * base;
        }
    }
};

// 练习2：参数传递比较
class ParameterPassingDemo {
public:
    // 值传递
    static void passByValue(int x) {
        cout << "值传递 - 函数内修改前: " << x << endl;
        x = 100;
        cout << "值传递 - 函数内修改后: " << x << endl;
    }
    
    // 引用传递
    static void passByReference(int& x) {
        cout << "引用传递 - 函数内修改前: " << x << endl;
        x = 100;
        cout << "引用传递 - 函数内修改后: " << x << endl;
    }
    
    // 指针传递
    static void passByPointer(int* x) {
        cout << "指针传递 - 函数内修改前: " << *x << endl;
        *x = 100;
        cout << "指针传递 - 函数内修改后: " << *x << endl;
    }
    
    // 常量引用传递（推荐用于大对象）
    static void passByConstReference(const string& str) {
        cout << "常量引用传递 - 字符串长度: " << str.length() << endl;
        // str[0] = 'X';  // 编译错误：不能修改常量引用
    }
    
    // 性能测试
    static void performanceTest() {
        const int SIZE = 1000000;
        vector<int> largeVector(SIZE, 42);
        
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
    }
    
private:
    static int processByValue(vector<int> vec) {
        return vec.size();  // 会拷贝整个vector
    }
    
    static int processByReference(const vector<int>& vec) {
        return vec.size();  // 不会拷贝，只是引用
    }
};

// 练习3：函数重载应用
class StringProcessor {
public:
    // 构造函数重载
    StringProcessor() : data("") {}
    StringProcessor(const string& str) : data(str) {}
    StringProcessor(const char* str) : data(str) {}
    StringProcessor(int length, char fill) : data(length, fill) {}
    
    // 处理函数重载
    string process() {
        return "处理: " + data;
    }
    
    string process(const string& suffix) {
        return "处理: " + data + suffix;
    }
    
    string process(const string& prefix, const string& suffix) {
        return prefix + "处理: " + data + suffix;
    }
    
    // 查找函数重载
    int find(char c) {
        return data.find(c);
    }
    
    int find(const string& substr) {
        return data.find(substr);
    }
    
    int find(char c, int startPos) {
        return data.find(c, startPos);
    }
    
    // 替换函数重载
    string replace(char oldChar, char newChar) {
        string result = data;
        for (char& c : result) {
            if (c == oldChar) c = newChar;
        }
        return result;
    }
    
    string replace(const string& oldStr, const string& newStr) {
        string result = data;
        size_t pos = 0;
        while ((pos = result.find(oldStr, pos)) != string::npos) {
            result.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
        return result;
    }
    
    void print() const {
        cout << "数据: " << data << endl;
    }
    
private:
    string data;
};

// 练习4：递归算法实现
class RecursiveAlgorithms {
public:
    // 斐波那契数列（递归）
    static int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // 斐波那契数列（记忆化递归）
    static int fibonacciMemo(int n) {
        static vector<int> memo(100, -1);
        if (n <= 1) return n;
        if (memo[n] != -1) return memo[n];
        memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
        return memo[n];
    }
    
    // 阶乘（递归）
    static long long factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
    
    // 阶乘（尾递归）
    static long long factorialTail(int n, long long acc = 1) {
        if (n <= 1) return acc;
        return factorialTail(n - 1, n * acc);
    }
    
    // 汉诺塔
    static void hanoi(int n, char from, char to, char aux) {
        if (n == 1) {
            cout << "移动盘子 1 从 " << from << " 到 " << to << endl;
            return;
        }
        hanoi(n - 1, from, aux, to);
        cout << "移动盘子 " << n << " 从 " << from << " 到 " << to << endl;
        hanoi(n - 1, aux, to, from);
    }
    
    // 快速排序（递归）
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }
    
    // 二分查找（递归）
    static int binarySearch(const vector<int>& arr, int target, int left, int right) {
        if (left > right) return -1;
        
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] > target) {
            return binarySearch(arr, target, left, mid - 1);
        } else {
            return binarySearch(arr, target, mid + 1, right);
        }
    }
    
private:
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

// 练习5：作用域演示
class ScopeDemo {
public:
    static int globalVar;  // 全局变量声明
    
    static void demonstrateScope() {
        cout << "=== 作用域演示 ===" << endl;
        
        int localVar = 10;
        cout << "局部变量: " << localVar << endl;
        cout << "全局变量: " << globalVar << endl;
        
        {
            int blockVar = 20;
            cout << "块作用域变量: " << blockVar << endl;
            cout << "局部变量（在块内）: " << localVar << endl;
        }
        // cout << blockVar << endl;  // 编译错误：blockVar不在作用域内
        
        static int staticVar = 30;
        staticVar++;
        cout << "静态局部变量: " << staticVar << endl;
    }
    
    static void modifyGlobal() {
        globalVar = 100;
        cout << "修改后的全局变量: " << globalVar << endl;
    }
};

// 静态成员变量定义
int ScopeDemo::globalVar = 50;

// 练习6：默认参数演示
class DefaultParameterDemo {
public:
    static void printInfo(string name, int age = 18, string city = "Unknown", string country = "Unknown") {
        cout << "姓名: " << name << ", 年龄: " << age 
             << ", 城市: " << city << ", 国家: " << country << endl;
    }
    
    static void demonstrateDefaultParams() {
        cout << "\n=== 默认参数演示 ===" << endl;
        
        printInfo("Alice");                                    // 使用所有默认参数
        printInfo("Bob", 25);                                  // 部分使用默认参数
        printInfo("Charlie", 30, "Beijing");                   // 部分使用默认参数
        printInfo("David", 35, "Shanghai", "China");          // 不使用默认参数
    }
};

// 练习7：内联函数演示
class InlineFunctionDemo {
public:
    // 内联函数（适合简单、频繁调用的函数）
    inline static int square(int x) {
        return x * x;
    }
    
    inline static int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    inline static bool isEven(int x) {
        return x % 2 == 0;
    }
    
    static void demonstrateInline() {
        cout << "\n=== 内联函数演示 ===" << endl;
        
        int a = 5, b = 10;
        cout << "square(" << a << ") = " << square(a) << endl;
        cout << "max(" << a << ", " << b << ") = " << max(a, b) << endl;
        cout << "isEven(" << a << ") = " << (isEven(a) ? "true" : "false") << endl;
    }
};

int main() {
    cout << "C++ 函数与作用域练习" << endl;
    cout << "===================" << endl;
    
    // 练习1：基本函数操作
    cout << "\n=== 基本函数操作 ===" << endl;
    cout << "5 + 3 = " << MathUtils::add(5, 3) << endl;
    cout << "5.5 + 3.2 = " << MathUtils::add(5.5, 3.2) << endl;
    cout << "2^10 = " << MathUtils::power(2, 10) << endl;
    cout << "2^10 (快速幂) = " << MathUtils::fastPower(2, 10) << endl;
    
    // 练习2：参数传递演示
    cout << "\n=== 参数传递演示 ===" << endl;
    int value = 10;
    cout << "原始值: " << value << endl;
    
    ParameterPassingDemo::passByValue(value);
    cout << "值传递后: " << value << endl;
    
    ParameterPassingDemo::passByReference(value);
    cout << "引用传递后: " << value << endl;
    
    ParameterPassingDemo::passByPointer(&value);
    cout << "指针传递后: " << value << endl;
    
    string str = "Hello, World!";
    ParameterPassingDemo::passByConstReference(str);
    
    // 练习3：函数重载应用
    cout << "\n=== 函数重载应用 ===" << endl;
    StringProcessor sp1("Hello");
    StringProcessor sp2(10, '*');
    
    sp1.print();
    cout << sp1.process() << endl;
    cout << sp1.process("!!!") << endl;
    cout << sp1.replace('l', 'L') << endl;
    
    sp2.print();
    cout << sp2.process() << endl;
    
    // 练习4：递归算法
    cout << "\n=== 递归算法 ===" << endl;
    cout << "斐波那契数列前10项: ";
    for (int i = 0; i < 10; i++) {
        cout << RecursiveAlgorithms::fibonacci(i) << " ";
    }
    cout << endl;
    
    cout << "10! = " << RecursiveAlgorithms::factorial(10) << endl;
    cout << "10! (尾递归) = " << RecursiveAlgorithms::factorialTail(10) << endl;
    
    cout << "\n汉诺塔（3个盘子）:" << endl;
    RecursiveAlgorithms::hanoi(3, 'A', 'C', 'B');
    
    // 练习5：作用域演示
    ScopeDemo::demonstrateScope();
    ScopeDemo::modifyGlobal();
    ScopeDemo::demonstrateScope();  // 再次调用，观察静态变量
    
    // 练习6：默认参数演示
    DefaultParameterDemo::demonstrateDefaultParams();
    
    // 练习7：内联函数演示
    InlineFunctionDemo::demonstrateInline();
    
    // 练习8：性能测试
    cout << "\n=== 性能测试 ===" << endl;
    ParameterPassingDemo::performanceTest();
    
    // 练习9：排序和查找
    cout << "\n=== 排序和查找 ===" << endl;
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    cout << "原数组: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    RecursiveAlgorithms::quickSort(arr, 0, arr.size() - 1);
    cout << "排序后: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    int target = 25;
    int index = RecursiveAlgorithms::binarySearch(arr, target, 0, arr.size() - 1);
    cout << "查找 " << target << " 的索引: " << index << endl;
    
    return 0;
}
