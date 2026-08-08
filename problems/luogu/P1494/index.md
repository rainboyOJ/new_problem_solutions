---
oj: "luogu"
problem_id: "P1494"
difficulty: "普及+/提高"
title: "[国家集训队] 小 Z 的袜子"
description: "用莫队维护当前区间内同色袜子对数量，再与总二元组数量约分得到概率。"
date: 2026-06-22 23:14
toc: true
tags: ["莫队", "离线", "数据结构"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1494
---

[[TOC]]

### 题意

给定一排袜子的颜色。每个询问 `[l,r]` 中随机选两只袜子，求两只颜色相同的概率，输出约分后的分数。

### 思路

如果已知区间内每种颜色的出现次数 `cnt[c]`，那么同色选择方案数是：

```text
sum cnt[c] * (cnt[c] - 1) / 2
```

总选择方案数是：

```text
len * (len - 1) / 2
```

朴素做法是每个询问重新扫描区间统计颜色。

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

要处理很多区间询问，可以用莫队。维护当前区间 `[cur_l, cur_r]`，以及当前区间内同色袜子对数量 `same_pair_count`。

移动端点时只会加入或删除一只袜子：

- 加入颜色 `c`：它能和已有 `cnt[c]` 只同色袜子组成新同色对，所以 `same_pair_count += cnt[c]`；
- 删除颜色 `c`：删除后剩余 `cnt[c]` 只同色袜子，少掉这些配对，所以 `same_pair_count -= cnt[c]`。

莫队排序后，左右端点移动总量较小。每个询问调整完区间后，用 `same_pair_count / C(len,2)` 约分输出即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度约为 $O((n+m)\sqrt{n})$。

空间复杂度 $O(n+m)$。

### 总结

莫队题的关键是设计好“加入一个点”和“删除一个点”对答案的影响。本题维护的是同色二元组数量，而不是直接维护概率。
