---
oj: "roj"
problem_id: "1167"
title: "再求f(x,n)"
description: "按题面给出的连分式递归定义直接计算 f(x,n)，用 functools.cache 做一行式记忆化递归。"
difficulty: "入门"
date: 2026-09-29 21:39
updated: 2026-10-04 12:56
toc: true
tags: ["递归", "连分式", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1167"
---

[[TOC]]

## 形式化题目

给定两个数 $x$、$n$，函数 $f(x,n)$ 定义为：

$$
f(x,1)=\frac{x}{1+x},\qquad
f(x,n)=\frac{x}{n+f(x,n-1)}\ (n>1)
$$

要求输出 $f(x,n)$ 的值，保留两位小数。

## 正解

### 思路

题面已经把递归式写清楚了，直接按定义实现即可。把

$$
f(x,n)=\cfrac{x}{n+\cfrac{x}{(n-1)+\cfrac{x}{\cdots+\cfrac{x}{1+x}}}}
$$

翻译成递归函数：

- 当 $n=1$ 时返回 $\dfrac{x}{1+x}$；
- 否则返回 $\dfrac{x}{n+f(x,n-1)}$。

由于测试数据中 $n$ 很小（$n\leqslant 9$），递归深度完全在 Python 默认栈范围内。用 `functools.cache` 把结果记忆化，既保持一行式表达，也避免重复计算。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，每层只算一次。
- 空间复杂度：$O(n)$，递归栈与记忆化各 $O(n)$。

## 总结

这是一道“按公式写递归”的入门题。核心是把题面给出的连分式直接映射为递归函数，注意 $n=1$ 的边界即可。
