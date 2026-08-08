---
oj: "luogu"
problem_id: "P3662"
title: "[USACO17FEB] Why Did the Cow Cross the Road II S"
description: "把坏灯位置转成 01 数组，在所有长度为 K 的固定窗口中用滑动窗口维护坏灯个数的最小值。"
difficulty: "普及-"
date: 2026-06-18 15:06
toc: true
tags: ["双指针", "模拟", "USACO"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3662
---

[[TOC]]

### 题意

有 `N` 个信号灯，其中 `B` 个损坏。

要求最少修好多少个坏灯，才能使某一段连续长度为 `K` 的信号灯全部正常。

### 思路

先看最直接的办法：枚举每个长度为 `K` 的区间，重新统计这个区间里有多少个坏灯，再取最小值。

这个暴力版最符合题意：

@include-code(./brute.cpp, cpp)

但这样每个窗口都重新数一遍，复杂度是 $O(NK)$。

注意这题真正要求的是：

- 找一个长度为 `K` 的区间；
- 让这个区间里的坏灯数量最少。

于是只要把坏灯位置转成 `01` 数组：

- 坏灯记为 `1`
- 好灯记为 `0`

题目就变成：在所有长度为 `K` 的固定窗口里，找窗口和最小的那个。

这正是固定长度滑动窗口模型：

1. 先算第一个窗口的坏灯数 `cur`；
2. 窗口右移一格时：
   - 减去离开窗口的元素；
   - 加上进入窗口的元素；
3. 不断更新最小值。

如果你想先补一下这个基础模型，可以参考 rbook 的《滑动窗口》：
<https://rbook2.roj.ac.cn/chapter3/optimization/slide-window/index.html>

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(N)$
- 空间复杂度：$O(N)$

### 总结

这题的难点不在数据结构，而在把题目重新表达成“固定长度窗口最小和”。

一旦完成这个转化，剩下就是最基础的滑动窗口“加新减旧”。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
