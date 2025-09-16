#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// 练习1：指针基本操作
class PointerBasics {
public:
    // 指针声明和初始化
    static void demonstrateBasicOperations() {
        cout << "=== 指针基本操作 ===" << endl;
        
        int x = 10;
        int* ptr = &x;  // 指针声明并初始化
        
        cout << "变量x的值: " << x << endl;
        cout << "变量x的地址: " << &x << endl;
        cout << "指针ptr的值: " << ptr << endl;
        cout << "指针ptr指向的值: " << *ptr << endl;
        cout << "指针ptr的地址: " << &ptr << endl;
        
        // 通过指针修改值
        *ptr = 20;
        cout << "通过指针修改后，x的值: " << x << endl;
    }
    
    // 指针运算
    static void demonstratePointerArithmetic() {
        cout << "\n=== 指针运算 ===" << endl;
        
        int arr[5] = {10, 20, 30, 40, 50};
        int* ptr = arr;  // 指向数组首元素
        
        cout << "数组: ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        cout << "指针地址: ";
        for (int i = 0; i < 5; i++) {
            cout << (ptr + i) << " ";
        }
        cout << endl;
        
        cout << "通过指针访问: ";
        for (int i = 0; i < 5; i++) {
            cout << *(ptr + i) << " ";
        }
        cout << endl;
        
        // 指针递增
        cout << "指针递增访问: ";
        ptr = arr;  // 重置指针
        for (int i = 0; i < 5; i++) {
            cout << *ptr << " ";
            ptr++;
        }
        cout << endl;
        
        // 指针递减
        cout << "指针递减访问: ";
        ptr = arr + 4;  // 指向最后一个元素
        for (int i = 0; i < 5; i++) {
            cout << *ptr << " ";
            ptr--;
        }
        cout << endl;
    }
    
    // 指针比较
    static void demonstratePointerComparison() {
        cout << "\n=== 指针比较 ===" << endl;
        
        int arr[5] = {10, 20, 30, 40, 50};
        int* ptr1 = arr;
        int* ptr2 = arr + 2;
        int* ptr3 = arr + 4;
        
        cout << "ptr1地址: " << ptr1 << endl;
        cout << "ptr2地址: " << ptr2 << endl;
        cout << "ptr3地址: " << ptr3 << endl;
        
        cout << "ptr1 < ptr2: " << (ptr1 < ptr2) << endl;
        cout << "ptr2 < ptr3: " << (ptr2 < ptr3) << endl;
        cout << "ptr1 == ptr2: " << (ptr1 == ptr2) << endl;
        
        cout << "ptr2 - ptr1: " << (ptr2 - ptr1) << endl;
        cout << "ptr3 - ptr1: " << (ptr3 - ptr1) << endl;
    }
};

// 练习2：指针与数组
class PointerArrayOperations {
public:
    // 数组名作为指针
    static void demonstrateArrayAsPointer() {
        cout << "\n=== 数组名作为指针 ===" << endl;
        
        int arr[5] = {1, 2, 3, 4, 5};
        
        cout << "arr: " << arr << endl;
        cout << "&arr[0]: " << &arr[0] << endl;
        cout << "arr == &arr[0]: " << (arr == &arr[0]) << endl;
        
        // 访问数组元素的多种方式
        cout << "访问arr[2]的多种方式:" << endl;
        cout << "arr[2]: " << arr[2] << endl;
        cout << "*(arr + 2): " << *(arr + 2) << endl;
        cout << "*(2 + arr): " << *(2 + arr) << endl;
        cout << "2[arr]: " << 2[arr] << endl;  // 不推荐但合法
    }
    
    // 指针数组
    static void demonstratePointerArray() {
        cout << "\n=== 指针数组 ===" << endl;
        
        int a = 10, b = 20, c = 30;
        int* ptrArray[3] = {&a, &b, &c};
        
        cout << "指针数组内容:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "ptrArray[" << i << "] = " << ptrArray[i] 
                 << ", 指向的值 = " << *ptrArray[i] << endl;
        }
    }
    
    // 数组指针
    static void demonstrateArrayPointer() {
        cout << "\n=== 数组指针 ===" << endl;
        
        int arr[5] = {1, 2, 3, 4, 5};
        int (*arrayPtr)[5] = &arr;  // 指向包含5个int的数组
        
        cout << "数组指针访问元素:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "(*arrayPtr)[" << i << "] = " << (*arrayPtr)[i] << endl;
        }
    }
    
    // 二维数组的指针
    static void demonstrate2DArrayPointer() {
        cout << "\n=== 二维数组指针 ===" << endl;
        
        int matrix[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        };
        
        // 使用指针访问二维数组
        int* ptr = &matrix[0][0];
        cout << "二维数组内容:" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                cout << *(ptr + i * 4 + j) << "\t";
            }
            cout << endl;
        }
    }
};

