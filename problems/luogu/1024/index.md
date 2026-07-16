---
oj: "luogu"
problem_id: "P1024"
title: "[NOIP 2001 提高组] 一元三次方程求解"
description: "扫描相邻整数区间定位变号区间，再用浮点二分逼近三个互异实根。"
difficulty: "普及/提高-"
date: 2026-07-16 17:49
toc: true
tags: ["二分", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1024
---

[[TOC]]

### 题意

求一元三次方程在 $[-100,100]$ 内的三个不同实根，按从小到大输出并保留两位小数。任意两根之差至少为 `1`。

### 思路

相邻两根至少相差 `1`，因此依次检查每个整数区间 `[i,i+1]`，每个区间至多含一个根。

- 若 `f(i)=0`，整数 `i` 本身就是根；
- 若 `f(i)` 与 `f(i+1)` 异号，根据连续函数零点定理，区间内有一个根；
- 对变号区间执行 60 次二分，精度远高于输出需要的两位小数。

计算多项式使用霍纳法：`((a*x+b)*x+c)*x+d`，既简短又少做乘法。

### Python 知识

- Python 的 `float` 足以满足本题误差要求；固定迭代次数可以避免纠结浮点终止条件。
- `f"{root:.2f}"` 按两位小数格式化输出。
- 列表推导式用于把非常接近 `0` 的根规范成 `0.0`，避免输出 `-0.00`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：浮点输入和格式化输出。

### 代码

@include-code(./main.py, python)

### 复杂度

只扫描 200 个整数区间，每个根二分 60 次，时间复杂度可视为 $O(1)$；根列表使用 $O(1)$ 空间。

### 总结

根间距保证让“逐个整数区间定位”成立；先处理整数根，再对变号区间二分，可以避免边界根被重复记录。
