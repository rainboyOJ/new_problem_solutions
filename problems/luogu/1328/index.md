---
oj: "luogu"
problem_id: "P1328"
title: "[NOIP 2014 提高组] 生活大爆炸版石头剪刀布"
description: "用胜负表判断每轮结果，并用取模从双方周期序列中取当前手势。"
difficulty: "普及-"
date: 2026-07-15 21:35
toc: true
tags: ["模拟", "周期", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1328
---

[[TOC]]

### 题意

小 A 和小 B 各有一个周期出拳序列，一共比赛 `N` 轮。每轮按五种手势的胜负关系决定得分，平局不得分。输出两人的总分。

### 思路

先把胜负关系写成表 `win[a][b]`：

```text
win[a][b] = 1 表示手势 a 能赢手势 b
```

第 `round_index` 轮时：

```python
gesture_a = pattern_a[round_index % length_a]
gesture_b = pattern_b[round_index % length_b]
```

用取模就能循环使用周期序列。然后查表给胜者加分。

这题是周期模拟和查表练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数数组用 `list(map(int, input().split()))` 读取。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：二维列表可以作为固定规则表使用。
- `% length` 是周期访问的常用写法。
- 查表比写大量 `if` 更稳定。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

模拟 `N` 轮，每轮常数时间，时间复杂度是 $O(N)$，空间复杂度是 $O(N_A+N_B)$。

### 总结

周期模拟题通常用下标取模；规则复杂但规模固定时，用表格表达胜负关系更清楚。
