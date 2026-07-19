---
oj: "luogu"
problem_id: "P5708"
title: "【深基2.习2】三角形面积"
description: "用海伦公式计算面积，再用格式化字符串保留一位小数。"
difficulty: "入门"
date: 2026-07-15 17:56
toc: true
tags: ["python", "入门", "数学", "浮点"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5708
---

[[TOC]]

### 题意

给出三角形三边 $a,b,c$，用海伦公式计算面积：

$$
p=\frac{a+b+c}{2},\quad S=\sqrt{p(p-a)(p-b)(p-c)}
$$

输出面积，保留 $1$ 位小数。

### 思路

题目已经给出公式。Python 中可以从 `math` 模块导入 `sqrt` 计算平方根，然后用 f-string 控制输出为一位小数。

`brute.py` 不适合这题，因为没有可枚举的方案空间；公式计算就是完整解法。

### Python 知识

- `from math import sqrt` 只导入平方根函数，调用时直接写 `sqrt(...)`。
- `map(float, input().split())` 把三个输入 token 转成浮点数。
- `/` 是浮点除法，计算半周长 `p` 很自然。
- `f"{area:.1f}"` 控制输出固定 $1$ 位小数。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：浮点输入和格式化输出背景。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：按题面控制输出格式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：常用数学工具与浮点注意事项。

### 代码

@include-code(./main.py, python)



### 复杂度

只做常数次浮点运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

公式题要把题目给出的数学式直接翻译成代码。输出精度是这题最容易漏的细节，最后用 `:.1f` 固定一位小数。
