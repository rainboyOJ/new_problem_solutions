---
oj: "codeforces"
problem_id: "977F"
title: "Consecutive Subsequence"
description: "按结尾定义长度 + 用值到最后出现位置的桶替代前驱枚举 + 沿 pre 链回推下标"
difficulty: "1700"
date: 2026-11-04 14:50
updated: 2026-11-08 16:24
toc: true
tags:
  - 动态规划
  - 线性DP
  - 哈希表
favorite: false
favorite_reason: ""
categories:
  - 动态规划
showAtRbook: ["rbook1:lis"]
rbookLinks:
  - id: "rbook1:lis"
    reason: "本题的 f_i 就是这篇讲的「以第 i 个元素结尾的 LIS 长度」，先看这篇的 f(i)=max{1, f(j)+1} 转移，再看本题把前驱枚举换成「值→最后出现位置」的桶"
pre: []
common: []
recommend: []
source: https://vjudge.net/problem/CodeForces-977F#author=translator:1281309:zh
---

[[TOC]]

## 形式化题目

给定序列 $a_1, a_2, \dots, a_n$，选出下标 $i_1 < i_2 < \cdots < i_k$，使存在整数 $x$ 满足 $a_{i_j} = x + j - 1$，最大化 $k$ 并输出一组下标。

## 正解

### 思路

::: info
以 $i$ 结尾的最长长度只由值 $a_i - 1$ 的最优结尾决定，用哈希桶记住「值 → 最后一次出现的下标」，一次查表代替回扫，$O(n)$ 完成。
:::

记 $f_i$ 为以位置 $i$ 结尾的最长长度。位置 $i$ 前面只能接值 $a_i - 1$，所以回扫所有前驱时反复回答的其实是同一个问题——值 $a_i - 1$ 的哪个位置让 $f$ 最大，于是改成用 `last[v]` 记值 $v$ 最后一次出现的下标，$f_i = f_{last[a_i-1]} + 1$，查不到时取 $1$。同值的 $f$ 随时间单调不减（后出现的同值元素能继承前一次的全部前驱），所以桶里只留最后一次出现就是该值上的最优结尾。再开一个 `pre` 数组记前驱下标，从 $f$ 最大的位置沿链回退即得一组答案。

样例 $a = [3, 3, 4, 7, 5, 6, 8]$ 逐位算得 $f = [1, 1, 2, 1, 3, 4, 2]$，最大在 $i = 6$，沿 $pre$ 回退得 $6 \to 5 \to 3 \to 2$，反转后即 `2 3 5 6`。

::: warning
桶若改成「值第一次出现的位置」，$a = [1, 2, 3, 0, 1, 2, 3, 4]$ 会错答 $4$（正确为 $5$），所以每次出现都要覆盖。
:::

### 代码

C++ 用 `unordered_map` 存桶，Python 用 `defaultdict` 让缺键直接拿到 $-1$。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

时间期望 $O(n)$（每个位置一次查表、一次写表），空间 $O(n)$（$a$、$f$、`pre` 各 $n$ 项，桶内最多 $n$ 个不同值）。值域到 $10^9$，桶只能用哈希表，不能开数组。

## 总结

- 前驱的值由 $a_i$ 唯一确定，把不确定的「位置」换成「值 → 最后一次出现」，$O(n^2)$ 的枚举就成了一次查表。
- 需要输出方案时加一个 `pre` 数组沿链回退，相邻两项差为定值 $d$ 时把 $a_i - 1$ 换成 $a_i - d$ 即可。
- 验证：四组样例 C++/Python 均通过；与 $O(n^2)$ 暴力对拍 $200$ 组、两版互拍 $120$ 组无差异；$n = 2 \cdot 10^5$ 链式数据 C++ $96$ ms / $15.1$ MiB，Python $646$ ms / $62.6$ MiB。
