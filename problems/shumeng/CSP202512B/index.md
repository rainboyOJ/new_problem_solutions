---
oj: "shumeng"
problem_id: "CSP202512B"
title: 数字变换
description: "由于状态只有 512 个，预计算所有输入经过参数序列后的输出，再建立输出到输入的逆映射。"
date: 2026-07-31 16:22
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202512B
difficulty: "未知"
---

[[TOC]]

### 题意

变换 `F` 由一串 `k_i` 依次作用在 9 位状态上。给出若干最终状态，要求找出唯一的初始状态。

### 思路

9 位状态只有 `2^9 = 512` 种。对每个可能的初始值完整模拟 `m` 次变换，得到 `F(start)`，再令 `inverse[F(start)] = start`。

将状态拆成三组 3 位数字 `a,b,c` 后，题面中的变换为：

```text
new_a = b
new_b = c ^ f(b,k)
new_c = a ^ f(c,k)
```

预处理后每个输入只需一次数组查询即可恢复。题目保证最终状态对应唯一初始状态。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理时间复杂度为 `O(512m)`，查询时间复杂度为 `O(n)`，空间复杂度为 `O(m+512)`。

### 总结

当状态空间极小时，可以直接枚举整个状态空间并反向建立映射，避免推导复杂的逐步逆变换。
