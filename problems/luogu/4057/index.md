---
oj: "luogu"
problem_id: "P4057"
title: "[Code+#1] 晨跑"
description: "三人下一次相遇的天数就是三个晨跑周期的最小公倍数，先求 lcm(a,b) 再与 c 合并即可。"
difficulty: "入门"
date: 2026-06-18 22:31
toc: true
tags: ["数论", "最大公约数", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4057
---

[[TOC]]

### 题意

三个人在第 $0$ 天一起晨跑。  
之后他们分别每 $a$、$b$、$c$ 天晨跑一次。  
要求输出下一次三个人再次相遇是第几天。

### 思路

先看一个可以直接验证想法的朴素解：

从第 $1$ 天开始一天天枚举，第一次同时满足：

- $day \bmod a = 0$
- $day \bmod b = 0$
- $day \bmod c = 0$

时，这一天就是答案。

@include-code(./brute.cpp, cpp)

这个暴力写法可以帮助理解题意，但本质上它只是在找一个最小的正整数 $day$，使得它同时是 $a,b,c$ 的倍数。

换句话说，题目其实就在问：

$\operatorname{lcm}(a, b, c)$

而两个数的最小公倍数可以用：

$\operatorname{lcm}(x, y) = x / \gcd(x, y) \times y$

来计算。

所以三个数直接分两步合并就行：

1. 先求 $\operatorname{lcm}(a, b)$
2. 再求 $\operatorname{lcm}(\operatorname{lcm}(a, b), c)$

正式代码就是按这个式子直接计算答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度是 $O(\log \max(a,b,c))$，空间复杂度是 $O(1)$。

### 总结

这题虽然包装成"晨跑相遇"，本质就是一个周期同步问题。

一旦看出"下一次同时出现"对应"最小公倍数"，题目就变成了非常直接的 gcd/lcm 模板题。
