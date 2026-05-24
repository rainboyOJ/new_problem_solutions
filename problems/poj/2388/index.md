---
oj: "POJ"
problem_id: "2388"
title: "Who&#39;s in the Middle"
date: 2025-12-31 23:00
toc: true
tags: []
desc: ""
source: https://vjudge.net/problem/POJ-2388#author=DeepSeek_zh
pre:
 - luogu,P1314
book:
 - bookid
---

[[TOC]]


这道题目（通常被称为 **"The Median"**）其实就是[[problem: luogu,P1923]] 的 **“求第 $k$ 小的数”** 的一个特例。

## 1. 题目解析

中位数 (Median) 的定义：

在一个有序的序列中，处于最中间位置的那个数。

题目中强调了 $N$ 是**奇数**，这让问题变得非常简单，不需要考虑偶数个数取中间两个平均值的情况。

假设数组下标从 $0$ 开始（$0, 1, 2, \dots, N-1$）：

- 如果有 5 个数 ($N=5$)，排序后下标为 $0, 1, \mathbf{2}, 3, 4$。中位数是下标为 **2** 的数。
- 计算公式：目标下标 $k = N / 2$ (整数除法)。

本质：

这就等同于：求数组中第 $N/2$ 小的数（注意这里是 0-indexed，即第 0 小是最小值）。

------

## 2. 算法选择

由于 $N$ 只有 $10,000$ (1e4)：

1. **直接排序 (`std::sort`)**：
   - 复杂度 $O(N \log N)$。
   - 对于 $N=10000$ 来说，计算量大概在 $1.3 \times 10^5$ 次，瞬间完成。这是比赛中最推荐的写法，因为不易写错。
2. **快速选择 (`Quick Select`)**：
   - 复杂度 $O(N)$。
   - 这就是你刚才学的算法。虽然对于这么小的数据量有点“杀鸡用牛刀”，但用来练习你的模板是最好的！

------

## 3. 代码实现 (使用你的三路快排模板)

我们直接套用刚才那个**“不交换基准数、i从l开始”**的三路切分模板。

C++

```
/**
 * Problem: FJ的中位数
 * Algorithm: Quick Select (3-Way Partition)
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 10005; // 题目中 N < 10000
int a[maxn];
int n;

// 三路 Quick Select 模板
// 寻找数组中下标为 k 的元素 (即第 k+1 小)
int quick_select(int l, int r, int k) {
    if (l >= r) return a[l];

    // 1. 取中间值为 key
    std::swap(a[l],a[(l+r)/2])
    int key = a[l];

    // 2. 初始化
    int lt = l;
    int gt = r;
    int i = l+1; 

    // 3. 三路切分
    while (i <= gt) {
        if (a[i] < key) {
            swap(a[i], a[lt]);
            lt++;
            i++;
        } 
        else if (a[i] > key) {
            swap(a[i], a[gt]);
            gt--;
            // i 不动
        } 
        else {
            i++;
        }
    }

    // 4. 递归查找
    if (k < lt) return quick_select(l, lt - 1, k);
    else if (k > gt) return quick_select(gt + 1, r, k);
    else return key;
}

int main() {
    // 1. 输入
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 2. 求解
    // 中位数的下标就是 n / 2
    // 例如 n=5, 索引为 0,1,2,3,4，中位数是 a[2]，即 5/2 = 2
    int median_index = n / 2;
    
    int ans = quick_select(0, n - 1, median_index);

    // 3. 输出
    cout << ans << endl;

    return 0;
}
```

## 4. 偷懒写法 (比赛常用)

既然数据这么小，如果是打比赛，我会直接这样写，节省脑力：

C++

```
#include <bits/stdc++.h>
using namespace std;

int a[10005];

int main() {
    int n;
    cin >> n;
    for(int i=0; i<n; i++) cin >> a[i];
    
    // 直接排序
    sort(a, a + n);
    
    // 输出中间那个
    cout << a[n / 2] << endl;
    return 0;
}
```

## 总结

这道题完全就是 **luogu P1923** 的简化版。区别只在于：

1. P1923 明确告诉你求第 $k$ 小。
2. 这道题告诉你求“中位数”，你需要自己反应过来就是求第 $N/2$ 小。
