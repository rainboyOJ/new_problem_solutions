---
oj: "luogu"
problem_id: "P1421"
title: "小玉买文具"
description: "先把元角统一换成角，再用整除计算最多能买多少支笔。"
difficulty: "入门"
date: 2026-07-15 17:56
toc: true
tags: ["python", "入门", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1421
---

[[TOC]]

### 题意

小玉有 `a` 元 `b` 角。一支签字笔价格是 `1` 元 `9` 角，求最多可以买多少支。

### 思路

先统一单位，把所有钱都换成“角”：

- `a` 元 `b` 角等于 `a * 10 + b` 角；
- 一支笔等于 `19` 角。

最多能买多少支，就是总角数里有多少个完整的 `19`，用整数除法即可。

`brute.py` 不适合这篇 Python 教学题解。虽然可以每次减去 `19` 角来模拟购买，但本题真正要训练的是单位换算和 `//` 整除。

### Python 知识

- `//` 是整数除法，结果向下取整，正好表示“最多能买多少个完整物品”。
- `money = a * 10 + b` 把复合单位转成单一单位。
- `print(money // 19)` 直接输出整数答案。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入与输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：整数运算与 `divmod`/整除关系。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个答案输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

整数运算：

@include-code(./main-pythonic.py, python)


### 复杂度

只做常数次运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

遇到元角、小时分钟这类复合单位，先统一成一个最小单位。统一之后，很多题就只剩一次整除或取余。
