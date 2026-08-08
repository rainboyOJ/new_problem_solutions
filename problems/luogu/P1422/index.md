---
oj: "luogu"
problem_id: "P1422"
title: "小玉家的电费"
description: "按用电量所在区间分段计费，最后用一位小数格式化输出。"
difficulty: "入门"
date: 2026-07-15 18:12
toc: true
tags: ["python", "入门", "条件判断", "浮点"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1422
---

[[TOC]]

### 题意

给出月用电量，按三段电价计算电费：

- `150` 千瓦时及以下：每千瓦时 `0.4463` 元；
- `151..400` 的超出部分：每千瓦时 `0.4663` 元；
- `401` 及以上的超出部分：每千瓦时 `0.5663` 元。

输出电费，保留 1 位小数。

### 思路

这是分段计费。按照用电量所在区间分类：

- 如果不超过 `150`，全部按第一段价格；
- 如果不超过 `400`，先算前 `150`，再算超出部分；
- 否则先算前两段，再算超过 `400` 的部分。

`brute.py` 不适合这题，因为分段公式就是完整解法。

### Python 知识

- `if / elif / else` 适合互斥区间。
- 浮点数可以直接保存单价并参与乘法。
- `f"{fee:.1f}"` 表示保留小数点后 1 位输出。
- 分段计费时，不要把所有电量都按最后一段价格算，只对超出部分使用更高单价。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入和浮点输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：控制浮点小数位数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：浮点数注意事项。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

match-case：

@include-code(./main-pythonic.py, python)

### match-case 写法

分段电价可用 guard 按用电量区间匹配：

@include-code(./match_case.py, python)

### 复杂度

只做常数次判断和计算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

分段计费的关键是“每一段只算自己负责的区间”。代码中把前面完整区间先算掉，再处理最后的超出部分，最不容易错。
