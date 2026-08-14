---
oj: "luogu"
problem_id: "P5722"
title: "【深基4.例11】数列求和"
description: "按题意用 for 循环逐项累加 1 到 n，避免直接套等差数列公式。"
difficulty: "入门"
date: 2026-07-15 18:26
toc: true
tags: ["入门", "循环", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5722
---

[[TOC]]

### 题意

输入正整数 `n`，求：

$$
1+2+3+\cdots+n
$$

题目明确要求不要直接使用等差数列求和公式，所以这里练习循环累加。

### 思路

用变量 `answer` 保存当前已经累加出来的和。

从 `1` 到 `n` 依次枚举每个数 `x`，每次执行：

```text
answer = answer + x
```

循环结束后，`answer` 就是 `1` 到 `n` 的总和。

这题本身就是循环语法练习，`brute.py` 会和正解完全相同，因此不创建额外暴力文件。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `int(input())` 读取一个整数。
- `range(1, n + 1)` 会生成 `1, 2, ..., n`，右端点 `n + 1` 不会被取到。
- `answer += x` 是 `answer = answer + x` 的简写，适合表达累加。
- `print(answer, end="")` 输出最终答案。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### Pythonic 写法

等差公式：

@include-code(./main-pythonic.py, python)


### 复杂度

循环执行 `n` 次，时间复杂度是 $O(n)$；只使用一个累加变量，空间复杂度是 $O(1)$。

### 总结

这题要训练的是“从左到右逐项累加”的基本循环模式。以后遇到前缀和、计数、统计类问题，也会反复用到这个写法。