// 练习3：指针作为函数参数
class PointerFunctions {
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
    
    // 引用传递（C++推荐）
    static void swapByReference(int& a, int& b) {
        cout << "引用传递 - 交换前: a=" << a << ", b=" << b << endl;
        int temp = a;
        a = b;
        b = temp;
        cout << "引用传递 - 交换后: a=" << a << ", b=" << b << endl;
    }
    
    // 数组作为指针参数
    static void printArray(int* arr, int size) {
        cout << "数组内容: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    // 修改数组元素
    static void modifyArray(int* arr, int size, int multiplier) {
        for (int i = 0; i < size; i++) {
            arr[i] *= multiplier;
        }
    }
    
    // 返回指针的函数
    static int* findMax(int* arr, int size) {
        if (size <= 0) return nullptr;
        
        int* maxPtr = arr;
        for (int i = 1; i < size; i++) {
            if (arr[i] > *maxPtr) {
                maxPtr = &arr[i];
            }
        }
        return maxPtr;
    }
    
    // 字符串操作
    static int stringLength(const char* str) {
        int len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }
    
    static void stringCopy(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
};

// 练习4：动态内存管理
class DynamicMemory {
public:
    // 动态分配单个变量
    static void demonstrateSingleAllocation() {
        cout << "\n=== 动态分配单个变量 ===" << endl;
        
        int* ptr = new int(42);
        cout << "动态分配的值: " << *ptr << endl;
        cout << "动态分配的地址: " << ptr << endl;
        
        *ptr = 100;
        cout << "修改后的值: " << *ptr << endl;
        
        delete ptr;  // 释放内存
        ptr = nullptr;  // 避免野指针
        cout << "内存已释放" << endl;
    }
    
    // 动态分配数组
    static void demonstrateArrayAllocation() {
        cout << "\n=== 动态分配数组 ===" << endl;
        
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
        
        delete[] arr;  // 释放数组内存
        arr = nullptr;
        cout << "数组内存已释放" << endl;
    }
    
    // 动态分配二维数组
    static void demonstrate2DArrayAllocation() {
        cout << "\n=== 动态分配二维数组 ===" << endl;
        
        int rows = 3, cols = 4;
        int** matrix = new int*[rows];
        
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
        
        // 初始化矩阵
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = i * cols + j + 1;
            }
        }
        
        // 打印矩阵
        cout << "动态二维数组:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
        
        // 释放内存
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        cout << "二维数组内存已释放" << endl;
    }
    
    // 创建动态数组的函数
    static int* createArray(int size) {
        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = i * i;
        }
        return arr;
    }
    
    // 释放动态数组的函数
    static void deleteArray(int* arr) {
        delete[] arr;
        arr = nullptr;
    }
};

// 练习5：指针链表
class PointerLinkedList {
public:
    struct ListNode {
        int data;
        ListNode* next;
        
        ListNode(int val) : data(val), next(nullptr) {}
    };
    
    // 创建链表
    static ListNode* createList(int arr[], int size) {
        if (size == 0) return nullptr;
        
        ListNode* head = new ListNode(arr[0]);
        ListNode* current = head;
        
        for (int i = 1; i < size; i++) {
            current->next = new ListNode(arr[i]);
            current = current->next;
        }
        
        return head;
    }
    
