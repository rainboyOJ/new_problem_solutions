---
oj: "luogu"
problem_id: "P1720"
title: "月落乌啼算钱（斐波那契数列）"
description: "用两个整数变量迭代计算斐波那契数，再用格式化输出保留两位小数。"
difficulty: "入门"
date: 2026-07-15 18:35
toc: true
tags: ["数学", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1720
---

[[TOC]]

### 题意

输入自然数 `n`，输出斐波那契数列第 `n` 项 `F_n`，并保留两位小数。

本题给出了通项公式，但数据范围只有 `0 <= n <= 48`，也可以直接用递推计算。

### 思路

斐波那契数列满足：

```text
F_0 = 0
F_1 = 1
F_n = F_{n-1} + F_{n-2}
```

用两个变量维护相邻两项：

- `previous` 表示当前要输出位置之前的值；
- `current` 表示下一项。

每循环一次，执行：

```text
previous, current = current, previous + current
```

循环 `n` 次后，`previous` 就是 `F_n`。

最后题目要求输出实数且保留两位小数，因此用 `f"{previous:.2f}"` 格式化。

这题的直接递推已经足够简单，`brute.py` 与正解没有区别，所以不创建额外暴力文件。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `int(input())` 读取整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python `int` 是任意精度整数，本题 `F_48` 不会有溢出问题。
- `previous, current = current, previous + current` 是 Python 的多变量同时赋值，适合写递推状态滚动。
- `f"{previous:.2f}"` 表示按两位小数输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

斐波那契滚动：

@include-code(./main-pythonic.py, python)

### 复杂度

循环 `n` 次，时间复杂度是 $O(n)$；只用两个变量，空间复杂度是 $O(1)$。

### 总结

虽然题面给了通项公式，但在 OJ 里小范围斐波那契更适合用整数递推。这样避免浮点误差，也更容易解释和模仿。
