# 第16天：STL算法复习

## 学习目标
掌握C++标准模板库中各种算法的使用，理解算法与容器的结合使用，学会自定义比较器和谓词。

## 学习内容

### 1. 查找算法 (Search Algorithms)

#### find 系列
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

void findExamples() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // find - 查找第一个匹配的元素
    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "找到元素5，位置: " << std::distance(vec.begin(), it) << std::endl;
    }
    
    // find_if - 查找第一个满足条件的元素
    auto it2 = std::find_if(vec.begin(), vec.end(), [](int n) { return n > 7; });
    if (it2 != vec.end()) {
        std::cout << "找到第一个大于7的元素: " << *it2 << std::endl;
    }
    
    // find_if_not - 查找第一个不满足条件的元素
    auto it3 = std::find_if_not(vec.begin(), vec.end(), [](int n) { return n < 5; });
    if (it3 != vec.end()) {
        std::cout << "找到第一个不小于5的元素: " << *it3 << std::endl;
    }
}
```

#### binary_search 系列
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

void binarySearchExamples() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // binary_search - 二分查找（需要有序）
    bool found = std::binary_search(vec.begin(), vec.end(), 5);
    std::cout << "5是否存在: " << (found ? "是" : "否") << std::endl;
    
    // lower_bound - 查找第一个不小于目标值的位置
    auto it1 = std::lower_bound(vec.begin(), vec.end(), 5);
    std::cout << "第一个不小于5的元素: " << *it1 << std::endl;
    
    // upper_bound - 查找第一个大于目标值的位置
    auto it2 = std::upper_bound(vec.begin(), vec.end(), 5);
    std::cout << "第一个大于5的元素: " << *it2 << std::endl;
    
    // equal_range - 查找等于目标值的范围
    auto range = std::equal_range(vec.begin(), vec.end(), 5);
    std::cout << "等于5的元素范围: [" 
              << std::distance(vec.begin(), range.first) << ", "
              << std::distance(vec.begin(), range.second) << ")" << std::endl;
}
```

### 2. 排序算法 (Sorting Algorithms)

#### sort 系列
```cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

void sortExamples() {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    // sort - 排序（默认升序）
    std::sort(vec.begin(), vec.end());
    std::cout << "升序排序: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // sort - 自定义比较器（降序）
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    std::cout << "降序排序: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // partial_sort - 部分排序（前k个元素）
    std::vector<int> vec2 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::partial_sort(vec2.begin(), vec2.begin() + 3, vec2.end());
    std::cout << "前3个最小元素: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;
    
    // nth_element - 找到第n个元素
    std::vector<int> vec3 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::nth_element(vec3.begin(), vec3.begin() + 4, vec3.end());
    std::cout << "第5个元素: " << vec3[4] << std::endl;
}
```

#### 自定义比较器
```cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

struct Person {
    std::string name;
    int age;
    double salary;
    
    Person(const std::string& n, int a, double s) : name(n), age(a), salary(s) {}
};

void customComparatorExamples() {
    std::vector<Person> people = {
        {"Alice", 25, 50000},
        {"Bob", 30, 60000},
        {"Charlie", 20, 45000},
        {"Diana", 35, 70000}
    };
    
    // 按年龄排序
    std::sort(people.begin(), people.end(), 
              [](const Person& a, const Person& b) {
                  return a.age < b.age;
              });
    
    std::cout << "按年龄排序:" << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ")" << std::endl;
    }
    
    // 按工资降序排序
    std::sort(people.begin(), people.end(), 
              [](const Person& a, const Person& b) {
                  return a.salary > b.salary;
              });
    
    std::cout << "\n按工资降序排序:" << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " ($" << person.salary << ")" << std::endl;
    }
}
```

### 3. 修改算法 (Modifying Algorithms)

#### transform
```cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

void transformExamples() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> result;
    
    // 计算平方
    std::transform(vec.begin(), vec.end(), std::back_inserter(result),
                   [](int n) { return n * n; });
    
    std::cout << "原数组: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    std::cout << "平方后: ";
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
    
    // 字符串转换
    std::vector<std::string> words = {"hello", "world", "cpp"};
    std::vector<std::string> upperWords;
    
    std::transform(words.begin(), words.end(), std::back_inserter(upperWords),
                   [](const std::string& s) {
                       std::string result = s;
                       std::transform(s.begin(), s.end(), result.begin(), ::toupper);
                       return result;
                   });
    
    std::cout << "大写转换: ";
    for (const auto& word : upperWords) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}
```

