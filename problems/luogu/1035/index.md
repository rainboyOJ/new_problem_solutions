---
oj: "luogu"
problem_id: "P1035"
title: "[NOIP 2002 普及组] 级数求和"
description: "用 while 循环累加调和级数，直到前缀和第一次严格超过 k。"
difficulty: "入门"
date: 2026-06-18 20:24
toc: true
tags: ["模拟", "数学", "循环", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1035
---

[[TOC]]

### 题意

给出正整数 `k`，求最小的 `n`，使得：

$$
1+\frac{1}{2}+\frac{1}{3}+\cdots+\frac{1}{n} > k
$$

注意是不等式右边的 `k` 被“严格超过”。

### 思路

从 `n = 0`、当前和 `total = 0` 开始，每次先让 `n` 增加 `1`，再把第 `n` 项 `1 / n` 加进 `total`。

只要 `total <= k`，说明还没有超过 `k`，必须继续加下一项。循环停止时，第一次满足 `total > k`，当前的 `n` 就是题目要求的最小项数。

这题的范围只有 `k <= 15`，直接循环模拟足够；额外写暴力程序只会重复同一个过程，所以 Python 教学版不再创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：本题使用 `int(input())` 读取一个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：本题涉及浮点累加，但只需要判断是否超过整数 `k`，在数据范围内直接使用 `float` 足够。
- `while total <= k:` 很贴合“直到第一次超过”的题意，比先猜循环次数更自然。
- `print(n, end="")` 可以避免输出多余空行；洛谷通常允许末尾换行，不过这里保持输出精确。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

调和级数：

@include-code(./main-pythonic.py, python)

### 复杂度

设答案为 `n`。循环执行 `n` 次，时间复杂度是 $O(n)$，空间复杂度是 $O(1)$。

### 总结

这题的核心是把“最小的 `n`”翻译成循环停止条件：一直累加到前缀和第一次严格大于 `k`。
