---
oj: "roj"
problem_id: "1039"
title: "判断数正负"
description: "对整数 N 与 0 做三分支比较，直接输出 positive / zero / negative。"
difficulty: "入门"
date: 2026-09-29 15:38
updated: 2026-10-04 23:13
toc: true
tags: ["入门", "语法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1039
---

[[TOC]]

## 题目描述

给定一个整数 $N$（$-10^9 \leqslant N \leqslant 10^9$），判断它的正负：$N > 0$ 输出 `positive`，$N = 0$ 输出 `zero`，$N < 0$ 输出 `negative`。

输入：一个整数 $N$。

输出：按上述规则输出对应单词。

样例输入：

```
1
```

样例输出：

```
positive
```

## 思路

三个条件互斥且完备，直接用 `if-else if-else` 三分支比较 $N$ 与 0，命中哪支就输出哪个单词。注意输出必须是题面的三个英文单词，不能写成 `+`/`-`/`0`。

## 参考代码

@include-code(./main.cpp, cpp)
