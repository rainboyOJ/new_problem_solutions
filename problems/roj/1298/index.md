---
oj: "roj"
problem_id: "1298"
title: "计算字符串距离"
description: "编辑距离 DP：用 dp[j] 滚动数组记录把 a 前缀变成 b 前缀的最少操作次数。"
difficulty: "普及-"
date: 2026-09-30 03:53
updated: 2026-10-05 08:25
toc: true
tags: ["动态规划", "字符串", "编辑距离", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common:
  - oj: "roj"
    problem_id: "1276"
    reason: "同为一本通编辑距离模板题，操作集完全相同，可用来对照同一份状态定义和转移。"
  - oj: "leetcodecn"
    problem_id: "edit-distance"
    reason: "同模型（Levenshtein 距离）的经典题，题面只差输入输出格式，适合一起对比训练。"
recommend: []
source: https://roj.ac.cn/problem/1298
---

[[TOC]]

## 题目描述

对于两个字符串，允许两种代价为 1 的操作：替换某位置字符；删掉某个字符（增加字符也等价于对面删一次），求把第一个串变成第二个串的最少操作次数，即两串距离。第一行为测试组数 $n$，接下来 $n$ 行每行两个字符串（长度 ≤ 1000），逐组输出一行答案。样例：输入 `3` / `abcdefg  abcdef` / `ab ab` / `mnklj jlknm`，输出 `1` / `0` / `4`。

## 思路

令 $dp[i][j]$ 表示 a 前 i 个字符变成 b 前 j 个字符的最少代价，边界 $dp[i][0]=i$、$dp[0][j]=j$；按 $a_i$ 与 $b_j$ 的关系转移：相同则白拿左上 $dp[i-1][j-1]$，否则在「替换」「删 $a_i$」「删 $b_j$」三种候选里取最小加 1。每行只依赖上一行，用一维数组加 `diag` 暂存左上角即可，复杂度 $O(mn)$，空间 $O(\min(m,n))$。

## 参考代码

@include-code(./main.cpp, cpp)