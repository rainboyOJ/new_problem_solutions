---
oj: "luogu"
problem_id: "P3743"
title: "小鸟的设备"
description: "二分共同运行时间，汇总各设备在该时刻前的能量缺口并与充电宝供能比较。"
difficulty: "普及/提高-"
date: 2026-07-16 17:49
toc: true
tags: ["二分答案", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3743
---

[[TOC]]

### 题意

多个设备同时耗能，一个充电宝可以随时在设备间切换。求所有设备能共同运行的最长时间；若可以无限运行则输出 `-1`。

### 思路

若所有设备每秒总消耗不超过充电宝功率 `p`，初始能量耗尽后也能持续供能，答案为无限。

否则二分运行时间 `t`。设备 `(a,b)` 在 `t` 秒内消耗 `a*t`，超过初始能量 `b` 的部分必须由充电宝补充，所以总需求为：

$$
\sum \max(0,a_i t-b_i)
$$

若总需求不超过 `p*t`，时间 `t` 可行。可行时间构成从零开始的连续区间，因此可以浮点二分最大可行值。

### Python 知识

- `zip(data[2::2], data[3::2])` 把交错输入重组成 `(消耗, 初始能量)` 元组。
- 两个生成器 `sum(...)` 分别计算总消耗和给定时间的总能量缺口。
- Python 的 `float` 与 100 次二分足以满足相对误差要求。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：用生成器汇总一次性聚合结果。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数读取与浮点输出。

### 代码

@include-code(./main.py, python)

### 复杂度

每次判定扫描全部设备，总时间复杂度为 $O(100n)=O(n)$，保存设备需要 $O(n)$ 空间。

### 总结

充电宝可以任意切换，因此无需模拟具体充电顺序；只要比较时间区间内“总缺口”和“总供能”即可。
