---
oj: "luogu"
problem_id: "P5727"
title: "【深基5.例3】冰雹猜想"
description: "按奇偶规则模拟冰雹序列，把经过的数存入列表后反转输出。"
difficulty: "入门"
date: 2026-07-15 18:44
toc: true
tags: ["模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5727
---

[[TOC]]

### 题意

给出正整数 `n`。不断执行：

- 如果 `n` 是奇数，变成 `3n + 1`；
- 如果 `n` 是偶数，变成 `n / 2`。

直到变成 `1`。要求从最后的 `1` 开始，倒序输出整个变化序列。

### 思路

先按题意正向模拟，把每次出现的数字加入列表 `sequence`。

当 `n != 1` 时继续循环。每轮根据奇偶选择下一步：

```text
奇数：n = n * 3 + 1
偶数：n = n // 2
```

循环结束后，`sequence` 中保存的是从初始值到 `1` 的顺序。题目要求倒序输出，所以反转列表后输出即可。

这题是列表保存过程再倒序输出的练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `int(input())` 读取单个整数，用 `print(*sequence)` 输出列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`//` 是整数除法，适合偶数除以 `2`。
- `n % 2 == 1` 判断奇数。
- `sequence.append(n)` 保存过程值，`sequence.reverse()` 原地反转。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

用条件表达式写奇偶变换，`sequence[::-1]` 切片反转输出：

@include-code(./main-pythonic.py, python)

### 复杂度

设序列长度为 `k`。模拟和反转都是 $O(k)$，空间复杂度是 $O(k)$。

### 总结

这题不要一边倒序一边输出。先把正向过程存下来，再反转输出，代码更直接，也更容易检查。
