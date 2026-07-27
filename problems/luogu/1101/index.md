---
oj: "luogu"
problem_id: "P1101"
title: "单词方阵"
description: "枚举每个起点和八个固定方向，用 all 验证 yizhong 的七个位置并统一标记。"
difficulty: "普及-"
date: 2026-07-16 18:01
toc: true
tags: ["字符串", "枚举", "网格", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1101
---

[[TOC]]

### 题意

在字母方阵中寻找所有沿同一方向连续出现的 `yizhong`。保留属于任意一个单词的字符，其余位置输出 `*`。

### 思路

枚举起点 `(x,y)` 和八个方向 `(dx,dy)`。第 `step` 个字符应位于 `(x+dx*step,y+dy*step)`。

先生成七个坐标，再用 `all` 同时检查边界和字符。如果全部匹配，就把这七个位置标记。不同单词可以交叉，因此只将标记从假改为真，不会互相覆盖。

### Python 知识

- 双层列表推导式生成八个方向，并排除 `(0,0)`。
- `zip(positions,word)` 同时遍历坐标与目标字符。
- `all(...)` 遇到第一个越界或字符不符就短路停止。
- 输出时用嵌套 `zip` 和生成器选择原字符或 `*`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：`all` 的短路判断。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：列表推导式和整体判定。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

每个格子检查八个方向，每次固定七个字符，时间复杂度为 $O(n^2)$，标记矩阵空间为 $O(n^2)$。

### 总结

方向一旦选定，七个坐标就由一个统一公式产生；用 `all` 写整体匹配，比七层手工判断更短也更不容易漏方向。
