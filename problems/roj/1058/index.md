---
oj: "roj"
problem_id: "1058"
title: "求一元二次方程"
description: "用判别式 b²-4ac 的符号三分支：为负输出 No answer!，精度内为零输出重根，否则套求根公式并把两根排序，统一按 %.5f 输出。"
difficulty: "入门"
date: 2026-09-29 17:18
updated: 2026-10-04 23:43
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1058
---

[[TOC]]

## 题目描述

求一元二次方程 $ax^2+bx+c=0$（$a \neq 0$）的根，结果精确到小数点后 5 位。输入一行三个浮点数 $a,b,c$；若两根相等输出 `x1=x2=...`，若两根不等按根小者在前的顺序输出 `x1=...;x2=...`，若无实根输出 `No answer!`，数字与符号之间没有空格。
样例输入：`-15.97 19.69 12.02`；样例输出：`x1=-0.44781;x2=1.68075`。

## 思路

先算判别式 $\Delta=b^2-4ac$：$\Delta<-10^{-12}$ 时输出 `No answer!`，$|\Delta|<10^{-12}$ 时视为重根按 `x1=x2=` 输出，$\Delta>10^{-12}$ 时用求根公式算出两根。两根谁大谁小由分母 $2a$ 的符号决定，所以算出后要比较交换，保证根小者在前。输出前把 $|x|<10^{-6}$ 的根写成 $0$，避免打印出 `-0.00000`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
