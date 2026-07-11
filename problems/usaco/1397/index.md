---
oj: "usaco"
problem_id: "1397"
title: "Maximizing Productivity"
description: "把准时条件化为 c_i - t_i > S，排序差值后用二分统计可访问农场数。"
difficulty: "普及-"
date: 2026-07-11 16:03
toc: true
tags: ["排序", "二分", "查询", "不等式变形", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1397
---

[[TOC]]

### 题意

有 $N$ 个农场。农场 $i$ 在时刻 $c_i$ 关闭，Bessie 如果在时刻 $S$ 起床，则会在时刻 $t_i + S$ 到达农场 $i$。

她必须严格早于关闭时间到达，也就是：

$$
t_i + S < c_i
$$

每个询问给出 `V S`，问是否至少有 $V$ 个农场能及时访问。

### 思路

先看一个小数据暴力：

@include-code(./brute.cpp, cpp)

暴力对每个询问扫描所有农场，直接判断 `t[i] + S < c[i]`。这样每个询问 $O(N)$，总复杂度 $O(NQ)$，无法通过满数据。

把判断条件移项：

$$
t_i + S < c_i
$$

等价于：

$$
c_i - t_i > S
$$

令：

$$
d_i = c_i - t_i
$$

那么一次询问 `(V, S)` 只是在问：有多少个 $d_i > S$？

以样例为例：

| i | $c_i$ | $t_i$ | $d_i=c_i-t_i$ |
| --- | --- | --- | --- |
| 1 | 3 | 4 | -1 |
| 2 | 5 | 2 | 3 |
| 3 | 7 | 3 | 4 |
| 4 | 9 | 3 | 6 |
| 5 | 12 | 8 | 4 |

排序后得到：

```text
-1 3 4 4 6
```

例如询问 $V=3, S=3$，需要统计大于 `3` 的数，有 `4,4,6` 共 $3$ 个，所以答案是 `YES`。

代码中用 `upper_bound` 找到第一个大于 `S` 的位置，后面的元素个数就是可访问农场数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序需要 $O(N \log N)$。

每个询问二分一次，复杂度为 $O(\log N)$。

总时间复杂度为 $O(N \log N + Q \log N)$，空间复杂度为 $O(N)$。

### 总结

本题的关键不在模拟访问过程，而在把每个农场预处理成一个阈值 $d_i=c_i-t_i$。

询问 `S` 之后，只需要快速统计有多少个阈值严格大于 `S`。严格不等号对应代码里的 `upper_bound`，这是最容易写错的边界。
