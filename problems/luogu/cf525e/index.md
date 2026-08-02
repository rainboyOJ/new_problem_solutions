---
oj: "luogu"
problem_id: "CF525E"
title: "Anya and Cubes"
description: "Luogu 无法提交 Codeforces 原题，解析已迁移至 codeforces/525E，本页仅保留入口。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["Meet-in-the-Middle", "枚举", "计数"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF525E
---

[[TOC]]

### 题意

每个数可不选、按原值选、贴贴纸后按阶乘选，最多使用 `k` 张贴纸，统计和为 `S` 的方案数。完整教学解析（含 Python 版本与思考过程）已迁移至：

- [[problem: codeforces,525E]] · [CF525E Anya and Cubes 题解](https://codeforces.com/problemset/problem/525/E)

### 思路

折半搜索：左半枚举后按贴纸数分桶存 `sum -> 方案数`，右半枚举叶子时查左半所有允许贴纸数的桶，累加 `S-right_sum` 的出现次数。`a > 18` 时 `a! > 10^16`，阶乘分支可省略。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间约 $O(3^{n/2}k)$，空间 $O(3^{n/2})$。

### 总结

完整解析已迁移至 [[problem: codeforces,525E]]。
