---
oj: "luogu"
problem_id: "P4391"
title: "[BalticOI 2009] Radio Transmission 无线传输"
description: "求字符串的最小周期长度。用整个字符串的最长 border 求能够生成接收片段的最短信号周期。"
difficulty: "普及/提高-"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "周期", "border", "哈希", "字符串", "python", "cpp"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P3375"
    reason: "KMP 模板题：先掌握 nxt 数组（最长 border）的本质，才能理解最小正周期公式"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4391
---

[[TOC]]

### 题意

给出一段可能从周期信号中截取的字符串，求原信号最短可能长度。

### 思路

周期与 border 是同一枚硬币的两面：$\text{周期长度} = n - \text{border长度}$。最小周期对应最长 border。

#### KMP 法

求前缀函数 $\text{pref}[i]$ 表示 $s[:i+1]$ 的最长 border。答案 $= n - \text{pref}[n-1]$。

#### 哈希法

用滚动哈希直接枚举长度验证。

#### 周期与 border 的数学证明

**定义**：$\text{len}$ 是字符串 $s[1..n]$ 的周期 $\iff \forall i \in [1, n-\text{len}],\; s[i] = s[i+\text{len}]$。

**定理**：$\text{len}$ 是周期 $\iff s[1..n-\text{len}] = s[\text{len}+1..n]$。

**证明**（$\Rightarrow$）：对任意 $k \in [1, n-\text{len}]$，左边第 $k$ 个字符为 $s[k]$，右边第 $k$ 个字符为 $s[\text{len}+k]$。由周期定义取 $i=k$ 得 $s[k] = s[\text{len}+k]$。$k$ 的任意性保证两子串在所有对应位置相等，故 $s[1..n-\text{len}] = s[\text{len}+1..n]$。

（$\Leftarrow$）若 $s[1..n-\text{len}] = s[\text{len}+1..n]$，则对任意 $k \in [1, n-\text{len}]$ 有 $s[k] = s[\text{len}+k]$，即 $\text{len}$ 是周期。$\square$

#### 图解：样例 $cabcabca$（n=8）周期 $3$

```
┌───┬───┬───┬───┬───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │  ← 位置
├───┼───┼───┼───┼───┼───┼───┼───┤
│ c │ a │ b │ c │ a │ b │ c │ a │  ← 字符
└───┴───┴───┴───┴───┴───┴───┴───┘
├───── s[1..5] ─────┤
              ├───── s[4..8] ─────┤
              ↑ 错位 len=3

      c a b c a
      c a b c a        ← 5 个字符逐位相等
```

逐位验证周期定义 $s[i]=s[i+len]$：

```
i=1: s[1]=c, s[4]=c  ✓
i=2: s[2]=a, s[5]=a  ✓
i=3: s[3]=b, s[6]=b  ✓
i=4: s[4]=c, s[7]=c  ✓
i=5: s[5]=a, s[8]=a  ✓
```

答案 $= 3 = n - \text{border} = 8 - 5$。

#### 哈希原理

滚动哈希把前缀视为 $P$ 进制数，$s[1]$ 在最高位：

$$
h[i] = h[i-1] \times P + s[i]
$$

取子串 $s[l..r]$ 等价于切掉 $h[r]$ 的高位（$s[1..l-1]$）和低位（$s[r+1..n]$）：

$$
\text{get\_hash}(l, r) = h[r] - h[l-1] \times p^{\,r-l+1}
$$

以 $P=10$，字符串 $\text{"abc"}$ 截取 $\text{"bc"}$（位置 $2\sim3$）为例：

| 表达式 | 值 |
|--------|-----|
| $h[3]$ | $a\cdot 10^2 + b\cdot 10 + c$ |
| $h[1]$ | $a$ |
| $h[1] \times 10^{2}$ | $a\cdot 10^2$ |
| $h[3] - h[1]\times 10^{2}$ | $b\cdot 10 + c = \text{"bc"}$ |

减去 $h[l-1] \times P^{\,r-l+1}$ 就是砍掉高位，保留长度 $r-l+1$ 的一段。

#### 哈希法枚举周期

定理给出周期的充要条件：$s[1..n-\text{len}] = s[\text{len}+1..n]$。哈希法从 $\text{len}=1$ 枚举到 $n$，用 $\text{get\_hash}$ 判断此条件是否成立，第一个满足的 $\text{len}$ 就是最小周期。每次判断 $O(1)$，总 $O(n)$。

### 代码

KMP 法：

@include-code(./main.py, python)

@include-code(./main-kmp.cpp, cpp)

哈希实现：

@include-code(./main-hash.cpp, cpp)

### 复杂度

时间和空间均为 $O(n)$。

### 总结

周期与 border 是同一件事的两种描述：`周期长度 = 前缀长度 - border 长度`。
