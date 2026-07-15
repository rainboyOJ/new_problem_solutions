---
oj: "luogu"
problem_id: "P5714"
title: "【深基3.例7】肥胖问题"
description: "计算 BMI 后按区间分支，超重时用 .6g 输出六位有效数字。"
difficulty: "入门"
date: 2026-07-15 18:07
toc: true
tags: ["python", "入门", "条件判断", "浮点"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5714
---

[[TOC]]

### 题意

输入体重 `m` 和身高 `h`，计算 BMI：

$$
BMI=\frac{m}{h^2}
$$

如果 BMI 小于 `18.5` 输出 `Underweight`；如果小于 `24` 输出 `Normal`；否则先输出 BMI，再输出 `Overweight`。

### 思路

先计算 `bmi = m / (h * h)`，再按区间判断：

- `bmi < 18.5`
- `18.5 <= bmi < 24`
- `bmi >= 24`

Python 中按顺序写 `if / elif / else`，第二个分支只需要写 `bmi < 24`，因为能到这里说明前一个条件已经不成立。

`brute.py` 不适合这题，因为它是公式计算和区间分支题。

### Python 知识

- `map(float, input().split())` 读取浮点数。
- `h * h` 表示 $h^2$，比写 `h ** 2` 更直观也可以。
- `if / elif / else` 适合互斥区间分类。
- `f"{bmi:.6g}"` 表示六位有效数字，并自动去掉不必要的后缀 `0`，符合本题非 C++ 输出要求。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：浮点输入与输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：控制浮点输出格式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：浮点数注意事项。

### 代码

@include-code(./main.py, python)

### 复杂度

只做常数次浮点运算和比较，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

区间分类题适合按边界从小到大写分支。浮点输出要仔细看题面是“几位小数”还是“几位有效数字”，本题是有效数字。
