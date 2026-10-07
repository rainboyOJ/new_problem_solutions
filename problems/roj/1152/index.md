---
oj: "roj"
problem_id: "1152"
title: "最大数max(x,y,z)"
description: "三次调用 max3 代入公式后浮点除法，%.3f 保留三位小数输出。"
difficulty: "入门"
date: 2026-09-29 21:02
updated: 2026-10-05 03:45
toc: true
tags: ["入门", "语法", "函数", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1152
---

[[TOC]]

## 题目描述

给定三个数 $a,b,c$，计算 $m=\dfrac{\max(a,b,c)}{\max(a+b,b,c)\times\max(a,b,b+c)}$，其中分子取三个原数的最大值，分母左因子把 $a$ 换成 $a+b$、右因子把 $c$ 换成 $b+c$。题面还要求把"求三个数的最大值 $\max(x,y,z)$"分别定义成函数和过程来做。

**输入**：一行三个数 $a,b,c$。**输出**：$m$，保留到小数点后三位。样例输入 `1 2 3`：分子 $\max(1,2,3)=3$，左因子 $\max(3,2,3)=3$，右因子 $\max(1,2,5)=5$，$m=3/(3\times5)=0.2$，输出 `0.200`。

## 思路

按公式逐字代入：分子用函数版 `max3` 拿返回值，两个分母因子用过程版 `max3_proc`（C++ 用引用/全局输出参数模拟 Pascal 的 var 参数）写出结果。注意 `1.0*` 把整数除法抬成浮点除法，最后 `printf("%.3f")` 四舍五入保留三位小数即可，整体 $O(1)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
