---
oj: "roj"
problem_id: "1015"
title: "计算并联电阻的阻值"
description: "把并联公式通分成 R = r1·r2/(r1+r2) 一次算出结果，再用 %.2f 格式化四舍五入保留 2 位小数输出。"
difficulty: "入门"
date: 2026-09-29 13:19
updated: 2026-10-04 22:30
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1015
---

[[TOC]]
## 题目描述

对于阻值为 $r_1$ 和 $r_2$ 的两个电阻，其并联总阻值按公式 $R = \dfrac{1}{\frac{1}{r_1} + \frac{1}{r_2}}$ 计算。

输入格式：一行两个浮点数 $r_1$、$r_2$，以一个空格分开。输出格式：输出并联之后的阻抗大小，保留小数点后 2 位。

输入样例：`1 2`；输出样例：`0.67`。

## 思路

把公式通分成 $R = \dfrac{r_1 r_2}{r_1 + r_2}$，读入后一次乘法一次除法即可；再用 `printf("%.2f")` 一步完成四舍五入与固定两位补零。

## 参考代码
@include-code(./main.cpp, cpp)