    // 打印链表
    static void printList(ListNode* head) {
        ListNode* current = head;
        cout << "链表内容: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // 在链表末尾添加节点
    static void appendNode(ListNode*& head, int value) {
        ListNode* newNode = new ListNode(value);
        
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        ListNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    // 在链表开头添加节点
    static void prependNode(ListNode*& head, int value) {
        ListNode* newNode = new ListNode(value);
        newNode->next = head;
        head = newNode;
    }
    
    // 删除链表
    static void deleteList(ListNode*& head) {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // 查找节点
    static ListNode* findNode(ListNode* head, int value) {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    // 反转链表
    static ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
};

// 练习6：二级指针
class DoublePointer {
public:
    // 二级指针基本操作
    static void demonstrateDoublePointer() {
        cout << "\n=== 二级指针 ===" << endl;
        
        int x = 10;
        int* ptr1 = &x;       // 一级指针
        int** ptr2 = &ptr1;   // 二级指针
        
        cout << "x: " << x << endl;
        cout << "&x: " << &x << endl;
        cout << "ptr1: " << ptr1 << endl;
        cout << "&ptr1: " << &ptr1 << endl;
        cout << "ptr2: " << ptr2 << endl;
        cout << "*ptr2: " << *ptr2 << endl;
        cout << "**ptr2: " << **ptr2 << endl;
        
        // 通过二级指针修改值
        **ptr2 = 20;
        cout << "通过二级指针修改后，x: " << x << endl;
    }
    
    // 指针数组的指针
    static void demonstratePointerArrayPointer() {
        cout << "\n=== 指针数组的指针 ===" << endl;
        
        int a = 1, b = 2, c = 3;
        int* ptrArray[3] = {&a, &b, &c};
        int** ptrToPtrArray = ptrArray;
        
        cout << "通过指针数组的指针访问:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "ptrToPtrArray[" << i << "] = " << ptrToPtrArray[i] 
                 << ", 指向的值 = " << *ptrToPtrArray[i] << endl;
        }
    }
};

int main() {
    cout << "C++ 指针基础练习" << endl;
    cout << "===============" << endl;
    
    // 练习1：指针基本操作
    PointerBasics::demonstrateBasicOperations();
    PointerBasics::demonstratePointerArithmetic();
    PointerBasics::demonstratePointerComparison();
    
    // 练习2：指针与数组
    PointerArrayOperations::demonstrateArrayAsPointer();
    PointerArrayOperations::demonstratePointerArray();
    PointerArrayOperations::demonstrateArrayPointer();
    PointerArrayOperations::demonstrate2DArrayPointer();
    
    // 练习3：指针作为函数参数
    cout << "\n=== 指针作为函数参数 ===" << endl;
    int a = 10, b = 20;
    cout << "原始值: a=" << a << ", b=" << b << endl;
    
    PointerFunctions::swapByValue(a, b);
    cout << "值传递后: a=" << a << ", b=" << b << endl;
    
    PointerFunctions::swapByPointer(&a, &b);
    cout << "指针传递后: a=" << a << ", b=" << b << endl;
    
    PointerFunctions::swapByReference(a, b);
    cout << "引用传递后: a=" << a << ", b=" << b << endl;
    
    // 数组操作
    int arr[5] = {1, 2, 3, 4, 5};
    PointerFunctions::printArray(arr, 5);
    PointerFunctions::modifyArray(arr, 5, 2);
    cout << "乘以2后: ";
    PointerFunctions::printArray(arr, 5);
    
    // 查找最大值
    int* maxPtr = PointerFunctions::findMax(arr, 5);
    if (maxPtr != nullptr) {
        cout << "最大值: " << *maxPtr << " 位置: " << (maxPtr - arr) << endl;
    }
    
    // 字符串操作
    const char* str = "Hello, World!";
    cout << "字符串长度: " << PointerFunctions::stringLength(str) << endl;
    
    char dest[50];
    PointerFunctions::stringCopy(dest, str);
    cout << "复制的字符串: " << dest << endl;
    
    // 练习4：动态内存管理
    DynamicMemory::demonstrateSingleAllocation();
    DynamicMemory::demonstrateArrayAllocation();
    DynamicMemory::demonstrate2DArrayAllocation();
    
    // 动态数组的创建和释放
    int* dynamicArr = DynamicMemory::createArray(5);
    cout << "动态创建的数组: ";
    for (int i = 0; i < 5; i++) {
        cout << dynamicArr[i] << " ";
    }
    cout << endl;
    DynamicMemory::deleteArray(dynamicArr);
    
    // 练习5：指针链表
    cout << "\n=== 指针链表 ===" << endl;
    int listData[] = {1, 2, 3, 4, 5};
    PointerLinkedList::ListNode* head = PointerLinkedList::createList(listData, 5);
    PointerLinkedList::printList(head);
    
    PointerLinkedList::appendNode(head, 6);
    PointerLinkedList::prependNode(head, 0);
    PointerLinkedList::printList(head);
    
    // 查找节点
    PointerLinkedList::ListNode* found = PointerLinkedList::findNode(head, 3);
    if (found != nullptr) {
        cout << "找到节点: " << found->data << endl;
    }
    
    // 反转链表
    head = PointerLinkedList::reverseList(head);
    cout << "反转后的链表: ";
    PointerLinkedList::printList(head);
    
    // 释放链表
    PointerLinkedList::deleteList(head);
    cout << "链表已释放" << endl;
    
    // 练习6：二级指针
    DoublePointer::demonstrateDoublePointer();
    DoublePointer::demonstratePointerArrayPointer();
    
    return 0;
}
