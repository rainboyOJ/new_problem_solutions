---
oj: "luogu"
problem_id: "P1067"
title: "[NOIP 2009 普及组] 多项式输出"
description: "按次数从高到低扫描非零项，分类处理首项符号、系数 1 和指数 0/1/>1 的输出格式。"
difficulty: "入门"
date: 2026-06-19 10:02
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1067
---

[[TOC]]

### 题意

给出一元多项式从高次到常数项的系数，按题目格式输出多项式。要跳过系数为 `0` 的项，并处理符号、系数 `1`、指数等格式细节。

### 思路

把“输出一项”封装成函数：

```python
format_term(coefficient, power, is_first)
```

它负责处理：

- 首项正号省略，非首项需要 `+` 或 `-`；
- 负数项输出 `-`；
- 非常数项系数绝对值为 `1` 时不输出 `1`；
- 指数为 `0`、`1`、大于 `1` 时分别输出常数、`x`、`x^k`。

主程序从高次到低次扫描，跳过 `0` 系数，把每一项字符串加入列表，最后 `"".join(terms)`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用列表收集字符串片段后 `join`，比反复拼接更清楚。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：频繁字符串拼接会产生新字符串，列表收集适合构造答案。
- `enumerate(coefficients)` 可以同时得到系数位置和系数值。
- `not terms` 可以判断当前是否还没有输出过任何项。

### 代码

@include-code(./main.py, python)


### 复杂度

扫描 `n+1` 个系数，时间复杂度是 $O(n)$，空间复杂度是 $O(n)$。

### 总结

格式模拟题不要把所有规则塞进主循环。把一项的格式化单独写成函数，主流程会更稳定。
