---
oj: "roj"
problem_id: "3566"
title: "[NOIP2008-提高] 火柴棒等式"
description: "枚举 A、B 后 C=A+B 唯一确定，O(1) 核对三个数的火柴根数之和是否等于 n-4。"
difficulty: "普及-"
date: 2026-10-02 08:02
updated: 2026-10-06 14:16
toc: true
tags: ["枚举", "剪枝", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3566
---

[[TOC]]

## 题目描述

给你 $n$ 根火柴棍（$n \leqslant 24$），统计能拼出多少个形如 $A+B=C$ 的等式。$A$、$B$、$C$ 是用火柴棍拼出的非负整数（非零数最高位不能是 $0$），加号与等号各需 2 根，$n$ 根火柴必须全部用完；$A \neq B$ 时 $A+B=C$ 与 $B+A=C$ 视为不同等式。数字 $0$–$9$ 各需的火柴根数为：$0$ 要 6 根，$1$ 要 2 根，$2$ 要 5 根，$3$ 要 5 根，$4$ 要 4 根，$5$ 要 5 根，$6$ 要 6 根，$7$ 要 3 根，$8$ 要 7 根，$9$ 要 6 根。

**输入格式**：一个整数 $n$。

**输出格式**：一个整数，能拼成的不同等式的数目。

**样例输入 1**：`14`；**样例输出 1**：`2`（两个等式为 $0+1=1$ 和 $1+0=1$）。

**样例输入 2**：`18`；**样例输出 2**：`9`（如 $0+4=4$、$0+11=11$、$2+7=9$、$10+1=11$ 等）。

## 思路

先查出每个数字需要的火柴根数，定义 $\mathrm{cost}(x)$ 为整数 $x$ 逐位求和的根数（$\mathrm{cost}(0)=6$），扣除加号等号的 4 根后需满足 $\mathrm{cost}(A)+\mathrm{cost}(B)+\mathrm{cost}(A+B)=n-4$。由于 $C=A+B$ 被唯一确定，只需枚举有序对 $(A,B)$ 再 $O(1)$ 核对；又因为每位至少 2 根且 $C$ 的位数不小于 $A$、$B$，$n \leqslant 24$ 时可证 $A$、$B$ 都不超过 4 位，枚举到 $9999$ 即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
