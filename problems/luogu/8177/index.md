---
oj: "luogu"
problem_id: "P8177"
title: "「EZEC-11」等差数列"
description: "把公差拆成 odd*2^t 后，新增数量只由 2^t 决定，答案是 (n-1)(2^t-1)。"
difficulty: "普及/提高-"
date: 2026-06-18 21:34
toc: true
tags: ["数学", "构造"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P8177
---

[[TOC]]

### 题意

给出一个首项为 `a`、公差为 `d`、长度为 `n` 的等差数列。
如果选出的两个数平均值是整数且还不在集合里，就可以把这个平均数加入集合。
问最多还能加入多少个新数。

### 思路

先看一个可以直接验证想法的朴素解：

小数据时可以维护集合，不断枚举两数并加入新的整数中点，直到再也加不动。

@include-code(./brute.cpp, cpp)

关键是把公差拆成：

$$
d = odd \times 2^t
$$

去掉奇数因子后，问题就变成：

$$
0, 2^t, 2 \times 2^t, \dots, (n-1) \times 2^t
$$

不断取整数中点后，每个原始间隔都会被一层层二分，最终补成连续整数。
所以最后总共有：

$$
(n-1) \times 2^t + 1
$$

个数，新增数量就是：

$$
(n-1) \times (2^t - 1)
$$

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

每组数据只需要统计 `d` 中 2 的幂次，时间复杂度 $O(log d)$，空间复杂度 $O(1)$。

### 总结

这题的关键不是模拟闭包，而是发现答案只取决于公差里的 2 的幂次。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
