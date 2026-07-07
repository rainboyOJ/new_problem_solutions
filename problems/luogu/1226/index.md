---
oj: "luogu"
problem_id: "P1226"
title: "【模板】快速幂"
description: "按指数的二进制位做快速幂，每次平方底数，当前位为 1 时把答案乘上底数并取模。"
difficulty: "普及-"
date: 2026-07-06 20:42
toc: true
tags: ["数学", "快速幂", "模板题"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1226
---

[[TOC]]

### 题意

给出整数 `a, b, p`，求：

```text
a^b mod p
```

并按题目指定格式输出。

### 思路

最直接的办法是连乘 `b` 次：

@include-code(./brute.cpp, cpp)

这个做法适合小数据，但 `b` 可以接近 `2^31`，不能逐次乘。

快速幂的思想是把指数按二进制拆开。例如：

```text
13 = 8 + 4 + 1
a^13 = a^8 * a^4 * a
```

扫描 `b` 的二进制位时，维护：

- `ans`：当前已经选中的幂次乘积；
- `base`：当前位对应的 `a^(2^i)`。

每一轮：

1. 如果当前最低位是 `1`，就令 `ans = ans * base % p`；
2. 令 `base = base * base % p`；
3. 让 `b` 右移一位。

所有乘法都及时对 `p` 取模，避免数值无限变大。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：`O(log b)`
- 空间复杂度：`O(1)`

### 总结

快速幂的核心是“指数二进制拆分”。每一位只处理一次，所以能把连乘 `b` 次降到 `log b` 次。
