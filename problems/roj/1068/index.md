---
oj: "roj"
problem_id: "1068"
title: "与指定数字相同的数的个数"
description: "线性扫描序列，用生成器表达式统计等于指定数字的元素个数。"
difficulty: "入门"
date: 2026-07-05 21:47
updated: 2026-09-29 17:17
toc: true
tags: ["入门", "计数", "线性扫描"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1068"
---

[[TOC]]

## 形式化题目

给定整数 $n$（序列长度，$n \leqslant 100$）和目标整数 $m$，以及长度为 $n$ 的整数序列 $a_1, a_2, \ldots, a_n$。要求输出满足 $a_i = m$ 的下标 $i$ 的个数。

### 样例

输入：

```text
3 2
2 3 2
```

输出：

```text
2
```

序列中有两个 `2` 与 $m=2$ 相同。

## 正解

### 思路

依次读取序列中的每个数，若与 $m$ 相等，则计数器加 1。读完整个序列后输出计数器值即可。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，每个元素只判断一次。
- 空间复杂度：$O(1)$ 额外空间。

## 总结

本题是最基础的计数练习：线性扫描并统计满足条件的元素个数。
