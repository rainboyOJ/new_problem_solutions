---
oj: "luogu"
problem_id: "P1980"
title: "[NOIP 2013 普及组] 计数问题"
description: "把 1 到 n 的每个数转成字符串，用 count 统计目标数字出现次数并求和。"
difficulty: "入门"
date: 2026-07-15 18:22
toc: true
tags: ["python", "入门", "字符串", "计数"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1980
---

[[TOC]]

### 题意

给定 `n` 和一个数字 `x`，统计从 `1` 到 `n` 的所有整数中，数字 `x` 一共出现多少次。

### 思路

本题数据范围是 `n <= 10^6`。Python 直接枚举每个整数，把它转成字符串后用 `count` 统计目标字符出现次数，足够通过。

```python
sum(str(number).count(target) for number in range(1, n + 1))
```

`brute.py` 不适合这篇 Python 教学题解；这里的直接字符串计数就是完整且清晰的做法。

### Python 知识

- `target = str(x)` 把目标数字转成字符。
- `str(number)` 把整数转成十进制字符串。
- `"111".count("1")` 会返回 `3`。
- 生成器表达式可以和 `sum` 配合，把每个数中的出现次数累加起来。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串转换和常用字符串操作。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器表达式与 `sum`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：计数问题的常见表达方式。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

str.count 统计：

@include-code(./main-pythonic.py, python)

### 复杂度

枚举 `1..n`，每个数最多约 7 位，时间复杂度可以看作 $O(n\log n)$ 的字符串处理量；本题 `n <= 10^6` 可以接受。空间复杂度 $O(1)$。

### 总结

当数据范围允许时，字符串化计数是最直接的做法。先写出清楚正确的版本，再考虑数位统计优化，会更适合入门学习。
