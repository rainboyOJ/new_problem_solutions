---
oj: "luogu"
problem_id: "P1909"
title: "[NOIP 2016 普及组] 买铅笔"
description: "对三种包装分别用整数公式向上取整包数，再取最小花费。"
difficulty: "入门"
date: 2026-07-15 18:12
toc: true
tags: ["python", "入门", "数学", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1909
---

[[TOC]]

### 题意

要买至少 `n` 支铅笔。商店有三种包装，每种包装给出每包支数和价格。只能选择一种包装，不能拆包。求买够至少 `n` 支的最小花费。

### 思路

对每种包装独立计算：

1. 每包有 `count` 支；
2. 至少需要的包数是向上取整 `ceil(n / count)`；
3. 花费是 `packs * price`。

Python 中常用整数公式写向上取整：

```python
packs = (n + count - 1) // count
```

三种包装算出三个花费后取最小值即可。

这题已有旧 C++ 版本；本篇重点是 Python 中的整除公式和 `min` 更新。`brute.py` 不再单独写，因为三种包装直接公式比较已经足够清楚。

### Python 知识

- `(n + count - 1) // count` 是正整数向上取整的常用写法。
- `answer = 10**18` 可以作为很大的初始最小值。
- `answer = min(answer, cost)` 用来维护当前最小花费。
- `for _ in range(3)` 表示循环 3 次，但循环变量本身不重要。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：整数运算、最值初始化。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入与输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行输入格式。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

min + ceil 推导：

@include-code(./main-pythonic.py, python)


### 复杂度

只处理 3 种包装，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

不能拆包的问题经常会出现向上取整。只要每种方案互不影响，就分别算成本，再用 `min` 选最小。
