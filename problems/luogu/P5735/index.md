---
oj: "luogu"
problem_id: "P5735"
title: "【深基7.例1】距离函数"
description: "把两点距离封装成函数，用 hypot 计算三条边长并格式化输出周长。"
difficulty: "入门"
date: 2026-07-15 21:08
toc: true
tags: ["数学", "函数", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5735
---

[[TOC]]

### 题意

给出平面上三个点的坐标，求它们围成的三角形周长，结果保留两位小数。

### 思路

两点距离公式是：

```text
sqrt((x1-x2)^2 + (y1-y2)^2)
```

Python 标准库 `math.hypot(dx, dy)` 可以直接计算 `sqrt(dx*dx + dy*dy)`。把距离计算封装成函数：

```python
def distance(p, q):
    return hypot(p[0] - q[0], p[1] - q[1])
```

读入三个点后，分别计算三条边并相加即可。

这题是函数封装和浮点格式化练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(float, input().split())` 读取一行两个实数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：浮点计算和格式化输出时要关注误差与保留位数。
- `math.hypot(dx, dy)` 表达二维距离更直接。
- `f"{perimeter:.2f}"` 输出两位小数。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### 复杂度

只处理三个点，时间复杂度和空间复杂度都是 $O(1)$。

### 总结

重复使用的公式适合封装成函数。浮点题按题目要求用格式化字符串控制输出位数。
