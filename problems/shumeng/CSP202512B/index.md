---
oj: "shumeng"
problem_id: "CSP202512B"
title: "数字变换"
description: "由于状态只有 512 个，预计算所有输入经过参数序列后的输出，再建立输出到输入的逆映射。"
difficulty: "未知"
date: 2026-07-31 16:22
toc: true
tags: ["位运算", "模拟", "状态压缩", "预处理"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202512B
---

[[TOC]]

## 形式化题目

9 位整数 $x$（$0 \le x < 2^9$）经过 $m$ 步变换得到输出。每步使用参数 $k_i$，先把 $x$ 的 9 位二进制分成高、中、低三组 3 位数字 $(a,b,c)$，再按规则

$$
(a',b',c')=(b,\ c \oplus f(b,k_i),\ a \oplus f(c,k_i)),\qquad
f(x,k)=((x^2+k^2)\bmod 2^3)\oplus k
$$

组合回 9 位。给定 $n$ 个输出值，求它们各自唯一的输入。

## 思路

状态空间极小，直接正向建逆映射。

### 枚举全部初始值

9 位整数只有 $2^9 = 512$ 种。对每个初始值完整模拟 $m$ 步变换，得到输出，并记录 `inverse[输出] = 初始值`。

### 按位拆合

每次变换先把 `value` 拆成三组 3 位数字，套用变换公式后再拼回 9 位。题目保证每个输出对应唯一输入，所以直接查表即可。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

预处理 $O(512 \cdot m)$，查询 $O(n)$，空间复杂度 $O(m + 512)$。

## 总结

当状态空间足够小时，正向枚举全部状态并建立逆映射，比推导逐步逆变换简单可靠。本题还体现了位运算拆位拼位的基本操作：右移、与 `7`、左移、或。