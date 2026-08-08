---
oj: "luogu"
problem_id: "P3601"
title: "签到题"
description: "把 qiandao(x) 转化为 x-phi(x)，再用分段筛批量计算短区间内每个数的欧拉函数。"
difficulty: "提高+/省选-"
date: 2026-07-16 19:20
toc: true
tags: ["欧拉函数", "分段筛", "数论", "筛法"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3601
---

[[TOC]]

### 题意

定义 $\operatorname{qiandao}(x)$ 为 $1$ 到 $x$ 中与 $x$ 不互质的整数个数。给出区间 $[l,r]$，求：

$$
\sum_{x=l}^{r}\operatorname{qiandao}(x)\pmod {666623333}.
$$

右端点可达 $10^{12}$，但区间长度满足 $r-l\leqslant 10^6$。

### 思路

#### 按定义枚举只能验证小数据

最直接的方法是对每个 $x$ 枚举 $1$ 到 $x$，用最大公约数判断是否不互质：

@include-code(./brute.cpp, cpp)

这个程序适合验证很小的区间，但当 $x$ 接近 $10^{12}$ 时，连枚举一个数的候选都不可能完成。

#### 转化为欧拉函数

欧拉函数 $\varphi(x)$ 表示 $1$ 到 $x$ 中与 $x$ 互质的整数个数，因此：

$$
\operatorname{qiandao}(x)=x-\varphi(x).
$$

问题转化为批量计算区间内每个数的欧拉函数。若

$$
x=p_1^{c_1}p_2^{c_2}\cdots p_s^{c_s},
$$

则：

$$
\varphi(x)=x\prod_{q=1}^{s}\left(1-\frac{1}{p_q}\right).
$$

所以只要找出 $x$ 的所有不同质因子，每发现一个质因子 $p$，就执行：

$$
\varphi(x)\leftarrow\frac{\varphi(x)}{p}(p-1).
$$

#### 在短区间上做分段质因数分解

不能从 $1$ 筛到 $r$，因为 $r$ 可达 $10^{12}$；但 $[l,r]$ 最多只有约一百万个数。为区间内每个位置维护两个值：

- `remaining[i]`：尚未除去已知质因子的部分，初始为 $l+i$；
- `phi_value[i]`：欧拉函数当前值，初始也为 $l+i$。

先用线性筛求出所有不超过 $\lfloor\sqrt r\rfloor$ 的质数。对每个质数 $p$，从区间内第一个 $p$ 的倍数开始枚举：

1. 对这个位置的 `phi_value` 乘上 $(p-1)/p$；
2. 从 `remaining` 中把所有 $p$ 因子除尽。

同一个质因子无论指数是多少，都只应在欧拉函数乘积中出现一次，所以先更新一次 `phi_value`，再用 `while` 除尽 `remaining`。

#### 为什么最后的剩余部分至多是一个质数

所有 $p\leqslant\sqrt r$ 的质因子处理完后，若某个 `remaining[i]` 仍大于 `1`，它一定是质数。

反设它是合数，那么它至少有一个质因子不超过自身平方根，也不超过原数平方根，进而不超过 $\sqrt r$。这个质因子本应已经在前面的分段处理中被除尽，产生矛盾。

因此最后只需对大于 `1` 的剩余因子再更新一次欧拉函数，就完成了完整分解。

原 `main.py` 使用相同数学模型，但百万长度区间上的多轮 Python 循环、任意精度整数运算和数组访问常数较大，未通过评测。C++ 用两个连续的 `long long` 数组完成原地分解，并用整数下标访问区间。

#### 正确性说明

对区间内任意 $x$，程序会处理它的每个不超过 $\sqrt r$ 的不同质因子，并对每个质因子恰好执行一次 $\varphi\leftarrow\varphi/p\cdot(p-1)$。除尽该质因子的所有幂次，只用于确保后续能识别尚未处理的因子，不会重复修改欧拉函数。

小质数处理结束后，剩余部分只能是 `1` 或一个大质数；若是大质数，程序再执行一次相同更新。因此 `phi_value[x-l]` 最终等于欧拉乘积公式给出的 $\varphi(x)$。

由 $\operatorname{qiandao}(x)=x-\varphi(x)$，逐项累加并取模后得到题目要求的区间和，所以算法正确。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设区间长度为 $D=r-l+1$。

- 线性筛到 $\sqrt r$ 的时间复杂度为 $O(\sqrt r)$。
- 分段枚举的总次数约为 $D\sum_{p\leqslant\sqrt r}1/p$，可写为 $O(D\log\log r)$；除去质因子幂次的总次数也受每个数的质因子个数限制。
- 总时间复杂度为 $O(\sqrt r+D\log\log r)$。
- 质数筛和区间数组占用 $O(\sqrt r+D)$ 空间。
- `brute.cpp` 按定义枚举，只适用于很小的 $r$。

### 总结

大端点并不允许筛到 $r$，短区间才是真正可以利用的约束。先把不互质计数转成 $x-\varphi(x)$，再用 $\sqrt r$ 内的质数对 $[l,r]$ 做分段分解，就能在只保存一百万个区间状态的前提下求出全部欧拉函数。
