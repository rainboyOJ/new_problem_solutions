---
oj: "luogu"
problem_id: "P1572"
title: "计算分数"
description: "用正则提取带符号分数，并交给 fractions.Fraction 自动完成精确运算与约分。"
difficulty: "入门"
date: 2026-06-19 10:22
toc: true
tags: ["字符串", "分数", "正则表达式", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1572
---

[[TOC]]

### 题意

计算只含分数加减的表达式，输出整数或最简分数。

### 思路

表达式中的每一项都符合“可选正负号 + 分子 + `/` + 分母”。正则 `[+-]?\d+/\d+` 可以按原顺序提取全部项。

Python 标准库 `Fraction` 能从 `"-1/4"` 这样的字符串建立精确有理数，并自动通分、约分。将所有项映射为 `Fraction` 后求和即可。

若最终分母为 `1`，只输出分子；否则 `Fraction` 的字符串形式已经是最简的 `p/q`。

### Python 知识

- `re.findall` 返回所有不重叠匹配，符号会与后面的分数一起保留。
- `map(Fraction,tokens)` 惰性地把每个字符串转换为精确分数。
- `sum(...,Fraction())` 指定有理数零作为初值。
- `Fraction.numerator/denominator` 直接访问最简分子分母。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：`map` 和 `sum` 归约。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串提取和输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

表达式长度不超过 100，解析为 $O(n)$；有理数运算还包含整数 gcd 的对数代价。额外空间 $O(n)$。

### 总结

标准库已经完整封装了有理数运算。识别并正确使用 `Fraction`，比手写解析、通分和约分更短也更可靠。