#### replace 系列
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

void replaceExamples() {
    std::vector<int> vec = {1, 2, 3, 2, 4, 2, 5};
    
    // replace - 替换所有匹配的元素
    std::replace(vec.begin(), vec.end(), 2, 99);
    std::cout << "替换2为99: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // replace_if - 替换满足条件的元素
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::replace_if(vec2.begin(), vec2.end(), 
                    [](int n) { return n % 2 == 0; }, 0);
    std::cout << "替换偶数为0: ";
    for (int n : vec2) std::cout << n << " ";
    std::cout << std::endl;
    
    // replace_copy - 复制并替换
    std::vector<int> vec3 = {1, 2, 3, 2, 4, 2, 5};
    std::vector<int> result;
    std::replace_copy(vec3.begin(), vec3.end(), std::back_inserter(result), 2, 99);
    std::cout << "原数组: ";
    for (int n : vec3) std::cout << n << " ";
    std::cout << std::endl;
    std::cout << "复制替换后: ";
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
}
```

#### remove 系列
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

void removeExamples() {
    std::vector<int> vec = {1, 2, 3, 2, 4, 2, 5};
    
    // remove - 移除元素（不改变容器大小）
    auto newEnd = std::remove(vec.begin(), vec.end(), 2);
    std::cout << "移除2后（未调整大小）: ";
    for (auto it = vec.begin(); it != newEnd; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 调整容器大小
    vec.erase(newEnd, vec.end());
    std::cout << "调整大小后: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // remove_if - 移除满足条件的元素
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto newEnd2 = std::remove_if(vec2.begin(), vec2.end(), 
                                  [](int n) { return n % 2 == 0; });
    vec2.erase(newEnd2, vec2.end());
    std::cout << "移除偶数后: ";
    for (int n : vec2) std::cout << n << " ";
    std::cout << std::endl;
}
```

### 4. 数值算法 (Numeric Algorithms)

#### accumulate
```cpp
#include <numeric>
#include <vector>
#include <iostream>
#include <string>

void accumulateExamples() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // 求和
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "求和: " << sum << std::endl;
    
    // 求积
    int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
    std::cout << "求积: " << product << std::endl;
    
    // 自定义操作
    int customSum = std::accumulate(vec.begin(), vec.end(), 0,
                                   [](int acc, int n) { return acc + n * n; });
    std::cout << "平方和: " << customSum << std::endl;
    
    // 字符串连接
    std::vector<std::string> words = {"Hello", " ", "World", "!"};
    std::string sentence = std::accumulate(words.begin(), words.end(), std::string(""));
    std::cout << "连接字符串: " << sentence << std::endl;
}
```

#### inner_product
```cpp
#include <numeric>
#include <vector>
#include <iostream>

void innerProductExamples() {
    std::vector<int> vec1 = {1, 2, 3, 4};
    std::vector<int> vec2 = {2, 3, 4, 5};
    
    // 内积（点积）
    int dotProduct = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
    std::cout << "内积: " << dotProduct << std::endl;
    
    // 自定义内积操作
    int customInner = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0,
                                        std::plus<int>(), std::multiplies<int>());
    std::cout << "自定义内积: " << customInner << std::endl;
}
```

### 5. 集合算法 (Set Algorithms)

```cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

void setAlgorithmExamples() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {3, 4, 5, 6, 7};
    std::vector<int> result;
    
    // set_union - 并集
    std::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                   std::back_inserter(result));
    std::cout << "并集: ";
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
    
    // set_intersection - 交集
    result.clear();
    std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                          std::back_inserter(result));
    std::cout << "交集: ";
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
    
    // set_difference - 差集
    result.clear();
    std::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                        std::back_inserter(result));
    std::cout << "差集: ";
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
    
    // set_symmetric_difference - 对称差集
    result.clear();
    std::set_symmetric_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                                  std::back_inserter(result));
    std::cout << "对称差集: ";
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
}
```

### 6. 堆算法 (Heap Algorithms)

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

void heapAlgorithmExamples() {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // make_heap - 创建堆
    std::make_heap(vec.begin(), vec.end());
    std::cout << "最大堆: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // push_heap - 添加元素到堆
    vec.push_back(8);
    std::push_heap(vec.begin(), vec.end());
    std::cout << "添加8后: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // pop_heap - 移除堆顶元素
    std::pop_heap(vec.begin(), vec.end());
    int max = vec.back();
    vec.pop_back();
    std::cout << "移除的最大元素: " << max << std::endl;
    std::cout << "剩余堆: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // sort_heap - 堆排序
    std::sort_heap(vec.begin(), vec.end());
    std::cout << "堆排序后: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
}
```

## 实践练习

### 练习1：数据分析器
```cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <map>

