#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;

// 练习1：数组基本操作
class ArrayOperations {
public:
    // 数组打印
    static void printArray(int arr[], int size) {
        cout << "数组内容: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    // 数组查找
    static int linearSearch(int arr[], int size, int target) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    // 数组插入
    static bool insertElement(int arr[], int& size, int capacity, int index, int value) {
        if (size >= capacity || index < 0 || index > size) {
            return false;
        }
        
        // 从后往前移动元素
        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        
        arr[index] = value;
        size++;
        return true;
    }
    
    // 数组删除
    static bool deleteElement(int arr[], int& size, int index) {
        if (index < 0 || index >= size) {
            return false;
        }
        
        // 从前往后移动元素
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        
        size--;
        return true;
    }
    
    // 数组反转
    static void reverseArray(int arr[], int size) {
        int left = 0, right = size - 1;
        while (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
    
    // 数组最大值和最小值
    static pair<int, int> findMinMax(int arr[], int size) {
        if (size == 0) return {0, 0};
        
        int minVal = arr[0], maxVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        return {minVal, maxVal};
    }
};

// 练习2：排序算法
class SortingAlgorithms {
public:
    // 冒泡排序
    static void bubbleSort(int arr[], int size) {
        for (int i = 0; i < size - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;  // 优化：如果没发生交换，说明已有序
        }
    }
    
    // 选择排序
    static void selectionSort(int arr[], int size) {
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
    
    // 插入排序
    static void insertionSort(int arr[], int size) {
        for (int i = 1; i < size; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    // 快速排序
    static void quickSort(int arr[], int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }
    
    // 归并排序
    static void mergeSort(int arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
private:
    static int partition(int arr[], int low, int high) {
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
    
    static void merge(int arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        int* leftArr = new int[n1];
        int* rightArr = new int[n2];
        
        for (int i = 0; i < n1; i++) {
            leftArr[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArr[j] = arr[mid + 1 + j];
        }
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
        
        delete[] leftArr;
        delete[] rightArr;
    }
};

// 练习3：C风格字符串操作
class CStringOperations {
public:
    // 字符串长度
    static int stringLength(const char* str) {
        int len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }
    
    // 字符串复制
    static void stringCopy(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    
    // 字符串连接
    static void stringConcat(char* dest, const char* src) {
        int destLen = stringLength(dest);
        int i = 0;
        while (src[i] != '\0') {
            dest[destLen + i] = src[i];
            i++;
        }
        dest[destLen + i] = '\0';
    }
    
    // 字符串比较
    static int stringCompare(const char* str1, const char* str2) {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] < str2[i]) return -1;
            if (str1[i] > str2[i]) return 1;
            i++;
        }
        if (str1[i] == '\0' && str2[i] == '\0') return 0;
        if (str1[i] == '\0') return -1;
        return 1;
    }
    
    // 字符串反转
    static void stringReverse(char* str) {
        int len = stringLength(str);
        int left = 0, right = len - 1;
        while (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
    
    // 字符串查找
    static int stringFind(const char* text, const char* pattern) {
        int textLen = stringLength(text);
        int patternLen = stringLength(pattern);
        
        for (int i = 0; i <= textLen - patternLen; i++) {
            int j;
            for (j = 0; j < patternLen; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == patternLen) {
                return i;
            }
        }
        return -1;
    }
};

// 练习4：C++字符串操作
class StringOperations {
public:
    // 字符串反转
    static string reverseString(string str) {
        int left = 0, right = str.length() - 1;
        while (left < right) {
            swap(str[left], str[right]);
            left++;
            right--;
        }
        return str;
    }
    
    // 检查回文
    static bool isPalindrome(const string& str) {
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
    
    // 字符串去重
    static string removeDuplicates(string str) {
        string result = "";
        bool seen[256] = {false};
        
        for (char c : str) {
            if (!seen[c]) {
                seen[c] = true;
                result += c;
            }
        }
        return result;
    }
    
    // 字符串压缩
    static string compressString(const string& str) {
        if (str.empty()) return str;
        
        string result = "";
        int count = 1;
        
        for (int i = 1; i < str.length(); i++) {
            if (str[i] == str[i - 1]) {
                count++;
            } else {
                result += str[i - 1];
                if (count > 1) {
                    result += to_string(count);
                }
                count = 1;
            }
        }
        
        result += str[str.length() - 1];
        if (count > 1) {
            result += to_string(count);
        }
        
        return result.length() < str.length() ? result : str;
    }
    
    // 字符串分割
    static vector<string> splitString(const string& str, char delimiter) {
        vector<string> result;
        string current = "";
        
        for (char c : str) {
            if (c == delimiter) {
                if (!current.empty()) {
                    result.push_back(current);
                    current = "";
                }
            } else {
                current += c;
            }
        }
        
        if (!current.empty()) {
            result.push_back(current);
        }
        
        return result;
    }
    
    // 字符串匹配（KMP算法简化版）
    static int stringMatch(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();
        
        if (m == 0) return 0;
        if (n < m) return -1;
        
        for (int i = 0; i <= n - m; i++) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                return i;
            }
        }
        return -1;
    }
};

// 练习5：二维数组操作
class MatrixOperations {
public:
    // 矩阵打印
    static void printMatrix(int matrix[][4], int rows, int cols) {
        cout << "矩阵内容:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }
    
    // 矩阵转置
    static void transposeMatrix(int matrix[][4], int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = i + 1; j < cols; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
    
    // 矩阵查找
    static pair<int, int> findElement(int matrix[][4], int rows, int cols, int target) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == target) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }
    
    // 矩阵行和列的和
    static void calculateSums(int matrix[][4], int rows, int cols) {
        cout << "行和:" << endl;
        for (int i = 0; i < rows; i++) {
            int rowSum = 0;
            for (int j = 0; j < cols; j++) {
                rowSum += matrix[i][j];
            }
            cout << "第" << i + 1 << "行: " << rowSum << endl;
        }
        
        cout << "列和:" << endl;
        for (int j = 0; j < cols; j++) {
            int colSum = 0;
            for (int i = 0; i < rows; i++) {
                colSum += matrix[i][j];
            }
            cout << "第" << j + 1 << "列: " << colSum << endl;
        }
    }
};

// 练习6：性能测试
class PerformanceTest {
public:
    static void testSortingPerformance() {
        const int SIZE = 10000;
        int* arr1 = new int[SIZE];
        int* arr2 = new int[SIZE];
        int* arr3 = new int[SIZE];
        int* arr4 = new int[SIZE];
        
        // 生成随机数据
        for (int i = 0; i < SIZE; i++) {
            int val = rand() % 1000;
            arr1[i] = arr2[i] = arr3[i] = arr4[i] = val;
        }
        
        // 测试冒泡排序
        auto start = chrono::high_resolution_clock::now();
        SortingAlgorithms::bubbleSort(arr1, SIZE);
        auto end = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        // 测试选择排序
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::selectionSort(arr2, SIZE);
        end = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        // 测试插入排序
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::insertionSort(arr3, SIZE);
        end = chrono::high_resolution_clock::now();
        auto duration3 = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        // 测试快速排序
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::quickSort(arr4, 0, SIZE - 1);
        end = chrono::high_resolution_clock::now();
        auto duration4 = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "排序性能测试 (数组大小: " << SIZE << "):" << endl;
        cout << "冒泡排序: " << duration1.count() << " ms" << endl;
        cout << "选择排序: " << duration2.count() << " ms" << endl;
        cout << "插入排序: " << duration3.count() << " ms" << endl;
        cout << "快速排序: " << duration4.count() << " ms" << endl;
        
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
    }
};

int main() {
    cout << "C++ 数组与字符串练习" << endl;
    cout << "===================" << endl;
    
    // 练习1：数组基本操作
    cout << "\n=== 数组基本操作 ===" << endl;
    int arr[10] = {1, 2, 3, 4, 5};
    int size = 5;
    
    ArrayOperations::printArray(arr, size);
    
    // 查找元素
    int target = 3;
    int index = ArrayOperations::linearSearch(arr, size, target);
    cout << "查找 " << target << " 的索引: " << index << endl;
    
    // 插入元素
    if (ArrayOperations::insertElement(arr, size, 10, 2, 99)) {
        cout << "插入元素后: ";
        ArrayOperations::printArray(arr, size);
    }
    
    // 删除元素
    if (ArrayOperations::deleteElement(arr, size, 2)) {
        cout << "删除元素后: ";
        ArrayOperations::printArray(arr, size);
    }
    
    // 数组反转
    ArrayOperations::reverseArray(arr, size);
    cout << "反转后: ";
    ArrayOperations::printArray(arr, size);
    
    // 查找最大值和最小值
    auto minMax = ArrayOperations::findMinMax(arr, size);
    cout << "最小值: " << minMax.first << ", 最大值: " << minMax.second << endl;
    
    // 练习2：排序算法
    cout << "\n=== 排序算法 ===" << endl;
    int sortArr[] = {64, 34, 25, 12, 22, 11, 90};
    int sortSize = sizeof(sortArr) / sizeof(sortArr[0]);
    
    cout << "原数组: ";
    ArrayOperations::printArray(sortArr, sortSize);
    
    // 复制数组用于不同排序
    int bubbleArr[7], selectionArr[7], insertionArr[7], quickArr[7];
    for (int i = 0; i < sortSize; i++) {
        bubbleArr[i] = selectionArr[i] = insertionArr[i] = quickArr[i] = sortArr[i];
    }
    
    SortingAlgorithms::bubbleSort(bubbleArr, sortSize);
    cout << "冒泡排序: ";
    ArrayOperations::printArray(bubbleArr, sortSize);
    
    SortingAlgorithms::selectionSort(selectionArr, sortSize);
    cout << "选择排序: ";
    ArrayOperations::printArray(selectionArr, sortSize);
    
    SortingAlgorithms::insertionSort(insertionArr, sortSize);
    cout << "插入排序: ";
    ArrayOperations::printArray(insertionArr, sortSize);
    
    SortingAlgorithms::quickSort(quickArr, 0, sortSize - 1);
    cout << "快速排序: ";
    ArrayOperations::printArray(quickArr, sortSize);
    
    // 练习3：C风格字符串
    cout << "\n=== C风格字符串操作 ===" << endl;
    char cstr1[50] = "Hello";
    char cstr2[50] = "World";
    char cstr3[100];
    
    cout << "str1: " << cstr1 << " (长度: " << CStringOperations::stringLength(cstr1) << ")" << endl;
    cout << "str2: " << cstr2 << " (长度: " << CStringOperations::stringLength(cstr2) << ")" << endl;
    
    CStringOperations::stringCopy(cstr3, cstr1);
    cout << "复制后: " << cstr3 << endl;
    
    CStringOperations::stringConcat(cstr3, " ");
    CStringOperations::stringConcat(cstr3, cstr2);
    cout << "连接后: " << cstr3 << endl;
    
    int cmp = CStringOperations::stringCompare(cstr1, cstr2);
    cout << "字符串比较结果: " << cmp << endl;
    
    CStringOperations::stringReverse(cstr1);
    cout << "反转后: " << cstr1 << endl;
    
    // 练习4：C++字符串操作
    cout << "\n=== C++字符串操作 ===" << endl;
    string str1 = "Hello World";
    string str2 = "racecar";
    string str3 = "aabcccccaaa";
    
    cout << "原字符串: " << str1 << endl;
    cout << "反转后: " << StringOperations::reverseString(str1) << endl;
    
    cout << "\"" << str2 << "\" 是回文: " << (StringOperations::isPalindrome(str2) ? "是" : "否") << endl;
    
    cout << "去重前: " << str1 << endl;
    cout << "去重后: " << StringOperations::removeDuplicates(str1) << endl;
    
    cout << "压缩前: " << str3 << endl;
    cout << "压缩后: " << StringOperations::compressString(str3) << endl;
    
    string text = "Hello World Hello";
    string pattern = "World";
    int pos = StringOperations::stringMatch(text, pattern);
    cout << "在 \"" << text << "\" 中查找 \"" << pattern << "\" 的位置: " << pos << endl;
    
    // 练习5：二维数组操作
    cout << "\n=== 二维数组操作 ===" << endl;
    int matrix[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    MatrixOperations::printMatrix(matrix, 4, 4);
    MatrixOperations::calculateSums(matrix, 4, 4);
    
    auto pos2 = MatrixOperations::findElement(matrix, 4, 4, 7);
    cout << "查找元素7的位置: (" << pos2.first << ", " << pos2.second << ")" << endl;
    
    // 练习6：性能测试
    cout << "\n=== 性能测试 ===" << endl;
    PerformanceTest::testSortingPerformance();
    
    return 0;
}
