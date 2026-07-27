---
oj: "luogu"
problem_id: "P1200"
title: "[USACO1.1] 你的飞碟在这儿 Your Ride Is Here"
description: "把名字中字母编号连乘并始终对 47 取模，比较彗星名和团队名的余数。"
difficulty: "入门"
date: 2026-07-15 21:01
toc: true
tags: ["字符串", "模拟", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1200
---

[[TOC]]

### 题意

给定彗星名和团队名。把每个字母转成 `A=1, B=2, ..., Z=26`，分别计算所有字母编号的乘积。如果两个乘积对 `47` 的余数相同，输出 `GO`，否则输出 `STAY`。

### 思路

写一个函数 `name_value(name)`，扫描名字中的每个大写字母：

```text
编号 = ord(ch) - ord("A") + 1
```

乘积可能变大，但只关心模 `47` 的结果，所以每乘一次就取模：

```python
result = result * 编号 % 47
```

最后比较两个名字的结果即可。

这题是字符编号和取模练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `input().strip()` 读取不含空格的字符串。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：取模可以控制中间数大小，并保留余数信息。
- `ord(ch)` 可以得到字符编码，适合把大写字母转成 `1..26`。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

`functools.reduce` 计算名字乘积模 47：

@include-code(./main-pythonic.py, python)

### 复杂度

名字长度最多为 6，时间复杂度和空间复杂度都可视为 $O(1)$。

### 总结

字母编号题常用 `ord(ch) - ord("A") + 1`。只比较余数时，可以在连乘过程中持续取模。
