---
oj: "luogu"
problem_id: "P7072"
title: "[CSP-J 2020] 直播获奖"
description: "用树状数组维护 0..600 的成绩频率，并通过第 k 小查询在线求当前获奖分数线。"
difficulty: "普及-"
date: 2026-06-19 00:26
toc: true
tags: ["树状数组", "计数", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P7072
---

[[TOC]]

### 题意

成绩依次公布。公布第 `seen` 个成绩后，取排名前 `max(1, seen*w//100)` 人中的最低成绩作为当前分数线。

### 思路

成绩只在 `0..600`，用树状数组保存每个分数的出现次数。若当前有 `winners` 人获奖，分数线就是升序第 `seen-winners+1` 个成绩。树状数组的倍增查找可以在 $O(\log 601)$ 找到这个次序统计量。

全程只用整数计算获奖人数，避免浮点向下取整误差。

### Python 知识

- `enumerate(data, 1)` 直接得到当前已公布人数。
- `int.bit_length()` 取得树状数组倍增搜索的最高二进制步长。
- 分数范围虽小，Fenwick 写法比每轮倒扫 601 个桶更适合 Python 的循环性能。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log 601)$，空间复杂度 $O(601)$。

### 总结

动态分数线本质是频率数组上的第 $k$ 小查询。
