---
oj: "luogu"
problem_id: "P5710"
title: "【深基3.例2】数的性质"
description: "先写出两个布尔性质，再用 and、or、异或和 not 得到四个输出。"
difficulty: "入门"
date: 2026-07-15 18:02
toc: true
tags: ["python", "入门", "条件判断", "布尔表达式"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5710
---

[[TOC]]

### 题意

整数有两个性质：

- 性质 `a`：是偶数；
- 性质 `b`：大于 `4` 且不大于 `12`。

按顺序输出四个人是否喜欢这个数：

- 小 A：两个性质同时满足；
- Uim：至少满足一个；
- 小 B：刚好满足一个；
- 正妹：两个都不满足。

### 思路

先把两个性质写成布尔变量：

```python
a = x % 2 == 0
b = 4 < x <= 12
```

然后四个答案分别是：

- `a and b`
- `a or b`
- `a != b`
- `not (a or b)`

最后把布尔值用 `int(...)` 转成 `1` 或 `0` 输出。

`brute.py` 不适合这题，因为这是一道布尔表达式练习题，没有算法优化过程。

### Python 知识

- `x % 2 == 0` 判断偶数。
- Python 支持链式比较：`4 < x <= 12`。
- `and`、`or`、`not` 分别表示与、或、非。
- `a != b` 对布尔值来说相当于“刚好一个为真”。
- `int(True) == 1`，`int(False) == 0`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入和输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：空格分隔输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：整数和取模相关基础。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

布尔运算直接输出：

@include-code(./main-pythonic.py, python)

### 复杂度

只做常数次判断，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

布尔题不要急着写嵌套 `if`。先把基本性质命名成变量，再组合 `and`、`or`、`not`，代码会更接近题意。
