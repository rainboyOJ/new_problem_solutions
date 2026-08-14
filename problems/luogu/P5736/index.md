---
oj: "luogu"
problem_id: "P5736"
title: "【深基7.例2】质数筛"
description: "写 is_prime 函数用试除法判断质数，再用列表推导式保留输入中的质数。"
difficulty: "入门"
date: 2026-07-15 21:08
toc: true
tags: ["数学", "质数", "函数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5736
---

[[TOC]]

### 题意

输入 `n` 个不超过 `100000` 的正整数，按原顺序输出其中所有质数。

### 思路

先写一个质数判断函数：

- 小于 2 的数不是质数；
- 从 2 开始试除；
- 只需要检查到 `divisor * divisor <= x`，因为如果 `x` 有大于平方根的因子，必然还有一个小于平方根的配对因子。

然后扫描输入数组，保留所有满足 `is_prime(x)` 的数。

数据只有 `n <= 100`，试除法足够。题目名叫“质数筛”，但这里直接判断每个数更适合初学函数练习。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`list(map(int, input().split()))` 读取整数数组。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：列表推导式 `[x for x in numbers if ...]` 适合筛选结果。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：用 `divisor * divisor <= x` 避免浮点平方根误差。
- `print(*answer)` 按空格输出列表元素。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### 复杂度

设最大数为 `A`，共有 `n` 个数。每个数试除到平方根，时间复杂度是 $O(n\sqrt A)$，空间复杂度是 $O(n)$。

### 总结

质数判断适合封装成函数。筛选数组时，列表推导式能清楚表达“保留满足条件的元素”。
