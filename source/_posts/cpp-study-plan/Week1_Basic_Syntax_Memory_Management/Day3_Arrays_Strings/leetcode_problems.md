# 第3天算法题 - 数组与字符串

## 今日算法题（4道 Medium/Hard 难度）

### 1. 三数之和 (3Sum)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/3sum/  
**描述：** 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c，使得 a + b + c = 0？请你找出所有满足条件且不重复的三元组。  
**关键点：** 双指针、排序、去重、数组操作

### 2. 最长回文子串 (Longest Palindromic Substring)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/longest-palindromic-substring/  
**描述：** 给你一个字符串 s，找到 s 中最长的回文子串。  
**关键点：** 中心扩展法、动态规划、字符串处理、回文判断

### 3. 无重复字符的最长子串 (Longest Substring Without Repeating Characters)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/longest-substring-without-repeating-characters/  
**描述：** 给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。  
**关键点：** 滑动窗口、哈希表、字符串遍历、双指针

### 4. 合并区间 (Merge Intervals)
**难度：** Medium  
**链接：** https://leetcode.cn/problems/merge-intervals/  
**描述：** 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]。请你合并所有重叠的区间，并返回一个不重叠的区间数组。  
**关键点：** 排序、区间合并、数组操作、边界处理

## 解题思路提示

### 题目1：三数之和
**双指针思路：**
1. 先对数组排序
2. 固定第一个数，用双指针找另外两个数
3. 左指针从i+1开始，右指针从末尾开始
4. 根据三数之和调整指针位置
5. 注意去重：跳过重复的元素

**关键代码：**
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;  // 去重
        
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                // 去重
                while (left < right && nums[left] == nums[left+1]) left++;
                while (left < right && nums[right] == nums[right-1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}
```

### 题目2：最长回文子串
**中心扩展法：**
1. 遍历每个可能的中心点
2. 从中心向两边扩展，检查是否为回文
3. 考虑奇数和偶数长度的回文
4. 记录最长的回文子串

**关键代码：**
```cpp
string longestPalindrome(string s) {
    int start = 0, maxLen = 1;
    
    for (int i = 0; i < s.length(); i++) {
        // 奇数长度回文
        int len1 = expandAroundCenter(s, i, i);
        // 偶数长度回文
        int len2 = expandAroundCenter(s, i, i + 1);
        
        int len = max(len1, len2);
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    
    return s.substr(start, maxLen);
}

int expandAroundCenter(string s, int left, int right) {
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}
```

### 题目3：无重复字符的最长子串
**滑动窗口思路：**
1. 使用双指针维护一个滑动窗口
2. 右指针扩展窗口，左指针收缩窗口
3. 用哈希表记录字符最后出现的位置
4. 当遇到重复字符时，移动左指针

**关键代码：**
```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charMap;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        if (charMap.count(s[right]) && charMap[s[right]] >= left) {
            left = charMap[s[right]] + 1;
        }
        charMap[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

### 题目4：合并区间
**排序+合并思路：**
1. 按区间起始位置排序
2. 遍历区间，合并重叠的区间
3. 比较当前区间与前一个区间的关系
4. 如果重叠则合并，否则添加新区间

**关键代码：**
```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result;
    result.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= result.back()[1]) {
            // 重叠，合并
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        } else {
            // 不重叠，添加新区间
            result.push_back(intervals[i]);
        }
    }
    
    return result;
}
```

## 今日学习重点

1. **双指针技术**：在数组和字符串问题中的应用
2. **滑动窗口**：解决子串/子数组问题的高效方法
3. **排序预处理**：很多问题需要先排序
4. **去重技巧**：避免重复结果的常见方法
5. **边界处理**：注意数组越界和空输入

## 常用技巧

### 双指针模板
```cpp
int left = 0, right = n - 1;
while (left < right) {
    if (condition) {
        // 处理逻辑
        left++;
    } else {
        // 处理逻辑
        right--;
    }
}
```

### 滑动窗口模板
```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    // 扩展窗口
    while (window_needs_shrink) {
        // 收缩窗口
        left++;
    }
    // 更新结果
}
```

### 去重模板
```cpp
// 排序后去重
sort(nums.begin(), nums.end());
for (int i = 0; i < nums.size(); i++) {
    if (i > 0 && nums[i] == nums[i-1]) continue;
    // 处理逻辑
}
```

## 常见错误与注意事项

1. **数组越界**：注意边界条件检查
2. **重复结果**：忘记去重导致结果重复
3. **指针移动**：双指针移动时机错误
4. **排序稳定性**：排序后原数组顺序改变
5. **空输入处理**：没有处理空数组或空字符串

## 性能优化技巧

1. **提前终止**：找到答案后及时返回
2. **剪枝优化**：跳过不可能的情况
3. **空间优化**：使用原地算法减少空间使用
4. **数据结构选择**：选择合适的容器提高效率
5. **算法选择**：根据数据规模选择合适算法

## 学习检查点

- [ ] 能够使用双指针解决数组问题
- [ ] 掌握滑动窗口的基本应用
- [ ] 理解排序在算法中的重要作用
- [ ] 能够处理字符串的各种操作
- [ ] 掌握去重的常见技巧
- [ ] 能够分析算法的时间和空间复杂度

## 扩展练习

1. 实现四数之和问题
2. 解决最长公共子序列问题
3. 实现字符串的KMP匹配算法
4. 解决区间插入问题
5. 实现数组的旋转操作
