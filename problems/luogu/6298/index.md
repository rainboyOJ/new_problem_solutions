---
oj: "luogu"
problem_id: "P6298"
title: "齿轮"
description: "先统计每个 t 的倍数里有多少齿轮，再用 C(cnt[t],k) 算 gcd 是 t 的倍数的方案数，最后按倍数从大到小容斥还原精确 gcd。"
difficulty: "提高+/省选-"
date: 2026-06-20 07:04
toc: true
tags: ["数论", "容斥", "组合计数", "最大公约数", "思维"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P6298
---

[[TOC]]

### 题意

给出 $n$ 个齿轮，第 $i$ 个齿轮的齿数是 $a_i$。  
要从中选出恰好 $k$ 个齿轮组成一个齿轮组。

一个齿轮组的损耗因子定义为这 $k$ 个齿轮齿数的最大公约数。

要求对每个 $t \in [1, m]$，输出：

- gcd 恰好等于 $t$ 的 $k$ 元组合个数

答案对 $10^9+7$ 取模。

### 思路

先看一个可以直接验证的小数据暴力：

@include-code(./brute.cpp, cpp)

暴力版直接枚举所有大小为 $k$ 的组合，算出它们的 gcd，然后计数。  
这当然只能跑很小的数据，但它把题意表达得很直接。

#### 第一步：先数“gcd 是 $t$ 的倍数”的方案数

固定一个 $t$。  
如果一个组合的 gcd 是 $t$ 的倍数，那么这个组合里的每个数都必须是 $t$ 的倍数。

设：

- $cnt[t] = $ 数组里有多少个数能被 $t$ 整除

那么从这些数里任选 $k$ 个，就得到一个 gcd 为 $t$ 的倍数的组合。  
所以：

- $ways[t] = C(cnt[t], k)$

这里 $ways[t]$ 数的不是“gcd 恰好等于 $t$”，而是：

- gcd 属于 $t, 2t, 3t, \ldots$ 这些倍数的所有组合

#### 第二步：从大到小做容斥

设：

- $ans[t] = $ gcd 恰好等于 $t$ 的组合数

那么：

- $ways[t] = ans[t] + ans[2t] + ans[3t] + \ldots$

于是只要按 $t$ 从大到小枚举，就可以把更大的倍数答案先减掉：

- $ans[t] = ways[t] - ans[2t] - ans[3t] - \ldots$

这就是这题的核心容斥。

#### 组合数怎么求

因为需要大量计算 $C(x, k)$，而 $n \leqslant 10^6$，所以直接预处理：

- $fact[i]$
- $inv\_fact[i]$

然后用：

- $C(n, k) = fact[n] \cdot inv\_fact[k] \cdot inv\_fact[n-k]$

在 $O(1)$ 时间求每个组合数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设值域上界为 $m$。

- 统计 $cnt[t]$：$O(m \log m)$
- 从大到小做倍数容斥：$O(m \log m)$
- 预处理阶乘：$O(n)$

总时间复杂度：

- $O(n + m \log m)$

空间复杂度：

- $O(n + m)$

### 总结

这题的标准套路是：

1. 先统计“所有数都能被 $t$ 整除”的组合数
2. 再按倍数关系把“gcd 恰好等于 $t$”还原出来

所以本质上是一题：

- 倍数统计
- 组合数
- 容斥还原 exact gcd

的组合题。


### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
