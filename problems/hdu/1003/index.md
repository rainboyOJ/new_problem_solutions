---
oj: "HDU"
problem_id: "1003"
title: "Max Sum"
date: 2025-12-26 16:12
toc: true
tags: ["dp","经典题"]
desc: "经典题:最大子段和"
source: https://vjudge.net/problem/HDU-1003#author=DeepSeek_zh
---

[[TOC]]

# 题目解析：最大子段和 (Maximum Subarray Sum)

## 题目背景
这是一个非常经典的算法问题，要求在一个给定的整数序列中，找到一个连续的子序列（子段），使得该子序列的元素之和最大，并输出该和以及子段的起始和结束位置。

## 题目分析

给定序列 $A = \{a_1, a_2, \dots, a_n\}$。
我们需要找到 $1 \le i \le j \le n$，使得 $\sum_{k=i}^{j} a_k$ 最大。

**难点与细节：**
1.  **多解情况：** 题目要求如果存在多个子段和相同，输出**第一个**（即起始位置最小，若起始位置相同则取结束位置最小的，但在本题逻辑中，一旦起始位置确定，贪心扩展时长度越长和越大越好吗？其实只要找到第一个最大的即可）。
2.  **负数处理：** 序列中包含负数。如果全为负数，最大子段和即为最大的那个单个元素。
3.  **时间复杂度：** $N \le 100000$，这意味着 $O(N^2)$ 的暴力枚举会超时，必须使用 $O(N)$ 或 $O(N \log N)$ 的算法。

---

## 方法一：动态规划 (Kadane's Algorithm)

### 核心思想
这是解决此问题最标准、最高效的方法，时间复杂度为 $O(N)$。

定义状态 $dp[i]$ 为 **以第 $i$ 个元素结尾的最大子段和**。
状态转移方程如下：
$$dp[i] = \max(a[i], dp[i-1] + a[i])$$

* **解释：** 如果以前一个元素结尾的子段和 $dp[i-1]$ 是正数，那么加上 $a[i]$ 会使当前和变大，不仅如此，连接起来肯定比单独 $a[i]$ 要大；如果 $dp[i-1]$ 是负数，加上它只会拖累 $a[i]$，不如从 $a[i]$ 重新开始。

### 空间优化
我们在遍历时只需要知道前一个状态，因此不需要开 $O(N)$ 的数组，仅需一个变量 `current_sum` 即可。

### 代码实现 (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int case_num) {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // max_sum 初始化为极小值，或者第一个元素
    int max_sum = -1001; // 题目范围 -1000 到 1000
    int start_pos = 1, end_pos = 1;

    int current_sum = 0;
    int temp_start = 1; // 记录当前子段可能的起始位置

    for (int i = 1; i <= n; ++i) {
        current_sum += a[i];

        // 如果当前累计和比历史最大值还大，更新结果
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start_pos = temp_start;
            end_pos = i;
        }

        // 核心贪心/DP策略：
        // 如果当前累计和变成了负数，那么对于后面的元素来说，
        // 加上这一段负数还不如从头开始。
        // 所以重置 current_sum 为 0，并将可能的起点设为下一位。
        if (current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }

    cout << "Case " << case_num << ":" << endl;
    cout << max_sum << " " << start_pos << " " << end_pos << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
        if (i != t) cout << endl; // 两个测试用例间输出空行
    }
    return 0;
}
````

* * *

方法二：前缀和 + 贪心
------------

### 核心思想

子段和可以转化为前缀和相减：

$$
Sum\left(i,j\right)=S\left[j\right]-S\left[i-1\right]
$$

其中  $S\left[x\right]$  表示  $a\left[1\right]$  到  $a\left[x\right]$  的和。

要使  $S\left[j\right]-S\left[i-1\right]$  最大，当我们固定右端点  $j$  时，只需要找到一个左端点  $i-1$ （即下标  $k<j$ ），使得  $S\left[k\right]$  最小。

### 算法流程

