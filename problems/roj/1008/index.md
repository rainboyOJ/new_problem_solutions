---
oj: "roj"
problem_id: "1008"
title: "计算(a+b)/c的值"
description: "把 C 的向零取整整数除法翻译成 Python：判号分流，同号直接 //，异号取负修正，一步 O(1) 求得 (a+b)/c。"
difficulty: "入门"
date: 2026-09-29 12:42
updated: 2026-09-29 12:45
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1008
---

[[TOC]]

## 形式化题目

给定三个整数 $a, b, c$（$c \neq 0$），求

$$q = \operatorname{trunc}\!\left(\frac{a+b}{c}\right)$$

即先算和 $s = a + b$，再除以 $c$ 并**舍去小数部分**。取整方向由评测数据确定：样例 $2/3 \to 0$ 说明输出是整数；真实数据 `problem3`（$-3601\ -1589\ 930$）的答案是 $-5$ 而不是 $-6$，因为 $-5190/930 = -5.58\ldots$，所以本题采用 C/C++ 整数除法的**向零取整**（trunc），不是数学上的向下取整（floor）。

等价地，$q = \operatorname{sign}(s)\cdot\lfloor |s|/|c| \rfloor$（$s = 0$ 时 $q = 0$）。

## 正解

### 思路

最自然的直译是 C++ 的 `(a+b)/c`，写成 Python 就是 `(a + b) // c`。它能通过同号的测例，却会在"和与 $c$ 异号"时集体偏小 1——因为 Python 的 `//` 是向下取整，而本题要求向零取整：

| $s = a+b$ | $c$ | 商 $s/c$ | Python `//`（floor） | 本题答案（trunc） | 是否一致 |
| --- | --- | --- | --- | --- | --- |
| $2$ | $3$ | $0.666$ | $0$ | $0$（样例） | ✅ 同号（正/正） |
| $-8699$ | $-1551$ | $5.608$ | $5$ | $5$（`problem2`） | ✅ 同号（负/负） |
| $-5190$ | $930$ | $-5.580$ | $-6$ | $-5$（`problem3`） | ❌ 异号 |
| $17401$ | $-3524$ | $-4.938$ | $-5$ | $-4$（`problem7`） | ❌ 异号 |

两种取整只在**异号**时分岔：同号时商非负，floor 与 trunc 重合；异号时商为负，floor 比 trunc 恰好小 1。真实数据 10 个测例中 8 个是异号，所以关键不是算除法，而是把"向零取整"正确翻译成 Python。

推导落地方式：trunc 可以分解为"绝对值上做 floor、最后补回符号"，即 $\operatorname{trunc}(s/c) = \operatorname{sign}(s)\cdot\lfloor|s|/|c|\rfloor$。在 Python 里用一次乘积符号分流：

- **同号**（$s \cdot c \geqslant 0$，含 $s = 0$）：floor 与 trunc 本就相等，直接 `total // c`；
- **异号**（$s \cdot c < 0$）：$-s$ 与 $c$ 同号，`(-s) // c` 恰好是 $\lfloor |s|/|c| \rfloor$，取负即得 trunc。

于是整题归结为一个二选一表达式 `total // c if total * c >= 0 else -(-total // c)`，全程整数运算、无循环。备选写法 `int((a + b) / c)` 用浮点除法再截断，在本题范围内结果也对，但把一步整数运算交给浮点舍入是多余的风险，故不采用。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(1)$：一次读入、一次乘法判号、一次整数除法，与输入规模无关。
- 空间复杂度：$O(1)$：只保存三个输入整数、和与商，无数组与递归。

## 总结

这道题考的是**两种取整语义的区别**：Python 的 `//` 是向下取整，C 的整数除法是向零取整，两者只在被除数与除数异号时相差 1。解法是判号分流——同号直接 `//`，异号先取负再 `//` 最后补负号，等价于"绝对值做除法、再加回符号"。注意不要直接写 `(a + b) // c`（负数测例必挂），也不必引入 `int(x / y)` 的浮点写法。实测 10 个评测点全部一致，单点约 0.018 s、峰值内存 14.5 MB，相对 1000 ms / 128 MB 的限制十分宽裕。
