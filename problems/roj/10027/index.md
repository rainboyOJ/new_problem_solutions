---
oj: "roj"
problem_id: "10027"
title: "Decode"
description: "第二行给出 A~Z 的 26 位编码表：对第一行逐字符查表，大写字母换成 T[c-A]，空格等表外字符原样输出，一趟 O(n) 扫完。"
difficulty: "普及"
date: 2026-10-02 18:54
updated: 2026-10-04 22:08
toc: true
tags: ["入门", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10027
---

[[TOC]]

## 题目描述

给定一行字符串 $s$（长度不超过 $10000$，只含大写字母和空格），以及一个恰含 $26$ 个大写字母的串 $T$：$T$ 的第 $i$ 位表示字母 $\mathrm{A}+i$ 编码后变成的字母。把 $s$ 中每个大写字母按此表替换，空格原样保留后输出整行。

样例 1 输入 `HPC PJVYMIY` / `BLMRGJIASOPZEFDCKWYHUNXQTV`，输出 `ACM CONTEST`；样例 2 输入 `FDY GAI BG UKMY` / `KIMHOTSQYRLCUZPAGWJNBVDXEF`，输出 `THE SKY IS BLUE`。

## 思路

对每个大写字母 $c$，输出 $T[c-\mathrm{A}]$；其它字符（如空格）原样输出。字符之间互不影响，所以一趟 $O(n)$ 线性扫描即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
