---
oj: "shumeng"
problem_id: "CSP202503D"
title: "集体锻炼"
description: "按右端点维护所有不同 gcd 的左端点分组，并用左端点之和一次统计每组区间贡献。"
difficulty: "普及/提高-"
date: 2026-07-31 16:21
toc: true
tags: ["数论", "gcd", "前缀状态"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202503D
---

[[TOC]]

### 题意

对每个连续区间 `[l,r]`，定义价值为 `l*r*gcd(a[l..r])`，求所有区间价值之和模 `998244353`。

### 思路

固定右端点 `r`，从所有以 `r` 结尾的区间出发。若把区间左端点向左扩展，gcd 只会变小；因此这些区间的 gcd 不同取值数量很少。

维护若干组 `(g, sum_l)`：本组所有以当前 `r` 结尾的区间 gcd 都是 `g`，`sum_l` 是这些区间左端点之和。加入新元素 `a[r]` 后，新单点区间的 gcd 是 `a[r]`，旧组的 gcd 变为 `gcd(g,a[r])`，相邻的相同 gcd 立即合并。

一组的所有区间贡献为

```text
g * r * sum_l
```

每次只需遍历 gcd 分组并累加即可。小数据暴力程序直接枚举每个 `[l,r]`：

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个右端点的 gcd 分组数量为 `O(log max(a_i))`，总时间复杂度为 `O(n log A)`，空间复杂度为 `O(log A)`。

### 总结

不要逐个区间重复计算 gcd；把同一右端点下 gcd 相同的连续左端点合并，就能同时保留 gcd 和位置权重 `l*r`。
