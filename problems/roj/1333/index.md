---
oj: "roj"
problem_id: "1333"
title: "【例2-2】Blah数集"
description: "用两个指针分别加工升序序列已生成前缀的 2x+1 与 3x+1 两族候选，队首取小接回序列、相等双消费去重，O(n) 得到第 n 个 Blah 数，多组询问逐组计算。"
difficulty: "普及-"
date: 2026-09-30 05:44
updated: 2026-10-05 10:11
toc: true
tags: ["贪心", "多路归并", "双指针", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1333
---
[[TOC]]

## 题目描述

大数学家高斯小时候发现一种有趣的自然数集合 Blah：以 a 为基的集合 Ba 定义为——a 是 Ba 的第一个元素；如果 x 在 Ba 中，则 2x+1 和 3x+1 也都在 Ba 中；没有其他元素。将 Ba 中元素按升序排列，问第 N 个元素是多少。

输入很多行，每行两个数字：基 a（1≤a≤50）与序号 n（1≤n≤1000000）。对每组输入，输出 Ba 的第 n 个元素值。

输入样例：

```text
1 100
28 5437
```

输出样例：

```text
418
900585
```

## 思路

把升序序列记作 q，q 中每个元素（除 a 外）都由某个更小的元素经 2x+1 或 3x+1 生成，所以用两个指针分别指向 q 中"待加工"的位置，2q_p+1 与 3q_r+1 各自构成递增候选。每轮取两族队首的较小者接到 q 尾部并把对应指针后移，两族候选相等时两个指针同时后移（天然去重），生成满 n 个数即为答案，每组询问 O(n)。

## 参考代码

@include-code(./main.cpp, cpp)
