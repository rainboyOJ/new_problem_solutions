---
oj: "luogu"
problem_id: "CF525E"
title: "Anya and Cubes"
description: "折半枚举每个数的不选、原值、阶乘三种状态，按使用贴纸数统计目标和方案。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["Meet-in-the-Middle", "枚举", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF525E
---

[[TOC]]

### 题意

每个数可不选、按原值选、贴贴纸后按阶乘选，最多使用 `k` 张贴纸，统计和为 `S` 的方案数。

### 思路

直接三进制枚举是 $3^{25}$。把数组分成两半，先枚举左半，把结果按贴纸数存为 `sum -> 方案数`；枚举右半叶子时，查询左半所有允许贴纸数中 `S-right_sum` 的出现次数。

`a > 18` 时 `a! > 10^16`，不可能进入合法总和，可省略阶乘分支。原值与阶乘即使相等也代表不同贴纸选择，两个递归分支都必须保留。

### Python 知识

- `defaultdict(int)` 自动累加重复元素产生的相同 `(sum, stickers)` 方案。
- `math.factorial` 只预计算可用的小数值。
- `sum(mapping.get(key, 0) for ...)` 汇总所有可接受贴纸数。

### 代码

@include-code(./main.py, python)

### 复杂度

时间约 $O(3^{n/2}k)$，空间 $O(3^{n/2})$。

### 总结

折半搜索不仅拆“和”，还要保留贴纸数这一限制维度；按限制分桶能让合并保持直接。
