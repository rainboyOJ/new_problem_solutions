---
oj: "roj"
problem_id: "1046"
title: "判断一个数能否同时被3和5整除"
description: "“同时被 3 和 5 整除”折叠成一次取余：3 与 5 互质，等价于 n % 15 == 0，命中输出 YES，否则 NO。"
difficulty: "入门"
date: 2026-09-29 16:10
updated: 2026-10-04 23:23
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1046
---

[[TOC]]

## 题目描述

输入一个整数 $n$（$-1{,}000{,}000 < n < 1{,}000{,}000$，含负数与 $0$），判断它能否同时被 3 和 5 整除：能则输出 `YES`，否则输出 `NO`。

输入：一行一个整数 $n$。

输出：一行 `YES` 或 `NO`。

样例输入：

```
15
```

样例输出：

```
YES
```

## 思路

3 与 5 互质，"同时被 3 和 5 整除"等价于"被 $\operatorname{lcm}(3,5)=15$ 整除"，所以只需一次取余 `n % 15 == 0`。注意条件是"同时"，不能写成 `||`；负数与 $0$ 不必特判，$0$ 也是 15 的倍数。

## 参考代码

@include-code(./main.cpp, cpp)
