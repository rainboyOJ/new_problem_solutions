---
oj: "luogu"
problem_id: "P1072"
title: "[NOIP 2009 提高组] Hankson 的趣味题"
description: "由 lcm(x,b0)=b1 可知 x 只能在 b1 的约数里取值，因此枚举 b1 的所有约数，再检查 gcd 和 lcm 两个条件即可。"
difficulty: "普及+/提高"
date: 2026-06-20 12:18
toc: true
tags: ["数论", "最大公约数", "约数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1072
---

[[TOC]]

### 题意

每组给出四个整数 $a0,a1,b0,b1$，要求统计有多少个正整数 $x$ 同时满足：

1. $gcd(x, a0) = a1$
2. $lcm(x, b0) = b1$

### 思路

先看一个最直接的小数据暴力：

@include-code(./brute.cpp, cpp)

暴力方法是直接枚举 $1..b1$ 的所有整数，逐个检查：

- $gcd(x,a0) == a1$
- $lcm(x,b0) == b1$

这个思路完全正确，但如果真的每次都枚举到 $b1$，面对 $2 * 10^9$ 的数据就肯定不行。

#### 关键观察：x 一定是 b1 的约数

因为题目要求：

$lcm(x, b0) = b1$

最小公倍数一定同时是 $x$ 和 $b0$ 的倍数，所以 $b1$ 一定是 $x$ 的倍数。  
换句话说：

$x | b1$

这就把候选范围从“所有正整数”一下缩成了“$b1$ 的所有约数”。

#### 为什么只检查约数就够了？

如果某个数 $x$ 不是 $b1$ 的约数，那么它根本不可能满足：

$lcm(x, b0) = b1$

所以不会漏解。

于是正式做法就是：

1. 枚举 $b1$ 的所有约数
2. 对每个约数 $x$，检查：
   - $gcd(x, a0) == a1$
   - $lcm(x, b0) == b1$
3. 满足就计数

#### 约数怎么枚举？

Python 版本先用预筛的质数分解 `b1`，再逐个质因子扩展约数列表。这样只生成真正的约数；最多 2000 组数据时，比每组枚举所有整数到平方根更稳定。

### Python 知识

- `math.gcd` 直接提供经过优化的欧几里得算法。
- 约数列表从 `[1]` 开始，每得到质因子幂就用生成器扩展所有新约数。
- `sum(条件 for value in divisors)` 利用布尔值可当 `0/1`，直接统计合法约数。
- 一次预筛到所有 `b1` 的最大平方根，供全部测试用例复用。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：条件计数生成器。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：列表扩展模式。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度主要是质因数分解和枚举 `b1` 的所有约数；若约数个数为 $d(b1)$，检查部分为 $O(d(b1)\log V)$。
- 空间复杂度为 $O(d(b1)+\sqrt V)$，包含约数列表和预筛质数。

其中 $V$ 是数值大小，`gcd` 的复杂度是对数级。

### 总结

这题最关键的一步是先从：

$lcm(x,b0)=b1$

推出：

$x | b1$

一旦意识到答案只可能出现在 $b1$ 的约数里，题目就从一个看似无从下手的“逆问题”，变成了标准的约数枚举 + 条件检验。


### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
