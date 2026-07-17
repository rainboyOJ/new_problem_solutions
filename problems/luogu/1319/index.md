---
oj: "luogu"
problem_id: "P1319"
title: "压缩技术"
description: "按游程长度交替展开 0 和 1，再每 n 个字符切成一行输出矩阵。"
difficulty: "入门"
date: 2026-07-15 18:58
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1319
---

[[TOC]]

### 题意

输入压缩码。第一个数是矩阵大小 `n`，后面的数依次表示连续 `0`、连续 `1`、连续 `0`……的长度。要求还原 `n * n` 的 `01` 矩阵。

### 思路

压缩码本质是游程编码。先从字符 `"0"` 开始，遇到一个长度 `length`，就把当前字符重复 `length` 次加入一维列表 `cells`，然后把当前字符在 `"0"` 和 `"1"` 之间切换。

展开完成后，`cells` 长度正好是 `n*n`。第 `row` 行对应：

```text
cells[row*n : row*n+n]
```

把这一段拼接成字符串输出即可。

这题是字符串展开和切片练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `sys.stdin.read().split()` 读取所有整数，输入换行方式不影响解析。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：切片 `cells[left:right]` 适合取出一行。
- `cells.extend(value for _ in range(length))` 批量追加重复字符。
- `"".join(...)` 把字符列表拼成一行。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

用 `cycle("01")` 与 `repeat` / `chain` 展开游程，再按行切片输出：

@include-code(./main-pythonic.py, python)

### 复杂度

展开和输出都处理 `n^2` 个字符，时间复杂度是 $O(n^2)$，空间复杂度是 $O(n^2)$。

### 总结

解压题先按长度展开成一维序列，再按行切开。这样可以避免边展开边处理换行的混乱。
