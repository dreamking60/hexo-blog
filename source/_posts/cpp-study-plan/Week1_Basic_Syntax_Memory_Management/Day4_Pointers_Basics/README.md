# 第4天：指针基础

## 学习目标
深入理解指针的概念和使用，掌握指针的各种操作和应用场景。

## 学习内容

### 1. 指针的基本概念
- 指针的定义与声明
- 指针的初始化
- 指针的解引用
- 指针的地址运算
- 空指针与野指针

### 2. 指针运算
- 指针算术运算
- 指针比较
- 指针与数组的关系
- 指针的递增递减
- 指针的差值运算

### 3. 指针与数组
- 数组名作为指针
- 指针访问数组元素
- 多维数组的指针
- 指针数组
- 数组指针

### 4. 指针作为函数参数
- 值传递vs指针传递
- 指针传递的优势
- 指针传递的注意事项
- 指针的const修饰

### 5. 指针的指针
- 二级指针的概念
- 指针数组的指针
- 动态内存分配中的指针
- 指针链表的实现

## 重点概念

### 指针的基本操作
```cpp
int x = 10;
int* ptr = &x;        // 指针声明并初始化
cout << "x的值: " << x << endl;
cout << "x的地址: " << &x << endl;
cout << "ptr的值: " << ptr << endl;
cout << "ptr指向的值: " << *ptr << endl;
cout << "ptr的地址: " << &ptr << endl;
```

### 指针运算
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;       // 指向数组首元素

// 指针算术
cout << "ptr: " << ptr << endl;
cout << "ptr+1: " << ptr + 1 << endl;
cout << "ptr+2: " << ptr + 2 << endl;

// 通过指针访问数组元素
for (int i = 0; i < 5; i++) {
    cout << "arr[" << i << "] = " << *(ptr + i) << endl;
}

// 指针递增
for (int i = 0; i < 5; i++) {
    cout << "元素: " << *ptr << endl;
    ptr++;  // 指针递增
}
```

### 指针与数组的关系
```cpp
int arr[5] = {1, 2, 3, 4, 5};

// 数组名就是指针
cout << "arr: " << arr << endl;
cout << "&arr[0]: " << &arr[0] << endl;

// 访问数组元素的多种方式
cout << "arr[2]: " << arr[2] << endl;
cout << "*(arr + 2): " << *(arr + 2) << endl;
cout << "*(2 + arr): " << *(2 + arr) << endl;
cout << "2[arr]: " << 2[arr] << endl;  // 不推荐但合法
```

### 指针作为函数参数
```cpp
// 值传递（不能修改原变量）
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// 指针传递（可以修改原变量）
void swapByPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用传递（C++推荐方式）
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

### 指针数组与数组指针
```cpp
// 指针数组：数组的每个元素都是指针
int a = 1, b = 2, c = 3;
int* ptrArray[3] = {&a, &b, &c};

// 访问指针数组
for (int i = 0; i < 3; i++) {
    cout << "ptrArray[" << i << "] = " << *ptrArray[i] << endl;
}

// 数组指针：指向数组的指针
int arr[5] = {1, 2, 3, 4, 5};
int (*arrayPtr)[5] = &arr;  // 指向包含5个int的数组

// 通过数组指针访问元素
for (int i = 0; i < 5; i++) {
    cout << "(*arrayPtr)[" << i << "] = " << (*arrayPtr)[i] << endl;
}
```

### 二级指针
```cpp
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
```

## 指针的常见应用

### 1. 动态内存分配
```cpp
// 分配单个整数
int* ptr = new int(42);
cout << "动态分配的值: " << *ptr << endl;
delete ptr;  // 释放内存

// 分配数组
int size = 5;
int* arr = new int[size];
for (int i = 0; i < size; i++) {
    arr[i] = i * i;
}
delete[] arr;  // 释放数组内存
```

### 2. 函数返回指针
```cpp
// 返回动态分配的数组
int* createArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i * i;
    }
    return arr;
}

// 使用
int* myArray = createArray(5);
// 使用完后记得释放
delete[] myArray;
```

### 3. 指针链表
```cpp
struct ListNode {
    int data;
    ListNode* next;
    
    ListNode(int val) : data(val), next(nullptr) {}
};

// 创建链表
ListNode* head = new ListNode(1);
head->next = new ListNode(2);
head->next->next = new ListNode(3);

// 遍历链表
ListNode* current = head;
while (current != nullptr) {
    cout << current->data << " ";
    current = current->next;
}
cout << endl;
```

## 实践练习

### 练习1：指针基本操作
实现指针的各种基本操作。

### 练习2：指针与数组
使用指针操作数组。

### 练习3：指针作为函数参数
实现各种指针传递的函数。

### 练习4：动态内存管理
实现动态内存的分配和释放。

## 常见错误与注意事项

1. **野指针**：使用未初始化的指针
2. **空指针解引用**：对空指针进行解引用操作
3. **内存泄漏**：分配内存后忘记释放
4. **重复释放**：对同一块内存释放多次
5. **指针越界**：访问超出分配范围的内存

## 安全编程建议

1. **初始化指针**：声明指针时立即初始化
2. **检查空指针**：使用指针前检查是否为空
3. **及时释放内存**：使用完后立即释放
4. **避免野指针**：释放后立即置空
5. **使用智能指针**：C++11引入的智能指针更安全

## 学习检查点

- [ ] 理解指针的基本概念和操作
- [ ] 掌握指针与数组的关系
- [ ] 能够使用指针作为函数参数
- [ ] 理解指针运算的规则
- [ ] 掌握动态内存分配和释放
- [ ] 了解指针的常见错误和避免方法

## 扩展阅读

- C++ Primer 第2章：变量和基本类型
- 了解智能指针（unique_ptr, shared_ptr）
- 学习指针的高级应用（函数指针、成员指针）
