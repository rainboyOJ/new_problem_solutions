---
oj: "luogu"
problem_id: "P5711"
title: "【深基3.例3】闰年判断"
description: "按闰年定义组合取模条件，并把布尔结果转成 0/1 输出。"
difficulty: "入门"
date: 2026-07-15 18:02
toc: true
tags: ["python", "入门", "条件判断", "取模"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5711
---

[[TOC]]

### 题意

输入一个年份，判断它是否是闰年。闰年的规则是：

- 能被 `4` 整除，并且不能被 `100` 整除；
- 或者能被 `400` 整除。

满足其中一种情况输出 `1`，否则输出 `0`。

### 思路

直接把定义翻译成布尔表达式：

```python
is_leap = (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)
```

这里括号很重要，它让“普通闰年”和“世纪闰年”两种情况分得很清楚。最后用 `int(is_leap)` 输出 `1` 或 `0`。

`brute.py` 不适合这题，因为闰年定义本身就是判定规则。

### Python 知识

- `year % k == 0` 判断年份能否被 `k` 整除。
- `and` 的优先级高于 `or`，但写括号能让逻辑更容易检查。
- `!=` 表示不等于。
- `int(True)` 为 `1`，`int(False)` 为 `0`，适合这种需要输出 `0/1` 的题。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入和输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：整数取模和数学工具。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个答案输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

match-case：

@include-code(./main-pythonic.py, python)

### match-case 写法

闰年规则可用 guard 写成 `case y if ...`：

@include-code(./match_case.py, python)

### 复杂度

只做常数次取模和布尔判断，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

条件判断题的关键是忠实翻译定义。把两类闰年分别写在括号里，再用 `or` 连接，最不容易把规则写反。
