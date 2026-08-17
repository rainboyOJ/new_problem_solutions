---
oj: "shumeng"
problem_id: "CSP202603D"
title: "异或"
description: "利用 f(n) 的逐位公式，把区间数位平移转化为线段树上的模 k 线性维护。"
difficulty: "提高+/省选-"
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
---

[[TOC]]

## 形式化题目

给定 $n,m,k$（$k$ 为奇数），定义 $a\oplus_k b$ 为 $k$ 进制下逐位相加且不进位的运算，并递归定义

$$f(0)=0,\qquad f(n)=n\oplus_k f(n-1).$$

维护一个长度为 $n$ 的序列 $a_1,\dots,a_n$，支持两种操作：

- `1 l r v`：把 $[l,r]$ 内的每个 $a_i$ 改为 $a_i\oplus_k v$；
- `2 l r`：查询 $f(a_l)\oplus_k f(a_{l+1})\oplus_k\cdots\oplus_k f(a_r)$。

## 思路

### 把递推函数化成数位公式

设 $n$ 的 $k$ 进制最低位为 $d_0$，第 $p$ 位为 $d_p$。把递推式逐位展开可得：

$$
f(n)_0=\frac{d_0(d_0+1)}2\pmod k,\qquad
f(n)_p=d_p(d_0+1)\pmod k\quad(p\ge 1).
$$

这里除以 $2$ 使用逆元 $(k+1)/2$，因为 $k$ 为奇数时 $2$ 在模 $k$ 下有逆元。

### 朴素实现

按上面的公式逐元素计算即可验证结论，只适合小数据：

@include-code(./brute.cpp, cpp)

### 线段树维护统计量

查询需要 $f$ 的按位和，而 $f$ 只依赖 $d_0$ 和 $d_p$，因此每个节点只需维护下面这些模 $k$ 的量：

- $S_0=\sum d_0$，$S_{00}=\sum d_0^2$；
- 对每个高位 $p$：$S_p=\sum d_p$，$S_{p0}=\sum d_p d_0$。

于是查询答案的第 $0$ 位是 $(S_{00}+S_0)/2$，第 $p$ 位是 $S_{p0}+S_p$。

### 区间加如何更新

区间加上 $v$ 后，设 $v$ 的第 $0$ 位和第 $p$ 位分别为 $c_0,c_p$，则每个数变为 $d_0'=d_0+c_0,\ d_p'=d_p+c_p$（模 $k$）。代入上面两个公式展开，得到逐项的线性更新：

| 维护量 | 更新后 |
| --- | --- |
| $S_0$ | $S_0+\text{len}\cdot c_0$ |
| $S_{00}$ | $S_{00}+2c_0S_0+\text{len}\cdot c_0^2$ |
| $S_p$ | $S_p+\text{len}\cdot c_p$ |
| $S_{p0}$ | $S_{p0}+c_0S_p+c_pS_0+\text{len}\cdot c_pc_0$ |

所有公式都在模 $k$ 的环上成立。区间操作用懒标记保存每个数位的平移量，`push_down` 时对整段节点做同样的线性更新即可。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设 $D$ 为需要的 $k$ 进制位数（由出现过的最大值决定）。

- 时间：每次区间操作或查询为 $O(D\log n)$，总时间复杂度 $O(mD\log n)$。
- 空间：每个节点保存 $O(D)$ 个统计量，空间复杂度 $O(Dn)$。

## 总结

先把递推函数化成数位公式，再维护公式中真正需要的低阶统计量，就能把看似逐个数位处理的区间操作转化为线段树上的线性更新。关键在于发现 $f(n)$ 每位的值只依赖最低位 $d_0$，因此不需要维护整个数值。