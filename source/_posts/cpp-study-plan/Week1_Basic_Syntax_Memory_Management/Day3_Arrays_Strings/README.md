# 第3天：数组与字符串

## 学习目标
掌握数组和字符串的使用，理解C风格字符串和C++字符串的区别。

## 学习内容

### 1. 一维数组
- 数组的声明与初始化
- 数组的访问与遍历
- 数组作为函数参数
- 数组的大小计算
- 数组的边界检查

### 2. 多维数组
- 二维数组的声明与初始化
- 多维数组的访问
- 数组的存储方式
- 动态多维数组

### 3. 字符数组与C风格字符串
- 字符数组的声明
- C风格字符串函数
- 字符串长度计算
- 字符串比较与复制
- 字符串连接与查找

### 4. C++字符串类
- `std::string` 的使用
- 字符串的构造与赋值
- 字符串的操作函数
- 字符串的迭代器
- 字符串的性能考虑

### 5. 数组与字符串的常见算法
- 查找算法
- 排序算法
- 字符串匹配算法
- 数组操作算法

## 重点概念

### 一维数组
```cpp
// 数组声明与初始化
int arr1[5];                    // 声明，未初始化
int arr2[5] = {1, 2, 3, 4, 5};  // 声明并初始化
int arr3[] = {1, 2, 3, 4, 5};   // 自动推导大小
int arr4[5] = {1, 2};           // 部分初始化，其余为0

// 数组访问
cout << arr2[0] << endl;        // 访问第一个元素
cout << arr2[4] << endl;        // 访问最后一个元素

// 数组遍历
for (int i = 0; i < 5; i++) {
    cout << arr2[i] << " ";
}
cout << endl;

// 范围for循环（C++11）
for (int element : arr2) {
    cout << element << " ";
}
cout << endl;
```

### 二维数组
```cpp
// 二维数组声明与初始化
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// 二维数组访问
cout << matrix[1][2] << endl;   // 访问第2行第3列

// 二维数组遍历
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}
```

### C风格字符串
```cpp
#include <cstring>

// 字符数组声明
char str1[20] = "Hello";
char str2[] = "World";
char str3[20];

// 字符串长度
cout << "str1长度: " << strlen(str1) << endl;

// 字符串复制
strcpy(str3, str1);
cout << "复制后: " << str3 << endl;

// 字符串连接
strcat(str3, " ");
strcat(str3, str2);
cout << "连接后: " << str3 << endl;

// 字符串比较
if (strcmp(str1, str2) == 0) {
    cout << "字符串相等" << endl;
} else {
    cout << "字符串不相等" << endl;
}

// 字符串查找
char* pos = strstr(str3, "World");
if (pos != nullptr) {
    cout << "找到子字符串" << endl;
}
```

### C++字符串类
```cpp
#include <string>

// 字符串构造
string str1 = "Hello";
string str2("World");
string str3(5, 'A');  // 5个'A'
string str4(str1);    // 拷贝构造

// 字符串操作
cout << "str1长度: " << str1.length() << endl;
cout << "str1大小: " << str1.size() << endl;

// 字符串连接
string result = str1 + " " + str2;
cout << "连接结果: " << result << endl;

// 字符串比较
if (str1 == str2) {
    cout << "字符串相等" << endl;
} else {
    cout << "字符串不相等" << endl;
}

// 字符串查找
size_t pos = str1.find("ll");
if (pos != string::npos) {
    cout << "找到子字符串，位置: " << pos << endl;
}

// 字符串截取
string substr = str1.substr(1, 3);  // 从位置1开始，长度3
cout << "子字符串: " << substr << endl;

// 字符串替换
str1.replace(0, 2, "Hi");
cout << "替换后: " << str1 << endl;
```

## 数组与字符串算法

### 查找算法
```cpp
// 线性查找
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 二分查找（数组必须有序）
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

### 排序算法
```cpp
// 冒泡排序
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 选择排序
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}
```

### 字符串算法
```cpp
// 字符串反转
void reverseString(string& str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        swap(str[left], str[right]);
        left++;
        right--;
    }
}

// 检查回文字符串
bool isPalindrome(const string& str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// 字符串匹配（朴素算法）
int stringMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            return i;  // 找到匹配
        }
    }
    return -1;  // 未找到
}
```

## 实践练习

### 练习1：数组基本操作
实现数组的增删改查操作。

### 练习2：字符串处理
实现各种字符串处理函数。

### 练习3：数组排序
实现多种排序算法并比较性能。

### 练习4：字符串匹配
实现字符串匹配算法。

## 常见错误与注意事项

1. **数组越界**：访问超出数组边界的内存
2. **未初始化数组**：使用未初始化的数组元素
3. **字符串长度**：C风格字符串需要额外空间存储'\0'
4. **内存管理**：动态数组需要手动释放内存
5. **字符编码**：处理多字节字符时注意编码问题

## 性能考虑

1. **数组访问**：数组访问是O(1)时间复杂度
2. **字符串操作**：C++字符串比C风格字符串更安全但可能稍慢
3. **内存局部性**：连续内存访问比随机访问更高效
4. **算法选择**：根据数据规模选择合适的算法

## 学习检查点

- [ ] 能够正确声明和初始化数组
- [ ] 掌握数组的遍历和访问方法
- [ ] 理解C风格字符串和C++字符串的区别
- [ ] 能够使用字符串的各种操作函数
- [ ] 掌握基本的数组和字符串算法
- [ ] 了解数组和字符串的性能特点

## 扩展阅读

- C++ Primer 第3章：字符串、向量和数组
- 了解STL容器（vector, array等）
- 学习更高级的字符串算法（KMP、Rabin-Karp等）