class DataAnalyzer {
private:
    std::vector<double> data;
    
public:
    void addData(double value) {
        data.push_back(value);
    }
    
    double getMean() const {
        if (data.empty()) return 0.0;
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }
    
    double getMedian() const {
        if (data.empty()) return 0.0;
        
        std::vector<double> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        
        size_t n = sortedData.size();
        if (n % 2 == 0) {
            return (sortedData[n/2 - 1] + sortedData[n/2]) / 2.0;
        } else {
            return sortedData[n/2];
        }
    }
    
    double getMode() const {
        if (data.empty()) return 0.0;
        
        std::map<double, int> frequency;
        for (double value : data) {
            frequency[value]++;
        }
        
        auto mode = std::max_element(frequency.begin(), frequency.end(),
                                    [](const auto& a, const auto& b) {
                                        return a.second < b.second;
                                    });
        return mode->first;
    }
    
    std::vector<double> getTopK(int k) const {
        std::vector<double> result = data;
        std::partial_sort(result.begin(), result.begin() + std::min(k, static_cast<int>(result.size())), 
                          result.end(), std::greater<double>());
        result.resize(std::min(k, static_cast<int>(result.size())));
        return result;
    }
    
    void removeOutliers(double threshold) {
        data.erase(std::remove_if(data.begin(), data.end(),
                                  [this, threshold](double value) {
                                      return std::abs(value - getMean()) > threshold;
                                  }), data.end());
    }
    
    void printStatistics() const {
        std::cout << "数据统计:" << std::endl;
        std::cout << "平均值: " << getMean() << std::endl;
        std::cout << "中位数: " << getMedian() << std::endl;
        std::cout << "众数: " << getMode() << std::endl;
        std::cout << "数据量: " << data.size() << std::endl;
    }
};
```

### 练习2：文本处理器
```cpp
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

class TextProcessor {
public:
    static std::vector<std::string> split(const std::string& text, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(text);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }
    
    static std::string toLowerCase(const std::string& str) {
        std::string result = str;
        std::transform(str.begin(), str.end(), result.begin(), ::tolower);
        return result;
    }
    
    static std::string removePunctuation(const std::string& str) {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](char c) { return std::isalnum(c) || std::isspace(c); });
        return result;
    }
    
    static std::map<std::string, int> wordFrequency(const std::string& text) {
        std::map<std::string, int> frequency;
        std::vector<std::string> words = split(removePunctuation(text), ' ');
        
        for (std::string& word : words) {
            word = toLowerCase(word);
            if (!word.empty()) {
                frequency[word]++;
            }
        }
        
        return frequency;
    }
    
    static std::vector<std::string> getMostFrequentWords(const std::string& text, int n) {
        auto freq = wordFrequency(text);
        std::vector<std::pair<std::string, int>> sortedFreq(freq.begin(), freq.end());
        
        std::partial_sort(sortedFreq.begin(), 
                          sortedFreq.begin() + std::min(n, static_cast<int>(sortedFreq.size())),
                          sortedFreq.end(),
                          [](const auto& a, const auto& b) {
                              return a.second > b.second;
                          });
        
        std::vector<std::string> result;
        for (int i = 0; i < std::min(n, static_cast<int>(sortedFreq.size())); ++i) {
            result.push_back(sortedFreq[i].first);
        }
        
        return result;
    }
};
```

## 学习要点总结

1. **算法分类**：查找、排序、修改、数值、集合、堆算法
2. **迭代器使用**：理解各种迭代器的适用范围
3. **自定义比较器**：掌握Lambda表达式和函数对象
4. **性能考虑**：了解各算法的时间复杂度
5. **组合使用**：多个算法的组合使用

## 今日算法题

完成以下4道LeetCode题目，巩固STL算法的使用：

1. [LeetCode 56. Merge Intervals](https://leetcode.com/problems/merge-intervals/) - 使用排序和合并算法
2. [LeetCode 347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) - 使用排序和计数算法
3. [LeetCode 215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) - 使用部分排序算法
4. [LeetCode 49. Group Anagrams](https://leetcode.com/problems/group-anagrams/) - 使用排序和分组算法

每道题目都涉及多个STL算法的组合使用，是很好的实践机会！
