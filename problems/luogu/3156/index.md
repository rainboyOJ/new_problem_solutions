---
oj: "luogu"
problem_id: "P3156"
title: "【深基15.例1】询问学号"
description: "保存按入场顺序排列的学号列表，把每个一号起始询问转换成 Python 列表下标。"
difficulty: "入门"
date: 2026-07-16 18:10
toc: true
tags: ["列表", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3156
---

[[TOC]]

### 题意

按进教室顺序给出 `n` 个学号。每次询问第 `i` 个进入的学生学号，逐行输出答案。

### 思路

顺序固定且只查询位置，直接把学号按入场顺序存起来。题目编号从 `1` 开始，下标从 `0` 开始，因此查询 `position` 的答案是 `student_ids[position-1]`。

注意：`n <= 2e6`。若写成

```python
data = list(map(int, sys.stdin.buffer.read().split()))
```

会瞬间创建约 `n+m` 个 Python `int` 对象，常数很大，容易在大数据上 **TLE / MLE**，小样例仍正确，分数常停在 30 分左右。

更稳妥的做法：

1. `sys.stdin.buffer.read().split()` 只得到 `bytes` token；
2. 学号用 `array("i", ...)` 存成连续整型数组；
3. 查询时再 `int(token)`，答案用 `"\n".join` 一次写出。

### Python 知识

- `array("i")` 存 32 位有符号整数，比 `list[int]` 省对象开销。
- 大数据输入优先 `sys.stdin.buffer.read()`，避免逐行 `input()`。
- `"\n".join(...)` 比十万次 `print` 更适合批量输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数 token 与多行输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

下标查询生成器：

@include-code(./main-pythonic.py, python)


### 复杂度

读入为 $O(n+m)$，每个查询 $O(1)$；保存数据和答案需要 $O(n+m)$ 空间。

### 总结

先辨认操作需求：只有按位置查询时，连续列表就是最简单、最高效的数据结构。
