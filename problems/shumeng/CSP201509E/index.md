---
oj: "shumeng"
problem_id: "CSP201509E"
title: "最佳文章"
description: "在 AC 自动机上建立 max-plus 转移矩阵，快速幂求超长文章的最大匹配次数。"
difficulty: "提高+/省选-"
date: 2026-07-31 16:21
toc: true
tags: ["AC 自动机", "矩阵快速幂", "动态规划"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201509E
---

[[TOC]]

### 题意

构造恰好 $m$ 个字符的文章，使给定单词在文章中的总出现次数最多，重叠出现也计数。

### 思路

先看只适用于短文章的枚举基准：

@include-code(./brute.cpp, cpp)

AC 自动机状态表示当前文章后缀能匹配到的最长前缀。状态沿某个字符转移后，该状态的 `score` 是以当前位置结尾的所有重要单词数，失配指针把包含关系和重叠出现都累计进去。

令矩阵 `T[u][v]` 表示从状态 `u` 追加一个字符到 `v` 能增加的重要度，取 max-plus 意义下的最大值。长度为 $m$ 的文章对应 `T` 的 $m$ 次幂；用二进制快速幂将初始只有根状态为 0 的 DP 向量推进即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设自动机状态数为 $S\leqslant100$，时间复杂度为 $O(S^3\log m)$，空间复杂度为 $O(S^2)$。

### 总结

超长长度使逐字符 DP 不可行，但转移规则固定。把普通加法换成“取最大值和加奖励”，矩阵快速幂就能跳过任意多次相同转移。
