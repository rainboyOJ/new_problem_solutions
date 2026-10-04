---
oj: "roj"
problem_id: "1468"
title: "「一本通 2.2 练习 2」OKR-Periods of Words"
description: "利用 KMP 的 border 性质与失配指针链，将求最大周期转化为求每个前缀的最短正 border，通过路径压缩在 O(n) 时间内完成前缀周期求和。"
difficulty: "普及+/提高-"
date: 2026-09-30 12:30
updated: 2026-10-04 13:20
toc: true
tags:
  - "字符串"
  - "KMP"
  - "周期"
favorite: false
favorite_reason: ""
categories:
  - "字符串"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1468
---

[[TOC]]

## 形式化题目

给定一个长度为 $k$ 的小写字母字符串 $S$。

对于 $S$ 的任意前缀 $A$：
- 若存在一个真前缀 $Q$（即 $Q \neq A$ 且 $Q$ 非空），使得 $A$ 是字符串 $QQ$ 的前缀，则称 $Q$ 是 $A$ 的一个周期。
- $A$ 的最大周期定义为 $A$ 的所有周期中最长的那一个；若 $A$ 不存在任何周期，则其最大周期为空串（长度为 $0$）。

求字符串 $S$ 的所有非空前缀的最大周期长度之和。

## 正解

### 思路

#### 1. 周期与 Border 的对偶转化

设当前考虑的前缀为 $A$，其长度为 $|A| = i$。假设 $Q$ 是 $A$ 的一个周期，长度为 $|Q| = q$。

根据定义：
1. $Q$ 是 $A$ 的真前缀，因此 $1 \le q < i$。
2. $A$ 是 $QQ$ 的前缀。因为 $q < i \le 2q$，字符串 $QQ$ 的长度为 $2q$。
   - $QQ$ 的前 $q$ 个字符构成了 $Q$，而后 $q$ 个字符同样是 $Q$。
   - $A$ 作为 $QQ$ 的前缀，其长度为 $i$。因此 $A$ 的后缀（从位置 $q + 1$ 到 $i$，长度为 $i - q$）必然等于 $Q$ 的前缀（长度为 $i - q$）。
   - 又因为 $Q$ 本身是 $A$ 的前缀，所以 $Q$ 的前 $i - q$ 个字符也就是 $A$ 的前 $i - q$ 个字符。
   - 这意味着：$A$ 拥有一个长度为 $b = i - q$ 的公共真前缀与真后缀（即 Border）。

反过来，如果 $A$ 拥有一个长度为 $b$（$1 \le b < i$）的 Border，那么取 $q = i - b$：
- 由于 $b \ge 1$，有 $q < i$，即 $Q = A[1 \dots q]$ 是 $A$ 的真前缀；
- 由于 $b < i$，有 $q > 0$；
- 此时 $QQ$ 的前 $i$ 个字符刚好与 $A$ 匹配，即 $A$ 是 $QQ$ 的前缀。

因此，**$Q$ 是 $A$ 的周期 $\iff$ $A$ 存在长度为 $i - |Q|$ 的 Border**。

#### 2. 最大周期与最短 Border

题目要求求出 $A$ 的**最大周期**长度 $\max(q)$。由等式 $q = i - b$ 可知：
$$
\max(q) = i - \min(b)
$$
其中 $b$ 是 $A$ 的合法 Border 长度（$b > 0$）。
- 如果 $A$ 不存在任何正长度的 Border，则 $A$ 没有任何周期，最大周期长度计为 $0$。
- 如果 $A$ 存在 Border，则 $A$ 的最大周期长度等于 $i$ 减去 $A$ 的**最短正 Border 长度**。

#### 3. 利用 KMP失配树与路径压缩

在 KMP 算法中，前缀函数（`next` 数组）记录的是每个前缀的最长非平凡 Border 长度。
根据 Border 的传递性，前缀 $A$ 的所有 Border 长度依次为：
$$
nxt[i], \quad nxt[nxt[i]], \quad nxt[nxt[nxt[i]]], \quad \dots
$$
这条链最终会收敛到 $0$。链上所有非零节点就是 $A$ 的所有可能 Border 长度，其中**最靠近链底的非零值**即为 $A$ 的最短正 Border。

若每次暴力沿着 $nxt$ 链跳转到底部，单次最坏退化为 $O(i)$，总时间复杂度会退化为 $O(n^2)$。

我们可以采用**路径压缩（记忆化递推）**：
记 $\text{min\_border}[i]$ 为前缀 $S[1 \dots i]$ 的最短正 Border 长度。
- 若 $nxt[i] = 0$，说明前缀 $i$ 没有 Border，$\text{min\_border}[i] = 0$。
- 若 $nxt[i] > 0$：
  - 如果子前缀 $nxt[i]$ 自身已有最短正 Border（即 $\text{min\_border}[nxt[i]] > 0$），则前缀 $i$ 直接继承它：$\text{min\_border}[i] = \text{min\_border}[nxt[i]]$；
  - 否则说明 $nxt[i]$ 自身就是最底层的非平凡 Border，直接取 $\text{min\_border}[i] = nxt[i]$。

这样每个状态只需 $O(1)$ 时间即可转移，总复杂度线性。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(n)$。预处理 KMP 的 `next` 数组耗时 $O(n)$；随后进行一次线性扫描，通过已计算的 `min_border` 数组 $O(1)$ 转移并累加答案，总耗时为 $O(n)$。
- **空间复杂度**：$O(n)$。需要存储原字符串以及长度为 $n + 1$ 的 `next` 数组与 `min_border` 数组。

## 总结

本题的关键在于通过数学观察将「求最大周期 $Q$」对偶转化为「求最短正 Border $b$」。借助 KMP 算法的失配指针链结构以及记忆化/路径压缩技巧，避免了沿失配树向上暴跳的退化风险，将求解过程优化至严格的 $O(n)$ 线性时间。
