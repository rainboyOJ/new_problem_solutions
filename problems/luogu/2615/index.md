---
oj: "luogu"
problem_id: "P2615"
title: "[NOIP 2015 提高组] 神奇的幻方"
description: "按奇阶幻方规则从首行中间开始填数，优先走右上格，已占用则向下。"
difficulty: "普及-"
date: 2026-07-15 18:48
toc: true
tags: ["模拟", "矩阵", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2615
---

[[TOC]]

### 题意

给出奇数 `N`，按题面规则构造一个 `N * N` 幻方，并输出矩阵。

规则可以概括为：从第一行中间放 `1`，之后每次尝试把下一个数放到上一个数的右上方；如果右上方越界就循环到另一边；如果右上方已经填过，就放到上一个数的正下方。

### 思路

用二维列表 `square` 保存矩阵，空位置用 `0` 表示。

当前位置是 `(row, col)`。填入当前数字后，先计算右上方：

```text
next_row = (row - 1) % n
next_col = (col + 1) % n
```

取模可以自然处理“从第一行跳到最后一行”“从最后一列跳到第一列”。

如果 `square[next_row][next_col] == 0`，说明右上方没有填过，就移动过去。否则移动到当前格子的正下方。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：二维矩阵可以用列表推导式创建。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`print(*line)` 可以把一行矩阵用空格输出。
- `% n` 可以把越界行列绕回矩阵另一侧。
- `[[0 for _ in range(n)] for _ in range(n)]` 能创建互不共享的二维列表。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

幻方模拟精简：

@include-code(./main-pythonic.py, python)

### 复杂度

一共填 `n^2` 个数，时间复杂度是 $O(n^2)$，矩阵空间复杂度是 $O(n^2)$。

### 总结

这题的难点是把题面的四种边界情况统一成“右上取模”。再加一个“目标格已占用则向下”的判断，代码会比逐条分支更短。
