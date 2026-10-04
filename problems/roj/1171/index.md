---
oj: "roj"
problem_id: "1171"
title: "大整数的因子"
description: "利用同余性质逐位递推，判断 30 位十进制大整数能被 2~9 中哪些数整除。"
difficulty: "入门"
date: 2026-09-29 21:51
updated: 2026-09-29 21:53
toc: true
tags:
  - "大整数"
  - "同余"
  - "模拟"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1171
---

[[TOC]]

## 形式化题目

给定一个十进制非负整数 $c$（位数 $|c| \le 30$），求集合

$$
\{\, k \in \{2,3,\dots,9\} \mid c \bmod k = 0 \,\}
$$

若集合为空，输出 `none`。

## 直接正解

### 思路

$c$ 最多有 30 位，远超普通整型能直接存储的范围，因此不能直接算出 $c$ 再取模。但判断一个数能否被 $k$ 整除，只需要知道它对 $k$ 的余数。

利用同余性质：

$$
(10a + b) \bmod k = (10 \cdot (a \bmod k) + b) \bmod k
$$

把 $c$ 的十进制表示从高位到低位逐位扫描，维护当前余数 $r$。每读入一位数字 $d$，就更新

$$
r \leftarrow (10r + d) \bmod k
$$

扫描结束后，若 $r=0$，则 $c$ 能被 $k$ 整除。

由于 $k$ 的范围只有 $2$ 到 $9$，对每个 $k$ 分别做一次扫描即可；也可以在扫描过程中同时维护 8 个余数，但题目范围很小，分别判断已经足够简洁。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(8 \cdot |c|) = O(|c|)$，其中 $|c| \le 30$。
- 空间复杂度：$O(1)$，仅使用常数额外空间。

## 总结

本题核心是把“大整数取模”化归为“逐位递推求余数”。利用同余的线性性质，不需要高精度除法，也不需要把整个数存下来，就能完成整除判定。
