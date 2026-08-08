---
oj: "luogu"
problem_id: "P8395"
title: "[CCC 2022 S1]  Good Fours and Good Fives"
description: "把 5 的个数当作枚举量，利用 `b ≡ n (mod 4)` 直接统计满足 `4a+5b=n` 的非负整数解个数。"
difficulty: "入门"
date: 2026-06-19 11:15
toc: true
tags: ["数学", "枚举", "推导"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P8395
---

[[TOC]]

### 题意

给出一个正整数 `n`。

要求统计有多少组非负整数解 `(a,b)` 满足：

`4a + 5b = n`

这里 `a` 表示用了多少个 `4`，`b` 表示用了多少个 `5`，并且不区分顺序。

### 思路

最直接的办法是枚举用了多少个 `5`。

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

如果当前用了 `b` 个 `5`，那么剩下的值就是 `n - 5b`。
只要这个剩余值是非负数，并且能被 `4` 整除，就得到一种合法方案。

这份朴素代码的瓶颈是要把 `b = 0..floor(n/5)` 全部试一遍。

继续观察整除条件：

`n - 5b ≡ 0 (mod 4)`

因为 `5 ≡ 1 (mod 4)`，上式等价于：

`b ≡ n (mod 4)`

也就是说，合法的 `b` 不是随便出现的，而是：

`n % 4, n % 4 + 4, n % 4 + 8, ...`

只要这些值不超过 `floor(n/5)` 就行。

于是可以直接计数：

- 设 `max_five = floor(n/5)`；
- 设 `first_five = n % 4`，它是最小的合法 `b`；
- 如果 `first_five > max_five`，说明一个合法值都没有，答案是 `0`；
- 否则答案就是等差数列项数：

`(max_five - first_five) / 4 + 1`

这就把逐个枚举变成了 $O(1)$ 计算。

#### 核心公式

题目要求统计非负整数解：

$$
4a+5b=n
$$

枚举 $b$ 时，合法条件为：

$$
n-5b\equiv 0\pmod 4
$$

因为 $5\equiv 1\pmod 4$，所以：

$$
b\equiv n\pmod 4
$$

令 $maxFive=\lfloor n/5\rfloor$，$first=n\bmod 4$。若 $first>maxFive$，答案为 $0$；否则：

$$
ans=\left\lfloor\frac{maxFive-first}{4}\right\rfloor+1
$$


公式解释：决定用了多少个 `5` 后，剩下部分必须全部由 `4` 组成。模 `4` 后能直接筛出所有合法的 `b`，它们按公差 `4` 出现，所以答案就是这个等差序列在合法范围内的项数。


### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(1)$
- 空间复杂度：$O(1)$

### 总结

这题本质是在统计方程 `4a + 5b = n` 的非负整数解个数。

关键一步是把“剩余部分能否由 `4` 组成”转成同余条件 `b ≡ n (mod 4)`，然后直接数出区间里有多少个这样的 `b`。
