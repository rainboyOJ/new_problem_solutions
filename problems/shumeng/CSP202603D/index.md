---
oj: "shumeng"
problem_id: "CSP202603D"
title: "异或"
description: "利用 f(n) 的逐位公式，把区间数位平移转化为线段树上的模 k 线性维护。"
date: 2026-07-31 16:22
toc: true
tags: ["线段树", "数位", "数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202603D
difficulty: "提高+/省选-"
---

[[TOC]]

### 题意

定义 `a \oplus_k b` 为 `k` 进制下逐位相加且不进位。函数满足

$$f(0)=0,\qquad f(n)=n\oplus_k f(n-1).$$

对序列进行区间数位平移，要求查询区间内所有 `f(a_i)` 的 `\oplus_k` 和。`k` 是奇数。

### 思路

设 `n` 的 `k` 进制最低位为 `d_0`，第 `p` 位为 `d_p`。由递推逐位展开可得：

$$
f(n)_0=\frac{d_0(d_0+1)}2\pmod k,\qquad
f(n)_p=d_p(d_0+1)\pmod k\quad(p\ge 1).
$$

这里除以 2 使用逆元 `(k+1)/2`，因为 `k` 为奇数。

暴力程序直接按公式计算每个元素，适合小数据验证：

@include-code(./brute.cpp, cpp)

线段树节点维护以下量，所有量都在模 `k` 意义下保存：

- `S0=sum(d_0)`，`S00=sum(d_0^2)`；
- 对每个高位 `p`，维护 `Sp=sum(d_p)` 与 `Sp0=sum(d_p d_0)`。

于是查询答案的第 0 位是 `(S00+S0)/2`，第 `p` 位是 `Sp0+Sp`。

若区间加上数 `v`，记其第 0 位和第 `p` 位分别为 `c_0,c_p`，则

$$d_0'=d_0+c_0,\qquad d_p'=d_p+c_p\pmod k.$$

对应的更新公式如下：

| 维护量 | 更新后 |
| --- | --- |
| `S0` | `S0 + len*c0` |
| `S00` | `S00 + 2*c0*S0 + len*c0^2` |
| `Sp` | `Sp + len*cp` |
| `Sp0` | `Sp0 + c0*Sp + cp*S0 + len*cp*c0` |

所有公式都在模 `k` 的环上成立，区间操作用懒标记保存各数位的平移量。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

令 `D` 为 `k` 进制位数。每次区间操作或查询的复杂度为 `O(D log n)`，空间复杂度为 `O(Dn)`。

### 总结

先把递推函数化成数位公式，再维护公式中真正需要的低阶统计量，就能把看似逐个数位处理的区间操作转化为线段树上的线性更新。