1.  维护一个变量 `min_prefix_sum`，记录当前位置之前出现的最小前缀和。
2.  遍历  $j$  从 1 到  $n$ ，计算当前前缀和  $S\left[j\right]$ 。
3.  用  $S\left[j\right]-min_prefix_sum$  更新最大值。
4.  如果  $S\left[j\right]<min_prefix_sum$ ，则更新 `min_prefix_sum`。

### 代码片段 (关键逻辑)

```
    int max_ans = -1e9;
    int ans_start = 1, ans_end = 1;
    
    int current_s = 0;
    int min_s = 0;      // 最小前缀和的值
    int min_s_pos = 0;  // 最小前缀和的位置 (对应公式中的 i-1)

    for (int j = 1; j <= n; ++j) {
        current_s += a[j]; // S[j]
        
        // 计算区间和 S[j] - min_s
        if (current_s - min_s > max_ans) {
            max_ans = current_s - min_s;
            ans_start = min_s_pos + 1; // 真正的起始位置是 min_pos 的下一个
            ans_end = j;
        }

        // 更新最小前缀和
        // 注意：题目要求如有多个结果输出第一个。
        // 因此只有严格小于才更新min_s，这样能保证左端点尽可能靠前(还是靠后?)
        // 实际上，保持 min_s 不变意味着左端点不变，这符合题目要求。
        if (current_s < min_s) {
            min_s = current_s;
            min_s_pos = j;
        }
    }
```

* * *

方法三：分治法 (线段树风格)
---------------

### 核心思想

这种方法虽然对于本题  $O\left(N\right)$  的限制来说稍显复杂，但它是解决 **区间最大子段和查询 (GSS Problem)** 的核心思路，非常适合作为进阶数据结构的入门。

对于区间  $\left[L,R\right]$ ，其最大子段和可能出现在：

1.  **左半部分**  $\left[L,mid\right]$  中。
2.  **右半部分**  $\left[mid+1,R\right]$  中。
3.  **横跨中点**，即包含  $mid$  和  $mid+1$  的一部分。

为了能够递归合并（PushUp），我们需要维护四个信息：

*   `max_sum`: 当前区间的最大子段和。
*   `l_max`: 必须包含左端点的最大前缀和。
*   `r_max`: 必须包含右端点的最大后缀和。
*   `sum`: 当前区间的总和。

### 合并逻辑 (PushUp)

假设我们合并左子区间  $lc$  和右子区间  $rc$ ：

1.  总和：`sum = lc.sum + rc.sum`
2.  最大前缀：`l_max = max(lc.l_max, lc.sum + rc.l_max)`
3.  最大后缀：`r_max = max(rc.r_max, rc.sum + lc.r_max)`
4.  最大子段和：`max_sum = max(lc.max_sum, rc.max_sum, lc.r_max + rc.l_max)`

### 代码实现 (C++)

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int max_sum; // 区间最大子段和
    int l_max;   // 最大前缀和
    int r_max;   // 最大后缀和
    int sum;     // 区间总和
    int l, r;    // 对应的区间范围（用于记录题目需要的下标）
    // 为了记录下标，实际实现会比较繁琐，这里主要展示计算数值的逻辑
};

// 简化版：仅计算最大值，不记录下标细节（下标记录在递归中需要额外的struct处理）
// 如果需要严格输出下标，建议使用方法一。本方法主要用于理解结构。
Node pushUp(Node left, Node right) {
    Node res;
    res.sum = left.sum + right.sum;
    res.l_max = max(left.l_max, left.sum + right.l_max);
    res.r_max = max(right.r_max, right.sum + left.r_max);
    
    // 横跨中间的情况
    int cross_max = left.r_max + right.l_max;
    res.max_sum = max({left.max_sum, right.max_sum, cross_max});
    
    return res;
}

// 这里的代码主要展示分治思想，针对本题的输出格式（需要First Index），
// 编写完整的线段树合并判断逻辑较为冗长，推荐使用DP解决本题。
```

总结
--

*   **DP (Kadane)**：最推荐，代码短，逻辑清晰， $O\left(N\right)$ 。
*   **前缀和**：本质与DP相同，是数形结合的体现。
*   **分治法**：是很多高级区间操作题目的基础，值得学习。


